#ifndef MAINCLIENTWINDOW_H
#define MAINCLIENTWINDOW_H

#include <QMainWindow>
#include "chatwidget.h"
#include "connection.h"

namespace Ui {
class MainClientWindow;
}

class MainClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainClientWindow(Connection *connection,
            IRCData::UserData *user, QWidget *parent = 0);
    ~MainClientWindow();

    void Disconnected();

signals:
    void OnClose();

public slots:
    void AddChannelTab(IRCData::ChannelData *channelData);
    void AddMessageToChannel(IRCData::MessageData *messageData);


private slots:
    void ChannelCreatedPrompt(bool *ok);

    void CreateNewChannel(QString *channelName);
    void JoinChannel(QString *channelName);
    void SendByteArray(QByteArray *array);

    void on_chatWindow_tabBarClicked(int index);
    void on_button_send_clicked();
    void on_MainClientWindow_destroyed();
    void on_chatWindow_tabCloseRequested(int index);

    void on_actionDisconnect_triggered();
    void on_actionCreate_new_channel_triggered();
    void on_actionConnect_triggered();

private:
    Ui::MainClientWindow *ui;

    QTabWidget *tabbedPane;
    QList<ChatWidget*> channels;
    IRCData::UserData *user;
    Connection *connection;

    void RefreshUserList(int index);
    ChatWidget *GetChannel(QString channelName);
    ChatWidget *GetCurrentChannel();
};

#endif // MAINCLIENTWINDOW_H
