#include "roomdetail.h"
#include "ui_roomdetail.h"
#include <QPixmap>
#include <QSize>
#include <QMainWindow>
#include <QDebug>
#include "ccashieroperate.h"

RoomDetail::RoomDetail(RoomInfo room_info,QWidget *parent) :
    m_room_info(room_info),
    QWidget(parent),
    ui(new Ui::RoomDetail)
{
   ui->setupUi(this);
   //this->setMouseTracking(true);
  // oldstylesheet = this->styleSheet();
   //newstylesheet = "color:rgb(255, 255, 0);background:rgb(153,153,153)";
   ui->label_roomword->setText(m_room_info.get_room_name());
   connect(this,SIGNAL(signalshowbillmessage(RoomInfo)),
           ((CCashierOperate *)this->parent()->parent()->parent()->parent()),
           SLOT(SlotShowbillMessage(RoomInfo)));
}

 void RoomDetail::setPic(QString picload)
 {
     QSize picSize(151,121);
     ui->label_roompic->setPixmap(QPixmap(picload).scaled(picSize,Qt::KeepAspectRatio));//保持比例
      ui->label_roompic->setAlignment(Qt::AlignHCenter);
 }

RoomDetail::~RoomDetail()
{
    delete ui;
}
void RoomDetail::mousePressEvent(QMouseEvent * event)
{
    if(event->button()==Qt::LeftButton)
    {

       emit signalshowbillmessage(m_room_info);
       // qDebug()<<"left button clicked"<<endl;

    }
    QWidget::mousePressEvent(event);
}
void RoomDetail::enterEvent(QEvent *event)
{
     QString data = m_room_info.get_room_id()+":"+m_room_info.get_room_state();
    //this->setStyleSheet(newstylesheet);
    ui->label_roomword->setText(data);
    //qDebug()<<"mouseEnterEvent"<<endl;
    QWidget::enterEvent(event);
}
void  RoomDetail::leaveEvent(QEvent  *event)
{
     this->setStyleSheet(oldstylesheet);
     ui->label_roomword->setText(m_room_info.get_room_name());
     QWidget::leaveEvent(event);
}
QString& RoomDetail::GetRoomState()
 {
    m_room_info.get_room_state();
 }




