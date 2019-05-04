#ifndef USERMANGE_H
#define USERMANGE_H

#include <QWidget>
#include <QDebug>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QRegExp>

#include "comboxdelegate.h"
#include "pushbottondelegate.h"
#include "calenderdelegate.h"
#include "comboxsexdelegate.h"
#include "lineeditdelegate.h"
#include "spinboxdelegate.h"
#include "checkboxdelegate.h"
#include "userinfobox.h"

namespace Ui {
class userMange;
}

class userMange : public QWidget
{
    Q_OBJECT

public:
    explicit userMange(QWidget *parent = 0);
    ~userMange();
    void selectUserData(const QString &sql,QSqlQuery &query,const QString &name);
signals:
    void signalShowUserInfoBox();
private slots:
    void on_pb_search_clicked();

    void on_pb_adduser_clicked();

    void on_comboBox_type_activated(const QString &arg1);

private:
    QStandardItemModel* model;

    Comboxdelegate *comdelegate;
    PushBottonDelegate *Buttondelegate;
    CalenderDelegate *Calenderdelegate;
    comboxSexDelegate *SexDelegate;
    LineEditDelegate * mLineEditDelegat;
    SpinBoxDelegate * mSpinBoxDelegate;
    CheckBoxDelegate *mCheckBoxDelegate;

    UserInfoBox *m_pointerToUserInfo;
    Ui::userMange *ui;
};

#endif // USERMANGE_H
