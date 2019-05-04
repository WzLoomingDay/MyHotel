#ifndef CDATABASE_H
#define CDATABASE_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QString>
class CDataBase
{
public:
    CDataBase();
    ~CDataBase();
    bool DataBaseConnect();
};

#endif // CDATABASE_H
