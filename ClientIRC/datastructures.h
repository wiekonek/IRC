#ifndef DATASTRUCTURES
#define DATASTRUCTURES

#include <QString>
#include <vector>

namespace IRCData {
typedef struct channelMessageData {
    QString content;
    QString username;
    QString channelName;
} ChannelMessageData;

typedef struct commandMessageData {
    QString command;
} CommandMessaegData;

typedef struct userData {
    QString username;
    QString perrmission; // ??
} UserData;

typedef struct channelData {
    QString name;
    QList<QString> users;
} ChannelData;
}

#endif // DATASTRUCTURES

