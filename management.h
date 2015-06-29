#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include "problem_db.h"
#include "problem_file.h"

namespace Ui {
    class management;
}

class management : public QDialog
{
    Q_OBJECT
    problem_db *mydb;
    //problem_file *pro_file;
    QStandardItemModel *model;
public:
    explicit management(QWidget *parent = 0);
    ~management();

private slots:

    void on_quit_clicked();

    void on_handin_clicked();

    void on_filein_clicked();

    void on_deleteBtn_clicked();

    void on_quesid_editingFinished();

private:
    Ui::management *ui;
};

#endif // MANAGEMENT_H
