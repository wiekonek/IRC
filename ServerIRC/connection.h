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

using std::queue;

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QObject *parent = 0);
    Connection(int clientSocket);
    ~Connection();

    bool IsWorking();
    void Close();
    void SetPort(int port);
    void Disconnect();
    QString GetName();
    void SetName(QString name);
    void SetName(char* name);
    void Send(Message* message);

signals:
    void OnRegisterToChannel(Connection *connection);
    void OnNewMessage(Message *message);
    void OnDisconnected();

private:
    bool working;
    bool tosend;
    int client_socket;
    QString client_name;
    queue<Message *> *output_messages;

    int port;
    pthread_t id;
    pthread_mutex_t queue_mutex;

    void* mainLoop();
    void analyze(char* buf);
    int sendManage();
    static void* connect2Thread(void *arg);
    static void sigpipeHandler(int signo);

};

#endif // CONNECTION_H
