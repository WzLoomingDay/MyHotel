#ifndef DATABASEOPERATE_H
#define DATABASEOPERATE_H
#include<QDebug>
#include<QSqlQuery>
#include<QStandardItem>
#include<QObject>
#include<QWidget>
#include<QSqlRecord>
#include<QVariant>
#include<QStringList>
#include<QList>
#include<QMap>
#include <QDate>
#include <QVector>
#include "userinfo.h"
#include "workerinfo.h"
#include "roominfo.h"
#include "billinfo.h"
#include "addmeals.h"
#include "mealinfo.h"
#include "customerinfo.h"

#define ALL_BILL "ALL"
#define USING_BILL "USING"

#define YEAR "YEAR"
#define MOUTH "MOUTH"

#define ALL_MEAL "ALLMEAL"

#define ALL_CUSTOMER "ALLCUSTOMER"

#define EMPTY "0"
#define FULL "1"

#define CUSTOMER_IDCARD "0"
#define CUSTOMER_NAME "1"

#define ROOM_EMPYT "空闲"
#define ROOM_BOOK "预定"
#define BOOK_USE "使用"

class DataBaseOperate
{
public:
    DataBaseOperate();
    ~DataBaseOperate();
    static UserInfo selectUserCashierInfo(QString id,QString passwd);
    static UserInfo selectUserMangerInfo(QString id,QString passwd);

    static bool AddWorkerInfo();
    static void DeleteWorkerInfo(const QString &ID);
    static void DeleteMealInfo(const int &MEALID);
    static bool DeleteRoomInfo(QString &RID);

    static bool CreateWorkerInfo(WorkerInfo &info);
    static void CreateBillInfo(BillInfo &info);
    static void CreateMealInfo(MealInfo &info);
    static bool CreateRoomInfo(RoomInfo &info);


    static void UpdateUserType(QString const &ID,const QString &new_type);
    static void UpdateUserMessage(QString const &ID,QString const &name,const QString &new_type);
    static void UpdateBillMeal(BillInfo &info);
    static void UpdateIncome(int &money);
    static void UpdateMealInfo(MealInfo &info);
    static bool UpdateRoomInfo(RoomInfo &info);
    static void UpdateRoomState(QString RID,QString state);
    static bool updateCustomerInfo(CustomerInfo &info);

    static void UpdateBillCheckout(QString &Billid,QString &RID);

    static RoomInfoList SelectRoomInfo(QString roomtype,QString roomfloor);
    static ListBillInfo SelectUsingBillInfo(QString roomtype);
    static ListCustomerInfo SelectCustomerInfo(QString cid);
    static RoomInfo SelectRoomIDInfo(QString ROOMID);
    static RoomInfo SelectRoomNameInfo(QString ROOMNAME);
    static RoomInfoList SelectEmptyRoomInfo(QString roomtype);
    static RoomInfoList SelectUsingRoomInfo(QString roomtype);
    static ListBillInfo SelectBillInfo(QString RID);
    static ListMealInfo SelectMealInfo(QString type);
    static MealInfo SelectMealInfo(int ID);
    static ListBillInfo SelectHistoryInfo(QString date);
    static QStringList SelectCustomerInRoom(QString type,QString message);


   // static RoomInfo SelectRoomIDInfo(QString ROOMID);
    static QList<int> SelectIncomeInfo(QString type,QString data);


    static void ClearAllBookCustomer();
    static void ClearOneBookCustomer(QString cid);
    static int countRoomNumber(QString type);
    static QString GetRecentday();
    static int GetPayid();
    static QString SelectNewMealID();
    static int GetTodayPayid();
    static void ResetPayID();
    static void CreateIncomeInfo(QString const &dayid);
    static QString  GetIdnumber();//得到第一个不连续的id
    static QString  GetRoomIdnumber();//得到第一个不连续的Rid
protected:
    static int  countbits(int number);//计算数字有几位


};

#endif // DATABASEOPERATE_H
