#include "userinfobox.h"
#include "ui_userinfobox.h"


UserInfoBox::UserInfoBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfoBox)
{
    //this->setAttribute(Qt::WA_DeleteOnClose);
    //m_userInfoBox = nullptr;
   // qDebug()<<"UserInfoBox1"<<endl;
    ui->setupUi(this);
    QStringList strlist;
    strlist<<"Cashier"<<"Manger";
    ui->comboBox_type->addItems(strlist);
    //qDebug()<<"UserInfoBox2"<<endl;
    QString MyNewID = DataBaseOperate::GetIdnumber();
    //qDebug()<<"MyNewID = "<<MyNewID<<endl;


    ui->text_ID->setText(MyNewID);//获取最新id
    ui->dateEdit_birth->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit_birth->setCalendarPopup(true);
    ui->spinBox_salary->setRange(0,1000000);
    ui->spinBox_salary->setSuffix(" 元/月");
    ui->text_JoinTime->setText(QDate::currentDate().toString("yyyy-MM-dd"));

}
UserInfoBox* UserInfoBox::m_userInfoBox = nullptr;

UserInfoBox::~UserInfoBox()
{
   // delete m_databaseoperate;
    delete ui;
    qDebug()<<"delete UserInfo Box"<<endl;
}


void UserInfoBox::slotShowUserInfoBox()
{
    //ui->text_ID->setText();
    //this->setWindowFlags(q);
    this->show();
}


UserInfoBox * UserInfoBox::GetUserInfoBox()
{

    if(m_userInfoBox == nullptr)
    {
        qDebug()<<"m_userInfoBox == nullptr"<<endl;
        m_userInfoBox = new UserInfoBox();
    }
    qDebug()<<"m_userInfoBox !!!!= nullptr"<<endl;
    return m_userInfoBox;
}
void UserInfoBox::setUserInfoNullptr()
{
    m_userInfoBox = nullptr;
}
void UserInfoBox::on_pb_confirm_clicked()
{
    QString mCallRegExp = "[0-9]{11}";
    if(ui->lineEdit_psswd->displayText() ==
            ui->lineEdit_psswdagain->displayText())
    {
    if(ui->lineEdit_psswd->displayText() == "")
    {
       // qDebug()<<"密码不能为空"<<endl;
        QString title("密码为空");
        QString tips("密码不能为空");
        QMessageBox::information((QWidget *)0,title,tips,QMessageBox::Ok);
    }else if(!RegExp::JudgeRegExp(mCallRegExp,ui->lineEdit_call->text()))
    {
        QString title("手机号格式不正确");
        QString tips("手机号必须是11位数字");
        QMessageBox::information((QWidget *)0,title,tips,QMessageBox::Ok);
    }else
    {
    QVariant salary = ui->spinBox_salary->value();
    QString salarystr = salary.toString();
    m_workerInfo.setID(ui->text_ID->toPlainText());
    m_workerInfo.setPswd(ui->lineEdit_psswd->displayText());
    m_workerInfo.setType(ui->comboBox_type->currentText());
    m_workerInfo.SetWorkerBirth(ui->dateEdit_birth->text());
    m_workerInfo.SetWorkerCall(ui->lineEdit_call->text());
    m_workerInfo.SetWorkerJoinTime(ui->text_JoinTime->toPlainText());
    m_workerInfo.SetWorkerName(ui->lineEdit_Name->text());
    m_workerInfo.SetWorkerSalary(salarystr);
    m_workerInfo.SetWorkerSex(ui->comboBox_Sex->currentText());
    DataBaseOperate::CreateWorkerInfo(m_workerInfo);
    this->close();//触发close event

    }
    }else
    {
        QString title("密码不同");
        QString tips("两次输入的密码不一致请重新输入");
        QMessageBox::information((QWidget *)0,title,tips,QMessageBox::Ok);

    }
}
void UserInfoBox::closeEvent(QCloseEvent *event)
{
    UserInfoBox::setUserInfoNullptr();
    delete this;
}
void UserInfoBox::on_pb_giveup_clicked()
{
    UserInfoBox::setUserInfoNullptr();
    delete this;
}
