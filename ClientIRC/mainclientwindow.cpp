#include "mainclientwindow.h"
#include "ui_mainclientwindow.h"
#include "chatwidget.h"
#include <QStandardItemModel>

MainClientWindow::MainClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainClientWindow)
{
    ui->setupUi(this);
    tabbedPane = ui->chatWindow;
    tabbedPane->removeTab(0);

    tabbedPane->addTab(new ChatWidget("Example Channel", this->tabbedPane),
                       "Example Channel");
}

MainClientWindow::~MainClientWindow()
{
    delete ui;
}

void MainClientWindow::AddChannelTab(IRCData::ChannelData *channel)
{
    // TODO

}

void MainClientWindow::AddMessageToChannel(IRCData::MessageData *message)
{
    // TODO
}

void MainClientWindow::on_chatWindow_tabBarClicked(int index)
{
    // TODO
}

void MainClientWindow::on_button_send_clicked()
{
    // TODO
    //emit
    RefreshUserList();
}

void MainClientWindow::RefreshUserList()
{
    QString name = ((ChatWidget*)tabbedPane->currentWidget())->GetChannelName();
    for(int i=0; i < channels.size(); i++) {
        IRCData::ChannelData *channel;
        if(channels[i]->name == name) {
            channel=channels[i];
            QStandardItemModel *model = new QStandardItemModel();
            for(int k = 0; k < channel->users.size(); k++)
                model->appendRow(new QStandardItem(channel->users[k]));
            ui->listView_channelUsers->setModel(model);
        }
    }
}
