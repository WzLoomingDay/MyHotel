#include "databaseoperate.h"

DataBaseOperate::DataBaseOperate()
{

}
DataBaseOperate::~DataBaseOperate()
{

}

UserInfo DataBaseOperate::selectUserCashierInfo(QString id,QString passwd)
{
    UserInfo info;
    QSqlQuery query;
    QString queryString =
    QString("select * from user where UID = '%1' and type_name = 'Cashier'").arg(id);
    //查找id并且是cashier的用户
    qDebug() << queryString;
    query.exec(queryString);
    if(query.isActive())//isActive判断sql语句是否正确
    {
    if(query.first())//first判断是否查到，查到true，没查到false
    {//如果有该前台用户判断密码是否正确
        queryString =
        QString("select * from user where UID = '%1' and pswd = '%2'").arg(id).arg(passwd);
        qDebug() << queryString;
        query.exec(queryString);
        if(query.first())
        {
         int select_ID = query.record().indexOf(QString("UID"));//查到了一条完整数据的ID
         QString select_IDstr =query.value(select_ID).toString();
         qDebug()<<"UID:"<<select_IDstr<<endl;
        }else
        {
            info.setPswd(QString("NULL"));
        }
        }else
        {

            qDebug() << "Error select User"<<endl;
            info.setID(QString("NULL"));//没查到就返回ID为NULL
        }
        }else
        {
            qDebug() << "Error select sql order"<<endl;//select的sql语句错误，查找失败
        }
        return info;

}


UserInfo DataBaseOperate::selectUserMangerInfo(QString id,QString passwd)
{
    UserInfo info;
    QSqlQuery query;
    QString queryString =
    QString("select * from user where UID = '%1' and type_name = 'Manger'").arg(id);
    query.exec(queryString);
    if(query.isActive())
    {
    if(query.first())
    {//如果有该管理员用户判断密码是否正确
        queryString =
        QString("select * from user where UID = '%1' and pswd = '%2'").arg(id).arg(passwd);
        query.exec(queryString);
        if(query.first())
        {
         QString i1=query.value(0).toString();
         qDebug() << i1;
        }else
        {
            info.setPswd(QString("NULL"));
        }
    }else
    {

        qDebug() << "Error select User"<<endl;
        info.setID(QString("NULL"));//没查到就返回ID为NULL
    }
    }else
    {
        qDebug() << "Error select sql order"<<endl;//select的sql语句错误，查找失败
    }
    return info;

}


bool DataBaseOperate::CreateWorkerInfo(WorkerInfo &info)
{
    QSqlQuery Createquery;
    QString CreateUserqueryString =
    QString("insert into user values('%1','%2','%3')")
            .arg(info.getID()).arg(info.getPswd()).arg(info.getType());
    QString CreateWorkerqueryString =
    QString("insert into Worker values ('%1','%2','%3','%4','%5','%6','%7')")
            .arg(info.GetWorkerID()).arg(info.GetWorkerName()).arg(info.GetWorkerSex())
            .arg(info.GetWorkerCall()).arg(info.GetWorkerSalary())
            .arg(info.GetWorkerBirth()).arg(info.GetWorkerJoinTime());
     qDebug()<<CreateUserqueryString;
     qDebug()<<CreateWorkerqueryString;
     Createquery.exec(CreateUserqueryString);
     Createquery.exec(CreateWorkerqueryString);
     return true;

}
void DataBaseOperate::CreateMealInfo(MealInfo &info)
{
    QSqlQuery Createquery;
    QString CreateMealqueryString =
    QString("insert into meal values(%1,'%2','%3',%4)")
            .arg(info.getm_mealid()).arg(info.getm_mealname()).arg(info.getm_mealtype())
            .arg(info.getm_mealprice());

     qDebug()<<CreateMealqueryString;
     Createquery.exec(CreateMealqueryString);
     return;

}
bool DataBaseOperate::CreateRoomInfo(RoomInfo &info)
{
    QSqlQuery Createquery;
    QString CreateRoomInfoString =
    QString("insert into room values('%1','%2','%3','%4','%5','%6','%7','%8')")
            .arg(info.get_room_id()).arg(info.get_room_state()).arg(info.get_room_name())
            .arg(info.get_room_type()).arg(info.get_room_place()).arg(info.get_room_price())
            .arg(info.get_room_discount()).arg(info.get_room_call());

     qDebug()<<CreateRoomInfoString;
     if(!Createquery.exec(CreateRoomInfoString))
     {
        qDebug()<<"CreateRoomInfo error"<<endl;
        return false;
     }
     return true;
}

void DataBaseOperate::UpdateUserType(const QString &ID,const QString &new_type)
{
    QSqlQuery UpdateTypequery;
    QString UpataUserTypeString =
            QString("update user set type_name = '%1' where UID = '%2'").arg(new_type).arg(ID);
    qDebug()<<UpataUserTypeString;
    UpdateTypequery.exec(UpataUserTypeString);
}

void DataBaseOperate::UpdateMealInfo(MealInfo &info)
{
    QSqlQuery UpdateTypequery;
    QString UpdateMealInfo =
            QString("update meal set meal_name = '%1',meal_type = '%2',meal_price = %3 where MEALID = %4")
            .arg(info.getm_mealname()).arg(info.getm_mealtype()).arg(info.getm_mealprice()).arg(info.getm_mealid());

    qDebug()<<UpdateMealInfo;
    if(!UpdateTypequery.exec(UpdateMealInfo))
    {
        qDebug()<<"UpdateMealInfo error"<<endl;
    }
}


