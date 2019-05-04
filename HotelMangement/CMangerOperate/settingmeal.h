#ifndef SETTINGMEAL_H
#define SETTINGMEAL_H

#include <QWidget>
#include "databaseoperate.h"
#include "mealinfo.h"
#include "globalvar.h"

namespace Ui {
class SettingMeal;
}

class SettingMeal : public QWidget
{
    Q_OBJECT

public:
    explicit SettingMeal(QWidget *parent = 0);
    ~SettingMeal();
    void clearMealDetail();
    void clearMealAdd();
private slots:
     void updateMealList(QString type);
     void slotClickedTable(QModelIndex index);
     void on_PB_change_clicked();

     void on_PB_delete_clicked();

     void on_PB_add_clicked();

private:
    Ui::SettingMeal *ui;
};

#endif // SETTINGMEAL_H
