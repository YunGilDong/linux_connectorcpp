/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <memory>
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
    cout << "Procedure test..." << endl;

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

        
        pstmt = con->prepareStatement("SELECT * FROM GW where GW_ID = ?");
        pstmt->setInt(1, 1);
        res = pstmt->executeQuery();

        while (res->next()) {         
            cout <<"ID : "<< res->getInt("GW_ID") << endl;
            cout <<"NM : "<< res->getString("GW_NM") << endl;
        }

        delete pstmt;
        delete res;        
        delete con;

        pstmt = NULL;
        res = NULL;
        con = NULL;

        if(con != NULL)
        {
            delete pstmt;
            delete res;        
            delete con;
        }

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