
/****************************************************************************************************************************

  MRF101 Amplifier
  150W LDMOS HF Amplifier

  by Rod Gatehouse

  Distributed under the terms of the MIT License:
  http://www.opensource.org/licenses/mit-license

  VERSION 1.4.0
  June 4, 2021

*****************************************************************************************************************************/

#include <Adafruit_SleepyDog.h>
#include <Mrf_Link.h>
#include <arduino.h>
#include <Mrf_L_LCD.h>
#include <Mrf_R_LCD.h>

Mrf_R_LCD rightLCD;
Mrf_L_LCD leftLCD;
Mrf_Link  mrfLink;

uint8_t   AMP_STATE;
uint8_t   AMP_LAST_STATE;

enum
{
  STDBY,
  ENABLE,
  ON_AIR,
  CLEAR
};

enum
{
  RX,
  TX
};

/******************** for Digital I/O ***************************************************************************************/

#define enableSwitch  3
#define trLED         4
#define pwrRelay      5
#define bypassRelay   6
#define fanControl    7
#define biasControl   8
#define DS18B20_A     9
#define DS18B20_B     10

/******************** Set Up ************************************************************************************************/

void setup()
{
  pinMode(trLED, OUTPUT);
  digitalWrite(trLED, LOW);

  pinMode(pwrRelay, OUTPUT);
  digitalWrite(pwrRelay, LOW);

  pinMode(fanControl, OUTPUT);
  digitalWrite(fanControl, LOW);

  pinMode(biasControl, OUTPUT);
  digitalWrite(biasControl, LOW);

  pinMode(bypassRelay, OUTPUT);
  digitalWrite(bypassRelay, LOW);
  
  pinMode(enableSwitch, INPUT_PULLUP);

  leftLCD.begin();
  rightLCD.begin();

  leftLCD.splash();
  rightLCD.splash();

  delay(5000);

  leftLCD.initializeDisplay();
  rightLCD.initializeDisplay();

  while (!digitalRead(enableSwitch))                       // ENABLE / STDBY switch must be in "STDBY" before proceeding
  {
    rightLCD.updateStatusDisplay(ENABLE);
    delay(500);
    rightLCD.updateStatusDisplay(CLEAR);
    delay(500);
  }

  Watchdog.enable(8000);                                  // watchdog timer to reset Amp in event of SW problem

  mrfLink.begin();
  delay(250);
  mrfLink.getBand();                                      // establish link with receiver and get current Band setting
  while (!mrfLink.available()) {}                         // if link not working, watchdog timer will reset Arduino, setting up for another try, and keep trying until link is established

  leftLCD.initializeACS723();                             // initialize Amp current sensor
}


void loop()
{
  mrfLink.available();                                   // check receiver link for PTT and Band info
  
  leftLCD.readADC();                                     // update current and temperature readings
  
  mrfLink.available();                                   // check receiver link again for PTT and Band info. Want to react quickly to PTT commands.
  
  if (digitalRead(enableSwitch)) AMP_STATE = STDBY;      // Front panel ENABLE-STDBY switch in STDBY position
  else if(AMP_STATE != ON_AIR) AMP_STATE = ENABLE;       // Front panel ENABLE-STDBY switch in ENABLE position   

  switch (AMP_STATE)                                     // Amp State Machine
  {
    case STDBY:
      {
        if (AMP_LAST_STATE == STDBY) break;
        else
        {                                                // Amp to STANDBY mode
          digitalWrite(biasControl, LOW);                // remove amp bias
          digitalWrite(pwrRelay, LOW);                   // remove 50V power
          digitalWrite(bypassRelay, LOW);                // amp to bypass
          digitalWrite(fanControl, LOW);                 // turn off fan
          digitalWrite(trLED, LOW);                      // On Air LED off
          AMP_LAST_STATE = AMP_STATE;                    // save Amp current state
          break;
        }
      }

    case ENABLE:
      {
        if (AMP_LAST_STATE != ENABLE)                    // Amp to ENABLE mode
        {
          digitalWrite(pwrRelay, HIGH);                  // apply 50V power
          digitalWrite(bypassRelay, HIGH);               // amp in-line
          digitalWrite(fanControl, HIGH);                // turn on fan
          AMP_LAST_STATE = AMP_STATE;                    // save Amp current state
        }

        if (mrfLink.trStatus() == TX)                    // PTT active, Amp to ON AIR mode
        {
          AMP_STATE = ON_AIR;
          digitalWrite(biasControl, HIGH);               // apply amp bias
          digitalWrite(trLED, HIGH);                     // On Air LED on
        }
        break;
      }

    case ON_AIR:
      {
        if (AMP_LAST_STATE != ON_AIR) AMP_LAST_STATE = AMP_STATE;

        if (mrfLink.trStatus() == RX)                    // PTT inactive, Amp to ENABLE mode
        {
          digitalWrite(biasControl, LOW);                // remove amp bias
          digitalWrite(trLED, LOW);                      // On Air LED off
          AMP_STATE = ENABLE;
        }
        break;
      }
  }
  
  rightLCD.updateStatusDisplay(AMP_STATE);
  
  Watchdog.reset();
}
