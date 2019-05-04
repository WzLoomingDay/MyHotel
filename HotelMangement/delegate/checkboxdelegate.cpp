#include "checkboxdelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent):QItemDelegate(parent)
{

}

CheckBoxDelegate::~CheckBoxDelegate()
{
}

QWidget *CheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   Q_UNUSED(option)
   QCheckBox *checkbox = new QCheckBox(parent);
   QFont font;
   font.setBold(true);
   font.setPixelSize(18);
   checkbox->setStyleSheet("QCheckBox{color:rgb(105,170,238)}");
    checkbox->setStyleSheet("QCheckBox{ background-color: rgb(255,91,51)}");
    checkbox->setText("是否删除");



    checkbox->setFont(font);
    return checkbox;
}
void CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//将model数据(data(index))更新到delegate中
{

}
void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//将delegate数据写回model中
{
        QCheckBox *checkBox=static_cast<QCheckBox*>(editor);
        if(checkBox->isChecked()){
            int row = index.row();
            QString ID = model->index(row,0).data().toString();
            QString tips = "您确认删除用户"+ID+"吗?";
            QString name = "是否删除";
            int choice = QMessageBox::question((QWidget *)0,name,tips,
                                  QMessageBox::Ok|QMessageBox::Cancel
                                               |QMessageBox::NoButton,
                                              QMessageBox::Ok);//如果parent为0消息框变为应用程序全局的模式对话框
            //如果parent为一个窗口部件,消息框变为相对于parent的模式对话框
            if(choice == QMessageBox::Ok)
            {
                DataBaseOperate::DeleteWorkerInfo(ID);
                model->removeRow(row);
            }else if(choice == QMessageBox::Cancel)
            {
                checkBox->setCheckState(Qt::Unchecked);
            }

        }
        else{
            model->setData(index,QString("点击删除"));
        }
}
void CheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
void CheckBoxDelegate::slotCheckBoxChanged(QStandardItem *item)
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



