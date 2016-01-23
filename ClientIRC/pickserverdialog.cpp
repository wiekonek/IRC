 #include "pickserverdialog.h"
#include "ui_pickserverdialog.h"

#include <QMessageBox>

PickServerDialog::PickServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PickServerDialog)
{
    ui->setupUi(this);
    ip = ui->lineEdit_ip->text();
    port = ui->lineEdit_port->text();
    SetupButton();
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
    QTcpSocket *tcpSocket = new QTcpSocket();
    tcpSocket->connectToHost(ipNumber, portNumber);

    if(tcpSocket->waitForConnected()) {
        establishedConnection = new Connection(tcpSocket);
        return true;
    }

    return false;
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
        QMessageBox::warning(this, "IRC Client",
                             "Can't connect. "
                             "Please check the ip and port.");
        qDebug("Can't connect. Try other ip/port");
    }
}
