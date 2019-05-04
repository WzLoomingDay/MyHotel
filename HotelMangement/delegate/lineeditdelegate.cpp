#include "lineeditdelegate.h"

LineEditDelegate::LineEditDelegate(QObject *parent):QItemDelegate(parent)
{

}

LineEditDelegate::~LineEditDelegate()
{
}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *lineEdit = new QLineEdit(parent);

    return lineEdit;
}
void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//将model数据(data(index))更新到delegate中
{
     QString str = index.model()->data(index).toString();//将model数据取到delegate中
     QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
     lineEdit->setText(str);
}
void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//将delegate数据写回model中
{
     QLineEdit *lineEdit  = static_cast<QLineEdit *>(editor);
    connect(model,SIGNAL(itemChanged(QStandardItem*)),//连接信号
            this,SLOT(slotLineEditDataChanged(QStandardItem*)));
    QString str = lineEdit->text();

    int row = index.row();
    int column = index.column();
    if(column == 4)//如果是手机号
    {
        QString mRegExp = "[0-9]{11}";
        if(RegExp::JudgeRegExp(mRegExp,str))
        {
            model->setData(index,str);
        }else
        {
            //qDebug()<<"error input delete"<<endl;
            QString title("手机号格式不正确");
            QString tips("手机号必须是11位数字");
            QMessageBox::information((QWidget *)0,title,tips,QMessageBox::Ok);
        }
    }else if(column == 1)//如果是姓名
    {
        model->setData(index,str);
    }
    disconnect(model,SIGNAL(itemChanged(QStandardItem*)),
               this,SLOT(slotLineEditDataChanged(QStandardItem*)));//关闭该信号
}
void LineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
void LineEditDelegate::slotLineEditDataChanged(QStandardItem *item)
{
    QString new_name = item->index().model()->data(item->index()).toString();

    int row = item->index().row();
     int column = item->index().column();
    if(column == 1)
    {
    QModelIndex id_coord = item->index().model()->index(row,0);//获得该行第0列的index（即是id）
    QString ID = id_coord.data().toString();
    DataBaseOperate::UpdateUserMessage(ID,"Worker_name",new_name);
    }else if(column == 4)
    {
    QModelIndex id_coord = item->index().model()->index(row,0);//获得该行第0列的index（即是id）
    QString ID = id_coord.data().toString();
    DataBaseOperate::UpdateUserMessage(ID,"Worker_call",new_name);
    }
}

