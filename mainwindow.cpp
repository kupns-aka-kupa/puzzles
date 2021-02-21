#include "mainwindow.hpp"
#include "./static/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto tableView = ui->tableView;

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

    tableView->setModel(model);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setDragEnabled(false);

    QFont cellFont("mainfont.ttf", 24, QFont::Normal);
    tableView->setFont(cellFont);

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

void loadFont()
{
    QFile file(":/fonts/static/fonts/mainfont.ttf");
    qDebug() << file.exists();
    QFontDatabase::addApplicationFont(file.fileName());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}
