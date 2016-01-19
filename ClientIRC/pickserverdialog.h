#ifndef PICKSERVERDIALOG_H
#define PICKSERVERDIALOG_H

#include <QDialog>
#include <QtNetwork>

#include "connection.h"

namespace Ui {
class PickServerDialog;
}

class PickServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PickServerDialog(QWidget *parent = 0);
    ~PickServerDialog();

signals:
    void OnClose();
    void OnConnect(Connection *connection);

private slots:
    void on_lineEdit_ip_textChanged(const QString &arg1);
    void on_lineEdit_port_textChanged(const QString &arg1);
    void on_button_quit_clicked();
    void on_button_connect_clicked();
    void OnSocketConnected();


private:
    Ui::PickServerDialog *ui;

    QString port;
    QString ip;
    Connection *establishedConnection;

    void SetupButton();
    bool TryConnect(const char *ipNumber, int portNumber);
};

#endif // PICKSERVERDIALOG_H
