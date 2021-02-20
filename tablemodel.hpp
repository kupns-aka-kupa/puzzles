#ifndef TABLE_HPP
#define TABLE_HPP

#include <QObject>
#include <QColor>
#include <QPainter>
#include <QWidget>
#include <QVectorIterator>
#include <QStandardItemModel>

#include "gradient.hpp"
#include "colors.hpp"

using Item = QPair<QString, QRgb>;
using Row = QVector<Item>;
Q_DECLARE_METATYPE(Item);

class TableModel : public QStandardItemModel
{
public:
    using Base = QStandardItemModel;


    TableModel() = default;
    explicit TableModel(int i, int j, QObject *parent = nullptr);

    QVectorIterator<Item> rowIterator(int j);
    QVectorIterator<Item> collumnIterator(int i);
private:

    QRgb delta;
};



#endif // TABLE_HPP
