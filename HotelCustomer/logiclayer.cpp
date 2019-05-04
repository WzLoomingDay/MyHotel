#include "logiclayer.h"

LogicLayer::LogicLayer()
{
    m_login = new LoginWidget();
    m_register = new RegisterWidget();
    m_setting = new SettingWidget();
    m_booking = new BookingWidget();
    m_connect = new ConnectSever(this);


    connect(m_connect,SIGNAL(signalSetLoginState(QString)),//获取服务器状态
            m_login,SLOT(slotGetLoginState(QString)));
    connect(m_login,SIGNAL(signalLogin(QString,QString)),
            m_connect,SLOT(slotConnectServer(QString,QString)));//登陆模块点击登陆
    connect(m_login,SIGNAL(signalRefreshRequset()),
            m_connect,SLOT(ReConnect()));//登陆模块刷新
    connect(m_booking,SIGNAL(signalBooking(QStringList)),
            m_connect,SLOT(slotSendBookMsg(QStringList)));

    connect(m_login,SIGNAL(signalShowSetting()),
            m_setting,SLOT(slotShowSetting()));
    connect(m_setting,SIGNAL(signalSettingIp(QString)),
            m_connect,SLOT(setCilentIp(QString)));

    m_login->show();
}

void LogicLayer::SlotLoginSuccess(CustomerInfo info)
{
    m_login->hide();
    m_booking->ShowBookingWidget(info);
}

void LogicLayer::slotLoginFail(QString msg)
{
    m_login->LoginFail(msg);
}


LogicLayer::~LogicLayer()
{
    qDebug()<<"LogicLayer::~LogicLayer()"<<endl;
}
