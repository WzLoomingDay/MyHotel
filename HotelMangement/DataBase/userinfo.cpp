#include "userinfo.h"
UserInfo::UserInfo()
{
        m_UserId.clear();
        m_UserPswd.clear();
        m_UserType.clear();
}
UserInfo::UserInfo(QString &id,QString &passwd,QString &type)
:m_UserId(id),
m_UserPswd(passwd),
m_UserType(type)
{
}
void UserInfo::setID(const QString &ID)
{
    m_UserId = ID;
}
void UserInfo::setPswd(const QString &PSWD)
{
    m_UserPswd = PSWD;
}
void UserInfo::setType(const QString &TYPE)
{
    m_UserType = TYPE;
}

const QString &UserInfo::getID()
{
    return m_UserId;
}
const QString &UserInfo::getPswd()
{
    return m_UserPswd;
}
const QString &UserInfo::getType()
{
    return m_UserType;
}
void UserInfo::UpDateUserInfo(UserInfo &Info)
{

}

UserInfo::~UserInfo()
{

}
