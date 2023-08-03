#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlTableModel>

#include "./ui_mainwindow.h"
#include "book.h"
#include "add.h"
#include "connect.h"
#include "search.h"
#include "edit.h"
#include "delete.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
// #######################################################################
// Descriptions of the following functions are available in mainwindow.cpp
// #######################################################################

    void on_add_save_clicked();

    void on_search_button_clicked();

    void on_delete_search_button_clicked();

    void on_delete_button_clicked();

    void on_edit_search_button_clicked();

    void on_edit_save_button_clicked();

    void on_edit_check_firstName_stateChanged(int arg1);

    void on_edit_check_title_stateChanged(int arg1);

    void on_edit_check_lastName_stateChanged(int arg1);

    void on_edit_check_copies_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

    QSqlQuery *query_search;
    QSqlQueryModel *model_search;

    QSqlQuery *query_history;
    QSqlQueryModel *model_history;

    QSqlQuery *query_add;

    QSqlQuery *query_delete;

    QSqlQuery *query_edit;

    QString current; // Used in delete
};
#endif // MAINWINDOW_H
