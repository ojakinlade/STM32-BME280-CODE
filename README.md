# STM32-BME280-CODE
Lightweight, reusable, and portable code to interface the Bosch Sensortec BME280 sensor with STM32F4 microcontrollers.

# Requirements
1.) ARM keil uVision 5 MDK

2.) STM32F4 microcontroller e.g. STM32F407VGTx(STM32F4Discovery board) used in the sample code

3.) Bosch Sensortec BME280 sensor

4.) Breadboard

5.) Connectors (Male-Female jumper wires)

# Connections
| N | BME280 | STM32 |
|:---:| :-------:| :------:|
| 1 | VIN    |      3V  |
| 2 | GND    |      GND  |
| 3 |  SDA  |    SDA (Sample code uses PB7)|
| 4 |  SCL  |    SCL (Sample code uses PB6)|

# Software Architecture
The program is divided into 3 layers of software. These layers are:

1.) Low Layer API

2.) High Level API

3.) Main Application

Low Layer APIs are functions that directly interface with the STM32F4 hardware e.g GPIO drivers, I2C drivers, SysTick drivers etc.

High Layer APIs are functions that access the hardware through Low Layer APIs thereby creating a level of abstraction e.g. BME280 drivers, and System drivers etc

The Main Application is a layer of software that is intended to reflect the logic behind the project without knowing much about the hardware. It i the highest level of abstraction
and it calls High Layer APIs in order to perform operations.

# Description of sample code
The humidity, pressure and temperature readings of the BME280 sensor are contained in a variable of type **bme280_t** whose address is passed to the **BME280_Get_Data()**
function. For demonstration purposes, the structure variable that contains the sensor data is named bme280Data and declared in the main function as follows:

```
bme20_t bme280Data;
```
# Checking the Sensor's readings using Keil uVision's debugger
Steps:

1.) Open Keil uVision debugger and ensure the active window is the **main.c**

2.) Set a breakpoint on the line in which the **System_Timer_DelayMs()** function is called in the while(1) loop

3.) Add bme280Data structure to one of the watch windows

3.) Run the debugger

4.) When the debugger stops, check the bme280Data's humidity, pressure and temperature structure members for the BME280 sensor's readings.

# Additional Reseources
1.) STM32F4 reference manual

2.) BME280 Datasheet

3.) STM32F407 datasheet

# NOTE
To use the project in a plug-and-play manner, follow the connections and instructions above and run the sample code on an STM32F4 board.


