#ifndef CONNECTSEVER_H
#define CONNECTSEVER_H

#include <QObject>
#include <QTcpSocket>

class ConnectSever:public QObject
{
    Q_OBJECT
public:
    const quint16 m_sever_port;
    ConnectSever();

    QTcpSocket *m_socket;
private slots:
    void slotReadyToRead();


};

#endif // CONNECTSEVER_H
