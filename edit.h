#ifndef EDIT_H
#define EDIT_H

#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QString>
#include "mainwindow.h"

// #######################################################################
// Descriptions of the following functions are available in edit.cpp
// #######################################################################
QString edit_search(Ui::MainWindow *ui, QSqlQuery *query_edit, QSqlDatabase db);
void edit_save(Ui::MainWindow *ui, QSqlQuery *query_edit, QSqlQuery *query_history, QSqlDatabase db, QString current);
void init_edit_widgets(Ui::MainWindow *ui);

#endif // EDIT_H
