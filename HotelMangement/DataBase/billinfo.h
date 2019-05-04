#ifndef BILLINFO_H
#define BILLINFO_H

#include <QString>
#include <QList>
#include"getsetmethod.h"
class BillInfo
{
public:
    BillInfo(QString BILLID,QString RID,QString UID,QString c_usingflag,int c_payid,
             QString c_idcard,QString c_name,QString c_sex,QString c_call,
             int c_day,QString c_timebegin,QString c_timeend,
             int c_cash,int c_pledge,QString c_mealflag,
             QString c_mealbill,QString c_mealcash);
    BillInfo();

private:
    QString m_BILLID;
    QString m_RID;
    QString m_UID;
    QString m_usingfalg;
    int m_payid;
    QString m_idcard;
    QString m_name;
    QString m_sex;
    QString m_call;
    int m_day;
    QString m_timebegin;
    QString m_timeend;
    int m_cash;
    int m_pledge;
    QString m_mealflag;
    QString m_mealbill;
    QString m_mealcash;
    PropertyBuilderByName(QString,m_BILLID)
    PropertyBuilderByName(QString,m_RID)
    PropertyBuilderByName(QString,m_UID)
    PropertyBuilderByName(QString,m_usingfalg)
    PropertyBuilderByName(int,m_payid)
    PropertyBuilderByName(QString,m_idcard)
    PropertyBuilderByName(QString,m_name)
    PropertyBuilderByName(QString,m_sex)
    PropertyBuilderByName(QString,m_call)
    PropertyBuilderByName(int,m_day)
    PropertyBuilderByName(QString,m_timebegin)
    PropertyBuilderByName(QString,m_timeend)
    PropertyBuilderByName(int,m_cash)
    PropertyBuilderByName(int,m_pledge)
    PropertyBuilderByName(QString,m_mealflag)
    PropertyBuilderByName(QString,m_mealbill)
    PropertyBuilderByName(QString,m_mealcash)


};
typedef QList<BillInfo> ListBillInfo;

#endif // BILLINFO_H
