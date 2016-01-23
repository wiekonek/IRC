#ifndef CONNECTION_H
#define CONNECTION_H

#define LOGIN 0
#define CREATE 1
#define JOIN 2
#define LEAVE 3
#define MESSAGE 4
#define DISCONNECT 5

#define LOGIN_ACC 6
#define CREATE_ACC 7
#define JOIN_ACC 8
#define LEAVE_ACC 9
#define WELCOME 10
#define ERROR

#include <QObject>
#include <QtNetwork>

#include "message.h"
#include "datastructures.h"


class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket *tcpSocket, QObject *parent = 0);

signals: //messages from server
    void OnMessageReceived(IRCData::MessageData *message);
    void OnAcceptUser(bool *ok);
    void OnConnectToChannel(IRCData::ChannelData *channelData);
    void OnLeaveChannel(IRCData::ChannelData *channelData);
    void OnConnectionLost();
    void OnError();

public slots: //messages to server
    void SendMessage(IRCData::MessageData *message);
    void SendLoginRequest(IRCData::UserData *userData);
    void SendCreateChannelRequest(IRCData::ChannelData *channelData);
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
