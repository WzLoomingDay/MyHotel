#ifndef EXECUSERCMD_H
#define EXECUSERCMD_H

#include <QObject>
#include <QTcpSocket>
#include "improtocol.h"
#include "customerinfo.h"
#include "databaseoperate.h"
#include "globalvar.h"


class ExecUserCmd : public QObject
{
    Q_OBJECT

signals:
    void signalSendMsgtoClient(QByteArray *buffer);
    void signalSendErrorMsgtoClient(QByteArray *buffer);
    void signalBookingRequest(CustomerInfo info);
   // void signalRecordChatInfo(const UserInfo &recvUser,
     //                         const UserInfo &sendUser,
       //                       const QString &msg);
public:
    ExecUserCmd(QTcpSocket *msocket);
    ~ExecUserCmd();

    void analysisProtocol(IMProtocol *protocol);

    void execErrorInfo(void);
    void execUserOperate(void);

    void execOperateCmdUser(void);

    ///
    /// \brief execOperateCmdLogin
    ///
    void execOperateCmdLogin(void);
    void execOperateCmdLoginAsk(void);
    void execOperateCmdExitAsk(void);
    void execOperateCmdRegisterAsk(void);


    void execOperateCmdUserBook(void);
    void execOperateCmdUserBookOk(void);
    void execOperateCmdUserChangeData(void);


private:
    IMProtocol *m_imProtocol;
    QTcpSocket *m_tcpsocket;
};

#endif // EXECUSERCMD_H
