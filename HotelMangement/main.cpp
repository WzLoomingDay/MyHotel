#include "header.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CDataBase m_DataBase;
    m_DataBase.DataBaseConnect();

    HotelMangement w;
    w.show();

    return a.exec();
}
