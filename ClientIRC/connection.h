#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "message.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = 0);

signals:
    void OnMessageReceived(Message *message);
    void OnConnectionLost();

public slots:

private:
    void ConnectionLoop();
};

#endif // CONNECTION_H
