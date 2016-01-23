#include "server.h"

#include <QDebug>

Server::Server(QObject *parent) : QObject(parent)
{

}

Server* Server::getInstance() // statyczna klasa signleton
{
    static Server instance;
    return &instance;
}

Channel* Server::Create(Connection* connection, QString channel_name)
{
    if(Find(channel_name) == NULL)
    {
        Channel* channel = new Channel(channel_name);
        addChannel(channel);
        SendConfirm(connection, CREATE_ACC, 1);
        return channel;
    }
    else
    {
        SendConfirm(connection, CREATE_ACC, 0);
        return NULL;
    }
}

Channel* Server::Join(Connection* connection, QString channel_name)
{
    Channel* channel = Find(channel_name);
    if(channel != NULL)
    {
        channel->Add(connection);
        SendConfirm(connection, JOIN_ACC, 1);
    }
    else
    {
        qDebug("JOIN::kanal nie istnieje");
        SendConfirm(connection, JOIN_ACC, 0);
    }
    return channel;
}

void Server::Leave(Connection* connection, QString channel_name)
{
    Channel* channel = Find(channel_name);
    if(channel != NULL)
    {
        channel->Remove(connection);
        SendConfirm(connection, LEAVE_ACC, 1);
    }
    else
    {
        qDebug("LEAVE::kanal nie istnieje ");
        SendConfirm(connection, LEAVE_ACC, 0);
    }
}

void Server::Send(Connection* sender, QString channel_name, QString text)
{
    Channel* channel = Find(channel_name);
    if(channel != NULL)
    {
        for(Connection* connection : channel->GetConnections())
        {
            if(connection != sender) //niech stworzy sie wiele kopi tego obiektu, connection->Send() je niszczy
            {
                Message* message = new Message();
                message->add("user", sender->GetName());
                message->add("text", text);
                message->add("command", MESSAGE);
                message->add("channel", channel_name);
                connection->Send(message);
            }
        }
    }
    else
    {
        qDebug("wyslano wiadomosc do nie istniejacego kanalu...");
    }
}

void Server::Login(Connection* connection, QString name)
{
    connection->SetName(name);
    SendConfirm(connection, LOGIN_ACC, 1);
}

void Server::Disconnect(Connection *connection)
{
    connection->Stop();
    for(Channel* channel : public_channels)
    {
        channel->Remove(connection);
    }
}

void Server::SendConfirm(Connection *connection, int command, int value)
{
    Message* message = new Message();
    message->add("command", command);
    message->add("value", value);
    connection->Send(message);
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

void Server::removeConnection(Connection *connection)
{
    Erase(active_connection, connection);
}

Channel* Server::Find(QString name)
{
    vector<Channel*> *channels = &public_channels;
    for(Channel* channel : *channels)
    {
        if(channel->GetName() == name)
           return channel;
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
    //message->printAll();
    //message->add("password", "");
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
