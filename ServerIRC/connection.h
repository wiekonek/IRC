#ifndef CONNECTION_H
#define CONNECTION_H

#define BUF_SIZE 2000

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
    pthread_t id;

    static void* handle(void *arg);
    void* loop();

    static void sigpipe_handler(int signo);

};

#endif // CONNECTION_H
