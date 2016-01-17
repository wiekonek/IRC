#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "pickserverdialog.h"
#include "logindialog.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();

signals:

public slots:
    void Connect(Connection *connection);
    void Disconnect();
    void Cleanup();
    void LoggedIn(IRCData::UserData *userData);
    void NewMessageReceived(Message *message);

private:
    Connection *connection;
    IRCData::UserData *userData;
};

#endif // CLIENT_H
