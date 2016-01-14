#include "message.h"
#include <QDebug>

Message::Message()
{
    container = new QJsonObject();
}

Message::Message(char* json)
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
}

void Message::add(QString key, QString value)
{
    QJsonValue *json_value = new QJsonValue(value);
    container->insert(key, *json_value);
}

void Message::add(QString key, qint32 value)
{
    add(key, QString::number(value));
}

QString Message::getValue(QString key)
{
    QJsonValue answear = container->value(key);
    //qDebug(qPrintable(answear.toString()));
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
    qDebug("%s", toChar());
}


/*qDebug("%d", toByte().size());
QByteArray array = toByte();
char* data = array.data();
QByteArray *json_array = new QByteArray(data);
QJsonDocument *doc = new QJsonDocument();
QJsonParseError *error = new QJsonParseError();
QJsonDocument ret_doc = doc->fromJson(*json_array, error);
qDebug(ret_doc.toJson());*/
