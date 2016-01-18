#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtNetwork/QTcpSocket>

#include "message.h"
#include "datastructures.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = 0);

signals:
    void OnMessageReceived(Message *message);
    void OnConnectionLost();

public slots:
    void SendMessage(IRCData::MessageData *message);

private:
    QTcpSocket *tcpSocket;
};

#endif // CONNECTION_H
