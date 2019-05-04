#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include "databaseoperate.h"
#include "globalvar.h"

namespace Ui {
class History;
}

class History : public QWidget
{
    Q_OBJECT

public:
    void closeEvent(QCloseEvent *event = nullptr);
    static History * GetHistory();
    ~History();
private slots:
    void on_pb_search_clicked();
    void slotShowHistory(QString ID);

private:
     explicit History(QWidget *parent = 0);
    static History * m_History;
    Ui::History *ui;
};

#endif // HISTORY_H
