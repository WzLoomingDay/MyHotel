#include "workerinfo.h"

WorkerInfo::WorkerInfo()
{

}
WorkerInfo::WorkerInfo(QString WorkerName, QString WorkerSex,
                         QString WorkerJoinTime,QString WorkerCall,
                         QString WorkerSalary):
m_WorkerName(WorkerName),m_WorkerSex(WorkerSex),m_WorkerJoinTime(WorkerJoinTime),
m_WorkerCall(WorkerCall),m_WorkerSalary(WorkerSalary)
{

}
WorkerInfo::~WorkerInfo()
{

}
/*bool WorkerInfo::operator=(WorkerInfo &dest,WorkerInfo &source)
{
    if(dest == source)
    {
        return false;
    }else
    {
    dest.setID(source.getID());
    dest.setPswd(source.getPswd());
    dest.setType(source.getType());
    dest.m_WorkerCall = source.m_WorkerCall;
    dest.m_WorkerName = source.m_WorkerName;
    dest.m_WorkerSex = source.m_WorkerSex;
    dest.m_WorkerSalary = source.m_WorkerSalary;
    dest.m_WorkerJoinTime = source.m_WorkerJoinTime;
    return true;
    }
}*/
/*bool WorkerInfo::operator==(WorkerInfo &info1,WorkerInfo &info2)
{
    QString str1 = info1.getID()+info1.getPswd()+info1.getType()+
            info1.GetWorkerCall()+info1.GetWorkerID()+info1.GetWorkerJoinTime()+
            info1.GetWorkerName()+info1.GetWorkerSalary()+info1.GetWorkerSex();
    QString str2 = info2.getID()+info2.getPswd()+info2.getType()+
            info2.GetWorkerCall()+info2.GetWorkerID()+info2.GetWorkerJoinTime()+
            info2.GetWorkerName()+info2.GetWorkerSalary()+info2.GetWorkerSex();

   if(str1 == str2)
   {
       return false;
   }else
   {
       return true;
   }
}*/
void WorkerInfo::SetWorkerName(const QString &name)
{
    m_WorkerName = name;
}
void WorkerInfo::SetWorkerSex(const QString &sex)
{
    m_WorkerSex = sex;
}
void WorkerInfo::SetWorkerJoinTime(const QString &JoinTime)
{
    m_WorkerJoinTime = JoinTime;
}
void WorkerInfo::SetWorkerCall(const QString &Call)
{
    m_WorkerCall = Call;
}
void WorkerInfo::SetWorkerSalary(const QString &Salary)
{
    m_WorkerSalary = Salary;
}
void WorkerInfo::SetWorkerBirth(const QString &birth)
{
    m_WorkerBirth = birth;
}

const QString & WorkerInfo::GetWorkerID()
{
    return this->getID();
}
const QString &WorkerInfo::GetWorkerPsswd()
{
     return this->getPswd();
}
const QString &WorkerInfo::GetWorkerType()
{
     return this->getType();
}
const QString &WorkerInfo::GetWorkerBirth()
{
     return m_WorkerBirth;
}
const QString &WorkerInfo::GetWorkerName()
{
    return m_WorkerName;
}
const QString &WorkerInfo::GetWorkerSex()
{
    return m_WorkerSex;
}
const QString &WorkerInfo::GetWorkerJoinTime()
{
    return m_WorkerJoinTime;
}
const QString &WorkerInfo::GetWorkerCall()
{
    return m_WorkerCall;
}
const QString &WorkerInfo::GetWorkerSalary()
{
    return m_WorkerSalary;
}

