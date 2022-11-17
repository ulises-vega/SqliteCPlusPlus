//Final Version
#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "SQLiteWrapper.h"

using namespace std;

std::string ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	std::wstring path = std::wstring(buffer).substr(0, pos);
	return std::string(path.begin(), path.end());
}

int main()
{
	std::string dir = ExePath() + "\\Students.db";
	const char* dirPointer = dir.c_str();
	SQLiteWrapper sqlite(dir);

	std::string createHello = "CREATE TABLE IF NOT EXISTS HELLO("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME VARCHAR(255));";
	sqlite.ExecuteQuery(createHello, NULL);

	std::string insertHello = "INSERT INTO HELLO(NAME) VALUES('ULISES');";
	sqlite.ExecuteQuery(insertHello, NULL);


	//createDB(dirPointer);
	//createTable(dirPointer);
	//deleteData(dirPointer); // use prior to insert
	//insertData(dirPointer); // uncomment the deleteData above to avoid duplicates
	//updateData(dirPointer);
	//selectData(dirPointer);

	return 0;
}
//
//static int createDB(const char* s)
//{
//	sqlite3* DB;
//
//	int exit = 0;
//	exit = sqlite3_open(s, &DB);
//
//	sqlite3_close(DB);
//
//	return exit;
//}
//
//static int createTable(const char* s)
//{
//	sqlite3* DB;
//	char* messageError;
//
//	string sql = "CREATE TABLE IF NOT EXISTS GRADES("
//		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
//		"NAME      TEXT NOT NULL, "
//		"LNAME     TEXT NOT NULL, "
//		"AGE       INT  NOT NULL, "
//		"ADDRESS   CHAR(50), "
//		"GRADE     CHAR(1) );";
//	int exit = 0;
//	try
//	{
//		
//		exit = sqlite3_open(s, &DB);
//		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
//		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
//		if (exit != SQLITE_OK) {
//			cerr << "Error in createTable function." << messageError << endl;
//			sqlite3_free(messageError);
//		}
//		else
//			cout << "Table created Successfully" << endl;
//		sqlite3_close(DB);
//	}
//	catch (const exception& e)
//	{
//		cerr << e.what();
//	}
//
//	return exit;
//}
//
//static int insertData(const char* s)
//{
//	sqlite3* DB;
//	char* messageError;
//
//	string sql("INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Alice', 'Chapa', 35, 'Tampa', 'A');"
//		"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Bob', 'Lee', 20, 'Dallas', 'B');"
//		"INSERT INTO GRADES (NAME, LNAME, AGE, ADDRESS, GRADE) VALUES('Fred', 'Cooper', 24, 'New York', 'C');");
//
//	int exit = sqlite3_open(s, &DB);
//	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
//	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
//	if (exit != SQLITE_OK) {
//		cerr << "Error in insertData function." << endl;
//		sqlite3_free(messageError);
//	}
//	else
//		cout << "Records inserted Successfully!" << endl;
//
//	return 0;
//}
//
//static int updateData(const char* s)
//{
//	sqlite3* DB;
//	char* messageError;
//
//	string sql("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'");
//
//	int exit = sqlite3_open(s, &DB);
//	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
//	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
//	if (exit != SQLITE_OK) {
//		cerr << "Error in updateData function." << endl;
//		sqlite3_free(messageError);
//	}
//	else
//		cout << "Records updated Successfully!" << endl;
//
//	return 0;
//}
//
//static int deleteData(const char* s)
//{
//	sqlite3* DB;
//	char* messageError;
//
//	string sql = "DELETE FROM GRADES;";
//
//	int exit = sqlite3_open(s, &DB);
//	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
//	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
//	if (exit != SQLITE_OK) {
//		cerr << "Error in deleteData function." << endl;
//		sqlite3_free(messageError);
//	}
//	else
//		cout << "Records deleted Successfully!" << endl;
//
//	return 0;
//}
//
//static int selectData(const char* s)
//{
//	sqlite3* DB;
//	char* messageError;
//
//	string sql = "SELECT * FROM GRADES;";
//
//	int exit = sqlite3_open(s, &DB);
//	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
//	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
//
//	if (exit != SQLITE_OK) {
//		cerr << "Error in selectData function." << endl;
//		sqlite3_free(messageError);
//	}
//	else
//		cout << "Records selected Successfully!" << endl;
//
//	return 0;
//}

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		// column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}

	cout << endl;

	return 0;
}