RoomInfoList DataBaseOperate::SelectUsingRoomInfo(QString roomtype)
{
    RoomInfoList list;
    QSqlQuery query;
    QString SelectUsingRoomInfoString =
            QString("select * from room where "
                    "(room_type = '%1' and room_state = '使用')").arg(roomtype);
    qDebug()<<"SelectUsingRoomInfoString = "<<SelectUsingRoomInfoString;
    if(query.exec(SelectUsingRoomInfoString))
    {
        int id_idx = query.record().indexOf("RID");
        int state_idx = query.record().indexOf("room_state");
        int name_idx = query.record().indexOf("room_name");
        int type_idx = query.record().indexOf("room_type");
        int place_idx = query.record().indexOf("room_place");
        int price_idx = query.record().indexOf("room_price");
        int discount_idx = query.record().indexOf("room_discount");
        int call_idx = query.record().indexOf("room_call");

        while (query.next())
        {
            QString id = query.value(id_idx).toString();
            QString state = query.value(state_idx).toString();
            QString name = query.value(name_idx).toString();
            QString type = query.value(type_idx).toString();
            QString place = query.value(place_idx).toString();
            QString price = query.value(price_idx).toString();
            QString discount = query.value(discount_idx).toString();
            QString call = query.value(call_idx).toString();

            RoomInfo info(id,state,name,type,place,price,discount,call);
            list.append(info);
            //info.displayinfo();
        }

    }else
    {
        qDebug()<<"SelectUsingRoomInfoString error"<<endl;
    }
    return list;
}



void DataBaseOperate::UpdateUserMessage(const QString &ID,QString const &name,const QString &new_type)
{
    QSqlQuery UpdateUserMessagequery;
    QString UpdateUserMessageString =
            QString("update worker set %1 = '%2' where UID = '%3'").arg(name).arg(new_type).arg(ID);
    qDebug()<<UpdateUserMessageString;
    UpdateUserMessagequery.exec(UpdateUserMessageString);
}

void DataBaseOperate::UpdateBillCheckout(QString &Billid,QString &RID)
{


    QSqlQuery UpdateBillCheckoutquery;
    QString UpdateBillCheckoutString =
            QString("update roombill set c_useingflag = '0' where BILLID = '%1'").arg(Billid);
    QString UpdateRoomState =
            QString("update room set room_state = '空闲' where RID = '%1'").arg(RID);
        qDebug()<<"Billid = "<<UpdateBillCheckoutString<<endl;
        qDebug()<<"RID = "<<UpdateRoomState<<endl;

    if(!UpdateBillCheckoutquery.exec(UpdateBillCheckoutString))
    {
            qDebug()<<"UpdateBillCheckoutquery error"<<endl;
    }
    if(!UpdateBillCheckoutquery.exec(UpdateRoomState))
    {
            qDebug()<<"UpdateRoomState error"<<endl;
    }



}

 bool DataBaseOperate::UpdateRoomInfo(RoomInfo &info)
 {
     QSqlQuery UpdateRoomquery;
     QString UpdateRoomInfo =
             QString("update room set room_name = '%1',room_type = '%2',"
                     "room_place = '%3',room_price = %4,room_discount = '%5',"
                     "room_call = '%6' where RID = %7")
             .arg(info.get_room_name()).arg(info.get_room_type()).arg(info.get_room_place())
             .arg(info.get_room_price()).arg(info.get_room_discount()).arg(info.get_room_call())
             .arg(info.get_room_id());

     qDebug()<<UpdateRoomInfo;
     if(!UpdateRoomquery.exec(UpdateRoomInfo))
     {
         qDebug()<<"UpdateRoomInfo error"<<endl;
         return false;

     }
     return true;

 }
 void DataBaseOperate::UpdateRoomState(QString RID,QString state)
 {
      QSqlQuery UpdateRoomStatequery;

     QString updateRoomStateString =
              QString("update room set room_state = '%1' where RID = '%2'").arg(state)
             .arg(RID);//更新房间状态
      qDebug()<<updateRoomStateString<<endl;
     if(!UpdateRoomStatequery.exec(updateRoomStateString))
     {
         qDebug()<<"UpdateRoomState error"<<endl;
     }

 }

 bool DataBaseOperate::updateCustomerInfo(CustomerInfo &info)
 {
     QSqlQuery UpdateCustomerquery;
     QString updatecustomerInfo =
             QString("update customer set customer_pswd = '%1',customer_name = '%2',"
                     "customer_Sex = '%3',customer_call = %4,customer_idcard = '%5',"
                     "customer_orderflag = '%6',RID = '%7',croom_type = '%8',"
                     "c_ipaddr = '%9',c_port = '%10' where CID = %11")
             .arg(info.getm_pswd()).arg(info.getm_name()).arg(info.getm_Sex())
             .arg(info.getm_Call()).arg(info.getm_idcard()).arg(info.getm_flag())
             .arg(info.getm_RID()).arg(info.getm_roomtype())
             .arg(info.getm_addr()).arg(info.getm_port()).arg(info.getm_cid());
     qDebug()<<updatecustomerInfo;
     if(!UpdateCustomerquery.exec(updatecustomerInfo))
     {
         qDebug()<<"UpdateCustomerquery error"<<endl;
         return false;
     }
     return true;

 }

void DataBaseOperate::DeleteWorkerInfo(const QString &ID)
{
    QSqlQuery DeleteWorkerInfoquery;
    QString  DeleteWorkerInfoString =
            QString("delete from worker where UID = '%1'").arg(ID);
    DeleteWorkerInfoquery.exec(DeleteWorkerInfoString);
    DeleteWorkerInfoString =
            QString("delete from user where UID = '%1'").arg(ID);
     DeleteWorkerInfoquery.exec(DeleteWorkerInfoString);

}

void DataBaseOperate::DeleteMealInfo(const int &MEALID)
{
    QSqlQuery DeleteMealInfoquery;
    QString  DeleteMealInfoString =
            QString("delete from meal where MEALID = %1").arg(MEALID);
    if(!DeleteMealInfoquery.exec(DeleteMealInfoString))
    {
        qDebug()<<"DeleteMealInfo error"<<endl;
    }


}

bool DataBaseOperate::DeleteRoomInfo(QString &RID)
{
    QSqlQuery DeleteRoomInfoquery;
    QString  DeleteRoomInfoString =
            QString("delete from room where RID = '%1'").arg(RID);
    if(!DeleteRoomInfoquery.exec(DeleteRoomInfoString))
    {
        qDebug()<<"DeleteRoomInfo error"<<endl;
        return false;
    }
    return true;
}


