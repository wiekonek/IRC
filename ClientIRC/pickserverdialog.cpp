#include "pickserverdialog.h"
#include "ui_pickserverdialog.h"

PickServerDialog::PickServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PickServerDialog)
{
    ui->setupUi(this);
    ip = "";
    port = "";
    ui->button_connect->setEnabled(false);
    ui->lineEdit_port->setValidator( new QIntValidator(100, 60000, this));
}

PickServerDialog::~PickServerDialog()
{
    delete ui;
}

void PickServerDialog::on_lineEdit_ip_textChanged(const QString &arg1)
{
    ip = arg1;
    SetupButton();
}

void PickServerDialog::on_lineEdit_port_textChanged(const QString &arg1)
{
    port = arg1;
    SetupButton();
}

void PickServerDialog::SetupButton()
{
    if(port.length() > 1 && ip.length() > 5)
        ui->button_connect->setEnabled(true);
    else
        ui->button_connect->setEnabled(false);
}

bool PickServerDialog::TryConnect(const char *ipNumber, int portNumber)
{
    // TODO, it should return true if client can connect to that ip and port.
    // It should also setup establishedConnection
    establishedConnection = new Connection();
    return true;
}

void PickServerDialog::on_button_quit_clicked()
{
    emit OnClose();
    this->close();
}

void PickServerDialog::on_button_connect_clicked()
{
    if(TryConnect(ip.toStdString().c_str(), port.toInt())) {
        emit OnConnect(establishedConnection);
        this->close();
    } else {
        qDebug("Can't connect. Try other ip/port");
    }
}
