#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtNetwork>

#include "message.h"
#include "datastructures.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket *tcpSocket, QObject *parent = 0);

signals:
    void OnMessageReceived(Message *message);
    void OnConnectionLost();

public slots:
    void SendMessage(IRCData::MessageData *message);

private slots:
    void ReadyToRead();
    void Error(QAbstractSocket::SocketError error);

private:
    QTcpSocket *tcpSocket;
};

#endif // CONNECTION_H
