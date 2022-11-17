#include "SQLiteWrapper.h"

SQLiteWrapper::SQLiteWrapper(std::string path): path(path) {
	pathPointer = path.c_str();
	CreateDB();
}

void SQLiteWrapper::CreateDB(){
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open(pathPointer, &DB);

	sqlite3_close(DB);
}

void SQLiteWrapper::ExecuteQuery(std::string query, int (*callback)(void*, int, char**, char**)) {
	char* messageError;
	sqlite3* DB;
	int exit = 0;
	try
	{
		exit = sqlite3_open(path.c_str(), &DB);
		
		exit = sqlite3_exec(DB, query.c_str(), callback, NULL, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in " << query << messageError << std::endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Query Executed Successfully " << std::endl << query << std::endl;
		}
			
		sqlite3_close(DB);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		sqlite3_close(DB);
	}
}