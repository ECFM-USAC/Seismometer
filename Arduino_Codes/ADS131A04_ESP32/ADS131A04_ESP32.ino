//#include <SPI.h>
#include "ADS131A04_driver.h"

uint8_t datos[10][18];
#define Select 22
#define push_1 34
uint8_t Activated;
uint32_t ADC_DATA;
int contador;
int x = 0;
int push1;

void setup() {
  Serial.begin(9600);
  
  pinMode (slavePin, OUTPUT);
  //pinMode (MOSI, OUTPUT);
  pinMode (2, OUTPUT);
  pinMode (Select, INPUT);
  pinMode (push_1, INPUT);
  SPI.begin();
  digitalWrite(slavePin, HIGH);
  ADC_CONFIGURATION_WAKEUP();
  
//    Serial.print("NO LECTURA");  // prints a label
//    Serial.print("\t");         // prints a tab
//
//    Serial.print("LECTURA");
//    Serial.print("\t");
//    Serial.println();
}

void loop() {
//  push1=digitalRead(push_1);
//  if(push1){
//    ADC_CONFIGURATION_WAKEUP();
//  }
  

  //ADC_DATA = ReadADC_4();
  
  Activated = digitalRead(Select);
  while(Activated){
    
    Serial.print(x);
    Serial.print("\t\t");
    ADC_DATA = ReadADC_4();
    Serial.print(ADC_DATA, BIN);
    Serial.print("\t"); 
    Serial.println();
    x = x+1;
    if(x==1001){
      x=0;
    };
    Activated = digitalRead(Select);

//      
//    for (int x = 0; x < 50; x++) {
//      ADC_DATA = ReadADC_4();
//      Serial.print(x);
//      Serial.print("\t\t");
//
//      Serial.print(ADC_DATA, BIN);
//      Serial.print("\t"); 
//      Serial.println();
//      Activated = digitalRead(Select);
//      }
    
    }  
  
}











void ADC_CONFIGURATION_WAKEUP(void){
  //Wait for READY Command
  //Check STAT_S F_STARTUP
  
  SetADC(UNLOCK);

  //By default, initialize in Dynamic-frame mode
  
  //Select the external 16MHz Clock
  RegisterWrite(CLK1, CLKSRC, EXT_16M);
  //Divider to generate ICLK = 8MHz
  RegisterWrite(CLK1, CLK_DIV, CLK_DIV_02);

  //Disable CRC
  RegisterWrite(D_SYS_CFG, CRC_EN, CRC_N);
  
  //Divider to generate FMOD = 4MHz
  RegisterWrite(CLK2, ICLK_DIV, ICLK_DIV_02);
  //OSR to get FDATA = 5kHz
  RegisterWrite(CLK2, OSR, OSR_0800);  // Para Effective Bits dado OSR --> LUP con define
  //By default, Internal Reference is enabled.
  //Select Internal Reference to 2.442V
  RegisterWrite(A_SYS_CFG, VREF_4V, REFP_2_4);
  //Select the High-Resolution mode
  RegisterWrite(A_SYS_CFG, HRM, HRM_HIGH);
  //Disable Watchdog Timer
  RegisterWrite(D_SYS_CFG, WDT_EN, WDT_N);
  //Timethat the device asserts Hi-Z on DOUT after the LSB is shifted out
  RegisterWrite(D_SYS_CFG, HIZDLY, HIZDLY_06);

  //Digital Gain of the ADC output
  RegisterWrite(ADC1, GAIN, GAIN_01);
  RegisterWrite(ADC2, GAIN, GAIN_01);
  RegisterWrite(ADC3, GAIN, GAIN_01);
  RegisterWrite(ADC4, GAIN, GAIN_01);
  //All ADC channels powered up
  RegisterWrite(ADC_ENA, ENA, ENA_Y);
  
  //Start conversions
  SetADC(WAKEUP);
  digitalWrite(2,HIGH);
  delay(2000);
  digitalWrite(2,LOW);
  }
