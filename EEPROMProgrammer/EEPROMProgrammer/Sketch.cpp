#include <Arduino.h>
#include "EEPROMWriter.h"
#include "EEPROMReaderWriter.h"
#include "UsedPorts.h"

uint8_t segmentBytes[] = { 0x1, 0x2, 0x3, 0x4 };

void setup() {
	Serial.begin(57600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	
	// put your setup code here, to run once:
	EEPROMWriter writer(Ports::SHIFT_DATA, Ports::SHIFT_CLK, Ports::SHIFT_LATCH, Ports::EEPROM_WE, Ports::EEPROM_DATAPINS);
	
	Serial.println(F("Before:"));
	writer.printData(256);
	
	uint8_t bytes[256];
	for(size_t i = 0; i < sizeof(bytes); i++) {
		bytes[i] = i;
	}
	
	writer.writeData(bytes, sizeof(bytes));
	
	Serial.println(F("After:"));
	writer.printData(256);
	
	Serial.println(F("EOF"));
}

void loop() {
	// put your main code here, to run repeatedly:
	
}