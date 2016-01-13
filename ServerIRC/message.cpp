#include "message.h"
//qDebug(qPrintable(answear.toString()));


Message::Message()
{
    container = new QJsonObject();
}

void Message::add(QString key, QString value)
{
    QJsonValue *json_value = new QJsonValue(value);
    container->insert(key, *json_value);
}

QString Message::getValue(QString key)
{
    QJsonValue answear = container->value(key);
    return answear.toString();
}

QByteArray Message::toByte()
{
    QJsonDocument *json_document = new QJsonDocument(*container);
    return json_document->toJson();
}

char* Message::toChar()
{
    return toByte().data();
}

void Message::printAll()
{
    QDebug(toByte());
}

