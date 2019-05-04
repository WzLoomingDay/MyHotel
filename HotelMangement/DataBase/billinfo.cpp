#include "billinfo.h"

BillInfo::BillInfo(QString BILLID,QString RID,QString UID,QString c_usingflag,int c_payid,
                   QString c_idcard,QString c_name,QString c_sex,QString c_call,
                   int c_day,QString c_timebegin,QString c_timeend,
                   int c_cash,int c_pledge,QString c_mealflag,
                   QString c_mealbill,QString c_mealcash)
                   :m_BILLID(BILLID),m_RID(RID),m_UID(UID),m_usingfalg(c_usingflag),m_payid(c_payid),
                    m_idcard(c_idcard),m_name(c_name),m_sex(c_sex),m_call(c_call),
                    m_day(c_day),m_timebegin(c_timebegin),m_timeend(c_timeend),
                    m_cash(c_cash),m_pledge(c_pledge),m_mealflag(c_mealflag),
                    m_mealbill(c_mealbill),m_mealcash(c_mealcash)
{

}


BillInfo::BillInfo()
{

}
