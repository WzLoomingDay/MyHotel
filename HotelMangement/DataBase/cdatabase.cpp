#include "cdatabase.h"

CDataBase::CDataBase()
{

}

CDataBase::~CDataBase()
{

}
 bool CDataBase::DataBaseConnect()
 {
         qDebug() << "We are building connect DataBase~"<<endl;
         QSqlDatabase db;
         db = QSqlDatabase::addDatabase("QMYSQL");//用来选择连接的数据库类型
         db.setHostName("localhost");//选择服务器地址
         db.setDatabaseName("hotelmangement");//数据库名字
         db.setUserName("root");//账号
         db.setPassword("123456");//密码
         if(db.open())
         {
             qDebug() << "Success: Connect MySQL!!";
             return true;
         }else
         {
             qCritical("Can't open database: %s(%s)",
                       db.lastError().text().toLocal8Bit().data(),
                       qt_error_string().toLocal8Bit().data());
            return false;
         }
 }
