#include "comboxsexdelegate.h"

comboxSexDelegate::comboxSexDelegate(QObject *parent):QItemDelegate(parent)
{

}
comboxSexDelegate::~comboxSexDelegate()
{
}

QWidget *comboxSexDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    QStringList str;
    str << "男" << "女";
    editor->addItems(str);
    return editor;
}
void comboxSexDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//将model数据(data(index))更新到delegate中
{

    QString str = index.model()->data(index).toString();//将model数据取到delegate中
    QComboBox *box = static_cast<QComboBox *>(editor);//box指向createEditor创建的QComboBox对象
    int i = box->findText(str);//从combox（delegate）中找到model中的数据
    //qDebug()<<"i = "<<i<<"str = "<<str<<endl;
    box->setCurrentIndex(i);
}
void comboxSexDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//将delegate数据写回model中
{
    QComboBox *box = static_cast<QComboBox *>(editor);
    connect(model,SIGNAL(itemChanged(QStandardItem*)),//连接信号
            this,SLOT(slotSexDataChanged(QStandardItem*)));
    QString str = box->currentText();//delegate 查看当前combox文字

    model->setData(index,str);

    disconnect(model,SIGNAL(itemChanged(QStandardItem*)),
               this,SLOT(slotSexDataChanged(QStandardItem*)));//关闭该信号
}
void comboxSexDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
void comboxSexDelegate::slotSexDataChanged(QStandardItem* item)
{
    QString new_sex = item->index().model()->data(item->index()).toString();

    int row = item->index().row();
    QModelIndex id_coord = item->index().model()->index(row,0);//获得该行第0列的index（即是id）
    QString ID = id_coord.data().toString();
    DataBaseOperate::UpdateUserMessage(ID,"Worker_Sex",new_sex);
}


