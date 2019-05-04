#include "signallistitem.h"
#include <QPixmap>
#include <signalcustomer.h>
SignalListItem::SignalListItem(QWidget *parent):QWidget(parent)

{
   m_layout = new QHBoxLayout(this);
    //"房间名字"<< "房间楼层" << "房间价格"<<"房间折扣";
   m_room_pic = new QLabel(this);
   m_room_name = new QLabel(this);
   m_room_floor = new QLabel(this);
   m_room_price = new QLabel(this);
   m_room_discount = new QLabel(this);
   m_pushbutton = new QPushButton("选择",this);//可以添加图片
   m_layout->addWidget(m_room_pic);
   m_layout->addWidget(m_room_name);
   m_layout->addWidget(m_room_floor);
   m_layout->addWidget(m_room_price);
   m_layout->addWidget(m_room_discount);
   m_layout->addWidget(m_pushbutton);
   this->setLayout(m_layout);

  // connect(m_pushbutton,SIGNAL(clicked(bool)),
    //       (SignalCustomer *)(this->parent()->parent()),SLOT(slotSetSelectedRoom()));
   connect(m_pushbutton,SIGNAL(clicked(bool)),
           this,SLOT(slotSendRoomName()));
  // m_grandfather = (SignalCustomer *)(this->parent()->parent());


}
SignalListItem::~SignalListItem()
{
    delete m_layout;
    delete m_room_pic;
    delete m_room_name;
    delete m_room_floor;
    delete m_room_price;
    delete m_room_discount;
    delete m_pushbutton;

}
void SignalListItem::SetMessage(QString room_id,QString room_name,QString room_floor,
                 QString room_price,QString room_discount)
{
        m_room_id = room_id;
        m_room_name->setText(room_name);
        m_room_floor->setText(room_floor);
        m_room_price->setText(room_price);
        m_room_discount->setText(room_discount);
}
void SignalListItem::slotSendRoomName()
{
    QString name = m_room_name->text();
    connect(this,SIGNAL(signalSendName(QString,QString)),
            (SignalCustomer *)(this->parent()->parent()->parent()),SLOT(slotSetSelectedRoom(QString,QString)));

    emit signalSendName(name,m_room_id);
}
 void SignalListItem::SetPic(QString picpath)
 {
    QSize picSize(30,30);
    m_room_pic->setPixmap(QPixmap(picpath).scaled(picSize,Qt::KeepAspectRatio));

 }

