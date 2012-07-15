#include "dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::on_btnLogin_clicked()
{
    emit Login(ui->txtJID->text(), ui->txtPassword->text());
    this->close();
    this->deleteLater();
}
