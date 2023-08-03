#include "delete.h"

// Searches the "inventory" table via the isbn column.
// Searches via the
// Returns "0" if ISBN is not found.
// Returns QString of the ISBN found if the entered ISBN exists.
QString delete_search(Ui::MainWindow *ui, QSqlQuery *query_delete, QSqlDatabase db)
{
    QString searchTerm = ui->delete_search_box->text();

    if(db.isOpen())
    {
        qDebug() << "Connection successful in delete_search()";

        // Creates SQL query from the search box
        QString searchQry = "SELECT title, first_name, last_name, copies FROM inventory WHERE isbn = :isbn";
        query_delete->prepare(searchQry);
        query_delete->bindValue(":isbn", searchTerm);

        if(query_delete->exec())
        {
            if(query_delete->first())
            {
                ui->delete_title_label->setText(query_delete->value(0).toString()); // title
                ui->delete_author_label->setText(query_delete->value(1).toString()+" "+query_delete->value(2).toString()); // author
                ui->delete_numCopies_label->setText(query_delete->value(3).toString()); // copies

                return searchTerm;
            }
            else
            {
                qDebug() << "ISBN does not exist in database...";
                return "0";
            }
        }
    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
        return "0";
    }
    return "0";
}

// Deletes the book from the "inventory" table whose ISBN is stored in QString current
// Updates the "history" table
void delete_current(Ui::MainWindow *ui, QSqlQuery *query_delete, QSqlQuery *query_history, QSqlDatabase db, QString current)
{
    if(db.isOpen())
    {
        Book book = get_book(current, db); // Grabs the title and the isbn of the deleted book for update_history()

        QString searchQry = "DELETE FROM inventory WHERE isbn = :isbn";
        query_delete->prepare(searchQry);
        query_delete->bindValue(":isbn", current);

        if(query_delete->exec())
        {
            ui->delete_title_label->setText("");
            ui->delete_author_label->setText("");
            ui->delete_numCopies_label->setText("");

            ui->delete_success->setText(QString::fromStdString("DELETED: '"+book.get_title())+"' by "
                                        +QString::fromStdString(book.get_firstName())+" "
                                        +QString::fromStdString(book.get_lastName()));

            update_history(book, "Delete", query_history, db);
        }
        else
        {
            qDebug() << "ERROR: Could not delete entry...";
        }
    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
    }
}

// Called in delete_current()
// Returns a Book instance
// Loads info of book whose ISBN is stored in current
// The Book instance returned by this function is used to update
// the "history" table through update_history()
Book get_book(QString current, QSqlDatabase db)
{
    Book book;
    QSqlQuery *query_book;
    query_book = new QSqlQuery(db);
    query_book->prepare("SELECT isbn, title, first_name, last_name FROM inventory WHERE isbn = :isbn");
    query_book->bindValue(":isbn", current);

    if (query_book->exec())
    {
        qDebug() << query_book->first();
        QString title = query_book->value(1).toString();
        QString first_name = query_book->value(2).toString();
        QString last_name = query_book->value(3).toString();

        qDebug() << title;
        book.set_title(title.toStdString());
        book.set_isbn(current.toStdString());
        book.set_firstName(first_name.toStdString());
        book.set_lastName(last_name.toStdString());
    }
    else
    {
        qDebug() << "ERROR: Could not execute query_book in get_book()";
    }

    delete query_book;

    return book;
}
