#include "database.h"

DataBase::DataBase()
{
}
DataBase::~DataBase()
{
    CloseDataBase();
}
void DataBase::CloseDataBase()
{
    QSqlDatabase::database().close();
    qDebug() << "We have closed DataBse"<<endl;
}
int DataBase::DataBase_Connect()
{
    qDebug() << "We are building connect DataBase~"<<endl;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");//用来选择连接的数据库类型
    db.setHostName("localhost");//选择服务器地址
    db.setDatabaseName("foodmanger");//数据库名字
    db.setUserName("root");//账号
    db.setPassword("123456");//密码
    if(db.open())
    {
        qDebug() << "Success: Connect MySQL!!";
        return 0;
    }else
    {
       QString tips = "ERROR: Can't Open MySQL DataBase named "+db.databaseName();
        QString name = "数据库错误";
        QMessageBox::information(this,name,tips,0x00000400);
        return 1;
    }

}