QString DataBaseOperate::GetIdnumber()
{
      QString New_ID;
      QSqlQuery GetAllIdQuery;
      QList<int> userIdList;
      int i = 0;
      QString  GetAllIdString =
              QString("select UID from user");
      GetAllIdQuery.exec(GetAllIdString);
      //在exec之后必须执行一下first()或者next()因为exec之后record指针没有在数据上，而是在数据的上面

      while(GetAllIdQuery.next())
      {
          qDebug()<<"id "<<GetAllIdQuery.at()<<" = "<<GetAllIdQuery.value(0).toInt()<<endl;
          userIdList.append(GetAllIdQuery.value(0).toInt());
      }
      int totalnumber =userIdList.size();//总共的用户数量
      int MaxIdnumber = userIdList.last();
      if(totalnumber==MaxIdnumber)
      {
           //qDebug()<<"当前位数"<<this->countbits(MaxIdnumber+1)<<endl;
           QVariant temp = MaxIdnumber+1;
           QString tempstr =temp.toString();
           for(int j = 0;j<4-countbits(MaxIdnumber+1);j++)//id最大为6位数，如果数字是两位数前面就有6-2个0
           {
              New_ID.append('0');
           }
           New_ID = New_ID+tempstr;
           qDebug()<<"New_ID = "<<New_ID<<endl;
           return New_ID;
      }else
      {
          for(i = 0;i<=totalnumber;i++)
          {
             if(userIdList.value(i)!=(i+1))//如果数据库数据都是按照id自增排序的话那么，第0个索引放的是id为1的账户
             {
                 QVariant temp = i+1;
                 QString tempstr =temp.toString();
                 for(int j = 0;j<4-countbits(i+1);j++)//id最大为6位数，如果数字是两位数前面就有6-2个0
                 {
                    New_ID.append('0');
                 }
                 New_ID = New_ID+tempstr;
                 qDebug()<<"New_ID = "<<New_ID<<endl;
                 return New_ID;

             }
          }
      }
}
QString DataBaseOperate::GetRoomIdnumber()
{
    QString New_ID;
    QSqlQuery GetAllIdQuery;
    QList<int> roomIdList;
    int i = 0;
    QString  GetAllIdString =
            QString("select RID from room");
    GetAllIdQuery.exec(GetAllIdString);
    //在exec之后必须执行一下first()或者next()因为exec之后record指针没有在数据上，而是在数据的上面

    while(GetAllIdQuery.next())
    {
        //qDebug()<<"id "<<GetAllIdQuery.at()<<" = "<<GetAllIdQuery.value(0).toInt()<<endl;
        roomIdList.append(GetAllIdQuery.value(0).toInt());
    }
    int totalnumber =roomIdList.size();//总共的用户数量
    int MaxIdnumber = roomIdList.last();
    if(totalnumber==MaxIdnumber)
    {
         //qDebug()<<"当前位数"<<this->countbits(MaxIdnumber+1)<<endl;
         QVariant temp = MaxIdnumber+1;
         QString tempstr =temp.toString();
         for(int j = 0;j<4-countbits(MaxIdnumber+1);j++)//id最大为6位数，如果数字是两位数前面就有6-2个0
         {
            New_ID.append('0');
         }
         New_ID = New_ID+tempstr;
         qDebug()<<"New_ID = "<<New_ID<<endl;
         return New_ID;
    }else
    {
        for(i = 0;i<=totalnumber;i++)
        {
           if(roomIdList.value(i)!=(i+1))//如果数据库数据都是按照id自增排序的话那么，第0个索引放的是id为1的账户
           {
               QVariant temp = i+1;
               QString tempstr =temp.toString();
               for(int j = 0;j<4-countbits(i+1);j++)//id最大为6位数，如果数字是两位数前面就有6-2个0
               {
                  New_ID.append('0');
               }
               New_ID = New_ID+tempstr;
               qDebug()<<"New_ID = "<<New_ID<<endl;
               return New_ID;

           }
        }
    }
}

int DataBaseOperate::countbits(int number)
{
    int count = 0;
    while(number)
    {
        number = number/10;
        count++;
    }
    return count;
}
RoomInfo DataBaseOperate::SelectRoomIDInfo(QString ROOMID)
{

    qDebug()<<"SelectRoomIDInfo"<<endl;
    QSqlQuery query;
    QString queryString;
    queryString = QString("select * from room where RID = '%1'").arg(ROOMID);
    if(!query.exec(queryString))
    {
        qDebug()<<"SelectRoomIDInfo error"<<endl;
    }
    query.exec(queryString);
        int id_idx = query.record().indexOf("RID");
        int state_idx = query.record().indexOf("room_state");
        int name_idx = query.record().indexOf("room_name");
        int type_idx = query.record().indexOf("room_type");
        int place_idx = query.record().indexOf("room_place");
        int price_idx = query.record().indexOf("room_price");
        int discount_idx = query.record().indexOf("room_discount");
        int call_idx = query.record().indexOf("room_call");

        query.next();

        QString id = query.value(id_idx).toString();
        QString state = query.value(state_idx).toString();
        QString name = query.value(name_idx).toString();
        QString type = query.value(type_idx).toString();
        QString place = query.value(place_idx).toString();
        QString price = query.value(price_idx).toString();
        QString discount = query.value(discount_idx).toString();
        QString call = query.value(call_idx).toString();

        RoomInfo info(id,state,name,type,place,price,discount,call);
        return info;
        }
