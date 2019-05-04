#include "hotelmangement.h"
#include "ui_hotelmangement.h"
#include <QPalette>
#include <QSize>

HotelMangement::HotelMangement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotelMangement)
{
    ui->setupUi(this);
    this->resize(1478,854);
    this->setAutoFillBackground(true);
    QPalette palette;
    QSize  picsize(1478,854);
    QPixmap mpic =  QPixmap(":/login/login.png");
    mpic.scaled(picsize, Qt::KeepAspectRatio);
    palette.setBrush(QPalette::Background, QBrush(mpic));

    this->setPalette(palette);
    this->setFixedSize(1478,854);

    ui->widgetlogin->installEventFilter(this);

}

HotelMangement::~HotelMangement()
{
    delete ui;
}

bool HotelMangement::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->widgetlogin)
    {

        if(event->type() == QEvent::Enter)
        {
            ui->widgetlogin->setStyleSheet("QWidget{background-color: rgba(202,154,60,1);}");
        }else if(event->type() == QEvent::Leave)
        {
             ui->widgetlogin->setStyleSheet("QWidget{background-color: rgba(202,154,60,0.5);}");
        }
    }

}
void HotelMangement::on_pushButton_cashier_clicked()
{
    qDebug()<<"on_pushButton_Cashier_clicked()"<<endl;
   QString tips;
   QString name;
   UserInfo UserTemp =
   DataBaseOperate::selectUserCashierInfo(ui->lineEdit_ID->text(),ui->lineEdit_PASSWD->text());
   if(UserTemp.getID() == "NULL")
   {
       tips = "错误：没有该前台ID";
       name = "ID错误";
       QMessageBox::information(this,name,tips,0x00000400);
   }else if(UserTemp.getPswd() == "NULL")
   {
       tips = "错误：密码错误";
       name = "密码错误";
       QMessageBox::information(this,name,tips,0x00000400);
   }else
   {
       PointertoCashier = new CCashierOperate();
       connect(this,SIGNAL(SignalCashierLogin(QString)),PointertoCashier,SLOT(slotShowCashierLogin(QString)));

       emit SignalCashierLogin(ui->lineEdit_ID->text());
       this->hide();
   }
}

void HotelMangement::on_pushButton_manger_clicked()
{
    qDebug()<<"on_pushButton_Manger_clicked()"<<endl;
    QString tips;
    QString name;
    UserInfo UserTemp =
    DataBaseOperate::selectUserMangerInfo(ui->lineEdit_ID->text(),ui->lineEdit_PASSWD->text());
    if(UserTemp.getID() == "NULL")
    {
        tips = "错误：没有该管理员ID";
        name = "ID错误";
        QMessageBox::information(this,name,tips,0x00000400);
    }else if(UserTemp.getPswd() == "NULL")
    {
        tips = "错误：密码错误";
        name = "密码错误";
        QMessageBox::information(this,name,tips,0x00000400);
    }else
    {
        PointertoManger = new MangerOperate();
        connect(this,SIGNAL(SignalMangerLogin(QString)),PointertoManger,SLOT(slotShowMangerLogin(QString)));
        emit SignalMangerLogin(ui->lineEdit_ID->text());
        this->hide();
    }
}
