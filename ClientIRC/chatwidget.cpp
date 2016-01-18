#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QString channelName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatWidget)
{
    ui->setupUi(this);
    this->channelName = channelName;
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::AddMessage(IRCData::MessageData *messageData)
{
    // TODO do it better, with html
    ui->textBrowser->append(messageData->username);
    ui->textBrowser->append(messageData->content);
}

void ChatWidget::Clean()
{
    // TODO
}

QString ChatWidget::GetChannelName()
{
    return channelName;
}
