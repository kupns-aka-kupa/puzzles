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
    using Base = QStyledItemDelegate;
public:
    TableViewItemDelegate(QObject *parent);

    void paint(
            QPainter *painter,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const override;
private:
    Q_DISABLE_COPY(TableViewItemDelegate)
};

#endif // TABLEVIEWITEMDELEGATE_HPP
