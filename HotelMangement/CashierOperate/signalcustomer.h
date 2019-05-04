#ifndef SIGNALCUSTOMER_H
#define SIGNALCUSTOMER_H

#include <QWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "databaseoperate.h"
#include "globalvar.h"
#include "signallistitem.h"
#include "billinfo.h"
namespace Ui {
class SignalCustomer;
}

class SignalCustomer : public QWidget
{
    Q_OBJECT

public:

    ~SignalCustomer();
     void closeEvent(QCloseEvent *event = nullptr);
     static SignalCustomer *getSignalCustomer();
signals:
     void signalUpdateMainMesage(QString roomtype);
private slots:
     void slotShowSignalCustomer(QString);
     void slotCurrentIndexChanged(QString);
     void slotSetSelectedRoom(QString,QString);
     void on_pushButton_calculate_clicked();


     void on_pb_deal_clicked();

     void on_pb_cancle_clicked();

private:
    Ui::SignalCustomer *ui;
    explicit SignalCustomer(QWidget *parent = 0);//构造方法private，限制了其外部new的想法
    static SignalCustomer *m_SignalCustomer;

    QListWidgetItem *m_listItem;
    SignalListItem *m_signaListlWidget;
    QString m_roomselect;
    QString m_uid;
    /*QWidget *WContanter;
    QHBoxLayout *m_layout;
    QLabel *m_room_pic;
    QLabel *m_room_name ;
    QLabel *m_room_floor ;
    QLabel *m_room_price;
    QLabel *m_room_discount ;
    QPushButton *m_pushbutton;*/
};

#endif // SIGNALCUSTOMER_H
