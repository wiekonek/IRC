#include "connection.h"
#include <QDebug>
#include <QtNetwork>
#include <QMessageBox>

const QString Connection::KEY_CMD = "command";
const QString Connection::KEY_USER = "user";
const QString Connection::KEY_PUBLIC = "public";
const QString Connection::KEY_PASSWORD = "password";
const QString Connection::KEY_TEXT = "text";
const QString Connection::KET_TYPE = "type";
const QString Connection::KEY_CHANNEL = "channel";

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
    msg->add(KEY_CMD, MESSAGE);
    msg->add(KEY_CHANNEL, message->channelName);
    msg->add(KEY_TEXT, message->content);

    SendCommand(msg);
    delete msg;
}

void Connection::SendLoginRequest(IRCData::UserData *userData)
{
    Message *msg = new Message();
    msg->add(KEY_CMD, LOGIN);
    msg->add(KEY_USER, userData->username);
    msg->add(KEY_PASSWORD, userData->password);

    SendCommand(msg);
    delete msg;
}

void Connection::SendJoinChannelRequest(IRCData::ChannelData *channelData)
{
    Message *msg = new Message();
    msg->add(KEY_CMD, JOIN);
    msg->add(KEY_CHANNEL, channelData->name);

    SendCommand(msg);
    delete msg;
}

void Connection::LeaveChannel(IRCData::ChannelData *channelData)
{
    Message *msg = new Message();
    msg->add(KEY_CMD, LEAVE);
    msg->add(KEY_CHANNEL, channelData->name);

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
    qDebug() << "<<<<<<" << dataArray;
    Message *msg = new Message(dataArray);
    QString command = msg->getValue("command");
//    switch(command) {
//    case "message":

//    }

//    if(false) // jeśli wiadomość na kanał
//        emit OnMessageReceived();
}

void Connection::Error(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error:" << error;
    emit OnConnectionLost();
}
