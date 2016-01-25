#include "message.h"
#include <QDebug>

Message::Message()
{
    container = new QJsonObject();
}

Message::Message(const char* json)
{
    QByteArray *byte_array = new QByteArray(json);

    QJsonDocument *json_document = new QJsonDocument();
    QJsonParseError *error = new QJsonParseError();
    QJsonDocument return_json = json_document->fromJson(*byte_array, error);

    if(error->offset != 0)
        qDebug("error : %s", qPrintable(error->errorString()));
    else
    {
        QJsonObject container = return_json.object();
        this->container = new QJsonObject(container);
    }
    delete(byte_array);
    delete(json_document);
    delete(error);
}

QString Message::getValue(QString key)
{
    if(container->value(key) != QJsonValue::Undefined)
    {
        QJsonValue answear = container->value(key);
        return answear.toString();
    }
    else
    {
        return "";
    }
}

QStringList Message::getList(QString key)
{
    QJsonArray array = container->value(key).toArray();
    QStringList list;
    for(auto element : array)
    {
        list.append(element.toString());
    }
    return list;
}

void Message::add(QString key, QString value)
{
    QJsonValue *json_value = new QJsonValue(value); //to mozna zmienic!
    container->insert(key, *json_value);
    delete(json_value);
}

void Message::add(QString key, qint32 value)
{
    add(key, QString::number(value));
}

void Message::add(QString key, QStringList list)
{
    QJsonArray array;
    for(QString element : list)
    {
        QJsonValue json_value(element);
        array.append(json_value);
    }
    container->insert(key, array);
}

QByteArray Message::toByte()
{
    QJsonDocument json_document(*container);
    return json_document.toJson();
}

char* Message::toChar()
{
    return toByte().data();
}

void Message::printAll()
{
    qDebug("%s", toChar());
}

void Message::printList(QString key)
{
    for(auto element: getList(key))
    {
        qDebug("%s", element.toStdString().c_str());
    }
}
