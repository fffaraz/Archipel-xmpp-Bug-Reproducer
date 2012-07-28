#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>

namespace Ui {
    class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = 0);
    ~DialogLogin();

private slots:
    void on_btnLogin_clicked();

signals:
    void Login(QString jid, QString pass);

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
