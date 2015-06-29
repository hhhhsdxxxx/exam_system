#include "mainwidget2.h"
#include "setpaper.h"
#include "ui_setpaper.h"
#include "exam_paper.h"
#include "problem_db.h"
#include "problem_file.h"
#include "problem.h"
#include <iostream>
#include <QMessageBox>
#include <QStandardItemModel>
#include <string>

using namespace std;


extern mainwidget2 *m;

setpaper::setpaper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setpaper),
    ans(0),
    type(0),
    num(0),
    pid(0)
{
    ui->setupUi(this);
    mydb = new problem_db;
    mydb->readin();
    model = new QStandardItemModel;
    model->setColumnCount(1);
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("problem_id"));
    //model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("db_name"));
    ui->list->setModel(model);
    ui->list->setColumnWidth(0,240);
    //ui->list->setColumnWidth(1,120);
}

setpaper::~setpaper()
{
    delete ui;
}

void setpaper::on_back_clicked()
{
    m->show();
    this -> destroy();
    exam_paper::give_up();
}

void setpaper::on_create_clicked()
{
    string filename = (ui->paperid->text()).toStdString();
    //QMessageBox::about(this, "debug", QString::fromStdString(filename));
    if(exam_paper::write_to_file(filename))
        QMessageBox::about(this, "Info", "Succeed!");
    else
        QMessageBox::about(this, "Error", "The paper exists!");
}

void setpaper::on_search_clicked()
{
    int id = (ui->quesid->text()).toInt();
    int iid = id/100*100;
    string filename = mydb->find(iid);
    if(filename == ""){
        //QMessageBox::about(this, "Error", "No such problem!");
        return;
    }
    else {
        problem_file file(filename);
        file.read_in();
        problem *ptr = file.get(id);
        if(!ptr){
            //QMessageBox::about(this, "Error", "No such problem!");
            return;
        }
        //file.remove(id);
        //file.write_back();
        //ui->comments->setText("");
        ui->quesinf->setText(QString::fromStdString(ptr->show_comment()));
        ans = ptr->show_answer();
        type = ptr->Type();
        pid = id;
        //QMessageBox::about(this, "Info", "Succeed!");
    }
}

void setpaper::on_pushButton_clicked()
{
    problem *ptr;
    if(type == 1)
        ptr = new judgement(ans);
    else if(type == 2)
        ptr = new selection(ans);
    ptr->set_problem((ui->quesinf->toPlainText()).toStdString());
    exam_paper::add(ptr);
    model->setItem(num, 0, new QStandardItem(QString::number(pid)));
    model->item(num, 0)->setTextAlignment(Qt::AlignCenter);
    num++;
}

void setpaper::on_delete_2_clicked()
{
    int indx = (ui->list->currentIndex()).row();
    exam_paper::removes(indx);
    model->removeRow(indx);
}
