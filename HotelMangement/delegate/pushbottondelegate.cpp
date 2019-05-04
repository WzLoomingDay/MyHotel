#include "pushbottondelegate.h"

#include "usermange.h"

PushBottonDelegate::PushBottonDelegate(QObject *parent)
    :QItemDelegate(parent)
{

}
PushBottonDelegate::~PushBottonDelegate()
{

}
 QWidget *PushBottonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const
 {
        Button=new QPushButton("查看",parent);
       // connect(Button, SIGNAL(clicked(bool)),
         //      ((UserMangement*)parent->((QObject *)parent)), SLOT(CreateDetailedMessage()));
     //QModelIndex mindex = index.model()->parent(index);
         return Button;
 }
 void PushBottonDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {
     QString str = index.model()->data(index).toString();//将model数据取到delegate中
     QPushButton *t_button = static_cast<QPushButton *>(editor);
     t_button->setText(str);
     //qDebug()<<"i = "<<i<<"str = "<<str<<endl;

 }
 void PushBottonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{


}
void PushBottonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
const QPushButton * PushBottonDelegate::getButton()
{
    return  Button;
}

