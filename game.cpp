#include "game.hpp"

Game::Game(TableModel *model, QObject *parent)
    : QObject(parent)
    , model(model)
    , sourceModel(new TableModel(this))
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

    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
            this, SLOT(compare(const QModelIndex &, const QModelIndex &)));
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
    sourceModel->setColumnCount(model->columnCount());
    sourceModel->setRowCount(model->rowCount());
    resetModel(sourceModel);
    resetModel(model);
    emit stoped();
}

void Game::resetModel(TableModel *model)
{
    QPixmap pixmap(initTablePixmap());
    model->setData(pixmap);
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

void Game::compare(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    // TODO QGIS Levenshtein (edit) distance check

    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);

    Q_ASSERT(model->rowCount() == sourceModel->rowCount());
    Q_ASSERT(model->columnCount() == sourceModel->columnCount());

    //emit finished();
}

