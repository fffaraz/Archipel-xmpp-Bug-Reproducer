#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include <QtCore>
#include <QObject>

#include "QXmppClient.h"
#include "QXmppMessage.h"

class xmppClient : public QXmppClient
{
    Q_OBJECT
public:
    explicit xmppClient(QObject *parent = 0);
    ~xmppClient();

signals:
    void messageReceived(QString from, QString msg);

public slots:
    void messageReceived(const QXmppMessage&);

};

#endif // XMPPCLIENT_H
