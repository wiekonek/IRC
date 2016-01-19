#include "mainclientwindow.h"
#include "ui_mainclientwindow.h"
#include "chatwidget.h"
#include <QStandardItemModel>

MainClientWindow::MainClientWindow(IRCData::UserData *user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainClientWindow)
{
    ui->setupUi(this);
    this->user = user;
    tabbedPane = ui->chatWindow;
    tabbedPane->removeTab(0);

    ui->label_userName->setText(user->username);
}

MainClientWindow::~MainClientWindow()
{
    emit OnClose();
    delete ui;
}

void MainClientWindow::AddChannelTab(IRCData::ChannelData *channel)
{
    ChatWidget *newTab = new ChatWidget(channel, tabbedPane);
    tabbedPane->addTab(newTab, channel->name);
    channels.append(newTab);

    IRCData::MessageData message;
    message.channelName = channel->name;
    message.username = user->username;
    message.content = "Join to channel!";

    AddMessageToChannel(&message);
    AddMessageToChannel(&message);

    RefreshUserList(0);
}

void MainClientWindow::AddMessageToChannel(IRCData::MessageData *messageData)
{
    ChatWidget *widget = GetChannel(messageData->channelName);
    widget->AddMessage(messageData);
}

void MainClientWindow::on_chatWindow_tabBarClicked(int index)
{
    // TODO
    RefreshUserList(index);
}

void MainClientWindow::on_button_send_clicked()
{
    IRCData::MessageData *message = new IRCData::MessageData();
    message->channelName = GetCurrentChannel()->GetChannelData()->name;
    message->content = ui->lineEdit_message->text();
    message->username = user->username;

    ui->lineEdit_message->setText("");

    emit OnSendMessage(message);
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
