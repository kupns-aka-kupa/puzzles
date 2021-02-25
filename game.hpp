#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>
#include <QElapsedTimer>
#include <QTime>
#include <QStateMachine>

#include "tablemodel.hpp"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(TableModel *model, QObject *parent = nullptr);

    QTime currentTime();

public slots:
    void rotateTableModel(const QItemSelection &, const QItemSelection &);
    void grabModeActivated();
    void reset();
    void start();

signals:
    void started();
    void stoped();

private:
    QPixmap initTablePixmap();

    TableModel *model;
    QTableView *tableView;

    QElapsedTimer timer;
    QStateMachine machine;
};

#endif // GAME_HPP
