#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <QWidget>
#include <databaseoperate.h>
#include <QListWidgetItem>
#include "globalvar.h"
#include "checkoutlist.h"

namespace Ui {
class CheckOut;
}

class CheckOut : public QWidget
{
    Q_OBJECT

public:
    ~CheckOut();
    void closeEvent(QCloseEvent *event = nullptr);

    static CheckOut * getCheckOut();
signals:
    void signalUpdateCheckWidget(QString roomtype);
private slots:
    void slotShowCheckOut(QString user);
    void SlotIndexChanged(QString data);
    void slotUpdateInfo(QString sender,QString roomtype);
    void on_pb_back_clicked();

private:
    QListWidgetItem *m_listwidget;
    CheckOutList * m_CheckoutItem;
    Ui::CheckOut *ui;
    explicit CheckOut(QWidget *parent = 0);
    static CheckOut * m_checkout;

};

#endif // CHECKOUT_H
