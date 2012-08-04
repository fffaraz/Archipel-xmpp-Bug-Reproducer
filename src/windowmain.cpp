#include "windowmain.h"
#include "ui_windowmain.h"

WindowMain::WindowMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowMain)
{
    ui->setupUi(this);

    login = new DialogLogin(this);
    connect(login, SIGNAL(Login(QString,QString)), this, SLOT(onLogin(QString,QString)));
    login->setWindowTitle("Auth");
    login->setModal(true);
    login->show();
}

WindowMain::~WindowMain()
{
    delete ui;
}

void WindowMain::onLogin(QString jid, QString pass)
{
    client = new xmppClient(this);
    connect(client, SIGNAL(messageReceived(QString,QString)), this, SLOT(onMessageReceived(QString,QString)));
    connect(client, SIGNAL(iqReceived(QString)), this, SLOT(onIqReceived(QString)));
    client->connectToServer(jid, pass);
}

void WindowMain::on_actionManual_Test_triggered()
{
    MainWindow *manualtest = new MainWindow(client, this);
    manualtest->show();
}

void WindowMain::onMessageReceived(QString from, QString msg)
{
    if(from == "Me")
    {
        ui->txtChat->append("Me:    " + msg);
    }
    else
    {
        ui->txtChat->append(from + " : ");
        ui->txtChat->append("<b><div style=\"color:#990099\" ><pre>" + msg + "</pre></div></b>");
    }
}

void WindowMain::onIqReceived(QString msg)
{
    ui->txtChat->append(" IQ :");
    //ui->txtChat->append("<b><div style=\"color:#990000\" ><pre>" + msg + "</pre></div></b>");
    ui->txtChat->append(msg);
}

void WindowMain::on_btnSend_clicked()
{
    sendMessage(ui->txtTarget->text(), ui->txtInput->text());
    ui->txtInput->clear();
}

void WindowMain::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}

void WindowMain::sendMessage(QString to, QString msg)
{
    client->sendMessage(to, msg);
    ui->txtChat->append("Me:    " + to + ": <b>" + msg + "</b>");
}

void WindowMain::on_actionSend_IQ_triggered()
{
    WindowIq* iq = new WindowIq(client, this);
    iq->show();
}