static RoomInfo SelectRoomNameInfo(QString ROOMNAME)
{
    QSqlQuery query;
    QString queryString;
    queryString = QString("select * from room where room_name = '%1'").arg(ROOMNAME);
    if(!query.exec(queryString))
    {
        qDebug()<<"SelectRoomIDInfo error"<<endl;
    }
    query.exec(queryString);
        int id_idx = query.record().indexOf("RID");
        int state_idx = query.record().indexOf("room_state");
        int name_idx = query.record().indexOf("room_name");
        int type_idx = query.record().indexOf("room_type");
        int place_idx = query.record().indexOf("room_place");
        int price_idx = query.record().indexOf("room_price");
        int discount_idx = query.record().indexOf("room_discount");
        int call_idx = query.record().indexOf("room_call");

        query.next();

        QString id = query.value(id_idx).toString();
        QString state = query.value(state_idx).toString();
        QString name = query.value(name_idx).toString();
        QString type = query.value(type_idx).toString();
        QString place = query.value(place_idx).toString();
        QString price = query.value(price_idx).toString();
        QString discount = query.value(discount_idx).toString();
        QString call = query.value(call_idx).toString();

        RoomInfo info(id,state,name,type,place,price,discount,call);
        return info;

}
RoomInfoList DataBaseOperate::SelectRoomInfo(QString roomtype,QString roomfloor)
 {
    RoomInfoList list;

    QSqlQuery query;
    QString queryString;
    QString temp_roomall = "所有";

    if(roomtype == roomfloor)
    {
        queryString = QString("select * from room ");
    }else if(temp_roomall == roomfloor)
    {
        queryString = QString("select * from room where room_type = '%1'").arg(roomtype);
    }else if(temp_roomall ==roomtype)
    {
        queryString = QString("select * from room where room_place = '%1'").arg(roomfloor);
    }else
    {
        queryString = QString("select * from room "
                                      "where room_type = '%1' and room_place = '%2'")
                                       .arg(roomtype).arg(roomfloor);
    }


    qDebug()<<queryString<<endl;

    if(query.exec(queryString))
    {
        int id_idx = query.record().indexOf("RID");
        int state_idx = query.record().indexOf("room_state");
        int name_idx = query.record().indexOf("room_name");
        int type_idx = query.record().indexOf("room_type");
        int place_idx = query.record().indexOf("room_place");
        int price_idx = query.record().indexOf("room_price");
        int discount_idx = query.record().indexOf("room_discount");
        int call_idx = query.record().indexOf("room_call");

        while (query.next())
        {
            QString id = query.value(id_idx).toString();
            QString state = query.value(state_idx).toString();
            QString name = query.value(name_idx).toString();
            QString type = query.value(type_idx).toString();
            QString place = query.value(place_idx).toString();
            QString price = query.value(price_idx).toString();
            QString discount = query.value(discount_idx).toString();
            QString call = query.value(call_idx).toString();

            RoomInfo info(id,state,name,type,place,price,discount,call);
            list.append(info);
            //info.displayinfo();
        }
    }

    return list;


 }
 RoomInfoList  DataBaseOperate::SelectEmptyRoomInfo(QString roomtype)
 {
    RoomInfoList list;
    QSqlQuery query;
    QString queryString;
     if(roomtype == "所有")
     {
         queryString = QString("select * from room where room_state = '空闲'");
     }else
     {
         queryString = QString("select * from room where room_type = '%1' and room_state = '空闲'")
                 .arg(roomtype);
     }

    if(query.exec(queryString))
    {
        int id_idx = query.record().indexOf("RID");
        int state_idx = query.record().indexOf("room_state");
        int name_idx = query.record().indexOf("room_name");
        int type_idx = query.record().indexOf("room_type");
        int place_idx = query.record().indexOf("room_place");
        int price_idx = query.record().indexOf("room_price");
        int discount_idx = query.record().indexOf("room_discount");
        int call_idx = query.record().indexOf("room_call");

        while (query.next())
        {
            QString id = query.value(id_idx).toString();
            QString state = query.value(state_idx).toString();
            QString name = query.value(name_idx).toString();
            QString type = query.value(type_idx).toString();
            QString place = query.value(place_idx).toString();
            QString price = query.value(price_idx).toString();
            QString discount = query.value(discount_idx).toString();
            QString call = query.value(call_idx).toString();

            RoomInfo info(id,state,name,type,place,price,discount,call);
            list.append(info);
            //info.displayinfo();
        }

    }
    return list;
 }

