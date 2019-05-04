#include "usermange.h"
#include "ui_usermange.h"

userMange::userMange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userMange)
{
    ui->setupUi(this);
    ui->comboBox_type->addItem("管理员");
     ui->comboBox_type->addItem("前台");
      ui->comboBox_type->addItem("所有用户");
      model = new QStandardItemModel(this);//Qtableview用到的
      comdelegate = new Comboxdelegate(this);//还没delete
      Buttondelegate = new PushBottonDelegate(this);
      Calenderdelegate = new CalenderDelegate(this);
      SexDelegate = new comboxSexDelegate(this);
      mLineEditDelegat = new LineEditDelegate(this);
      mSpinBoxDelegate = new SpinBoxDelegate(this);
      mCheckBoxDelegate = new CheckBoxDelegate(this);


}

userMange::~userMange()
{
    delete ui;
}

void userMange::on_pb_search_clicked()
{
    model->clear();//清除上一次表格中的内容
    model->setColumnCount(10);//设置表格几列
    model->setHeaderData(0,Qt::Horizontal,"id");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"性别");
     model->setHeaderData(3,Qt::Horizontal,"职位");
     model->setHeaderData(4,Qt::Horizontal,"电话");
      model->setHeaderData(5,Qt::Horizontal,"工资");
      model->setHeaderData(6,Qt::Horizontal,"出生日期");
    model->setHeaderData(7,Qt::Horizontal,"删除用户");
    model->setHeaderData(8,Qt::Horizontal,"修改密码");
     model->setHeaderData(9,Qt::Horizontal,"入职时间");
    QString MUID = ui->lineEdit_searchid->text();
    QSqlQuery querySearch;

    QString queryStringSearch =
    QString("select * from (user natural join worker) where UID = '%1'").arg(MUID);//ORDER BY UID ASC防止mysql乱序排列
    userMange::selectUserData(queryStringSearch,querySearch,"worker_name");

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//让表格大小适应model，即是tableview

     ui->tableView->setModel(model);
     ui->tableView->setItemDelegateForColumn(1,mLineEditDelegat);
     ui->tableView->setItemDelegateForColumn(2,SexDelegate);
     ui->tableView->setItemDelegateForColumn(3,comdelegate);
     ui->tableView->setItemDelegateForColumn(4,mLineEditDelegat);
     ui->tableView->setItemDelegateForColumn(6,Calenderdelegate);
     ui->tableView->setItemDelegateForColumn(5,mSpinBoxDelegate);
     ui->tableView->setItemDelegateForColumn(7,mCheckBoxDelegate);
     ui->tableView->setItemDelegateForColumn(8,Buttondelegate);
}

