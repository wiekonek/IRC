#include "connection.h"
#include <server.h>

Connection::Connection(QObject *parent) : QObject(parent) { }

Connection::Connection(int clientSocket)
{
    this->clientSocket = clientSocket;
    this->working = true;
    SocketManager::Write(clientSocket, "Connection slot granted.\n", 50);
    QObject::connect(this, SIGNAL(OnNewMessage(Message*)),
                     &(Server::getInstance()), SLOT(readMessage(Message*)), Qt::QueuedConnection);

    pthread_create(&id, NULL, &Connection::handle, this);
}

Connection::~Connection()
{
    SocketManager::Write(clientSocket, "EXIT", 10);
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
    qDebug("XD");
}

void* Connection::handle(void *arg)
{
    return ((Connection*)arg)->loop();
}

void* Connection::loop()
{
    if (signal(SIGPIPE, Connection::sigpipeHandler) == SIG_ERR)
    {
        qDebug("cant catch SIGPIPE");
        perror(0);
        exit(1);
    }

    while(working)
    {
        int size = SocketManager::Write(this->clientSocket, "XD", 50);

        if(size < 0)
            break;

        char buf[BUF_SIZE];
        int recv_size = SocketManager::ReadNoWait(clientSocket, buf, BUF_SIZE);
        if(recv_size > 0)
        {
            analyze(buf);
        }

        sleep(1);
    }
    qDebug("disconnected");
    close(clientSocket);
    Server::getInstance().removeConnection(this);
    working = false;
    return NULL;
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
        }
    }
}

void Connection::sigpipeHandler(int signo)
{
    if (signo == SIGPIPE)
    {
        qDebug("connection lost");
    }
}
