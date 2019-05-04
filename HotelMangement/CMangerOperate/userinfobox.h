#ifndef USERINFOBOX_H
#define USERINFOBOX_H

#include <QWidget>
#include <QString>
#include<QDate>
#include<QMessageBox>
#include "databaseoperate.h"
#include "workerinfo.h"
#include "regexp.h"


namespace Ui {
class UserInfoBox;
}

class UserInfoBox : public QWidget
{
    Q_OBJECT
public:


    ~UserInfoBox();
    void closeEvent(QCloseEvent *event);
    static UserInfoBox * GetUserInfoBox();
    static void setUserInfoNullptr();
private:
     UserInfoBox(QWidget *parent = 0);//将构造函数私有化，堵死了外部利用new实例化对象的方法
private slots:
    void slotShowUserInfoBox();

    void on_pb_confirm_clicked();

    void on_pb_giveup_clicked();
private:

    WorkerInfo m_workerInfo;

    Ui::UserInfoBox *ui;
    static UserInfoBox *m_userInfoBox;
};

#endif // USERINFOBOX_H
