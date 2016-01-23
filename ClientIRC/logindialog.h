#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include "datastructures.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QWidget
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void OnLoggedIn(IRCData::UserData *userData);
    void OnClose();
    void OnSendLoginRequest(IRCData::UserData *userData);

public slots:
    void AcceptUser(bool *ok);

private slots:
    void on_button_login_clicked();
    void on_button_quit_clicked();

private:
    Ui::LoginDialog *ui;
    IRCData::UserData *userData;
};

#endif // LOGINDIALOG_H
