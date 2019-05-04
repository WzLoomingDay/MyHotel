#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H
#include<QItemDelegate>
#include<QDebug>
#include<QStandardItem>
#include <QCheckBox>
#include<QVariant>
#include<QFont>
#include<QPalette>
#include<QMessageBox>
#include"databaseoperate.h"

class CheckBoxDelegate:public QItemDelegate
{
    Q_OBJECT//提供信号与槽机制
public:
    CheckBoxDelegate(QObject *parent  = 0);
    ~CheckBoxDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //createEditor完成创建控件的工作  由参数QModelIndex对象指定的表项数据的编辑控件

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //设置控件显示数据，将Model数据更新到delegate中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    //将delegate数据更新到Model中
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //更新控件区域的显示
public slots:
     void slotCheckBoxChanged(QStandardItem *item);
};

#endif // CHECKBOXDELEGATE_H
