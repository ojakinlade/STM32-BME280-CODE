#include "stm32f4xx.h"                  // Device header
#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"
#include "gpio.h"
#include "bme280.h"

#define ADC_REGISTER_SIZE		8
#define CALIB00_25_SIZE			26
#define CALIB26_41_SIZE			16


//Private enums
enum Register_address
{
	BME280_ADDR = 0x76,
	CALIB_00_25_ADDR = 0x88,
	CALIB_26_41_ADDR = 0xE1,
	CTRL_HUM_ADDR = 0xF2,
	CTRL_MEAS_ADDR = 0xF4,
	DATA_REG_ADDR = 0xF7
};

enum Bit_field
{
	CTRL_HUM_OSRS_H_OVR1 = 0x01,
	CTRL_HUM_OSRS_H_OVR2 = 0x02,
	CTRL_HUM_OSRS_H_OVR4 = 0x03,
	CTRL_HUM_OSRS_H_OVR8 = 0x04,
	CTRL_HUM_OSRS_H_OVR16 = 0x05,
	
	CTRL_MEAS_OSRS_P_OVR1 = 1<<2,
	CTRL_MEAS_OSRS_P_OVR2 = 2<<2,
	CTRL_MEAS_OSRS_P_OVR4 = 3<<2,
	CTRL_MEAS_OSRS_P_OVR8 = 4<<2,
	CTRL_MEAS_OSRS_P_OVR16 = 5<<2,
	
	CTRL_MEAS_MODE_SLEEP = 0x00,
	CTRL_MEAS_MODE_FORCED1 = 0x01,
	CTRL_MEAS_MODE_FORCED2 = 0x02,
	CTRL_MEAS_MODE_NORMAL = 0x03,
	
	CTRL_MEAS_OSRS_T_OVR1 = 1<<5,
	CTRL_MEAS_OSRS_T_OVR2 = 2<<5,
	CTRL_MEAS_OSRS_T_OVR4 = 3<<5,
	CTRL_MEAS_OSRS_T_OVR8 = 4<<5,
	CTRL_MEAS_OSRS_T_OVR16 = 5<<5
};

typedef struct COMPENSATION_PARAMETER
{
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
	uint8_t dig_H1;
	int16_t dig_H2;
	uint8_t dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	int8_t dig_H6;
}bme280_comp_param_t;


static void BME280_Store_Compensation_Parameters(uint8_t* calibReg1, uint8_t* calibReg2, bme280_comp_param_t* bme)
{
	bme->dig_T1 = (calibReg1[0] | (calibReg1[1]<<8));
	bme->dig_T2 = (calibReg1[2] | (calibReg1[3]<<8));
	bme->dig_T3 = (calibReg1[4] | (calibReg1[5]<<8));
	bme->dig_P1 = (calibReg1[6] | (calibReg1[7]<<8));
	bme->dig_P2 = (calibReg1[8] | (calibReg1[9]<<8));
	bme->dig_P3 = (calibReg1[10] | (calibReg1[11]<<8));
	bme->dig_P4 = (calibReg1[12] | (calibReg1[13]<<8));
	bme->dig_P5 = (calibReg1[14] | (calibReg1[15]<<8));
	bme->dig_P6 = (calibReg1[16] | (calibReg1[17]<<8));
	bme->dig_P7 = (calibReg1[18] | (calibReg1[19]<<8));
	bme->dig_P8 = (calibReg1[20] | (calibReg1[21]<<8));
	bme->dig_P9 = (calibReg1[22] | (calibReg1[23]<<8));
	bme->dig_H1 = (calibReg1[25]);
	bme->dig_H2 = (calibReg2[0] | (calibReg2[1]<<8));
	bme->dig_H3 = (calibReg2[2]);
	bme->dig_H4 = ((calibReg2[3]<<4) | (calibReg2[4] & 0x0F));
	bme->dig_H5 = ((calibReg2[4] & 0xF0)>>4 | (calibReg2[5] << 4));
	bme->dig_H6 = (calibReg2[6]);
	
}

static uint8_t rawAdcValue[ADC_REGISTER_SIZE];
static uint8_t bme280calib00_25[CALIB00_25_SIZE];
static uint8_t bme280calib26_41[CALIB26_41_SIZE];
static bme280_comp_param_t bme280;
static int32_t t_fine;

void BME280_Init(void)
{
	GPIO_Alt_Func_Init(GPIOB, GPIO_PIN6_ALT_FUNCTION, GPIO_PIN6, I2C_1_2);
	GPIO_Alt_Func_Init(GPIOB, GPIO_PIN7_ALT_FUNCTION, GPIO_PIN7, I2C_1_2);
	I2C_Init(I2C1, I2C_PERIPH_CLOCK_FREQ_8MHZ, I2C_STANDARD_MODE_8MHZ_CCR, I2C_STANDARD_MODE_8MHZ_TRISE);
	I2C_ReadMultipleBytes(I2C1, BME280_ADDR, CALIB_00_25_ADDR, bme280calib00_25, CALIB00_25_SIZE);
	I2C_ReadMultipleBytes(I2C1, BME280_ADDR, CALIB_26_41_ADDR, bme280calib26_41, 7);
	BME280_Store_Compensation_Parameters(bme280calib00_25, bme280calib26_41, &bme280);	
}

