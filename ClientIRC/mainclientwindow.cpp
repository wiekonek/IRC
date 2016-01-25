#include "mainclientwindow.h"
#include "ui_mainclientwindow.h"
#include "chatwidget.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include "stringpicker.h"
#include "commandsender.h"

MainClientWindow::MainClientWindow(Connection *connection,
                                   IRCData::UserData *user, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainClientWindow)
{
    ui->setupUi(this);
    this->user = user;
    this->connection = connection;
    tabbedPane = ui->chatWindow;
    tabbedPane->removeTab(0);
    ui->label_userName->setText(user->username);
    ui->button_send->setEnabled(false);

    connect(connection, SIGNAL(OnMessageReceived(IRCData::MessageData*)),
            this, SLOT(AddMessageToChannel(IRCData::MessageData*)));
    connect(connection, SIGNAL(OnConnectToChannel(IRCData::ChannelData*)),
            this, SLOT(AddChannelTab(IRCData::ChannelData*)));
    connect(connection, SIGNAL(OnCreateChannel(bool*)),
            this, SLOT(ChannelCreatedPrompt(bool*)));
    connect(connection, SIGNAL(OnNewUserList(IRCData::ChannelData*)),
            this, SLOT(RefreshUsers(IRCData::ChannelData*)));
}

MainClientWindow::~MainClientWindow()
{
    emit OnClose();
    delete ui;
}

void MainClientWindow::Disconnected()
{
    QMessageBox::warning(this, "Server", "Server error. Disconnected.");
    this->close();
}

void MainClientWindow::AddChannelTab(IRCData::ChannelData *channel)
{
    ChatWidget *newTab = new ChatWidget(channel, tabbedPane);
    tabbedPane->addTab(newTab, channel->name);
    channels.append(newTab);

    ui->button_send->setEnabled(true);
    RefreshUserList(0);
}

void MainClientWindow::AddMessageToChannel(IRCData::MessageData *messageData)
{
    ChatWidget *widget = GetChannel(messageData->channelName);
    widget->AddMessage(messageData);
}

void MainClientWindow::ChannelCreatedPrompt(bool *ok)
{
    if(*ok)
        QMessageBox::information(this, "Channel", "Channel created.");
    else
        QMessageBox::warning(this, "Channel", "Channel didn't created. "
                                              "Probably channel with specific "
                                              "name already exists. "
                                              "Try other name.");
}

void MainClientWindow::CreateNewChannel(QString *channelName)
{
    IRCData::ChannelData *channelData = new IRCData::ChannelData();
    channelData->name = *channelName;
    QList<QString> *userList = new QList<QString>();
    userList->append(user->username);
    channelData->users = *userList;
    connection->SendCreateChannelRequest(channelData);
}

void MainClientWindow::JoinChannel(QString *channelName)
{
    IRCData::ChannelData *channelData = new IRCData::ChannelData();
    channelData->name = *channelName;
    channelData->users = QList<QString>();
    connection->SendJoinChannelRequest(channelData);
}

void MainClientWindow::SendByteArray(QByteArray *array)
{
    connection->SendByteArray(array);
}

void MainClientWindow::RefreshUsers(IRCData::ChannelData *channelData)
{
    GetChannel(channelData->name)->GetChannelData() = channelData;
    RefreshUserList(tabbedPane->currentIndex());
}

void MainClientWindow::on_chatWindow_tabBarClicked(int index)
{
    RefreshUserList(index);
}

void MainClientWindow::on_button_send_clicked()
{
    IRCData::MessageData *message = new IRCData::MessageData();
    message->channelName = GetCurrentChannel()->GetChannelData()->name;
    message->content = ui->lineEdit_message->text();
    message->username = user->username;

    ui->lineEdit_message->setText("");

    connection->SendMessage(message);
}

void MainClientWindow::RefreshUserList(int index)
{
    QString channelName = tabbedPane->tabText(index);
    IRCData::ChannelData *channelData =
            GetChannel(channelName)->GetChannelData();
    QStandardItemModel *model =
            new QStandardItemModel(ui->listView_channelUsers);

    for(int i = 0; i < channelData->users.size(); i++)
        model->appendRow(new QStandardItem(channelData->users[i]));
    ui->listView_channelUsers->setModel(model);
}

ChatWidget *MainClientWindow::GetChannel(QString channelName)
{
    for(int i=0; i<channels.size(); i++) {
        if(channels[i]->GetChannelData()->name == channelName)
            return channels[i];
    }
    return NULL;
}

ChatWidget *MainClientWindow::GetCurrentChannel()
{
    QString name = ((ChatWidget*)tabbedPane->currentWidget())
            ->GetChannelData()->name;
    return GetChannel(name);
}

void MainClientWindow::on_actionDisconnect_triggered()
{
    emit OnClose();
    close();
}

void MainClientWindow::on_MainClientWindow_destroyed()
{
    emit OnClose();
}

void MainClientWindow::on_chatWindow_tabCloseRequested(int index)
{
    IRCData::ChannelData *channelData = new IRCData::ChannelData();
    channelData->name = tabbedPane->tabText(index);
    connection->SendLeaveChannel(channelData);
    tabbedPane->removeTab(index);
}

void MainClientWindow::on_actionCreate_new_channel_triggered()
{
    StringPicker *channelNamePicker
            = new StringPicker("New channel", "Pick new channel name", "Create");
    QObject::connect(channelNamePicker, SIGNAL(OnValuePicked(QString*)),
                                      this, SLOT(CreateNewChannel(QString*)));
    channelNamePicker->show();
}

void MainClientWindow::on_actionConnect_triggered()
{
    StringPicker *channelNamePicker
            = new StringPicker("Connect", "Pick channel name", "Connect");
    QObject::connect(channelNamePicker, SIGNAL(OnValuePicked(QString*)),
                                      this, SLOT(JoinChannel(QString*)));
    channelNamePicker->show();
}

void MainClientWindow::on_actionRaw_commands_triggered()
{
        CommandSender *cmdSender = new CommandSender();
        QObject::connect(cmdSender, SIGNAL(OnSendCommand(QByteArray*)),
                         this, SLOT(SendByteArray(QByteArray*)));
        cmdSender->show();
}
