#include "connection.h"

#include <pthread.h>
#include <sstream>
#include <server.h>
#include <signal.h>

Connection::Connection(QObject *parent) : QObject(parent) { }

Connection::Connection(int clientSocket, sockaddr_in address)
{
    this->clientSocket = clientSocket;
    SocketManager::Write(clientSocket, "Connection slot granted.\n", 50);
    std::string str = "NEW_PORT" + std::to_string(port);
    SocketManager::Write(clientSocket, str.c_str(), 40);

    pthread_create(&id, NULL, &Connection::handle, this);

}

Connection::~Connection()
{
    SocketManager::Write(clientSocket, "EXIT", 10);
}

void Connection::SetPort(int port)
{
    this->port = port;
}

void* Connection::handle(void *arg)
{
    return ((Connection*)arg)->loop();
}

void* Connection::loop()
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 500;

    if (signal(SIGPIPE, Connection::sigpipe_handler) == SIG_ERR) {
      qDebug("cant catch SIGPIPE");
      perror(0);
      exit(1);
    }

    while(true)
    {
        int size = SocketManager::Write(this->clientSocket, "XD", 50);

        if(size < 0)
            break;

        char buf[BUF_SIZE];
        int recv_size = SocketManager::ReadNoWait(clientSocket, buf, BUF_SIZE);
        if(recv_size > 0)
        {
            qDebug("message from client appear!");
            qDebug("%s", buf);
        }

        sleep(1);
    }

    close(clientSocket);
    Server::getInstance().removeConnection(this);
    delete(this);
}

void Connection::sigpipe_handler(int signo)
{
    if (signo == SIGPIPE)
    {
        qDebug("connection lost");
    }
}
