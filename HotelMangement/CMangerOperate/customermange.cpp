#include "customermange.h"
#include "ui_customermange.h"
#include <QTableWidgetItem>
CustomerMange::CustomerMange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerMange)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中
    QStringList strlist;
    strlist<<"CID"<<"密码"<<"姓名"<<"性别"<<"电话"<<"身份证"<<"预定标志"<<"预定房间号"<<"房间类型"<<"最后一次登陆的ip";
    ui->tableWidget->setHorizontalHeaderLabels(strlist);


}

CustomerMange::~CustomerMange()
{
    delete ui;
}

void CustomerMange::on_pb_check_clicked()
{
    ui->tableWidget->clear();
    updateTabWidget(ALL_CUSTOMER);
}

void CustomerMange::updateTabWidget(QString mcid)
{
    ui->tableWidget->clear();
    GlobalVar::m_customerInfoList.clear();
    GlobalVar::m_customerInfoList = DataBaseOperate::SelectCustomerInfo(mcid);
    int size = GlobalVar::m_customerInfoList.size();
    ui->tableWidget->setRowCount(size);
    QStringList strlist;
    strlist<<"CID"<<"密码"<<"姓名"<<"性别"<<"电话"<<"身份证"<<"预定标志"<<"预定房间号"<<"房间类型"<<"最后一次登陆的ip";
    ui->tableWidget->setHorizontalHeaderLabels(strlist);
    //ui->tableWidget->horizontalHeader()->ResizeMode();
     ui->tableWidget->horizontalHeader()->setSectionResizeMode(5,QHeaderView::ResizeToContents);
    for(int i = 0;i<size;i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_cid());
        ui->tableWidget->setItem(i,0,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_pswd());
        ui->tableWidget->setItem(i,1,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_name());
        ui->tableWidget->setItem(i,2,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_Sex());
        ui->tableWidget->setItem(i,3,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_Call());
        ui->tableWidget->setItem(i,4,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_idcard());
        ui->tableWidget->setItem(i,5,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_flag());
        ui->tableWidget->setItem(i,6,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_RID());
        ui->tableWidget->setItem(i,7,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_roomtype());
        ui->tableWidget->setItem(i,8,item);
        item = new QTableWidgetItem(GlobalVar::m_customerInfoList[i].getm_addr());
        ui->tableWidget->setItem(i,9,item);
    }
}

void CustomerMange::on_pb_searchid_clicked()
{
    ui->tableWidget->clear();
    updateTabWidget(ui->lineEdit_id->text());
}
