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
        std::cout << "The temperature is " << std::get<0>(dhtValues) << " and humidity is " << std::get<1>(dhtValues) << std::endl;
        delay( 1000 );
    }
    return 0;
}