#ifndef WINDOWPEACE_H
#define WINDOWPEACE_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMap>
#include <QClipboard>
#include "dialoglogin.h"
#include "xmppclient.h"
#include "peacedelay.h"

namespace Ui {
    class WindowPeace;
}

class WindowPeace : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowPeace(xmppClient* Client, QWidget *parent = 0);
    ~WindowPeace();

private slots:
    void onTimerTimeout();
    void iqReceived(const QXmppIq&);
    void on_btnSend_clicked();
    void on_txtAttr1_returnPressed();
    void on_txtAttr2_returnPressed();
    void on_btnClear_clicked();
    void on_btnAddAttr_clicked();
    void on_btnAddChild_clicked();
    void on_btnStart_clicked();

    void on_btnCopy_clicked();

    void on_btnClearRes_clicked();

private:
    Ui::WindowPeace *ui;
    xmppClient* client;
    QList<PeaceDelay*>* _delays;
    bool _isStarted;
    QTimer _timer;
    QXmppElementList el;
    QXmppElement* el1;
    int _avg_t;
    int _avg_n;
    void updateXML();
    void updateDelays();

};

#endif // WINDOWPEACE_H
