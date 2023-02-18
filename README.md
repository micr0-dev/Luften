# Luften - Rocket Flight Computer
This is a flight computer for a rocket, using an Arduino and an Adafruit MPL3115A2 altimeter to record altitude data. The code is written in C++ and uses PlatformIO as the development environment.

## Usage
1. Insert a microSD card into the module and power it on.
2. The code will run and record altitude data to the microSD card until the microSD card is removed.
3. The data will be saved to a new file on the microSD card in CSV format with a name in the format ANALOG##.TXT, where ## is a number between 00 and 99.
4. If an error occurs, the LED connected to pin 13 will blink to indicate the error code. The number of blinks corresponds to the error code, and each blink lasts for 100 milliseconds.
## Error Codes (number of beeps/blinks)
2: Could not find MPL3115A2 sensor. Check wiring.

3: Failed to initiliz SD card

4: Could not create the logfile on the SD card

5: Altimeter is reporting impossible altitude
