#include "showmealdetail.h"
#include "ui_showmealdetail.h"
#include <QDebug>
#include <QTableWidgetItem>
ShowMealDetail::ShowMealDetail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowMealDetail)
{
    ui->setupUi(this);

    ui->tableWidget_detail->setColumnCount(3);
    QStringList headers;
    headers << "菜id" <<"菜名字"<<"菜数量";
    ui->tableWidget_detail->setHorizontalHeaderLabels(headers);
    //ui->tableWidget_detail->setItem();
    ui->tableWidget_detail->setColumnWidth(0,50);
     ui->tableWidget_detail->setColumnWidth(1,140);
      ui->tableWidget_detail->setColumnWidth(2,95);

     qDebug()<<m_data<<endl;
     AnalyiseData(m_data);
     int size = m_mealmessage.size();
     ui->tableWidget_detail->setRowCount(size);
     for(int i = 0;i<size;i++)
     {
         QTableWidgetItem *item = new QTableWidgetItem(m_mealmessage[i].id);
         ui->tableWidget_detail->setItem(i, 0, item);
         item = new  QTableWidgetItem(m_mealmessage[i].name);
         ui->tableWidget_detail->setItem(i, 1, item);
         item = new  QTableWidgetItem(m_mealmessage[i].number);
         ui->tableWidget_detail->setItem(i, 2, item);
     }
}
ShowMealDetail * ShowMealDetail::m_mealdetail = nullptr;
QString ShowMealDetail::m_data = "";
ShowMealDetail::~ShowMealDetail()
{
    delete ui;
}

void ShowMealDetail::showMealDetail()
{
    qDebug()<<"showMealDetail"<<endl;
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);//设置一直为顶层窗体
    this->show();
}


void ShowMealDetail::on_pb_sure_clicked()
{

    closeEvent();
}

void ShowMealDetail::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    m_mealdetail = nullptr;
    qDebug()<<"delete ShowMealDetail"<<endl;
    delete this;

}

void ShowMealDetail::AnalyiseData(QString data)
{
    int size = data.length();
    //"(1.鱼香肉丝*1)(1.鱼香肉丝*2)"
    for(int i = 0;i < size;i++)
    {
        if(data.at(i) == '(')
        {
            struct MealMessage meal;
            i++;
            QString argID;
            while(data.at(i) != '.')
            {
                argID = argID + data.at(i);
                i++;
            }
            meal.id = argID;
            qDebug()<<"id = "<<meal.id<<" ";
            i++;//跳过 ‘.’
            QString argName;
            while(data.at(i) != '*')
            {
                argName = argName + data.at(i);
                i++;
            }
            meal.name = argName;
            qDebug()<<"name = "<<meal.name<<" ";
            i++;//跳过'*'
            QString argNum;
            while(data.at(i) != ')')
            {
                argNum = argNum + data.at(i);
                i++;
            }
            meal.number = argNum;
            qDebug()<<"number = "<<meal.number<<" ";
            //i++;
            m_mealmessage.append(meal);
        }

    }
    qDebug()<<"m_mealmessage size= "<<m_mealmessage.size()<<endl;


}

ShowMealDetail * ShowMealDetail::GetmealDetail(QString &data)
{

    if(m_mealdetail == nullptr)
    {
        m_data = data;
        m_mealdetail = new ShowMealDetail();
    }

    return m_mealdetail;
}
