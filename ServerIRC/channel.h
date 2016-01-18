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
    Channel(QString name, bool ispublic = true, QString password = "");

    int Add(Connection* connection, QString password = "");
    void Remove(Connection* connection);

    bool IsPublic();
    QString GetName();

    void PrintUsers();
signals:

public slots:
private:
    int port;
    bool ispublic;
    QString name;
    QString password;
    vector<Connection *> connections;

};

#endif // CHANNEL_H
