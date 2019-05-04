#include "mangeroperate.h"
#include "ui_mangeroperate.h"
#include <QDebug>
#include <QDesktopWidget>

MangerOperate::MangerOperate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MangerOperate)

{
    ui->setupUi(this);
    ui->listWidget_menu->addItem("用户管理");
    ui->listWidget_menu->addItem("客户管理");
    ui->listWidget_menu->addItem("设置菜单");
    ui->listWidget_menu->addItem("设置房间");
    ui->listWidget_menu->addItem("营业额查询");


    connect(ui->listWidget_menu,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    m_usermange = new userMange();
    m_customermange = new CustomerMange();
    m_settingmeal = new SettingMeal();
    m_settingroom = new SettingRoom();
    m_settingcount = new SettingCount();
    m_searchincome = new SrarchIncom();
    ui->stackedWidget->insertWidget(0,m_usermange);
    ui->stackedWidget->insertWidget(1,m_customermange);
    ui->stackedWidget->insertWidget(2,m_settingmeal);
    ui->stackedWidget->insertWidget(3,m_settingroom);
    ui->stackedWidget->insertWidget(4,m_searchincome);


}

MangerOperate::~MangerOperate()
{
    delete ui;
}
 void MangerOperate::slotShowMangerLogin(const QString ID)
 {
     QString title = "当前管理员ID号为"+ID;
     qDebug()<<title;
     this->setWindowTitle(title);
     this->show();

 }

