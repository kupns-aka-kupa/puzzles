#include "tablemodel.hpp"

TableModel::TableModel(int rows, int collumns, QObject *parent)
    : Base(rows, collumns, parent)
{
    auto p = qobject_cast<QTableView *>(this->parent());
    QPixmap pixmap = p->grab();
    auto rect = p->rect();
    Gradient gradient(rect.topLeft(), rect.bottomRight());

    gradient.setColorAt(0, Colors::Red);
    gradient.setColorAt(1, Colors::Blue);

    QPainter painter(&pixmap);
    painter.fillRect(rect, gradient);
    QImage image = pixmap.toImage();

    auto size = rect.size();
    size.rheight() /= columnCount();
    size.rwidth() /= rowCount();

    for(int i = 0; i < columnCount(); i++)
    {
        for(int j = 0; j < rowCount(); j++)
        {
            auto index = this->index(i, j, QModelIndex());
            QRect r {{size.width() * i, size.height() * j}, size};

            auto color = image.pixelColor(r.topLeft());
            Item c {
                {QMetaType::QString, QString::number(i + j)},
                {QMetaType::QColor, color}
            };
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
