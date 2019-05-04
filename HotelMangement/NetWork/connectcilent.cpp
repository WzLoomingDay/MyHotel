#include "connectcilent.h"


connectCilent::connectCilent(QTcpSocket *msocket)
{
    m_execUserCmd = new ExecUserCmd(msocket);
    m_protocol = new IMProtocol;
    m_socket = msocket;

    //qDebug()<<"connectCilent::connectCilent(QTcpSocket *msocket)"<<endl;
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(slotReadyToRead()));
    connect(m_execUserCmd, SIGNAL(signalSendMsgtoClient(QByteArray*)),
            this, SLOT(slotSendMessageToCilent(QByteArray*)));
    connect(m_execUserCmd,SIGNAL(signalSendErrorMsgtoClient(QByteArray*)),
            this,SLOT(slotSendErrorMessageToCilent(QByteArray*)));
    connect(m_execUserCmd,SIGNAL(signalBookingRequest(CustomerInfo)),
            this,SIGNAL(signalSendBookingRequest(CustomerInfo)));



}
 void connectCilent::run()
 {

 }
void connectCilent::slotReadyToRead()
{
    qDebug()<<"connectCilent::slotReadyToRead()"<<endl;
    recvMsg();

}
void connectCilent::slotSendMessageToCilent(QByteArray *buffer)
{
    qDebug()<<"connectCilent::slotSendMessageToCilent"<<endl;
    m_socket->write(*buffer);

}
void connectCilent::slotSendErrorMessageToCilent(QByteArray *buffer)
{
    qDebug()<<"connectCilent::slotSendErrorMessageToCilent"<<endl;
     m_socket->write(*buffer);
}

void connectCilent::recvMsg(void)//收到信息解包
{
    QDataStream in(m_socket);//QDataStream数据流进来
    in.setVersion(QDataStream::Qt_5_8);//设置版本
    //QString data;
    //in>>data;
    //qDebug()<<"data = "<<data<<endl;
    m_protocol->unpackageMsg(in);//流到协议类中
    m_execUserCmd->analysisProtocol(m_protocol);

}

void connectCilent::sendMsg(QString msg)
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);

    out << msg;

    m_socket->write(buffer);
//  m_socket->disconnectFromHost();
}

QTcpSocket* connectCilent::get_mTcpSocket()
{
    return m_socket;
}




