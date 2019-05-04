#include "signalcustomer.h"
#include "ui_signalcustomer.h"
#include <QDebug>
#include <QMessageBox>
#include <QVariant>
#include <QTime>
#include <QDate>
SignalCustomer::SignalCustomer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignalCustomer)
{
    ui->setupUi(this);
    ui->comboBox_sex->addItem("男");
    ui->comboBox_sex->addItem("女");

    ui->comboBox_roomchoice->addItem("标准单人间");
    ui->comboBox_roomchoice->addItem("商务单人间");
    ui->comboBox_roomchoice->addItem("标准双人间");
    ui->comboBox_roomchoice->addItem("豪华双人间");
    ui->comboBox_roomchoice->addItem("家庭套间");
    ui->comboBox_roomchoice->addItem("总统套房");
    ui->comboBox_roomchoice->addItem("所有");


    ui->lineEdit_roomname->setFocusPolicy(Qt::NoFocus);
    slotCurrentIndexChanged("标准单人间");
    connect(ui->comboBox_roomchoice,SIGNAL(currentIndexChanged(QString)),
                                           this,SLOT(slotCurrentIndexChanged(QString)));
    ui->pb_deal->setEnabled(false);//必须按下计算按钮才能开单


}
SignalCustomer* SignalCustomer::m_SignalCustomer = nullptr;
SignalCustomer::~SignalCustomer()
{
    delete ui;
}
SignalCustomer *SignalCustomer::getSignalCustomer()
{
    if(m_SignalCustomer == nullptr)
    {
        m_SignalCustomer = new SignalCustomer();
    }
    return m_SignalCustomer;
}
void SignalCustomer::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    m_SignalCustomer = nullptr;
    delete this;//关闭删除当前对象
    qDebug()<<"delete SignalCustomer"<<endl;
}
 void SignalCustomer::slotShowSignalCustomer(QString uid)
 {

    m_uid = uid;
    ui->label_userid->setText(m_uid);
    QVariant payid = DataBaseOperate::GetPayid();
    ui->label_payid->setText(payid.toString());
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);//设置一直为顶层窗体
    this->show();
 }
 void SignalCustomer::slotCurrentIndexChanged(QString data)
 {
    //qDebug()<<"slotCurrentIndexChanged :"<<data<<endl;

     ui->listWidget_roomlist->clear();
     GlobalVar::m_roomInfoList.clear();
     GlobalVar::m_roomInfoList = DataBaseOperate::SelectEmptyRoomInfo(data);
     int size = GlobalVar::m_roomInfoList.size();
     //"房间名字"<< "房间楼层" << "房间价格"<<"房间折扣";

     for(int i = 0;i < size;i++)
     {
        m_signaListlWidget = new SignalListItem(ui->listWidget_roomlist);
        m_signaListlWidget->SetMessage(GlobalVar::m_roomInfoList[i].get_room_id(),
                                       GlobalVar::m_roomInfoList[i].get_room_name(),
                                       GlobalVar::m_roomInfoList[i].get_room_place(),
                                       GlobalVar::m_roomInfoList[i].get_room_price(),
                                       GlobalVar::m_roomInfoList[i].get_room_discount());
        if(GlobalVar::m_roomInfoList[i].get_room_type() == "标准单人间")
        {

            m_signaListlWidget->SetPic(":/paybill/menu/signalmenu.png");
        }else if(GlobalVar::m_roomInfoList[i].get_room_type() == "商务单人间")
        {

            m_signaListlWidget->SetPic(":/paybill/menu/ssignalmenu.png");

        }else if(GlobalVar::m_roomInfoList[i].get_room_type() == "标准双人间")
        {

            m_signaListlWidget->SetPic(":/paybill/menu/doublemenu.png");

        }else if(GlobalVar::m_roomInfoList[i].get_room_type() == "豪华双人间")
        {
            m_signaListlWidget->SetPic(":/paybill/menu/sdoublemenu.png");

        }else if(GlobalVar::m_roomInfoList[i].get_room_type() == "家庭套间")
        {

            m_signaListlWidget->SetPic(":/paybill/menu/familymenu.png");

        }else if(GlobalVar::m_roomInfoList[i].get_room_type() == "总统套房")
        {

            m_signaListlWidget->SetPic(":/paybill/menu/presentmenu.png");

        }



        m_listItem = new QListWidgetItem(ui->listWidget_roomlist);
        ui->listWidget_roomlist->addItem(m_listItem);
        m_listItem->setSizeHint(QSize(0,60));//qHboxlayout好像不用设置width设置啥都无所谓，qsize第二个参数设置高度
        m_listItem->sizeHint();
        ui->listWidget_roomlist->setItemWidget(m_listItem,m_signaListlWidget);
     }

 }
 void SignalCustomer::slotSetSelectedRoom(QString data,QString roomid)
 {
    // qDebug()<<"click   ="<<data<<endl;
   // ui->label_selectroom->setText(data);
  m_roomselect  = roomid;
  ui->lineEdit_roomname->setText(data);

 }


