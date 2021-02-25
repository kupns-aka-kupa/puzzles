#include "mainwindow.hpp"
#include "./static/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , timerLabel(new QLabel(this))
    , timer(new QTimer(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto tableView = ui->tableView;
    auto statusBar = ui->statusBar;

    QList<QHeaderView*> headers
    {
        tableView->horizontalHeader(),
        tableView->verticalHeader()
    };

    foreach(auto header, headers)
    {
        header->setSectionResizeMode(QHeaderView::Stretch);
        header->hide();
    }

    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Space), tableView);

    model = new TableModel(5, 5, tableView);
    game = new Game(model, tableView);
    game->reset();

    model->applyConfig({"R0", "U0", "R3", "D1"});
    model->scramble();

    tableView->setModel(model);
    tableView->setItemDelegate(new TableViewItemDelegate(tableView));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setDragEnabled(false);

    loadFont();
    setStyleSheet();

    connect(game, SIGNAL(started()), this, SLOT(disableControls()));
    connect(game, SIGNAL(stoped()), this, SLOT(enableControls()));
    connect(ui->pushButtonScrumble, SIGNAL(clicked()), model, SLOT(scramble()));
    connect(ui->pushButtonReset, SIGNAL(clicked()), game, SLOT(reset()));
    connect(shortcut, SIGNAL(activated()), game, SLOT(grabModeActivated()));
    connect(tableView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        game,
        SLOT(rotateTableModel(const QItemSelection &, const QItemSelection &)));

    statusBar->addWidget(timerLabel);
    timer->start(100);
}

bool MainWindow::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::KeyPress:
            keyPressEvent(static_cast<QKeyEvent *>(event));
        default: break;
    }

    return Base::event(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "You Pressed Key ";
}

void MainWindow::setStyleSheet()
{
    QFile file(":/styles/styles/style.qss");
    file.open(QIODevice::ReadOnly);
    Base::setStyleSheet(file.readAll());
}

void MainWindow::loadFont()
{
    QFile file(":/fonts/fonts/mainfont.ttf");

#ifdef QT_DEBUG
    if(!file.exists())
        qDebug() << "Font file %0 does not exist"_Q.arg(file.fileName());
#endif

    int id = QFontDatabase::addApplicationFont(file.fileName());
    QString family = QFontDatabase::applicationFontFamilies(id).first();
    QFont cellFont(family, 50, QFont::Normal);
    ui->tableView->setFont(cellFont);
}

void MainWindow::timeUpdate()
{
    QString time = game->currentTime().toString("hh:mm:ss,z");
    timerLabel->setText(time);
}

void MainWindow::disableControls()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    ui->pushButtonScrumble->setEnabled(false);
}

void MainWindow::enableControls()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    ui->pushButtonScrumble->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}
