#include "settingroom.h"
#include "ui_settingroom.h"
#include <QMessageBox>

SettingRoom::SettingRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingRoom)
{
    ui->setupUi(this);
    ui->CB_room_type->addItem("标准单人间");
    ui->CB_room_type->addItem("标准双人间");
    ui->CB_room_type->addItem("商务单人间");
    ui->CB_room_type->addItem("豪华双人间");
    ui->CB_room_type->addItem("总统套房");
    ui->CB_room_type->addItem("家庭套间");
    ui->CB_room_type->addItem("所有");

    ui->CB_room_floor->addItem("美丽一楼");
    ui->CB_room_floor->addItem("优雅二楼");
    ui->CB_room_floor->addItem("清新三楼");
    ui->CB_room_floor->addItem("脱俗四楼");
     ui->CB_room_floor->addItem("所有");

    ui->comboBox_type->addItem("标准单人间");
    ui->comboBox_type->addItem("标准双人间");
    ui->comboBox_type->addItem("商务单人间");
    ui->comboBox_type->addItem("豪华双人间");
    ui->comboBox_type->addItem("总统套房");
    ui->comboBox_type->addItem("家庭套间");

    ui->comboBox_floor->addItem("美丽一楼");
    ui->comboBox_floor->addItem("优雅二楼");
    ui->comboBox_floor->addItem("清新三楼");
    ui->comboBox_floor->addItem("脱俗四楼");

    ui->comboBox2_type->addItem("标准单人间");
    ui->comboBox2_type->addItem("标准双人间");
    ui->comboBox2_type->addItem("商务单人间");
    ui->comboBox2_type->addItem("豪华双人间");
    ui->comboBox2_type->addItem("总统套房");
    ui->comboBox2_type->addItem("家庭套间");

    ui->comboBox2_floor->addItem("美丽一楼");
    ui->comboBox2_floor->addItem("优雅二楼");
    ui->comboBox2_floor->addItem("清新三楼");
    ui->comboBox2_floor->addItem("脱俗四楼");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    connect(ui->tableWidget,SIGNAL(clicked(QModelIndex))
            ,this,SLOT(slotShowRoomDetail(QModelIndex)));
}

SettingRoom::~SettingRoom()
{
    delete ui;
}

void SettingRoom::on_pushButton_clicked()
{
    QString roomtype = ui->CB_room_type->currentText();
    QString roomfloor = ui->CB_room_floor->currentText();
    GlobalVar::m_roomInfoList.clear();
    GlobalVar::m_roomInfoList = DataBaseOperate::SelectRoomInfo(roomtype,roomfloor);
    updataTableWidget(GlobalVar::m_roomInfoList.size());


}
 void SettingRoom::updataTableWidget(int row)
 {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setColumnCount(8);
    QStringList headers;
    headers << "RID" <<"状态" <<"房间名字" << "房间类型" << "房间楼层" << "房间价格"
            <<"房间折扣"<<"房间电话";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    int count = row;
    int index = 0;

    for(int i = 0; i < count; i++)
    {
        QTableWidgetItem *item = new  QTableWidgetItem(GlobalVar::m_roomInfoList.at(index+i).get_room_id());
        ui->tableWidget->setItem(i, 0, item);
        item = new  QTableWidgetItem(GlobalVar::m_roomInfoList.at(index+i).get_room_state());
        ui->tableWidget->setItem(i, 1, item);
        item = new  QTableWidgetItem(GlobalVar::m_roomInfoList.at(index+i).get_room_name());
        ui->tableWidget->setItem(i, 2, item);
        item = new  QTableWidgetItem(GlobalVar::m_roomInfoList.at(index+i).get_room_type());
        ui->tableWidget->setItem(i, 3, item);
        item = new  QTableWidgetItem(GlobalVar::m_roomInfoList.at(index+i).get_room_place());
        ui->tableWidget->setItem(i, 4, item);
        item = new  QTableWidgetItem(GlobalVar::m_roomInfoList.at(index+i).get_room_price());
        ui->tableWidget->setItem(i, 5, item);
        item = new  QTableWidgetItem(GlobalVar::m_roomInfoList.at(index+i).get_room_discount());
        ui->tableWidget->setItem(i, 6, item);
        item = new  QTableWidgetItem(GlobalVar::m_roomInfoList.at(index+i).get_room_call());
        ui->tableWidget->setItem(i, 7, item);
        /*ItemForOpertor *buttonBox = new ItemForOpertor(i);
        connect(buttonBox, SIGNAL(signalModifyStudentInfo(int)),
                m_studentInfoDialog, SLOT(slotModifyStudentInfo(int)));
        connect(buttonBox, SIGNAL(signalDeleteStudentInfo(int)),
                m_studentInfoDialog, SLOT(slotDeleteStudentInfo(int)));
        ui->tableWidget->setCellWidget(i, 4, buttonBox);*/
    }

 }

 void SettingRoom::slotShowRoomDetail(QModelIndex Mmodel)
 {
    int row = Mmodel.row();
    ui->lineEdit_roomid->setText(Mmodel.model()->index(row,0).data().toString());
    ui->lineEdit_roomname->setText(Mmodel.model()->index(row,2).data().toString());
    ui->lineEdit_roomprice->setText(Mmodel.model()->index(row,5).data().toString());
    ui->lineEdit_roomcount->setText(Mmodel.model()->index(row,6).data().toString());
    ui->lineEdit_roomcall->setText(Mmodel.model()->index(row,7).data().toString());

    QString roomtype = Mmodel.model()->index(row,3).data().toString();
    int typeindex = ui->comboBox_type->findText(roomtype);//找到文字相关索引
    ui->comboBox_type->setCurrentIndex(typeindex);//设置索引

    QString roomfloor = Mmodel.model()->index(row,4).data().toString();
    int floorindex = ui->comboBox_floor->findText(roomfloor);//找到文字相关索引
    ui->comboBox_floor->setCurrentIndex(floorindex);//设置索引


 }



