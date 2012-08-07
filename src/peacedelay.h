#ifndef PEACEDELAY_H
#define PEACEDELAY_H

#include <QTime>
#include <QString>

struct PeaceDelay
{
    bool isReceived;
    QString IqId;
    int delayms;
    QTime timer;

    PeaceDelay()
    {
        isReceived=false;
        delayms=-1;
    }
};

#endif // PEACEDELAY_H
