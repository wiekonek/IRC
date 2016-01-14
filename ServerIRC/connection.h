#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "message.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QObject *parent = 0);
    Connection(int clientSocket, struct sockaddr_in address);
    ~Connection();

    void Send(Message *message);
    void Close();
    void SetPort(int port);


signals:
    void OnRegisterToChannel(Connection *connection);


public slots:


private:
    int clientSocket;
    int port;
    struct sockaddr_in address;

    void ConnectionHandler();

};

#endif // CONNECTION_H
