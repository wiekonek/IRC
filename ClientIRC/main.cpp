#include "mainclientwindow.h"
#include <QApplication>

#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    new Client();



    return a.exec();
}
