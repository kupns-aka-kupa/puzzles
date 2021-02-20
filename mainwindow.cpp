#include "mainwindow.hpp"
#include "./static/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto tableView = ui->tableView;

    model = new TableModel(5, 5, tableView);
    tableView->setModel(model);
    tableView->setItemDelegate(new TableViewItemDelegate(tableView));
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

    QFont cellFont("mainfont.ttf", 24, QFont::Normal);
    tableView->setFont(cellFont);
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
