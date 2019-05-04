#ifndef MANGEROPERATE_H
#define MANGEROPERATE_H

#include <QWidget>
#include <QSplitter>
#include <QPushButton>
#include <QIcon>
#include <QPoint>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QListWidget>

#include <QList>
#include "usermange.h"
#include "settingroom.h"
#include "customermange.h"
#include "settingmeal.h"
#include "settingcount.h"
#include "srarchincom.h"


#define MAIN_HIGH 640
#define MAIN_WITH 1137
#define LIST_HIGH MAIN_HIGH
#define LIST_WITH 280
#define BUTTON_HIGH 44
#define BUTTON_WITH 40



namespace Ui {
class MangerOperate;
}

class MangerOperate : public QWidget
{
    Q_OBJECT


public:
    explicit MangerOperate(QWidget *parent = 0);
    ~MangerOperate();
private slots:
    void slotShowMangerLogin(const QString ID);
 private:



private:
    Ui::MangerOperate *ui;
    userMange * m_usermange;
    CustomerMange* m_customermange;
    SettingMeal *m_settingmeal;
    SettingRoom *m_settingroom;
    SettingCount *m_settingcount;
    SrarchIncom *m_searchincome;


};

#endif // MANGEROPERATE_H
