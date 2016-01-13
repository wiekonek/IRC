#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent)
{
    qDebug("Setup listener socket...");
    SocketManager::SetupSockaddr(address, LISTENER_PORT);
    int listenerSocket = SocketManager::CreateSocket(address, LISTENER_QUEUE_SIZE);
    qDebug("Listener socket working.");

    struct sockaddr_in clientAddress;
    while(1)
    {
        socklen_t nTmp = sizeof(struct sockaddr);
        int clientSocket = accept(listenerSocket, (struct sockaddr*)&clientAddress, &nTmp);
        if (clientSocket < 0)
        {
           fprintf(stderr, "Can't create a connection's socket.\n");
           exit(1);
        }

        time_t now;
        struct tm *local;
        time (&now);
        local = localtime(&now);
        char buffer[50];
        int n;
        n = sprintf(buffer, "%s\n", asctime(local));
        write(clientSocket, buffer, n);
        close(clientSocket);
    }

    close(listenerSocket);
}
