#include <Arduino.h>
#include "EEPROMWriter.h"
#include "EEPROMReaderWriter.h"
#include "UsedPorts.h"

uint8_t const segmentBytes[] = { 0x01, 0x4f, 0x12, 0x06, 0x4c, 0x24, 0x20, 0x0f, 0x00, 0x04, 0x08, 0x60, 0x31, 0x42, 0x30, 0x38 };

void setup() {
	Serial.begin(57600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	
	// put your setup code here, to run once:
	EEPROMWriter writer(Ports::SHIFT_DATA, Ports::SHIFT_CLK, Ports::SHIFT_LATCH, Ports::EEPROM_WE, Ports::EEPROM_DATAPINS);
	
	Serial.println(F("Before:"));
	writer.printData(256);
	
	writer.writeData(segmentBytes, sizeof(segmentBytes));
	
	Serial.println(F("After:"));
	writer.printData(256);
	
	Serial.println(F("EOF"));
}

void loop() {
	// put your main code here, to run repeatedly:
	
}