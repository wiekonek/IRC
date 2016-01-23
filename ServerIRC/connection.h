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

    void Send(Message* message);
    void Stop();

    bool IsWorking();
    QString GetName();
    int GetClientSocket();
    void SetName(QString name);
    void SetName(char* name);

signals:
    void OnNewMessage(Message *message);

private:
    void* MainLoop();
    void InputManage(char* buf);
    int OutputManage();
    void ClearArray(char* array);
    static void* Connect2Thread(void *arg);
    static void SigpipeHandler(int signo);

    bool working;
    bool tosend;
    int client_socket;
    QString client_name;
    queue<Message *> *output_messages;

    pthread_t id;
    pthread_mutex_t queue_mutex;
};

#endif // CONNECTION_H
