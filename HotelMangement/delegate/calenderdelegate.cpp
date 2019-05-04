#include "calenderdelegate.h"

CalenderDelegate::CalenderDelegate(QObject *parent):QItemDelegate(parent)
{

}
CalenderDelegate::~CalenderDelegate()
{

}
 QWidget *CalenderDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index)const
 {
        QDateTimeEdit *m_DateTimeEdit = new QDateTimeEdit(parent);
        m_DateTimeEdit->setDisplayFormat("yyyy.MM.dd");
        m_DateTimeEdit->setCalendarPopup(true);
        return m_DateTimeEdit;
 }
 void CalenderDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {
        QString dateStr = index.model()->data(index).toString();

        QDate date = QDate::fromString(dateStr,Qt::ISODate);
        qDebug()<<"QDate dateStr = "<<date.toString()<<endl;
        QDateTimeEdit *edit = static_cast<QDateTimeEdit *>(editor);
        edit->setDate(date);
 }
 void CalenderDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
     QDateTimeEdit *DateTimeEdit = static_cast<QDateTimeEdit *>(editor);
     connect(model,SIGNAL(itemChanged(QStandardItem*)),//连接信号
             this,SLOT(slotCalenderDataChanged(QStandardItem*)));
     QDate date  = DateTimeEdit->date();
     model->setData(index,QVariant(date.toString(Qt::ISODate)));
     disconnect(model,SIGNAL(itemChanged(QStandardItem*)),//连接信号
             this,SLOT(slotCalenderDataChanged(QStandardItem*)));

}
void CalenderDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
void CalenderDelegate::slotCalenderDataChanged(QStandardItem* item)
{
    QString new_name = item->index().model()->data(item->index()).toString();

    int row = item->index().row();
    QModelIndex id_coord = item->index().model()->index(row,0);//获得该行第0列的index（即是id）
    QString ID = id_coord.data().toString();
    DataBaseOperate::UpdateUserMessage(ID,"Worker_Birth",new_name);
}

