#ifndef TABLE_HPP
#define TABLE_HPP

#include <QObject>
#include <QColor>
#include <QPainter>
#include <QTableView>
#include <QDebug>
#include <QVectorIterator>
#include <QStandardItemModel>

#include "gradient.hpp"
#include "colors.hpp"

using Item = QMap<int, QVariant>;
using Row = QVector<Item>;
Q_DECLARE_METATYPE(Item);

class TableModel : public QStandardItemModel
{
    Q_OBJECT
    using Base = QStandardItemModel;
public:

    TableModel() = default;
    explicit TableModel(int rows, int collumns, QObject *parent = nullptr);

    QVectorIterator<Item> rowIterator(int j);
    QVectorIterator<Item> collumnIterator(int i);
private:

    QRgb delta;
};



#endif // TABLE_HPP