ListBillInfo DataBaseOperate::SelectUsingBillInfo(QString roomtype)
{
    ListBillInfo list;
    QSqlQuery query;
    QString queryString;

    queryString = QString("select * from roombill where c_useingflag = '1' and RID in "
                          "(select RID from room where room_state = '使用' and room_type = '%1')")
                  .arg(roomtype);

    if(query.exec(queryString))
    {
        int billid_idx = query.record().indexOf("BILLID");
        int roomid_idx = query.record().indexOf("RID");
        int userid_idx = query.record().indexOf("UID");
        int usingflag_idx = query.record().indexOf("c_useingflag");
        int payid_idx = query.record().indexOf("c_payid");
        int idcard_idx = query.record().indexOf("c_idcard");
        int name_idx = query.record().indexOf("c_name");
        int sex_idx = query.record().indexOf("c_sex");
        int call_idx = query.record().indexOf("c_call");
        int day_idx = query.record().indexOf("c_day");
        int timebegin_idx = query.record().indexOf("c_timebegin");
        int timeend_idx = query.record().indexOf("c_timeend");
        int cash_idx = query.record().indexOf("c_cash");
        int pledge_idx = query.record().indexOf("c_pledge");
        int mealflag_idx = query.record().indexOf("c_mealflag");
        int mealbill_idx = query.record().indexOf("c_mealbill");
        int mealcash_idx = query.record().indexOf("c_mealcash");
        while(query.next())
        {
        QString billid = query.value(billid_idx).toString();
        QString roomid = query.value(roomid_idx).toString();
        QString useingflag = query.value(usingflag_idx).toString();
        QString userid = query.value(userid_idx).toString();
        int payid = query.value(payid_idx).toInt();
        QString idcard = query.value(idcard_idx).toString();
        QString name = query.value(name_idx).toString();
        QString sex = query.value(sex_idx).toString();
        QString call = query.value(call_idx).toString();
        int day = query.value(day_idx).toInt();
        QString timebegin = query.value(timebegin_idx).toString();
        QString timeend = query.value(timeend_idx).toString();
        int cash = query.value(cash_idx).toInt();
        int pledge = query.value(pledge_idx).toInt();
        QString mealflag = query.value(mealflag_idx).toString();
        QString mealbill = query.value(mealbill_idx).toString();
        QString mealcash = query.value(mealcash_idx).toString();

        BillInfo info(billid,roomid,userid,useingflag,payid,idcard,name,sex,call
                      ,day,timebegin,timeend,cash,pledge,mealflag,mealbill,mealcash);
        list.append(info);
        }
        return list;

    }else
    {
        qDebug()<<"error SelectUsingBillInfo"<<endl;
        return list;
    }

}
 ListBillInfo DataBaseOperate::SelectBillInfo(QString RID)
 {

     ListBillInfo list;
     QSqlQuery query;
     QString queryString;
     if(RID == ALL_BILL)
     {
        queryString = QString("select *from roombill");
     }else if(RID == USING_BILL)
     {
        queryString = QString("select * from roombill where c_useingflag = '1'");
     }else
     {
        queryString = QString("select * from roombill where RID = '%1' and c_useingflag = '1'")
                      .arg(RID);
     }


     if(query.exec(queryString))
     {
         int billid_idx = query.record().indexOf("BILLID");
         int roomid_idx = query.record().indexOf("RID");
         int userid_idx = query.record().indexOf("UID");
         int usingflag_idx = query.record().indexOf("c_useingflag");
         int payid_idx = query.record().indexOf("c_payid");
         int idcard_idx = query.record().indexOf("c_idcard");
         int name_idx = query.record().indexOf("c_name");
         int sex_idx = query.record().indexOf("c_sex");
         int call_idx = query.record().indexOf("c_call");
         int day_idx = query.record().indexOf("c_day");
         int timebegin_idx = query.record().indexOf("c_timebegin");
         int timeend_idx = query.record().indexOf("c_timeend");
         int cash_idx = query.record().indexOf("c_cash");
         int pledge_idx = query.record().indexOf("c_pledge");
         int mealflag_idx = query.record().indexOf("c_mealflag");
         int mealbill_idx = query.record().indexOf("c_mealbill");
         int mealcash_idx = query.record().indexOf("c_mealcash");
         while(query.next())
         {
         QString billid = query.value(billid_idx).toString();
         QString roomid = query.value(roomid_idx).toString();
         QString useingflag = query.value(usingflag_idx).toString();
         QString userid = query.value(userid_idx).toString();
         int payid = query.value(payid_idx).toInt();
         QString idcard = query.value(idcard_idx).toString();
         QString name = query.value(name_idx).toString();
         QString sex = query.value(sex_idx).toString();
         QString call = query.value(call_idx).toString();
         int day = query.value(day_idx).toInt();
         QString timebegin = query.value(timebegin_idx).toString();
         QString timeend = query.value(timeend_idx).toString();
         int cash = query.value(cash_idx).toInt();
         int pledge = query.value(pledge_idx).toInt();
         QString mealflag = query.value(mealflag_idx).toString();
         QString mealbill = query.value(mealbill_idx).toString();
         QString mealcash = query.value(mealcash_idx).toString();

         BillInfo info(billid,roomid,userid,useingflag,payid,idcard,name,sex,call
                       ,day,timebegin,timeend,cash,pledge,mealflag,mealbill,mealcash);
         list.append(info);
         }
         return list;

     }else
     {
         qDebug()<<"error SelectBillRoomInfo"<<endl;
         return list;
     }
 }

 ListBillInfo DataBaseOperate::SelectHistoryInfo(QString date)
 {
     ListBillInfo list;
     QSqlQuery query;
     QString queryString;

     queryString = QString("select * from roombill where c_useingflag = '0' and BILLID like '%1%'").arg(date);
    qDebug()<<queryString<<endl;
     if(query.exec(queryString))
     {
         int billid_idx = query.record().indexOf("BILLID");
         int roomid_idx = query.record().indexOf("RID");
         int userid_idx = query.record().indexOf("UID");
         int usingflag_idx = query.record().indexOf("c_useingflag");
         int payid_idx = query.record().indexOf("c_payid");
         int idcard_idx = query.record().indexOf("c_idcard");
         int name_idx = query.record().indexOf("c_name");
         int sex_idx = query.record().indexOf("c_sex");
         int call_idx = query.record().indexOf("c_call");
         int day_idx = query.record().indexOf("c_day");
         int timebegin_idx = query.record().indexOf("c_timebegin");
         int timeend_idx = query.record().indexOf("c_timeend");
         int cash_idx = query.record().indexOf("c_cash");
         int pledge_idx = query.record().indexOf("c_pledge");
         int mealflag_idx = query.record().indexOf("c_mealflag");
         int mealbill_idx = query.record().indexOf("c_mealbill");
         int mealcash_idx = query.record().indexOf("c_mealcash");
         while(query.next())
         {
         QString billid = query.value(billid_idx).toString();
         QString roomid = query.value(roomid_idx).toString();
         QString useingflag = query.value(usingflag_idx).toString();
         QString userid = query.value(userid_idx).toString();
         int payid = query.value(payid_idx).toInt();
         QString idcard = query.value(idcard_idx).toString();
         QString name = query.value(name_idx).toString();
         QString sex = query.value(sex_idx).toString();
         QString call = query.value(call_idx).toString();
         int day = query.value(day_idx).toInt();
         QString timebegin = query.value(timebegin_idx).toString();
         QString timeend = query.value(timeend_idx).toString();
         int cash = query.value(cash_idx).toInt();
         int pledge = query.value(pledge_idx).toInt();
         QString mealflag = query.value(mealflag_idx).toString();
         QString mealbill = query.value(mealbill_idx).toString();
         QString mealcash = query.value(mealcash_idx).toString();

         BillInfo info(billid,roomid,userid,useingflag,payid,idcard,name,sex,call
                       ,day,timebegin,timeend,cash,pledge,mealflag,mealbill,mealcash);
         list.append(info);
         }
         return list;

     }else
     {
         qDebug()<<"error SelectBillRoomInfo"<<endl;
         return list;
     }
 }
  QString DataBaseOperate::GetRecentday()
 {
      QSqlQuery query;
      QString queryString = QString("select MAX(DAYID) from income");
      if(query.exec(queryString))
      {
         int id_idx = query.record().indexOf("MAX(DAYID)");

         query.next();
         QString id = query.value(id_idx).toString();
        // qDebug()<<"id =  ;= "<<id<<"id_idx ="<<id_idx<<endl;
         QStringList strlist;
         strlist =id.split("-");
         QString day = strlist.at(2);
        // qDebug()<<"day =  "<<day<<endl;
         return day;
      }else
      {
          qDebug()<<"null"<<endl;
          return QString("null");
      }
 }
  void DataBaseOperate::CreateIncomeInfo(QString const &dayid)
  {
      QSqlQuery query;
      QString queryString =
              QString("insert into income values('%1',0)").arg(dayid);
      qDebug()<<queryString<<endl;
      if(!query.exec(queryString))
      {
         qDebug()<<"insert error"<<endl;
      }
  }
