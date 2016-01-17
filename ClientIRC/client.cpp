#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    PickServerDialog *pickServer = new PickServerDialog();
    pickServer->show();

    QObject::connect(pickServer, SIGNAL(OnConnect(Connection*)),
                     this, SLOT(Connect(Connection*)));

    QObject::connect(pickServer, SIGNAL(OnClose()),
                     this, SLOT(Cleanup()));
}

Client::~Client()
{
    delete connection;
    delete userData;
    this->~QObject();
}

void Client::Connect(Connection *connection)
{
    // TODO: hehe
    qDebug("Connected!");
    this->connection = connection;


    QObject::connect(connection, SIGNAL(OnNewMessageReceived(Message*)),
                     this, SLOT(NewMessageReceived(Message*)));
    QObject::connect(connection, SIGNAL(OnConnectionLost()),
                     this, SLOT(Disconnect()));

    LoginDialog *loginDialog = new LoginDialog();

    QObject::connect(loginDialog, SIGNAL(OnLoggedIn(IRCData::UserData*)),
                     this, SLOT(LoggedIn(IRCData::UserData*)));
    QObject::connect(loginDialog, SIGNAL(OnClose()),
                     this, SLOT(Cleanup()));
}

void Client::Disconnect()
{
    qDebug("Disconnected.");
    Cleanup();
}

void Client::Cleanup()
{
    qDebug("Cleaning");

}

void Client::LoggedIn(IRCData::UserData *userData)
{
    // TODO
    qDebug("Logged in.");
}

void Client::NewMessageReceived(Message *message)
{
    // TODO
}

