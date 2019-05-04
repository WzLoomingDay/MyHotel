#include "srarchincom.h"
#include "ui_srarchincom.h"
#include <qmessagebox.h>


SrarchIncom::SrarchIncom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SrarchIncom)
{
    ui->setupUi(this);
     m_customerplot = ui->widget_customplot;
     QStringList strlist;
     strlist << "01"<<"02"<<"03"<<"04"<<"05"<<"06"<<"07"<<"08"<<"09"
             <<"10"<<"11"<<"12";
     ui->comboBox_mouth->addItems(strlist);
     ui->comboBox_detail->addItem("柱形图");
     ui->comboBox_detail->addItem("折线图");

     m_painter = new QPainter(this);
}

SrarchIncom::~SrarchIncom()
{
    delete ui;
}


void SrarchIncom::on_pb_searchyearmouth_clicked()
{
    QString inputyear =  ui->line_YearYear->text();
    if(inputyear.length()!=4)
    {
        QString name = "格式错误";
        QString tips = inputyear+"不是正确的年份格式";
        QMessageBox::information(0,name,tips,QMessageBox::Ok);
    }else
    {
        QString data = ui->line_YearYear->text() +"-"+ui->comboBox_mouth->currentText();
        QList<int> m_daydata =  DataBaseOperate::SelectIncomeInfo(MOUTH,data);
        int max = m_daydata[0];

        for(int i = 0; i<m_daydata.size();i++)
        {
            qDebug()<<"第"<<i+1<<"天 收入"<<m_daydata[i]<<endl;
            if(max < m_daydata[i])
            {
                max = m_daydata[i];
            }
        }
        int high = max+max*0.2;
        int with = m_daydata.size()+1;

         if(ui->comboBox_detail->currentText() == "柱形图")
         {
              ShowBar(m_daydata,high,with);
         }else if(ui->comboBox_detail->currentText() == "折线图")
         {
              ShowDrawLine(m_daydata,high,with);
         }
    }
    //qDebug()<<ui->line_Year->text()<<endl;


}


void SrarchIncom::on_pb_searchyear_clicked()
{
    qDebug()<<ui->line_Year->text()<<endl;
    QList<int> m_mouthdata =  DataBaseOperate::SelectIncomeInfo(YEAR,ui->line_Year->text());
    int max = m_mouthdata[0];
    for(int i = 0; i<m_mouthdata.size();i++)
    {

        qDebug()<<"第"<<i+1<<"月 收入"<<m_mouthdata[i]<<endl;

        if(max < m_mouthdata[i])
        {
            max = m_mouthdata[i];
        }
    }
    int high = max+max*0.2;
    int with = m_mouthdata.size()+1;
    if(ui->comboBox_detail->currentText() == "柱形图")
    {
         ShowBar(m_mouthdata,high,with);
    }else if(ui->comboBox_detail->currentText() == "折线图")
    {
         ShowDrawLine(m_mouthdata,high,with);
    }

}

void SrarchIncom::on_pb_showlegend_clicked()
{
    if(ui->pb_showlegend->text() == "关闭图例")
    {
        m_customerplot->legend->setVisible(false);
         m_customerplot->replot();
        ui->pb_showlegend->setText("查看图例");
    }else
    {
        m_customerplot->legend->setVisible(true);
         m_customerplot->replot();
        ui->pb_showlegend->setText("关闭图例");
    }

}

