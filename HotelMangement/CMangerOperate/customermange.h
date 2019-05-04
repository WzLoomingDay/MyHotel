#ifndef CUSTOMERMANGE_H
#define CUSTOMERMANGE_H

#include <QWidget>
#include "customerinfo.h"
#include "globalvar.h"
#include "databaseoperate.h"

namespace Ui {
class CustomerMange;
}

class CustomerMange : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerMange(QWidget *parent = 0);
    ~CustomerMange();

private slots:
    void on_pb_check_clicked();
    void updateTabWidget(QString mcid);

    void on_pb_searchid_clicked();

private:
    Ui::CustomerMange *ui;
};

#endif // CUSTOMERMANGE_H
