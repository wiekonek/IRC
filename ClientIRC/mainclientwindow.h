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
    explicit MainClientWindow(QWidget *parent = 0);
    ~MainClientWindow();

signals:
    void OnSendMessage(IRCData::MessageData *message);
    void OnQuitChannel(IRCData::ChannelData *channel);

public slots:
    void AddChannelTab(IRCData::ChannelData *channel);
    void AddMessageToChannel(IRCData::MessageData *message);


private slots:
    void on_chatWindow_tabBarClicked(int index);
    void on_button_send_clicked();

private:
    Ui::MainClientWindow *ui;

    QTabWidget *tabbedPane;
    QList<IRCData::ChannelData*> channels;

    void RefreshUserList();
};

#endif // MAINCLIENTWINDOW_H
