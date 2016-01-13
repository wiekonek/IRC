#ifndef MESSAGE_H
#define MESSAGE_H

#include "socketmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

class Message
{
public:
    Message();
    void add(QString key, QString value);
    QString getValue(QString key);
    QByteArray toByte();
    char* toChar();
    void printAll();

    struct sockaddr_in addres;

private:
    QJsonObject *container;


};

#endif // MESSAGE_H
