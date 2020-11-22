/*
* EEPROMWriter.cpp
*
* Created: 24/10/2020 19:42:34
* Author: Maurice Hieronymus
*/


#include "EEPROMWriter.h"

EEPROMWriter::EEPROMWriter(const uint8_t shiftDataPin, const uint8_t shiftClockPin, const uint8_t shiftLatchPin, const uint8_t writeEnablePin, const uint8_t (&dataPins)[8])
: eepromReaderWriter(shiftDataPin, shiftClockPin, shiftLatchPin, writeEnablePin, dataPins)
{

}

// default destructor
EEPROMWriter::~EEPROMWriter()
{
} //~EEPROMWriter

bool EEPROMWriter::write(const uint8_t data, uint16_t address) const
{
	eepromReaderWriter.write(address, data);
	
	if (!validate(data, address)) {		
		Serial.println(F("####################################"));
		Serial.println(F("Validation failed!!!."));
		Serial.println(F("####################################"));
		return false;
	}
	return true;
}

void EEPROMWriter::erase(const size_t bytes) const
{
	Serial.println(F("Erasing..."));
	for(size_t i = 0; i < bytes; i++) {
		eepromReaderWriter.write(i, 0);
	}
}

void EEPROMWriter::printData(size_t bytes) const
{
	bytes = bytes + (16 - (bytes % 16));
	
	for(size_t base = 0; base < bytes; base+=16) {
		uint8_t data[16];
		
		for(uint8_t offset = 0; offset < 16; offset++) {
			data[offset] = eepromReaderWriter.read(base + offset);
		}
		
		char buf[80];
		sprintf(buf, "%03x: %02x %02x %02x %02x %02x %02x %02x %02x     %02x %02x %02x %02x %02x %02x %02x %02x",
		base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11],
		data[12], data[13], data[14], data[15]);
		
		Serial.println(buf);
	}
}

bool EEPROMWriter::validate(const uint8_t data, uint16_t address) const
{
	auto readValue = eepromReaderWriter.read(address);
	if (readValue != data) {
		return false;
	}
	return true;
}
