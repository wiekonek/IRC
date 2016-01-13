#ifndef LISTENER_H
#define LISTENER_H

#define LISTENER_PORT 9999
#define LISTENER_QUEUE_SIZE 20

#include <QObject>

#include "connection.h"
#include "message.h"
#include "socketmanager.h"

class Listener : public QObject
{
    Q_OBJECT
public:
    Listener(QObject *parent = 0);

signals:
    void onNewConnection(Connection *);

public slots:

private:
    struct sockaddr_in address;

    bool IsLoginMessage(Message &message);
    bool IsRequestMessage(Message &message);
};

#endif // LISTENER_H
