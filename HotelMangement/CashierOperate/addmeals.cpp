#include "addmeals.h"
#include "ui_addmeals.h"
#include "globalvar.h"
AddMeals::AddMeals(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddMeals),
    m_mealprice("0"),
    m_mealpriceInt(0)
{
    ui->setupUi(this);
    InitTreeWidget();
    on_PB_refresh_clicked();
    //connect
}
AddMeals * AddMeals::m_AddMeals = nullptr;


AddMeals::~AddMeals()
{
    delete ui;
}

AddMeals *AddMeals::getAddMeals()
{
    if(m_AddMeals == nullptr)
    {
        m_AddMeals = new AddMeals();
    }
    return m_AddMeals;
}

void AddMeals::closeEvent(QCloseEvent *event)
 {
    Q_UNUSED(event);
    m_AddMeals = nullptr;
    delete this;
    qDebug()<<"delete AddMeals"<<endl;
 }

 void AddMeals::InitTreeWidget()
 {


        ui->tree_mealmenu->clear();
        ui->tree_mealmenu->setColumnCount(4);
        ui->tree_mealmenu->setColumnWidth(0,150);
        ui->tree_mealmenu->setColumnWidth(1,150);
        ui->tree_mealmenu->setColumnWidth(2,150);
        QStringList strlist;
        strlist<<"菜id"<<"菜名"<<"菜价格"<<"输入菜数量";
        ui->tree_mealmenu->setHeaderLabels(strlist);
        m_font.setPointSize(15);
        m_ditalfont.setPointSize(15);
        m_ditalfont.setFamily("楷体");
        //第一组 精品菜组
        int size = 0;
        QTreeWidgetItem *group1=new QTreeWidgetItem(ui->tree_mealmenu);


        group1->setText(0,"精品菜");
        group1->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        group1->setCheckState(0,Qt::Unchecked);

        group1->setFont(0,m_font);

        GlobalVar::m_mealInfoList.clear();
        GlobalVar::m_mealInfoList =  DataBaseOperate::SelectMealInfo(group1->text(0));
        size = GlobalVar::m_mealInfoList.size();
        QTreeWidgetItem *item1[size];
        for(int i = 0;i<size;i++)
        {
             item1[i]=new QTreeWidgetItem(group1);
             QVariant temp = GlobalVar::m_mealInfoList[i].getm_mealid();
             item1[i]->setText(0,temp.toString());
             item1[i]->setText(1,GlobalVar::m_mealInfoList[i].getm_mealname());
             item1[i]->setText(2,GlobalVar::m_mealInfoList[i].getm_mealprice());

            item1[i]->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            item1[i]->setCheckState(0,Qt::Unchecked);
            item1[i]->setFont(0,m_ditalfont);
            item1[i]->setFont(1,m_ditalfont);
            item1[i]->setFont(2,m_ditalfont);
            item1[i]->setFont(3,m_ditalfont);
             ui->tree_mealmenu->openPersistentEditor(item1[i],3);
        }

        //第二组 主食组
        QTreeWidgetItem *group2=new QTreeWidgetItem(ui->tree_mealmenu);
        group2->setText(0,"主食");
        group2->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        group2->setCheckState(0,Qt::Unchecked);
        group2->setFont(0,m_font);
        GlobalVar::m_mealInfoList.clear();
        GlobalVar::m_mealInfoList =  DataBaseOperate::SelectMealInfo(group2->text(0));
        size = GlobalVar::m_mealInfoList.size();
        QTreeWidgetItem *item2[size];
        for(int i = 0;i<size;i++)
        {
             item2[i]=new QTreeWidgetItem(group2);
             QVariant temp = GlobalVar::m_mealInfoList[i].getm_mealid();
             item2[i]->setText(0,temp.toString());
             item2[i]->setText(1,GlobalVar::m_mealInfoList[i].getm_mealname());
             item2[i]->setText(2,GlobalVar::m_mealInfoList[i].getm_mealprice());

             item2[i]->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
             item2[i]->setCheckState(0,Qt::Unchecked);
             item2[i]->setFont(0,m_ditalfont);
             item2[i]->setFont(1,m_ditalfont);
             item2[i]->setFont(2,m_ditalfont);
             item2[i]->setFont(3,m_ditalfont);
              ui->tree_mealmenu->openPersistentEditor(item2[i],3);
        }

        //第三组 饮品组
        QTreeWidgetItem *group3=new QTreeWidgetItem(ui->tree_mealmenu);
        group3->setText(0,"饮品");
        group3->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        group3->setCheckState(0,Qt::Unchecked);
        group3->setFont(0,m_font);
        GlobalVar::m_mealInfoList.clear();
        GlobalVar::m_mealInfoList = DataBaseOperate::SelectMealInfo(group3->text(0));
        size = GlobalVar::m_mealInfoList.size();
        QTreeWidgetItem *item3[size];
        for(int i = 0;i<size;i++)
        {
             item3[i]=new QTreeWidgetItem(group3);
              QVariant temp = GlobalVar::m_mealInfoList[i].getm_mealid();
             item3[i]->setText(0,temp.toString());
             item3[i]->setText(1,GlobalVar::m_mealInfoList[i].getm_mealname());
             item3[i]->setText(2,GlobalVar::m_mealInfoList[i].getm_mealprice());

             item3[i]->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
             item3[i]->setCheckState(0,Qt::Unchecked);
             ui->tree_mealmenu->openPersistentEditor(item3[i],3);
             item3[i]->setFont(0,m_ditalfont);
             item3[i]->setFont(1,m_ditalfont);
             item3[i]->setFont(2,m_ditalfont);
             item3[i]->setFont(3,m_ditalfont);

        }
        connect(ui->tree_mealmenu,SIGNAL(itemChanged(QTreeWidgetItem *,int)),
                this,SLOT(slotItemChanged(QTreeWidgetItem*,int)));


 }
 void AddMeals::slotShowAddMeals(QString ID)
 {
    qDebug()<<"ID = "<<ID<<endl;
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);//设置一直为顶层窗体
    this->show();

 }
  void AddMeals::slotItemChanged(QTreeWidgetItem *item, int column)
  {
    //qDebug()<<"column = "<<column <<"count  = "<<item->columnCount();
    if(column == 3)
    {
        m_mealpriceInt = 0;
        m_mealprice.clear();
       if(item->text(column).isEmpty())
       {
          item->setCheckState(0,Qt::Unchecked);
       }else
       {
           item->setCheckState(0,Qt::Checked);
       }

           //item->setCheckState(0,Qt::Checked);
           //QString data = "(" + item->text(0) + "," +item->text(column) + ")";
           //qDebug()<<" data = " <<data<<endl;
           //item->text(2).toInt();

           QTreeWidgetItemIterator it(ui->tree_mealmenu);//遍历整个treewidget
           while (*it)
           {
               if((*it)->checkState(0) == Qt::Checked)//checkbox选定并且菜的个数不为空
               {
                   m_mealpriceInt = m_mealpriceInt +
                           ((*it)->text(2).toInt())*((*it)->text(3).toInt());
                   qDebug()<<"text1 = "<<(*it)->text(2).toInt()<<endl;
                   qDebug()<<"text2 = "<<(*it)->text(3).toInt()<<endl;
                    qDebug()<<"m_mealpriceInt = "<<m_mealpriceInt<<endl;


               }
               ++it;
           }
           QVariant tempmealprice =  m_mealpriceInt;
           m_mealprice = tempmealprice.toString();
           qDebug()<<"m_mealprice  = "<<m_mealprice<<"m_mealpriceInt = "<<m_mealpriceInt<<endl;

           ui->lineEdit_cash->setText(m_mealprice);

       }

  }




