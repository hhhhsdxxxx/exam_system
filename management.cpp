#include "mainwidget2.h"
#include "management.h"
#include "ui_management.h"
#include "problem_db.h"
#include "problem_file.h"
#include <string>
#include <QMessageBox>
#include <fstream>
#include <iostream>

using namespace std;

extern mainwidget2 *m;

management::management(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::management)
{
    ui->setupUi(this);
    mydb = new problem_db;
    mydb->readin();
    model = new QStandardItemModel;
    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("start_id"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("db_name"));
    ui->queslist->setModel(model);
    ui->queslist->setColumnWidth(0,120);
    ui->queslist->setColumnWidth(1,120);
    int i = -1;
    for(auto it : *(mydb->getdb())){
        model->setItem(++i, 0, new QStandardItem(QString::number(it.first)));
        model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(it.second)));
        model->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }
}

management::~management()
{
    delete ui;
}

void management::on_quit_clicked()
{
    m->show();
    this -> destroy();
}

void management::on_handin_clicked()
{
    int ans = -1, type;
    string re = (ui->answerline->text()).toStdString();
    if(re == ""){
        QMessageBox::about(this, "error", "Please input answer first!");
        return;
    }
    else if(re.length()>1){
        QMessageBox::about(this, "error", "Illegalanswer!");
        return;
    }
    else {
        switch(re.at(0)){
        case 't':
        case 'T': ans = 1; type = 1; break;
        case 'f':
        case 'F': ans = 0; type = 1; break;
        case 'a':
        case 'A': ans = 0; type = 2; break;
        case 'b':
        case 'B': ans = 1; type = 2; break;
        case 'c':
        case 'C': ans = 2; type = 2; break;
        case 'd':
        case 'D': ans = 3; type = 2; break;
        default:
            QMessageBox::about(this, "error", "Illegalanswer!");
            break;
        }
    }
    string comment = (ui->comments->toPlainText()).toStdString();
    int i = ui->queslist->currentIndex().row();
    string filename = mydb->find(i*100);
    //QMessageBox::about(this, QString::fromStdString(filename), QString::number(i*100));
    if(filename == "")
        return;
    problem_file pro_file(filename);
    pro_file.read_in();
    problem *ptr;
    if(type == 1)
        ptr = new judgement(ans);
    else
        ptr = new selection(ans);
    ptr->set_problem(comment+"\n");
    if(!(pro_file.add(-1, ptr)))
            QMessageBox::about(this, "error", "Fail to add problem!");
    pro_file.write_back();
    delete ptr;
    //QMessageBox::about(this, "debug", QString::number(i));
}

void management::on_filein_clicked()
{
    string filename = (ui->nameline->text()).toStdString();
    ifstream fin(filename, ios::in);
    int sid;
    fin >> sid >> sid;
    if(sid%100 != 0){
        QMessageBox::about(this, "Error", "ID must start with **00");
        return;
    }
    if(mydb->add(sid, filename)){
        QMessageBox::about(this, "info", "Succeed!");
        ui->nameline->setText("");
        model->removeRows(0, model->rowCount());
        int i = -1;
        for(auto it : *(mydb->getdb())){
            model->setItem(++i, 0, new QStandardItem(QString::number(it.first)));
            model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, 1, new QStandardItem(QString::fromStdString(it.second)));
            model->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
    }
    else {
        QMessageBox::about(this, "Error", "Add file error!");
    }
}

void management::on_deleteBtn_clicked()
{
    int id = (ui->quesid->text()).toInt();
    int iid = id/100*100;
    cout << iid << endl;
    string filename = mydb->find(iid);
    if(filename == ""){
        QMessageBox::about(this, "Error", "No such problem!");
        return;
    }
    else {
        problem_file file(filename);
        file.read_in();
        cout << id << " " << filename << endl;
        if(!file.get(id)){
            QMessageBox::about(this, "Error", "No such problem!");
            return;
        }
        file.remove(id);
        file.write_back();
        QMessageBox::about(this, "Info", "Succeed!");
    }
}

void management::on_quesid_editingFinished()
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
        if(!file.get(id)){
            //QMessageBox::about(this, "Error", "No such problem!");
            return;
        }
        //file.remove(id);
        //file.write_back();
        //ui->comments->setText("");
        ui->comments->setText(QString::fromStdString(file.get(id)->show_comment()));
        //QMessageBox::about(this, "Info", "Succeed!");
    }
}
