#include "tablemodel.hpp"

TableModel::TableModel(int i, int j, QObject *parent)
    : Base(i, j, parent)
{
    auto p = qobject_cast<QWidget *>(this->parent());
    auto rect = p->rect();

    QPointF finish (rect.bottomRight());
    Gradient gradient({}, finish);
    QPixmap pixmap = p->grab();

    gradient.setColorAt(0, Colors::Red);
    gradient.setColorAt(1, Colors::Blue);

    QPainter painter(&pixmap);
    painter.fillRect(rect, gradient);

    for(int i = 0; i < columnCount(); i++)
    {
        for(int j = 0; j < rowCount(); j++)
        {
            auto index = this->index(i, j, QModelIndex());
            auto color = gradient.getColor((qreal)(i + j));
            Item c { QString::number(i + j), color.rgb()};
            setData(index, QVariant::fromValue(c));
        }
    }
}

QVectorIterator<Item> TableModel::rowIterator(int i)
{
    Row row;

    for(int j = 0; j < columnCount(); j++)
    {
        auto data = item(i, j)->data();
        row.append(data.value<Item>());
    }

    return row;
}

QVectorIterator<Item> TableModel::collumnIterator(int j)
{
    Row row;

    for(int i = 0; i < rowCount(); i++)
    {
        auto data = item(j, i)->data();
        row.append(data.value<Item>());
    }
    return row;
}
