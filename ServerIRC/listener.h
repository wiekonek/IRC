#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

#include "connection.h"


class Listener : public QObject
{
    Q_OBJECT
public:
    Listener(QObject *parent = 0);
    void NewUser();

signals:
    void newConnection(Connection *);

public slots:
};

#endif // LISTENER_H
