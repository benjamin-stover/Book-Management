#include "history.h"

// Updates the "history" table.
void update_history(Book book, QString action, QSqlQuery *query_history, QSqlDatabase db)
{
    if (db.isOpen())
    {
        qDebug() << "Connection successful in update_history()";

        query_history->prepare("INSERT INTO history (title ,isbn, action, modification_time)"
                       "VALUES (:title, :isbn, :action, CURRENT_TIMESTAMP)");
        query_history->bindValue(":title", QString::fromStdString(book.get_title()));
        query_history->bindValue(":isbn", QString::fromStdString(book.get_isbn()));
        query_history->bindValue(":action", action);

        if (query_history->exec())
        {
            query_history->clear();
            qDebug() << "History updated.";
        }
    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
    }
}

// Displays the "history" table via QSqlQueryModel *model in the "History" tab
void display_history(Ui::MainWindow *ui, QSqlQueryModel *model, QSqlQuery *query_history, QSqlDatabase db)
{
    if(db.isOpen())
    {
        query_history->prepare("SELECT title AS \"Title\", isbn AS \"ISBN\", action AS \"Action\", modification_time AS \"Modification Time\" FROM history ORDER BY id DESC");

        // Executes the query, then displays the information
        // sent back from the database
        if(query_history->exec())
        {
            model->setQuery(std::move(*query_history));
            ui->history_table->setModel(model);
        }

    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
    }
}
