#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>

class Channel : public QObject
{
    Q_OBJECT
public:
    Channel(QObject *parent = 0);

signals:

public slots:
private:
    int port;
    char *name;
};

#endif // CHANNEL_H
