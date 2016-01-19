#ifndef MAINCLIENTWINDOW_H
#define MAINCLIENTWINDOW_H

#include <QMainWindow>
#include "chatwidget.h"

namespace Ui {
class MainClientWindow;
}

class MainClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainClientWindow(IRCData::UserData *user, QWidget *parent = 0);
    ~MainClientWindow();

signals:
    void OnClose();
    void OnSendMessage(IRCData::MessageData *messageData);
    void OnJoinChannelRequest(IRCData::MessageData *messageData);
    void OnLeaveChannel(IRCData::ChannelData *channelData);

public slots:
    void AddChannelTab(IRCData::ChannelData *channelData);
    void AddMessageToChannel(IRCData::MessageData *messageData);


private slots:
    void on_chatWindow_tabBarClicked(int index);
    void on_button_send_clicked();
    void on_actionDisconnect_triggered();
    void on_MainClientWindow_destroyed();

private:
    Ui::MainClientWindow *ui;

    QTabWidget *tabbedPane;
    QList<ChatWidget*> channels;
    IRCData::UserData *user;

    void RefreshUserList(int index);
    ChatWidget *GetChannel(QString channelName);
    ChatWidget *GetCurrentChannel();
};

#endif // MAINCLIENTWINDOW_H
