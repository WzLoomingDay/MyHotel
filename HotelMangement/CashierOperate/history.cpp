#include "history.h"
#include "ui_history.h"
#include <QTableWidgetItem>
#include <QDebug>

History::History(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);
    ui->dateEdit->setCalendarPopup(true);
    ui->tableWidget->setColumnCount(14);
    QStringList strlist;
    strlist<<"BILLID"<<"房间号"<<"操作员ID"<<"订单号"<<"身份证号"
          <<"名字"<<"性别"<<"电话"<<"开始时间"<<"结束时间"<<"现金"
         <<"押金"<<"菜钱"<<"总收入";
    ui->tableWidget->setHorizontalHeaderLabels(strlist);
    ui->dateEdit->setDate(QDate::currentDate());

}
History * History::m_History = nullptr;

History::~History()
{
    delete ui;
}

void History::slotShowHistory(QString ID)
{
    this->show();
}

void History::closeEvent(QCloseEvent *event)
{
    m_History = nullptr;
    delete this;
}
History * History::GetHistory()
{
    if(m_History == nullptr)
    {
        m_History = new History();
    }
    return m_History;
}
void History::on_pb_search_clicked()
{
    GlobalVar::m_billInfoList.clear();
    QDate mdate = ui->dateEdit->date();
    QString mdateString = mdate.toString("yyyyMMdd");
    GlobalVar::m_billInfoList = DataBaseOperate::SelectHistoryInfo(mdateString);
    int msize = GlobalVar::m_billInfoList.size();
    ui->tableWidget->setRowCount(msize);
    qDebug()<<"msize = "<<msize<<endl;
    for(int i = 0;i<msize;i++)
    {
        QVariant temp;
        //strlist<<"BILLID"<<"房间号"<<"操作员ID"<<"订单号"<<"身份证号"
          //    <<"名字"<<"性别"<<"电话"<<"开始时间"<<"结束时间"<<"现金"
            // <<"押金"<<"菜钱"<<"总收入";
        QTableWidgetItem *item = new  QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_BILLID());
        ui->tableWidget->setItem(i,0,item);
        item = new QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_RID());
        ui->tableWidget->setItem(i,1,item);
        item = new  QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_UID());
        ui->tableWidget->setItem(i,2,item);
        temp = GlobalVar::m_billInfoList[i].getm_payid();
        item = new QTableWidgetItem(temp.toString());
        ui->tableWidget->setItem(i,3,item);
        item = new QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_idcard());
        ui->tableWidget->setItem(i,4,item);
        item = new QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_name());
        ui->tableWidget->setItem(i,5,item);
        item = new QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_sex());
        ui->tableWidget->setItem(i,6,item);
       item = new QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_call());
        ui->tableWidget->setItem(i,7,item);
        item = new QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_timebegin());
        ui->tableWidget->setItem(i,8,item);
        item = new QTableWidgetItem(GlobalVar::m_billInfoList[i].getm_timeend());
        ui->tableWidget->setItem(i,9,item);

        temp = GlobalVar::m_billInfoList[i].getm_cash();
        item = new QTableWidgetItem(temp.toString());
        ui->tableWidget->setItem(i,10,item);

        temp = GlobalVar::m_billInfoList[i].getm_pledge();
        item = new QTableWidgetItem(temp.toString());
        ui->tableWidget->setItem(i,11,item);

        temp = GlobalVar::m_billInfoList[i].getm_mealcash();
        item = new QTableWidgetItem(temp.toString());
        ui->tableWidget->setItem(i,12,item);

        temp = GlobalVar::m_billInfoList[i].getm_mealcash().toInt()+GlobalVar::m_billInfoList[i].getm_cash();
        item = new QTableWidgetItem(temp.toString());
        ui->tableWidget->setItem(i,13,item);
        //qDebug()<<GlobalVar::m_billInfoList[i].getm_BILLID()<<endl;

    }


}
