#include "customerinfo.h"

CustomerInfo::CustomerInfo(QString cid,QString pswd,QString name,
                           QString Sex,QString Call,QString idcard,
                           QString flag,QString RID,QString roomtype,
                           QString addr,QString port)
                            :m_cid(cid),m_pswd(pswd),m_name(name),
                              m_Sex(Sex),m_Call(Call),m_idcard(idcard),
                              m_flag(flag),m_RID(RID),m_roomtype(roomtype),
                              m_addr(addr),m_port(port)


{

}

QString* CustomerInfo::packageinfos()
{
    QString *data = new QString();
    data->clear();

    data->append(getm_cid());
    data->append("|");
    data->append(getm_pswd());
    data->append("|");
    data->append(getm_name());
    data->append("|");
    data->append(getm_Sex());
    data->append("|");
    data->append(getm_Call());
    data->append("|");
    data->append(getm_idcard());
    data->append("|");
    data->append(getm_flag());
    data->append("|");
    data->append(getm_RID());
    data->append("|");
    data->append(getm_roomtype());
    data->append("|");
    data->append(getm_addr());
    data->append("|");
    data->append(getm_port());

    return data;

}

/*void CustomerInfo::setmSocket(QTcpSocket *msocket)
{
   m_socket = msocket;
}
QTcpSocket * CustomerInfo::getmSocket()
{
    return m_socket;
}*/
 CustomerInfo CustomerInfo::setCustomerInfo(QStringList list)
 {
     CustomerInfo info;
     info.setm_cid(list[0]);
     info.setm_pswd(list[1]);
     info.setm_name(list[2]);
     info.setm_Sex(list[3]);
     info.setm_Call(list[4]);
     info.setm_idcard(list[5]);
     info.setm_flag(list[6]);
     info.setm_RID(list[7]);
     info.setm_roomtype(list[8]);
     info.setm_addr(list[9]);
     info.setm_port(list[10]);
     return info;
 }




