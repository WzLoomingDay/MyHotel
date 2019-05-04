#ifndef MEALINFO_H
#define MEALINFO_H
#include "getsetmethod.h"
#include <QString>
#include <QList>
class MealInfo
{
public:
    MealInfo();
    MealInfo(int mealid,QString meal_name,QString meal_type,QString meal_price);
private:
    int m_mealid;
    QString m_mealname;
    QString m_mealtype;
    QString m_mealprice;
    PropertyBuilderByName(int,m_mealid)
    PropertyBuilderByName(QString,m_mealname)
    PropertyBuilderByName(QString,m_mealtype)
    PropertyBuilderByName(QString,m_mealprice)
};
typedef QList<MealInfo> ListMealInfo;
#endif // MEALINFO_H
