#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->button_login->setEnabled(false);
    userData = new IRCData::UserData();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
void LoginDialog::on_button_login_clicked()
{
    userData->username = ui->lineEdit_username->text();
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
    } else {
        QMessageBox::warning(this, "IRC Client",
                             "Can't login. Try other username.");
    }
}

void LoginDialog::on_lineEdit_username_textChanged(const QString &arg1)
{
    if(ui->lineEdit_username->text().length() > 0)
    {
        ui->button_login->setEnabled(true);
    } else
    {
        ui->button_login->setEnabled(false);
    }
}
