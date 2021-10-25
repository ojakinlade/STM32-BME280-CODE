#include <stdint.h>
#include <stdbool.h>
#include "system.h"
#include "bme280.h"

bme280_t data;

int main(void)
{
	
	System_Init();
	BME280_Init();
	BME280_GetData(&data);

	while(1)
	{
		
	}
}
