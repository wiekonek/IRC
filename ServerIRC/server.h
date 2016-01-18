#ifndef SERVER_H
#define SERVER_H

#define MAX_CONNECTIONS 200

#include <vector>
#include <string>
#include <QObject>

#include "connection.h"
#include "channel.h"

using std::vector;
using std::string;

class Server : public QObject
{
    Q_OBJECT

public:
     Server(QObject* parent=0);
     static Server* getInstance();

     Channel* Create(QString channel_name, bool ispublic = true, QString password = "");
     Channel* Join(QString channel_name, Connection *connection, QString password = "", bool ispublic = true);
     void Leave(QString channel_name, Connection* connection);
     void Send(QString channel_name, Connection* sender, QString text);

     void PrintAllChannels();
     void PrintPublicChannels();
     void PrintPrivatechannels();
signals:

public slots:
    void addChannel(Channel *channel);
    void removeChannel(Channel *channel);

    void addConnection(Connection *connection);
    void removeConnection(Connection *connection);

    void readMessage(Message *message);

private:
    Channel* Find(QString name, bool ispublic = true);
    void Print(vector<Channel *> channels);

    Connection *activeConnections[MAX_CONNECTIONS];

    vector<Channel *> public_channels;
    vector<Channel *> private_channels;
    vector<Connection *>  active_connection;
    int GetFreePortNumber();
};

#endif // SERVER_H
