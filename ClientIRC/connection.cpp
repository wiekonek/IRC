#include "connection.h"
#include <QDebug>
#include <QtNetwork>
#include <QMessageBox>


Connection::Connection(QTcpSocket *tcpSocket, QObject *parent) : QObject(parent)
{
    this->tcpSocket = tcpSocket;

    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(ReadyToRead()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(Error(QAbstractSocket::SocketError)));

    qDebug() << "<New connection>"
             << "\n  host:" << tcpSocket->localAddress().toString()
             << "\n  local port: " << tcpSocket->localPort();
}

void Connection::SendMessage(IRCData::ChannelMessageData *message)
{
    qDebug() << "<Send message>"
             << "\n  channel:" << message->channelName
             << "\n  username:" <<message->username
             << "\n  content:" <<message->content;
    // TODO send message!!!
    tcpSocket->write(message->content.toStdString().c_str());
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
