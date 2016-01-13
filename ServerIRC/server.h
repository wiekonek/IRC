#ifndef SERVER_H
#define SERVER_H

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

signals:

public slots:
    void addChannel(Channel *channel);
    void removeChannel(Channel *channel);

    void addConnection(Connection *connection);
    void removeConnection(Connection *connection);

private:
    vector<Connection *>  active_connection;
    vector<Channel *> static_channels;
    vector<Channel *> dynamic_channels;
};

#endif // SERVER_H
