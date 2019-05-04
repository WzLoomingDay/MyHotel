#include "checkout.h"
#include "ui_checkout.h"
#include <QDebug>
#include "CashierOperate/ccashieroperate.h"
CheckOut::CheckOut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckOut)
{
    ui->setupUi(this);
    ui->comboBox_roomtype->addItem("标准单人间");
    ui->comboBox_roomtype->addItem("商务单人间");
    ui->comboBox_roomtype->addItem("标准双人间");
    ui->comboBox_roomtype->addItem("豪华双人间");
    ui->comboBox_roomtype->addItem("家庭套间");
    ui->comboBox_roomtype->addItem("总统套房");
    ui->comboBox_roomtype->addItem("所有");

    connect(ui->comboBox_roomtype,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(SlotIndexChanged(QString)));



}
CheckOut *CheckOut::m_checkout = nullptr;
CheckOut::~CheckOut()
{
    delete ui;
}
CheckOut * CheckOut::getCheckOut()
{
    if(m_checkout == nullptr)
    {
        m_checkout = new CheckOut();
    }
    return m_checkout;
}

void CheckOut::slotUpdateInfo(QString sender,QString roomtype)
{
    emit ui->comboBox_roomtype->currentIndexChanged(sender);
    //qDebug()<<"hello world"<<endl;
    emit signalUpdateCheckWidget(roomtype);
}
void CheckOut::SlotIndexChanged(QString data)
{
    ui->listWidget->clear();
    qDebug()<<data<<endl;

    int size = 0;
    if(data == "所有")
    {
         GlobalVar::m_billInfoList.clear();
        GlobalVar::m_billInfoList = DataBaseOperate::SelectBillInfo(USING_BILL);
        size = GlobalVar::m_billInfoList.size();
        qDebug()<<"size ="<<size<<endl;

    }else
    {
         GlobalVar::m_billInfoList.clear();
        GlobalVar::m_billInfoList = DataBaseOperate::SelectUsingBillInfo(data);
        size = GlobalVar::m_billInfoList.size();
        qDebug()<<"size ="<<size<<endl;
    }

    for(int i = 0; i < size ;i++)
    {
        qDebug()<<i<<endl;
        m_CheckoutItem = new CheckOutList(data,GlobalVar::m_billInfoList[i],ui->listWidget);
        m_listwidget = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(m_listwidget);
        m_listwidget->setSizeHint(QSize(0,60));//qHboxlayout好像不用设置width设置啥都无所谓，qsize第二个参数设置高度
        ui->listWidget->setItemWidget(m_listwidget,m_CheckoutItem);
    }

}
void CheckOut::slotShowCheckOut(QString user)
{
    qDebug()<<"slotShowCheckOut  = "<<user<<endl;
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);//设置一直为顶层窗体
    this->show();
}
void CheckOut::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    delete this;
    m_checkout = nullptr;
    qDebug()<<"delete closeEvent"<<endl;
}

void CheckOut::on_pb_back_clicked()
{
    closeEvent();
}
