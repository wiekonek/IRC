#include "channel.h"

Channel::Channel(QObject *parent) : QObject(parent)
{

}

Channel::Channel(QString name, int ispublic, QString password)
{
    this->name = name;
    this->ispublic = 1;
    this->password = password;
}

int Channel::Add(Connection *connection, QString password)
{
    if(ispublic == 1)
    {
        connections.push_back(connection);
        return 0;
    }
    else if(this->password == password)
    {
        connections.push_back(connection);
        return 0;
    }
    return 1;
}

void Channel::Remove(Connection *connection)
{
    auto index = find(connections.begin(), connections.end(), connection);
    if(index != connections.end())
        connections.erase(index);
}

int Channel::IsPublic()
{
    return ispublic;
}

QString Channel::GetName()
{
    return name;
}

const vector<Connection *> Channel::GetConnections()
{
    return connections;
}

void Channel::PrintUsers()
{
    for(Connection* connection : connections)
    {
        qDebug() << connection->GetName();
    }
}


