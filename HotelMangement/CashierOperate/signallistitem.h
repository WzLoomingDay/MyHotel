#ifndef SIGNALLISTITEM_H
#define SIGNALLISTITEM_H
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>


class SignalListItem : public QWidget
{
    Q_OBJECT
public:
    explicit SignalListItem(QWidget *parent = 0);
    ~SignalListItem();
    void SetMessage(QString room_id,QString room_name,QString room_floor,
                     QString room_price,QString room_discount);
    void SetPic(QString picpath);
signals:
    void signalSendName(QString,QString);
public slots:
    void slotSendRoomName();

private:
    QHBoxLayout *m_layout;
    QLabel *m_room_pic;
    QLabel *m_room_name;
    QLabel *m_room_floor;
    QLabel *m_room_price;
    QLabel *m_room_discount;
    QPushButton *m_pushbutton;
    QString m_room_id;


};

#endif // SIGNALLISTITEM_H
