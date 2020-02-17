/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main(void)
{
    cout << endl;
    cout << "Let's have MySQL count from 10 to 1..." << endl;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;
        sql::PreparedStatement *pstmt;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("192.168.1.74", "gildong", "gildong");
        /* Connect to the MySQL test database */
        con->setSchema("els_test");

        // stmt = con->createStatement();
        // stmt->execute("DROP TABLE IF EXISTS test");
        // stmt->execute("CREATE TABLE test(id INT)");
        // delete stmt;

        /* '?' is the supported placeholder syntax */
        pstmt = con->prepareStatement("INSERT INTO GW(TNL_ID, GW_ID, GW_NM, UPDATE_DATE) VALUES (?,?,?,Now())");
        pstmt->setInt(1, 1);
        pstmt->setInt(2, 6);
        pstmt->setString(3, "TEST2");

        pstmt->executeUpdate();
        
        delete pstmt;

        /* Select in ascending order */
        pstmt = con->prepareStatement("SELECT * FROM GW");
        res = pstmt->executeQuery();

        /* Fetch in reverse = descending order! */
        res->afterLast();
        while (res->previous())
            cout << "\t... MySQL counts: " << res->getInt("GW_ID") << endl;
        delete res;

        delete pstmt;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() <<" )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;
}