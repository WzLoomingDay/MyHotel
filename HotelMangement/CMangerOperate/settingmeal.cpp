#include "settingmeal.h"
#include "ui_settingmeal.h"
#include <QTableWidgetItem>
#include <QMessageBox>

SettingMeal::SettingMeal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingMeal)
{
    ui->setupUi(this);
    QStringList typelist;
    typelist<<"所有"<<"精品菜"<<"主食"<<"饮品";
    ui->comboBox_type->addItems(typelist);
    typelist.clear();
    typelist<<"精品菜"<<"主食"<<"饮品";
    ui->comb1_type->addItems(typelist);
    ui->comb2_type->addItems(typelist);
    ui->table_meallist->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->table_meallist->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中
 //  ui->table_meallist->setHorizontalHeader(QHeaderView::Stretch); ResizeMode();


    //ui->table_meallist->setColumnWidth(0,11);
    //ui->table_meallist->setColumnWidth(1,110);
    //ui->table_meallist->setColumnWidth(2,110);
    //ui->table_meallist->setColumnWidth(3,110);
    updateMealList(ui->comboBox_type->currentText());
    connect(ui->comboBox_type,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(updateMealList(QString)));
    connect(ui->table_meallist,SIGNAL(clicked(QModelIndex)),this,SLOT(slotClickedTable(QModelIndex)));

}

SettingMeal::~SettingMeal()
{
    delete ui;
}

void SettingMeal::updateMealList(QString type)
{
    //ui->table_meallist->resizeColumnsToContents();//自动适应列宽

    GlobalVar::m_mealInfoList.clear();

    if(type == "所有")
    {
        GlobalVar::m_mealInfoList = DataBaseOperate::SelectMealInfo(ALL_MEAL);
    }else
    {
        GlobalVar::m_mealInfoList = DataBaseOperate::SelectMealInfo(type);
    }
    int row = GlobalVar::m_mealInfoList.size();
    ui->table_meallist->clear();
    ui->table_meallist->setRowCount(row);
    ui->table_meallist->setColumnCount(4);
    ui->table_meallist->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->table_meallist->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->table_meallist->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->table_meallist->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    QStringList headers;
    headers << "菜ID" <<"菜名字" <<"菜类型" << "菜价格";
    ui->table_meallist->setHorizontalHeaderLabels(headers);
    for(int i = 0; i < row; i++)
    {
        QVariant vid =  GlobalVar::m_mealInfoList[i].getm_mealid();
        QTableWidgetItem *item = new  QTableWidgetItem(vid.toString());
        ui->table_meallist->setItem(i, 0, item);
        item = new  QTableWidgetItem(GlobalVar::m_mealInfoList[i].getm_mealname());
        ui->table_meallist->setItem(i, 1, item);
        item = new  QTableWidgetItem(GlobalVar::m_mealInfoList[i].getm_mealtype());
        ui->table_meallist->setItem(i, 2, item);
        item = new  QTableWidgetItem(GlobalVar::m_mealInfoList[i].getm_mealprice());
        ui->table_meallist->setItem(i, 3, item);
    }

}
void SettingMeal::slotClickedTable(QModelIndex model)
{
     qDebug()<<model.row()<<endl;
     QVariant MealID = model.model()->index(model.row(),0).data();//取得当前行第一列的值
    // qDebug()<<MealID<<endl;
     MealInfo info = DataBaseOperate::SelectMealInfo(MealID.toInt());
     //qDebug()<<info.getm_mealname()<<endl;
     ui->line1_mealid->setText(MealID.toString());
     ui->line1_mealname->setText(info.getm_mealname());
     int myindex = ui->comb1_type->findText(info.getm_mealtype());
     ui->comb1_type->setCurrentIndex(myindex);
     ui->spin1_price->setValue(info.getm_mealprice().toInt());

}

void SettingMeal::on_PB_change_clicked()
{
    if(ui->line1_mealid->text().isEmpty()||
            ui->line1_mealname->text().isEmpty())
    {
        QString name = "参数错误";
        QString tips = "您选择修改的参数有误";
        QMessageBox::information(this,name,tips,QMessageBox::Ok);

    }else
    {
        QVariant vint =  ui->spin1_price->value();
        MealInfo info(ui->line1_mealid->text().toInt(),ui->line1_mealname->text(),
                      ui->comb1_type->currentText(),vint.toString());


        DataBaseOperate::UpdateMealInfo(info);
        updateMealList(ui->comboBox_type->currentText());


        QString name = "修改成功";
        QString tips = "您成功修改了 id = "+ui->line1_mealid->text()+" 的信息";
        QMessageBox::information(this,name,tips,QMessageBox::Ok);
        clearMealDetail();
    }
}

void SettingMeal::on_PB_delete_clicked()
{
    QString name = "是否删除";
    QString tips = "是否删除id = "+ui->line1_mealid->text()+"菜品";
    switch(QMessageBox::information(0,name,tips,QMessageBox::Ok|QMessageBox::Cancel))
    {
    case QMessageBox::Ok:
        DataBaseOperate::DeleteMealInfo(ui->line1_mealid->text().toInt());

        updateMealList(ui->comboBox_type->currentText());
        name = "删除成功";
        tips = "成功删除 id = "+ui->line1_mealid->text();
        QMessageBox::information(0,name,tips,QMessageBox::Ok);

        clearMealDetail();
        break;
    case QMessageBox::Cancel:
        break;
    }


}
void  SettingMeal::clearMealDetail()
{
    ui->line1_mealid->clear();
    ui->comb1_type->setCurrentIndex(0);
    ui->line1_mealname->clear();
    ui->spin1_price->clear();

}

void SettingMeal::on_PB_add_clicked()
{
   // qDebug()<<"SelectNewMealID = "<<<<endl;
    if(ui->line2_mealname_2->text().isEmpty())
    {
        QString name = "参数错误";
        QString tips = "您选择修改的参数有误";
        QMessageBox::information(this,name,tips,QMessageBox::Ok);
    }else
    {
        QString mealID = DataBaseOperate::SelectNewMealID();
        MealInfo info;
        info.setm_mealid(mealID.toInt());
        info.setm_mealname(ui->line2_mealname_2->text());
        info.setm_mealtype(ui->comb2_type->currentText());
        QVariant vint = ui->spin2_price->value();
        info.setm_mealprice(vint.toString());
        DataBaseOperate::CreateMealInfo(info);

        updateMealList(ui->comboBox_type->currentText());

        QString name = "添加成功";
        QString tips = "添加菜品id = " + mealID +" 成功";
        QMessageBox::information(this,name,tips,QMessageBox::Ok);
        clearMealAdd();
    }
}
void SettingMeal::clearMealAdd()
{
    ui->line2_mealname_2->clear();
    ui->comb2_type->setCurrentIndex(0);
    ui->spin2_price->setValue(0);
}


