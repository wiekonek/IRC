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

Channel* Server::Create(QString channel_name, int ispublic, QString password)
{
    Channel* channel = new Channel(channel_name, ispublic, password);
    if(ispublic == 1)
    {
        public_channels.push_back(channel);
    }
    else
    {
        private_channels.push_back(channel);
    }
    return channel;
}

Channel* Server::Join(QString channel_name, Connection* connection, QString password, int ispublic)
{
    Channel* channel = Find(channel_name, ispublic);
    if(ispublic == 1)
    {
        channel->Add(connection);
    }
    else
    {
        int err = channel->Add(connection, password);
        if(err != 0)
            qDebug("odrzucono - zaimplementuj join");
    }
    return channel;
}

void Server::Leave(QString channel_name, Connection* connection)
{
    Channel* channel = Find(channel_name) != NULL ? Find(channel_name) : Find(channel_name, false);
    if(channel != NULL)
    {
        channel->Remove(connection);
    }
    else
    {
        qDebug("kanal nie istnieje");
    }
}

void Server::Send(QString channel_name, Connection* sender, QString text)
{
    Channel* channel = Find(channel_name) != NULL ? Find(channel_name) : Find(channel_name, false);
    Message* message = new Message();
    message->add("user", sender->GetName());
    message->add("text", text);
    message->add("command", MESSAGE);
    if(channel != NULL)
    {
        for(Connection* connection : channel->GetConnections())
        {
            if(connection != sender)
            {
                SocketManager::Write(connection->GetClientSocket(), message->toChar(), BUF_SIZE);
            }
        }
    }
}

void Server::Login(Connection* connection, QString name)
{
    connection->SetName(name);
    Message* message = new Message();
    message->add("command", "login");
    message->add("result", 1);
    SocketManager::Write(connection->GetClientSocket(), message->toChar(), 200);
}

void Server::Disconnect(Connection *connection)
{
    connection->Stop();
    for(Channel* channel : public_channels)
    {
        channel->Remove(connection);
    }

    for(Channel* channel : private_channels)
    {
        channel->Remove(connection);
    }
}

void Server::PrintPublicChannels()
{
    Print(public_channels);
}

void Server::PrintPrivatechannels()
{
    Print(private_channels);
}

void Server::PrintAllChannels()
{
    qDebug() << "publiczne";
    PrintPublicChannels();
    qDebug() << "prywatne:";
    PrintPrivatechannels();
}

void Server::addChannel(Channel *channel)
{
    private_channels.push_back(channel);
    qDebug() << "New channel created.";
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
    active_connection.push_back(connection);
    qDebug() << "New connection established.\n";
}

void Server::removeConnection(Connection *connection)
{
    for(int i = 0; i < MAX_CONNECTIONS; i++) {
        if(activeConnections[i] == connection)
            delete activeConnections[i];
    }
}

Channel* Server::Find(QString name, int ispublic)
{
    vector<Channel*> *channels = ispublic ? &public_channels : &private_channels;
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
    message->printAll();
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
            break;

        case CREATE:
            Create(message->getValue("channel"),
                   message->getValue("public").toInt(),
                   message->getValue("password"));
            break;

        case JOIN:
            Join(message->getValue("channel"),
                 connection,
                 message->getValue("password"),
                 message->getValue("public").toInt());
            break;

        case LEAVE:
            Leave(message->getValue("channel"), connection);
            break;

        case MESSAGE:
            Send(message->getValue("channel"),
                 connection,
                 message->getValue("text"));
            break;

        case DISCONNECT:
            Disconnect(connection);
            break;

        }
    }
}
