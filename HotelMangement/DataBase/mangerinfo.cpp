#include "mangerinfo.h"

MangerInfo::MangerInfo(QString MangerName, QString MangerCall, QString MangerSex):
m_MangerName(MangerName),m_MangerCall(MangerCall),m_MangerSex(MangerSex)
{

}
MangerInfo::MangerInfo()
{

}
void MangerInfo::SetMangerName(const QString &name)
{
    m_MangerName = name;
}
void MangerInfo::SetMangerSex(const QString &sex)
{
    m_MangerSex = sex;
}
void MangerInfo::SetMangerCall(const QString &Call)
{
    m_MangerCall = Call;
}

const QString &MangerInfo::GetMangerID()
{
    return this->getID();
}
const QString &MangerInfo::GetMangerName()
{
    return m_MangerName;
}
const QString &MangerInfo::GetMangerCall()
{
    return m_MangerCall;
}
const QString &MangerInfo::GetMangerSex()
{
    return m_MangerSex;
}



