#include <Arduino.h>
#include "EEPROMWriter.h"
#include "UsedPorts.h"

const uint8_t segmentBytes[] PROGMEM = { 0x01, 0x4f, 0x12, 0x06, 0x4c, 0x24, 0x20, 0x0f, 0x00, 0x04, 0x08, 0x60, 0x31, 0x42, 0x30, 0x38 };

void setup() {
	Serial.begin(57600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	EEPROMWriter writer(Ports::SHIFT_DATA, Ports::SHIFT_CLK, Ports::SHIFT_LATCH, Ports::EEPROM_WE, Ports::EEPROM_DATAPINS);
	
	Serial.println(F("Before:"));
	writer.printData(sizeof(segmentBytes));
	
	writer.erase(sizeof(segmentBytes));
	writer.writeDataFromProgmem(segmentBytes, sizeof(segmentBytes));
	
	Serial.println(F("After:"));
	writer.printData(sizeof(segmentBytes));
	
	Serial.println(F("EOF"));
}

void loop() { }