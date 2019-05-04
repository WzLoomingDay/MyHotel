#include "checkoutlist.h"
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QVariant>
#include <QMessageBox>
#include "checkout.h"
CheckOutList::CheckOutList(QString &sender,BillInfo &billinfo,QWidget *parent)
    :QWidget(parent),
    m_billinfo(billinfo),
    m_sender(sender)
{
    m_layout = new QHBoxLayout(this);
    m_room_id = new QLabel(m_billinfo.getm_RID());
    m_roominfo = DataBaseOperate::SelectRoomIDInfo(m_billinfo.getm_RID());
    m_room_name = new QLabel(m_roominfo.get_room_name(),this);
    m_bill_name = new QLabel(m_billinfo.getm_name(),this);

    QString lefttimetext;
    QDateTime endTime = QDateTime::fromString(m_billinfo.getm_timeend(),"yyyy-MM-dd hh:mm:ss");
    QDateTime currentTime = QDateTime::currentDateTime();
    uint uendtime = endTime.toTime_t();
    uint ucurrentTime = currentTime.toTime_t();
    int uleftttime = uendtime - ucurrentTime;
    qDebug()<<"ucurrentTime = "<<ucurrentTime<<"uendtime"<<uendtime<<"uleftttime"<<uleftttime<<endl;
    if(uleftttime < 0)
    {
        lefttimetext = "已到点";
    }else
    {
        QVariant vlefttime; //= currentTime.daysTo(endTime);
        //lefttimetext = vlefttime.toString();
        //vlefttime = currentTime.msecsTo(endTime);
        uint days = 60*60*24;
        //uint hours = 60*60;
        vlefttime = uleftttime/days;
        lefttimetext = vlefttime.toString()+"小时";
    }
    m_bill_lefttime = new QLabel(lefttimetext,this);
    QVariant temp =  m_billinfo.getm_cash();
    m_bill_roomcash = new QLabel(temp.toString(),this);
    temp =  m_billinfo.getm_pledge();
    m_bill_pledge = new QLabel(temp.toString(),this);
    m_bill_mealcash = new QLabel(m_billinfo.getm_mealcash());
    m_pbMealDetail = new QPushButton("点菜细节",this);
    temp =  m_billinfo.getm_cash()+m_billinfo.getm_mealcash().toInt();
    m_bill_totalcash = new QLabel(temp.toString(),this);
    m_pbCheckOut = new QPushButton("退房",this);

    m_layout->addWidget(m_room_id);
    m_layout->addWidget(m_room_name);
    m_layout->addWidget(m_bill_name);
    m_layout->addWidget(m_bill_lefttime);
    m_layout->addWidget(m_bill_roomcash);
    m_layout->addWidget(m_bill_pledge);
    m_layout->addWidget(m_bill_mealcash);
    m_layout->addWidget(m_pbMealDetail);
    m_layout->addWidget(m_bill_totalcash);
    m_layout->addWidget(m_pbCheckOut);
    this->setLayout(m_layout);

    connect(m_pbMealDetail,SIGNAL(clicked(bool)),this,SLOT(slotPBmealdetail()));
    connect(m_pbCheckOut,SIGNAL(clicked(bool)),this,SLOT(slotClickCheckOut()));
    connect(this,SIGNAL(SignalUpdateList(QString,QString)),//这里主要是为了点击退房后更新退房主界面信息
            (CheckOut *)this->parent()->parent(),SLOT(slotUpdateInfo(QString,QString)));

}
 void CheckOutList::slotPBmealdetail()
 {
     m_pointerToMealDetail = ShowMealDetail::GetmealDetail(m_billinfo.getm_mealbill());
     connect(this,SIGNAL(signalShowMealDetails()),
             m_pointerToMealDetail,SLOT(showMealDetail()));
     emit signalShowMealDetails();
 }
 void CheckOutList::slotClickCheckOut()
 {
     QString tips = "用户 "+ m_roominfo.get_room_name()+":"+m_billinfo.getm_name() +" 是否退房";
     QString name = "是否退房";
     switch(QMessageBox::question(this,name,tips,QMessageBox::No|QMessageBox::Yes))
     {
      case QMessageBox::No:
         break;
      case QMessageBox::Yes:
         //qDebug()<<"yes"<<endl;
        QString bid = m_billinfo.getm_BILLID();
        QString rid = m_roominfo.get_room_id();
        DataBaseOperate::UpdateBillCheckout(bid,rid);
        emit SignalUpdateList(m_sender,m_roominfo.get_room_type());
        break;
     }
 }
