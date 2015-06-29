#ifndef MAINWIDGET2_H
#define MAINWIDGET2_H

#include <QtWidgets/QDialog>
#include <QStandardItemModel>
#include "management.h"
#include "setpaper.h"

namespace Ui {
    class mainwidget2;
}

class mainwidget2 : public QDialog
{
    Q_OBJECT
//    management *manager;
//    setpaper *paper;
    QStandardItemModel *model_m;
public:
    explicit mainwidget2(QWidget *parent = 0);
    ~mainwidget2();

private slots:
    void on_pushButton_clicked();

    void on_exampaper_clicked();

    void on_historygrade_clicked();

    void on_quesmanage_clicked();

    void on_pwdchange_clicked();

    void on_confirm_clicked();

    void on_search_clicked();

private:
    Ui::mainwidget2 *ui;
};

#endif // MAINWIDGET2_H
