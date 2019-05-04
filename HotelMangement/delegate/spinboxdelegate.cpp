#include "spinboxdelegate.h"

SpinBoxDelegate::SpinBoxDelegate(QObject *parent):QItemDelegate(parent)
{

}
SpinBoxDelegate::~SpinBoxDelegate()
{

}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     QSpinBox *spinbox = new QSpinBox(parent);
     spinbox->setRange(0,1000000);
     spinbox->setSuffix(" 元/月");
     return spinbox;
}
void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//将model数据(data(index))更新到delegate中
{
     int data = index.model()->data(index).toInt();//将model数据取到delegate中
     QSpinBox *spinbox = static_cast<QSpinBox *>(editor);

     spinbox->setValue(data);
}
void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//将delegate数据写回model中
{
     QSpinBox *spinbox  = static_cast<QSpinBox *>(editor);
    connect(model,SIGNAL(itemChanged(QStandardItem*)),//连接信号
            this,SLOT(slotSpinBoxDataChanged(QStandardItem*)));
    QVariant data = spinbox->value();
    QString str = data.toString();
    model->setData(index,str);
    disconnect(model,SIGNAL(itemChanged(QStandardItem*)),
               this,SLOT(slotSpinBoxDataChanged(QStandardItem*)));//关闭该信号
}
void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
void SpinBoxDelegate::slotSpinBoxDataChanged(QStandardItem *item)
{
    QString new_name = item->index().model()->data(item->index()).toString();

    int row = item->index().row();
    QModelIndex id_coord = item->index().model()->index(row,0);//获得该行第0列的index（即是id）
    QString ID = id_coord.data().toString();
    DataBaseOperate::UpdateUserMessage(ID,"Worker_Salary",new_name);
}

