#include "tableviewitemdelegate.hpp"

TableViewItemDelegate::TableViewItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) { }


QWidget *TableViewItemDelegate::createEditor(
        QWidget *parent,
        const QStyleOptionViewItem &,
        const QModelIndex &) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(2);
    return editor;
}

void TableViewItemDelegate::setEditorData(
        QWidget *editor,
        const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
    spinbox->setValue(value);
}

void TableViewItemDelegate::setModelData(
        QWidget *,
        QAbstractItemModel *,
        const QModelIndex &) const
{

}

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

void TableViewItemDelegate::updateEditorGeometry(
        QWidget *,
        const QStyleOptionViewItem &,
        const QModelIndex &) const
{

}
