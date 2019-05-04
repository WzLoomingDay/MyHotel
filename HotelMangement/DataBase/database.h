#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>


class DataBase:public QWidget
{
public:
    DataBase();
    ~DataBase();
    int DataBase_Connect();
    void CloseDataBase();

};

#endif // DATABASE_H
