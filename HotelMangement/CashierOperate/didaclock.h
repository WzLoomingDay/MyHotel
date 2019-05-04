#ifndef DIDACLOCK_H
#define DIDACLOCK_H
#include <QLCDNumber>
#include <QPalette>
#include <QTimer>
#include <QTime>
#include <QDate>
#include "databaseoperate.h"

class DiDaClock:public QLCDNumber
{
    Q_OBJECT
public:
    DiDaClock(QWidget *parent=0);
private slots:
    void slotshowtime();

private:
    QTimer *timer;
    QPalette m_p;
    QString m_old_day;

};

#endif // DIDACLOCK_H
