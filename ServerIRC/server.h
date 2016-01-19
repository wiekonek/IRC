#ifndef SERVER_H
#define SERVER_H

#define MAX_CONNECTIONS 200

#define LOGIN 0
#define CREATE 1
#define JOIN 2
#define LEAVE 3
#define MESSAGE 4
#define DISCONNECT 5

#define LOGIN_ACC 6
#define CREATE_ACC 7
#define JOIN_ACC 8
#define LEAVE_ACC 9
#define ERROR 20

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

     Channel* Create(Connection* connection, QString channel_name, int ispublic = 1, QString password = "");
     Channel* Join(Connection *connection, QString channel_name, QString password = "", int ispublic = true);
     void Leave(Connection* connection, QString channel_name);
     void Send(Connection* sender, QString channel_name, QString text);
     void Login(Connection* connection, QString name);
     void Disconnect(Connection* connection);
     void Confirm(Connection* connection, int command, int value);

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
    Channel* Find(QString name, int ispublic = true);
    void Print(vector<Channel *> channels);

    Connection *activeConnections[MAX_CONNECTIONS];

    vector<Channel *> public_channels;
    vector<Channel *> private_channels;
    vector<Connection *>  active_connection;
    int GetFreePortNumber();
};

#endif // SERVER_H
