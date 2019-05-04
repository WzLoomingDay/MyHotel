#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "connectsever.h"
#include "customerinfo.h"


namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    void setPbEnabled(bool state);
    void LoginFail(QString error);

signals:
    void signalLogin(QString uid,QString psswd);
    void signalRefreshRequset();
    void signalShowSetting();
private slots:
    void slotGetLoginState(QString state);//测试服务器是否能连接通顺

    void on_pb_login_clicked();

    void on_pb_refresh_clicked();

    void on_pb_setting_clicked();


private:
    Ui::LoginWidget *ui;
    //ConnectSever *m_connectserver;
};

#endif // LOGINWIDGET_H
