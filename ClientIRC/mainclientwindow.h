#ifndef MAINCLIENTWINDOW_H
#define MAINCLIENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainClientWindow;
}

class MainClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainClientWindow(QWidget *parent = 0);
    ~MainClientWindow();

private:
    Ui::MainClientWindow *ui;
};

#endif // MAINCLIENTWINDOW_H
