#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isStarted=false;
    isOneTime=false;
    loopMode=1;
    state = -1;
    vmState = -1;

    connect(&cmdTimer, SIGNAL(timeout()), this, SLOT(onCMDTimerTimeout()));
    connect(&loopTimer, SIGNAL(timeout()), this, SLOT(onLoopTimerTimeout()));
    loopTimer.setSingleShot(true);

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
        cmdTimer.stop();
        state=-1;
        vmState=-1;
        isStarted = false;
        ui->btnStart->setText("Start");
        ui->btnClear->setEnabled(true);
        ui->btnClearVM->setEnabled(true);
        ui->radio1->setEnabled(true);
        ui->radio2->setEnabled(true);
        ui->chkOneTime->setEnabled(true);
    }
    else
    {
        if(ui->lstCMD->count()<1) return;
        if(ui->lstVM->count() <1) return;
        state=0;
        vmState=0;
        cmdTimer.start(ui->spinDelay->value());
        isStarted = true;
        ui->btnStart->setText("Stop");
        ui->btnClear->setEnabled(false);
        ui->btnClearVM->setEnabled(false);
        ui->radio1->setEnabled(false);
        ui->radio2->setEnabled(false);
        ui->chkOneTime->setEnabled(false);
    }
}

void MainWindow::on_btnClear_clicked()
{
    ui->lstCMD->clear();
}

void MainWindow::on_btnClearVM_clicked()
{
    ui->lstVM->clear();
}

void MainWindow::on_txtAddCMD_returnPressed()
{
    if(isStarted) return;
    ui->lstCMD->addItem(ui->txtAddCMD->text());
    ui->txtAddCMD->clear();
}


void MainWindow::on_txtAddVM_returnPressed()
{
    if(isStarted) return;
    ui->lstVM->addItem(ui->txtAddVM->text());
    ui->txtAddVM->clear();
}


void MainWindow::onCMDTimerTimeout()
{
    qDebug() << "State: " << state;
    qDebug() << "vmState: " << vmState;
    if(state<0) return;
    if(vmState<0) return;
    QString cmd = ui->lstCMD->item(state)->text();
    QString target = ui->lstVM->item(vmState)->text();

    switch (loopMode)
    {
    case 1:     // To One
        sendMessage(target, cmd);
        state++;
        break;
    case 2:     // To Many
        sendMessage(target, cmd);
        vmState++;
        break;
    default:
        return;
    }
    if(state >= ui->lstCMD->count()) // reaching end of command queue
    {
        state=0;
        if(isOneTime)
            on_btnStart_clicked();
        else
        {
            cmdTimer.stop();
            loopTimer.start(ui->spinDelayLoop->value());
        }
    }

}

void MainWindow::onLoopTimerTimeout()
{
    if(loopMode == 2)
        state++;
    cmdTimer.start();
}

void MainWindow::sendMessage(QString to, QString msg)
{
    client->sendMessage(to, msg);
    ui->txtChat->append("Me : " + to + ": <b>" + msg + "</b>");
}

void MainWindow::on_chkOneTime_toggled(bool checked)
{
    isOneTime = checked;
}

void MainWindow::on_radio1_toggled(bool checked)
{
    loopMode = checked? 1 : 2;
}



