#include "severwindow.h"
#include "ui_severwindow.h"

#include <QTableWidgetItem>
#include <QInputDialog>
#include <QByteArray>

SeverWindow::SeverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SeverWindow),
    m_port(8888)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Widget);//设置完windowsflag之后调用hide
    this->show();

    m_tcpServer = new QTcpServer(this);

    ui->tableWidget_request->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->tableWidget_request->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中

    ui->tableWidget_booking->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->tableWidget_booking->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中

    connect(ui->tableWidget_request,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(slotChickRequestTable(QModelIndex)));
    connect(ui->tableWidget_booking,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(slotChickBookingTable(QModelIndex)));
}



SeverWindow::~SeverWindow()
{
    qDebug()<<"shutDownServer SeverWindow"<<endl;
    shutDownServer();
    delete ui;
}

QTcpServer *SeverWindow::getMtcpServer()
{
    return m_tcpServer;
}
void SeverWindow::on_pb_opensever_clicked()
{
    if(ui->pb_opensever->text()=="开启服务")
    {
        if(!m_tcpServer->isListening())//如果已经正在监听
        {
            m_tcpServer->listen(QHostAddress::Any,m_port);
            QVariant t_port =  m_port;
            ui->lineEdit_port->setText(t_port.toString());
            connect(m_tcpServer, SIGNAL(newConnection()),
                    this, SLOT(slotNewConnectSocket()));
        }
         ui->pb_opensever->setText("关闭服务");

    }else if(ui->pb_opensever->text()=="关闭服务")
    {

         ui->lineEdit_port->setText("");
         ui->pb_opensever->setText("开启服务");
    }


}

 void  SeverWindow::slotNewConnectSocket()
 {
    connectCilent *newcilent =
            new connectCilent(m_tcpServer->nextPendingConnection());

    connect(newcilent,SIGNAL(signalSendBookingRequest(CustomerInfo)),
            this,SLOT(slotAddNewCustomer(CustomerInfo)));//连接客户端发来消息的信号于槽
    newcilent->start();
 }

 void SeverWindow::slotAddNewCustomer(CustomerInfo info)
 {
    qDebug()<<"SeverWindow::slotAddNewCustomer(CustomerInfo info)"<<endl;
    m_customerRequestList.append(info);
    updateRequestTable();

 }

 void  SeverWindow::updateRequestTable()
 {
      qDebug()<<"void  SeverWindow::updateRequestTable()"<<endl;
     int row = m_customerRequestList.size();
     ui->tableWidget_request->clear();
     ui->tableWidget_request->setRowCount(row);
     ui->tableWidget_request->setColumnCount(3);
     QStringList headers;
     headers << "用户ID" <<"用户名字" <<"请求房间类型";
     ui->tableWidget_request->setHorizontalHeaderLabels(headers);

     for(int i = 0; i < row; i++)
     {
         QString temp = m_customerRequestList[i].getm_cid();
         QTableWidgetItem *item = new  QTableWidgetItem(temp);
         ui->tableWidget_request->setItem(i, 0, item);

          temp =m_customerRequestList[i].getm_name();
         item = new  QTableWidgetItem(temp);
         ui->tableWidget_request->setItem(i, 1, item);

         temp =m_customerRequestList[i].getm_roomtype();
         item = new  QTableWidgetItem(temp);//房间类型
         ui->tableWidget_request->setItem(i, 2, item);

     }
 }

 void  SeverWindow::updateBookingTable()
 {
     qDebug()<<"void  SeverWindow::updateRequestTable()"<<endl;
    int row = m_customerBookedList.size();
    ui->tableWidget_booking->clear();
    ui->tableWidget_booking->setRowCount(row);
    ui->tableWidget_booking->setColumnCount(4);
    QStringList headers;
    headers << "用户ID" <<"用户名字" <<"请求房间类型"<<"房间号";
    ui->tableWidget_booking->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < row; i++)
    {
        QString temp = m_customerBookedList[i].getm_cid();
        QTableWidgetItem *item = new  QTableWidgetItem(temp);
        ui->tableWidget_booking->setItem(i, 0, item);

         temp =m_customerBookedList[i].getm_name();
        item = new  QTableWidgetItem(temp);
        ui->tableWidget_booking->setItem(i, 1, item);

        temp =m_customerBookedList[i].getm_roomtype();
        item = new  QTableWidgetItem(temp);//房间类型
        ui->tableWidget_booking->setItem(i, 2, item);

        temp =m_customerBookedList[i].getm_RID();
        item = new  QTableWidgetItem(temp);//房间号
        ui->tableWidget_booking->setItem(i,3, item);

    }

 }

