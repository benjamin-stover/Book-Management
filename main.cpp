// Author: Benjamin Stover
// Phone Number: 865-660-9948
// Email: benjaminstover2023@gmail.com
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    connect_db(); //sets up connection to postgresql database

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int num = a.exec(); // exec() returns 0 when main window is exited

    QSqlDatabase::removeDatabase("connect");


    return num;
}
