#include "edit.h"

// Searches the "inventory" table via the isbn column
// Uses the isbn enetered into edit_search
// If ISBN is found, returns the isbn to QString current
// If ISBN is not found, returns "0" to QString current
QString edit_search(Ui::MainWindow *ui, QSqlQuery *query_edit, QSqlDatabase db)
{
    QString searchTerm = ui->edit_search->text();

    if(db.isOpen())
    {
        qDebug() << "Connection successful in edit_search()";

        // Creates SQL query from the search box
        QString searchQry = "SELECT title, first_name, last_name, copies FROM inventory WHERE isbn = :isbn";
        query_edit->prepare(searchQry);
        query_edit->bindValue(":isbn", searchTerm);

        if(query_edit->exec())
        {
            if(query_edit->first())
            {
                ui->edit_title->setText(query_edit->value(0).toString()); // title
                ui->edit_firstName->setText(query_edit->value(1).toString()); // first name
                ui->edit_lastName->setText(query_edit->value(2).toString()); // last name
                ui->edit_copies->setText(query_edit->value(3).toString()); // copies

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

// Grabs the information stored in edit_title, edit_firstName, edit_lastName, edit_copies
// and replaces the information with the ISBN stored in "current" with the information
// stored in those variables in the "inventory" table.
// Updates the "history" table via update_history()
void edit_save(Ui::MainWindow *ui, QSqlQuery *query_edit, QSqlQuery *query_history, QSqlDatabase db, QString current)
{
    if (db.isOpen())
    {
        qDebug() << "Connection successful in edit_save()";

        QString title = ui->edit_title->text();
        QString first_name = ui->edit_firstName->text();
        QString last_name = ui->edit_lastName->text();
        QString copies = ui->edit_copies->text();

        Book book;
        book.set_title(title.toStdString());
        book.set_firstName(first_name.toStdString());
        book.set_lastName(last_name.toStdString());
        book.set_numCopies(copies.toInt());
        book.set_isbn(current.toStdString());

        QString searchQry = "UPDATE inventory SET title = :title, first_name = :first_name, last_name = :last_name, copies = :copies WHERE isbn = :isbn";
        query_edit->prepare(searchQry);
        query_edit->bindValue(":title", title);
        query_edit->bindValue(":first_name", first_name);
        query_edit->bindValue(":last_name", last_name);
        query_edit->bindValue(":copies", copies);
        query_edit->bindValue(":isbn", current);

        if (query_edit->exec())
        {
            ui->edit_title->setText("");
            ui->edit_firstName->setText("");
            ui->edit_lastName->setText("");
            ui->edit_copies->setText("");

            ui->edit_changes_saved->setText(QString::fromStdString("Saved changes to '"+book.get_title())+"' by "
                                            +QString::fromStdString(book.get_firstName())+" "
                                            +QString::fromStdString(book.get_lastName()));

            update_history(book, "Edit", query_history, db);
        }
        else
        {
            qDebug() << "ERROR: Could not execute query_edit in edit_save()";
        }
    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
    }
}

// Sets the line edit boxes in the "Edit" tab to read only
void init_edit_widgets(Ui::MainWindow *ui)
{
    ui->edit_title->setReadOnly(true);
    ui->edit_firstName->setReadOnly(true);
    ui->edit_lastName->setReadOnly(true);
    ui->edit_copies->setReadOnly(true);
}

