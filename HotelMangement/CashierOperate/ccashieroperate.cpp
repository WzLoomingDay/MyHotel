#include "ccashieroperate.h"
#include "ui_ccashieroperate.h"
#include <QDebug>
#include "globalvar.h"

CCashierOperate::CCashierOperate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCashierOperate),
    m_pointToSignalCustomer(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(1475,952);//1859
    m_pointerToSeverWindow = new SeverWindow(ui->widget_sever);
    connect(m_pointerToSeverWindow,SIGNAL(signalUpDateMainWindow(QString)),
            this,SLOT(slotRefleshCurrentIndex(QString)));
    connect(m_pointerToSeverWindow,SIGNAL(signalUpDateMainWindow(QString)),
                    this,SLOT(slotUpdateRoomState()));


    m_table_signal = new QWidget(ui->tabWidget_room);
    m_table_ssignal= new QWidget(ui->tabWidget_room);
    m_table_double= new QWidget(ui->tabWidget_room);
    m_table_sdouble= new QWidget(ui->tabWidget_room);
    m_table_family= new QWidget(ui->tabWidget_room);
    m_table_present= new QWidget(ui->tabWidget_room);//定义tab中不同的界面

    ui->tabWidget_room->insertTab(0,m_table_signal,"标准单人间");
    ui->tabWidget_room->insertTab(1,m_table_ssignal,"商务单人间");
    ui->tabWidget_room->insertTab(2,m_table_double,"标准双人间");
    ui->tabWidget_room->insertTab(3,m_table_sdouble,"豪华双人间");
    ui->tabWidget_room->insertTab(4,m_table_family,"家庭套间");
    ui->tabWidget_room->insertTab(5,m_table_present,"总统套房");

    ui->comboBox_search->addItem("名字查找");
    ui->comboBox_search->addItem("身份证号查找");



    m_gridlayout_signal = new QGridLayout(m_table_signal);//6个界面6个布局
    m_gridlayout_signal->setMargin(5);
    m_gridlayout_signal->setSpacing(5);

    m_gridlayout_ssignal = new QGridLayout(m_table_ssignal);
    m_gridlayout_ssignal->setMargin(5);
    m_gridlayout_ssignal->setSpacing(5);

    m_gridlayout_double = new QGridLayout(m_table_double);
    m_gridlayout_double->setMargin(2);
    m_gridlayout_double->setSpacing(2);

    m_gridlayout_sdouble = new QGridLayout(m_table_sdouble);
    m_gridlayout_sdouble->setMargin(2);
    m_gridlayout_sdouble->setSpacing(2);

    m_gridlayout_family = new QGridLayout(m_table_family);
    m_gridlayout_family->setMargin(2);
    m_gridlayout_family->setSpacing(2);

    m_gridlayout_present= new QGridLayout(m_table_present);
    m_gridlayout_present->setMargin(2);
    m_gridlayout_present->setSpacing(2);


    updateOperateWindow(7,m_gridlayout_signal,m_table_signal,":/room/room/signal");//初始化更新主界面,标准单人间

    connect(ui->tabWidget_room,SIGNAL(currentChanged(int)),
            this,SLOT(slotCurrentTabIndexChange(int)));


    ui->lcd_empty->setDigitCount(3);
    ui->lcd_Full->setDigitCount(3);

    slotUpdateRoomState();

    this->show();//show之前，程序的gremory左上角起始点是(0,0）
    rect = this->geometry();
    rectSever =  ui->widget_sever->geometry();
    this->setGeometry(rect.topLeft().x(),rect.topLeft().y(),rectSever.bottomLeft().x(),rectSever.bottomLeft().y());
   // qDebug()<<rect.topLeft()<<endl;
   // qDebug()<<rect.topRight()<<endl;
   // qDebug()<<rect.bottomLeft()<<endl;
   // qDebug()<<rect.bottomRight()<<endl;

}

CCashierOperate::~CCashierOperate()
{
    qDebug()<<"::~CCashierOperate()"<<endl;

    delete ui;

}

void CCashierOperate::closeEvent(QCloseEvent *event)//为了，能够调用析构函数
{
    Q_UNUSED(event)
    if(m_pointerToSeverWindow->getMtcpServer()->isListening())
    {
        QString name = "未关闭服务器";
        QString tips = "您还未关闭服务器，是否关闭服务器，并清除所有预定信息";
        switch(QMessageBox::information(0,name,tips,QMessageBox::Ok|QMessageBox::Cancel))
        {
        case QMessageBox::Ok:
            delete m_pointerToSeverWindow;
            delete this;
            break;
        case QMessageBox::Cancel:
            delete m_pointerToSeverWindow;
            break;
        default:
            delete m_pointerToSeverWindow;
            delete this;
        }

    }

}

