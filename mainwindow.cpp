#include "mainwindow.hpp"
#include "./static/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    model->applyConfig({"R0", "U0", "R3", "D1"});
    model->scramble();

    tableView->setModel(model);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setDragEnabled(false);

    loadFont();
    setStyleSheet();

    connect(ui->pushButtonScrumble, SIGNAL(clicked()), model, SLOT(scramble()) );
    connect(ui->pushButtonReset, SIGNAL(clicked()), model, SLOT(init()) );
    connect(shortcut, SIGNAL(activated()), model, SLOT(grabModeActivated()));
    connect(tableView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        this,
        SLOT(rotateTableModel(const QItemSelection &, const QItemSelection &)));
}

void MainWindow::rotateTableModel(
    const QItemSelection &selected,
    const QItemSelection &deselected)
{
    if(!ui->tableView->dragEnabled()
        || selected.empty()
        || deselected.empty()) return;

    auto s = deselected.first().indexes().first();
    auto f = selected.first().indexes().first();

    auto vector = QVector2D(f.row(), f.column()) - QVector2D(s.row(), s.column());
    Move move = MoveVector.key(vector.normalized());
    model->rotate(s.row(), s.column(), move);
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
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont cellFont(family, 50, QFont::Normal);
    ui->tableView->setFont(cellFont);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}
