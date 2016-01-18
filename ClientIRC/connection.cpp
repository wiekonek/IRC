#include "connection.h"
#include "QDebug"
#include "QtNetwork/QTcpSocket"
#include "QtNetwork/QTcpServer"

Connection::Connection(QObject *parent) : QObject(parent)
{

}

void Connection::SendMessage(IRCData::MessageData *message)
{
    qDebug() << "Send message:"
             << message->channelName
             << message->username
             << message->content;
    // TODO send message!!!
    message->username.toStdString().c_str();
    QTcp *asd = new QTcpSocket();
    QHostAddress *hostAddress = new QHostAddress();
    asd->connectToHost(new QHostAddress());
}

