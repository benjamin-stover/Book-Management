#ifndef SEARCH_H
#define SEARCH_H

#include <QtSql>
#include <QDebug>
#include <QSqlDatabase>
#include <QString>
#include "mainwindow.h"

// #######################################################################
// Descriptions of the following functions are available in search.cpp
// #######################################################################
void search_func(Ui::MainWindow *ui, QSqlQueryModel *model, QSqlQuery *query, QSqlDatabase db);
void init_display_search(Ui::MainWindow *ui, QSqlQueryModel *model, QSqlQuery *query, QSqlDatabase db);

#endif // SEARCH_H
