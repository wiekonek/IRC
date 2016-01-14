#include "listener.h"

#include <QDebug>

Listener::Listener(QObject *parent) : QObject(parent)
{
    qDebug("Setup listener socket...");
    SocketManager::SetupSockaddr(address, LISTENER_PORT);
    listenerSocket = SocketManager::CreateSocket(address, LISTENER_QUEUE_SIZE);
    qDebug("Listener socket working.");

    ListenerLoop();
}

void Listener::SetListening(bool isActive)
{
    Listen = isActive;
}

Listener::~Listener()
{
    close(listenerSocket);
}

void Listener::ListenerLoop()
{
    struct sockaddr_in clientAddress;
    while(Listen)
    {
        int clientSocket = SocketManager::Accept(clientAddress, listenerSocket);
        qDebug() << "New connection slot granted." << "Port:" << clientAddress.sin_port;

        onNewConnection(new Connection(clientSocket, clientAddress));
    }
}


