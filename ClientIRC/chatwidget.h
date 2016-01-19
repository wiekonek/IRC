#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "datastructures.h"

namespace Ui {
class chatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(IRCData::ChannelData *channelData, QWidget *parent = 0);
    ~ChatWidget();
    void AddMessage(IRCData::MessageData *messageData);
    void Clean();
    IRCData::ChannelData *GetChannelData();

private:
    Ui::chatWidget *ui;

    IRCData::ChannelData *channelData;
};

#endif // CHATWIDGET_H
