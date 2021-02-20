#ifndef TABLEVIEWITEMDELEGATE_HPP
#define TABLEVIEWITEMDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QSpinBox>
#include <QVariant>
#include <QPainter>
#include "tablemodel.hpp"

class TableViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TableViewItemDelegate(QObject *parent);

    QWidget *createEditor(
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const override;

    void setEditorData(
            QWidget *editor,
            const QModelIndex &index) const override;

    void setModelData(
            QWidget *editor,
            QAbstractItemModel *model,
            const QModelIndex &index) const override;

    void updateEditorGeometry(
            QWidget *editor,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const override;

    void paint(
            QPainter *painter,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const override;
private:
    Q_DISABLE_COPY(TableViewItemDelegate)
};

#endif // TABLEVIEWITEMDELEGATE_HPP