void BME280_GetData(bme280_t* pSensorData)
{
	/*
	Description:
	Function to obtain compensated bme280 temperature, pressure and humidity readings.
	
	Parameters:
	1.)pSensorData: pointer to bme280_t structure containing temperature
	and humidity readings.
	
	Return:
	None
	
	Note:
	The actual temperature = sensor reading / 100 (see Bosch Sensortec BME280 datasheet).
	The actual humidity = sensor reading / 1024 (see Bosch Sensortec BME280 datasheet).
	*/
	I2C_WriteByte(I2C1,BME280_ADDR, CTRL_HUM_ADDR, CTRL_HUM_OSRS_H_OVR16);
	I2C_WriteByte(I2C1,BME280_ADDR, CTRL_MEAS_ADDR, (CTRL_MEAS_OSRS_T_OVR16 | CTRL_MEAS_OSRS_P_OVR16 | CTRL_MEAS_MODE_FORCED1));
	I2C_ReadMultipleBytes(I2C1,BME280_ADDR, DATA_REG_ADDR, rawAdcValue, ADC_REGISTER_SIZE);
	
	//The calculations below are based on equations from the.....
	//Bosch Sensortec BME280 datasheet.
	
	//Temperature calculation
	int32_t adc_T, var1, var2, T;
	adc_T = ((rawAdcValue[3] << 12) | (rawAdcValue[4] << 4) | (rawAdcValue[5] >> 4));
	var1 = ((((adc_T>>3) - ((int32_t)bme280.dig_T1<<1))) * ((int32_t)bme280.dig_T2)) >> 11;
	
	var2 = (((((adc_T>>4) - ((int32_t)bme280.dig_T1)) * 
						((adc_T>>4) - ((int32_t)bme280.dig_T1))) >> 12) * ((int32_t)bme280.dig_T3)) >> 14;

	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	
	pSensorData->temperature = T / 100;
	
	//Humidity calculation
	int32_t adc_H, v_x1_u32r;
	adc_H = ((rawAdcValue[6] << 8) | rawAdcValue[7]);

	v_x1_u32r = (t_fine - ((uint32_t)76800));
	
	v_x1_u32r = (((((adc_H << 14) - (((int32_t)bme280.dig_H4) << 20) -
              (((int32_t)bme280.dig_H5) * v_x1_u32r)) +
              ((int32_t)16384)) >> 15) *
              (((((((v_x1_u32r * ((int32_t)bme280.dig_H6)) >> 10) *
              (((v_x1_u32r * ((int32_t)bme280.dig_H3)) >> 11) +
              ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
              ((int32_t)bme280.dig_H2) + 8192) >> 14));
	
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)bme280.dig_H1)) >> 4));

	//change the ternary operators to if..else statements if you like
  v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
  v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
	
  uint32_t rawHumidity = (uint32_t)(v_x1_u32r >> 12);
	pSensorData->humidity = rawHumidity / 1024;
	
	//Pressure calculation
	int32_t var3, var4;
	uint32_t p;
	int32_t adc_P = ((rawAdcValue[0]<<12) | (rawAdcValue[1]<<4) | (rawAdcValue[2]>>4));
	var3 = (t_fine>>1) - (int32_t)64000;
	var4 = (((var3>>2) * (var3>>2))>>11) * (int32_t)bme280.dig_P6;
	var4 = var4 + ((var3*((int32_t)bme280.dig_P5))<<1);
	var4 = (var4>>2) + (((int32_t)bme280.dig_P4)<<16);
	var3 = (((bme280.dig_P3 * (((var3>>2) * (var3>>2)) >> 13))>>3) + ((((int32_t)bme280.dig_P2) *
					var3)>>1))>>18;
	var3 = ((((32768+var3))*((int32_t)bme280.dig_P1))>>15);
	
	if(var3 == 0)
	{
		return; //avoid exception caused by division by zero
	}
	p = (((uint32_t)(((int32_t)1048576)-adc_P) - (var4>>12)))*3125;
	if(p < 0x80000000)
	{
		p = (p << 1) / (uint32_t)var3;
	}
	else
	{
		p = (p / (uint32_t)var3) * 2;
	}
	
	var3 = (((int32_t)bme280.dig_P9) *((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
	var4 = (((int32_t)(p>>2)) * ((int32_t)bme280.dig_P8))>>13;
	p = (uint32_t)((int32_t)p + ((var1 + var2 + bme280.dig_P7) >> 4));
	pSensorData->pressure = p;
	
	
}





