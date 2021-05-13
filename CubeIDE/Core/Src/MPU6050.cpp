/*
 * MPU6050.cpp
 *
 *  Created on: May 11, 2021
 *      Author: hydra
 */

#include "MPU6050.h"

MPU6050::MPU6050 () {
	// TODO Auto-generated constructor stub

}
MPU6050::MPU6050 (I2C_HandleTypeDef *dev,uint8_t add)
{
	_dev=dev;
	_dev_address=add;

}

int MPU6050:: isDetected()
{
	uint8_t tmp=0;

	if(_dev==NULL)
		return 0;
	else
	{
		HAL_StatusTypeDef result = readSingleByte(&tmp, MPU6050_WHO_AM_I);

		if(result!=HAL_OK)
			return 0;
		else
		{
			if(tmp==0x68)
				return 1;
			else
				return 0;
		}

	}
}


int  MPU6050::setSampleRateDiv(uint8_t val)
{
	HAL_StatusTypeDef status = writeSingleByte(val,MPU6050_SMPLRT_DIV);
	if(status==HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::setExtFrameSync(uint8_t d)
{
	/*
	 *  Register CONFIG [0x1A]
	 *  Bits: [5:3] EXT_SYNC_SET
	 * */
	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0xC7;
	register_value = register_value | (d<<3);

	status = status | writeSingleByte(register_value, MPU6050_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::setLowPassFilter(uint8_t d)
{
	/*
	 *  Register CONFIG [0x1A]
	 *  Bits: [2:0] DLPF_CFG
	 * */
	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0xF8;
	register_value = register_value | d;

	status = status | writeSingleByte(register_value, MPU6050_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::setGyroscopeConfig(uint8_t d)
{
	/*
	 *  Register GYRO_CONFIG [0x1B]
	 *  Bit 7: XG_ST
	 *  Bit 6: YG_ST
	 *  Bit 5: ZG_ST
	 *  Bits [4:3]: FS_SEL
	 *
	 * */
	/* This is for a complete register write */

	HAL_StatusTypeDef status = writeSingleByte(d, MPU6050_GYRO_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::selfTestXGAxis()
{
	/*
	 *  Register GYRO_CONFIG [0x1B]
	 *  Bit 7: XG_ST
	 *  Bit 6: YG_ST
	 *  Bit 5: ZG_ST
	 *  Bits [4:3]: FS_SEL
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_GYRO_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0x7F;
	register_value = register_value | 0x80;

	status = status | writeSingleByte(register_value, MPU6050_GYRO_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::selfTestYGAxis()
{
	/*
	 *  Register GYRO_CONFIG [0x1B]
	 *  Bit 7: XG_ST
	 *  Bit 6: YG_ST
	 *  Bit 5: ZG_ST
	 *  Bits [4:3]: FS_SEL
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_GYRO_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0xBF;
	register_value = register_value | 0x40;

	status = status | writeSingleByte(register_value, MPU6050_GYRO_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::selfTestZGAxis()
{
	/*
	 *  Register GYRO_CONFIG [0x1B]
	 *  Bit 7: XG_ST
	 *  Bit 6: YG_ST
	 *  Bit 5: ZG_ST
	 *  Bits [4:3]: FS_SEL
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_GYRO_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0xDF;
	register_value = register_value | 0x20;

	status = status | writeSingleByte(register_value, MPU6050_GYRO_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::setGyroscopeScale(uint8_t d)
{
	/*
	 *  Register GYRO_CONFIG [0x1B]
	 *  Bit 7: XG_ST
	 *  Bit 6: YG_ST
	 *  Bit 5: ZG_ST
	 *  Bits [4:3]: FS_SEL
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_GYRO_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0xE7;
	register_value = register_value | d<3;

	status = status | writeSingleByte(register_value, MPU6050_GYRO_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}


int MPU6050::setAccelerometerConfig(uint8_t d)
{
	/*
	 *  Register ACCEL_CONFIG [0x1C]
	 *  Bit 7: XA_ST
	 *  Bit 6: YA_ST
	 *  Bit 5: ZA_ST
	 *  Bits [4:3]: AFS_SEL
	 *
	 * */

	/* This is for a complete register write */

	HAL_StatusTypeDef status = writeSingleByte(d, MPU6050_ACCEL_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::selfTestXAAxis()
{
	/*
	 *  Register ACCEL_CONFIG [0x1C]
	 *  Bit 7: XA_ST
	 *  Bit 6: YA_ST
	 *  Bit 5: ZA_ST
	 *  Bits [4:3]: AFS_SEL
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_ACCEL_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0x7F;
	register_value = register_value | 0x80;

	status = status | writeSingleByte(register_value, MPU6050_ACCEL_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::selfTestYAAxis()
{
	/*
	 *  Register ACCEL_CONFIG [0x1C]
	 *  Bit 7: XA_ST
	 *  Bit 6: YA_ST
	 *  Bit 5: ZA_ST
	 *  Bits [4:3]: AFS_SEL
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_ACCEL_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0xBF;
	register_value = register_value | 0x40;

	status = status | writeSingleByte(register_value, MPU6050_ACCEL_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::selfTestZAAxis()
{
	/*
	 *  Register ACCEL_CONFIG [0x1C]
	 *  Bit 7: XA_ST
	 *  Bit 6: YA_ST
	 *  Bit 5: ZA_ST
	 *  Bits [4:3]: AFS_SEL
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_ACCEL_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0xDF;
	register_value = register_value | 0x20;

	status = status | writeSingleByte(register_value, MPU6050_ACCEL_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::setAccelerometerScale(uint8_t d)
{
	/*
	 *  Register ACCEL_CONFIG [0x1C]
	 *  Bit 7: XA_ST
	 *  Bit 6: YA_ST
	 *  Bit 5: ZA_ST
	 *  Bits [4:3]: AFS_SEL
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_ACCEL_CONFIG);

	/*
	 * 	I assume that the data that you send has this format in 8 bits value:
	 * 	0b00000xxx
	 * */

	register_value = register_value & 0xE7;
	register_value = register_value | d<3;

	status = status | writeSingleByte(register_value, MPU6050_ACCEL_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}



int  MPU6050::writeFifoReg(uint8_t d)
{
	/*
	 *  Register FIFO_EN [0x23]
	 *  Bit 7: TEMP_ FIFO_EN
	 *  Bit 6: XG_ FIFO_EN
	 *  Bit 5: YG_ FIFO_EN
	 *  Bit 4: ZG_ FIFO_EN
	 *  Bit 3: ACCEL _FIFO_EN
	 *  Bit 2: SLV2 _FIFO_EN
	 *  Bit 1: SLV1 _FIFO_EN
	 *  Bit 0: SLV0 _FIFO_EN
	 *
	 * */

	/* This is for a complete register write */

	HAL_StatusTypeDef status = writeSingleByte(d, MPU6050_FIFO_EN);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::enableTemperatureFifo()
{
	/*
	 *  Register FIFO_EN [0x23]
	 *  Bit 7: TEMP_ FIFO_EN
	 *  Bit 6: XG_ FIFO_EN
	 *  Bit 5: YG_ FIFO_EN
	 *  Bit 4: ZG_ FIFO_EN
	 *  Bit 3: ACCEL _FIFO_EN
	 *  Bit 2: SLV2 _FIFO_EN
	 *  Bit 1: SLV1 _FIFO_EN
	 *  Bit 0: SLV0 _FIFO_EN
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_FIFO_EN);

	register_value = register_value & 0x7F;
	register_value = register_value | 0x80;

	status = status | writeSingleByte(register_value, MPU6050_FIFO_EN);

	if(status == HAL_OK)
		return 1;
	else
		return 0;

}


int MPU6050::enableXGyroscopeFifo()
{
	/*
	 *  Register FIFO_EN [0x23]
	 *  Bit 7: TEMP_ FIFO_EN
	 *  Bit 6: XG_ FIFO_EN
	 *  Bit 5: YG_ FIFO_EN
	 *  Bit 4: ZG_ FIFO_EN
	 *  Bit 3: ACCEL _FIFO_EN
	 *  Bit 2: SLV2 _FIFO_EN
	 *  Bit 1: SLV1 _FIFO_EN
	 *  Bit 0: SLV0 _FIFO_EN
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_FIFO_EN);

	register_value = register_value & 0xBF;
	register_value = register_value | 0x40;

	status = status | writeSingleByte(register_value, MPU6050_FIFO_EN);

	if(status == HAL_OK)
		return 1;
	else
		return 0;

}

int MPU6050::enableYGyroscopeFifo()
{
	/*
	 *  Register FIFO_EN [0x23]
	 *  Bit 7: TEMP_ FIFO_EN
	 *  Bit 6: XG_ FIFO_EN
	 *  Bit 5: YG_ FIFO_EN
	 *  Bit 4: ZG_ FIFO_EN
	 *  Bit 3: ACCEL _FIFO_EN
	 *  Bit 2: SLV2 _FIFO_EN
	 *  Bit 1: SLV1 _FIFO_EN
	 *  Bit 0: SLV0 _FIFO_EN
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_FIFO_EN);

	register_value = register_value & 0xDF;
	register_value = register_value | 0x20;

	status = status | writeSingleByte(register_value, MPU6050_FIFO_EN);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::enableZGyroscopeFifo()
{
	/*
	 *  Register FIFO_EN [0x23]
	 *  Bit 7: TEMP_ FIFO_EN
	 *  Bit 6: XG_ FIFO_EN
	 *  Bit 5: YG_ FIFO_EN
	 *  Bit 4: ZG_ FIFO_EN
	 *  Bit 3: ACCEL _FIFO_EN
	 *  Bit 2: SLV2 _FIFO_EN
	 *  Bit 1: SLV1 _FIFO_EN
	 *  Bit 0: SLV0 _FIFO_EN
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_FIFO_EN);

	register_value = register_value & 0x7F;
	register_value = register_value | 0x80;

	status = status | writeSingleByte(register_value, MPU6050_FIFO_EN);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

/*
 * Pendiente agregar funciones para sensor externo
 *
 * */

/*
 * Pending add functions for:
 * 	I2C_MST_CTRL
 * 	I2C_SLV0_ADDR
 * 	 I2C_SLV0_REG
 * 	 I2C_SLV0_CTRL
 * 	 I2C_SLV1_ADDR
 * 	 I2C_SLV1_REG
 * 	 I2C_SLV1_CTRL
 * 	 I2C_SLV2_ADDR
 * 	 I2C_SLV2_REG
 * 	 I2C_SLV2_CTRL
 * 	 I2C_SLV3_ADDR
 * 	 I2C_SLV3_REG
 * 	 I2C_SLV3_CTRL
 * 	 I2C_SLV4_ADDR
 * 	 I2C_SLV4_REG
 * 	 I2C_SLV4_DO
 * 	 I2C_SLV4_CTRL
 * 	 I2C_SLV4_DI
 * 	 I2C_MST_STATUS
 * 	 INT_PIN_CFG
 * 	 INT_ENABLE
 * 	 INT_STATUS
 * */

int16_t MPU6050::getAccelX()
{
	uint8_t buffer[2];
	int16_t tmp;
	HAL_StatusTypeDef status =readSingleByte(&buffer[0], MPU6050_ACCEL_XOUT_H);
	status = status | readSingleByte(&buffer[1], MPU6050_ACCEL_XOUT_L);
	tmp=(uint16_t)buffer;
	tmp-=1;
	tmp = ~tmp;

	if(status == HAL_OK)
		return tmp;
	else
		return 0;
}

int16_t MPU6050::getAccelY()
{
	uint8_t buffer[2];
	int16_t tmp;
	HAL_StatusTypeDef status =readSingleByte(&buffer[0], MPU6050_ACCEL_YOUT_H);
	status = status | readSingleByte(&buffer[1], MPU6050_ACCEL_YOUT_L);
	tmp=(uint16_t)buffer;
	tmp-=1;
	tmp = ~tmp;

	if(status == HAL_OK)
		return tmp;
	else
		return 0;
}

int16_t MPU6050::getAccelZ()
{
	uint8_t buffer[2];
	int16_t tmp;
	HAL_StatusTypeDef status =readSingleByte(&buffer[0], MPU6050_ACCEL_ZOUT_H);
	status = status | readSingleByte(&buffer[1], MPU6050_ACCEL_ZOUT_L);
	tmp=(uint16_t)buffer;
	tmp-=1;
	tmp = ~tmp;

	if(status == HAL_OK)
		return tmp;
	else
		return 0;
}

float MPU6050::getTemperature()
{
	uint8_t buffer[2];
	int16_t tmp;
	float result;
	HAL_StatusTypeDef status =readSingleByte(&buffer[0], MPU6050_TEMP_OUT_H);
	status = status | readSingleByte(&buffer[1], MPU6050_TEMP_OUT_L);
	tmp=(uint16_t)buffer;
	result=(tmp/340.0)+36.53;

	if(status == HAL_OK)
		return result;
	else
		return 0;

}


int16_t MPU6050::getGyroX()
{
	uint8_t buffer[2];
	int16_t tmp;
	HAL_StatusTypeDef status =readSingleByte(&buffer[0], MPU6050_GYRO_XOUT_H);
	status = status | readSingleByte(&buffer[1], MPU6050_GYRO_XOUT_L);
	tmp=(uint16_t)buffer;
	tmp-=1;
	tmp = ~tmp;

	if(status == HAL_OK)
		return tmp;
	else
		return 0;
}

int16_t MPU6050::getGyroY()
{
	uint8_t buffer[2];
	int16_t tmp;
	HAL_StatusTypeDef status =readSingleByte(&buffer[0], MPU6050_GYRO_YOUT_H);
	status = status | readSingleByte(&buffer[1], MPU6050_GYRO_YOUT_L);
	tmp=(uint16_t)buffer;
	tmp-=1;
	tmp = ~tmp;

	if(status == HAL_OK)
		return tmp;
	else
		return 0;
}

int16_t MPU6050::getGyroZ()
{
	uint8_t buffer[2];
	int16_t tmp;
	HAL_StatusTypeDef status =readSingleByte(&buffer[0], MPU6050_GYRO_ZOUT_H);
	status = status | readSingleByte(&buffer[1], MPU6050_GYRO_ZOUT_L);
	tmp=(uint16_t)buffer;
	tmp-=1;
	tmp = ~tmp;

	if(status == HAL_OK)
		return tmp;
	else
		return 0;
}

/*
 * 	Pendiente:
 * 	EXT_SENS_DATA_00[7:0]
	EXT_SENS_DATA_01[7:0]
	EXT_SENS_DATA_02[7:0]
	EXT_SENS_DATA_03[7:0]
	EXT_SENS_DATA_04[7:0]
	EXT_SENS_DATA_05[7:0]
	EXT_SENS_DATA_06[7:0]
	EXT_SENS_DATA_07[7:0]
	EXT_SENS_DATA_08[7:0]
	EXT_SENS_DATA_09[7:0]
	EXT_SENS_DATA_10[7:0]
	EXT_SENS_DATA_11[7:0]
	EXT_SENS_DATA_12[7:0]
	EXT_SENS_DATA_13[7:0]
	EXT_SENS_DATA_14[7:0]
	EXT_SENS_DATA_15[7:0]
	EXT_SENS_DATA_16[7:0]
	EXT_SENS_DATA_17[7:0]
	EXT_SENS_DATA_18[7:0]
	EXT_SENS_DATA_19[7:0]
	EXT_SENS_DATA_20[7:0]
	EXT_SENS_DATA_21[7:0]
	EXT_SENS_DATA_22[7:0]
	EXT_SENS_DATA_23[7:0]
 * 	I2C_SLV0_DO
 * 	I2C_SLV1_DO
 * 	I2C_SLV2_DO
 * 	I2C_SLV3_DO
 * 	I2C_MST_DELAY_CTRL
 *
 *
 *
 * */

int MPU6050::resetGyroscopeADC()
{
	uint8_t register_value=0x04;
	HAL_StatusTypeDef status =  writeSingleByte(register_value, MPU6050_SIGNAL_PATH_RESET);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::resetAccelerometerADC()
{
	uint8_t register_value=0x02;
	HAL_StatusTypeDef status =  writeSingleByte(register_value, MPU6050_SIGNAL_PATH_RESET);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::resetTemperatureADC()
{
	uint8_t register_value=0x01;
	HAL_StatusTypeDef status =  writeSingleByte(register_value, MPU6050_SIGNAL_PATH_RESET);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::enableFIFO()
{
	/*
	 *  Register USER_CTRL [0x6A]
	 *  Bit 7: NA
	 *  Bit 6: FIFO_EN
	 *  Bit 5: I2C_MST _EN
	 *  Bit 4: I2C_IF _DIS
	 *  Bit 3: NA
	 *  Bit 2: FIFO _RESET
	 *  Bit 1: I2C_MST _RESET
	 *  Bit 0: SIG_COND _RESET
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_USER_CTRL);

	register_value = register_value & 0xBF;
	register_value = register_value | 0x40;

	status = status | writeSingleByte(register_value, MPU6050_USER_CTRL);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

/*
 * 	Pendiente escribir la opción de master i2c 2C_MST_EN
 * 	Pendiente I2C_IF_DIS
 * */


int MPU6050::resetFIFO()
{
	/*
	 *  Register USER_CTRL [0x6A]
	 *  Bit 7: NA
	 *  Bit 6: FIFO_EN
	 *  Bit 5: I2C_MST _EN
	 *  Bit 4: I2C_IF _DIS
	 *  Bit 3: NA
	 *  Bit 2: FIFO _RESET
	 *  Bit 1: I2C_MST _RESET
	 *  Bit 0: SIG_COND _RESET
	 *
	 * */

	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_USER_CTRL);

	register_value = register_value & 0xFB;
	register_value = register_value | 0x04;

	status = status | writeSingleByte(register_value, MPU6050_USER_CTRL);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

/*
 * 	Pendiente 2C_MST_RESET
 * 	Pendiente SIG_COND_RESET
 * */
int MPU6050::resetDevice()
{
	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_PWR_MGMT_1);

	register_value = register_value | 0x80;
	status = status | writeSingleByte(register_value, MPU6050_PWR_MGMT_1);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::goSleep()
{
	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_PWR_MGMT_1);

	register_value = register_value | 0x40;
	status = status | writeSingleByte(register_value, MPU6050_PWR_MGMT_1);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::disableTempSensor()
{
	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_PWR_MGMT_1);

	register_value = register_value | 0x08;
	status = status | writeSingleByte(register_value, MPU6050_PWR_MGMT_1);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::enableTempSensor()
{
	uint8_t register_value=0;
	HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_PWR_MGMT_1);

	register_value = register_value & 0xF7;
	status = status | writeSingleByte(register_value, MPU6050_PWR_MGMT_1);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}

int MPU6050::setClockSource(uint8_t d)
{
	if(d > 0x07 | d==0x06)
		return 0;
	else
	{
		uint8_t register_value=0;
		HAL_StatusTypeDef status = readSingleByte(&register_value,MPU6050_PWR_MGMT_1);

		register_value = register_value & 0xF8;
		register_value = register_value | d;

		status = status | writeSingleByte(register_value, MPU6050_PWR_MGMT_1);

		if(status == HAL_OK)
			return 1;
		else
			return 0;

	}
}

int MPU6050::getFIFOCount()
{
	uint8_t buffer[2];
	uint16_t tmp;
	HAL_StatusTypeDef status =readSingleByte(&buffer[0], MPU6050_FIFO_COUNTH);
	status = status | readSingleByte(&buffer[1], MPU6050_FIFO_COUNTL);
	tmp=(uint16_t)buffer;



	if(status == HAL_OK)
		return tmp;
	else
		return 0;
}

/*
 * Pendiente FIFO_R_W
 *
 * */



/*
 * 	Pendiente Power Management 2
 * */






HAL_StatusTypeDef MPU6050::writeSingleByte(uint8_t d, uint8_t reg)
{
	uint8_t buffer[2];
	buffer[0] = reg;
	buffer[1] = d;
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(_dev,MPU6050_WRITE_ADD,buffer,2,10);
	return status;

}/*
HAL_StatusTypeDef MPU6050::writeWords(uint8_t *buffer,uint8_t len, uint8_t reg)
{

}*/

HAL_StatusTypeDef MPU6050::readSingleByte(uint8_t *d, uint8_t reg)
{
	uint8_t tmp=0,r=reg;
	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(_dev,MPU6050_WRITE_ADD,&r,1,10);
	status = status | HAL_I2C_Master_Receive(_dev,MPU6050_READ_ADD,&tmp,1,10);
	*d=tmp;
	return status;

}
/*
HAL_StatusTypeDef MPU6050::readWords(uint8_t *buffer,uint8_t len, uint8_t reg)
{

}*/
