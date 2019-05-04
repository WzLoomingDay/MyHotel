#ifndef CCASHIEROPERATE_H
#define CCASHIEROPERATE_H

#include <QWidget>
#include<QMessageBox>
#include <QTableWidget>
#include <QTabWidget>

#include <QGridLayout>
#include "roomdetail.h"
#include "databaseoperate.h"
#include "signalcustomer.h"
#include "checkout.h"
#include "history.h"
#include "severwindow.h"


namespace Ui {
class CCashierOperate;
}

class CCashierOperate : public QWidget
{
    Q_OBJECT

public:
    explicit CCashierOperate(QWidget *parent = 0);
    ~CCashierOperate();
    void updateOperateWindow(int colum,QGridLayout *layout_type,QWidget * room_type,QString pic);
    void glanceOverDetail(QString roomtype,QString roomcall,QString roompalce,QString roomdiscount,
                          QString roomstarttime = " ",QString roomlefttime = " ",QString customername = " ",
                          QString customersex = " ",QString customeridcard = " ",int customerdays  = 0,
                          int customerpledge = 0,int customercash = 0,int payid = 0);
    void closeEvent(QCloseEvent *event);
signals:
     void SignalSignalCustomer(QString ID);
     void SingalAddMeals(QString ID);
     void SignalCheckOut(QString ID);
     void SignalHistory(QString ID);
private slots:
    void slotShowCashierLogin(QString ID);
    void slotCurrentTabIndexChange(int index);
    void slotRefleshCurrentIndex(QString roomtype);
    void SlotShowbillMessage(RoomInfo roominfo);
    void slotUpdateRoomState();

    void on_pushButton_SignalCustomer_clicked();

    void on_PB_addmeals_clicked();

    void on_PB_accument_clicked();

    void on_PB_history_clicked();

    void on_pushButton_search_clicked();

    void on_pb_sever_clicked();

private:

    Ui::CCashierOperate *ui;
    QString m_operate_id;
    QWidget *m_table_signal;
    QWidget *m_table_ssignal;
    QWidget *m_table_double;
    QWidget *m_table_sdouble;
    QWidget *m_table_family;
    QWidget *m_table_present;

    QGridLayout *m_gridlayout_signal;
    QGridLayout *m_gridlayout_ssignal;
    QGridLayout *m_gridlayout_double;
    QGridLayout *m_gridlayout_sdouble;
    QGridLayout *m_gridlayout_family;
    QGridLayout *m_gridlayout_present;

    QRect rect;
    QRect rectSever;

    SignalCustomer * m_pointToSignalCustomer;
    AddMeals *m_pointerToaddmeals;
    CheckOut *m_pointerToCheckout;
    History *m_pointerToHistory;
    SeverWindow *m_pointerToSeverWindow;

};

#endif // CCASHIEROPERATE_H
