#include "ClsMariaDBcpp.h"

using namespace std;
MDB_DESC db_desc = {"192.168.1.74", "dev", "dev", "els_test"};

int main(void)
{
    ClsMariaDBcpp MDB("MDB", &db_desc);
    //cout<<db_desc.database<<","<<db_desc.user<<", "<<db_desc.password<<", "<<db_desc.server<<endl;
    
    cout << endl;
    cout << "CLSDB test..." << endl;

    try
    {
        MDB.Connect();

        char blobaa[10];
        MDB.SetPrepareStmt("SELECT * FROM GW where GW_ID = 1");               

        if(MDB.Execute())
        {
            while (MDB.res->next()) {         
                cout <<"ID : "<< MDB.res->getInt("GW_ID") << endl;
                cout <<"NM : "<< MDB.res->getString("GW_NM").c_str() << endl;
            }
        }

        MDB.SetPrepareStmt("SELECT * FROM GW where GW_ID = 2");               

        if(MDB.Execute())
        {
            while (MDB.res->next()) {         
                cout <<"ID : "<< MDB.res->getInt("GW_ID") << endl;
                cout <<"NM : "<< MDB.res->getString("GW_NM") << endl;
            }
        }
    }
    catch(const std::exception& e)
    {     
        cout<<MDB.strExcepMsg1.str();
        cout<<MDB.strExcepMsg2.str();
        cout<<"EXCEPTION"<<endl;
        cout << "#0 ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << "# ERR: " << e.what()<<endl;
    }    

    return EXIT_SUCCESS;
}