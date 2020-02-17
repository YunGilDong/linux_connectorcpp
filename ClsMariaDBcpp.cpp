//------------------------------------------------------------------------------
//
// Project:		General
// Target:		libGeneral.a
// Filename:	ClsMariaDBcpp.cpp
// Version:		1.1.1.0
//
// History:
//	Date		Who	Rev		Content
//	----------	---	-------	------------------------------------------------
//
//------------------------------------------------------------------------------
// Include
//------------------------------------------------------------------------------
#pragma	hdrstop
#include "ClsMariaDBcpp.h"
//------------------------------------------------------------------------------
// ClsMariaDBcpp
//------------------------------------------------------------------------------
ClsMariaDBcpp::ClsMariaDBcpp(void)
{
    //InitObject("MDB");
	Init(NULL);
}
//------------------------------------------------------------------------------
ClsMariaDBcpp::ClsMariaDBcpp(const char *pName, MDB_DESC *pDesc)
{
    Init(pDesc);
}
//------------------------------------------------------------------------------
ClsMariaDBcpp::ClsMariaDBcpp(const char *pName, string server, string user, string password, string database, bool connect)
{
    MDB_DESC	desc;
	
	desc.server = server;
	desc.user = user;
	desc.password = password;
	desc.database = database;
	Init(&desc, connect);
}
//------------------------------------------------------------------------------
// ~ClsMariaDBcpp
//------------------------------------------------------------------------------
ClsMariaDBcpp::~ClsMariaDBcpp(void)
{
    Disconnect();
}
//------------------------------------------------------------------------------
// Connect
//------------------------------------------------------------------------------
bool ClsMariaDBcpp::Connect(void)
{    
    bool ok = true;
    try {
        cout<<m_desc.database<<","<<m_desc.user<<", "<<m_desc.password<<", "<<m_desc.server<<endl;
        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect(m_desc.server, m_desc.user, m_desc.password);
        /* Connect to the MySQL test database */
        con->setSchema(m_desc.database);

        m_state = dsConnected_;

        cout<<"database connected"<<endl;
    } catch (sql::SQLException &e) {        
        ok = false;
        m_state = dsDisconnected_;
        std::stringstream strSqlExcep;
        strSqlExcep<< "# ERR: SQLException in " << __FILE__<< "(" << __FUNCTION__ << ") on line "<< __LINE__<<endl;
        ProcessException(strSqlExcep.str(), e);
        throw e;
        // cout << "# ERR: SQLException in " << __FILE__;        
        // cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        // cout << "# ERR: " << e.what();
        // cout << " (MySQL error code: " << e.getErrorCode();
        // cout << ", SQLState: " << e.getSQLState() <<" )" << endl;        
    }

    return (ok);
}
//------------------------------------------------------------------------------
// Disconnect
//------------------------------------------------------------------------------
void ClsMariaDBcpp::Disconnect(void)
{
    if(m_state == dsDisconnected_)
        return ;
        
    delete con;
    con = NULL;
    Close();
}
//------------------------------------------------------------------------------
// Execute
//------------------------------------------------------------------------------
bool ClsMariaDBcpp::Execute()
{
    bool ok  = true;
    if(res != NULL)
        delete res;
    try
    {
        cout<<"execute(1)"<<endl;
        res = pstmt->executeQuery();
        cout<<"execute(2)"<<endl;
    } catch (sql::SQLException &e) {         
        ok = false;       
        std::stringstream strSqlExcep;
        strSqlExcep<< "# ERR: SQLException in " << __FILE__<< "(" << __FUNCTION__ << ") on line "<< __LINE__<<endl;
        ProcessException(strSqlExcep.str(), e);
        throw e;
    }
    return (ok);
}
//------------------------------------------------------------------------------
// SetPrepareStmt
//------------------------------------------------------------------------------
void ClsMariaDBcpp::SetPrepareStmt(string query)
{
    if(pstmt != NULL)
        delete pstmt;
    try
    {
        strQuery = query;
        pstmt = con->prepareStatement(strQuery);
    } catch (sql::SQLException &e) {        
        std::stringstream strSqlExcep;
        strSqlExcep<< "# ERR: SQLException in " << __FILE__<< "(" << __FUNCTION__ << ") on line "<< __LINE__<<endl;
        ProcessException(strSqlExcep.str(), e);
        throw e;
    }
}
//------------------------------------------------------------------------------
// Init
//------------------------------------------------------------------------------
bool ClsMariaDBcpp::Init(MDB_DESC *pDesc, bool connect)
{
    strQuery="";
    pstmt = NULL;
    res = NULL;

    if (pDesc != NULL)
	{
	    m_desc.server = pDesc->server;
	    m_desc.database = pDesc->database;
	    m_desc.user = pDesc->user;
	    m_desc.password = pDesc->password;		
	}
	else
	{
	    m_desc.server = "";
	    m_desc.database = "";
	    m_desc.user = "";
	    m_desc.password = "";		
	}
    m_state = dsDisconnected_;

   	return(connect ? Connect() : true);
}
//------------------------------------------------------------------------------
// Close
//------------------------------------------------------------------------------
void ClsMariaDBcpp::Close(void)
{
    cout<<"close 1"<<endl;    
    if(pstmt != NULL)
    {
        delete pstmt;
        delete res;  
    }
    cout<<"close 2"<<endl;   
}
//------------------------------------------------------------------------------
// ProcessException
//------------------------------------------------------------------------------
void ClsMariaDBcpp::ProcessException(string msg, sql::SQLException e)
{
    strExcepMsg1<<msg;
    strExcepMsg2<< "# ERR: " << e.what()<< " (MySQL error code: " << e.getErrorCode()<< ", SQLState: " << e.getSQLState() <<" )"<<endl;        
    //cout<<strExcepMsg1.str()<<endl;
    //cout<<strExcepMsg2.str()<<endl;

}
//------------------------------------------------------------------------------
void ClsMariaDBcpp::SetBlob (int index, char* pBuf, int size)
{
    try
    {
        DataBuf buffer(pBuf, size);
        istream stream(&buffer);
        pstmt->setBlob(1, &stream);
    }
    catch(const std::exception& e)
    {
        cout<<"bolb exception"<<endl;
        std::cerr << e.what() << '\n';
    }
}
//------------------------------------------------------------------------------
void ClsMariaDBcpp::SetBoolean (int index, bool value)
{
    pstmt->setBoolean(index, value);
}
//------------------------------------------------------------------------------
void ClsMariaDBcpp::SetDouble (int index, double value)
{
    pstmt->setDouble(index, value);
}
//------------------------------------------------------------------------------
void ClsMariaDBcpp::SetInt (int index, int value)
{    
    pstmt->setInt(index, value);
}
//------------------------------------------------------------------------------
void ClsMariaDBcpp::SetNull (int index, int type)
{
    pstmt->setNull(index, type);
}
//------------------------------------------------------------------------------
void ClsMariaDBcpp::SetString (int index, const char *value)
{
    cout<<"set string 1"<<endl;
    pstmt->setString(index, value);
    cout<<"set string 2"<<endl;
}
//------------------------------------------------------------------------------
// End of ClsMariaDBcpp.cpp
//------------------------------------------------------------------------------