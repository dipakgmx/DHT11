# DHT11
A C++ implementaion for the Raspberry Pi to read temperature and humidity values from the DHT11 sensor and save into a sqlite3 db.

## Usage
Specify the GPIO pin in the constructur call for the `DHT11` object within the `main()` function.

Specify the sampling time also in the `main()` function by setting the delay value (here specified as 5 minutes `delay(300000)` ). Note that the delay is specified in milliseconds. 
