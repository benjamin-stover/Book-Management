#include "mainwindow.h"

// Initializes the database connection
// Initializes QSqlQueryModel model_search and QSqlQueryModel model_history
// Calls: init_display_search(), init_edit_widgets(), display_history
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::database("connect");

    query_search = new QSqlQuery(db);
    query_history = new QSqlQuery(db);

    model_search = new QSqlQueryModel(this);
    model_history = new QSqlQueryModel(this);

    current = "0"; // Recieves return value of edit_search() and delete_search()

    init_display_search(ui, model_search, query_search, db);
    init_edit_widgets(ui);
    display_history(ui, model_history, query_history, db);
}

// Deletes remaining pointers and closes database connection
MainWindow::~MainWindow()
{
    delete ui;

    delete query_search;
    delete query_history;

    delete model_search;
    delete model_history;

    db.close();
}

// Called after the "Save" button is clicked in the "Add" tab.
// Saves the information to the "inventory" table
// Calls: add_book(), display_history()
// Files: add.cpp, history.cpp
void MainWindow::on_add_save_clicked()
{
    delete query_history;
    query_history = new QSqlQuery(db);
    delete model_history;
    model_history = new QSqlQueryModel;

    query_add = new QSqlQuery(db);

    add_book(ui, query_add, query_history, db);
    display_history(ui, model_history, query_history, db);

    delete query_add;
}

// Called after the "Search" button is clicked in the "Search" tab.
// Searches for book by isbn, last name, or title.
// Calls: search_func()
// Files: search.cpp
void MainWindow::on_search_button_clicked()
{
    delete query_search;
    query_search = new QSqlQuery(db);
    delete model_search;
    model_search = new QSqlQueryModel;

    search_func(ui, model_search, query_search, db);
}

// Called after the "Search" button is clicked in the "Edit" tab
// Searches the "ISBN" column in the "inventory" table
// Calls: edit_search()
// Files: edit.cpp
void MainWindow::on_edit_search_button_clicked()
{
    query_edit = new QSqlQuery(db);

    current = edit_search(ui, query_edit, db);

    delete query_edit;
}

// Called after the "Save" button is clicked in the "Edit" tab
// Saves the changes made to the checked boxes
// Updates the "History" tab
// Calls: edit_save(), display_history()
// Files: edit.cpp, history.cpp
void MainWindow::on_edit_save_button_clicked()
{
    delete query_history;
    query_history = new QSqlQuery(db);
    delete model_history;
    model_history = new QSqlQueryModel;

    query_edit = new QSqlQuery(db);

    if (current != "0")
    {
        edit_save(ui, query_edit, query_history, db, current);
    }
    display_history(ui, model_history, query_history, db);
    current = "0";

    delete query_edit;
}

// Called after the "Search" button is clicked in the "Delete" tab
// Searches the "ISBN" column in the "inventory" table
// Calls: delete_search()
// Files: delete.cpp
void MainWindow::on_delete_search_button_clicked()
{
    query_delete = new QSqlQuery(db);

    current = delete_search(ui, query_delete, db);

    delete query_delete;
}

// Called after the "Delete" button is clicked in the "Delete" tab
// Deletes the the book whose ISBN is stored in QString current
// Calls: delete_current(), display_history()
// Files: delete.cpp, history.cpp
void MainWindow::on_delete_button_clicked()
{
    delete query_history;
    query_history = new QSqlQuery(db);
    delete model_history;
    model_history = new QSqlQueryModel;

    query_delete = new QSqlQuery(db);

    if (current != "0")
    {
        delete_current(ui, query_delete, query_history, db, current);
    }
    display_history(ui, model_history, query_history, db);
    current = "0";

    delete query_delete;
}


// All "on_edit_check_####_stateChanged(int arg1)" functions
// control whether the line edit boxes in the "Edit" tab
// are read only.
void MainWindow::on_edit_check_title_stateChanged(int arg1)
{
    if (ui->edit_title->isReadOnly())
    {
        ui->edit_title->setReadOnly(false);
    }
    else
    {
        ui->edit_title->setReadOnly(true);
    }
}

void MainWindow::on_edit_check_firstName_stateChanged(int arg1)
{
    if (ui->edit_firstName->isReadOnly())
    {
        ui->edit_firstName->setReadOnly(false);
    }
    else
    {
        ui->edit_firstName->setReadOnly(true);
    }
}


void MainWindow::on_edit_check_lastName_stateChanged(int arg1)
{
    if (ui->edit_lastName->isReadOnly())
    {
        ui->edit_lastName->setReadOnly(false);
    }
    else
    {
        ui->edit_lastName->setReadOnly(true);
    }
}


void MainWindow::on_edit_check_copies_stateChanged(int arg1)
{
    if (ui->edit_copies->isReadOnly())
    {
        ui->edit_copies->setReadOnly(false);
    }
    else
    {
        ui->edit_copies->setReadOnly(true);
    }
}

