#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main (void) {
    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        driver = get_driver_instance ();
        con = driver->connect ("tcp://127.0.0.1:3306", "root", "root");
        con->setSchema ("port");

        stmt = con->createStatement ();
        res = stmt->executeQuery ("SELECT * FROM port.port;");
        while (res->next ()) {
            cout << res->getString (1) << " \t" << res->getString (2) << "\t" << res->getString (3) << "\t" << res->getString (4) << endl;
        }
        delete res;
        delete stmt;
        delete con;

    } catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what () << " \t" << e.getErrorCode () << " \t" << e.getSQLState () << endl;
    }

    return EXIT_SUCCESS;
}