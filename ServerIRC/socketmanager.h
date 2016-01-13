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

class SocketManager
{
public:
    static void SetupSockaddr(struct sockaddr_in &address, int portNumber);
    static int CreateSocket(struct sockaddr_in &address, int queueSize);
};

#endif // SOCKETMANAGER_H
