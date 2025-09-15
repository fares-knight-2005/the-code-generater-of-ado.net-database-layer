// thsi Code Genrater Was Made By Fares
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum parmiterType {str = 1, integer = 2 , bol = 3 , DateTime = 4 , byte = 5 , doubl = 6 };

string types[] = { "" , "string" , "int" , "bool" , "DateTime" , "byte" , "Double" };

struct parmiter
{
    string parmiterName;
    parmiterType type;
    bool nullable;
    bool findMethod;

    parmiter(string Name, parmiterType type, bool nullable, bool findMethod)
    {
        this->findMethod = findMethod;
        this->nullable = nullable;
        this->parmiterName = Name;
        this->type = type;
    }
    parmiter(string name , parmiterType type)
    {
        this->findMethod = false;
        this->nullable = false;
        this->parmiterName = name;
        this->type = type;
    }

    parmiter(){}
};

struct DBinfo
{
    vector <parmiter> parmiters;
    string dBName;
    string tableName;
    string newTableName;
    string idName;

    DBinfo(vector <parmiter> parmiters, string dBName, string tableName , string newTableName , string idName)
    {
        this->dBName = dBName;
        this->parmiters = parmiters;
        this->tableName = tableName;
        this->newTableName = newTableName;
        this->idName = idName;
    }
    DBinfo(vector <parmiter> parmiters, string dBName, string tableName , string idName)
    {
        this->dBName = dBName;
        this->parmiters = parmiters;
        this->tableName = tableName;
        this->newTableName = tableName;
        this->idName = idName;
    }

    DBinfo()
    {
        this->dBName = "";
        this->newTableName = "";
        this->tableName = "";
        this->idName = "";
    }

};

parmiterType readParmiterType()
{
    cout << "\n\n";
    cout << "Choose Paramiter Kind : \n";
    cout << "[1] String   [2] Integer \n";
    cout << "[3] Boolean  [4] DateTime \n";
    cout << "[5] Byte     [6] Double \n";
    cout << "---------------------------" << endl;
    int choice;
    cin >> choice;

    cout << endl << endl;
    return (parmiterType)choice;
}

DBinfo readDBinfo()
{
    DBinfo toRead;

    cout << "Enter Database Name : ";
    cin >> toRead.dBName;
    cout << "Enter Table Name : ";
    cin >> toRead.tableName;
    cout << "Enter Table Name Inside The Finc Like (Add New person) Not People \n If They Are The Same Enter no : ";
    cin >> toRead.newTableName;
    if (toRead.newTableName == "no")
        toRead.newTableName = toRead.tableName;
    cout << "Enter ID Name in Your Database : ";
    cin >> toRead.idName;
    
    cout << "Now Please Enter Info About Paramiters \nWhen You Want To Stop Please Enter The Parmiter Name As \"stop\"";
    string pName = "";
    while (true)
    {
        cout << "Enter Paramiter Name or (stop) to Stop : ";
        cin >> pName;
        if (pName == "stop")
            break;
        parmiter p(pName , readParmiterType());
       
        cout << "If Allow Null Enter (1) else 0 : ";
        cin >> p.nullable;
        cout << endl << "If You Want Method Find By " << p.parmiterName << "Enter (1) else 0 : ";
        cin >> p.findMethod;

        toRead.parmiters.push_back(p);
    }
    return toRead;
}

string paramitersToString(vector <parmiter> all , bool withRef = false)
{
    
    string s = "";
    for (parmiter p : all)
    {

        s +=  (withRef ? " ref " : " ") + types[p.type] + " " + p.parmiterName + " ,";
    }
    s.erase(--s.end(), s.end());
    return s;
}

string paramitersToStringWithoutType(vector <parmiter> all , bool with = false)
{

    string s = "";
    for (parmiter p : all)
    {
        if (with)
        {
            s += "@";
        }
        s += p.parmiterName + " ,";
    }
    s.erase(--s.end(), s.end());
    return s;
}

void printParmiters(vector <parmiter> all)
{
    cout << endl;
    for (parmiter p : all)
    {
        if (!p.nullable)
        {
            cout << "        cmd.Parameters.AddWithValue(\"@" << p.parmiterName << "\", " << p.parmiterName << ");\n";
        }
        else
        {
            cout << "        if (" << p.parmiterName << " != null)\n";
            cout << "            cmd.Parameters.AddWithValue(\"@" << p.parmiterName << "\", " << p.parmiterName << ");\n";
            cout << "        else\n";
            cout << "            cmd.Parameters.AddWithValue(\"@" << p.parmiterName << "\", DBNull.Value);\n";
        }
    }
    cout << endl << endl;
}


