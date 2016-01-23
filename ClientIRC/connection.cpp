#include "connection.h"
#include <QDebug>
#include <QtNetwork>
#include <QMessageBox>

//const QString Connection::KEYS::CMD = "command";
//const QString Connection::KEYS::USER = "user";
//const QString Connection::KEYS::PUBLIC = "public";
//const QString Connection::KEYS::PASSWORD = "password";
//const QString Connection::KEYS::TEXT = "text";
//const QString Connection::KEYS::TYPE = "type";
//const QString Connection::KEYS::CHANNEL = "channel";

Connection::Connection(QTcpSocket *tcpSocket, QObject *parent) : QObject(parent)
{
    this->tcpSocket = tcpSocket;

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadyToRead()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(Error(QAbstractSocket::SocketError)));

    qDebug() << "<New connection>"
             << "\n  host:" << tcpSocket->localAddress().toString()
             << "\n  local port: " << tcpSocket->localPort();
}

void Connection::SendMessage(IRCData::MessageData *message)
{
    qDebug() << "<Send message>"
             << "\n  channel:" << message->channelName
             << "\n  username:" <<message->username
             << "\n  content:" <<message->content;

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
///
/// \brief Connection::SendCommand
/// \param message
///
void Connection::SendCommand(Message *message)
{
    tcpSocket->write(message->toByte());
}

void Connection::ReadyToRead()
{
    // TODO read from socket
    QByteArray dataArray = tcpSocket->readAll();
    qDebug() << "<<<<<<" << dataArray;
    Message *msg = new Message(dataArray);
    QString command = msg->getValue(KEYS::CMD);

    IRCData::MessageData *message;

    switch (command.toInt()) {
    case WELCOME:

        break;
    case LOGIN_ACC:

        break;
    case JOIN_ACC:

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
        OnMessageReceived(message);
        break;
//    case ERROR:

//        break;
    default:
        break;
    }

}

void Connection::Error(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error:" << error;
    emit OnConnectionLost();
}
