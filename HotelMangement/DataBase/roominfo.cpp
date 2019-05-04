#include "roominfo.h"

RoomInfo::RoomInfo(QString &id,QString &state,QString &name,QString &type,QString &place,
                  QString &price,QString &discount,QString &call):
                   m_room_id(id),m_room_state(state),m_room_name(name),m_room_type(type),m_room_place(place),
                   m_room_price(price),m_room_discount(discount),m_room_call(call)
                    {

                    }

void RoomInfo::displayinfo()
{
    qDebug()<<"m_room_info  ID = "<<m_room_id<<endl;
    qDebug()<<"m_room_info  STATE = "<<m_room_state<<endl;
    qDebug()<<"m_room_info  NAME = "<<m_room_name<<endl;
    qDebug()<<"m_room_info  Type = "<<m_room_type<<endl;
    qDebug()<<"m_room_info  place = "<<m_room_place<<endl;
    qDebug()<<"m_room_info  price = "<<m_room_price<<endl;
    qDebug()<<"m_room_info  discount = "<<m_room_discount<<endl;
    qDebug()<<"m_room_info  call = "<<m_room_call<<endl;
}
void RoomInfo::set_room_id(const QString &id)
{
 m_room_id = id;
}
void RoomInfo::set_room_state(const QString &state)
{
    m_room_state = state;
}
void RoomInfo::set_room_name(const QString &name)
{
    m_room_name = name;
}
void RoomInfo::set_room_type(const QString &type)
{
    m_room_type = type;
}
void RoomInfo::set_room_place(const QString &place)
{
    m_room_place = place;
}
void RoomInfo::set_room_price(const QString &price)
{
    m_room_price = price;
}
void RoomInfo::set_room_discount(const QString &discount)
{
    m_room_discount = discount;
}
void RoomInfo::set_room_call(const QString &call)
{
    m_room_call = call;
}



const QString &RoomInfo::get_room_id() const
{
    return m_room_id;
}
const QString &RoomInfo::get_room_state() const
{
   return  m_room_state;
}
const QString &RoomInfo::get_room_name() const
{
   return m_room_name;
}
const QString &RoomInfo::get_room_type() const
{
    return m_room_type;
}
const QString &RoomInfo::get_room_place() const
{
    return m_room_place;
}
const QString &RoomInfo::get_room_price() const
{
    return m_room_price;
}
const QString &RoomInfo::get_room_discount() const
{
    return m_room_discount;
}
const QString &RoomInfo::get_room_call() const
{
    return m_room_call;
}
