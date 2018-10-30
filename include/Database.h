//
// Created by dipak on 29.10.18.
//

#ifndef DHT11_DATABASE_H
#define DHT11_DATABASE_H
#include <iostream>
#include "sqlite3.h"


class Database
{
public:
    Database(std::string inputFilename);
    ~Database();
    int openDatabase(const char *filename);
    void execute(const std::string statement);

private:
    sqlite3 *db;
    char *err_msg;
    int resultCode;
    std::string inputFilename;
    char *filename;
};


#endif //DHT11_DATABASE_H
