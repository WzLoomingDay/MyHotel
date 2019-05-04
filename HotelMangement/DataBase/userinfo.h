#ifndef USERINFO_H
#define USERINFO_H
#include <QString>
#include <QList>

class UserInfo
{
//enum UserPosition{Manger,Cashier,Waiter};
public:
    UserInfo();
    UserInfo(QString &id, QString &name,QString &type);
    void setID(const QString & ID);
    const QString &getID();
    void setPswd(const QString & PSWD);
    const QString &getPswd();
    void setType(const QString & TYPE);
    const QString &getType();
    void UpDateUserInfo(UserInfo &Info);
    ~UserInfo();
private:
    QString m_UserId;
    QString m_UserPswd;
    QString m_UserType;
};
typedef QList<UserInfo> ListUserInfo;
#endif // USERINFO_H
