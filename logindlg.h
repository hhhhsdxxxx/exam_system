#ifndef LOGINDLG_H
#define LOGINDLG_H

//#include <QDialog>
//#include <QWidget>
#include <QtWidgets/QDialog>    //for  QT 5.*
#include <QtWidgets/QWidget>

namespace Ui {
    class loginDlg;
}

class loginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit loginDlg(QWidget *parent = 0);
    ~loginDlg();
    int setk();
private slots:
    void on_exitBtn_clicked();

    void on_loginBtn_clicked();

    void on_loginBtn2_clicked();

    void on_student_clicked();

    void on_teacher_clicked();

private:
    Ui::loginDlg *ui;
    int k;
};

#endif // LOGINDLG_H
