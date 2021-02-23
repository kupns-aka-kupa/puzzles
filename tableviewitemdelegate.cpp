#include "tableviewitemdelegate.hpp"

TableViewItemDelegate::TableViewItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) { }

void TableViewItemDelegate::paint(
        QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    QVariant data = index.data();
    const QRect &rect = option.rect;
    auto item = data.value<Item>();

    auto value = item
        .value(QMetaType::QString)
        .value<QString>();

    auto color = item
        .value(QMetaType::QColor)
        .value<QColor>();

    painter->fillRect(rect, color);
    painter->drawText(rect, Qt::AlignCenter, value);
    Base::paint(painter, option, index);
}
