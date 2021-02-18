#include "table.hpp"


Table::Table(int i, int j)
    : matrix(i, Table::Row(j))
    , delta(calculateDelta(i, j))
{
    for(auto &r : matrix)
    for(auto &c : r)
    {
        c = {i + j, {
            RED[0] + i * delta.red(),
            RED[1] + j * delta.green(),
            RED[2] + i * j * delta.blue()
        }};
    }
}

Table::Iterator Table::rowIterator(int i)
{
    Q_ASSERT(matrix.length() > i);
    auto c = matrix.at(i);
    return c.begin();
}

Table::Iterator Table::collumnIterator(int j)
{
    Q_ASSERT(matrix.length() > j);
    Table::Row row;
    for(auto &r : matrix)
    {
        row.push_back(r.at(j));
    }
    return row.begin();
}

QColor Table::calculateDelta(int i, int j)
{
    int r = (BLUE[0] - RED[0]) / i;
    int g = (BLUE[1] - RED[1]) / j;
    int b = (BLUE[2] - RED[2]) / (j * i);
    return {r, g, b};
}

