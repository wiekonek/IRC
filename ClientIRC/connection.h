#ifndef CONNECTION_H
#define CONNECTION_H


#include <QObject>
#include <QtNetwork>
//#include <QByteArray>

#include "message.h"
#include "datastructures.h"


class Connection : public QObject
{
    Q_OBJECT
public:
//    static const QString KEY_CMD;
//    static const QString KEY_USER;
//    static const QString KEY_PUBLIC;
//    static const QString KEY_PASSWORD;
//    static const QString KEY_TEXT;
//    static const QString KEY_TYPE;
//    static const QString KEY_CHANNEL;

    explicit Connection(QTcpSocket *tcpSocket, QObject *parent = 0);

signals: //messages from server
    void OnMessageReceived(IRCData::MessageData *message);
    void OnAcceptUser();
    void OnConnectToChannel(IRCData::ChannelData *channelData);
    void OnLeaveChannel(IRCData::ChannelData *channelData);
    void OnConnectionLost();
    void OnError();

public slots: //messages to server
    void SendMessage(IRCData::MessageData *message);
    void SendLoginRequest(IRCData::UserData *userData);
    void SendJoinChannelRequest(IRCData::ChannelData *channelData);
    void LeaveChannel(IRCData::ChannelData *channelData);

private slots:
    void ReadyToRead();
    void Error(QAbstractSocket::SocketError error);

private:
    QTcpSocket *tcpSocket;
    void SendCommand(Message *message);
};

#endif // CONNECTION_H
