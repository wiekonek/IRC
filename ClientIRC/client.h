#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "pickserverdialog.h"
#include "logindialog.h"
#include "mainclientwindow.h"

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
    void MessageReceived(Message *message);

private:
    Connection *connection;
    IRCData::UserData *userData;
    MainClientWindow *mainWindow;
};

#endif // CLIENT_H
