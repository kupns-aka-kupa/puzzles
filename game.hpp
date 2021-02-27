#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>
#include <QElapsedTimer>
#include <QTime>
#include <QStateMachine>
#include <QShortcut>

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
    void finished();
    void stoped();

private slots:
    void compare(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
    void resetModel(TableModel *);
    QPixmap initTablePixmap();

    TableModel *_model;
    TableModel * const _sourceModel;
    QTableView *_tableView;

    QElapsedTimer _timer;
    QStateMachine _machine;
};

#endif // GAME_HPP
