/*
 * MPU6050.h
 *
 *  Created on: May 11, 2021
 *      Author: hydra
 */

#ifndef MPU6050_H_
#define MPU6050_H_

/* REGISTERS */

#define	MPU6050_SELF_TEST_X			0x0D
#define	MPU6050_SELF_TEST_Y			0x0E
#define	MPU6050_SELF_TEST_Z			0x0F
#define	MPU6050_SELF_TEST_A			0x10
#define	MPU6050_SMPLRT_DIV			0x19
#define	MPU6050_CONFIG				0x1A
#define	MPU6050_GYRO_CONFIG			0x1B
#define	MPU6050_ACCEL_CONFIG			0x1C
#define	MPU6050_FIFO_EN				0x23
#define	MPU6050_I2C_MST_CTRL			0x24
#define	MPU6050_I2C_SLV0_ADDR			0x25
#define	MPU6050_I2C_SLV0_REG			0x26
#define	MPU6050_I2C_SLV0_CTRL			0x27
#define	MPU6050_I2C_SLV1_ADDR			0x28
#define	MPU6050_I2C_SLV1_REG			0x29
#define	MPU6050_I2C_SLV1_CTRL			0x2A
#define	MPU6050_I2C_SLV2_ADDR			0x2B
#define	MPU6050_I2C_SLV2_REG			0x2C
#define	MPU6050_I2C_SLV2_CTRL			0x2D
#define	MPU6050_I2C_SLV3_ADDR			0x2E
#define	MPU6050_I2C_SLV3_REG			0x2F
#define	MPU6050_I2C_SLV3_CTRL			0x30
#define	MPU6050_I2C_SLV4_ADD			0x31
#define	MPU6050_I2C_SLV4_REG			0x32
#define	MPU6050_I2C_SLV4_DO			0x33
#define	MPU6050_I2C_SLV4_CTRL			0x34
#define	MPU6050_I2C_SLV4_DI				0x35
#define	MPU6050_I2C_MST_STATUS			0x36
#define	MPU6050_INT_PIN_CFG			0x37
#define	MPU6050_INT_ENABLE			0x38
#define	MPU6050_INT_STATUS				0x3A
#define	MPU6050_ACCEL_XOUT_H			0x3B
#define	MPU6050_ACCEL_XOUT_L			0x3C
#define	MPU6050_ACCEL_YOUT_H			0x3D
#define	MPU6050_ACCEL_YOUT_L			0x3E
#define	MPU6050_ACCEL_ZOUT_H			0x3F
#define	MPU6050_ACCEL_ZOUT_L			0x40
#define	MPU6050_TEMP_OUT_H			0x41
#define	MPU6050_TEMP_OUT_L			0x42
#define	MPU6050_GYRO_XOUT_H			0x43
#define	MPU6050_GYRO_XOUT_L			0x44
#define	MPU6050_GYRO_YOUT_H			0x45
#define	MPU6050_GYRO_YOUT_L			0x46
#define	MPU6050_GYRO_ZOUT_H			0x47
#define	MPU6050_GYRO_ZOUT_L			0x48
#define	MPU6050_EXT_SENS_DATA_00		0x49
#define	MPU6050_EXT_SENS_DATA_01		0x4A
#define	MPU6050_EXT_SENS_DATA_02		0x4B
#define	MPU6050_EXT_SENS_DATA_03		0x4C
#define	MPU6050_EXT_SENS_DATA_04		0x4D
#define	MPU6050_EXT_SENS_DATA_05		0x4E
#define	MPU6050_EXT_SENS_DATA_06		0x4F
#define	MPU6050_EXT_SENS_DATA_07		0x50
#define	MPU6050_EXT_SENS_DATA_08		0x51
#define	MPU6050_EXT_SENS_DATA_09		0x52
#define	MPU6050_EXT_SENS_DATA_10		0x53
#define	MPU6050_EXT_SENS_DATA_11		0x54
#define	MPU6050_EXT_SENS_DATA_12		0x55
#define	MPU6050_EXT_SENS_DATA_13		0x56
#define	MPU6050_EXT_SENS_DATA_14		0x57
#define	MPU6050_EXT_SENS_DATA_15		0x58
#define	MPU6050_EXT_SENS_DATA_16		0x59
#define	MPU6050_EXT_SENS_DATA_17		0x5A
#define	MPU6050_EXT_SENS_DATA_18		0x5B
#define	MPU6050_EXT_SENS_DATA_19		0x5C
#define	MPU6050_EXT_SENS_DATA_20		0x5D
#define	MPU6050_EXT_SENS_DATA_21		0x5E
#define	MPU6050_EXT_SENS_DATA_22		0x5F
#define	MPU6050_EXT_SENS_DATA_23		0x60
#define	MPU6050_I2C_SLV0_DO			0x63
#define	MPU6050_I2C_SLV1_DO			0x64
#define	MPU6050_I2C_SLV2_DO			0x65
#define	MPU6050_I2C_SLV3_DO			0x66
#define	MPU6050_I2C_MST_DELAY_CTRL	0x67
#define	MPU6050_SIGNAL_PATH_RESET		0x68
#define	MPU6050_USER_CTRL				0x6A
#define	MPU6050_PWR_MGMT_1			0x6B
#define	MPU6050_PWR_MGMT_2			0x6C
#define	MPU6050_FIFO_COUNTH			0x72
#define	MPU6050_FIFO_COUNTL			0x73
#define	MPU6050_FIFO_R_W				0x74
#define	MPU6050_WHO_AM_I				0x75


