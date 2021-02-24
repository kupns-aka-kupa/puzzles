#include "game.hpp"

Game::Game(TableModel *model, QObject *parent)
    : QObject(parent)
    , model(model)
    , tableView(qobject_cast<QTableView *>(parent))
{
}

void Game::rotateTableModel(
    const QItemSelection &selected,
    const QItemSelection &deselected)
{
    if(!tableView->dragEnabled()
        || selected.empty()
        || deselected.empty()) return;

    auto s = deselected.first().indexes().first();
    auto f = selected.first().indexes().first();

    auto vector = QVector2D(f.row(), f.column()) - QVector2D(s.row(), s.column());
    Move move = MoveVector.key(vector.normalized());
    model->rotate(s.row(), s.column(), move);

    setStatus(Status::InProgress);
}

void Game::grabModeActivated()
{
    tableView->setDragEnabled(!tableView->dragEnabled());
}

QPixmap Game::initTablePixmap()
{
    QPixmap pixmap = tableView->grab();
    auto rect = tableView->rect();
    Gradient gradient(rect.topLeft(), rect.bottomRight());

    gradient.setColorAt(0, Palette::Color::Red);
    gradient.setColorAt(1, Palette::Color::Blue);

    QPainter painter(&pixmap);
    painter.fillRect(rect, gradient);

    return pixmap;
}

void Game::reset()
{
    QPixmap pixmap(initTablePixmap());
    model->setData(pixmap);
    setStatus(Status::Stoped);
}

void Game::start()
{
    disconnect(model, SIGNAL(changed(const QModelIndex &, const QModelIndex &)), this, SLOT(start()));
    emit started();
    qDebug() << "Started";
}

void Game::setStatus(Status s)
{
    if (status != s)
    {
       status = s;
       emit statusChanged(status);
    }
}

