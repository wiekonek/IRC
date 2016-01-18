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

    explicit ChatWidget(QString channelName, QWidget *parent = 0);
    ~ChatWidget();
    void AddMessage(IRCData::MessageData *messageData);
    void Clean();
    QString GetChannelName();

private:
    Ui::chatWidget *ui;

    QString channelName;
};

#endif // CHATWIDGET_H
