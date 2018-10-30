#include <iostream>
#include <string>
#include "Database.h"
#include "DHT11.h"
#include "sqlite3.h"

int main(int argc, char* argv[]) {
    //Local string to hold sqlite statements
    std::string sqlStatement;
    Database database("dht.11");

    // Creat Sqlite table dhtreadings if it does not exist
    sqlStatement = ("CREATE TABLE IF NOT EXISTS dhtreadings \
                    (id INTEGER PRIMARY KEY , \
                    humidity INTEGER, \
                    temperature INTEGER, \
                    datestamp DEFAULT CURRENT_DATE, \
                    timestamp DEFAULT (time('now', 'localtime'))); \
                    ");

    try {
        database.execute(sqlStatement);
    }
    catch (std::runtime_error const &exp) {
        std::cout << "Failed to execute: " << sqlStatement << " Reason: " << exp.what() << std::endl;
        return 0;
    }

    //Creating DHT class variable
    DHT11 dht11;
    //Creating tuple to retrieve values from DHT class
    std::tuple<int, int> dhtValues;

    std::cout << "Raspberry Pi wiringPi dht11 Temperature test program" << std::endl;

    if ( wiringPiSetup() == -1 )
        exit( 1 );
    //Loop every 5 minutes
    while (true)
    {
        dhtValues = dht11.getDhtValues();
        int humidity = std::get<0>(dhtValues);
        int temperature = std::get<1>(dhtValues);
        // Insert dht values into sqlite database
        std::string sqlStatement = "INSERT INTO dhtreadings(humidity, temperature) VALUES ("
                                    +  std::to_string(humidity) +
                                    "," +  std::to_string(temperature) + ");";

        database.execute(sqlStatement);
        std::cout <<  "The humidity is " << std::get<0>(dhtValues) << "% and temperature is " << std::get<1>(dhtValues) << " °C"<< std::endl;
        delay( 300000 );
    }
    return 0;
}