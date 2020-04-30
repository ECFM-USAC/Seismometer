//Libreria para el manejo del ADC - ADS131A04


#ifndef ADS131A04_driver_H_
#define ADS131A04_driver_H_

//**************************************************
//
//	CONFIGURACION ARDUINO
//
//**************************************************
#include <SPI.h>

//#define CLOCK 1000 //1MHz
//#define CLOCK 1000000 //1MHz
#define CLOCK 800000 //1MHz
SPISettings settings(CLOCK, MSBFIRST, SPI_MODE1);

const int slavePin = 5;

//**************************************************
//
// 	BASIC CONFIGURATION - SYSTEM COMMANDS
//
//**************************************************
//#define NULL		0x00000000 //Null Command
#define RESET     0x00110000 //Software reset
#define STANDBY		0x00220000 //Enter low-power standby mode
#define WAKEUP		0x00330000 //Wake-up from standby mode
#define LOCK		  0x05550000 //Interface Lock, except NULL, RREGS and UNLOCK
#define UNLOCK		0x06550000 //Unlock Interface 

//**************************************************
//
// 	REGISTERS ADDRESSES
//
//**************************************************
#define ID_MSB		0x00
#define ID_LSB		0x01
#define STAT_1		0x02
#define STAT_P		0x03
#define STAT_N		0x04
#define STAT_S		0x05
#define ERROR_CNT	0x06
#define STAT_M2		0x07
#define A_SYS_CFG	0x0B
#define D_SYS_CFG	0x0C
#define CLK1		  0x0D
#define CLK2		  0x0E
#define ADC_ENA		0x0F
#define ADC1		  0x11
#define ADC2		  0x12
#define ADC3		  0x13
#define ADC4		  0x14

//**************************************************
//
// 	POSICION ENTRE REGISTROS
//
//**************************************************
//----------A_SYS_CFG-------
#define VNCPEN		0x80
#define HRM		    0x40
#define VREF_4V		0x10
#define INT_REFEN	0x08
#define COMP_TH		0x07
//----------D_SYS_CFG-------
#define WDT_EN		0x80
#define CRC_MODE	0x40
#define DNDLY		  0x30
#define HIZDLY		0x0C
#define FIXED		  0x02
#define CRC_EN		0x01
//----------CLK1------------
#define CLKSRC		0x80
#define CLK_DIV		0x0E
//----------CLK2------------
#define ICLK_DIV	0xE0
#define OSR		    0x0F
//----------ADC_ENA---------
#define ENA		    0x0F
//----------ADCX------------
#define GAIN		  0x07

//**************************************************
//
//   CONFIGURACION REGISTROS
//
//**************************************************
//-----------A_SYS_CFG
#define VNCP0     0x00
#define VNCP1     0x80
#define HRM_LOW   0x00
#define HRM_HIGH  0x40
#define REFP_2_4  0x00
#define REFP_4_0  0x10
#define EXT_REF   0x00
#define INT_REF   0x08
#define THR_95_0  0x00
#define THR_92_5  0x01
#define THR_90_0  0x02
#define THR_87_5  0x03
#define THR_85_0  0x04
#define THR_80_0  0x05
#define THR_75_0  0x06
#define THR_70_0  0x07
//-----------D_SYS_CFG
#define WDT_N     0x00
#define WDT_Y     0x80
#define MODE_0    0x00
#define MODE_1    0x40
#define DNDLY_06  0x00
#define DNDLY_08  0x10
#define DNDLY_10  0x20
#define DNDLY_12  0x30
#define HIZDLY_06 0x00
#define HIZDLY_08 0x10
#define HIZDLY_10 0x20
#define HIZDLY_12 0x30
#define FIXED_N   0x00 
#define FIXED_Y   0x02
#define CRC_N     0x00
#define CRC_Y     0x01
//------------------CLK1
#define EXT_16M     0x00
#define SCLK_SL     0x80
#define CLK_DIV_02  0x02
#define CLK_DIV_04  0x04
#define CLK_DIV_06  0x06
#define CLK_DIV_08  0x08
#define CLK_DIV_10  0x0A
#define CLK_DIV_12  0x0C
#define CLK_DIV_14  0x0E
//------------------CLK2
#define ICLK_DIV_02 0x20
#define ICLK_DIV_04 0x40
#define ICLK_DIV_06 0x60
#define ICLK_DIV_08 0x80
#define ICLK_DIV_10 0xA0
#define ICLK_DIV_12 0xC0
#define ICLK_DIV_14 0xE0
#define OSR_4096    0x00
#define OSR_2048    0x01
#define OSR_1024    0x02
#define OSR_0800    0x03
#define OSR_0768    0x04
#define OSR_0512    0x05
#define OSR_0400    0x06
#define OSR_0384    0x07
#define OSR_0256    0x08
#define OSR_0200    0x09
#define OSR_0192    0x0A
#define OSR_0128    0x0B
#define OSR_0096    0x0C
#define OSR_0064    0x0D
#define OSR_0048    0x0E
#define OSR_0032    0x0F
//-------------ADC_ENA
#define ENA_N     0x00
#define ENA_Y     0x0F
//----------------ADCX
#define GAIN_01   0x00
#define GAIN_02   0x01
#define GAIN_04   0x02
#define GAIN_08   0x03
#define GAIN_16   0x04