string paramitersToEquals(vector <parmiter> all)
{

    string s = "";
    for (parmiter p : all)
    {
        s += p.parmiterName + "=@" + p.parmiterName + " ,";
    }
    s.erase(--s.end(), s.end());
    return s;
}

void prpar(vector <parmiter> all , parmiter pa)
{
    cout << "\n\n";
    for (parmiter p : all)
    {
        if (p.parmiterName == pa.parmiterName)
            continue;

        if (!p.nullable) {
            cout << p.parmiterName << " = (" << types[p.type] << ") reader[\"" << p.parmiterName << "\"];\n";
        }
        else
        {
            cout << p.parmiterName << " = reader[\" " << p.parmiterName << "\"] != DBNull.Value ? (" << types[p.type] << ") reader[\"" << p.parmiterName << "\"] : null;\n";
        }
    }
    cout << endl << endl;
}

void GenrateCode()
{
    DBinfo info = readDBinfo();
    system("cls");
    cout << "please Use Those in Your Code : \n";
    cout << "using System;\nusing System.Data;\nusing System.Data.SqlClient;" << endl;
    cout << endl << "And Then copy The Code I Will Write and Put it in Your Class " << endl;
    system("pause");
    system("cls");

    cout << "        private static string connectionString = \"Server = .;Database = " << info.dBName << ";User Id = sa; Password = 123456;\";\n";
    cout << "        public static int AddNew" << info.newTableName << "(";
    cout << paramitersToString(info.parmiters) << ")" << "\n";
    cout << "        {\n";
    cout << "        int ID = -1;\n";
    cout << "        SqlConnection con = new SqlConnection(connectionString);\n";
    cout << "        string query = \"Insert into " << info.tableName << "(" << paramitersToStringWithoutType(info.parmiters) << ")" << " \"+\n";
    cout << "            \"values" << "(" << paramitersToStringWithoutType(info.parmiters, true) << ")" << "; select Scope_Identity();\";\n";
    cout << "        SqlCommand cmd = new SqlCommand(query, con);\n" << endl;
    printParmiters(info.parmiters);

    cout << "        try\n";
    cout << "        {\n";
    cout << "            con.Open();\n\n";
    cout << "            object Readed = cmd.ExecuteScalar();\n\n";
    cout << "            if (Readed != null && int.TryParse(Readed.ToString(), out int NewID))\n";
    cout << "            {\n";
    cout << "                ID = NewID;\n";
    cout << "            }\n";
    cout << "        }\n" << endl;
    cout << "        catch (Exception ex){}\n\n";
    cout << "        finally { con.Close(); }\n";
    cout << "        return ID;\n";
    cout << "    }\n\n" << endl;





    cout << "public static bool Update" << info.newTableName << "(int id ," << paramitersToString(info.parmiters) << ")\n";
    cout << "    {\n";
    cout << "        SqlConnection conn = new SqlConnection(connectionString);\n";
    cout << "        string query = \"Update " << info.tableName << " set " << paramitersToEquals(info.parmiters) << "\" + " << endl;
    cout << "            \"where " << info.idName << " = @ID\";\n";
    cout << "        SqlCommand cmd = new SqlCommand(query, conn);\n";
    cout << "        cmd.Parameters.AddWithValue(\"@ID\", id);\n";
    printParmiters(info.parmiters);
    cout << "        int effectedRows = 0;\n";
    cout << "        try\n";
    cout << "        {\n";
    cout << "            conn.Open();\n";
    cout << "            effectedRows = cmd.ExecuteNonQuery();\n";
    cout << "        }\n";
    cout << "        catch (Exception ex) {}\n";
    cout << "        finally{conn.Close();}\n";
    cout << "        return (effectedRows > 0);\n";
    cout << "    }\n" << endl << endl;





    cout << "    public static bool Delete" << info.newTableName << "(int id)\n";
    cout << "    {\n";
    cout << "        SqlConnection conn = new SqlConnection(connectionString);\n";
    cout << "        string query = \"Delete From " << info.tableName << " Where " << info.idName << " = @ID\";\n";
    cout << "        SqlCommand cmd = new SqlCommand(query, conn);\n";
    cout << "        cmd.Parameters.AddWithValue(\"@ID\", id);\n";
    cout << "        bool IsDeleted = false;\n";
    cout << "        try\n";
    cout << "        {\n";
    cout << "            conn.Open();\n";
    cout << "            int numberOfEffectedRows = cmd.ExecuteNonQuery();\n";
    cout << "            if (numberOfEffectedRows > 0)  IsDeleted = true;\n";
    cout << "        }\n";
    cout << "        catch (Exception ex) {}\n";
    cout << "        finally { conn.Close(); }\n";
    cout << "        return IsDeleted;\n";
    cout << "    }\n" << endl << endl;
   




    cout << "    public static DataTable GetAll" << info.tableName << "()\n";
    cout << "    {\n";
    cout << "        DataTable dataTable = new DataTable();\n";
    cout << "        SqlConnection con = new SqlConnection(connectionString);\n";
    cout << "        string query = \"Select * from " << info.tableName << "\";\n";
    cout << "        SqlCommand command = new SqlCommand(query, con);\n";
    cout << "        try\n";
    cout << "        {\n";
    cout << "            con.Open();\n";
    cout << "            SqlDataReader reader = command.ExecuteReader();\n";
    cout << "            if (reader.HasRows)  dataTable.Load(reader);\n";
    cout << "            reader.Close();\n";
    cout << "        }\n";
    cout << "        catch (Exception ex) {}\n";
    cout << "        finally { con.Close(); }\n";
    cout << "        return dataTable;\n";
    cout << "    }\n" << endl << endl;


    parmiter i;
    i.parmiterName = info.idName;
    i.type = parmiterType::integer;
    i.nullable = false;
    i.findMethod = true;
    info.parmiters.push_back(i);

    for (parmiter p : info.parmiters)
    {
        if (p.findMethod)
        {
            cout << "    public static bool Find" << info.newTableName <<"By" << p.parmiterName << "(" << paramitersToString(info.parmiters , true) << ")\n";
            cout << "    {\n";
            cout << "        SqlConnection conn = new SqlConnection(connectionString);\n";
            cout << "        string query = \"Select * from " << info.tableName << " where " << p.parmiterName << " = @" << p.parmiterName << "\";\n";
            cout << "        SqlCommand cmd = new SqlCommand(query, conn);\n";
            cout << "        cmd.Parameters.AddWithValue(\"@" << p.parmiterName << "\", " << p.parmiterName << ");\n";
            cout << "        bool isFound = false;\n";
            cout << "        try\n";
            cout << "        {\n";
            cout << "            conn.Open();\n";
            cout << "            SqlDataReader reader = cmd.ExecuteReader();\n";
            cout << "            if (reader.Read()){\n";
            cout << "                isFound = true;\n";
            prpar(info.parmiters , p);
            cout << "            }\n";
            cout << "            reader.Close();\n";
            cout << "        }\n";
            cout << "        catch (Exception ex) {}\n";
            cout << "        finally { conn.Close(); }\n";
            cout << "        return isFound;\n";
            cout << "    }\n";
            cout << endl << endl;
        }



        cout << "        public static bool Is" << info.newTableName <<"ExistBy" << p.parmiterName << "(" << types[p.type] << " " << p.parmiterName << ")\n";
        cout << "        {\n";
        cout << "            SqlConnection con = new SqlConnection(connectionString);\n";
        cout << "            string Query = \"Select found = 1 from " << info.tableName << " where " << p.parmiterName << " = @" << p.parmiterName << "\";\n";
        cout << "            SqlCommand command = new SqlCommand(Query, con);\n";
        cout << "            command.Parameters.AddWithValue(\"@" << p.parmiterName << "\", " << p.parmiterName << ");\n";
        cout << "            bool isFound = false;\n";
        cout << "            try\n";
        cout << "            {\n";
        cout << "                con.Open();\n";
        cout << "                SqlDataReader reader = command.ExecuteReader();\n";
        cout << "                isFound = reader.HasRows;\n";
        cout << "                reader.Close();\n";
        cout << "            }\n";
        cout << "            catch (Exception ex) {}\n";
        cout << "            finally { con.Close(); }\n";
        cout << "            return isFound;\n";
        cout << "        }\n";
     
    }

}


int main()
{
    cout << "This program is to genrate Code for basic functions (add , delete , update , get all , find by .. , is exist by ..)\n";
    cout << "I am Using ADO.Net Becuse it's Faster than ORM and More Effeshant " << endl;
    cout << "This Code should Be Used Carfuly I Didn't Handle Any Thing It Was Fast Work To Code Faster" << endl;
    system("pause");
    system("cls");
    GenrateCode();
}
