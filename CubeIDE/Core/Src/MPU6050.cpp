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

void  MPU6050::setConfigReg(uint8_t val)
{
	/* Bits: X | X | EXT_SYNC_SET[2:0] | DLPF_CFG[2:0] */
	uint8_t pm1=0x00;


	uint8_t buffer[2];
	buffer[0]=MPU6050_PWR_MGMT_1;
	buffer[1]=0x00;
	HAL_I2C_Master_Transmit(_dev,MPU6050_WRITE_ADD,buffer,2,10);


	buffer[0]=MPU6050_CONFIG;
	buffer[1]=val;
	HAL_I2C_Master_Transmit(_dev,MPU6050_WRITE_ADD,buffer,2,10);

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

	register_value = register_value & 0x07;
	register_value = register_value | (d<<3);

	status = status | writeSingleByte(register_value, MPU6050_CONFIG);

	if(status == HAL_OK)
		return 1;
	else
		return 0;
}


void  MPU6050::setFifoEnable(uint8_t val)
{
	uint8_t buffer[2];
	buffer[0]=MPU6050_FIFO_EN;
	buffer[1]=val;
	HAL_I2C_Master_Transmit(_dev,MPU6050_WRITE_ADD,buffer,2,10);
}
float MPU6050::getTemperature()
{
	uint8_t temp_reg[2]={MPU6050_TEMP_OUT_H,MPU6050_TEMP_OUT_L};
	uint8_t temp_val[2];


	HAL_I2C_Master_Transmit(_dev,MPU6050_TEMP_OUT_H,&temp_reg[0],1,10);
	HAL_I2C_Master_Receive(_dev,MPU6050_READ_ADD,&temp_val[0],1,10);
	HAL_Delay(10);
	HAL_I2C_Master_Transmit(_dev,MPU6050_TEMP_OUT_H,&temp_reg[1],1,10);
	HAL_I2C_Master_Receive(_dev,MPU6050_READ_ADD,&temp_val[1],1,10);

	float temp= ((uint16_t)*temp_val/340.0)+36.53;
	return temp;

}
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
