#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H

#include <QString>
#include <QList>
#include <QTcpSocket>
#include"getsetmethod.h"
#define BOOKING_NO "0"
#define BOOKING_WAIT "1"
#define BOOKING_SUCCESS "2"
class CustomerInfo
{
public:
    CustomerInfo(){}
    CustomerInfo(QString cid,QString pswd,QString name,
                 QString Sex,QString Call,QString idcard,QString flag = "0",QString RID = "",QString roomtype = "",
            QString addr = "",QString port = "");
    QString m_cid;
    QString m_pswd;
    QString m_name;
    QString m_Sex;
    QString m_Call;
    QString m_idcard;
    QString m_flag;
    QString m_RID;
    QString m_roomtype;
    QString m_addr;
    QString m_port;

    //QTcpSocket *m_socket;//不是数据库的信息，临时记录socket通信
    //void setmSocket(QTcpSocket *msocket);
    //QTcpSocket * getmSocket();
    PropertyBuilderByName(QString,m_cid)
    PropertyBuilderByName(QString,m_pswd)
    PropertyBuilderByName(QString,m_name)
    PropertyBuilderByName(QString,m_Sex)
    PropertyBuilderByName(QString,m_Call)
    PropertyBuilderByName(QString,m_idcard)
    PropertyBuilderByName(QString,m_flag)
    PropertyBuilderByName(QString,m_RID)
    PropertyBuilderByName(QString,m_roomtype)
    PropertyBuilderByName(QString,m_addr)
    PropertyBuilderByName(QString,m_port)
    QString *packageinfos();
    CustomerInfo setCustomerInfo(QStringList list);

};
typedef QList<CustomerInfo> ListCustomerInfo;

#endif // CUSTOMERINFO_H
