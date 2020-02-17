//------------------------------------------------------------------------------
//
// Project:		General
// Target:		libGeneral.a
// Filename:	ClsMariaDBcpp.h
// Version:		1.1.1.0
// History:		Date		By		Content
//				----------	------	--------------------------------------------
// 
//------------------------------------------------------------------------------
#ifndef	ClsMariaDBCPPH
#define	ClsMariaDBCPPH
//------------------------------------------------------------------------------
// include
//------------------------------------------------------------------------------
/* Standard C++ includes */
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
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
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
// Type Definition
//------------------------------------------------------------------------------
// DB_STATE
//------------------------------------------------------------------------------
typedef enum {dsDisconnected_ = 0, dsConnected_, dsConnecting_}	DB_STATE_;
//------------------------------------------------------------------------------
// MDB_DESC
//------------------------------------------------------------------------------
typedef struct
{
	string	server;		// host address ("remote ip" or "localhost")
	string	user;		// user id
	string	password;	// user password
	string	database;	// database name
} MDB_DESC;

#define	MDB_DESC_SIZE		sizeof(MDB_DESC)
//------------------------------------------------------------------------------
// BlobData class
//------------------------------------------------------------------------------
class DataBuf : public streambuf
{
  public:
   DataBuf(char * d, size_t s) {
      setg(d, d, d + s);
   }
};
//------------------------------------------------------------------------------
// Class
//------------------------------------------------------------------------------
class ClsMariaDBcpp
{
private:
    MDB_DESC	m_desc;
    DB_STATE_	m_state;

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;        
    
    string strQuery;

    void Close(void);
    void ProcessException(string msg,sql::SQLException e);    
public:
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
    std::stringstream strExcepMsg1; 
    std::stringstream strExcepMsg2; 

    ClsMariaDBcpp(void);
    ClsMariaDBcpp(const char *pName, MDB_DESC *pDesc);
    ClsMariaDBcpp(const char *pName, string server, string user, string password, string database, bool connect = true);
    virtual ~ClsMariaDBcpp(void);

    bool Connect(void);
    void Disconnect(void);
    bool Execute();
    void SetPrepareStmt(string query);
    bool Init(MDB_DESC *pDesc, bool connect = false);    

    void SetBlob (int index, char* buf, int size);
    void SetBoolean (int index, bool value);
    void SetDouble (int index, double value);
    void SetInt (int index, int value);
    void SetNull (int index, int type);
    void SetString (int index, const char *value);
};
//------------------------------------------------------------------------------
#endif  // ClsMariaDBCPPH
//------------------------------------------------------------------------------
// End of ClsMariaDBcpp.h
//------------------------------------------------------------------------------