#ifndef ROOMDETAIL_H
#define ROOMDETAIL_H

#include <QWidget>
#include <QMouseEvent>
#include <QFocusEvent>
#include "roominfo.h"


namespace Ui {
class RoomDetail;
}

class RoomDetail : public QWidget
{
    Q_OBJECT

public:
    explicit RoomDetail(RoomInfo room_info,QWidget *parent = 0);
    void setPic(QString picload);
    ~RoomDetail();
    QString& GetRoomState();

signals:
    void signalshowbillmessage(RoomInfo info);
protected:
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
private:
    Ui::RoomDetail *ui;
    QString oldstylesheet;
    QString newstylesheet;
    RoomInfo m_room_info;
};

#endif // ROOMDETAIL_H
