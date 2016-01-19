#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
void LoginDialog::on_button_login_clicked()
{
// TODO zalogowac sieeeee
    IRCData::UserData *userData = new IRCData::UserData();
    userData->username = "admin";
    userData->perrmission = "a";
    emit OnLoggedIn(userData);
    this->close();
}

void LoginDialog::on_button_quit_clicked()
{
    emit OnClose();
    this->close();
}