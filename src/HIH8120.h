
#ifndef HIH8120_H_
#define HIH8120_H_
#include <stdbool.h>

typedef enum hih8120_driverReturnCodes {
	HIH8120_OK	/**< Everything went well */
	,HIH8120_OUT_OF_HEAP /**< Not enough heap to initialise the driver */
	,HIH8120_DRIVER_NOT_INITIALISED /**< Driver must be initialise before use */
	,HIH8120_TWI_BUSY /**< The two wire/I2C interface is busy */
} hih8120_driverReturnCode_t;

class HIH8120{
public:
	HIH8120(unsigned int bus, unsigned int device);
	virtual bool isReady();
	virtual hih8120_driverReturnCode_t wakeup();
	virtual hih8120_driverReturnCode_t measure();
	virtual float getHumidity();
	virtual float getTemperature();
	virtual void displayData();
	};

#endif /* HIH8120_H_ */
