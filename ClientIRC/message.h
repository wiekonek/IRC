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

    QString getValue(QString key);
    QStringList getList(QString key);
    void add(QString key, int value);
    void add(QString key, QString value);
    void add(QString key, QStringList list);

    char* toChar();
    void printAll();
    void printList(QString key);
    QByteArray toByte();

private:
    QJsonObject *container;

};

#endif // MESSAGE_H
