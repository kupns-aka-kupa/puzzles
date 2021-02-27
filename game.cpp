#include "game.hpp"

Game::Game(TableModel *model, QObject *parent)
    : QObject(parent)
    , _model(model)
    , _sourceModel(new TableModel(this))
    , _tableView(qobject_cast<QTableView *>(parent))
{
    QState *idle = new QState();
    QState *inProgress = new QState();

    _machine.addState(idle);
    _machine.addState(inProgress);

    _machine.setInitialState(idle);

    idle->addTransition(this, &Game::started, inProgress);
    inProgress->addTransition(this, &Game::stoped, idle);

    connect(inProgress, SIGNAL(entered()), this, SLOT(start()));

    _machine.start();

    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
            this, SLOT(compare(const QModelIndex &, const QModelIndex &)));
}

void Game::rotateTableModel(
    const QItemSelection &selected,
    const QItemSelection &deselected)
{
    if(!_tableView->dragEnabled()
        || selected.empty()
        || deselected.empty()) return;

    auto s = deselected.first().indexes().first();
    auto f = selected.first().indexes().first();

    auto vector = QVector2D(f.row(), f.column()) - QVector2D(s.row(), s.column());
    Move move = MoveVector.key(vector.normalized());
    _model->rotate(s.row(), s.column(), move);

    emit started();
}

void Game::grabModeActivated()
{
    _tableView->setDragEnabled(!_tableView->dragEnabled());
}

QPixmap Game::initTablePixmap()
{
    QPixmap pixmap = _tableView->grab();
    auto rect = _tableView->rect();
    Gradient gradient(rect.topLeft(), rect.bottomRight());

    gradient.setColorAt(0, Palette::Color::Red);
    gradient.setColorAt(1, Palette::Color::Blue);

    QPainter painter(&pixmap);
    painter.fillRect(rect, gradient);

    return pixmap;
}

void Game::reset()
{
    _sourceModel->setColumnCount(_model->columnCount());
    _sourceModel->setRowCount(_model->rowCount());
    resetModel(_sourceModel);
    resetModel(_model);
    emit stoped();
}

void Game::resetModel(TableModel *model)
{
    QPixmap pixmap(initTablePixmap());
    model->setData(pixmap);
}

QTime Game::currentTime()
{
    return QTime::fromMSecsSinceStartOfDay(_timer.elapsed());
}

void Game::start()
{
    qDebug() << "Game started";
    _timer.start();
}

void Game::compare(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    // TODO QGIS Levenshtein (edit) distance check

    Q_UNUSED(topLeft);
    Q_UNUSED(bottomRight);

    Q_ASSERT(_model->rowCount() == _sourceModel->rowCount());
    Q_ASSERT(_model->columnCount() == _sourceModel->columnCount());

    //emit finished();
}

