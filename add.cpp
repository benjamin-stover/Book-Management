#include "add.h"

// Gathers the information entered in the
// boxes on the "Add" tab
// i.e. title, lastName, firstName, isbn, numCopies
void add_book(Ui::MainWindow *ui, QSqlQuery *query_add, QSqlQuery *query_history, QSqlDatabase db)
{
    Book book;
    QString q_title = ui->title_box->text();
    book.set_title(q_title.toStdString());

    QString q_firstName = ui->firstName_box->text();
    book.set_firstName(q_firstName.toStdString());

    QString q_lastName = ui->lastName_box->text();
    book.set_lastName(q_lastName.toStdString());

    QString q_isbn = ui->isbn_box->text();
    book.set_isbn(q_isbn.toStdString());
    book.check_valid();
    QString output_book = QString::fromStdString(book.output());
    ui->valid_label->setText(output_book);

    QString q_numCopies = ui->numCopies_box->text();
    book.set_numCopies(q_numCopies.toInt());

    if (book.valid && isbn_check(ui, book, db))
    {
        send_book(ui, book, query_add, query_history, db);
    }
}

// Sends the information entered into "Book book" to the "inventory" table
// Updates the "history" table by calling update_history()
void send_book(Ui::MainWindow *ui, Book book, QSqlQuery *query_add, QSqlQuery *query_history, QSqlDatabase db)
{
    if (db.isOpen())
    {
        query_add->prepare("INSERT INTO inventory (isbn, title, first_name, last_name, copies)"
                      "VALUES (:isbn, :title, :first_name, :last_name, :copies)");
        query_add->bindValue(":isbn", QString::fromStdString(book.get_isbn()));
        query_add->bindValue(":title", QString::fromStdString(book.get_title()));
        query_add->bindValue(":first_name", QString::fromStdString(book.get_firstName()));
        query_add->bindValue(":last_name", QString::fromStdString(book.get_lastName()));
        query_add->bindValue(":copies", book.get_numCopies());

        if (query_add->exec())
        {
            query_add->clear();
            qDebug() << "Saved: " << QString::fromStdString(book.get_title());
            ui->valid_label->setText(QString::fromStdString("SAVED: '"+book.get_title())+"' by "
                                     +QString::fromStdString(book.get_firstName())+" "
                                     +QString::fromStdString(book.get_lastName()));
        }
        update_history(book, "Add", query_history, db);
    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
        book.valid = false;
    }
    book.valid = false; //resets book.valid for next book
}


// Checks to see if the isbn of the book entered into the "Add" tab exists.
// If the book exists, returns false so that send_book() is NOT called.
// If the book does not exists, returns true so that send_book() IS called.
bool isbn_check(Ui::MainWindow *ui, Book book, QSqlDatabase db)
{
    QSqlQuery *query_isbn;
    query_isbn = new QSqlQuery(db);

    query_isbn->prepare("SELECT isbn FROM inventory WHERE isbn = :isbn");
    query_isbn->bindValue(":isbn", QString::fromStdString(book.get_isbn()));


    if (query_isbn->exec())
    {
        if (query_isbn->first())
        {
            ui->valid_label->setText("A book with that ISBN already exists...");
            qDebug() << "isbn_check(): ISBN already exists...";
            delete query_isbn;
            return false;
        }
        else
        {
            qDebug() << "isbn_check(): ISBN does not already exists...";
            delete query_isbn;
            return true;
        }
    }
    else
    {
        qDebug() << "ERROR: " << db.lastError().text();
        return false;
    }
}
