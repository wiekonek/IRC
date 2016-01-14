#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <QDebug>

class SocketManager
{
public:
    static void SetupSockaddr(struct sockaddr_in &address, int portNumber);
    static int CreateSocket(struct sockaddr_in &address, int queueSize);
    static int Accept(struct sockaddr_in &clientAddress, int listenerSocket);
    static void Write(int destinationSocket, const char *message, int buffSize);
};

#endif // SOCKETMANAGER_H
