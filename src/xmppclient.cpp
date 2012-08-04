#include "xmppclient.h"

xmppClient::xmppClient(QObject *parent) :
    QXmppClient(parent)
{
    bool check = connect(this, SIGNAL(messageReceived(QXmppMessage)), SLOT(messageReceived(QXmppMessage)));
    Q_ASSERT(check);
    Q_UNUSED(check);

    connect(this, SIGNAL(iqReceived(QXmppIq)), SLOT(iqReceived(QXmppIq)));
}

xmppClient::~xmppClient()
{

}

void xmppClient::messageReceived(const QXmppMessage& message)
{
    QString from = message.from();
    QString msg = message.body();
    // qDebug() << "Type: " << message.type();
    emit messageReceived(from, msg);
}

void xmppClient::Sent(QString message)
{
    emit messageReceived("Me", message);
}

void xmppClient::Sent(const QXmppIq& iq)
{
    QString msg;
    QXmlStreamWriter xml(&msg);
    iq.toXml(&xml);
    emit messageReceived("Me", msg);
}

void xmppClient::iqReceived(const QXmppIq& iq)
{
    QString msg;
    QXmlStreamWriter xml(&msg);
    iq.toXml(&xml);
    emit iqReceived(msg);
}
