#include "windowpeace.h"
#include "ui_windowpeace.h"

WindowPeace::WindowPeace(xmppClient* Client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowPeace),
    client(Client)
{
    ui->setupUi(this);
    _isStarted = false;
    _delays = new QList<PeaceDelay*>();
    el1 = new QXmppElement();
    connect(&_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
    connect(Client, SIGNAL(iqReceived(QXmppIq)), this, SLOT(iqReceived(QXmppIq)));
    on_btnClear_clicked();
    _avg_t=0;
    _avg_n=0;
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
        //qDebug() << "IQ ID: " << iq.id();

        PeaceDelay* d = new PeaceDelay();
        d->IqId = iq.id();
        _delays->append(d);

        client->sendPacket(iq);
        d->timer.start();
        client->Sent(iq);
    }

    if(!_timer.isActive())
    {
        updateDelays();
        _timer.singleShot(500, this, SLOT(onTimerTimeout()));
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

void WindowPeace::iqReceived(const QXmppIq &iq)
{
    for(int i=0; i<_delays->count(); ++i)
        if(_delays->value(i)->IqId == iq.id())
        {
            PeaceDelay* p = _delays->value(i);
            p->isReceived = true;
            p->delayms = p->timer.elapsed();
            _avg_t += p->delayms;
            ++_avg_n;
        }
}

void WindowPeace::onTimerTimeout()
{
    if(_isStarted)
            on_btnSend_clicked();
    updateDelays();
}

void WindowPeace::updateXML()
{
    QString msg;
    QXmlStreamWriter xml(&msg);
    el1->toXml(&xml);
    ui->txtXML->setPlainText(msg);
    //qDebug() << "makeXML: " << msg;
}

void WindowPeace::updateDelays()
{
    ui->lstDelays->clear();
    for(int i=0; i<_delays->count(); ++i)
    {
        int value = _delays->value(i)->delayms;
        QString iq = _delays->value(i)->IqId;
        ui->lstDelays->addItem(iq + " : " + QString::number(value) + " ms");
    }
    ui->lstDelays->scrollToBottom();
    if(_avg_n>0)
        ui->lblAvg->setText("Average : " + QString::number( ((double)_avg_t)/_avg_n ) + "  (n=" + QString::number(_avg_n) + ")");
    else
        ui->lblAvg->setText("Average : ---");
}


void WindowPeace::on_btnStart_clicked()
{
    if(_isStarted)
    {
        _isStarted = false;
        ui->btnStart->setText("Start");
        ui->btnSend->setEnabled(true);
        ui->txtTarget->setEnabled(true);
        _timer.stop();
        updateDelays();
        _timer.singleShot(500, this, SLOT(onTimerTimeout()));
    }
    else
    {
        _isStarted = true;
        ui->btnStart->setText("Stop");
        ui->btnSend->setEnabled(false);
        ui->txtTarget->setEnabled(false);

        on_btnClearRes_clicked();

        _timer.start(ui->spinDelayLoop->value());
    }
}

void WindowPeace::on_btnCopy_clicked()
{
    QStringList texts;
    QList<QListWidgetItem *> items = ui->lstDelays->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    foreach(QListWidgetItem *item, items)
        texts << item->text();

    texts << "--------";
    texts << ui->lblAvg->text();

    QApplication::clipboard()->setText(texts.join("\n"));
}

void WindowPeace::on_btnClearRes_clicked()
{
    for(int i=0; i<_delays->count(); ++i)
        delete _delays->value(i);
    delete _delays;
    _delays = new QList<PeaceDelay*>();
    _avg_t=0;
    _avg_n=0;
    updateDelays();
}
