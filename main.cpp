#include <QtWidgets/QApplication>
#include <iostream>
#include "mainwidget.h"
#include "mainwidget2.h"
#include "logindlg.h"
#include "management.h"
#include "setpaper.h"
#include "user.h"

MainWidget *w = NULL;
mainwidget2 *m = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        w = new MainWidget;
        m = new mainwidget2;
        user::load();
        loginDlg login;
        if(login.exec()==QDialog::Accepted)
        {
            if(login.setk()==1)
                w->show();
            if(login.setk()==2)
                m->show();
            return a.exec();
        }
       return 0;
}
