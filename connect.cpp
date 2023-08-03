#include "connect.h"

// Sets up PostgreSQL database connection
void connect_db()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "connect");

    db.setHostName("localhost");      // Host Name
    db.setDatabaseName("");           // Database Name
    db.setUserName("");               // PSQL Username
    db.setPassword("");               // PSQL User Password
}
