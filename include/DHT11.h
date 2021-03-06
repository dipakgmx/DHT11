//
// Created by dipak on 21.10.18.
//

#ifndef DHT11_DHT_H
#define DHT11_DHT_H

#include <wiringPi.h>
#include <cstdint>
#include <tuple>
#include <array>

class DHT11
{
private:
    uint8_t dhtPin;
    uint8_t timeOut;

public:
    DHT11(uint8_t dhtPin = 7, uint8_t timeOut = 85);
    std::tuple<int, int> getDhtValues();

};


#endif //DHT11_DHT_H
