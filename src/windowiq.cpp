#include "windowiq.h"
#include "ui_windowiq.h"

WindowIq::WindowIq(xmppClient* Client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowIq),
    client(Client)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    _isStarted = false;
    connect(&_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
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

    QList<QString> keys = _attrs.keys();
    for(int i=0; i<keys.count(); ++i)
    {
        el2.setAttribute(keys[i], _attrs[keys[i]]);
    }


    el1.appendChild(el2);

    el.append(el1);

    QXmppIq iq;
    iq.setTo(ui->txtTarget->text());
    iq.setExtensions(el);
    client->sendPacket(iq);
    client->Sent(iq);
}

void WindowIq::on_btnClear_clicked()
{
    _attrs.clear();
    ui->lstAttrs->clear();
}


void WindowIq::on_txtAttr1_returnPressed()
{
    ui->txtAttr2->setFocus();
}

void WindowIq::on_txtAttr2_returnPressed()
{
    QString s1 = ui->txtAttr1->text();
    QString s2 = ui->txtAttr2->text();
    _attrs[s1] = s2;
    ui->lstAttrs->addItem(s1 + " = " + s2);
    ui->txtAttr1->clear();
    ui->txtAttr2->clear();
    ui->txtAttr1->setFocus();
}

void WindowIq::on_btnStart_clicked()
{
    if(_isStarted)
    {
        _isStarted = false;
        ui->btnStart->setText("Start");
        ui->btnSend->setEnabled(true);
        _timer.stop();
    }
    else
    {
        _isStarted = true;
        ui->btnStart->setText("Stop");
        ui->btnSend->setEnabled(false);
        _timer.setInterval(ui->spinDelayLoop->value());
        _timer.start();
    }
}

void WindowIq::onTimerTimeout()
{
    on_btnSend_clicked();
}
