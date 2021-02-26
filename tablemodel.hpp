#ifndef TABLE_HPP
#define TABLE_HPP

#include <QObject>
#include <QColor>
#include <QPainter>
#include <QTableView>
#include <QDebug>
#include <QVectorIterator>
#include <QRandomGenerator>
#include <QStandardItemModel>

#include <random>

#include "tableviewitemdelegate.hpp"
#include "gradient.hpp"
#include "palette.hpp"
#include "common.hpp"

using Item = QMap<int, QVariant>;
using Row = QVector<Item>;
Q_DECLARE_METATYPE(Item);

class TableModel : public QStandardItemModel
{
    Q_OBJECT
    using Base = QStandardItemModel;

public:
    explicit TableModel(QObject *parent = nullptr);
    explicit TableModel(int rows, int collumns, QObject *parent = nullptr);

    void rotate(int row, int collumn, Move direction, int step = 1);
    void rotate(QPoint point, Move direction, int step = 1);
    void applyConfig(QList<QString> config);
    void setData(QPixmap &pixmap);

public slots:
    void scramble();

private:
    QList<QModelIndex> rowIterator(int j);
    QList<QModelIndex> collumnIterator(int i);
    void applyRotate(QListIterator<QModelIndex> i, QList<QModelIndex> applyTo);
    QList<QModelIndex> rotateHelper(int row, int collumn, Move direction);

};

#endif // TABLE_HPP
