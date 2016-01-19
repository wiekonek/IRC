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

void Connection::SendMessage(IRCData::MessageData *message)
{
    qDebug() << "<Send message>"
             << "\n  channel:" << message->channelName
             << "\n  username:" <<message->username
             << "\n  content:" <<message->content;
    // TODO send message!!!
    tcpSocket->write(message->content.toStdString().c_str());
}

void Connection::ReadyToRead()
{
    // TODO read from socket
    qDebug() << "<<<<<<" << tcpSocket->readAll();

}

void Connection::Error(QAbstractSocket::SocketError error)
{
    qDebug() << "Socket error:" << error;
    emit OnConnectionLost();
}
