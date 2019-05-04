#ifndef WORKERINFO_H
#define WORKERINFO_H
#include<QList>
#include "userinfo.h"

class WorkerInfo:public UserInfo
{
public:
    WorkerInfo();
    WorkerInfo(QString WorkerName, QString WorkerSex,
                QString WorkerJoinTime, QString WorkerCall,
                QString WorkerSalary);
    ~WorkerInfo();
    //bool operator = (WorkerInfo &dest, WorkerInfo &source);
    //bool operator == (WorkerInfo &info1, WorkerInfo &info2);
    void SetWorkerName(const QString &name);
    void SetWorkerSex(const QString &sex);
    void SetWorkerJoinTime(const QString &JoinTime);
    void SetWorkerCall(const QString &Call);
    void SetWorkerSalary(const QString &Salary);
    void SetWorkerBirth(const QString &birth);

    const QString &GetWorkerID();
    const QString &GetWorkerPsswd();
    const QString &GetWorkerType();
    const QString &GetWorkerBirth();
    const QString &GetWorkerName();
    const QString &GetWorkerSex();
    const QString &GetWorkerJoinTime();
    const QString &GetWorkerCall();
    const QString &GetWorkerSalary();

private:
    QString m_WorkerID;
    QString m_WorkPsswd;
    QString m_WorkTypeName;
    QString m_WorkerName;
    QString m_WorkerSex;
    QString m_WorkerJoinTime;
    QString m_WorkerCall;
    QString m_WorkerSalary;
    QString m_WorkerBirth;
};
typedef QList<WorkerInfo> WorkerInfoList;

#endif // WORKERINFO_H