void SeverWindow::shutDownServer()
{
    qDebug()<<"SeverWindow::shutDownServer()"<<endl;
    DataBaseOperate::ClearAllBookCustomer();//每当关闭的时候清除所有预定列表

}

 void SeverWindow::updateMainWindow()
 {
        qDebug()<<"void SeverWindow::updateMainWindow()"<<endl;
       // updateRequestTable();

 }
 void SeverWindow::slotChickRequestTable(QModelIndex index)
 {
     int row = index.row();
     QString id = index.model()->index(row,0).data().toString();
     GlobalVar::m_customerInfoList.clear();
     GlobalVar::m_customerInfoList = DataBaseOperate::SelectCustomerInfo(id);
     CustomerInfo info = GlobalVar::m_customerInfoList[0];


     QString title = "选择操作";
     QString tips = "选择要对用户 "+info.getm_cid()+":"+info.getm_name()+" 的操作";
     QStringList itemlist;
     itemlist<<"允许预定"<<"取消预定";
     bool ok;
   // qDebug()<<"SeverWindow::slotChickRequestTable(QModelIndex index)"<<endl;
     QString SelectItem = QInputDialog::getItem(this,title,tips,itemlist,0,false,&ok);

     if(ok&&SelectItem == "允许预定")
     {
         QString roomtitle = "选择空闲房间";
         QString roomtips = "选择空闲的"+info.getm_roomtype()+"房间";
         GlobalVar::m_roomInfoList.clear();
         GlobalVar::m_roomInfoList = DataBaseOperate::SelectEmptyRoomInfo(info.getm_roomtype());
         int size = GlobalVar::m_roomInfoList.size();
         QStringList roomlist;
         for(int i = 0;i< size;i++)
         {
             roomlist<<GlobalVar::m_roomInfoList[i].get_room_id();
         }
         bool okroom;
       // qDebug()<<"SeverWindow::slotChickRequestTable(QModelIndex index)"<<endl;
         QString selectroom = QInputDialog::getItem(this,roomtitle,roomtips,roomlist,0,false,&okroom);
         if(okroom)//选择预定的房间，要更新表中flag成功，rid = 选择的id，然后向客户端发送用用户表更新的信息
         {
             qDebug()<<"okroom"<<endl;
             info.setm_flag(BOOKING_SUCCESS);//更新表中flag
             info.setm_RID(selectroom);
             DataBaseOperate::updateCustomerInfo(info);
             int i = 0;
             while(m_customerRequestList[i].getm_cid() != info.getm_cid())//找到相应的socket
             {
                 i++;
             }

             sendBookingMsgToCilent(m_customerRequestList[i].getmSocket(),*(info.packageinfos()));
             m_customerRequestList[i].setm_RID(selectroom);
             DataBaseOperate::UpdateRoomState(selectroom,ROOM_BOOK);
             //emit signalBookingSuccess(info);
             emit signalUpDateMainWindow(info.getm_roomtype());//更新主界面空闲/正在使用 的信息
             m_customerBookedList.append(m_customerRequestList[i]);
             m_customerRequestList.removeAt(i);
             updateRequestTable();
             updateBookingTable();
         }
     }else if(ok&&SelectItem == "取消预定")
     {

     }
 }
 void SeverWindow::slotChickBookingTable(QModelIndex index)
 {
    CustomerInfo info;
    qDebug()<<"SeverWindow::slotChickBookingTable(QModelIndex index)"<<endl;
    int row = index.row();
    QString customerID = index.model()->index(row,0).data().toString();
    QString roomID = index.model()->index(row,3).data().toString();
    QString name = "取消预定";
    QString tips = "是否取消顾客:"+customerID+"的预定信息";
    switch(QMessageBox::information(0,name,tips,QMessageBox::Ok|QMessageBox::Cancel))
    {
    case QMessageBox::Ok:
           DataBaseOperate::UpdateRoomState(roomID,ROOM_EMPYT);
           DataBaseOperate::ClearOneBookCustomer(customerID);
           GlobalVar::m_customerInfoList.clear();
           GlobalVar::m_customerInfoList = DataBaseOperate::SelectCustomerInfo(customerID);
           info = GlobalVar::m_customerInfoList[0];
           emit signalUpDateMainWindow(index.model()->index(row,2).data().toString());
           sendBookingMsgToCilent(m_customerBookedList[row].getmSocket(),*(info.packageinfos()));
           m_customerBookedList.removeAt(row);
           updateBookingTable();

           break;
    case QMessageBox::Cancel:
           break;
    default:
        break;
    }
 }

  void SeverWindow::sendBookingMsgToCilent(QTcpSocket *connsocket,QString data)//用户服务器和指定客户端通信
  {
      if(connsocket!= nullptr)
      {

          IMProtocol m_protocol;
          QByteArray *buffer =  m_protocol.updataMsg(3,ERROR_INFO_NONE,USER_OPE_USER,OPE_CMD_USER_BOOKOK,
                               MSG_USER_HOST_NONE,MSG_USER_HOST_NONE,data.size(),data);
          connsocket->write(*buffer);
          qDebug()<<"sendBookingMsgToCilent"<<endl;
      }
  }




