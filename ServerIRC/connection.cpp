#include "connection.h"
#include <server.h>

Connection::Connection(QObject *parent) : QObject(parent) { }

Connection::Connection(int client_socket)
{
    output_messages = new std::queue<Message *>();
    queue_mutex = PTHREAD_MUTEX_INITIALIZER;
    this->client_socket = client_socket;
    this->working = true;
    this->tosend = false;
    SocketManager::Write(client_socket, "Connection slot granted.\n", 50);

    pthread_create(&id, NULL, &Connection::connect2Thread, this);
}

Connection::~Connection()
{
    SocketManager::Write(client_socket, "EXIT", 10);
}

bool Connection::IsWorking()
{
    return working;
}

void Connection::SetPort(int port)
{
    this->port = port;
}

void Connection::Disconnect()
{
    working = false;
}

void Connection::Send(Message *messsage)
{
    pthread_mutex_lock(&queue_mutex);
    output_messages->push(messsage);
    tosend = true;
    pthread_mutex_unlock(&queue_mutex);
}

void* Connection::mainLoop()
{
    QObject::connect(this, SIGNAL(OnNewMessage(Message*)),
                     Server::getInstance(), SLOT(readMessage(Message*)));

    if (signal(SIGPIPE, Connection::sigpipeHandler) == SIG_ERR)
    {
        qDebug("cant catch SIGPIPE");
        perror(0);
        exit(1);
    }

    while(working)
    {
        int size = sendManage();
        size = SocketManager::Write(client_socket, "\4", 10);
        if(size < 0)
            break;

        char buf[BUF_SIZE];
        int recv_size = SocketManager::ReadNoWait(client_socket, buf, BUF_SIZE);
        if(recv_size > 0)
        {
            analyze(buf);
        }

        usleep(200000);
    }
    qDebug("disconnected");
    close(client_socket);
    Server::getInstance()->removeConnection(this);
    working = false;
    return 0;
}

void Connection::analyze(char *transmission)
{
    QString* buffer = new QString(transmission);
    QStringList messages = buffer->split('\4');
    for(int i=0; i<messages.size(); i++)
    {
        if(messages[i] != "")
        {
            Message* message = new Message((messages[i]).toStdString().c_str());
            emit OnNewMessage(message);
        }
    }
}

int Connection::sendManage()
{
    if(tosend)
    {
        std::queue<Message *> *bufor = new std::queue<Message *>();
        pthread_mutex_lock(&queue_mutex);
        while(output_messages->size() > 0)
        {
            bufor->push(output_messages->front());
            output_messages->pop();
        }
        tosend = false;
        pthread_mutex_unlock(&queue_mutex);

        int size = 0;
        while(bufor->size() > 0)
        {
            Message* message = bufor->front();
            bufor->pop();
            size = SocketManager::Write(client_socket, message->toChar(), BUF_SIZE);
            if(size < 0)
                break;
        }
        delete(bufor);
        return size;
    }
    return 0;
}

void* Connection::connect2Thread(void *arg)
{
    return ((Connection*)arg)->mainLoop();
}

void Connection::sigpipeHandler(int signo)
{
    if (signo == SIGPIPE)
    {
        qDebug("connection lost");
    }
}