int DataBaseOperate::GetTodayPayid()
 {
    QSqlQuery query;
    QString queryString =
            QString("select * from payid");
    if(!query.exec(queryString))
    {
       qDebug()<<"pay error"<<endl;
       return 0;
    }else
    {
      int id_idx = query.record().indexOf("MPAYID");
      query.next();
      QString id = query.value(id_idx).toString();
      qDebug()<<"MPAYID = "<<id<<endl;
      int todaypayid = id.toInt()+1;
      queryString = QString("update payid set MPAYID = %1").arg(todaypayid);
      if(!query.exec(queryString))
      {
         qDebug()<<"update payid error"<<endl;
         return 0;
      }
      return todaypayid;
    }
 }
int DataBaseOperate::GetPayid()
{
    QSqlQuery query;
    QString queryString =
            QString("select * from payid");
    query.exec(queryString);
    int id_idx = query.record().indexOf("MPAYID");
    query.next();
    QString id = query.value(id_idx).toString();
    qDebug()<<"MPAYID = "<<id<<endl;
    int todaypayid = id.toInt()+1;
    return todaypayid;
}
 void DataBaseOperate::ResetPayID()
 {
     QSqlQuery query;
     QString queryString =
             QString("update payid set MPAYID = 0");
     if(!query.exec(queryString))
     {
        qDebug()<<"reset error"<<endl;
     }
 }
 void DataBaseOperate::CreateBillInfo(BillInfo &info)
 {

     QSqlQuery query;
/***************************************************************************************/
     QString CreateBillqueryString =
     QString("insert into roombill values ('%1','%2','%3','%4',%5,"
             "'%6','%7','%8','%9',%10,'%11',"
             "'%12',%13,%14,'%15','%16','%17')").arg(info.getm_BILLID())
             .arg(info.getm_RID()).arg(info.getm_UID()).arg(info.getm_usingfalg()).arg(info.getm_payid())
             .arg(info.getm_idcard()).arg(info.getm_name()).arg(info.getm_sex())
             .arg(info.getm_call()).arg(info.getm_day()).arg(info.getm_timebegin())
             .arg(info.getm_timeend()).arg(info.getm_cash()).arg(info.getm_pledge())
             .arg(info.getm_mealflag()).arg(info.getm_mealbill())
             .arg(info.getm_mealcash());//更新bill信息
/***************************************************************************************/
      qDebug()<<CreateBillqueryString<<endl;
      QString updateRoomqueryString =
               QString("update room set room_state = '使用' where RID = '%1'")
              .arg(info.getm_RID());//更新房间状态
/***************************************************************************************/

     QString getTodayID =
             QString("select MAX(DAYID) from income");
     query.exec(getTodayID);
     int id_index = query.record().indexOf("MAX(DAYID)");
     query.next();
     QString myid = query.value(id_index).toString();
     QString updateIncomequeryString =
             QString("update income set daily_income = daily_income + %1 where DAYID = '%2'")
             .arg(info.getm_cash()).arg(myid);
     qDebug()<<updateIncomequeryString<<endl;


/***************************************************************************************/
     if(!query.exec(CreateBillqueryString))//添加信息到bill表中
     {
         qDebug()<<"CreateBillqueryString error"<<endl;
     }
     query.exec(updateRoomqueryString);//使房间状态变为使用
     query.exec(updateIncomequeryString);//更新当月收入

 }

ListMealInfo DataBaseOperate::SelectMealInfo(QString type)
 {
     ListMealInfo list;
     QSqlQuery query;
     QString queryString;
     if(type == ALL_MEAL)
     {
         queryString = QString("select * from meal");
     }else
     {
         queryString = QString("select * from meal where meal_type = '%1'").arg(type);
     }

     if(query.exec(queryString))
     {
         int id_idx = query.record().indexOf("MEALID");
         int name_idx = query.record().indexOf("meal_name");
         int type_idx = query.record().indexOf("meal_type");
         int price_idx = query.record().indexOf("meal_price");

         while (query.next())
         {
             int id = query.value(id_idx).toInt();
             QString name = query.value(name_idx).toString();
             QString type = query.value(type_idx).toString();
             QString price = query.value(price_idx).toString();

             MealInfo info(id,name,type,price);
             list.append(info);
         }

     }
     return list;
 }
