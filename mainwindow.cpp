#include "mainwindow.hpp"
#include "./static/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _timerLabel(new QLabel(this))
    , _timer(new QTimer(this))
    , _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    auto tableView = _ui->tableView;
    auto statusBar = _ui->statusBar;

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

    _controls.append(_ui->pushButtonScrumble);
    _controls.append(_ui->spinBoxHeight);
    _controls.append(_ui->spinBoxWidth);

    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Space), tableView);

    _model = new TableModel(tableView);
    _game = new Game(_model, tableView);
    resetGameModel();

    _model->applyConfig({"R0", "U0", "R3", "D1"});
    _model->scramble();

    tableView->setModel(_model);
    tableView->setItemDelegate(new TableViewItemDelegate(tableView));

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setDragEnabled(false);

    loadFont();
    setStyleSheet();

    connect(_ui->spinBoxWidth, SIGNAL(editingFinished()), this, SLOT(resetGameModel()));
    connect(_ui->spinBoxHeight, SIGNAL(editingFinished()), this, SLOT(resetGameModel()));
    connect(_game, SIGNAL(started()), this, SLOT(onStarted()));
    connect(_game, SIGNAL(stoped()), this, SLOT(onStoped()));
    connect(_game, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(_ui->pushButtonScrumble, SIGNAL(clicked()), _model, SLOT(scramble()));
    connect(_ui->pushButtonReset, SIGNAL(clicked()), _game, SLOT(reset()));
    connect(shortcut, SIGNAL(activated()), _game, SLOT(grabModeActivated()));
    connect(tableView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        _game,
        SLOT(rotateTableModel(const QItemSelection &, const QItemSelection &)));

    statusBar->addWidget(_timerLabel);
    _timer->start(100);
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
    qDebug() << "Pressed Key" << event->key();
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
    _ui->tableView->setFont({family, 50, QFont::Normal});
}

void MainWindow::timeUpdate()
{
    QString time = _game->currentTime().toString("hh:mm:ss,z");
    _timerLabel->setText(time);
}

void MainWindow::onStarted()
{
    connect(_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));

    foreach(auto box, _controls)
    {
        box->setEnabled(false);
    }
}

void MainWindow::onStoped()
{
    disconnect(_timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));

    foreach(auto box, _controls)
    {
        box->setEnabled(true);
    }
    _ui->tableView->setEnabled(true);
}

void MainWindow::onFinished()
{
    _ui->tableView->setEnabled(false);
}

void MainWindow::resetGameModel()
{
    _model->setColumnCount(_ui->spinBoxWidth->value());
    _model->setRowCount(_ui->spinBoxHeight->value());
    _game->reset();
}

MainWindow::~MainWindow()
{
    delete _ui;
}
