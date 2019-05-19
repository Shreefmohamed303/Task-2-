/********************************************************************************
 * Module : NODEMCU
 *
 * File Name : task2
 *
 * Description : - using The internal memory of NODEMCU  
 *               -to create database for analog sensor readings 
 * 
 * Author : Shreef Mohamed
 *
 * Created on: may 19, 2019
 *
 ********************************************************************************/

// include library to read and write from flash memory
#include <EEPROM.h>

// define the number of bytes you want to access
#define EEPROM_SIZE 512
#define ANALOG_PIN A0

int safeWrite(char sensor_readings, int address); 

/* 
i used char because the EEPROM is 512 bytes
so i have from 0 to 511 address 
every block could only contain 8 bits 
*/
char sensor_readings ; 
int address=0 ; 
int write_counter =0 ; 


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
EEPROM.begin(EEPROM_SIZE);
}

void loop() {
  // put your main code here, to run repeatedly:

  // take the readings from the sensor 
 sensor_readings= analogRead(ANALOG_PIN) ; 
 
 // i used this condition to reduce number of writes in different addresses
 // as by using this condition i will store reading in the next address after milliseconds 
if(write_counter>1000)
{
  write_counter=0;
  address +=1 ; 
}

write_counter++ ; 
 // there are only 512 bytes of EEPROM, from 0 to 511, so if we're
 // on address 512, wrap around to address 0
if(address==512) 
{
  address = 0 ; 
}

safeWrite(sensor_readings,address) ; 


 
}


 /*******************************************************************************
  *                     FUNCTIONS DEFINATION                                     *
  *******************************************************************************/
  
// Function to make the writing to EEPROM safe
//by not to dupliacate the same values of the sensor 
int safeWrite(char sensor_readings, int address) {
    if(EEPROM.read(address) != sensor_readings) {
        EEPROM.write(address, sensor_readings);
        EEPROM.commit();
    }
}
