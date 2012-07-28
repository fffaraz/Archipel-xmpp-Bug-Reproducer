#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "dialoglogin.h"
#include "xmppclient.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DialogLogin* login;
    xmppClient* client;
    bool isStarted;

    // Command State
    int state;
    // VM State
    int vmState;
    // Loop Modes
    bool isOneTime;
    int loopMode;

    QTimer cmdTimer;
    QTimer loopTimer;
    void sendMessage(QString to, QString msg);

public slots:
    void onLogin(QString jid, QString pass);

private slots:
    void onMessageReceived(QString from, QString msg);
    void onCMDTimerTimeout();
    void onLoopTimerTimeout();
    void on_btnSend_clicked();
    void on_txtInput_returnPressed();
    void on_btnStart_clicked();
    void on_btnClear_clicked();
    void on_txtAddCMD_returnPressed();
    void on_btnClearVM_clicked();
    void on_txtAddVM_returnPressed();
    void on_chkOneTime_toggled(bool checked);
    void on_radio1_toggled(bool checked);
};

#endif // MAINWINDOW_H