void SrarchIncom::ShowBar(QList<int> data,int high,int with)
{

     clearPlot();

     QLinearGradient gradient(0, 0, 0, 400);
     gradient.setColorAt(0, QColor(36,138,159));
     gradient.setColorAt(0.38, QColor(47,180,207));
     gradient.setColorAt(1, QColor(53,205,236));
     m_customerplot->setBackground(QBrush(gradient));//设置背景渐变色

     QCPBars *BarPlot = new QCPBars(m_customerplot->xAxis, m_customerplot->yAxis);//画柱状图

     BarPlot->setAntialiased(false); //取消反锯齿 gives more crisp, pixel aligned bar borders

     BarPlot->setName("营业额");
     BarPlot->setPen(QPen(QColor(205,19,37).lighter(130)));
     BarPlot->setBrush(QColor(255,31,53));
     int m_size = data.size();
     qDebug()<<"size = "<<m_size<<endl;
      QVector<double> ticks;
       qDebug()<<"ticks size = "<<ticks.size()<<endl;
      QVector<QString> labels;
     if(m_size == 12)
     {

         ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7<< 8 << 9 << 10 << 11 << 12;
         labels << "一月" << "二月" << "三月" << "四月" << "五月" << "六月" << "七月"
                    << "八月" << "九月" << "十月" << "十一月" << "十二月";
         qDebug()<<"msize mouth"<<ticks.size()<<labels.size()<<endl;
     }else
     {
          QVariant temp;
          for(int i = 0;i<m_size;i++)
          {
            ticks <<i;
            temp = i+1;
            labels<< temp.toString();
          }
          qDebug()<<"msize mouth"<<ticks.size()<<labels.size()<<endl;

     }
     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
     textTicker->addTicks(ticks, labels);
     m_customerplot->xAxis->setTicker(textTicker);
     m_customerplot->xAxis->setTickLabelRotation(30);//设置标签角度旋转
     m_customerplot->xAxis->setSubTicks(false);
     m_customerplot->xAxis->setTickLength(0, 4);
     m_customerplot->xAxis->setRange(0, with);
     m_customerplot->xAxis->setBasePen(QPen(Qt::white));
     m_customerplot->xAxis->setTickPen(QPen(Qt::white));
     m_customerplot->xAxis->grid()->setVisible(true);//设置网格是否显示
     m_customerplot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
     m_customerplot->xAxis->setTickLabelColor(Qt::white);//设置标记标签颜色
     m_customerplot->xAxis->setLabelColor(Qt::white);

     // prepare y axis:
     m_customerplot->yAxis->setRange(0,high);
     m_customerplot->yAxis->setPadding(5); // a bit more space to the left border设置左边留白
     m_customerplot->yAxis->setLabel("营业额");
     m_customerplot->yAxis->setBasePen(QPen(Qt::white));
     m_customerplot->yAxis->setTickPen(QPen(Qt::white));
     m_customerplot->yAxis->setSubTickPen(QPen(Qt::white));
     m_customerplot->yAxis->grid()->setSubGridVisible(true);
     m_customerplot->yAxis->setTickLabelColor(Qt::white);
     m_customerplot->yAxis->setLabelColor(Qt::white);
     m_customerplot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
     m_customerplot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

     QVector<double> InComeData;
     for(int i = 0;i<data.size();i++)
     {
        InComeData<<data[i];
       drawValue(InComeData[i],ticks[i],InComeData[i]);
     }
     BarPlot->setData(ticks, InComeData);

     m_customerplot->legend->setVisible(true);
     m_customerplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
     m_customerplot->legend->setBrush(QColor(255, 255, 255, 100));
     m_customerplot->legend->setBorderPen(Qt::NoPen);
     QFont legendFont = font();
     legendFont.setFamily("楷体");
     legendFont.setPointSize(10);
     m_customerplot->legend->setFont(legendFont);
     m_customerplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
     //m_customerplot->setFocus();
     m_customerplot->replot();
}

 void SrarchIncom::ShowDrawLine(QList<int> data,int high,int with)
 {
    clearPlot();


    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0,QColor(15,15,15));
    gradient.setColorAt(0.38, QColor(61,61,61));
    gradient.setColorAt(1,QColor(107,107,107));
    m_customerplot->setBackground(QBrush(gradient));//设置背景渐变色
    int m_size = data.size();
    qDebug()<<"size = "<<m_size<<endl;
    QVector<double> ticks;
    qDebug()<<"ticks size = "<<ticks.size()<<endl;
    QVector<QString> labels;
    if(m_size == 12)
    {

        ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7<< 8 << 9 << 10 << 11 << 12;
        labels << "一月" << "二月" << "三月" << "四月" << "五月" << "六月" << "七月"
                   << "八月" << "九月" << "十月" << "十一月" << "十二月";
        qDebug()<<"msize mouth"<<ticks.size()<<labels.size()<<endl;
    }else
    {
         QVariant temp;
         for(int i = 0;i<m_size;i++)
         {
           ticks <<i;
           temp = i+1;
           labels<< temp.toString();
         }
         qDebug()<<"msize mouth"<<ticks.size()<<labels.size()<<endl;

    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks,labels);
    m_customerplot->xAxis->setRange(0, with);
    m_customerplot->xAxis->setTicker(textTicker);
    m_customerplot->xAxis->setTickLabelRotation(0);//设置标签角度旋转
    m_customerplot->xAxis->setSubTicks(false);
    m_customerplot->xAxis->setTickLength(0, 4);
    m_customerplot->xAxis->setBasePen(QPen(Qt::white));
    m_customerplot->xAxis->setTickPen(QPen(Qt::white));
    m_customerplot->xAxis->grid()->setVisible(true);//设置网格是否显示
    m_customerplot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    m_customerplot->xAxis->setTickLabelColor(QColor(255,215,0));//设置标记标签颜色
    m_customerplot->xAxis->setLabelColor(Qt::white);


    m_customerplot->yAxis->setRange(0,high);
    m_customerplot->yAxis->setPadding(5); // a bit more space to the left border设置左边留白
    m_customerplot->yAxis->setLabel("营业额");
    m_customerplot->yAxis->setBasePen(QPen(Qt::white));
    m_customerplot->yAxis->setTickPen(QPen(Qt::white));
    m_customerplot->yAxis->setSubTickPen(QPen(Qt::white));
    m_customerplot->yAxis->grid()->setSubGridVisible(true);
    m_customerplot->yAxis->setTickLabelColor(Qt::white);
    m_customerplot->yAxis->setLabelColor(Qt::white);
    m_customerplot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    m_customerplot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    QCPGraph * curGraph = new QCPGraph(m_customerplot->xAxis, m_customerplot->yAxis);


    curGraph->setName("营业额");
    curGraph->setPen(QPen(QColor(255,215,0)));
    curGraph->setLineStyle(QCPGraph::lsLine);
    curGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    QVector<double> InComeData;
    for(int i = 0;i<data.size();i++)
    {
       InComeData<<data[i];
       drawValue(InComeData[i],ticks[i],InComeData[i]);
    }
    curGraph->setData(ticks,InComeData);
    m_customerplot->replot();


 }

 void SrarchIncom::clearPlot()
 {
     int plottableCount = m_customerplot->plottableCount();
         if (plottableCount != 0)
              m_customerplot->clearPlottables();
 }

 void SrarchIncom::drawValue(int value,int x,int y)
 {

    /* QVariant temp = value;
     //QCPItemText text;
     //text.setText("haha");
     QCPItemRect rect;

     rect.topLeft = x;
     rect.topRight = x+50;
     rect.bottomLeft = y;
     rect.bottomRight = y+50;
     rect.setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
     //QRectF rect(x,y,x+50,y+50);
    // m_painter->drawText(x,y,temp.toString());
    // qDebug()<<"drawText = "<<x<<y<<temp.toString()<<endl;
*/
 }
