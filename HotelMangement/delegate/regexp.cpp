#include "regexp.h"
#include<QDebug>
RegExp::RegExp(QObject* parent):QObject(parent)
{

}

RegExp::~RegExp()
{
}
bool RegExp::JudgeRegExp(const QString &regxStr,const QString &input)
{
    QRegExp mRegx(regxStr);
    if(mRegx.exactMatch(input))
    {
        qDebug()<<"regx true"<<endl;
        return true;
    }else
    {
         qDebug()<<"regx false"<<endl;
        return false;
    }
}
