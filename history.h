#ifndef HISTORY_H
#define HISTORY_H

#include <QString>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include "book.h"
#include "mainwindow.h"

// #######################################################################
// Descriptions of the following functions are available in history.cpp
// #######################################################################
void update_history(Book book, QString action, QSqlQuery *query_history, QSqlDatabase db);
void display_history(Ui::MainWindow *ui, QSqlQueryModel *model, QSqlQuery *query_history, QSqlDatabase db);

#endif // HISTORY_H
