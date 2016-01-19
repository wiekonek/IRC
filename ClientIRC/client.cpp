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
    if(mainWindow != NULL)
        mainWindow->close();
    delete mainWindow;
    this->~QObject();

    qDebug("Cleaning!");
}

void Client::Connect(Connection *connection)
{
    // TODO: hehe
    qDebug("Connected!");
    this->connection = connection;


    QObject::connect(connection, SIGNAL(OnMessageReceived(Message*)),
                     this, SLOT(MessageReceived(Message*)));
    QObject::connect(connection, SIGNAL(OnConnectionLost()),
                     this, SLOT(Disconnect()));

    LoginDialog *loginDialog = new LoginDialog();
    loginDialog->show();

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
    if(mainWindow != NULL)
        mainWindow->close();
    qDebug("Cleaning");
    delete this;
}

void Client::LoggedIn(IRCData::UserData *userData)
{
    this->userData = userData;
    qDebug() << "Logged in as:" << userData->username;

    mainWindow = new MainClientWindow(userData);
    mainWindow->show();

    QObject::connect(mainWindow, SIGNAL(OnSendMessage(IRCData::ChannelMessageData*)),
                     connection, SLOT(SendMessage(IRCData::ChannelMessageData*)));
    QObject::connect(mainWindow, SIGNAL(OnClose()), this, SLOT(Cleanup()));

    IRCData::ChannelData *newChannel = new IRCData::ChannelData();
    newChannel->name = "Admin test channel";
    newChannel->users.append("admin");
    newChannel->users.append("testUser");
    mainWindow->AddChannelTab(newChannel);

    IRCData::ChannelData *secondChannel = new IRCData::ChannelData();
    secondChannel->name = "Admin second channel";
    secondChannel->users.append("admin");
    secondChannel->users.append("scondTestUser");
    mainWindow->AddChannelTab(secondChannel);
}

void Client::MessageReceived(Message *message)
{
    // TODO
}

