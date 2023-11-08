#include "I2CDevice.h"
#include "HIH8120.h"
#include "unistd.h"
#include <cstdint>
#include <iostream>
using namespace std;


// I2C device file for the HIH8120 sensor (adjust as needed)
#define HIH8120_I2C_BUS BBB_I2C_2
// I2C address of the HIH8120 sensor
#define HIH8120_I2C_ADDR 0x27

// Global variable to keep track of the driver's initialization status
static bool isInitialized = false;
static I2CDevice* hih8120Device;

HIH8120::HIH8120(unsigned int bus, unsigned int device) {
	hih8120Device = new I2CDevice(bus, device);

    isInitialized = true;
}

bool HIH8120::isReady(void) {
    return isInitialized;
}

hih8120_driverReturnCode_t HIH8120::wakeup(void) {
    if (!isInitialized) {
        return HIH8120_DRIVER_NOT_INITIALISED;
    }
    unsigned char command = 0x0;
    // Send an I2C command to the sensor
    if (hih8120Device->write(command) != 1) {
        return HIH8120_TWI_BUSY;
    }

    return HIH8120_OK;
}

hih8120_driverReturnCode_t HIH8120::measure(void) {
    if (!isInitialized) {
        return HIH8120_DRIVER_NOT_INITIALISED;
    }

    wakeup();
    usleep(50000);

    return HIH8120_OK;
}

float HIH8120::getHumidity(void) {
    if (!isInitialized) {
        return -1.0; // Return an error value, e.g., -1, to indicate driver not initialized
    }

    // Read the 16-bit data value from the sensor
    unsigned char *data = ( hih8120Device->readDevice( 2 ) );

    if (data == nullptr) {
        return -1.0; // Handle error by returning an error value
    }


    double humidity = ( ( data[0] << 8 ) | data[1] ) & 0b0011111111111111;
    return humidity * ( 100.0 / ( ( 1<<14 ) - 2 ) );
}

float HIH8120::getTemperature(void) {
    if (!isInitialized) {
        return -1000.0; // Return an error value, e.g., -1000, to indicate driver not initialized
    }

    // Read the 16-bit data value from the sensor
    unsigned char* data = hih8120Device->readDevice(4);

    if (data == nullptr) {
        return -1000.0; // Handle error by returning an error value
    }

    double temperature = ( data[2] << 6 ) | ( data[3] >> 2 );
    return temperature * ( 165.0 / ( ( 1 << 14 ) - 2 ) ) - 40;
}

void HIH8120::displayData(void) {
	cout << "Temperature: " << getTemperature() << endl;
	cout << "Humidity: " << getHumidity() << endl;
}
