#ifndef CALENDERDELEGATE_H
#define CALENDERDELEGATE_H
#include<QItemDelegate>
#include<QDebug>
#include<QDateTimeEdit>
#include<QDate>
#include<QStandardItem>
#include"databaseoperate.h"

class CalenderDelegate:public QItemDelegate
{
    Q_OBJECT//提供信号与槽机制
public:
    CalenderDelegate(QObject *parent  = 0);
    ~CalenderDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //createEditor完成创建控件的工作  由参数QModelIndex对象指定的表项数据的编辑控件

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //设置控件显示数据，将Model数据更新到delegate中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    //将delegate数据更新到Model中
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //更新控件区域的显示
public slots:
     void slotCalenderDataChanged(QStandardItem* item);
private:

};

#endif // CALENDERDELEGATE_H
