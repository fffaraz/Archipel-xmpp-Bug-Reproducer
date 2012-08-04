#ifndef WINDOWIQ_H
#define WINDOWIQ_H

#include <QMainWindow>
#include <QTimer>
#include "dialoglogin.h"
#include "xmppclient.h"

namespace Ui {
    class WindowIq;
}

class WindowIq : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowIq(xmppClient* Client, QWidget *parent = 0);
    ~WindowIq();

private slots:
    void on_btnSend_clicked();

private:
    Ui::WindowIq *ui;
    xmppClient* client;

};

#endif // WINDOWIQ_H