void userMange::on_pb_adduser_clicked()
{
    m_pointerToUserInfo = UserInfoBox::GetUserInfoBox();
   // connect(ui->pb_adduser,SIGNAL(clicked(bool)),
     //     m_pointerToUserInfo,SLOT(slotShowUserInfoBox()));
    connect(this,SIGNAL(signalShowUserInfoBox()),
            m_pointerToUserInfo,SLOT(slotShowUserInfoBox()));

    emit signalShowUserInfoBox();

}
void userMange::selectUserData(const QString &sql, QSqlQuery &query,const QString &name)
{
    if(query.exec(sql))
    {
    int id_idx = query.record().indexOf("UID");
    int name_idx = query.record().indexOf(name);
    int sex_idx = query.record().indexOf("worker_Sex");
    int type_idx = query.record().indexOf("type_name");
    int call_idx = query.record().indexOf("worker_call");
    int salary_idx = query.record().indexOf("worker_Salary");
    int Birth_idx = query.record().indexOf("Worker_Birth");
    int JoinTime_idx = query.record().indexOf("worker_JoinTime");
    QString Select_Id;
    QString Select_Name;
    QString Select_Sex;
    QString Select_Type;
    QString Select_Call;
    QString Select_Salary;
    QString Select_Birth;
    QString Select_JoinTime;

    while (query.next())
    {
       Select_Id = query.value(id_idx).toString();
       Select_Name = query.value(name_idx).toString();
       Select_Sex = query.value(sex_idx).toString();
       Select_Type = query.value(type_idx).toString();
       Select_Call = query.value(call_idx).toString();
       Select_Salary = query.value(salary_idx).toString();
       Select_Birth = query.value(Birth_idx).toString();
       Select_JoinTime = query.value(JoinTime_idx).toString();

        qDebug()<<"Select_Id"<<Select_Id<<"Select_Name"<<Select_Name<<"Select_Type"<<Select_Type<<endl;
        QStandardItem * StandardItem = new QStandardItem(Select_Id);
        StandardItem->setBackground(QBrush(QColor(241,244,244) ) );
        StandardItem->setEditable(false);
        model->setItem(query.at(),0,StandardItem);

        StandardItem = new QStandardItem(Select_Name);
        StandardItem->setBackground(QBrush(QColor(153,255,153) ) );
        StandardItem->setEditable(true);
        model->setItem(query.at(),1,StandardItem);

        StandardItem = new QStandardItem(Select_Sex);
        StandardItem->setBackground(QBrush(QColor(137,207,240) ) );
        StandardItem->setEditable(true);
        model->setItem(query.at(), 2,StandardItem);

      StandardItem = new QStandardItem(Select_Type);
      StandardItem->setEditable(true);
      StandardItem->setBackground(QBrush(QColor(137,207,240) ) );//设置为浅蓝色
      model->setItem(query.at(),3,StandardItem);

      StandardItem = new QStandardItem(Select_Call);
      StandardItem->setBackground(QBrush(QColor(153,255,153) ) );
      StandardItem->setEditable(true);
      model->setItem(query.at(), 4,StandardItem);

      StandardItem = new QStandardItem(Select_Salary);
      StandardItem->setBackground(QBrush(QColor(255,255,153) ) );
      StandardItem->setEditable(true);
      model->setItem(query.at(), 5,StandardItem);

      StandardItem =new QStandardItem(Select_Birth);
      StandardItem->setEditable(true);//设置该列是否可以被修改
      StandardItem->setBackground(QBrush(QColor( 255, 204, 255) ) );
      model->setItem(query.at(), 6,StandardItem);

      StandardItem =new QStandardItem("点击删除");
      StandardItem->setEditable(true);//设置该列是否可以被修改
      StandardItem->setBackground(QBrush(QColor(255,185,115) ) );
      model->setItem(query.at(), 7,StandardItem);

      StandardItem =new QStandardItem("点击修改");
      StandardItem->setEditable(true);//设置该列是否可以被修改
      model->setItem(query.at(), 8,StandardItem);

      StandardItem =new QStandardItem(Select_JoinTime);
      StandardItem->setBackground(QBrush(QColor(241,244,244) ) );
      StandardItem->setEditable(false);//设置该列是否可以被修改
      model->setItem(query.at(),9,StandardItem);
     /*ui->tableView_User->horizontaladeHer()->setSectionResizeMode(0,QHeaderView::ResizeToContents);//让该列根据字数大小进行自动调整*/
    }
    }else
    {
         qDebug()<<"no Select"<<endl;
    }
    /*for(int i = 0;i<model->rowCount();i++)
    {
    standardItem = model->item(i,2);
    emit model->itemChanged(standardItem);
    }*/

}
void userMange::on_comboBox_type_activated(const QString &arg1)
{
    qDebug()<<"activated"<<arg1<<endl;
    model->clear();//清除上一次表格中的内容
    model->setColumnCount(10);//设置表格几列
    model->setHeaderData(0,Qt::Horizontal,"id");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"性别");
     model->setHeaderData(3,Qt::Horizontal,"职位");
     model->setHeaderData(4,Qt::Horizontal,"电话");
      model->setHeaderData(5,Qt::Horizontal,"工资");
      model->setHeaderData(6,Qt::Horizontal,"出生日期");
    model->setHeaderData(7,Qt::Horizontal,"删除用户");
    model->setHeaderData(8,Qt::Horizontal,"修改密码");
     model->setHeaderData(9,Qt::Horizontal,"入职时间");
    if(arg1 == "管理员")
    {
         QSqlQuery queryManger;
         QString queryStringManger =
         QString("select * from (user natural join worker) where UID in (select UID from user where type_name = 'Manger')"
                 "ORDER BY Uid ASC");//ORDER BY UID ASC防止mysql乱序排列
         userMange::selectUserData(queryStringManger,queryManger,"worker_name");

    }else if(arg1 == "前台")
    {
        QSqlQuery queryCashier;
        QString queryStringCashier =
        QString("select * from (user natural join worker) where UID in (select UID from user where type_name = 'Cashier')"
                "ORDER BY UID ASC");
        userMange::selectUserData(queryStringCashier,queryCashier,"worker_name");

    }else if(arg1 == "所有用户")
    {
        QSqlQuery queryUser;
        QString queryStringUser =
        QString("select * from (user natural join worker) ORDER BY UID ASC");
       // QString("select * from user");
        userMange::selectUserData(queryStringUser,queryUser,"worker_name");
    }
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//让表格大小适应model，即是tableview

     ui->tableView->setModel(model);
     ui->tableView->setItemDelegateForColumn(1,mLineEditDelegat);
     ui->tableView->setItemDelegateForColumn(2,SexDelegate);
     ui->tableView->setItemDelegateForColumn(3,comdelegate);
     ui->tableView->setItemDelegateForColumn(4,mLineEditDelegat);
     ui->tableView->setItemDelegateForColumn(6,Calenderdelegate);
     ui->tableView->setItemDelegateForColumn(5,mSpinBoxDelegate);
     ui->tableView->setItemDelegateForColumn(7,mCheckBoxDelegate);
     ui->tableView->setItemDelegateForColumn(8,Buttondelegate);

}
