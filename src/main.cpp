#include <iostream>
#include "HIH8120.h"
#include "unistd.h"

using namespace std;

int main(int args, char *argv[]) {
	unsigned int i2c_bus = 2;
	while (1) {
		HIH8120 sensor(i2c_bus, 0x27);
		sensor.measure();
		sensor.displayData();

		usleep(1000000);
	}

	return 0;
}
