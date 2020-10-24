#include <Arduino.h>
#include "AddressAndModeSetter.h"

const uint8_t SHIFT_DATA = 2;
const uint8_t SHIFT_CLK = 3;
const uint8_t SHIFT_LATCH = 4;

const uint8_t EEPROM_D0 = 5;
const uint8_t EEPROM_D7 = 12;
const uint8_t EEPROM_WE = 13;

const AddressAndModeSetter addressAndModeSetter(SHIFT_DATA, SHIFT_CLK, SHIFT_LATCH);

void setDatapinMode(uint8_t mode) {
	for(uint8_t i = EEPROM_D0; i <= EEPROM_D7; i++) {
		pinMode(i, mode);
	}
}

uint8_t readEEPROM(uint16_t address) {
	uint8_t readByte = 0;
	
	setDatapinMode(INPUT);
	addressAndModeSetter.setAddress(address, false);
	addressAndModeSetter.setAddress(address, true);
	
	_NOP();
	_NOP();
	_NOP();
	
	for(uint8_t i = EEPROM_D7; i >= EEPROM_D0; i--) {
		readByte = (readByte << 1) + digitalRead(i);
	}
	
	addressAndModeSetter.setAddress(address, false);
	
	return readByte;
}

void writeEEPROM(uint16_t address, uint8_t data) {
	
	setDatapinMode(OUTPUT);
	addressAndModeSetter.setAddress(address, false);
		
	for(uint8_t i = EEPROM_D0; i <= EEPROM_D7; i++) {
		digitalWrite(i, data & 0x01);
		data = data >> 1;
	}
	
	// Wait for data setup time
	_NOP();
	
	digitalWrite(EEPROM_WE, HIGH);
	digitalWrite(EEPROM_WE, LOW);
	_NOP();
	_NOP();
	_NOP();
	digitalWrite(EEPROM_WE, HIGH);
	
	delay(10);
}

void setup() {
	Serial.begin(57600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	
	// put your setup code here, to run once:
	pinMode(SHIFT_DATA, OUTPUT);
	pinMode(SHIFT_CLK, OUTPUT);
	pinMode(SHIFT_LATCH, OUTPUT);
	
	digitalWrite(EEPROM_WE, HIGH);
	pinMode(EEPROM_WE, OUTPUT);
	
	Serial.println(F("Start writing"));
	
	writeEEPROM(0, 0xef);
	
	for(uint16_t i = 0; i <= 0xff; i++) {
		writeEEPROM(i, i);
	}
	
	Serial.println(F("End writing"));
	
	for(uint16_t base = 0; base < 1024; base+=16) {
		uint8_t data[16];
		for(uint8_t offset = 0; offset < 16; offset++) {
			data[offset] = readEEPROM(base + offset);
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
