#ifndef IMPROTOCOL_H
#define IMPROTOCOL_H

#include <QByteArray>
#include <QString>
#include <QDataStream>


#define MSG_USER_ID_NONE 0
#define MSG_USER_HOST_NONE 0
#define MSG_CMD_NULL_NONE 0
#define MSG_DATA_LENGTH_NONE 0

/*错误信息定义*/
enum ERROR_INFO{
    ERROR_INFO_NONE = 0,
    ERROR_INFO_DATA,
    ERROR_INFO_BUSY,
};

/*用户操作定义*/
enum USER_OPE{
    USER_OPE_NONE = 0,
    USER_OPE_LOGIN,
    USER_OPE_USER,
};

/*操作命令定义*/
enum OPE_CMD_LOGIN{
    OPE_CMD_LOGIN_ASK = 1,
    OPE_CMD_EXIT_ASK,
    OPE_CMD_REGISTER_ASK
};

enum OPE_CMD_USER{
    OPE_CMD_USER_BOOK = 1,
    OPE_CMD_USER_BOOKOK,
    OPE_CMD_USER_CHANGEDATA
};

class IMProtocol
{
public:
    IMProtocol();
    void initMsgPackage(void);
    void clearMsgPackage();
    void printMsgInfo(void);
    void updataMsg(IMProtocol *protocol);//更新数据的两种方式
    QByteArray * updataMsg(const quint32 msgid, const quint8 errorinfo,
                                      const quint8 useroperate, const quint8 operatecmd,
                                      const quint16 recvhost, const quint16 sendhost,
                                      const quint16 datalength, const QString datacontent);

    QByteArray *packageMsg(void);
    void unpackageMsg(QDataStream &in);
    quint32 getMsgID(void) const;
    void setMsgID(const quint32 msgid);
    quint8 getErrorInfo(void) const;
    void setErrorInfo(const quint8 errorinfo);
    quint8 getUserOperate(void) const;
    void setUserOperate(const quint8 useroperate);
    quint8 getOperateCmd(void) const;
    void setOperateCmd(const quint8 operatecmd);
    quint16 getRecvHost(void) const;
    void setRecvHost(const quint16 recvhost);
    quint16 getSendHost(void) const;
    void setSendHost(const quint16 sendhost);
    quint16 getDataLength(void) const;
    void setDataLength(const quint16 datalength);
    const QString &getDataContent(void) const;
    void setDataContent(const QString dataContent);
private:
    quint32 m_MsgID;//
    quint8 m_ErrorInfo;//会收到错误信息
    quint8 m_UserOperate;//查看操作
    quint8 m_OperateCmd;//操作命令
    quint16 m_RecvHost;//
    quint16 m_SendHost;//
    quint16 m_DataLength;//数据长度
    QString m_DataContent;//数据内容

};

#endif // IMPROTOCOL_H
