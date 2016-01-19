#include "chatwidget.h"
#include "ui_chatwidget.h"
#include <QDebug>

ChatWidget::ChatWidget(IRCData::ChannelData *channelData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatWidget)
{
    ui->setupUi(this);
    this->channelData = channelData;
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::AddMessage(IRCData::ChannelMessageData *messageData)
{
    qDebug() << channelData->name
             << messageData->username
             << messageData->content;
    QString userNamePrefix = "<p style=\" margin-top:0px; margin-bottom:0px;"
                             "margin-left:0px; margin-right:0px;"
                             "-qt-block-indent:0; text-indent:0px;\""
                             "<span style=\" font-size:12pt;"
                             "font-weight:600;\">";
    QString userNameSufix = "</span></p>";
    QString contentPrefix = "<p align=\"right\" style=\" margin-top:0px;"
                            "margin-bottom:0px; margin-left:0px;"
                            "margin-right:0px; -qt-block-indent:0;"
                            "text-indent:0px;\">";
    QString contentSufix = "<br /></p>";

    ui->textBrowser->append(messageData->username);

    ui->textBrowser->append(">>>" + messageData->content);
//    ui->textBrowser->insertHtml(userNamePrefix + messageData->username
//                                 + userNameSufix);

}

void ChatWidget::Clean()
{
    // TODO
}

IRCData::ChannelData *ChatWidget::GetChannelData()
{
    return channelData;
}
