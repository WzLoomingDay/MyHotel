#include "bookingwidget.h"
#include "ui_bookingwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
BookingWidget::BookingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookingWidget)
{
    ui->setupUi(this);
    QStringList list;
    list<<"标准单人间"<<"标准双人间"<<"商务单人间"<<"豪华双人间"<<"总统套房"<<"家庭套间";
    ui->CB_roomtype->addItems(list);
    qDebug()<<"*this =  "<<this<<endl;
}

BookingWidget::~BookingWidget()
{
    qDebug()<<"BookingWidget::~BookingWidget()"<<endl;
    delete ui;
}

void BookingWidget::ShowBookingWidget(CustomerInfo info)
{
    ui->PB_Booking->setEnabled(true);
    m_info = info;
    qDebug()<<"BookingWidget::ShowBookingWidget(CustomerInfo info)"<<endl;
    this->show();
    if(info.getm_flag()==BOOKING_NO)//未提交预定
    {
         ui->PB_Booking->setEnabled(true);
         ui->PB_Booking->setText("预定");
        ui->lineEdit_state->setText("未预定");
        ui->lineEdit_room->setText("");
    }else if(info.getm_flag()==BOOKING_SUCCESS)//成功预定
    {
        ui->lineEdit_state->setText("成功预定");
        ui->PB_Booking->setText("成功预定");
        ui->PB_Booking->setEnabled(false);

        ui->lineEdit_room->setText(info.getm_RID());
    }else if(info.getm_flag() == BOOKING_WAIT)//等待预定反馈
    {
        ui->lineEdit_state->setText("等待反馈");
         ui->PB_Booking->setEnabled(false);

        ui->lineEdit_room->setText("");

    }
    ui->LineEdit_id->setText(info.getm_cid());
    ui->lineEdit_name->setText(info.getm_name());
    ui->lineEdit_sex->setText(info.getm_Sex());
    ui->lineEdit_idcard->setText(info.getm_idcard());
    ui->lineEdit_call->setText(info.getm_Call());

   // qDebug()<<"info getm_flag = "<<info.getm_flag()<<endl;
    //qDebug()<<"info getm_RID = "<<info.getm_RID()<<endl;
}

void BookingWidget::on_PB_Booking_clicked()//发送id+请求（预定/取消预定）
{
        if(ui->PB_Booking->text()=="预定")
        {

            ui->PB_Booking->setEnabled(false);
            QStringList list;
            list.append(m_info.getm_cid());
            list.append(ui->PB_Booking->text());
            list.append(ui->CB_roomtype->currentText());
            emit signalBooking(list);
            ui->PB_Booking->setText("等待反馈");
        }
}
