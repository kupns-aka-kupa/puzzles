#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFile>
#include <QList>
#include <QKeyEvent>
#include <QDebug>
#include <QAbstractItemView>
#include <QShortcut>
#include <QFontDatabase>
#include <QStandardItemModel>
#include "tablemodel.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    using Base = QMainWindow;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void rotateTableModel(const QItemSelection &selected, const QItemSelection &deselected);

protected:
    bool event(QEvent *event) override;
    void keyPressEvent(QKeyEvent *event);

private:
    TableModel *model;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
