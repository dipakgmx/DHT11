//
// Created by dipak on 21.10.18.
//

#include <DHT11.h>

DHT11::DHT11(uint8_t dhtPin, uint8_t timeOut)
    : dhtPin(dhtPin), timeOut(timeOut)
{

}
std::tuple<int, int> DHT11::getDhtValues()
{
    int temperature{0};
    int humidity{0};
    for (int attempt = 0; attempt < 20; attempt++) {

        std::array<int, 5> dht_values{0};
        uint8_t lastState	= HIGH;
        uint8_t counter		= 0;
        uint8_t j		= 0, i;

        pinMode( dhtPin, OUTPUT );
        digitalWrite( dhtPin, LOW );
        delay( 18 );
        digitalWrite( dhtPin, HIGH );
        delayMicroseconds( 40 );
        pinMode( dhtPin, INPUT );


        for ( i = 0; i < timeOut; i++ )
        {
            counter = 0;
            while ( digitalRead( dhtPin ) == lastState )
            {
                counter++;
                delayMicroseconds( 1 );
                if ( counter == 255 )
                {
                    break;
                }
            }

            lastState = static_cast<uint8_t>(digitalRead(dhtPin ));

            if ( counter == 255 )
                break;

            if ( (i >= 4) && (i % 2 == 0) )
            {
                dht_values[j / 8] <<= 1;
                if ( counter > 50 )
                    dht_values[j / 8] |= 1;
                j++;
            }
        }

        if ( (j >= 40) &&
            (dht_values[4] == ( (dht_values[0] + dht_values[1] + dht_values[2] + dht_values[3]) & 0xFF) ) )
        {
            temperature = dht_values[0];
            humidity = dht_values[2];
            break;
        }
    }
    return std::make_tuple(temperature, humidity);
}


