#include "client.h"

#include <QDebug>

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
    delete mainWindow;
    this->~QObject();
}

void Client::Connect(Connection *connection)
{
    qDebug("Connected!");
    this->connection = connection;

    QObject::connect(connection, SIGNAL(OnConnectionLost()),
                     this, SLOT(Disconnect()));

    LoginDialog *loginDialog = new LoginDialog();
    loginDialog->show();

    QObject::connect(loginDialog, SIGNAL(OnLoggedIn(IRCData::UserData*)),
                     this, SLOT(LoggedIn(IRCData::UserData*)));
    QObject::connect(loginDialog, SIGNAL(OnClose()),
                     this, SLOT(Cleanup()));
    QObject::connect(loginDialog,
                     SIGNAL(OnSendLoginRequest(IRCData::UserData*)),
                     connection, SLOT(SendLoginRequest(IRCData::UserData*)));
    QObject::connect(connection, SIGNAL(OnAcceptUser(bool*)), loginDialog,
                     SLOT(AcceptUser(bool*)));
}

void Client::Disconnect()
{
    qDebug("Disconnected.");
    Cleanup();
    mainWindow->Disconnected();
}

void Client::Cleanup()
{
    qDebug("Cleaning");
}

void Client::LoggedIn(IRCData::UserData *userData)
{
    this->userData = userData;
    qDebug() << "Logged in as:" << userData->username;

    mainWindow = new MainClientWindow(connection, userData);
    mainWindow->show();

    QObject::connect(mainWindow, SIGNAL(OnClose()), this, SLOT(Cleanup()));
}


