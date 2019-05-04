#ifndef PUSHBOTTONDELEGATE_H
#define PUSHBOTTONDELEGATE_H
#include<QItemDelegate>
#include<QPushButton>
#include<QDebug>

class PushBottonDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    PushBottonDelegate(QObject *parent  = 0);
    ~PushBottonDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //createEditor完成创建控件的工作  由参数QModelIndex对象指定的表项数据的编辑控件
    //createEditor是双击item后创建什么控件
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //设置控件显示数据，将Model数据更新到delegate中
    //setEditorData是显示控件后 设置里面的值，提供index 自己从model内提取数据
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    //将delegate数据更新到Model中
    //setmodeldata是确定 （按下回车后）设置model的值，
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //更新控件区域的显示
    const QPushButton *getButton();
public slots:
private:
    mutable QPushButton * Button;


};

#endif // PUSHBOTTONDELEGATE_H
