#include <QCoreApplication>
#include <QObject>

#include "server.h"
#include "listener.h"

void messageusage();
void listusage();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    if(argc < 2)
//    {
//       qDebug("Please specify IP adress.\n");
//        return a.exec();
//    }

    Server* server = Server::getInstance();
    Listener* listener = Listener::GetInstance();

    qDebug("Connecting QT signals...");
    QObject::connect(listener, SIGNAL(onNewConnection(Connection*)),
                     server, SLOT(addConnection(Connection*)));
    qDebug("QT signals connected.");

    return a.exec();
}


void messageusage()
{
    Message *json_out = new Message(); //tworzymy wiadomosc
    json_out->add("channel", "global channel");
    json_out->add("text", "Siema ziomeczki");
    json_out->add("id", 10);
    json_out->toChar(); // char[] gotowy do wyslania

    char* raw_message = (char*)malloc(100*sizeof(char)); //symulacja odebrania wiadomosci
    strcpy(raw_message, json_out->toChar());

    Message *json_in = new Message(raw_message); //tworzymy jsona z otrzymanej wiadomosci
    json_in->printAll();
    QString value = json_in->getValue("channel");
    //qDebug(qPrintable(value));
    value = json_in->getValue("text");
    //qDebug(qPrintable(value));
}

void listusage()
{
    Message* message = new Message();
    QStringList list;
    list.append("konrad");
    list.append("jacek");
    message->add("list", list);
    message->add("elo", "xD");
    message->printAll();
    message->printList("list");
}

