#ifndef SEVERWINDOW_H
#define SEVERWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMap>

#include "connectcilent.h"
#include "customerinfo.h"
#include "improtocol.h"
#include "execusercmd.h"


namespace Ui {
class SeverWindow;
}

class SeverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SeverWindow(QWidget *parent = 0);
    ~SeverWindow();
    //QMap<QString,QTcpServer*> m_customermap;
    ListCustomerInfo m_customerRequestList;
    ListCustomerInfo m_customerBookedList;
    void updateMainWindow();
    void updateRequestTable();
    void updateBookingTable();
    void sendBookingMsgToCilent(QTcpSocket *connsocket,QString data);
    void shutDownServer();
    QTcpServer *getMtcpServer();
signals:
    //void signalBookingSuccess(CustomerInfo info);
    void signalUpDateMainWindow(QString room_type);//预定后更新主界面
private slots:
    void on_pb_opensever_clicked();
    void slotNewConnectSocket();

    void slotAddNewCustomer(CustomerInfo info);

    void slotChickRequestTable(QModelIndex index);
    void slotChickBookingTable(QModelIndex index);


private:
    QTcpServer * m_tcpServer; //监听
    QTcpSocket * m_tcpSocket; //通信
    quint16 m_port;
    Ui::SeverWindow *ui;
};

#endif // SEVERWINDOW_H
