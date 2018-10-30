//
// Created by dipak on 29.10.18.
//

#include <Database.h>

Database::Database(std::string inputFilename)
{
    err_msg = nullptr;
    filename = const_cast<char *>(inputFilename.c_str());
    openDatabase(filename);
}

int Database::openDatabase(const char *filename)
{
    resultCode = sqlite3_open(filename, &db);
    if (resultCode != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
}

void Database::execute(const std::string statement)
{
    const char *sqlOperation = statement.c_str();
    resultCode = sqlite3_exec(db, sqlOperation, 0, 0, &err_msg);
    if (resultCode != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
}

Database::~Database()
{
    std::cout << "Closing database" << std::endl;
    sqlite3_close(db);
}
