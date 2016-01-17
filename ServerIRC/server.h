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
     static Server& getInstance();

signals:

public slots:
    void addChannel(Channel *channel);
    void removeChannel(Channel *channel);

    void addConnection(Connection *connection);
    void removeConnection(Connection *connection);

private:
    Connection *activeConnections[MAX_CONNECTIONS];
    vector<Connection *>  active_connection;
    vector<Channel *> public_channels;
    vector<Channel *> private_channels;

    int GetFreePortNumber();
};

#endif // SERVER_H
