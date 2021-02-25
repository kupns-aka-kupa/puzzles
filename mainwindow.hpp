#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QFile>
#include <QList>
#include <QKeyEvent>
#include <QDebug>
#include <QAbstractItemView>
#include <QShortcut>
#include <QPalette>
#include <QFontDatabase>
#include <QStandardItemModel>
#include <QLabel>
#include <QTimer>

#include "tablemodel.hpp"
#include "palette.hpp"
#include "game.hpp"

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
    void timeUpdate();
    void disableControls();
    void enableControls();

protected:
    bool event(QEvent *event) override;
    void keyPressEvent(QKeyEvent *event);

private:
    void loadFont();
    void setStyleSheet();

    QLabel *timerLabel;
    QTimer *timer;

    TableModel *model;
    Game *game;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