//**************************************************
//
// 	BASIC CONFIGURATION
//
//**************************************************
void SetADC(uint32_t command){
	uint32_t data_send;
	uint32_t data_received;
	SPI.beginTransaction(settings);
	digitalWrite(slavePin, LOW);
	SPI.transfer32(command);
	digitalWrite (slavePin, HIGH);

	digitalWrite(slavePin, LOW);
	data_received = SPI.transfer32(NULL);
	digitalWrite (slavePin, HIGH);
	SPI.endTransaction();
};

//**************************************************
//
// 	READ A SINGLE REGISTER
//
//**************************************************
uint8_t RegisterRead(uint8_t registro){ //Devuelve el valor del registro
	uint32_t data_received;
	uint32_t data_send;
  uint32_t registro_t;
  uint8_t data_out;
	
	registro = 0x20|registro;	// 0x20 = 0b0010 0000
	registro_t = (uint32_t)registro;
	registro_t = registro_t << 24;
	data_send = registro_t & 0xFF000000; 

	SPI.beginTransaction(settings);
	digitalWrite(slavePin, LOW);
	SPI.transfer32(data_send);
	digitalWrite (slavePin, HIGH);

  //delay(0.001);

	digitalWrite(slavePin, LOW);
	data_received = SPI.transfer32(NULL);
	digitalWrite (slavePin, HIGH);
	SPI.endTransaction();

	data_received = (data_received >> 16) & 0x000000FF;
  data_out = (uint8_t)data_received;
	return data_out;
};

//**************************************************
//
// 	WRITE TO A SINGLE REGISTER
//
//**************************************************
void RegisterWrite(uint8_t registro, uint8_t offset, uint8_t data_send){
  uint8_t data_actual = RegisterRead(registro);
  //uint8_t data_actual = 0xFF;
  uint32_t data_send_t;
  uint32_t registro_t;

	data_send = (data_actual & (~offset) ) | data_send;
	
	registro = registro | 0x40;
	registro_t =(uint32_t)registro;
	data_send_t=(uint32_t)data_send;

	data_send_t = ((registro_t << 24) & 0xFF000000) | ((data_send_t << 16) & 0x00FF0000);
  //data_send_t = 0xFFFFFFFF;

	SPI.beginTransaction(settings);
	digitalWrite(slavePin, LOW);
	SPI.transfer32(data_send_t);
	digitalWrite (slavePin, HIGH);

	digitalWrite(slavePin, LOW);
	SPI.transfer32(NULL);
	digitalWrite (slavePin, HIGH);
	SPI.endTransaction();
};

//**************************************************
//
// 	READ ADC VALUES
//
//**************************************************
uint32_t ReadADC_4(){
	uint32_t data_received;
	SPI.beginTransaction(settings);
	digitalWrite(slavePin, LOW);
	SPI.transfer32(NULL);
	SPI.transfer32(NULL);
	SPI.transfer32(NULL);
	SPI.transfer32(NULL);
	data_received = SPI.transfer32(0x00000000);
	digitalWrite (slavePin, HIGH);
	SPI.endTransaction();
  data_received = (data_received >> 8) & 0x00FFFFFF;
	return data_received;
};

#endif
