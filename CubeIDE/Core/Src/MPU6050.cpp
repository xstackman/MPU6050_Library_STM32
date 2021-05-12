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
	uint8_t tmp=0,reg=MPU6050_WHO_AM_I;
	uint8_t read_add=0xD0;
	uint8_t write_add=0xD1;

	if(_dev==NULL)
		return 0;
	else
	{
		HAL_I2C_Master_Transmit(_dev,MPU6050_WRITE_ADD,&reg,1,10);
		HAL_I2C_Master_Receive(_dev,MPU6050_READ_ADD,&tmp,1,10);
		if(tmp==0x68)
			return 1;
		else
			return 0;
	}
}