void CCashierOperate::slotCurrentTabIndexChange(int index)
{
    switch (index) {
    case 0:

        updateOperateWindow(7,m_gridlayout_signal,m_table_signal,":/room/room/signal");//更新标准单人间
        break;
    case 1:

        updateOperateWindow(7,m_gridlayout_ssignal,m_table_ssignal,":/room/room/ssignal");//更新商务单人间
        break;
    case 2:

        updateOperateWindow(7,m_gridlayout_double,m_table_double,":/room/room/double");//更新标准双人间
        break;
    case 3:
        updateOperateWindow(7,m_gridlayout_sdouble,m_table_sdouble,":/room/room/sdouble");//更新豪华双人间
        break;
    case 4:
        updateOperateWindow(7,m_gridlayout_family,m_table_family,":/room/room/family");//更新家庭套间
        break;
    case 5:
        updateOperateWindow(6,m_gridlayout_present,m_table_present,":/room/room/present");//更新总统套房
        break;
    default:
        break;
    }
}
void CCashierOperate::updateOperateWindow(int colum,QGridLayout *layout_type,QWidget * room_type,QString pic)
{
    QString roomtype = ui->tabWidget_room->tabText(ui->tabWidget_room->currentIndex());
    GlobalVar::m_roomInfoList.clear();
    GlobalVar::m_roomInfoList = DataBaseOperate::SelectRoomInfo(roomtype,"所有");
    int size = GlobalVar::m_roomInfoList.size();
    QString roomstate = "空闲";

   // qDebug()<<" size = "<< size << endl;

    if(size<=colum)
    {

        RoomDetail *m_roomdetail[size];

        int i = 0;
        for(;i < size;i++)
        {

            m_roomdetail[i] = new RoomDetail(GlobalVar::m_roomInfoList[i],room_type);
        }
        i = 0;
        for(;i < size;i++)
        {

            roomstate = m_roomdetail[i]->GetRoomState();
           // qDebug()<<"roomstate =  "<< roomstate << endl;
            if(roomstate == "空闲")
            {
               roomstate = pic + "empty.JPG";
            }else if(roomstate == "使用")
            {
              roomstate = pic + "occupy.JPG";
            }else if(roomstate == "预定")
            {
               roomstate = pic  + "book.JPG";
            }
            //qDebug()<<roomstate<< endl;
            (m_roomdetail[i])->setPic(roomstate);
            //m_roomdetail[i]->setPic(pic);
            layout_type->addWidget(m_roomdetail[i],0,i);
            m_roomdetail[i]->show();

        }
    }else if(size%colum == 0)
    {
        //qDebug()<<"size%colum == 0"<< endl;
        RoomDetail *m_roomdetail[size/colum+1][colum];
        int i = 0;
        for(;i < size/colum;i++)
        {
            int j = 0;
            for(;j<colum;j++)
            {

                m_roomdetail[i][j] = new RoomDetail(GlobalVar::m_roomInfoList[i*colum+j],room_type);
            }
        }

        i = 0;
        for(;i < size/colum;i++)
        {

            int j = 0;
            for(;j<colum;j++)
            {
                roomstate = m_roomdetail[i][j]->GetRoomState();
                if(roomstate == "空闲")
                {
                   roomstate = pic + "empty.JPG";
                }else if(roomstate == "使用")
                {
                  roomstate = pic + "occupy.JPG";
                }else if(roomstate == "预定")
                {
                   roomstate = pic  + "book.JPG";
                }
                (m_roomdetail[i][j])->setPic(roomstate);

                layout_type->addWidget(m_roomdetail[i][j],i,j);
                m_roomdetail[i][j]->show();
            }
        }
    }else
    {
       // qDebug()<<"size%colum != 0"<< endl;
         RoomDetail *m_roomdetail[size/colum+1][colum];
         int i = 0;
         for(;i < size/colum;i++)
         {
             int j = 0;
             for(;j<colum;j++)
             {

                 m_roomdetail[i][j] = new RoomDetail(GlobalVar::m_roomInfoList[i*colum+j],room_type);
             }
         }
         for(int j = 0;j < size%colum;j++)
         {
            m_roomdetail[i][j] = new RoomDetail(GlobalVar::m_roomInfoList[i*colum+j],room_type);
         }


          i = 0;
         for(;i < size/colum;i++)
         {
             int j = 0;
             for(;j<colum;j++)
             {
                 roomstate = m_roomdetail[i][j]->GetRoomState();
                 if(roomstate == "空闲")
                 {
                    roomstate = pic + "empty.JPG";
                 }else if(roomstate == "使用")
                 {
                   roomstate = pic + "occupy.JPG";
                 }else if(roomstate == "预定")
                 {
                    roomstate = pic  + "book.JPG";
                 }
                 m_roomdetail[i][j]->setPic(roomstate);
                 layout_type->addWidget(m_roomdetail[i][j],i,j);
                 m_roomdetail[i][j]->show();

                // qDebug()<<"m_roomdetail "<<i << j<< endl;
             }
         }
         for(int j = 0;j < size%colum;j++)
         {

             roomstate = m_roomdetail[i][j]->GetRoomState();
             if(roomstate == "空闲")
             {
                roomstate = pic + "empty.JPG";
             }else if(roomstate == "使用")
             {
               roomstate = pic + "occupy.JPG";
             }else if(roomstate == "预定")
             {
                roomstate = pic  + "book.JPG";
             }
             (m_roomdetail[i][j])->setPic(roomstate);
             layout_type->addWidget(m_roomdetail[i][j],i,j);
              m_roomdetail[i][j]->show();
            // qDebug()<<"m_roomdetail "<<i << j<< endl;

         }

    }

}

