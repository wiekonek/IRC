#include "mainclientwindow.h"
#include "ui_mainclientwindow.h"

MainClientWindow::MainClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainClientWindow)
{
    ui->setupUi(this);
}

MainClientWindow::~MainClientWindow()
{
    delete ui;
}
