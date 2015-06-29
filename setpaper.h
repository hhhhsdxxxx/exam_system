#ifndef SETPAPER_H
#define SETPAPER_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include "problem_db.h"

namespace Ui {
    class setpaper;
}

class setpaper : public QDialog
{
    Q_OBJECT
    problem_db *mydb;
    QStandardItemModel *model;
    int ans, type, num, pid;
public:
    explicit setpaper(QWidget *parent = 0);
    ~setpaper();

private slots:
    void on_back_clicked();

    void on_create_clicked();

    void on_search_clicked();

    void on_pushButton_clicked();

    void on_delete_2_clicked();

private:
    Ui::setpaper *ui;
};

#endif // SETPAPER_H
