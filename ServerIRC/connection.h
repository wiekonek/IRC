#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "message.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QObject *parent = 0);
    void Send(Message *message);
    void Close();
signals:

public slots:

private:

};

#endif // CONNECTION_H
