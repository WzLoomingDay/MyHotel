#ifndef HOTELMANGEMENT_H
#define HOTELMANGEMENT_H

#include <QWidget>
#include<QMessageBox>
#include <QEvent>
#include "ccashieroperate.h"
#include "mangeroperate.h"
#include "databaseoperate.h"
#include "userinfo.h"
namespace Ui {
class HotelMangement;
}

class HotelMangement : public QWidget
{
    Q_OBJECT

public:
    explicit HotelMangement(QWidget *parent = 0);
    ~HotelMangement();
signals:
    void SignalCashierLogin(QString UID);
    void SignalMangerLogin(QString UID);
private slots:
    bool eventFilter(QObject *, QEvent *);
    void on_pushButton_cashier_clicked();

    void on_pushButton_manger_clicked();

private:
    Ui::HotelMangement *ui;
    MangerOperate* PointertoManger;
    CCashierOperate* PointertoCashier;
};

#endif // HOTELMANGEMENT_H