void CCashierOperate::slotRefleshCurrentIndex(QString roomtype)
{
    qDebug()<<"slotRefleshCurrentIndex "<<endl;
    int i = 0;
    while(ui->tabWidget_room->tabText(i)!=roomtype)
    {
        i++;
    }
    slotCurrentTabIndexChange(i);

}

 void CCashierOperate::slotShowCashierLogin(QString ID)
 {

     QString title = "当前前台ID号为"+ID;
     m_operate_id = ID;
     qDebug()<<title;
     this->setWindowTitle(title);
     this->show();
 }


void CCashierOperate::on_pushButton_SignalCustomer_clicked()
{

    m_pointToSignalCustomer = SignalCustomer::getSignalCustomer();
    connect(this,SIGNAL(SignalSignalCustomer(QString)),
            m_pointToSignalCustomer,SLOT(slotShowSignalCustomer(QString)));
   //m_pointToSignalCustomer->setWindowFlags(
   //m_pointToSignalCustomer->windowFlags()|Qt::WindowStaysOnTopHint);
    connect(m_pointToSignalCustomer,SIGNAL(signalUpdateMainMesage(QString)),
            this,SLOT(slotUpdateRoomState()));
    connect(m_pointToSignalCustomer,SIGNAL(signalUpdateMainMesage(QString)),
            this,SLOT(slotRefleshCurrentIndex(QString)));
    emit SignalSignalCustomer(m_operate_id);
}


void CCashierOperate::SlotShowbillMessage(RoomInfo roominfo)
{
  // qDebug()<<"RID = "<<roominfo.get_room_id()<<endl;

   if(roominfo.get_room_state() == "使用")
   {
       GlobalVar::m_billInfoList.clear();
       GlobalVar::m_billInfoList = DataBaseOperate::SelectBillInfo(roominfo.get_room_id());

       QString roomtype = roominfo.get_room_id();
       roomtype = roomtype +" "+ roominfo.get_room_type();
       QString roomcall = roominfo.get_room_call();
       QString roompalce= roominfo.get_room_place();
       QString roomdiscount = roominfo.get_room_discount();
       QString room_starttime = GlobalVar::m_billInfoList[0].getm_timebegin();
       QString room_lefttime = GlobalVar::m_billInfoList[0].getm_timeend();
       QString customer_name = GlobalVar::m_billInfoList[0].getm_name();
       QString customer_sex = GlobalVar::m_billInfoList[0].getm_sex();
       QString customer_idcard = GlobalVar::m_billInfoList[0].getm_idcard();
       int customer_day = GlobalVar::m_billInfoList[0].getm_day();
       int customer_pledge = GlobalVar::m_billInfoList[0].getm_pledge();
       int customer_cash = GlobalVar::m_billInfoList[0].getm_cash();
       int customerpayid = GlobalVar::m_billInfoList[0].getm_payid();
         glanceOverDetail(roomtype,roomcall,roompalce,roomdiscount,room_starttime
                          ,room_lefttime,customer_name,customer_sex,customer_idcard,
                          customer_day,customer_pledge,customer_cash,customerpayid);

   }else
   {

      QString roomtype = roominfo.get_room_id();
      roomtype = roomtype +" "+ roominfo.get_room_type();
      QString roomcall = roominfo.get_room_call();
      QString roompalce= roominfo.get_room_place();
      QString roomdiscount = roominfo.get_room_discount();
      glanceOverDetail(roomtype,roomcall,roompalce,roomdiscount);

   }
}
void CCashierOperate::glanceOverDetail(QString roomtype,QString roomcall,QString roompalce,QString roomdiscount,
                      QString roomstarttime,QString roomlefttime,QString customername,
                      QString customersex,QString customeridcard,int customerdays,
                      int customerpledge,int customercash,int payid)
{
    ui->label_roomtype->setText(roomtype);
    ui->lineEdit_roomcall->setText(roomcall);
    ui->lineEdit_roomplace->setText(roompalce);
    ui->lineEdit_discount->setText(roomdiscount);
    ui->lineEdit_starttime->setText(roomstarttime);
    ui->lineEdit_lefttime->setText(roomlefttime);
    ui->lineEdit_cuntomername->setText(customername);
    ui->lineEdit_sex->setText(customersex);
    ui->lineEdit_idcard->setText(customeridcard);
    QVariant temp;
    temp = customerdays;
    QString days = temp.toString();
    ui->lineEdit_days->setText(days);
    temp = customerpledge;
    QString peldge = temp.toString();
    ui->lineEdit_pledge->setText(peldge);
    temp = customercash;
    QString cash = temp.toString();
    ui->lineEdit_cash->setText(cash);
    temp = payid;
    QString m_payid = temp.toString();
    ui->lineEdit_payid->setText(m_payid);
}

