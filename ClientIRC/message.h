#ifndef MESSAGE_H
#define MESSAGE_H

#define LOGIN 0
#define CREATE 1
#define JOIN 2
#define LEAVE 3
#define MESSAGE 4
#define DISCONNECT 5

#define LOGIN_ACC 6
#define CREATE_ACC 7
#define JOIN_ACC 8
#define LEAVE_ACC 9
#define WELCOME 10
#define ERROR

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
