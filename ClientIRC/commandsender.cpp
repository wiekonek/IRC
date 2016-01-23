#include "commandsender.h"
#include "ui_commandsender.h"

CommandSender::CommandSender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandSender)
{
    ui->setupUi(this);
    ui->button_send->setEnabled(false);
}

CommandSender::~CommandSender()
{
    delete ui;
}

void CommandSender::on_button_send_clicked()
{
    QString *str = new QString(ui->plainTextEdit_command->toPlainText());
    QByteArray *data = new QByteArray(QByteArray::fromStdString(str->toStdString()));
    data->append(4);
    ui->plainTextEdit_command->clear();
    emit OnSendCommand(data);
}

void CommandSender::on_plainTextEdit_command_textChanged()
{
    if(ui->plainTextEdit_command->toPlainText().length() < 1)
        ui->button_send->setEnabled(false);
    else
        ui->button_send->setEnabled(true);
}
