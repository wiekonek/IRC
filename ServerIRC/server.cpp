#include "server.h"

#include <iostream>

using std::cout;

Server::Server(QObject *parent) : QObject(parent)
{

}

void Server::addChannel(Channel *channel)
{
    dynamic_channels.push_back(channel);
    cout<<"New channel created.";
}

template<class T> void Erase(vector<T*> &vec, T *item) {
    vec.erase(std::remove(vec.begin(), vec.end(), item),
                           vec.end());
}

void Server::removeChannel(Channel *channel)
{
    Erase(dynamic_channels, channel);
}

void Server::addConnection(Connection *connection)
{
    active_connection.push_back(connection);
    cout<<"New connection established.\n";
}

void Server::removeConnection(Connection *connection)
{
    Erase(active_connection, connection);
}

