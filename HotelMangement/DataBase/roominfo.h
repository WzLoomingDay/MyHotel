#ifndef ROOMINFO_H
#define ROOMINFO_H

#include <QString>
#include <QList>
#include <QDebug>

class RoomInfo
{
public:
    RoomInfo(QString &id,QString &state,QString &name,QString &type,QString &place,
    QString &room_price,QString &discount,QString &room_call);
    RoomInfo(){}


    void displayinfo();
    void set_room_id(const QString &state);
    void set_room_state(const QString &state);
    void set_room_name(const QString &name);
    void set_room_type(const QString &type);
    void set_room_place(const QString &place);
    void set_room_price(const QString &price);
    void set_room_discount(const QString &discount);
    void set_room_call(const QString &call);

    const QString &get_room_id() const;
    const QString &get_room_state() const;
    const QString &get_room_name() const;
    const QString &get_room_type() const;
    const QString &get_room_place() const;
    const QString &get_room_price() const;
    const QString &get_room_discount() const;
    const QString &get_room_call() const;

private:
    QString m_room_id;
    QString m_room_state;
    QString m_room_name;
    QString  m_room_type;
    QString  m_room_place;
    QString m_room_price;
    QString  m_room_discount;
    QString  m_room_call;
};
typedef QList<RoomInfo> RoomInfoList;

#endif // ROOMINFO_H
