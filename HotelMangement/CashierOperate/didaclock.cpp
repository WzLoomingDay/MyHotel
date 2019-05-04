#include "didaclock.h"
#include <QDebug>
#include <QVariant>
#include <QMessageBox>
DiDaClock::DiDaClock(QWidget *parent):QLCDNumber(8,parent)
{
  m_p=palette();//QWidget::palette()获取当前面板,通过该值改变面板
  m_p.setColor(QPalette::Window, Qt::transparent);//改变控件背景色
  m_p.setColor(QPalette::WindowText,Qt::blue);//改变控件字体颜色
  this->setPalette(m_p);//改变属性
  setWindowFlags(Qt::FramelessWindowHint);//设置无边框
  setWindowOpacity(0.8);//设置透明度
  m_old_day =  DataBaseOperate::GetRecentday();//取得数据库中的最大日期
  if(m_old_day == "null")
  {
      QString tips = "日期查询错误，请立即关闭程序联系相关人员";
      QString name = "严重错误";
      QMessageBox::warning(this,name,tips,QMessageBox::Ok);
  }
  timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(slotshowtime()));
  timer->start(1000);
  slotshowtime();

}
void DiDaClock::slotshowtime()//完成功能1.更新显示面板上的时间，判断是否过了当天，如果过了就添加一个新表
{

      QTime time = QTime::currentTime();
      QString text = time.toString("hh:mm:ss");
      //qDebug() << "h m s: "<<text;
      text[2]=':';
      text[5]=':';
      this->display(text);//显示
      QDate date = QDate::currentDate();

      QVariant dateint = date.day();
      if(m_old_day != dateint.toString())
      {
         //qDebug()<<"m_old_day != dateint.toString()"<<endl;
          DataBaseOperate::CreateIncomeInfo(date.toString("yyyy-MM-dd"));//插入新数据
          m_old_day = dateint.toString();
          DataBaseOperate::ResetPayID();
      }

}
