#ifndef CONNECTION_H
#define CONNECTION_H

#define BUF_SIZE 2000

#include <QObject>
#include <pthread.h>
#include <sstream>
#include <signal.h>
#include <queue>
#include <QDebug>

#include "message.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QObject *parent = 0);
    Connection(int clientSocket, struct sockaddr_in address);
    ~Connection();

    bool IsWorking();
    void Close();
    void SetPort(int port);
    void Disconnect();

signals:
    void OnRegisterToChannel(Connection *connection);
    void OnNewMessage(Message *message);

public slots:
    void Send(Message *message);

private:
    bool working;
    int clientSocket;
    QString client_name;
    std::queue<Message *> output_messages;

    int port;
    pthread_t id;

    void* loop();
    void analyze(char* buf, int size);
    static void* handle(void *arg);
    static void sigpipeHandler(int signo);
    static bool isEndOfMessage(char sign);
    static bool isEndOfBuffor(char sign);

};

#endif // CONNECTION_H
