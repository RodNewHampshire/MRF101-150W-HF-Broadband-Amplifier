/******************************************************************************
*
* MRF101 Amplifier by AD5GH
*
* ARDUINO MEGA DISPLAY & CONTROL BOARD SOFTWARE
* RIGHT LCD FUNCTION ROUTINES
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

#include "Adafruit_LiquidCrystal.h"
#include <arduino.h>
#include <Mrf_R_LCD.h>
#include <Mrf_L_LCD.h>

Adafruit_LiquidCrystal  MrfLCD_R(1);
Mrf_L_LCD               MrfLeftLCD;

char Status[21]             = {'S','t','a','t','u','s',':',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','M','\0'};
char MRF_Amps_Acs[21]       = {'P','A',' ','A','m','p','s',':',' ',' ','0','.','0','0',' ',' ',' ',' ',' ',' ','\0'};

const char Band_Disp_1[11]  = {'1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
const char Band_Disp_2[11]  = {'6','8','4','3','2','1','1','1','1','1','1'};
const char Band_Disp_3[11]  = {'0','0','0','0','0','7','5','2','0','0','0'};

const char Status_Disp_1[5] = {'S','E','O',' ',' '};
const char Status_Disp_2[5] = {'t','n','n',' ',' '};
const char Status_Disp_3[5] = {'a','a',' ',' ',' '};
const char Status_Disp_4[5] = {'n','b','A',' ',' '};
const char Status_Disp_5[5] = {'d','l','i',' ',' '};
const char Status_Disp_6[5] = {'b','e','r',' ',' '};
const char Status_Disp_7[5] = {'y','d',' ',' ',' '};
const char Status_Disp_8[5] = {' ',' ',' ',' ',' '};

const char Amps_0[21] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_05[21] = {0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_10[21] = {0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_15[21] = {0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_20[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_25[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_30[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_35[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_40[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_45[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_50[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_55[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_60[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_65[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_70[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_75[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_80[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, 0x20, '\0'};
const char Amps_85[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, 0x20, '\0'};
const char Amps_90[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x20, '\0'};
const char Amps_95[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, '\0'};
const char Amps_100[21] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, '\0'};

int8_t    _Band;

Mrf_R_LCD::Mrf_R_LCD(void)
{

}

void Mrf_R_LCD::begin(void)
{
	MrfLCD_R.begin(20, 4);
}

void Mrf_R_LCD::clear(void)
{
	MrfLCD_R.clear();
}

void Mrf_R_LCD::splash(void)
{
 	MrfLCD_R.print(F("       AD5GH        "));                // Mrf LCD splash
  MrfLCD_R.setCursor(0, 1);
  MrfLCD_R.print(F("  MRF101 150 WATT  "));
  MrfLCD_R.setCursor(0, 2);
  MrfLCD_R.print(F("  HF AMATEUR BAND  "));
  MrfLCD_R.setCursor(0, 3);
  MrfLCD_R.print(F("     AMPLIFIER     "));
}

void Mrf_R_LCD::initializeDisplay(void)
{
  MrfLCD_R.clear();
  MrfLCD_R.setCursor(0, 0);
  MrfLCD_R.print(Status);
  MrfLCD_R.setCursor(0, 2);
  MrfLCD_R.print(MRF_Amps_Acs);
}

void Mrf_R_LCD::updateStatusDisplay(uint8_t status)
{
  Status[8] = Status_Disp_1[status];
  Status[9] = Status_Disp_2[status];
  Status[10] = Status_Disp_3[status];
  Status[11] = Status_Disp_4[status];
  Status[12] = Status_Disp_5[status];
  Status[13] = Status_Disp_6[status];
  Status[14] = Status_Disp_7[status];
  Status[15] = Status_Disp_8[status];
  MrfLCD_R.setCursor(0, 0);
  MrfLCD_R.print(Status);
}

void Mrf_R_LCD::UpdateBandDisplay(uint8_t band)
{
  Status[16] = Band_Disp_1[band];
  Status[17] = Band_Disp_2[band];
  Status[18] = Band_Disp_3[band];
  MrfLCD_R.setCursor(0, 0);
  MrfLCD_R.print(Status);
}

void Mrf_R_LCD::updateAmpDisplay(float mrf_Amps_ACS)
{
	String ACSAmps;

  ACSAmps = String(mrf_Amps_ACS, 4);

  if (mrf_Amps_ACS < 10)
  {
    char i;
    for (i = 6; i > 0; i--) ACSAmps[i] = ACSAmps[i - 1];
    ACSAmps[0] = 0x20;
  }

  MRF_Amps_Acs[9] = ACSAmps[0];
  MRF_Amps_Acs[10] = ACSAmps[1];
  MRF_Amps_Acs[11] = ACSAmps[2];
  MRF_Amps_Acs[12] = ACSAmps[3];
  MRF_Amps_Acs[13] = ACSAmps[4];
  MrfLCD_R.setCursor(0, 2);
  MrfLCD_R.print(MRF_Amps_Acs);

  if(mrf_Amps_ACS < 0.1) updateAmpBars(0);                              
  else if(mrf_Amps_ACS >= 0.1 && mrf_Amps_ACS < 0.5) updateAmpBars(1);
  else if(mrf_Amps_ACS >= 0.5 && mrf_Amps_ACS < 1.0) updateAmpBars(2);
  else if(mrf_Amps_ACS >= 1.0 && mrf_Amps_ACS < 1.5) updateAmpBars(3);
  else if(mrf_Amps_ACS >= 1.5 && mrf_Amps_ACS < 2.0) updateAmpBars(4);
  else if(mrf_Amps_ACS >= 2.0 && mrf_Amps_ACS < 2.5) updateAmpBars(5);
  else if(mrf_Amps_ACS >= 2.5 && mrf_Amps_ACS < 3.0) updateAmpBars(6);
  else if(mrf_Amps_ACS >= 3.0 && mrf_Amps_ACS < 3.5) updateAmpBars(7);
  else if(mrf_Amps_ACS >= 3.5 && mrf_Amps_ACS < 4.0) updateAmpBars(8);
  else if(mrf_Amps_ACS >= 4.0 && mrf_Amps_ACS < 4.5) updateAmpBars(9);
  else if(mrf_Amps_ACS >= 4.5 && mrf_Amps_ACS < 5.0) updateAmpBars(10);
  else if(mrf_Amps_ACS >= 5.0 && mrf_Amps_ACS < 5.5) updateAmpBars(11);
  else if(mrf_Amps_ACS >= 5.5 && mrf_Amps_ACS < 6.0) updateAmpBars(12);
  else if(mrf_Amps_ACS >= 6.0 && mrf_Amps_ACS < 6.5) updateAmpBars(13);
  else if(mrf_Amps_ACS >= 6.5 && mrf_Amps_ACS < 7.0) updateAmpBars(14);
  else if(mrf_Amps_ACS >= 7.0 && mrf_Amps_ACS < 7.5) updateAmpBars(15);
  else if(mrf_Amps_ACS >= 7.5 && mrf_Amps_ACS < 8.0) updateAmpBars(16);
  else if(mrf_Amps_ACS >= 8.0 && mrf_Amps_ACS < 8.5) updateAmpBars(17);
  else if(mrf_Amps_ACS >= 8.5 && mrf_Amps_ACS < 9.0) updateAmpBars(18);
  else if(mrf_Amps_ACS >= 9.0 && mrf_Amps_ACS < 9.5) updateAmpBars(19);
  else if(mrf_Amps_ACS >= 9.5) updateAmpBars(20);
}

void Mrf_R_LCD::updateAmpBars(uint8_t level)
{
    MrfLCD_R.setCursor(0, 3);
    switch (level)
    {
        case 0:
            MrfLCD_R.print(Amps_0);
            break;

        case 1:
            MrfLCD_R.print(Amps_05);
            break;

        case 2:
            MrfLCD_R.print(Amps_10);
            break;

        case 3:
            MrfLCD_R.print(Amps_15);
            break;

        case 4:
            MrfLCD_R.print(Amps_20);
            break;

        case 5:
            MrfLCD_R.print(Amps_25);
            break;

        case 6:
            MrfLCD_R.print(Amps_30);
            break;

        case 7:
            MrfLCD_R.print(Amps_35);
            break;

        case 8:
            MrfLCD_R.print(Amps_40);
            break;

        case 9:
            MrfLCD_R.print(Amps_45);
            break;

        case 10:
            MrfLCD_R.print(Amps_50);
            break;

        case 11:
            MrfLCD_R.print(Amps_55);
            break;

        case 12:
            MrfLCD_R.print(Amps_60);
            break;

        case 13:
            MrfLCD_R.print(Amps_65);
            break;

        case 14:
            MrfLCD_R.print(Amps_70);
            break;

        case 15:
            MrfLCD_R.print(Amps_75);
            break;

        case 16:
            MrfLCD_R.print(Amps_80);
            break;

        case 17:
            MrfLCD_R.print(Amps_85);
            break;

        case 18:
            MrfLCD_R.print(Amps_90);
            break;

        case 19:
            MrfLCD_R.print(Amps_95);
            break;

        case 20:
            MrfLCD_R.print(Amps_100);
            break;
    }
}

