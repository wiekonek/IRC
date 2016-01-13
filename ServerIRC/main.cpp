#include <QCoreApplication>
#include <QObject>

#include <iostream>

#include "server.h"
#include "listener.h"

using std::cout;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server* server = new Server();
    Listener* listener = new Listener();

    cout<<"Connecting signals...\n";
    QObject::connect(listener, SIGNAL(newConnection(Connection*)),
                     server, SLOT(addConnection(Connection*)));

    cout<<"Signals connected.\n";


    listener->NewUser();


    return a.exec();
}

