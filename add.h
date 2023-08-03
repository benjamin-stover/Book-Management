#ifndef ADD_H
#define ADD_H

#include "mainwindow.h"
#include "book.h"
#include "history.h"
#include <fstream>
#include <QtSql>
#include <QDebug>
#include <string>

// #######################################################################
// Descriptions of the following functions are available in add.cpp
// #######################################################################
void add_book(Ui::MainWindow *ui, QSqlQuery *query_add, QSqlQuery *query_history, QSqlDatabase db);
void send_book(Ui::MainWindow *ui, Book book, QSqlQuery *query_add, QSqlQuery *query_history, QSqlDatabase db);
bool isbn_check(Ui::MainWindow *ui, Book book, QSqlDatabase db);


#endif // ADD_H
