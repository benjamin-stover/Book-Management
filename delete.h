#ifndef DELETE_H
#define DELETE_H

#include "mainwindow.h"

// #######################################################################
// Descriptions of the following functions are available in delete.cpp
// #######################################################################
QString delete_search(Ui::MainWindow *ui, QSqlQuery *query_delete, QSqlDatabase db);
void delete_current(Ui::MainWindow *ui, QSqlQuery *query_delete, QSqlQuery *query_history, QSqlDatabase db, QString current);
Book get_book(QString current, QSqlDatabase db);


#endif // DELETE_H
