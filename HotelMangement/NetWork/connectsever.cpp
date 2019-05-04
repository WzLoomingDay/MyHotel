#include "connectsever.h"
#include <QDebug>

ConnectSever::ConnectSever():QObject(0),m_sever_port(55555)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket,SIGNAL(readyRead()),
            this,SLOT(slotReadyToRead()));
    m_socket->connectToHost("localhost",m_sever_port);

}

void ConnectSever::slotReadyToRead()
{
    qDebug()<<"ConnectSever::slotReadyToRead()"<<endl;
}
