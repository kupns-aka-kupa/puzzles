#ifndef GAME_HPP
#define GAME_HPP

#include <QObject>
#include <QElapsedTimer>

#include "tablemodel.hpp"

class Game : public QObject
{
    Q_OBJECT
public:
    enum Status
    {
        Stoped,
        InProgress
    };

    Q_ENUM(Status);

    Q_PROPERTY(Status Status WRITE setStatus MEMBER status NOTIFY statusChanged)
    explicit Game(TableModel *model, QObject *parent = nullptr);

    void setStatus(Status status);

public slots:
    void rotateTableModel(const QItemSelection &, const QItemSelection &);
    void grabModeActivated();
    void reset();
    void start();

signals:
    void started();
    void stoped();
    void statusChanged(Game::Status status);

private:
    QPixmap initTablePixmap();

    TableModel *model;
    QTableView *tableView;

    QElapsedTimer timer;
    Status status;
};

#endif // GAME_HPP
