#include "execusercmd.h"

#include <QDebug>
#include <QStringList>



ExecUserCmd::ExecUserCmd(QTcpSocket *msocket)//参数是为了给主线程传参的时候告诉主线程自己的地址
{
    qDebug()<<"m_socket 222222222222222222222"<<msocket<<endl;
    m_tcpsocket = msocket;
    m_imProtocol = new IMProtocol;


}

ExecUserCmd::~ExecUserCmd()
{
    delete m_imProtocol;
}

void ExecUserCmd::analysisProtocol(IMProtocol *protocol)
{
    m_imProtocol->updataMsg(protocol);//先更新协议
    m_imProtocol->printMsgInfo();
    execErrorInfo();//进入处理函数
}

///
/// \brief ExecUserCmd::execErrorInfo
///
void ExecUserCmd::execErrorInfo(void)
{
    switch (m_imProtocol->getErrorInfo()) {
    case ERROR_INFO_NONE: execUserOperate(); break;
    case ERROR_INFO_DATA: break;
    case ERROR_INFO_BUSY: break;
    default: break;
    }
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

    QStringList list = m_imProtocol->getDataContent().split("|");//先获取内容
    GlobalVar::m_customerInfoList.clear();
    GlobalVar::m_customerInfoList = DataBaseOperate::SelectCustomerInfo(list[0]);
    if(GlobalVar::m_customerInfoList.size() == 0)
    {
         qDebug()<<"无此用户"<<endl;
        QString error = "无此用户";
        QByteArray *buffer =
                m_imProtocol->updataMsg(1, ERROR_INFO_DATA,
                                      USER_OPE_LOGIN, OPE_CMD_LOGIN_ASK,
                                      MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                      error.size(), error);

        emit signalSendErrorMsgtoClient(buffer);
    }else if(GlobalVar::m_customerInfoList.size() == 1)//如果有这个用户
    {
        CustomerInfo info = GlobalVar::m_customerInfoList[0];//找到用户信息
        if(info.getm_pswd() == list[1])//密码正确
        {
            info.setm_addr(list[2]);
            info.setm_port(list[3]);
            DataBaseOperate::updateCustomerInfo(info);
            QString *msg = info.packageinfos();//打包用户信息
            QByteArray *buffer =
                    m_imProtocol->updataMsg(1, ERROR_INFO_NONE,
                                          USER_OPE_LOGIN, OPE_CMD_LOGIN_ASK,
                                          MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                          msg->size(), *msg);

            emit signalSendMsgtoClient(buffer);//给客户端发送用户信息
        }else//账号正确密码错误
        {
            qDebug()<<"账号正确密码错误"<<endl;
             QString error = "密码错误";
            QByteArray *buffer =
                    m_imProtocol->updataMsg(1, ERROR_INFO_DATA,
                                          USER_OPE_LOGIN, OPE_CMD_LOGIN_ASK,
                                          MSG_USER_HOST_NONE, MSG_USER_HOST_NONE,
                                          error.size(), error);

            emit signalSendErrorMsgtoClient(buffer);//给客户端发送错误信息
        }

    }
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

    case OPE_CMD_USER_BOOKOK: execOperateCmdUserBookOk(); break;
    case OPE_CMD_USER_CHANGEDATA: execOperateCmdUserChangeData(); break;
    default: break;
    }
}

void ExecUserCmd::execOperateCmdUserBook(void)
{
    qDebug()<<" ExecUserCmd::execOperateCmdUserBook(void)"<<endl;
    QString data = m_imProtocol->getDataContent();
    qDebug()<<" data = "<<data<<endl;
    QStringList list = data.split("|");
    GlobalVar::m_customerInfoList.clear();
    GlobalVar::m_customerInfoList = DataBaseOperate::SelectCustomerInfo(list[0]);
    CustomerInfo info  = GlobalVar::m_customerInfoList[0];
    info.setmSocket(m_tcpsocket);
    if(list[1] == "预定")
    {
       // qDebug()<<"list[1] == 预定 flag = "<<info.getm_flag()<<endl;
        if(info.getm_flag() == "0")
        {
            info.setm_flag(BOOKING_WAIT);//
            info.setm_roomtype(list[2]);//要预定的房间类型
            if(!DataBaseOperate::updateCustomerInfo(info))
            {
                qDebug()<<"ExecUserCmd::execOperateCmdUserBook(void) error"<<endl;
            }else
            {
                qDebug()<<"emit signalBookingRequest(info);"<<endl;
                emit signalBookingRequest(info);
            }

        }
    }
}

void ExecUserCmd::execOperateCmdUserBookOk(void)
{
    qDebug()<<"ExecUserCmd::execOperateCmdUserBookOK(void)"<<endl;

   // emit signalSendMsgtoClient();
}

void ExecUserCmd::execOperateCmdUserChangeData(void)
{
     qDebug()<<" ExecUserCmd::execOperateCmdUserChangeData(void)"<<endl;
}




