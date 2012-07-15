#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isStarted=false;
    state = -1;
    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));

    login = new DialogLogin(this);
    connect(login, SIGNAL(Login(QString,QString)), this, SLOT(onLogin(QString,QString)));
    login->setWindowTitle("Auth");
    login->setModal(true);
    login->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLogin(QString jid, QString pass)
{
    client = new xmppClient(this);
    connect(client, SIGNAL(messageReceived(QString,QString)), this, SLOT(onMessageReceived(QString,QString)));
    client->connectToServer(jid, pass);
}

void MainWindow::onMessageReceived(QString from, QString msg)
{
    ui->txtChat->append(from + " : ");
    ui->txtChat->append("<b><div style=\"color:#990099\" ><pre>" + msg + "</pre></div></b>");
}

void MainWindow::on_btnSend_clicked()
{
    sendMessage(ui->txtTarget->text(), ui->txtInput->text());
    ui->txtInput->clear();
}

void MainWindow::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}

void MainWindow::on_btnStart_clicked()
{
    if(isStarted)
    {
        timer.stop();
        state=-1;
        isStarted = false;
        ui->btnStart->setText("Start");
        ui->btnClear->setEnabled(true);
        ui->txtTarget->setEnabled(true);
    }
    else
    {
        if(ui->lstCMD->count()<1) return;
        if(ui->txtTarget->text().length()<3) return;
        state=0;
        timer.start(ui->spinDelay->value());
        isStarted = true;
        ui->btnStart->setText("Stop");
        ui->btnClear->setEnabled(false);
        ui->txtTarget->setEnabled(false);
    }
}

void MainWindow::on_btnClear_clicked()
{
    ui->lstCMD->clear();
}

void MainWindow::on_txtAddCMD_returnPressed()
{
    if(isStarted) return;
    ui->lstCMD->addItem(ui->txtAddCMD->text());
    ui->txtAddCMD->clear();
}

void MainWindow::onTimerTimeout()
{
    qDebug() << "State: " << state;
    if(state<0) return;
    QString cmd = ui->lstCMD->item(state)->text();
    sendMessage(ui->txtTarget->text(), cmd);
    if( ++state >= ui->lstCMD->count() )
        state=0;
}

void MainWindow::sendMessage(QString to, QString msg)
{
    client->sendMessage(to, msg);
    ui->txtChat->append("Me : " + to + ": <b>" + msg + "</b>");
}
