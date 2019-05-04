#ifndef BOOKINGWIDGET_H
#define BOOKINGWIDGET_H

#include <QWidget>
#include "customerinfo.h"
namespace Ui {
class BookingWidget;
}

class BookingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookingWidget(QWidget *parent = 0);
    void ShowBookingWidget(CustomerInfo info);
    ~BookingWidget();

signals:
    void signalBooking(QStringList list);


private slots:
    void on_PB_Booking_clicked();

private:
    Ui::BookingWidget *ui;
    CustomerInfo m_info;
};

#endif // BOOKINGWIDGET_H
