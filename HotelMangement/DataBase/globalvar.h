#ifndef GLOBALVAR_H
#define GLOBALVAR_H
#include "userinfo.h"
#include "workerinfo.h"
#include "roominfo.h"
#include "billinfo.h"
#include "mealinfo.h"
#include "customerinfo.h"
class GlobalVar
{
public:
    GlobalVar();
    static ListUserInfo m_userInfoList;
    static WorkerInfoList m_workerInfoList;
    static RoomInfoList m_roomInfoList;
    static ListBillInfo m_billInfoList;
    static ListMealInfo m_mealInfoList;
    static ListCustomerInfo m_customerInfoList;

};

#endif // GLOBALVAR_H
