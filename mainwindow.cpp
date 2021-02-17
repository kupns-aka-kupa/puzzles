#include "mainwindow.hpp"
#include "./static/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , model(new QStandardItemModel(5, 5))
    , delegate(new TableViewItemDelegate(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto tableView = ui->tableView;
    tableView->setModel(model);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QList<QHeaderView*> headers
    {
        tableView->horizontalHeader(),
        tableView->verticalHeader()
    };

    Q_FOREACH(auto header, headers)
    {
        header->setSectionResizeMode(QHeaderView::Stretch);
        header->hide();
    }

    QFont cellFont("mainfont.ttf", 24, QFont::Normal);
    tableView->setFont(cellFont);

    for(int i = 0; i < model->columnCount(); i++)
    {
        for(int j = 0; j < model->rowCount(); j++)
        {
            QModelIndex index = model->index(i, j, QModelIndex());
            model->setData(index, i + j);
        }
    }
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
}
