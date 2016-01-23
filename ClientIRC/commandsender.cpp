#include "commandsender.h"
#include "ui_commandsender.h"

CommandSender::CommandSender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandSender)
{
    ui->setupUi(this);
}

CommandSender::~CommandSender()
{
    delete ui;
}

void CommandSender::on_button_send_clicked()
{

}
