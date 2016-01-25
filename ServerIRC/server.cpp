#include "server.h"

#include <QDebug>

Server::Server(QObject *parent) : QObject(parent)
{

}

Server* Server::getInstance() // signleton
{
    static Server instance;
    return &instance;
}

Channel* Server::Create(Connection* connection, QString channel_name)
{
    if(FindChannel(channel_name) == NULL && channel_name.size() > 0)
    {
        Channel* channel = new Channel(channel_name);
        addChannel(channel);
        SendConfirm(connection, CREATE_ACC, 1, channel_name);
        return channel;
    }
    else
    {
        SendConfirm(connection, CREATE_ACC, 0, channel_name);
        return NULL;
    }
}

Channel* Server::Join(Connection* connection, QString channel_name)
{
    Channel* channel = FindChannel(channel_name);
    if(channel != NULL)
    {
        channel->Add(connection);
        SendConfirm(connection, JOIN_ACC, 1, channel_name);
        SendList(channel->GetName());
    }
    else
    {
        qDebug("JOIN::channel doesn't exist");
        SendConfirm(connection, JOIN_ACC, 0, channel_name);
    }
    return channel;
}

void Server::Leave(Connection* connection, QString channel_name)
{
    Channel* channel = FindChannel(channel_name);
    if(channel != NULL)
    {
        channel->Remove(connection);
        SendConfirm(connection, LEAVE_ACC, 1, channel_name);
        SendList(channel->GetName());
    }
    else
    {
        qDebug("LEAVE::channel doesn't exist");
        SendConfirm(connection, LEAVE_ACC, 0, channel_name);
    }
}

void Server::Send(Connection* sender, QString channel_name, QString text)
{
    Channel* channel = FindChannel(channel_name);
    if(channel != NULL)
    {
        for(Connection* connection : channel->GetConnections())
        {
            Message* message = new Message();
            message->add("user", sender->GetName());
            message->add("text", text);
            message->add("command", MESSAGE);
            message->add("channel", channel_name);
            connection->Send(message);
        }
    }
    else
    {
        qDebug("tried to send message to not existing channel");
    }
}

void Server::Login(Connection* connection, QString user_name)
{
    if(FindConnection(user_name) == NULL)
    {
        connection->SetName(user_name);
        SendConfirm(connection, LOGIN_ACC, 1);
    }
    else
    {
        SendConfirm(connection, LOGIN_ACC, 0);
    }
}

void Server::Disconnect(Connection *connection)
{
    connection->Stop();
    for(Channel* channel : public_channels)
    {
        channel->Remove(connection);
        SendList(channel->GetName());
    }
}

void Server::SendConfirm(Connection *connection, int command, int value, QString channel_name)
{
    Message* message = new Message();
    message->add("command", command);
    message->add("value", value);
    if(channel_name.size() > 0)
    {
        message->add("channel", channel_name);
    }
    connection->Send(message);
}

void Server::SendList(QString channel_name)
{
    Channel* channel = FindChannel(channel_name);
    if(channel != NULL)
    {
        QStringList list = channel->GetList();
        for(Connection* connection : channel->GetConnections())
        {
            Message* message = new Message();
            message->add("command", USER_LIST);
            message->add("list", list);
            message->add("channel", channel_name);
            connection->Send(message);
        }
    }
    else
    {
        qDebug("channel doesn't exists");
    }
}

void Server::PrintPublicChannels()
{
    Print(public_channels);
}

void Server::addChannel(Channel *channel)
{  
    public_channels.push_back(channel);
    qDebug() << "New public channel created.";
}

template<class T> void Erase(vector<T*> &vec, T *item) {
    vec.erase(std::remove(vec.begin(), vec.end(), item),
                           vec.end());
}

void Server::removeChannel(Channel *channel)
{
    Erase(public_channels, channel);
}

void Server::addConnection(Connection *connection)
{
    active_connection.push_back(connection);
    qDebug() << "New connection established.\n";
}

void Server::removeConnection()
{
    Connection *connection = (Connection*)QObject::sender();
    Erase(active_connection, connection);
    delete(connection);
}

Channel* Server::FindChannel(QString name)
{
    vector<Channel*> *channels = &public_channels;
    for(Channel* channel : *channels)
    {
        if(channel->GetName() == name)
           return channel;
    }
    return NULL;
}

Connection* Server::FindConnection(QString user_name)
{
    vector<Connection*> *connections = &active_connection;
    for(Connection* connection : *connections)
    {
        if(connection->GetName() == user_name)
           return connection;
    }
    return NULL;
}

void Server::Print(vector<Channel *> channels)
{
    for(Channel* channel : channels)
    {
        qDebug() << channel->GetName();
    }
}

void Server::readMessage(Message* message)
{
    Connection* connection = (Connection*)QObject::sender();
    if(connection == NULL)
    {
        qDebug("problem with arrived message...");
    }
    else
    {
        int command = message->getValue("command").toInt();
        switch(command)
        {
        case LOGIN:
            Login(connection, message->getValue("user"));
            qDebug() << "new user logged in" << message->getValue("user");
            break;

        case CREATE:
            Create(connection,
                   message->getValue("channel"));
            break;

        case JOIN:
            Join(connection,
                 message->getValue("channel"));
            break;

        case LEAVE:
            Leave(connection, message->getValue("channel"));
            break;

        case MESSAGE:
            Send(connection,
                 message->getValue("channel"),
                 message->getValue("text"));
            break;

        case DISCONNECT:
            Disconnect(connection);
            break;

        }
    }
}
