#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    userData = new IRCData::UserData();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
void LoginDialog::on_button_login_clicked()
{
    userData->username = ui->lineEdit_username->text();
    userData->password = ui->lineEdit_password->text();
    emit OnSendLoginRequest(userData);
}

void LoginDialog::on_button_quit_clicked()
{
    emit OnClose();
    this->close();
}

void LoginDialog::AcceptUser(bool *ok)
{
    if(*ok) {
        emit OnLoggedIn(userData);
        this->close();
    } else
        QMessageBox::warning(this, "IRC Client",
                             "Check login and password.");
}
