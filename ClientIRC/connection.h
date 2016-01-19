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
    explicit Connection(QTcpSocket *tcpSocket, QObject *parent = 0);

//#define LOGIN 0
//#define CREATE 1
//#define JOIN 2
//#define LEAVE 3
//#define MESSAGE 4
//#define DISCONNECT 5

//#define LOGIN_ACC 6
//#define CREATE_ACC 7
//#define JOIN_ACC 8
//#define LEAVE_ACC 9
//#define ERROR 20

signals:
    void OnMessageReceived(IRCData::ChannelMessageData *message);
    void OnAcceptUser();
    void OnConnectToChannel(IRCData::ChannelData *channelData);
    void OnLeaveChannel(IRCData::ChannelData *channelData);
    void OnConnectionLost();
    void OnError();

public slots:
    void SendMessage(IRCData::ChannelMessageData *message);
    void SendCommand(Message *message);

private slots:
    void ReadyToRead();
    void Error(QAbstractSocket::SocketError error);

private:
    QTcpSocket *tcpSocket;
};

#endif // CONNECTION_H
