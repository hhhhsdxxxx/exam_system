#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "logindlg.h"
#include "user.h"
#include "score.h"
#include "exam_paper.h"
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include <Qt>
#include <QButtonGroup>
#include <string>
#include <iostream>

using namespace std;

extern string login_id;

//exam_paper *paper = NULL;
//int index = 0;
//QButtonGroup *btn_choice = NULL;
//QStandardItemModel *model = NULL;
//int *ans;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->oldpwd->setEchoMode(QLineEdit::Password);
    ui->newpwd->setEchoMode(QLineEdit::Password);
    ui->confirmpwd->setEchoMode(QLineEdit::Password);

    paper = NULL;
    index = 0;
    btn_choice = NULL;
    model = NULL;
    ans = NULL;
    is_exam = false;
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_Quit_clicked()
{
    user::write_back();
    QApplication::quit();
}

void MainWidget::on_historgrade_clicked()
{
    if(is_exam){
        QMessageBox::about(this, "error!", "Please finish exam first!");
        return;
    }
    ui -> stackedWidget -> setCurrentIndex(3);
    score my(login_id);
    list<pair<int, int>> *re = my.get();
    if(!model){
        model = new QStandardItemModel;
        model->setColumnCount(2);
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("exam_id"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("score"));
    }
    else
        model->removeRows(0, model->rowCount());
    int i = -1;
    ui->history->setModel(model);
    ui->history->setColumnWidth(0,140);
    ui->history->setColumnWidth(1,130);
    for(auto it : *re){
        model->setItem(++i, 0, new QStandardItem(QString::number(it.first)));
        model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 1, new QStandardItem(QString::number(it.second)));
        model->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }
    delete re;
}

void MainWidget::on_onlineexam_clicked()
{
    if(is_exam){
        QMessageBox::about(this, "error!", "Please finish exam first!");
        return;
    }
    //QTextEdit *ptr = ui->question;
    //ptr->setText("fffffff uuuuuu cccc yyyyyy\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nyouuuuuuuu");
    ui -> stackedWidget -> setCurrentIndex(0);
}

void MainWidget::on_pwdchange_clicked()
{
    if(is_exam){
        QMessageBox::about(this, "error!", "Please finish exam first!");
        return;
    }
    ui -> stackedWidget -> setCurrentIndex(1);
}

void MainWidget::on_confirm_clicked()
{
    if(paper)
        delete paper;
    int eid = (ui->numpaperline->text()).toInt();
    score my(login_id);
    if(my.is_taken(eid)){
        QMessageBox::about(this, "info", "You have been finished this exam,\nyou can see you score in score part!");
        return;
    }
    paper = new exam_paper(eid);
    if(!paper->read_from_file())
        QMessageBox::about(this, "wrong", "No such exam!") ;
    else
        ui -> stackedWidget -> setCurrentIndex(2);
    if(!btn_choice){
        btn_choice = new QButtonGroup(this);
        btn_choice->addButton(ui->A, 0);
        btn_choice->addButton(ui->B, 1);
        btn_choice->addButton(ui->C, 2);
        btn_choice->addButton(ui->D, 3);
    }
    ans = new int[paper->numbers()];
    for(int i = 0; i < paper->numbers(); i++)
        ans[i] = -1;
    ui->question->setText(QString::fromStdString(paper->get(index)->show_comment()));
    is_exam = true;
}

void MainWidget::on_pushButton_clicked()  //change pwd
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

void MainWidget::on_pre_clicked()
{
    int anss = -1;
    switch(btn_choice->checkedId()){
    case 0: anss = 0; break;
    case 1: anss = 1; break;
    case 2: anss = 2; break;
    case 3: anss = 3; break;
    default: anss = -1; break;
    }
    //paper->givescore(index, ans);
    ans[index] = anss;
    index = (index==0)?0:index-1;
    ui->question->setText(QString::fromStdString(paper->get(index)->show_comment()));
    switch(ans[index]){
    case 0: ui->A->setChecked(true); break;
    case 1: ui->B->setChecked(true); break;
    case 2: ui->C->setChecked(true); break;
    case 3: ui->D->setChecked(true); break;
    default:
        ui->A->setChecked(false);
        ui->B->setChecked(false);
        ui->C->setChecked(false);
        ui->D->setChecked(false);
        break;
    }
    ui->lineEdit->setText(QString::number(index+1));
}

void MainWidget::on_next_clicked()
{
    int anss = -1;
    switch(btn_choice->checkedId()){
    case 0: anss = 0; break;
    case 1: anss = 1; break;
    case 2: anss = 2; break;
    case 3: anss = 3; break;
    default: anss = -1; break;
    }
    //paper->givescore(index, ans);
    ans[index] = anss;
    index = (index==paper->numbers()-1)?paper->numbers()-1:index+1;
    ui->question->setText(QString::fromStdString(paper->get(index)->show_comment()));
    switch(ans[index]){
    case 0: ui->A->setChecked(true); break;
    case 1: ui->B->setChecked(true); break;
    case 2: ui->C->setChecked(true); break;
    case 3: ui->D->setChecked(true); break;
    default:
        ui->A->setChecked(false);
        ui->B->setChecked(false);
        ui->C->setChecked(false);
        ui->D->setChecked(false);
        break;
    }
    ui->lineEdit->setText(QString::number(index+1));
}

void MainWidget::on_handon_clicked()
{
    int anss = -1;
    switch(btn_choice->checkedId()){
    case 0: anss = 0; break;
    case 1: anss = 1; break;
    case 2: anss = 2; break;
    case 3: anss = 3; break;
    default: anss = -1; break;
    }
    //paper->givescore(index, ans);
    ans[index] = anss;
    score my(login_id);
//    for(int i = 0; i < paper->numbers(); i++)
//        std::cout << ans[i] << std::endl;
    for(int i = 0; i < paper->numbers(); i++)
        paper->givescore(i, ans[i]);
    my.write(paper->getID() ,paper->result());
    if(paper)
        delete paper;
    paper = NULL;
    delete[] ans;
    ans = NULL;
    is_exam = false;
    ui -> stackedWidget -> setCurrentIndex(0);
}