ListCustomerInfo  DataBaseOperate::SelectCustomerInfo(QString cid)
{
    ListCustomerInfo list;
    QSqlQuery query;

    QString queryString;
    if(cid == ALL_CUSTOMER)
    {
        queryString = QString("select * from customer");
    }else
    {
        queryString = QString("select * from customer where CID = '%1'").arg(cid);
    }
    if(query.exec(queryString))
    {
        int id_idx = query.record().indexOf("CID");
        int psswd_idx = query.record().indexOf("customer_pswd");
        int name_idx = query.record().indexOf("customer_name");
        int sex_idx = query.record().indexOf("customer_Sex");
        int call_idx = query.record().indexOf("customer_call");
        int idcard_idx = query.record().indexOf("customer_idcard");
        int orderflag_idx = query.record().indexOf("customer_orderflag");
        int RID_idx = query.record().indexOf("RID");
        int roomtype_idx = query.record().indexOf("croom_type");
        int add_idx = query.record().indexOf("c_ipaddr");
        int port_idx = query.record().indexOf("c_port");


        while (query.next())
        {

            QString id = query.value(id_idx).toString();
            QString psswd = query.value(psswd_idx).toString();
            QString name = query.value(name_idx).toString();
            QString sex = query.value(sex_idx).toString();
            QString call = query.value(call_idx).toString();
            QString idcard = query.value(idcard_idx).toString();
            QString orderflag = query.value(orderflag_idx).toString();
            QString RID = query.value(RID_idx).toString();
            QString room_type = query.value(roomtype_idx).toString();
            QString add = query.value(add_idx).toString();
            QString port = query.value(port_idx).toString();
            CustomerInfo info(id,psswd,name,sex,call,idcard,orderflag,RID,room_type,add,port);
            list.append(info);
        }

        return list;
    }
    else{
          qDebug()<<"SelectCustomerInfo error"<<endl;
          return list;
        }
}
MealInfo DataBaseOperate::SelectMealInfo(int ID)
{
    QSqlQuery query;
    MealInfo info;
    QString queryString;
    queryString = QString("select * from meal where MEALID = '%1'").arg(ID);
    if(query.exec(queryString))
    {
        int id_idx = query.record().indexOf("MEALID");
        int name_idx = query.record().indexOf("meal_name");
        int type_idx = query.record().indexOf("meal_type");
        int price_idx = query.record().indexOf("meal_price");

        while (query.next())
        {
            int id = query.value(id_idx).toInt();
            QString name = query.value(name_idx).toString();
            QString type = query.value(type_idx).toString();
            QString price = query.value(price_idx).toString();
            info.setm_mealid(id);
            info.setm_mealname(name);
            info.setm_mealtype(type);
            info.setm_mealprice(price);
              //qDebug()<<"database "<<id<<name<<type<<price<<endl;
        }

        return info;
    }
    else{
          qDebug()<<"SelectMealInfoerror"<<endl;
          return info;
         }
}
void DataBaseOperate::UpdateBillMeal(BillInfo &info)
{

//先将旧信息（例如前几次点的餐）
    QString oldRID = info.getm_RID();
    GlobalVar::m_billInfoList.clear();
    GlobalVar::m_billInfoList = SelectBillInfo(oldRID);
    BillInfo oldmeal =  GlobalVar::m_billInfoList[0];
    QString oldcash = oldmeal.getm_mealcash();
    QString oldmealbill = oldmeal.getm_mealbill();

    oldmealbill = oldmealbill + info.getm_mealbill();
    int oldcashint = oldcash.toInt() + info.getm_mealcash().toInt();
    QVariant voldcashint = oldcashint;
    int intnewincome = info.getm_mealcash().toInt();
    DataBaseOperate::UpdateIncome(intnewincome);//更新新加入的收入
/***************************************************************************************/
    QSqlQuery query;
    QString StringUpdateBillMessage =
    QString("update roombill set c_mealflag = '%1',c_mealbill = '%2',c_mealcash = '%3'"
            "where BILLID = '%4'")
            .arg(info.getm_mealflag()).arg(oldmealbill)
            .arg(voldcashint.toString()).arg(info.getm_BILLID());//更新bill信息
     qDebug()<<StringUpdateBillMessage<<endl;
/***************************************************************************************/
     if(!query.exec(StringUpdateBillMessage))//添加信息到bill表中
     {
         qDebug()<<"StringUpdateBillMessage error"<<endl;
     }
}

