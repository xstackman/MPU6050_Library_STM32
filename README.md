## MPU6050 STM32 Library (Working/Under construction)

This is a C++ library for STM32 boards usign STM32CubeIDE.
This code implement the library in a STM32F767Zi Nucleo board usign this pinmap:

* I2C4_SDA = PF15
* I2C4_SCL = PF14
* USART3 RX/TX in PD8/PD9. This are directly connected to STlink and bridged to the computer.
* PB14 as debug LED. Including onboard

## How implement

After put the header and source file in your project you need to set the HAL library in the header file. For example, i'm working with the "stm32f7xx_hal.h" and i have the include in the line 139 of the header file. 

Then you can include this library in your main file. This is a C++ library so, you need to work with a C++ project and after generate your project you need to rename your main.c to main.cpp. After each config generation the IDE will generate a main.c so i recoment rename the main.cpp to main.c, then generate your code and then rename to main.cpp. If you know how generate only cpp files please tell me.

In your main code you need to declare the object:

    MPU6050 sensor = MPU6050(&hi2c4);

Also you need to set the I2C address. The comercial module have the A0 pin pulled low so the I2C address to operate are uncommented in the header file:

    #define MPU6050_WRITE_ADD 			0xD0
    #define MPU6050_READ_ADD 			0xD1

If you have a custom board or any other reason and you have Ao pulled high you need to uncomment this address:

    #define MPU6050_WRITE_ADD 			0xD2
    #define MPU6050_READ_ADD 			0xD3

After this settings you can start working with the module. Don't forget wake up the module with this:

    sensor.powerOn();

You need to set the basic settings, for example:

    sensor.powerOn();
	sensor.setSampleRateDiv(0);
	sensor.setLowPassFilter(0);
	sensor.setClockSource(internal8MHz);
	sensor.enableFIFO();
	sensor.enableTempSensor();
	sensor.resetTemperatureADC();

After this you can test the library.

I want any feedback :)






