#include "connection.h"
#include <server.h>

Connection::Connection(QObject *parent) : QObject(parent) { }

Connection::Connection(int clientSocket, sockaddr_in address)
{
    this->clientSocket = clientSocket;
    this->working = true;
    SocketManager::Write(clientSocket, "Connection slot granted.\n", 50);
    std::string str = "NEW_PORT" + std::to_string(port);
    SocketManager::Write(clientSocket, str.c_str(), 40);

    pthread_create(&id, NULL, &Connection::handle, this);
}

Connection::~Connection()
{
    SocketManager::Write(clientSocket, "EXIT", 10);
}

bool Connection::isWorking()
{
    return working;
}

int Connection::getMessageCount()
{
    //throw new std::exception("get message count not implemented");
    return 0;
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

void Connection::analyze(char *transmission, int size)
{
    int start = 0;
    for(int i = 0; i<size; i++)
    {
        if(isEndOfMessage(transmission[i]))
        {
            int end = i;
            char temp[BUF_SIZE];
            strncpy(temp, transmission + start, end);
            start = i;
        }
        if(isEndOfBuffor(transmission[i]))
            break;
    }
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
            qDebug("message from client appear!");
            analyze(buf, BUF_SIZE);
        }

        sleep(1);
    }
    qDebug("disconnected");
    close(clientSocket);
    Server::getInstance().removeConnection(this);
    working = false;
}

bool Connection::isEndOfBuffor(char *sign)
{
    return sign[0] == '\0';
}

bool Connection::isEndOfMessage(char *sign)
{
    return sign[0] == '\4';
}

void Connection::sigpipeHandler(int signo)
{
    if (signo == SIGPIPE)
    {
        qDebug("connection lost");
    }
}
