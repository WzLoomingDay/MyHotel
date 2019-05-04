#ifndef SETTINGROOM_H
#define SETTINGROOM_H
#include "roominfo.h"
#include <QWidget>
#include "globalvar.h"
#include "roominfo.h"
#include "databaseoperate.h"
namespace Ui {
class SettingRoom;
}

class SettingRoom : public QWidget
{
    Q_OBJECT

public:
    explicit SettingRoom(QWidget *parent = 0);
    void updataTableWidget(int row);
    void clearDetail();
    void clearAddDetail();
    ~SettingRoom();

private slots:
    void on_pushButton_clicked();
    void slotShowRoomDetail(QModelIndex Mmodel);

    void on_pb_change_clicked();

    void on_pb_delete_clicked();

    void on_pb2_add_clicked();

private:
    Ui::SettingRoom *ui;
};

#endif // SETTINGROOM_H
