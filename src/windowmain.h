#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QMainWindow>
#include <QTimer>
#include "dialoglogin.h"
#include "xmppclient.h"
#include "mainwindow.h"
#include "windowiq.h"

namespace Ui {
    class WindowMain;
}

class WindowMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowMain(QWidget *parent = 0);
    ~WindowMain();

private:
    Ui::WindowMain *ui;
    DialogLogin* login;
    xmppClient* client;
    void sendMessage(QString to, QString msg);

public slots:
    void onLogin(QString jid, QString pass);

private slots:
    void onMessageReceived(QString from, QString msg);
    void onIqReceived(QString msg);
    void on_actionManual_Test_triggered();
    void on_btnSend_clicked();
    void on_txtInput_returnPressed();
    void on_actionSend_IQ_triggered();
};

#endif // WINDOWMAIN_H
