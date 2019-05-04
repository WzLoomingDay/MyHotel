#include "comboxdelegate.h"

Comboxdelegate::Comboxdelegate(QObject *parent):QItemDelegate(parent)
{

}
Comboxdelegate::~Comboxdelegate()
{
}

QWidget *Comboxdelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    QStringList str;
    str << "Manger" << "Cashier" << "Waiter";
    editor->addItems(str);
    editor->installEventFilter(const_cast<Comboxdelegate*>(this));//在目标对象上调用installEventFilter()，注册监视对象。
    return editor;
}
void Comboxdelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//将model数据(data(index))更新到delegate中
{

    QString str = index.model()->data(index).toString();//将model数据取到delegate中
    QComboBox *box = static_cast<QComboBox *>(editor);//box指向createEditor创建的QComboBox对象
    int i = box->findText(str);//从combox（delegate）中找到model中的数据
    //qDebug()<<"i = "<<i<<"str = "<<str<<endl;
    box->setCurrentIndex(i);
}
void Comboxdelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//将delegate数据写回model中
{
    QComboBox *box = static_cast<QComboBox *>(editor);
    connect(model,SIGNAL(itemChanged(QStandardItem*)),//连接信号
            this,SLOT(slotTableDataChanged(QStandardItem*)));
    QString str = box->currentText();//delegate 查看当前combox文字

    model->setData(index,str);

    disconnect(model,SIGNAL(itemChanged(QStandardItem*)),
              this,SLOT(slotTableDataChanged(QStandardItem*)));//关闭该信号
}
void Comboxdelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
void Comboxdelegate::slotTableDataChanged(QStandardItem *item)
{
    QString new_name = item->index().model()->data(item->index()).toString();

    int row = item->index().row();
    QModelIndex id_coord = item->index().model()->index(row,0);//获得该行第0列的index（即是id）
    QString ID = id_coord.data().toString();
    DataBaseOperate::UpdateUserType(ID,new_name);
}
