#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MPL3115A2.h>
#include <SD.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13
byte ALTIM_ADDR = 0x60;

Adafruit_MPL3115A2 baro;

// Set the pins used
#define cardSelect 4

File logfile;

void error(uint8_t errno)
{
	while (1)
	{
		uint8_t i;
		for (i = 0; i < errno; i++)
		{
			digitalWrite(13, HIGH);
			delay(100);
			digitalWrite(13, LOW);
			delay(100);
		}
		for (i = errno; i < 10; i++)
		{
			delay(200);
		}
	}
}

void setup()
{
	delay(5000);
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);

	if (!baro.begin())
	{
		Serial.println("Could not find sensor. Check wiring.");
		error(2);
	}
	baro.setSeaPressure(1013.26);

	// see if the card is present and can be initialized:
	if (!SD.begin(cardSelect))
	{
		Serial.println("Card init. failed!");
		error(3);
	}
	char filename[15];
	strcpy(filename, "/ANALOG00.TXT");
	for (uint8_t i = 0; i < 100; i++)
	{
		filename[7] = '0' + i / 10;
		filename[8] = '0' + i % 10;
		// create if does not exist, do not open existing, write, sync after write
		if (!SD.exists(filename))
		{
			break;
		}
	}

	logfile = SD.open(filename, FILE_WRITE);
	if (!logfile)
	{
		Serial.print("Couldnt create ");
		Serial.println(filename);
		error(4);
	}
	Serial.print("Writing to ");
	Serial.println(filename);

	pinMode(13, OUTPUT);
	pinMode(8, OUTPUT);
	Serial.println("Ready!");
}

int logCount = 0;

void loop()
{
	// turn the LED on (HIGH is the voltage level)
	digitalWrite(LED_BUILTIN, HIGH);

	// unsigned int lsb, msb;

	// Wire.beginTransmission(ALTIM_ADDR); // Address of the altimeter
	// Wire.write(0x02); // Command to read altitude
	// Wire.endTransmission();
	// Wire.requestFrom(ALTIM_ADDR, 2, true); // Request 2 bytes of data

	// lsb = Wire.read();
	// msb = Wire.read();

	// Wire.endTransmission(false);

	// int altitude = ((msb << 8) | lsb);

	float altitude = baro.getAltitude();

	Serial.print("Sensor value: ");
	Serial.println(altitude);

	logfile.print(logCount);
	logfile.print(",");
	logfile.println(altitude);
	logfile.flush();

	logCount++;

	if (altitude <= 0)
	{
		error(4);
	}

	// turn the LED off by making the voltage LOW
	digitalWrite(LED_BUILTIN, LOW);

	delay(20);
}