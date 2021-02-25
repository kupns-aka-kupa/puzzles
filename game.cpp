#include "game.hpp"

Game::Game(TableModel *model, QObject *parent)
    : QObject(parent)
    , model(model)
    , tableView(qobject_cast<QTableView *>(parent))
{
    QState *idle = new QState();
    QState *inProgress = new QState();

    machine.addState(idle);
    machine.addState(inProgress);

    machine.setInitialState(idle);

    idle->addTransition(this, &Game::started, inProgress);
    inProgress->addTransition(this, &Game::stoped, idle);

    connect(inProgress, SIGNAL(entered()), this, SLOT(start()));

    machine.start();
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

    emit started();
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

    emit stoped();
}

QTime Game::currentTime()
{
    return QTime::fromMSecsSinceStartOfDay(timer.elapsed());
}

void Game::start()
{
    qDebug() << "Game started";
    timer.start();
}

