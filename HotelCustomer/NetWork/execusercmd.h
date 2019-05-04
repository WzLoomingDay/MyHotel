#ifndef EXECUSERCMD_H
#define EXECUSERCMD_H

#include <QObject>
#include "improtocol.h"
#include "customerinfo.h"
#include <QTcpSocket>


class ExecUserCmd : public QObject
{
    Q_OBJECT

signals:
 //   void signalSendMsgtoClient(QByteArray *buffer);
   // void signalRecordChatInfo(const UserInfo &recvUser,
     //                         const UserInfo &sendUser,
       //                       const QString &msg);
    void signalSendErrorTips(QString error);
    void signalLoginSuccess(CustomerInfo info);

public:
    ExecUserCmd();
    ~ExecUserCmd();
    void analysisProtocol(IMProtocol *protocol);

    void execErrorInfo(void);
    void execErrorData(void);
    void execUserOperate(void);

    void execOperateCmdUser();


    ///
    /// \brief execOperateCmdLogin
    ///
    void execOperateCmdLogin(void);
    void execOperateCmdLoginAsk(void);
    void execOperateCmdExitAsk(void);
    void execOperateCmdRegisterAsk(void);

    void execOperateCmdUserBook(void);
    void execOperateCmdUserBookOK(void);
    void execOperateCmdUserChangeData(void);


private:
    IMProtocol *m_imProtocol;

};

#endif // EXECUSERCMD_H