void SettingRoom::on_pb_change_clicked()
{
    if(ui->lineEdit_roomid->text().isEmpty()||
            ui->lineEdit_roomname->text().isEmpty()||
            ui->lineEdit_roomprice->text().isEmpty())
    {

        QString name = "修改错误";
        QString tips = "您修改的信息格式有误，信息不全";
        QMessageBox::information(0,name,tips,QMessageBox::Ok);
    }else
    {
        RoomInfo info;
        info.set_room_id(ui->lineEdit_roomid->text());

        info.set_room_name(ui->lineEdit_roomname->text());
        info.set_room_price(ui->lineEdit_roomprice->text());
        info.set_room_discount(ui->lineEdit_roomcount->text());
        info.set_room_call(ui->lineEdit_roomcall->text());
        info.set_room_place(ui->comboBox_floor->currentText());
        info.set_room_type(ui->comboBox_type->currentText());
        if(!DataBaseOperate::UpdateRoomInfo(info))
        {
            QString name = "更新错误";
            QString tips = "更新错误，可能修改的房间名已经存在";
            QMessageBox::information(0,name,tips,QMessageBox::Ok);
        }else
        {
            on_pushButton_clicked();
            clearDetail();
        }

    }

}

void SettingRoom::on_pb_delete_clicked()
{
    QString mrid = ui->lineEdit_roomid->text();
    if(!DataBaseOperate::DeleteRoomInfo(mrid))
    {
        QString name = "删除错误";
        QString tips = "删除信息失败";
        QMessageBox::information(0,name,tips,QMessageBox::Ok);
    }else
    {
        on_pushButton_clicked();
        clearDetail();
    }


}

void SettingRoom::on_pb2_add_clicked()
{
    if(ui->lineEdit2_roomname->text().isEmpty()||
            ui->lineEdit2_roomcount->text().isEmpty()||
            ui->lineEdit2_roomcall->text().isEmpty()||
            ui->lineEdit2_roomprice->text().isEmpty())
    {
        QString name = "输入错误";
        QString tips = "创建错误，信息填写不全";
        QMessageBox::information(0,name,tips,QMessageBox::Ok);
    }else
    {

        QString newRid = DataBaseOperate::GetRoomIdnumber();
        QString RoomState = "空闲";
        RoomInfo info;

        info.set_room_id(newRid);
        info.set_room_state(RoomState);
        info.set_room_name(ui->lineEdit2_roomname->text());
        info.set_room_type(ui->comboBox2_type->currentText());
        info.set_room_place(ui->comboBox2_floor->currentText());
        info.set_room_price(ui->lineEdit2_roomprice->text());
        info.set_room_discount(ui->lineEdit2_roomcount->text());
        info.set_room_call(ui->lineEdit2_roomcall->text());
        if(DataBaseOperate::CreateRoomInfo(info))
        {
            QString name = "添加房间成功";
            QString tips = "添加房间ID = " + newRid + " 房间名字为 :"+ui->lineEdit2_roomname->text() + "成功";
            QMessageBox::information(0,name,tips,QMessageBox::Ok);

            on_pushButton_clicked();
            clearAddDetail();
        }else
        {
            QString name = "添加房间失败";
            QString tips = "添加房间失败,可能是因为您输入的房间名已经存在";
            QMessageBox::information(0,name,tips,QMessageBox::Ok);
        }


    }
}
 void SettingRoom::clearDetail()
 {
    ui->lineEdit_roomcount->clear();
    ui->lineEdit_roomid->clear();
    ui->lineEdit_roomprice->clear();
    ui->lineEdit_roomcall->clear();
    ui->lineEdit_roomname->clear();
 }

 void SettingRoom::clearAddDetail()
 {
    ui->lineEdit2_roomcall->clear();
    ui->lineEdit2_roomcount->clear();
    ui->lineEdit2_roomname->clear();
    ui->lineEdit2_roomprice->clear();
 }
