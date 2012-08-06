#ifndef WINDOWIQ_H
#define WINDOWIQ_H

#include <QMainWindow>
#include <QTimer>
#include <QMap>
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
    void onTimerTimeout();
    void on_btnSend_clicked();
    void on_btnClear_clicked();
    void on_txtAttr1_returnPressed();
    void on_txtAttr2_returnPressed();
    void on_btnStart_clicked();


private:
    Ui::WindowIq *ui;
    xmppClient* client;
    bool _isStarted;
    QTimer _timer;
    QMap<QString, QString> _attrs;

};

#endif // WINDOWIQ_H