void CCashierOperate::on_PB_addmeals_clicked()
{
    m_pointerToaddmeals = AddMeals::getAddMeals();
    connect(this,SIGNAL(SingalAddMeals(QString)),
            m_pointerToaddmeals,SLOT(slotShowAddMeals(QString)));
    emit SingalAddMeals(m_operate_id);
}

void CCashierOperate::on_PB_accument_clicked()
{
    m_pointerToCheckout = CheckOut::getCheckOut();
    connect(this,SIGNAL(SignalCheckOut(QString)),
            m_pointerToCheckout,SLOT(slotShowCheckOut(QString)));
    connect(m_pointerToCheckout,SIGNAL(signalUpdateCheckWidget(QString)),
            this,SLOT(slotUpdateRoomState()));//当点击删除时候，更新两界面信息
    connect(m_pointerToCheckout,SIGNAL(signalUpdateCheckWidget(QString)),
            this,SLOT(slotRefleshCurrentIndex(QString)));
    emit SignalCheckOut(m_operate_id);
}

void CCashierOperate::on_PB_history_clicked()
{
    m_pointerToHistory = History::GetHistory();
    connect(this,SIGNAL(SignalHistory(QString)),
            m_pointerToHistory,SLOT(slotShowHistory(QString)));
    emit SignalHistory(m_operate_id);

}
void CCashierOperate::slotUpdateRoomState()
{
    qDebug()<<"slotUpdateRoomState"<<endl;
    QVariant temp = DataBaseOperate::countRoomNumber(EMPTY);
    ui->lcd_empty->display(temp.toString());
    temp = DataBaseOperate::countRoomNumber(FULL);
    ui->lcd_Full->display(temp.toString());
}

void CCashierOperate::on_pushButton_search_clicked()
{
    QString message = ui->lineEdit_search->text();
    if(message.isEmpty())
    {
         QString name = "输入错误";
         QString tips = "您未输入查找信息";
         QMessageBox::information(0,name,tips,QMessageBox::Ok);

    }else
    {
        QStringList list;
        if(ui->comboBox_search->currentText() == "名字查找")
        {
           list = DataBaseOperate::SelectCustomerInRoom(CUSTOMER_NAME,message);
        }else if(ui->comboBox_search->currentText() == "身份证号查找")
        {
           list =  DataBaseOperate::SelectCustomerInRoom(CUSTOMER_IDCARD,message);
        }
        if(list.isEmpty())
        {
            QString name = "没有用户信息";
            QString tips = "未查找相关信息";
            QMessageBox::information(0,name,tips,QMessageBox::Ok);
        }else
        {
            QVariant vsize = list.size();
            QString name = "有" + vsize.toString() +"条用户信息";
            QString tips;
            for(int i = 0;i < list.size();i++)
            {
                tips.append(QString(list[i]+"\n"));
            }
            QMessageBox::information(0,name,tips,QMessageBox::Ok);
        }

    }
}

void CCashierOperate::on_pb_sever_clicked()
{
    if(ui->pb_sever->text() == "显示服务器")
    {
       // QRect rectSever =  ui->widget_sever->geometry();
        //this->setGeometry(rect.topLeft().x(),rect.topLeft().y(),rectSever.bottomRight().x(),rectSever.bottomRight().y());
        this->setFixedSize(1859,952);
        ui->pb_sever->setText("隐藏服务器");
    }else if(ui->pb_sever->text() == "隐藏服务器")
    {
        //rect = this->geometry();
        //rectSever =  ui->widget_sever->geometry();
        //this->setGeometry(rect.topLeft().x(),rect.topLeft().y(),rectSever.bottomLeft().x(),rectSever.bottomLeft().y());
        this->setFixedSize(1475,952);
        ui->pb_sever->setText("显示服务器");
    }
}
