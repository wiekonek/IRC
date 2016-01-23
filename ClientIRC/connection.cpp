#include "connection.h"
#include <QDebug>
#include <QtNetwork>
#include <QMessageBox>

Connection::Connection(QTcpSocket *tcpSocket, QObject *parent) : QObject(parent)
{
    this->tcpSocket = tcpSocket;

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadyToRead()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(Error(QAbstractSocket::SocketError)));

    qDebug() << ">New connection>"
             << "\n>>host:" << tcpSocket->localAddress().toString()
             << "\n>>local port: " << tcpSocket->localPort();
}

void Connection::SendMessage(IRCData::MessageData *message)
{
    Message *msg = new Message();
    msg->add(KEYS::CMD, MESSAGE);
    msg->add(KEYS::CHANNEL, message->channelName);
    msg->add(KEYS::TEXT, message->content);

    SendCommand(msg);
    delete msg;
}

void Connection::SendLoginRequest(IRCData::UserData *userData)
{
    Message *msg = new Message();
    msg->add(KEYS::CMD, LOGIN);
    msg->add(KEYS::USER, userData->username);
    msg->add(KEYS::PASSWORD, userData->password);

    SendCommand(msg);
    delete msg;
}

void Connection::SendCreateChannelRequest(IRCData::ChannelData *channelData)
{
    Message *msg = new Message();
    msg->add(KEYS::CMD, CREATE);
    msg->add(KEYS::CHANNEL, channelData->name);

    SendCommand(msg);
}

void Connection::SendJoinChannelRequest(IRCData::ChannelData *channelData)
{
    Message *msg = new Message();
    msg->add(KEYS::CMD, JOIN);
    msg->add(KEYS::CHANNEL, channelData->name);

    SendCommand(msg);
    delete msg;
}

void Connection::LeaveChannel(IRCData::ChannelData *channelData)
{
    Message *msg = new Message();
    msg->add(KEYS::CMD, LEAVE);
    msg->add(KEYS::CHANNEL, channelData->name);

    SendCommand(msg);
    delete msg;
}

void Connection::SendCommand(Message *message)
{
    tcpSocket->write(message->toByte());

}

void Connection::ReadyToRead()
{
    // TODO read from socket
    QByteArray dataArray = tcpSocket->readAll();
    Message *msg = new Message(dataArray);
    qDebug(">Command received: \n>>%s", msg->toChar());
    QString command = msg->getValue(KEYS::CMD);

    IRCData::MessageData *message;

    switch (command.toInt()) {
    case WELCOME:

        break;
    case LOGIN_ACC:
    {
        QString str = msg->getValue(KEYS::VALUE);
        bool *ok = new bool();
        *ok = str.toInt() == 0 ?  false : true;
        emit OnAcceptUser(ok);
    }
        break;
    case JOIN_ACC:
    {
        IRCData::ChannelData *channel = new IRCData::ChannelData();
        channel->name = msg->getValue(KEYS::CHANNEL);
        channel->users.append("admin");
        channel->users.append("user");
        emit OnConnectToChannel(channel);
    }
        break;
    case LEAVE_ACC:

        break;
    case CREATE_ACC:

        break;
    case MESSAGE:
        message = new IRCData::MessageData();
        message->channelName = msg->getValue(KEYS::CHANNEL);
        message->content = msg->getValue(KEYS::TEXT);
        message->username = msg->getValue(KEYS::USER);
        emit OnMessageReceived(message);
        break;
//    case ERROR:

//        break;
    }

}

void Connection::Error(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error:" << error;
    emit OnConnectionLost();
}
