#include "mainwidget2.h"
#include "ui_mainwidget2.h"
#include "logindlg.h"
#include "management.h"
#include "setpaper.h"
#include "user.h"
#include "score.h"
#include <string>
#include <iostream>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTableView>
using namespace std;

management *manager = NULL;
setpaper *paper = NULL;

extern string login_id;
//QStandardItemModel *model_m = NULL;
mainwidget2::mainwidget2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwidget2)
{
    ui->setupUi(this);
    ui->oldpwd->setEchoMode(QLineEdit::Password);
    ui->newpwd->setEchoMode(QLineEdit::Password);
    ui->confirmpwd->setEchoMode(QLineEdit::Password);
    model_m = NULL;
}

mainwidget2::~mainwidget2()
{
    delete ui;
}

void mainwidget2::on_pushButton_clicked()
{
    user::write_back();
    QApplication::quit();
}

void mainwidget2::on_exampaper_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(0);
}

void mainwidget2::on_historygrade_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(1);

}

void mainwidget2::on_quesmanage_clicked()
{
    manager = new management;
    manager->show();
    this->hide();
}

void mainwidget2::on_pwdchange_clicked()
{
    paper = new setpaper;
    paper -> show();
    this -> hide();
}

void mainwidget2::on_confirm_clicked()
{
    if(ui->confirmpwd->text() == ui->newpwd->text()){
        if(user::change(login_id, (ui->oldpwd->text()).toStdString(), (ui->newpwd->text()).toStdString()))
            QMessageBox::about(this, "succeed","Password has been changed");
        else
            QMessageBox::about(this, "failed","Wrong old password");
    }
    else
        QMessageBox::about(this, "again","Wrong confirmed password!");
}

void mainwidget2::on_search_clicked()
{
    string id = (ui->studentid->text()).toStdString();
    if(id == ""){
        QMessageBox::about(this, "info", "Please input student id");
        return;
    }
    score my(id);
    list<pair<int, int>> *re = my.get();
    if(!re){
        QMessageBox::about(this, "info", "The student doesn't exist \nor he/she never take a exam.");
        return;
    }
    if(!model_m){
        model_m = new QStandardItemModel;
        model_m->setColumnCount(2);
        model_m->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("exam_id"));
        model_m->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("score"));
    }
    else
        model_m->removeRows(0, model_m->rowCount());
    int i = -1;
    ui->tableView->setModel(model_m);
    ui->tableView->setColumnWidth(0,140);
    ui->tableView->setColumnWidth(1,130);
    for(auto it : *re){
        model_m->setItem(++i, 0, new QStandardItem(QString::number(it.first)));
        model_m->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        model_m->setItem(i, 1, new QStandardItem(QString::number(it.second)));
        model_m->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }
    delete re;
}
