#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include <QButtonGroup>
#include "user.h"
#include "score.h"
#include "exam_paper.h"

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    exam_paper *paper;
    int index;
    QButtonGroup *btn_choice;
    QStandardItemModel *model;
    int *ans;
    bool is_exam;
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    //void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

    void on_Quit_clicked();

    void on_historgrade_clicked();

    void on_onlineexam_clicked();

    void on_pwdchange_clicked();

    void on_confirm_clicked();

    void on_pushButton_clicked();

    void on_pre_clicked();

    void on_next_clicked();

    void on_handon_clicked();

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
