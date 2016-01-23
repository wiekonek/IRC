#ifndef COMMANDSENDER_H
#define COMMANDSENDER_H

#include <QWidget>
#include <QByteArray>

namespace Ui {
class CommandSender;
}

class CommandSender : public QWidget
{
    Q_OBJECT

public:
    explicit CommandSender(QWidget *parent = 0);
    ~CommandSender();

signals:
    void OnSendCommand(QByteArray *array);

private slots:
    void on_button_send_clicked();

    void on_plainTextEdit_command_textChanged();

private:
    Ui::CommandSender *ui;
};

#endif // COMMANDSENDER_H
