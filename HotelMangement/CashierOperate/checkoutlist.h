#ifndef CHECKOUTLIST_H
#define CHECKOUTLIST_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "billinfo.h"
#include "roominfo.h"
#include "databaseoperate.h"
#include "showmealdetail.h"
class CheckOutList:public QWidget
{
    Q_OBJECT
public:
    CheckOutList(QString &Sender,BillInfo &info,QWidget *parent = 0);
signals:
    void signalShowMealDetails();
    void SignalUpdateList(QString sender,QString roomtype);
private slots:
    void slotPBmealdetail();
    void slotClickCheckOut();
private:

    QHBoxLayout *m_layout;
    QLabel *m_room_id;
    QLabel *m_room_name;
    QLabel *m_bill_name;
    QLabel *m_bill_lefttime;
    QLabel *m_bill_roomcash;
    QLabel *m_bill_pledge;
    QLabel *m_bill_mealcash;
    QPushButton *m_pbMealDetail;
    QLabel *m_bill_totalcash;
    QPushButton *m_pbCheckOut;

    RoomInfo m_roominfo;
    BillInfo m_billinfo;
    ShowMealDetail *m_pointerToMealDetail;
    QString m_sender;
};

#endif // CHECKOUTLIST_H
