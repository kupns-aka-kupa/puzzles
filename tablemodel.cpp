#include "tablemodel.hpp"

TableModel::TableModel(int i, int j)
    : Base(i, j)
    , delta(calculateDelta(i, j))
{
    for(int i = 0; i < columnCount(); i++)
    {
        for(int j = 0; j < rowCount(); j++)
        {
            auto index = this->index(i, j, QModelIndex());
            Item c {i + j, Red};
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

QRgb TableModel::calculateDelta(int i, int j)
{
    QRgb r = (Blue - Red) / i;
    QRgb g = (Blue - Red) / j;
    QRgb b = (Blue - Red) / (j * i);
    return b;
}

