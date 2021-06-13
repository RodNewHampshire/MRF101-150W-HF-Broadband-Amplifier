/******************************************************************************
*
* MRF101 Amplifier by AD5GH
*
* ARDUINO MEGA DISPLAY & CONTROL BOARD SOFTWARE
* LEFT LCD FUNCTION ROUTINES
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

#include <Adafruit_LiquidCrystal.h>
#include <Adafruit_ADS1015.h>
#include <arduino.h>
#include <Mrf_L_LCD.h>
#include <Mrf_R_LCD.h>
#include <Mrf_DS18B20.h>

#define tempASensor 9
#define tempBSensor 10

#define   numADCSamples 10

Adafruit_ADS1115        _adc;

Adafruit_LiquidCrystal  MrfLCD_L(0);

Mrf_R_LCD               MrfRightLCD;
Mrf_DS18B20             tempSensor;

int32_t   currentTicks;
int32_t   sumCurrentTicks = 0;

float     mrfAmps = 0;
float     mrfATemp = 0;
float     mrfBTemp = 0;

int8_t    adcReadPeriod = 0;

int32_t   zeroCurrentOffset;            

char Temperature_A[21]      = {'T','e','m','p','.',' ','A',':',' ',' ',' ',' ',' ','C',' ',' ',' ',' ',' ',' ','\0'};
char Temperature_B[21]      = {'T','e','m','p','.',' ','B',':',' ',' ',' ',' ',' ','C',' ',' ',' ',' ',' ',' ','\0'};

const char Temp_30[21] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_35[21] = {0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_40[21] = {0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_45[21] = {0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_50[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_55[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_60[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_65[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_70[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_75[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_80[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_85[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_90[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_95[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_100[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_105[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_110[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Temp_115[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, '\0'};
const char Temp_120[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, '\0'};
const char Temp_125[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, '\0'};
const char Temp_130[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, '\0'};

Mrf_L_LCD::Mrf_L_LCD(void)
{

}

void Mrf_L_LCD::begin(void)
{
	MrfLCD_L.begin(20, 4);
  _adc.begin();
  initializeACS723();
}

void Mrf_L_LCD::clear(void)
{
	MrfLCD_L.clear();
}

void Mrf_L_LCD::splash(void)
{
 	MrfLCD_L.print(F("       AD5GH        "));                // Mrf LCD splash
  MrfLCD_L.setCursor(0, 1);
  MrfLCD_L.print(F("  MRF101 150 WATT  "));
  MrfLCD_L.setCursor(0, 2);
  MrfLCD_L.print(F("  HF AMATEUR BAND  "));
  MrfLCD_L.setCursor(0, 3);
  MrfLCD_L.print(F("     AMPLIFIER     "));
}

void Mrf_L_LCD::initializeDisplay(void)
{
  MrfLCD_L.clear();
  MrfLCD_L.setCursor(0, 0);
  MrfLCD_L.print(Temperature_A);
  MrfLCD_L.setCursor(0, 2);
  MrfLCD_L.print(Temperature_B);
}

void Mrf_L_LCD::initializeACS723(void)                     // get zero current reading for offset adjustment
{
  int32_t sumTicks = 0;
  zeroCurrentOffset = 0;

  for(int i=0; i < numADCSamples; i++)
    {
      sumTicks += _adc.readADC_SingleEnded(3);
    }
  zeroCurrentOffset = sumTicks/numADCSamples;
}

void Mrf_L_LCD::updateTempDisplay(void)
{
  String _TempA, _TempB;

  updateTempBars(getBars(mrfATemp), 0);
  updateTempBars(getBars(mrfBTemp), 1);

  _TempA = String(mrfATemp, 3);
  _TempB = String(mrfBTemp, 3);

  if (mrfATemp < 100)
  {
    char i;
    for (i = 6; i > 0; i--) _TempA[i] = _TempA[i - 1];
    _TempA[0] = 0x20;
  }

  if (mrfATemp < 10)
  {
    char i;
    for (i = 6; i > 0; i--) _TempA[i] = _TempA[i - 1];
    _TempA[0] = 0x20;
  }

  Temperature_A[9] = _TempA[0];
  Temperature_A[10] = _TempA[1];
  Temperature_A[11] = _TempA[2];
  MrfLCD_L.setCursor(0, 0);
  MrfLCD_L.print(Temperature_A);

  if (mrfBTemp < 100)
  {
    char i;
    for (i = 6; i > 0; i--) _TempB[i] = _TempB[i - 1];
    _TempB[0] = 0x20;
  }

  if (mrfBTemp < 10)
  {
    char i;
    for (i = 6; i > 0; i--) _TempB[i] = _TempB[i - 1];
    _TempB[0] = 0x20;
  }

  Temperature_B[9] = _TempB[0];
  Temperature_B[10] = _TempB[1];
  Temperature_B[11] = _TempB[2];
  MrfLCD_L.setCursor(0, 2);
  MrfLCD_L.print(Temperature_B);
}

uint8_t Mrf_L_LCD::getBars(float temperature)
{
  if(temperature < 20) return 0;                              
  else if(temperature >= 20 && temperature < 22) return 1; 
  else if(temperature >= 22 && temperature < 24) return 2; 
  else if(temperature >= 24 && temperature < 26) return 3; 
  else if(temperature >= 26 && temperature < 28) return 4; 
  else if(temperature >= 28 && temperature < 30) return 5; 
  else if(temperature >= 30 && temperature < 32) return 6; 
  else if(temperature >= 32 && temperature < 34) return 7; 
  else if(temperature >= 34 && temperature < 36) return 8; 
  else if(temperature >= 36 && temperature < 38) return 9; 
  else if(temperature >= 38 && temperature < 40) return 10; 
  else if(temperature >= 40 && temperature < 42) return 11; 
  else if(temperature >= 42 && temperature < 44) return 12; 
  else if(temperature >= 44 && temperature < 46) return 13; 
  else if(temperature >= 46 && temperature < 48) return 14; 
  else if(temperature >= 48 && temperature < 50) return 15; 
  else if(temperature >= 50 && temperature < 52) return 16; 
  else if(temperature >= 52 && temperature < 54) return 17; 
  else if(temperature >= 54 && temperature < 56) return 18; 
  else if(temperature >= 56 && temperature < 58) return 19; 
  else if(temperature >= 58) return 20; 
}

void Mrf_L_LCD::updateTempBars(uint8_t level, uint8_t display)
{
  
    if(display == 0) MrfLCD_L.setCursor(0, 1);
    else MrfLCD_L.setCursor(0, 3);
    switch (level)
    {
        case 0:
            MrfLCD_L.print(Temp_30);
            break;

        case 1:
            MrfLCD_L.print(Temp_35);
            break;

        case 2:
            MrfLCD_L.print(Temp_40);
            break;

        case 3:
            MrfLCD_L.print(Temp_45);
            break;

        case 4:
            MrfLCD_L.print(Temp_50);
            break;

        case 5:
            MrfLCD_L.print(Temp_55);
            break;

        case 6:
            MrfLCD_L.print(Temp_60);
            break;

        case 7:
            MrfLCD_L.print(Temp_65);
            break;

        case 8:
            MrfLCD_L.print(Temp_70);
            break;

        case 9:
            MrfLCD_L.print(Temp_75);
            break;

        case 10:
            MrfLCD_L.print(Temp_80);
            break;

        case 11:
            MrfLCD_L.print(Temp_85);
            break;

        case 12:
            MrfLCD_L.print(Temp_90);
            break;

        case 13:
            MrfLCD_L.print(Temp_95);
            break;

        case 14:
            MrfLCD_L.print(Temp_100);
            break;

        case 15:
            MrfLCD_L.print(Temp_105);
            break;

        case 16:
            MrfLCD_L.print(Temp_110);
            break;

        case 17:
            MrfLCD_L.print(Temp_115);
            break;

        case 18:
            MrfLCD_L.print(Temp_120);
            break;

        case 19:
            MrfLCD_L.print(Temp_125);
            break;

        case 20:
            MrfLCD_L.print(Temp_130);
            break;
    }
}

bool Mrf_L_LCD::readADC(void)                              // read current sensor ADC
{

// ads1115 ADC default config. 2/3x gain +/- 6.144V  1 bit = 0.1875mV

  char mrf_A[10];

  int32_t normalizedTicks;

  currentTicks = _adc.readADC_SingleEnded(3);

   if (adcReadPeriod == numADCSamples)                     // update current sensor and temperature sensor readings
    {

      normalizedTicks = (sumCurrentTicks/numADCSamples) - zeroCurrentOffset;
      
      mrfAmps = (normalizedTicks * 0.1875) / 400.0;
                                                           // ADS1115 0.1875mV/bit
                                                           // ACS723 400mV/Amp
                                                           // Zero current offset typically 0.1 x Vcc
      
      if(mrfAmps < 0.0) mrfAmps = 0.0;
      
      mrfATemp = tempSensor.getTemp(tempASensor);
      mrfBTemp = tempSensor.getTemp(tempBSensor);

      sumCurrentTicks = 0;

      adcReadPeriod = 0;

      updateTempDisplay();
      MrfRightLCD.updateAmpDisplay(mrfAmps);

      return;
    }

    else
    {
      sumCurrentTicks += currentTicks;
      adcReadPeriod++;
    }
}
