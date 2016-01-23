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

    Message *message = new Message();
    message->add("command", WELCOM);
    SocketManager::Write(client_socket, message->toChar(), 50);


    pthread_create(&id, NULL, &Connection::Connect2Thread, this);
}

void* Connection::MainLoop()
{
    QObject::connect(this, SIGNAL(OnNewMessage(Message*)),
                     Server::getInstance(), SLOT(readMessage(Message*)));
    QObject::connect(this, SIGNAL(OnDisconnect()),
                     Server::getInstance(), SLOT(removeConnection()));

    if (signal(SIGPIPE, Connection::SigpipeHandler) == SIG_ERR)
    {
        qDebug("cant catch SIGPIPE");
        perror(0);
        exit(1);
    }

    while(working)
    {
        char buf[BUF_SIZE];
        ClearArray(buf);
        int recv_size = SocketManager::ReadNoWait(client_socket, buf, BUF_SIZE);

        if(recv_size > 0)
        {
            qDebug("otrzymano");
            qDebug(buf);
            InputManage(buf);
        }
        else if(recv_size == 0)
        {
            break;
        }

        OutputManage();

        usleep(200000);
    }

    qDebug("disconnected");
    close(client_socket);
    working = false;
    emit OnDisconnect();
    return 0;
}

void Connection::InputManage(char *transmission)
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
    delete(buffer);
}

int Connection::OutputManage()
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
            delete(message);
            if(size < 0)
                break;
        }
        delete(bufor);
        return size;
    }
    return 0;
}

void Connection::Send(Message *messsage)
{
    pthread_mutex_lock(&queue_mutex);
    output_messages->push(messsage);
    tosend = true;
    pthread_mutex_unlock(&queue_mutex);
}

bool Connection::IsWorking()
{
    return working;
}

void Connection::Stop()
{
    working = false;
}

int Connection::GetClientSocket()
{
    return client_socket;
}

QString Connection::GetName()
{
    return client_name;
}

void Connection::SetName(QString name)
{
    this->client_name = name;
}

void Connection::SetName(char* name)
{
    QString buf_name(name);
    SetName(buf_name);
}

void Connection::ClearArray(char *array)
{
    for(int i=0; i<BUF_SIZE; i++)
    {
        array[i] = '\0';
    }
}

void* Connection::Connect2Thread(void *arg)
{
    return ((Connection*)arg)->MainLoop();
}

void Connection::SigpipeHandler(int signo)
{
    if (signo == SIGPIPE)
    {
        qDebug("connection lost");
    }
}

Connection::~Connection()
{

}

