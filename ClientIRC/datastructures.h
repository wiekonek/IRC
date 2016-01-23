#ifndef DATASTRUCTURES
#define DATASTRUCTURES

#include <QString>

namespace KEYS {
const QString CMD = "command";
const QString USER = "user";
const QString PUBLIC = "public";
const QString PASSWORD = "password";
const QString TEXT = "text";
const QString TYPE = "type";
const QString CHANNEL = "channel";
}

namespace IRCData {
typedef struct MessageData {
    QString content;
    QString username;
    QString channelName;
    MessageData() {}
////    MessageData(Message *message) {
////        content = message->getValue(KEYS::CHANNEL);
////    }
} MessageData;

typedef struct UserData {
    QString username;
    QString password;
    QString perrmission; // ??
} UserData;

typedef struct ChannelData {
    QString name;
    QList<QString> users;
} ChannelData;
}

#endif // DATASTRUCTURES

