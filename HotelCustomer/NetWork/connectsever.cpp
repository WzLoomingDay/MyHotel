#include "connectsever.h"
#include <QDebug>
#include <QDataStream>
#include <QMessageBox>
#include <QByteArray>
#include "logicLayer.h"

ConnectSever::ConnectSever(QObject *parent):QObject(parent),m_tcpBlockSize(0)
{
    m_serverIpAddr = "172.20.10.11" ;
    m_serverPort = "8888";

    m_clientPort = "6666";
    m_clientIpAddr = "localhost";

    m_socket = new QTcpSocket(this);
    m_execUserCmd = new ExecUserCmd();
    m_protocol = new IMProtocol;

    connect(m_socket,SIGNAL(readyRead()),
            this,SLOT(slotReadyToRead()));

    connect(m_execUserCmd,SIGNAL(signalSendErrorTips(QString)),
            (LogicLayer *)(this->parent()),SLOT(slotLoginFail(QString)));//LogicLayer发送失败信号
    connect(m_execUserCmd,SIGNAL(signalLoginSuccess(CustomerInfo)),//发送成功信号
            (LogicLayer *)(this->parent()),SLOT(SlotLoginSuccess(CustomerInfo)));

    m_socket->connectToHost(m_serverIpAddr,m_serverPort.toInt());


    //connect(this,SIGNAL(signalSetLoginState(QString)),
      //       (LoginWidget *)this->parent(),SLOT(slotGetLoginState(QString)));//给主界面返回状态
    connect(m_socket,SIGNAL(error(QAbstractSocket::SocketError)),//连接服务器出错，返回状态
            this,SLOT(slotConnectError(QAbstractSocket::SocketError)));
    connect(m_socket,SIGNAL(connected()),//连接服务器成功返回
            this,SLOT(slotConnectSuccess()));


}

void  ConnectSever::setCilentIp(QString newip)
{
    m_clientIpAddr = newip;

}
void ConnectSever::ReConnect()//重新连接
{
    qDebug()<<"ConnectSever::ReConnect()"<<endl;
   if(m_socket->state() == QAbstractSocket::ConnectedState)
   {
       QString name = "已经连接";
       QString tips = "端口"+m_socket->peerName()+"已经连接";
       QMessageBox::information(0,name,tips,QMessageBox::Ok);

   }else
   {
       m_socket->connectToHost(m_serverIpAddr,m_serverPort.toInt());
   }

}

void ConnectSever::slotReadyToRead()
{
    qDebug()<<"ConnectSever::slotReadyToRead()"<<endl;
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_5_8);

    m_protocol->unpackageMsg(in);

    m_execUserCmd->analysisProtocol(m_protocol);

    m_tcpBlockSize = 0;
}

void ConnectSever::slotConnectError(QAbstractSocket::SocketError)
{
    qDebug()<<"error"<<m_socket->errorString()<<endl;
    QString state = "停机维护";
    emit signalSetLoginState(state);

}
void ConnectSever::slotConnectSuccess()
{
    qDebug()<<"loginsuccesss"<<endl;
    QString state = "通顺";
    emit signalSetLoginState(state);
}

void ConnectSever::slotSendBookMsg(QStringList list)
{
    qDebug()<<"ConnectSever::slotSendBookMsg(QStringList list)"<<endl;
     QString msg;
    int i = 0;
    for(i;i < (list.size()-1);i++)//size i -1是为了最后一个没有"|"
    {
       msg = msg + list[i]+"|";
    }
    msg = msg + list[i];
    QByteArray *data = m_protocol->updataMsg(2,ERROR_INFO_NONE,
                                             USER_OPE_USER,OPE_CMD_USER_BOOK,
                                             MSG_USER_HOST_NONE,MSG_USER_HOST_NONE,
                                             msg.size(),msg);
    SendMessageToServer(data);


}
void ConnectSever::SendMessageToServer(QByteArray *buffer)
{
    qDebug()<<"ConnectSever::slotSendMessageToServer(QByteArray *buffer)"<<endl;
    m_socket->write(*buffer);
}

void ConnectSever::slotConnectServer(QString id,QString passwd)
{
    QString msg = id + "|" + passwd + "|" +  m_clientIpAddr + "|" + m_clientPort;
    QByteArray * data = m_protocol->updataMsg(1,ERROR_INFO_NONE,
                                              USER_OPE_LOGIN,OPE_CMD_LOGIN_ASK,
                                              MSG_USER_HOST_NONE,MSG_USER_HOST_NONE,
                                              msg.size(),msg);
     m_socket->write(*data);//qbytearrary字节流(char流)
}



const QString &ConnectSever::getClientIpAddr(void) const
{
    return m_clientIpAddr;
}
void ConnectSever::setClientIpAddr(const QString &ipAddr)
{
    m_clientIpAddr = ipAddr;
}

const QString &ConnectSever::getClientPort(void) const
{
    return m_clientPort;
}
void ConnectSever::setClientPort(const QString &port)
{
    m_clientPort = port;
}
