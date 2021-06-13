/******************************************************************************
*
* MRF101 Amplifier by AD5GH
*
* ARDUINO MEGA DISPLAY & CONTROL BOARD SOFTWARE
* SERIAL LINK ROUTINES
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

#include <arduino.h>
#include <Mrf_Link.h>
#include <Mrf_R_LCD.h>


Mrf_R_LCD __mrfLCD;


char rxCommand[20];
uint8_t rxCounter = 0;
uint8_t rxCharacter = 0;

uint8_t TR_FLAG = 0;

enum
{
 	FALSE,
 	TRUE
};

enum
{
	REC,
	XMT
};


Mrf_Link::Mrf_Link(void)
{

}


void Mrf_Link::begin(void)
{
	pinMode(19, INPUT);
	Serial1.begin(115200);
}


void Mrf_Link::getBand()
{
	char cmdBD[3] = "BD;";
	send(cmdBD, 3);
}


bool Mrf_Link::available(void)
{
	if(Serial1.available())
	{
		rxCharacter = Serial1.read();
		rxCommand[rxCounter] = rxCharacter;
		if(rxCharacter == ';') 
		{
			execute();
			rxCounter = 0;
		}

		else
		{
			rxCounter++;
		}
	}
}


void Mrf_Link::execute(void)
{
	switch(rxCommand[0])
	{
		case 'B':
			switch(rxCommand[1])
			{
				case 'D':								// receiver sending frequency band
					updateBand();
					break;
			}
			break;

		case 'M':
			switch(rxCommand[1])
			{
				case 'D':								// receiver sending transmit / receive command
					updateTRStatus();
					break;
			}
			break;
	}
}


void Mrf_Link::updateBand(void)							// update amplifier frequency band
{
	__mrfLCD.UpdateBandDisplay(rxCommand[3]);
}


void Mrf_Link::updateTRStatus(void)						// update transmit / receive status
{
	switch(rxCommand[2])
	{
		case 'T':										// transmit mode
			TR_FLAG = XMT;
			break;

		case 'R':										// receive mode
			TR_FLAG = REC;
			break;
	}
}


void Mrf_Link::send(uint8_t data[], uint8_t num)
{
	for (uint8_t i=0; i<num; i++) Serial1.write(data[i]);
}


uint8_t Mrf_Link::trStatus(void)
{
	return(TR_FLAG);
}

