#include "windowpeace.h"
#include "ui_windowpeace.h"

WindowPeace::WindowPeace(xmppClient* Client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowPeace),
    client(Client)
{
    ui->setupUi(this);
    _isStarted = false;
    el1 = new QXmppElement();
    connect(&_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
    connect(Client, SIGNAL(iqReceived(QXmppIq)), this, SLOT(iqReceived(QXmppIq)));
    on_btnClear_clicked();
}

WindowPeace::~WindowPeace()
{
    delete ui;
}

void WindowPeace::on_btnSend_clicked()
{
    el.clear();
    el.append(*el1);
    QString target = ui->txtTarget->text();
    for(int i=0, e=ui->spinConcurrent->value(); i<e; ++i)
    {
        QXmppIq iq;
        iq.setTo(target);
        iq.setExtensions(el);
        qDebug() << "IQ ID: " << iq.id();
        // TODO: add to qmap
        client->sendPacket(iq);
        client->Sent(iq);
    }
}

void WindowPeace::on_txtAttr1_returnPressed()
{
    ui->txtAttr2->setFocus();
}

void WindowPeace::on_txtAttr2_returnPressed()
{
    ui->btnAddAttr->setFocus();
}

void WindowPeace::on_btnClear_clicked()
{
    delete el1;
    el1 = new QXmppElement();
    el1->setTagName(ui->txtTagName->text());
    el1->setAttribute("xmlns", ui->txtXmlns->text());
    updateXML();
}

void WindowPeace::on_btnAddAttr_clicked()
{
    el1->setAttribute(ui->txtAttr1->text(), ui->txtAttr2->text());
    ui->lstAttrs->addItem(ui->txtAttr1->text() + " = \"" + ui->txtAttr2->text() + "\"");
    ui->txtAttr1->clear();
    ui->txtAttr2->clear();
    updateXML();
}

void WindowPeace::on_btnAddChild_clicked()
{
    ui->lstAttrs->addItem("<" + ui->txtAttr1->text() + ">" + ui->txtAttr2->text() + "</" + ui->txtAttr1->text() + ">");
    QXmppElement tmp;
    tmp.setTagName(ui->txtAttr1->text());
    tmp.setValue(ui->txtAttr2->text());
    el1->appendChild(tmp);
    ui->txtAttr1->clear();
    ui->txtAttr2->clear();
    updateXML();
}

void WindowPeace::iqReceived(const QXmppIq &)
{

}

void WindowPeace::onTimerTimeout()
{
    on_btnSend_clicked();
}

void WindowPeace::updateXML()
{
    QString msg;
    QXmlStreamWriter xml(&msg);
    el1->toXml(&xml);
    ui->txtXML->setPlainText(msg);
    //qDebug() << "makeXML: " << msg;
}



void WindowPeace::on_btnStart_clicked()
{
    if(_isStarted)
    {
        _isStarted = false;
        ui->btnStart->setText("Start");
        ui->btnSend->setEnabled(true);
        ui->txtTarget->setEnabled(true);
    }
    else
    {
        _isStarted = true;
        ui->btnStart->setText("Stop");
        ui->btnSend->setEnabled(false);
        ui->txtTarget->setEnabled(false);
    }
}
