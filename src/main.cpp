#include <iostream>
#include <string>
#include "dht.h"
#include "sqlite3.h"

int main(int argc, char* argv[]) {

    //Creating database handle -db
    sqlite3 *db;
    sqlite3_stmt *res;
    char *err_msg = nullptr;

    int rc = sqlite3_open("dht11.db", &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    char *sql = const_cast<char *>("CREATE TABLE IF NOT EXISTS dhtreadings \
            (id INTEGER PRIMARY KEY , \
            humidity INTEGER, \
            temperature INTEGER, \
            datestamp DEFAULT CURRENT_DATE, \
            timestamp DEFAULT (time('now', 'localtime'))); \
    ");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to create table!. SQL error " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    else {
        std::cout << "Creation of SQL table successful!" << std::endl;
    }


    dht DHT11;
    std::tuple<int, int> dhtValues;
    std::cout << "Raspberry Pi wiringPi DHT11 Temperature test program" << std::endl;

    if ( wiringPiSetup() == -1 )
        exit( 1 );

    while (true)
    {
        dhtValues = DHT11.getDhtValues();
        int humidity = std::get<0>(dhtValues);
        int temperature = std::get<1>(dhtValues);

        std::string sqlStatement = "INSERT INTO dhtreadings(humidity, temperature) VALUES ("
                                    +  std::to_string(humidity) +
                                    "," +  std::to_string(temperature) + ");";

        const char *sqlOperation = sqlStatement.c_str();
        rc = sqlite3_exec(db, sqlOperation, 0, 0, &err_msg);
        if (rc != SQLITE_OK) {
            std::cerr << "Element insertion failed!" << sqlite3_errmsg(db) << std::endl;
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 1;
        }
        std::cout <<  "The humidity is " << std::get<0>(dhtValues) << "% and temperature is " << std::get<1>(dhtValues) << " °C"<< std::endl;
        delay( 2000 );
    }
    return 0;
}