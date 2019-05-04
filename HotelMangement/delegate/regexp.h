#ifndef REGEXP_H
#define REGEXP_H
#include <QRegExp>
#include <QString>
#include<QObject>
class RegExp:public QObject
{
public:
    RegExp(QObject* parent = 0);
    ~RegExp();
    static bool JudgeRegExp(const QString &regx,const QString &input);
};

#endif // REGEXP_H
