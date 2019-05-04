#include "execusercmd.h"

#include <QDebug>
#include <QStringList>



ExecUserCmd::ExecUserCmd()
{
    //m_tcpsocket = msocket;
    m_imProtocol = new IMProtocol;
}

ExecUserCmd::~ExecUserCmd()
{
    delete m_imProtocol;
}

void ExecUserCmd::analysisProtocol(IMProtocol *protocol)
{
    m_imProtocol->initMsgPackage();
    m_imProtocol->updataMsg(protocol);
    m_imProtocol->printMsgInfo();
    execErrorInfo();
}

///
/// \brief ExecUserCmd::execErrorInfo
///
void ExecUserCmd::execErrorInfo(void)
{
    switch (m_imProtocol->getErrorInfo()) {
    case ERROR_INFO_NONE: execUserOperate(); break;
    case ERROR_INFO_DATA: execErrorData(); break;
    case ERROR_INFO_BUSY: break;
    default: break;
    }
}

void ExecUserCmd::execErrorData(void)
{
   emit signalSendErrorTips(m_imProtocol->getDataContent());
}

///
/// \brief ExecUserCmd::execUserOperate
///
void ExecUserCmd::execUserOperate(void)
{
    switch (m_imProtocol->getUserOperate()) {
    case USER_OPE_NONE: break;
    case USER_OPE_LOGIN: execOperateCmdLogin(); break;
    case USER_OPE_USER: execOperateCmdUser(); break;
    default: break;
    }
}

///
/// \brief ExecUserCmd::execOperateCmdLogin
///
void ExecUserCmd::execOperateCmdLogin(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_LOGIN_ASK: execOperateCmdLoginAsk(); break;
    case OPE_CMD_EXIT_ASK: execOperateCmdExitAsk(); break;
    case OPE_CMD_REGISTER_ASK: execOperateCmdRegisterAsk(); break;
    default: break;
    }
}


void ExecUserCmd::execOperateCmdLoginAsk(void)
{
    qDebug()<<"ExecUserCmd::execOperateCmdLoginAsk(void)"<<endl;
    QString data = m_imProtocol->getDataContent();
    qDebug()<<"data = "<<data<<endl;
    QStringList list = data.split("|");
    qDebug()<<"sizeof list"<<list.size()<<endl;
    for(int i = 0;i< list.size();i++)
    {
        qDebug()<<list[i]<<endl;
    }
    CustomerInfo info;
    info = info.setCustomerInfo(list);
    //qDebug()<<"emit signalLoginSuccess"<<endl;
    emit signalLoginSuccess(info);

    //qDebug()<<"ExecUserCmd::signalLoginSuccess(info);"<<endl;
}

void ExecUserCmd::execOperateCmdExitAsk(void)
{
     qDebug()<<"ExecUserCmd::execOperateCmdExitAsk(void)"<<endl;
}

void ExecUserCmd::execOperateCmdRegisterAsk(void)
{
     qDebug()<<"ExecUserCmd::execOperateCmdRegisterAsk(void)"<<endl;
   /* QStringList list = m_imProtocol->getDataContent().split("|");

    if(SQLAnalysis::insertRegisterInfo(list[0], list[1]))
    {
        if(SQLAnalysis::insertUserInfo(SQLAnalysis::m_registerUserTotal))
        {
            UserInfo *info = SQLAnalysis::selectUserInfo(
                        QString::number(SQLAnalysis::m_currentUserTotal));
            QString *msg = info->packageinfos();
            QByteArray *buffer =
                    m_imProtocol->updataMsg(1, ERROR_INFO_NONE,
                                          USER_OPE_LOGIN, OPE_CMD_REGISTER_ASK,
                                          MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                          MSG_DATA_LENGTH_NONE, *msg);
            emit signalSendMsgtoClient(buffer);
        }
    }*/
}

///
/// \brief ExecUserCmd::execOperateCmdUser
///
void ExecUserCmd::execOperateCmdUser(void)
{
    switch (m_imProtocol->getOperateCmd()) {
    case OPE_CMD_USER_BOOK: execOperateCmdUserBook(); break;

    case OPE_CMD_USER_BOOKOK: execOperateCmdUserBookOK(); break;
    case OPE_CMD_USER_CHANGEDATA: execOperateCmdUserChangeData(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdUserBook(void)
{
     qDebug()<<" ExecUserCmd::execOperateCmdUserBook(void)"<<endl;
}

void ExecUserCmd::execOperateCmdUserBookOK(void)
{
    qDebug()<<"ExecUserCmd::execOperateCmdUserBookOK(void)"<<endl;
    QString data = m_imProtocol->getDataContent();
    QStringList list = data.split("|");
    CustomerInfo info;
    info = info.setCustomerInfo(list);
    emit signalLoginSuccess(info);

}

void ExecUserCmd::execOperateCmdUserChangeData(void)
{
     qDebug()<<" ExecUserCmd::execOperateCmdUserChangeData(void)"<<endl;
}




