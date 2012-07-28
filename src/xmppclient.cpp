#include "xmppclient.h"

xmppClient::xmppClient(QObject *parent) :
    QXmppClient(parent)
{
    bool check = connect(this, SIGNAL(messageReceived(QXmppMessage)), SLOT(messageReceived(QXmppMessage)));
    Q_ASSERT(check);
    Q_UNUSED(check);
}

xmppClient::~xmppClient()
{

}

void xmppClient::messageReceived(const QXmppMessage& message)
{
    QString from = message.from();
    QString msg = message.body();

    emit messageReceived(from, msg);
}
