#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>
class SQLiteWrapper
{
private:
	sqlite3* db;
	std::string path;
	const char* pathPointer;

public:
	SQLiteWrapper(std::string path);
	void CreateDB();
	void ExecuteQuery(std::string query, int (*callback)(void*, int, char**, char**));
};

