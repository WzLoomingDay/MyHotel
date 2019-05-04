#ifndef LOGICLAYER_H
#define LOGICLAYER_H

#include <QObject>
#include "loginwidget.h"
#include "registerwidget.h"
#include "settingwidget.h"
#include "bookingwidget.h"
#include "connectsever.h"

class LogicLayer:public QObject
{
    Q_OBJECT
public:
    LogicLayer();
    ~LogicLayer();
signals:
    void signalSendErrorTips(QString data);
    void signalLoginSuccess(CustomerInfo info);


public slots:
    void SlotLoginSuccess(CustomerInfo info);
     void slotLoginFail(QString msg);
private:
    LoginWidget *m_login;
    RegisterWidget *m_register;
    SettingWidget *m_setting;
    BookingWidget *m_booking;
    ConnectSever * m_connect;
};

#endif // LOGICLAYER_H
