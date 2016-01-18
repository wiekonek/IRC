#ifndef DATASTRUCTURES
#define DATASTRUCTURES

#include <QString>
#include <vector>

namespace IRCData {
typedef struct messageData {
    QString content;
    QString username;
    QString channel;
} MessageData;

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