/*  If you have pulled-up the A0 pin.
 */

//#define MPU6050_WRITE_ADD 			0xD2
//#define MPU6050_READ_ADD 			0xD3

/*  If you have pulled-low the A0 pin.
  Default setting in MPU6050 module */

#define MPU6050_WRITE_ADD 			0xD0
#define MPU6050_READ_ADD 			0xD1



typedef enum
{
	Gscale1 = 0x00,		/*  ± 250 °/s  */
	Gscale2 = 0x01,		/*  ± 500 °/s  */
	Gscale3 = 0x02,		/*  ± 1000 °/s  */
	Gscale4 = 0x03    		/*  ± 2000 °/s  */
} GyroScaleRange;

typedef enum
{
	Ascale1 = 0x00,		/*  ± 2 g  */
	Ascale2 = 0x01,		/*  ± 4 g  */
	Ascale3 = 0x02,		/*  ± 8 g  */
	Ascale4 = 0x03    		/*  ± 16 g  */
} AccelScaleRange;

typedef enum
{
	internal8MHz = 0x00,
	pllXGyroRef = 0x01,
	pllYGyroRef = 0x02,
	pllZGyroRef = 0x03,
	pllExt32768KHzRef = 0x04,
	pllExt192MHzRef = 0x05,
	stopClock= 0x07

}MPU6050ClockSource;

#include "stm32f7xx_hal.h"




class MPU6050
{
	public:
		MPU6050 ();
		MPU6050 (I2C_HandleTypeDef *dev,uint8_t add);
		int isDetected();
		int getFIFOCount();
		int setClockSource(uint8_t d);
		int enableTempSensor();
		int disableTempSensor();
		int goSleep();
		int resetDevice();
		int resetFIFO();
		int enableFIFO();
		int resetTemperatureADC();
		int resetAccelerometerADC();
		int resetGyroscopeADC();
		int16_t getGyroZ();
		int16_t getGyroY();
		int16_t getGyroX();
		float getTemperature();
		int16_t getAccelZ();
		int16_t getAccelY();
		int16_t getAccelX();
		int enableZGyroscopeFifo();
		int enableYGyroscopeFifo();
		int enableXGyroscopeFifo();
		int enableTemperatureFifo();
		int  writeFifoReg(uint8_t d);
		int setAccelerometerScale(uint8_t d);
		int selfTestZAAxis();
		int selfTestYAAxis();
		int selfTestXAAxis();
		int setAccelerometerConfig(uint8_t d);
		int setGyroscopeScale(uint8_t d);
		int selfTestZGAxis();
		int selfTestYGAxis();
		int selfTestXGAxis();
		int setGyroscopeConfig(uint8_t d);
		int setLowPassFilter(uint8_t d);
		int setExtFrameSync(uint8_t d);
		int  setSampleRateDiv(uint8_t val);
		int powerOn();





		HAL_StatusTypeDef writeSingleByte(uint8_t d, uint8_t reg);
		HAL_StatusTypeDef writeWords(uint8_t *buffer,uint8_t len, uint8_t reg);
		HAL_StatusTypeDef readSingleByte(uint8_t *d, uint8_t reg);
		HAL_StatusTypeDef readWords(uint8_t *buffer,uint8_t len, uint8_t reg);
	private:
		I2C_HandleTypeDef *_dev;
		uint8_t _dev_address;
};

#endif /* MPU6050_H_ */
