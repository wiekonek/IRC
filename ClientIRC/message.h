#ifndef MESSAGE_H
#define MESSAGE_H

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
    Message(const char* json);

    int GetCommand();

    QString getValue(QString key);
    void add(QString key, int value);
    void add(QString key, QString value);

    char* toChar();
    void printAll();
    QByteArray toByte();

private:
    QJsonObject *container;

};

#endif // MESSAGE_H
