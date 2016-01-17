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
        return -1;
    }
    setsockopt(socketNumber, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    int bindErr = bind(socketNumber, (struct sockaddr*)&address, sizeof(struct sockaddr));
    if (bindErr < 0)
    {
        fprintf(stderr, "Can't bind a name to a socket.\n");
        return -1;
    }

    int listenErr = listen(socketNumber, queueSize);
    if (listenErr < 0)
    {
        fprintf(stderr, "Can't set queue size.\n");
        return -1;
    }

    return socketNumber;
}

int SocketManager::Accept(sockaddr_in &clientAddress, int listenerSocket)
{
    socklen_t nTmp = sizeof(struct sockaddr);
    int clientSocket = accept(listenerSocket, (struct sockaddr*)&clientAddress, &nTmp);
    if (clientSocket < 0)
    {
       qDebug() << "Can't create a connection's socket.";
       return -1;
    }

    return clientSocket;
}

int SocketManager::Write(int destinationSocket, const char *message, int buffSize)
{
    char buffer[buffSize];
    int n;
    n = sprintf(buffer, message);
    int size = write(destinationSocket, buffer, n);
    return size;
}


int SocketManager::ReadNoWait(int destinationSocket, char *message, int buffSize)
{
    return recv(destinationSocket, message, buffSize, MSG_DONTWAIT);
}

