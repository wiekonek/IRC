#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <vector>
#include <connection.h>
#include <algorithm>

using std::vector;
using std::find;

class Channel : public QObject
{
    Q_OBJECT
public:
    Channel(QObject *parent = 0);
    Channel(QString name, int ispublic = true, QString password = "");

    int Add(Connection* connection, QString password = "");
    void Remove(Connection* connection);

    int IsPublic();
    QString GetName();
    const vector<Connection *> GetConnections();

    void PrintUsers();
signals:

public slots:
private:
    int port;
    int ispublic;
    QString name;
    QString password;
    vector<Connection *> connections;

};

#endif // CHANNEL_H
