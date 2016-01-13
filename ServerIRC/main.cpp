#include <QCoreApplication>
#include <QObject>

#include "server.h"
#include "listener.h"

#define SERVER_PORT 3333

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc < 2)
    {
        qDebug("Please specify IP adress.\n");
        return a.exec();
    }

    Server* server = new Server();
    Listener* listener = new Listener();

    qDebug("Connecting QT signals...");
    QObject::connect(listener, SIGNAL(onNewConnection(Connection*)),
                     server, SLOT(addConnection(Connection*)));
    qDebug("QT signals connected.");

    return a.exec();
}

