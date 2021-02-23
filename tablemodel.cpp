#include "tablemodel.hpp"

TableModel::TableModel(int rows, int collumns, QObject *parent)
    : Base(rows, collumns, parent)
{
    auto tableView = qobject_cast<QTableView *>(this->parent());
    tableView->setItemDelegate(new TableViewItemDelegate(tableView));
    init();
}

void TableModel::init()
{
    auto tableView = qobject_cast<QTableView *>(this->parent());
    QPixmap pixmap(initTablePixmap(tableView));
    initData(pixmap);
}

QPixmap TableModel::initTablePixmap(QTableView *tableView)
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

void TableModel::initData(QPixmap &pixmap)
{
    QImage image = pixmap.toImage();
    auto size = pixmap.rect().size();
    size.rheight() /= columnCount(); // size.scale(?, ?)
    size.rwidth() /= rowCount();

    for(int i = 0; i < columnCount(); i++)
    {
        for(int j = 0; j < rowCount(); j++)
        {
            auto index = this->index(i, j, QModelIndex());
            QRect r {{size.width() * i, size.height() * j}, size};

            auto color = image.pixelColor(r.topLeft());
            Item item {
                {QMetaType::QString, QString::number(i * rowCount() + j)},
                {QMetaType::QColor, color}
            };
            setData(index, QVariant::fromValue(item));
        }
    }

}
void TableModel::rotate(QPoint point, Move direction, int step)
{
    rotate(point.x(), point.y(), direction, step);
}

void TableModel::rotate(int row, int collumn, Move direction, int step)
{
    QList<QModelIndex> l = rotateHelper(row, collumn, direction);
    QListIterator<QModelIndex> i = rotateHelper(row, collumn, direction);

    switch(direction)
    {
        case Move::Right:
        case Move::Down:
            std::rotate(l.begin(), l.end() - step, l.end());
            break;
        case Move::Left:
        case Move::Up:
            std::rotate(l.begin(), l.begin() + step, l.end());
            break;
    }

    applyRotate(i, l);
}

QList<QModelIndex> TableModel::rotateHelper(int row, int collumn, Move direction)
{
    switch(direction)
    {
        case Move::Left:
        case Move::Right:
            return rowIterator(row);
        case Move::Down:
        case Move::Up:
            return collumnIterator(collumn);
        default:
            Q_ASSERT_X(false, __func__, "Unexpected rotation direction %0"_Q .arg(direction).toLocal8Bit());
    }
}

void TableModel::applyRotate(QListIterator<QModelIndex> applyTo, QList<QModelIndex> applied)
{
    QVector<QVariant> out(applied.length());
    std::transform(applied.begin(), applied.end(), out.begin(),
    [](QModelIndex i) -> QVariant
    {
        return i.data();
    });

    foreach(auto &index, out)
    {
        setData(applyTo.next(), index);
    }

    emit dataChanged(applied.first(), applied.last());
}

QList<QModelIndex> TableModel::rowIterator(int row)
{
    QList<QModelIndex> list;

    for(int j = 0; j < columnCount(); j++)
    {
        auto item = this->index(row, j);
        list.append(item);
    }

    return list;
}

QList<QModelIndex> TableModel::collumnIterator(int collumn)
{
    QList<QModelIndex> list;

    for(int i = 0; i < rowCount(); i++)
    {
        auto item = this->index(i, collumn);
        list.append(item);
    }
    return list;
}

void TableModel::grabModeActivated()
{
    auto tableView = qobject_cast<QTableView *>(this->parent());
    tableView->setDragEnabled(!tableView->dragEnabled());
}

void TableModel::applyConfig(QList<QString> config)
{
    foreach(auto move, config)
    {
        int index = move.rightRef(1).toInt();
        rotate(index, index,
            MoveLiteral.key({move.front()}));
    }
}

void TableModel::scramble()
{
    int min = Move::Left;
    int max = Move::Down;
    std::uniform_int_distribution movesDistibution(min, max);
    std::uniform_int_distribution indexDistribution(0, qMax(rowCount(), columnCount()));
    auto gen = QRandomGenerator::global();

    QList<QString> config;
    for(int i = 0; i < ScrambleMovesCount; i++)
    {
        auto move = movesDistibution(*gen);
        auto literal = MoveLiteral.value((Move)move);
        config.append(MoveFormat.arg(literal).arg(indexDistribution(*gen)));
    }

    applyConfig(config);
}
