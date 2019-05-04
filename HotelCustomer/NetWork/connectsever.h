#ifndef CONNECTSEVER_H
#define CONNECTSEVER_H

#include <QObject>
#include <QTcpSocket>
#include <QStringList>
#include "improtocol.h"
#include "execusercmd.h"

class ConnectSever:public QObject
{
    Q_OBJECT
public:
    ConnectSever(QObject *parent = 0);


    const QString &getClientIpAddr(void) const;
    void setClientIpAddr(const QString &ipAddr);

    const QString &getClientPort(void) const;
    void setClientPort(const QString &port);
    void SendMessageToServer(QByteArray *buffer);

signals:
    signalSetLoginState(QString state);
private slots:
    void ReConnect();
    void slotReadyToRead();
    void slotConnectError(QAbstractSocket::SocketError);//检测错误状态
    void slotConnectSuccess();//检测成功状态
    void slotConnectServer(QString id,QString passwd);
    void slotSendBookMsg(QStringList list);
    void setCilentIp(QString newip);

private:
    quint16 m_tcpBlockSize;
    QTcpSocket *m_socket;

    IMProtocol *m_protocol;
    ExecUserCmd *m_execUserCmd;

    QString m_serverIpAddr;
    QString m_serverPort;

    QString m_clientIpAddr;
    QString m_clientPort;
};

#endif // CONNECTSEVER_H
