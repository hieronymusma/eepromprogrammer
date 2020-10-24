#include <Arduino.h>
#include "EEPROMReaderWriter.h"
#include "UsedPorts.h"

void setup() {
	Serial.begin(57600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	
	// put your setup code here, to run once:
	EEPROMReaderWriter readerwriter(Ports::SHIFT_DATA, Ports::SHIFT_CLK, Ports::SHIFT_LATCH, Ports::EEPROM_WE, Ports::EEPROM_DATAPINS);
	
	Serial.println(F("Start writing"));
	
	for(uint16_t i = 0; i <= 0xff; i++) {
		readerwriter.write(i, i+1);
	}
	
	Serial.println(F("End writing"));
	
	for(uint16_t base = 0; base < 1024; base+=16) {
		uint8_t data[16];
		for(uint8_t offset = 0; offset < 16; offset++) {
			data[offset] = readerwriter.read(base + offset);
		}
		char buf[80];
		sprintf(buf, "%03x: %02x %02x %02x %02x %02x %02x %02x %02x     %02x %02x %02x %02x %02x %02x %02x %02x",
		base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11],
		data[12], data[13], data[14], data[15]);
		Serial.println(buf);
	}
	
	Serial.println(F("EOF"));
}

void loop() {
	// put your main code here, to run repeatedly:
	
}
