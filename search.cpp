#include "search.h"

// Allows the user to search the "inventory" database via Title, ISBN, and Author's last name
// Displays the "inventory" via QSqlQueryModel *model
void search_func(Ui::MainWindow *ui, QSqlQueryModel *model, QSqlQuery *query, QSqlDatabase db)
{

    QString searchTerm = ui->search_box->text();
    QString typeOfSearch = ui->search_type->currentText();


    if (typeOfSearch == "Title")
        typeOfSearch = "title";
    else if (typeOfSearch == "ISBN")
        typeOfSearch = "isbn";
    else
        typeOfSearch = "last_name";

    if(db.isOpen())
    {
        qDebug() << "Connection successful in search_func()";

        // Creates SQL query from the search box
        QString searchQry = "SELECT title AS \"Title\", first_name AS \"First Name\", last_name AS \"Last Name\", isbn AS \"ISBN\", copies AS \"Copies\" FROM inventory WHERE "
                            + typeOfSearch + " ILIKE :" + typeOfSearch;
        query->prepare(searchQry);
        query->bindValue(":"+typeOfSearch, searchTerm);

        // Executes the query, then displays the information
        // sent back from the database
        if(query->exec())
        {
            model->setQuery(std::move(*query));
            ui->search_table->setModel(model);
        }
    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
    }
}

// Displays the "inventory" via QSqlQuery *model when program is opened before any searches are permformed
void init_display_search(Ui::MainWindow *ui, QSqlQueryModel *model, QSqlQuery *query, QSqlDatabase db)
{
    ui->search_type->addItem("Title");
    ui->search_type->addItem("ISBN");
    ui->search_type->addItem("Last Name");

    if(db.isOpen())
    {
        query->prepare("SELECT title as \"Title\", first_name AS \"First Name\", last_name AS \"Last Name\", isbn AS \"ISBN\", copies AS \"Copies\" FROM inventory ORDER BY last_name ASC");

        // Executes the query, then displays the information
        // sent back from the database
        if(query->exec())
        {
            model->setQuery(std::move(*query));
            ui->search_table->setModel(model);
        }
    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
    }
}






















