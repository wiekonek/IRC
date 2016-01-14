#include "connection.h"

#include <pthread.h>
#include <sstream>

Connection::Connection(QObject *parent) : QObject(parent) { }

Connection::Connection(int clientSocket, sockaddr_in address)
{
    this->clientSocket = clientSocket;
    SocketManager::Write(clientSocket, "Connection slot granted.\n", 50);

    std::string str = "NEW_PORT" + std::to_string(port);
    SocketManager::Write(clientSocket, str.c_str(), 40);
    close(clientSocket);


    SocketManager::SetupSockaddr(address, port);
    SocketManager::CreateSocket(address, 10);

    if(fork()) {

    }


}

Connection::~Connection()
{
    SocketManager::Write(clientSocket, "EXIT", 10);
}

void Connection::SetPort(int port)
{
    this->port = port;
}

