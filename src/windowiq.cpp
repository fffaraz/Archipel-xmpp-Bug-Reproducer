#include "windowiq.h"
#include "ui_windowiq.h"

WindowIq::WindowIq(xmppClient* Client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowIq),
    client(Client)
{
    ui->setupUi(this);
}

WindowIq::~WindowIq()
{
    delete ui;
}

void WindowIq::on_btnSend_clicked()
{
    QXmppElementList el;

    QXmppElement el1;
    el1.setTagName("query");
    el1.setAttribute("xmlns", ui->txtPlugin->text());
    QXmppElement el2;
    el2.setTagName("archipel");
    el2.setAttribute("action", ui->txtAction->text());
    el1.appendChild(el2);

    el.append(el1);

    QXmppIq iq;
    iq.setTo(ui->txtTarget->text());
    iq.setExtensions(el);
    client->sendPacket(iq);
    client->Sent(iq);
}
