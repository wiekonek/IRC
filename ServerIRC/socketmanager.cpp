#include "socketmanager.h"

void SocketManager::SetupSockaddr(sockaddr_in &address, int portNumber)
{
    memset(&address, 0, sizeof(struct sockaddr));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(portNumber);
}

int SocketManager::CreateSocket(sockaddr_in &address, int queueSize)
{
    int opt = 1;

    int socketNumber = socket(AF_INET, SOCK_STREAM, 0);
    if (socketNumber < 0)
    {
        fprintf(stderr, "Can't create a socket.\n");
        exit(1);
    }
    setsockopt(socketNumber, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    int bindErr = bind(socketNumber, (struct sockaddr*)&address, sizeof(struct sockaddr));
    if (bindErr < 0)
    {
        fprintf(stderr, "Can't bind a name to a socket.\n");
        exit(1);
    }

    int listenErr = listen(socketNumber, queueSize);
    if (listenErr < 0)
    {
        fprintf(stderr, "Can't set queue size.\n");
    }

    return socketNumber;
}