void AddMeals::on_PB_refresh_clicked()
{
    //ui->listWidget_customer
    ui->listWidget_customer->clear();
    GlobalVar::m_billInfoList.clear();
    GlobalVar::m_billInfoList =  DataBaseOperate::SelectBillInfo(USING_BILL);
    for(int i = 0;i<GlobalVar::m_billInfoList.size();i++)
    {
        ui->listWidget_customer->addItem(GlobalVar::m_billInfoList[i].getm_RID());
    }
    connect(ui->listWidget_customer,SIGNAL(currentTextChanged(QString)),
            this,SLOT(slotShowSlectUser(QString)));

}
void AddMeals::slotShowSlectUser(QString RID)
{
    ui->lineEdit_mealuser->setText(RID);
    GlobalVar::m_billInfoList.clear();
    GlobalVar::m_billInfoList =  DataBaseOperate::SelectBillInfo(RID);//这里为什么要重新从数据库读一次，而不让直接用上一次的检索结果？
                                        //主要是m_billInfoList是全局变量，如果操作到一半，有别的需要检索
                                        //m_billInfoList的操作，就会导致信息不匹配
    m_selectbill = GlobalVar::m_billInfoList[0];
    if(m_selectbill.getm_mealflag() == "1")
    {
        qDebug()<<m_selectbill.getm_mealbill()<<endl;
    }
    //qDebug()<<m_selectbill.getm_RID()<<endl;

}


void AddMeals::on_pushButton_clicked()
{

     m_meal.clear();
     if(!(ui->lineEdit_cash->text().isEmpty()))//如果价格非空（非空说明了点了菜了）
     {
            m_selectbill.setm_mealflag("1");//设置mealflag为0
            m_selectbill.setm_mealcash(ui->lineEdit_cash->text());//设置价格
            QTreeWidgetItemIterator it(ui->tree_mealmenu);
            while (*it)
            {
                if(!((*it)->text(3).isEmpty()))//如果菜数量非空,也就是说点了这个菜
                {
                    m_meal = m_meal + "(" + (*it)->text(0) + "." +(*it)->text(1) + "*" + (*it)->text(3) + ")";
                }
                ++it;
            }

     }
     qDebug()<<"m_meal = "<<m_meal<<endl;
     m_selectbill.setm_mealbill(m_meal);
     DataBaseOperate::UpdateBillMeal(m_selectbill);
    QString information_name = QString("加菜成功");
    QString information_tips = QString("加菜成功");
    QMessageBox::information(this,information_name,information_tips,QMessageBox::Ok);
    closeEvent();
}



void AddMeals::on_pB_EXIT_clicked()
{
    closeEvent();
}
