#include "channel.h"

Channel::Channel(QObject *parent) : QObject(parent)
{

}

Channel::Channel(QString name, bool ispublic, QString password)
{
    this->name = name;
    this->ispublic = ispublic;
    this->password = password;
}

int Channel::Add(Connection *connection, QString password)
{
    if(ispublic)
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
    connections.erase(index);
}

bool Channel::IsPublic()
{
    return ispublic;
}

QString Channel::GetName()
{
    return name;
}

void Channel::PrintUsers()
{
    for(Connection* connection : connections)
    {
        qDebug() << connection->GetName();
    }
}