void SignalCustomer::on_pushButton_calculate_clicked()
{
    QString room_name = ui->lineEdit_roomname->text();
    QString room_day = ui->spinBox_days->text();
    qDebug()<<"roomname = "<<room_name<<endl;
    if(room_day == "0")
    {
        QString tips = "请选择入住天数";
        QString name = "入住错误天数";
        QMessageBox::information(this,name,tips,0x00000400);
    }else if(room_name.isEmpty())
    {

        QString tips = "请选择入住房间";
        QString name = "未选择房间";
        QMessageBox::information(this,name,tips,0x00000400);
    }else if((ui->lineEdit_pledge->text()).isEmpty())
    {
        QString tips = "请输入押金";
        QString name = "请输入押金";
        QMessageBox::information(this,name,tips,0x00000400);
    }else if(ui->lineEdit_idcard->text().isEmpty()||
             ui->lineEdit_name->text().isEmpty()||
             ui->lineEdit_call->text().isEmpty())
    {
        QString tips = "请填写完全顾客信息";
        QString name = "顾客信息不全";
        QMessageBox::information(this,name,tips,0x00000400);
    }
    else
    {
        RoomInfo info =  DataBaseOperate::SelectRoomIDInfo(m_roomselect);
        qDebug()<<"info "<<endl;
        QString price = info.get_room_price();
        qDebug()<<"price =  "<<price<<endl;
        QString pledge = ui->lineEdit_pledge->text();//押金
         qDebug()<<"pledge =  "<<pledge<<endl;//
        QString discount = info.get_room_discount();//打折
        QVariant vdiscount = discount.toFloat()/10;
        QVariant result = vdiscount.toFloat() * price.toFloat();//房间现价
        int intresult = result.toInt();
        QString strresult = result.toString();

        qDebug()<<"vdiscount.toString() =  "<<vdiscount.toString()<<endl;
        ui->label_roomprice->setText(price);
        ui->label_roomdiscount->setText(vdiscount.toString());
        ui->label_roomresult->setText(strresult);
        QVariant vintresult = intresult*room_day.toInt();
        ui->lineEdit_cash->setText(vintresult.toString());
        int total = result.toInt()*(room_day.toInt()) + ui->lineEdit_pledge->text().toInt();
        QVariant vtotal = total;

        ui->lineEdit_totalmoney->setText(vtotal.toString());

        ui->pb_deal->setEnabled(true);//计算收款后，允许开单

    }


}

void SignalCustomer::on_pb_deal_clicked()
{

    QString ymr = QDate::currentDate().toString("yyyyMMdd");
    QString hms = QTime::currentTime().toString("HHmmss");
    QString billID = ymr + hms;
    qDebug()<<"billID  = "<<billID<<endl;

    int payid = DataBaseOperate::GetTodayPayid();
    QString idcard =ui->lineEdit_idcard->text();
    QString name = ui->lineEdit_name->text();
    QString sex = ui->comboBox_sex->currentText();
    QString call = ui->lineEdit_call->text();
    QString day = ui->spinBox_days->text();
    int intday = day.toInt();

    QString ymrbegin = QDate::currentDate().toString("yyyy-MM-dd ");
    QString hmsbegin = QTime::currentTime().toString("HH:mm:ss");
    QString timebegin = ymrbegin + hmsbegin;

    QString ymrend = QDate::currentDate().addDays(intday).toString("yyyy-MM-dd ");

    QString timeend = ymrend + hmsbegin;

    int cash = ui->lineEdit_cash->text().toInt();
    int pledge = ui->lineEdit_pledge->text().toInt();
    //ui->label_payid->setText(billID);
    BillInfo info(billID,m_roomselect,m_uid,"1",payid,
                  idcard,name,sex,call,intday,timebegin,
                  timeend,cash,pledge,"0",NULL,NULL);
    DataBaseOperate::CreateBillInfo(info);

    RoomInfo rinfo = DataBaseOperate::SelectRoomIDInfo(m_roomselect);
    QString information_name = QString("开单成功");
    QString information_tips = QString("开单成功");
    QMessageBox::information(this,information_name,information_tips,QMessageBox::Ok);

    emit signalUpdateMainMesage(rinfo.get_room_type());
    closeEvent();
}

void SignalCustomer::on_pb_cancle_clicked()
{
    closeEvent();
}
