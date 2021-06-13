/******************************************************************************
*
* MRF101 Amplifier by AD5GH
*
* ARDUINO MEGA DISPLAY & CONTROL BOARD SOFTWARE
* DS18B20+ ONE WIRE TEMPERATURE SENSOR FUNCTION ROUTINES
*
* Distributed under the terms of the MIT License:
* http://www.opensource.org/licenses/mit-license
*
* See http://www.ad5gh.com for further details
*
* VERSION 1.4.0
* June 4, 2021
*
******************************************************************************/

#include <OneWire.h>
#include <Mrf_DS18B20.h>

Mrf_DS18B20::Mrf_DS18B20(void)
{

}

float Mrf_DS18B20::getTemp(int DS18S20_Pin)                       // returns the temperature from one DS18B20 in DEG C
{
  OneWire ds(DS18S20_Pin);                                        // set digital pin
  
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr))
  {
    ds.reset_search();
    if( !ds.search(addr))                                         // try a second time if first try fails
    {
      ds.reset_search();
      return -10;
    }
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("Invalid CRC");
      return -20;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device not recognized");
      return -30;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);                                             // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);                                               // read Scratchpad

  
  for (int i = 0; i < 9; i++) {                                 // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB);                          // using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return (TemperatureSum);                                      // return temperature in degrees C
  
}
