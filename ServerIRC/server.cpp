#include "server.h"

#include <iostream>

using std::cout;

Server::Server(QObject *parent) : QObject(parent)
{

}

Server& Server::getInstance() // statyczna klasa signleton
{
    static Server instance;
    return instance;
}

void Server::addChannel(Channel *channel)
{
    private_channels.push_back(channel);
    cout<<"New channel created.";
}

template<class T> void Erase(vector<T*> &vec, T *item) {
    vec.erase(std::remove(vec.begin(), vec.end(), item),
                           vec.end());
}

void Server::removeChannel(Channel *channel)
{
    Erase(private_channels, channel);
}

void Server::addConnection(Connection *connection)
{
    int freePort = GetFreePortNumber();
    activeConnections[freePort] = connection;
    connection->SetPort(freePort);
    cout<<"New connection established.\n";
}

void Server::removeConnection(Connection *connection)
{
    for(int i = 0; i < MAX_CONNECTIONS; i++) {
        if(activeConnections[i] == connection)
            delete activeConnections[i];
    }
}

int Server::GetFreePortNumber()
{
    for(int i = 0; i < MAX_CONNECTIONS; i++) {
        if(activeConnections[i] == NULL)
            return i;
    }
    return -1;
}

void Server::readMessage(Message* message)
{
    qDebug("message");
}
