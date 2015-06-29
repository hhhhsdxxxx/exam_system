#include "logindlg.h"
#include "ui_logindlg.h"
#include "user.h"
#include <iostream>
#include <QtWidgets/QApplication.h>
#include <QtWidgets/QMessageBox.h>

using namespace std;

string login_id;

loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
    {
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    ui->pwdlineEdit_2->setEchoMode(QLineEdit::Password);
    }
loginDlg::~loginDlg()
{
    delete ui;
}

int loginDlg::setk(){
    return k;
}

void loginDlg::on_exitBtn_clicked()
{
    QApplication *a;
    a -> quit();
}

void loginDlg::on_loginBtn_clicked()
{
    user login((ui->usrLineEdit->text()).toStdString(), (ui->pwdLineEdit->text()).toStdString());
    if(login.login() == 2){
        login_id = (ui->usrLineEdit->text()).toStdString();
        accept();
        k = 1;
    }
    else{
    QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);
    }
}


void loginDlg::on_student_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(0);
}

void loginDlg::on_teacher_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(1);
}

void loginDlg::on_loginBtn2_clicked()
{
    user login((ui->usrLineEdit2->text()).toStdString(), (ui->pwdlineEdit_2 ->text()).toStdString());
    //std::cout << (ui->usrLineEdit->text()).toStdString() << std::endl;
    if(login.login() == 1){
        login_id = (ui->usrLineEdit2->text()).toStdString();
        accept();//两种接受
        k = 2;
    }
    else{
    QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);
    }
}