void DataBaseOperate::UpdateIncome(int &money)
{

     QSqlQuery query;
    QString getTodayID =
            QString("select MAX(DAYID) from income");
    query.exec(getTodayID);
    int id_index = query.record().indexOf("MAX(DAYID)");
    query.next();
    QString myid = query.value(id_index).toString();
    QString updateIncomequeryString =
            QString("update income set daily_income = daily_income + %1 where DAYID = '%2'")
            .arg(money).arg(myid);
    qDebug()<<"updateIncomequeryString"<<updateIncomequeryString<<endl;
    query.exec(updateIncomequeryString);//更新当月收入
}
 QList<int> DataBaseOperate::SelectIncomeInfo(QString type,QString data)
 {
     QList<int> list;
     QSqlQuery query;
     QString queryString;
     if(type == YEAR)//某年12个月
     {

              QVariant vtemp;
             for(int i = 1;i <= 12;i++)//一年肯定有12个月
             {
                //qDebug()<<"year mouth = "<<i<<endl;
                vtemp = i;
                QString temp_str;
                if(i<=9)
                {
                    temp_str = "-0"+vtemp.toString();//+月
                }else
                {
                    temp_str = "-"+vtemp.toString();
                }

                queryString = QString("select * from income where DAYID like '%1%2%'")
                        .arg(data).arg(temp_str);
                //qDebug()<<"queryStringdayyear = "<<queryString<<endl;
                 query.record().clear();//清除上一次的记录
                if(query.exec(queryString))
                {

                    int count_mouth = 0;

                    if(query.record().count() != 0)//判断记录是否为空
                    {

                        while(query.next())
                        {
                            int idx_income = query.record().indexOf("daily_income");
                            int incomedaty = query.value(idx_income).toInt();
                            count_mouth += incomedaty;//计算当月的和
                            //qDebug()<<"incomedaty = "<<incomedaty<<endl;
                        }
                    }
                   // qDebug()<<i<<":"<<count_mouth<<endl;
                    list.append(count_mouth);
                }


            }
            return list;
     }else if(type == MOUTH)//传输格式为 eg:2019-03
     {

         QString str_date = data+"-01";
         QDate date =  QDate::fromString(str_date,"yyyy-MM-dd");

         int days = date.daysInMonth();//判断这个月有几天
         qDebug()<<"data = "<<data<<"days = "<<days<<"date.toString() = "<<date.toString()<<endl;
         QVariant vtemp;
         for(int i = 1;i<=days;i++)
         {
              vtemp = i;
              QString  temp_str;
              if(i <= 9)
              {
                 temp_str = "-0" + vtemp.toString();
              }else
              {
                 temp_str = "-" + vtemp.toString();
              }
               if(query.record().count() != 0)
               {
                    query.record().clear();//清除上一次的记录
               }

             queryString = QString("select * from income where DAYID = '%1%2'")
                     .arg(data).arg(temp_str);
             //qDebug()<<"queryString day= "<<queryString<<"   days = "<<days<<endl;
             int temp_day = 0;
             if(query.exec(queryString))
             {

                 if(query.record().count() != 0)//判断记录是否为空
                 {
                     while(query.next())
                     {
                         int idx_income = query.record().indexOf("daily_income");
                         int incomedaty = query.value(idx_income).toInt();
                         temp_day = incomedaty;
                         qDebug()<<"temp_day = "<<temp_day<<endl;
                     }

                 }
             }else
             {
                  qDebug()<<"queryString day error"<<endl;
             }

             list.append(temp_day);
         }
         return list;
     }

 }


 QString DataBaseOperate::SelectNewMealID()
 {
     QString New_ID;
     QSqlQuery GetAllIdQuery;
     QList<int> MealIdList;
     int i = 0;
     QString  GetAllIdString =
             QString("select MEALID from meal");
     GetAllIdQuery.exec(GetAllIdString);
     //在exec之后必须执行一下first()或者next()因为exec之后record指针没有在数据上，而是在数据的上面

     while(GetAllIdQuery.next())
     {
         //qDebug()<<"id "<<GetAllIdQuery.at()<<" = "<<GetAllIdQuery.value(0).toInt()<<endl;
         MealIdList.append(GetAllIdQuery.value(0).toInt());
     }
     int totalnumber =MealIdList.size();//总共的用户数量
     int MaxIdnumber = MealIdList.last();
     if(totalnumber==MaxIdnumber)
     {
          //qDebug()<<"当前位数"<<this->countbits(MaxIdnumber+1)<<endl;
          QVariant temp = MaxIdnumber+1;
          QString tempstr =temp.toString();
          New_ID = New_ID+tempstr;
          qDebug()<<"New_MEALID = "<<New_ID<<endl;
          return New_ID;
     }else
     {
         for(i = 0;i<=totalnumber;i++)
         {
            if(MealIdList.value(i)!=(i+1))//如果数据库数据都是按照id自增排序的话那么，第0个索引放的是id为1的账户
            {
                QVariant temp = i+1;
                QString tempstr =temp.toString();
                New_ID = New_ID+tempstr;
                qDebug()<<"New_MEALID UNconstant = "<<New_ID<<endl;
                return New_ID;
            }
         }
     }
 }


void DataBaseOperate::ClearAllBookCustomer()
{
    QSqlQuery clearQuery;
    QString clearString = QString("update room set room_state = '空闲' where room_state = '预定'");
    qDebug()<<clearString<<endl;
    if(clearQuery.exec(clearString))
    {
        clearString = QString("update customer set RID = ' ',customer_orderflag = '0',croom_type = ''");
        clearQuery.exec(clearString);
    }else
    {
        qDebug()<<"ClearAllBookCustomer error"<<endl;
    }
}

void DataBaseOperate::ClearOneBookCustomer(QString cid)
{
    QSqlQuery clearQuery;
    QString clearString = QString("update customer set RID = ' ',customer_orderflag = '0',croom_type = '' where "
                                  "CID = '%1'").arg(cid);
    qDebug()<<clearString<<endl;
    if(!clearQuery.exec(clearString))
    {
        qDebug()<<"ClearOneBookCustomer error "<<endl;
    }
}

 int DataBaseOperate::countRoomNumber(QString type)
 {
     int num = 0;
     QSqlQuery query;
     QString queryString;
      if(type == EMPTY)
      {
          QString data = "空闲";
          queryString = QString("select COUNT(*) from room where room_state = '%1' ").arg(data);
      }else if(type == FULL)
      {
          queryString = QString("select COUNT(*) from room where room_state = '使用' or room_state = '预定'");
      }
      if(query.exec(queryString))
      {
          int count_index = query.record().indexOf("COUNT(*)");
          while(query.next())
          {
              int count = query.value(count_index).toInt();
              qDebug()<<queryString<<"countnumber = "<<count<<endl;
              num = count;
          }

      }else
      {
          qDebug()<<"countnumber error "<<endl;
      }
      return num;
 }

 QStringList DataBaseOperate::SelectCustomerInRoom(QString type,QString message)
 {
    QStringList list;
    QSqlQuery query;
    QString queryString;
    if(type == CUSTOMER_NAME)
    {
        queryString = QString("select room_name,room_call,c_name from "
                              "(roombill natural join room) "
                              "where c_useingflag = '1' and c_name = '%1'").arg(message);
         qDebug()<<queryString<<endl;

    }else if(type == CUSTOMER_IDCARD)
    {
        queryString =  QString("select RID,c_name,c_call from roombill"
                       "where c_useingflag = '1' and c_idcard = '%1'").arg(message);
        qDebug()<<queryString<<endl;
    }
    if(query.exec(queryString))
    {
        while(query.next())
        {
            int rname_idx = query.record().indexOf("room_name");
            int name_idx = query.record().indexOf("c_name");
            int call_idx = query.record().indexOf("room_call");
            QString rid = query.value(rname_idx).toString();
            QString name = query.value(name_idx).toString();
            QString call = query.value(call_idx).toString();
            QString info = name + ":" + " 房间id :" + rid + " call:" + call;
            list.append(info);
        }
    }
    return list;
 }



