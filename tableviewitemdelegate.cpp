#include "tableviewitemdelegate.hpp"

TableViewItemDelegate::TableViewItemDelegate(QObject *parent)
    : QItemDelegate(parent) { }


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

void TableViewItemDelegate::updateEditorGeometry(
        QWidget *,
        const QStyleOptionViewItem &,
        const QModelIndex &) const
{

}
