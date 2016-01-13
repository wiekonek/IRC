#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent)
{

}


void Listener::NewUser()
{
    Connection* connection = new Connection();
    emit newConnection(connection);
}
