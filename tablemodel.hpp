#ifndef TABLE_HPP
#define TABLE_HPP

#include <QObject>
#include <QColor>
#include <QVectorIterator>
#include <QStandardItemModel>

enum Colors : QRgb
{
    Gray = 0x31363b,
    Black = 0x23262a,
    White = 0xeff0f1,
    Red = 0xce4250,
    Orange = 0xf59e16,
    Blue = 0x2980b9,
    Green = 0x268C52,
    Magenta = 0xbd93f9,
    Purple = 0xf676c0
};

using Item = QPair<int, QRgb>;
using Row = QVector<Item>;
Q_DECLARE_METATYPE(Item);

class TableModel : public QStandardItemModel
{
public:
    using Base = QStandardItemModel;


    TableModel() = default;
    explicit TableModel(int i, int j);

    QVectorIterator<Item> rowIterator(int j);
    QVectorIterator<Item> collumnIterator(int i);

private:
    static QRgb calculateDelta(int i, int j);

    QRgb delta;
};



#endif // TABLE_HPP
