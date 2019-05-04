#ifndef CONNECTCILENT_H
#define CONNECTCILENT_H

#include <QThread>
#include <QObject>
#include <QByteArray>
#include <QTcpSocket>
#include <QDataStream>
#include "improtocol.h"
#include "execusercmd.h"

class connectCilent:public QThread
{
    Q_OBJECT
public:
    connectCilent(QTcpSocket *msocket);
    QTcpSocket* get_mTcpSocket();
signals:
    void signalSendMsgtoClient(QByteArray *buffer);
    void signalSendBookingRequest(CustomerInfo info);
public slots:
    void slotReadyToRead();
    void slotSendMessageToCilent(QByteArray *buffer);
    void slotSendErrorMessageToCilent(QByteArray *buffer);
public:
    void run();
    void recvMsg(void);
    void sendMsg(QString msg);

private:
     QTcpSocket *m_socket;
     IMProtocol *m_protocol;
     ExecUserCmd *m_execUserCmd;
};

#endif // CONNECTCILENT_H
