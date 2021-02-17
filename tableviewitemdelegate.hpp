#ifndef TABLEVIEWITEMDELEGATE_HPP
#define TABLEVIEWITEMDELEGATE_HPP

#include <QItemDelegate>
#include <QSpinBox>

class TableViewItemDelegate : public QItemDelegate
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
};

#endif // TABLEVIEWITEMDELEGATE_HPP
