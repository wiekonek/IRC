#ifndef MESSAGE_H
#define MESSAGE_H

#include "socketmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>

class Message
{
public:
    Message();
    Message(char* json);

    void add(QString key, QString value);
    void add(QString key, int value);

    QByteArray toByte();
    char* toChar();

    QString getValue(QString key);
    void printAll();

private:
    QJsonObject *container;

};

#endif // MESSAGE_H
