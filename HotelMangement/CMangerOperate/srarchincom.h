#ifndef SRARCHINCOM_H
#define SRARCHINCOM_H

#include <QWidget>
#include <QList>
#include "qcustomplot.h"
#include "databaseoperate.h"


namespace Ui {
class SrarchIncom;
}

class SrarchIncom : public QWidget
{
    Q_OBJECT

public:
    explicit SrarchIncom(QWidget *parent = 0);
    ~SrarchIncom();
     void ShowBar(QList<int> data,int high,int with);
     void ShowDrawLine(QList<int> data,int high,int with);
     void clearPlot();
     void drawValue(int value,int x,int y);
private slots:
    void on_pb_searchyearmouth_clicked();

    void on_pb_searchyear_clicked();

    void on_pb_showlegend_clicked();


private:
    Ui::SrarchIncom *ui;
    QCustomPlot *m_customerplot;
    QPainter *m_painter;

};

#endif // SRARCHINCOM_H
