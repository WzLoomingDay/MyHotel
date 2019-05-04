#ifndef ADDMEALS_H
#define ADDMEALS_H

#include <QWidget>
#include <QFont>
#include "databaseoperate.h"
#include <QMessageBox>
#include <QTreeWidgetItem>
#include "globalvar.h"
#include "mealinfo.h"

namespace Ui {
class AddMeals;
}

class AddMeals : public QWidget
{
    Q_OBJECT

public:
    ~AddMeals();
    static AddMeals* getAddMeals();
    void closeEvent(QCloseEvent *event = nullptr);
    void InitTreeWidget();
private slots:
    void on_PB_refresh_clicked();

    void slotShowAddMeals(QString ID);

    void slotItemChanged(QTreeWidgetItem *item, int column);

    void slotShowSlectUser(QString RID);

    void on_pushButton_clicked();

    void on_pB_EXIT_clicked();

private:
    explicit AddMeals(QWidget *parent = 0);
    static AddMeals * m_AddMeals;
    Ui::AddMeals *ui;
    QFont m_font;
    QFont m_ditalfont;
    QString m_meal;
    QString m_mealprice;
    int m_mealpriceInt;
    BillInfo m_selectbill;

};

#endif // ADDMEALS_H
