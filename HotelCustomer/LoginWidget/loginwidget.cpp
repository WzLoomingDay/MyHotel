#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>
LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    setPbEnabled(true);

}

LoginWidget::~LoginWidget()
{
    delete ui;
}


void LoginWidget::on_pb_login_clicked()
{
    if(ui->lineEdit_id->text().isEmpty()||ui->lineedit_passwd->text().isEmpty())
    {
        QString name = QString("输入错误");
        QString tips = QString("用户名和密码不能为空");
        QMessageBox::information(0,name,tips,QMessageBox::Ok);
    }else
    {
        emit signalLogin(ui->lineEdit_id->text(),ui->lineedit_passwd->text());
    }
}
 void LoginWidget::slotGetLoginState(QString state)
 {
    qDebug()<<"state = "<<state<<endl;
        ui->lineEdit_severstate->setText(state);
        if(state == "停机维护")
        {
            setPbEnabled(false);
        }else if(state == "通顺")
        {

            setPbEnabled(true);
        }
 }

 void LoginWidget::LoginFail(QString error)
 {
     QString name = "登陆错误";
     QString tips = "登陆错误："+ error;
     QMessageBox::information(0,name,tips,QMessageBox::Ok);
     if(error == "无此用户")
     {
         ui->lineEdit_id->clear();
         ui->lineedit_passwd->clear();
     }else if(error == "密码错误")
     {
          ui->lineedit_passwd->clear();
     }


 }
 void LoginWidget::setPbEnabled(bool state)
 {
     if(state == true)
     {
         ui->lineEdit_id->setFocusPolicy(Qt::StrongFocus);
         ui->lineedit_passwd->setFocusPolicy(Qt::StrongFocus);
         ui->pb_login->setEnabled(true);
         ui->pb_register->setEnabled(true);
         ui->pb_login_call->setEnabled(true);
     }else
     {
         ui->lineEdit_id->setFocusPolicy(Qt::NoFocus);
         ui->lineedit_passwd->setFocusPolicy(Qt::NoFocus);
         ui->pb_login->setEnabled(false);
         ui->pb_register->setEnabled(false);
         ui->pb_login_call->setEnabled(false);
     }

 }

void LoginWidget::on_pb_refresh_clicked()
{
    emit signalRefreshRequset();
}



void LoginWidget::on_pb_setting_clicked()
{
   // emit signalShowSetting();
}



