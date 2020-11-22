#include <Arduino.h>
#include "EEPROMWriter.h"
#include "UsedPorts.h"
#include "OutputmoduleWriter.h"

// Common Anode
// const uint8_t data[] PROGMEM = { 0x81, 0xcf, 0x92, 0x86, 0xcc, 0xa4, 0xa0, 0x8f, 0x80, 0x84, 0x88, 0xe0, 0xb1, 0xc2, 0xb0, 0xb8 };
	
// Common Cathode
// const uint8_t data[] PROGMEM = { 0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b, 0x77, 0x1f, 0x4e, 0x3d, 0x4f, 0x47 };

void setup() {
	Serial.begin(57600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	EEPROMWriter writer(Ports::SHIFT_DATA, Ports::SHIFT_CLK, Ports::SHIFT_LATCH, Ports::EEPROM_WE, Ports::EEPROM_DATAPINS);
	OutputmoduleWriter outputWriter(writer);
	delay(5000);
	
	writer.printData(2048);
	
	Serial.println(F("Start writing!"));
	
	bool isSuccessful = outputWriter.write(256);
	
	if (!isSuccessful) {
		Serial.println(F("Error writing data!"));
	} else {
		Serial.println(F("Successful!"));
	}
	
	Serial.println(F("EOF"));
}

void loop() { }