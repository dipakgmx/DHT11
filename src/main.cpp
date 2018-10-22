#include <iostream>
#include "dht.h"

int main()
{
    dht DHT11;
    std::tuple<int, int> dhtValues;
    std::cout << "Raspberry Pi wiringPi DHT11 Temperature test program" << std::endl;

    if ( wiringPiSetup() == -1 )
        exit( 1 );

    while (true)
    {
        dhtValues = DHT11.getDhtValues();
        std::cout << "The humidity is " << std::get<0>(dhtValues) << "% and temperature is " << std::get<1>(dhtValues) << " °C"<< std::endl;
        delay( 2000 );
    }
    return 0;
}