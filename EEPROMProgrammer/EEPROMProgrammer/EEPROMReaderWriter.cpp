/*
* EEPROMReaderWriter.cpp
*
* Created: 24/10/2020 16:34:47
* Author: Maurice Hieronymus
*/


#include "EEPROMReaderWriter.h"
#include "Helper.h"

// default constructor
EEPROMReaderWriter::EEPROMReaderWriter(
const uint8_t shiftDataPin, 
const uint8_t shiftClockPin, 
const uint8_t shiftLatchPin, 
const uint8_t writeEnablePin,
const uint8_t (&dataPins)[8])
: addressAndModeSetter(shiftDataPin, shiftClockPin, shiftLatchPin), writeEnablePin(writeEnablePin), dataPins(dataPins)
{
	setDatapinMode(INPUT);
	digitalWrite(writeEnablePin, HIGH);
	pinMode(writeEnablePin, OUTPUT);
} //EEPROMReaderWriter

// default destructor
EEPROMReaderWriter::~EEPROMReaderWriter()
{
} //~EEPROMReaderWriter

void EEPROMReaderWriter::write(const uint16_t address, const uint8_t value) const
{	
	addressAndModeSetter.writeToAddress(address);
	setDatapinMode(OUTPUT);
	
	uint8_t valueToWrite = value;
	for(uint8_t port: dataPins) {
		digitalWrite(port, valueToWrite & 0x01);
		valueToWrite = valueToWrite >> 1;
	}
	
	digitalWrite(writeEnablePin, HIGH);
	digitalWrite(writeEnablePin, LOW);
	
	// Helper::ExecuteNops(3);
	
	digitalWrite(writeEnablePin, HIGH);
	
	// Data polling
	while(read(address) != value) {	}
}

uint8_t EEPROMReaderWriter::read(const uint16_t address) const
{
	setDatapinMode(INPUT);
	
	// Toggle output enable to trigger read of EEPROM
	addressAndModeSetter.readFromAddress(address);
	// Wait until address lines are stable
	delayMicroseconds(1);

	uint8_t readByte = 0;

	// Iterate over data pins
	// Start with LSB first
	uint8_t bitPosition = 0;
	for(uint8_t port: dataPins) {
		auto readValue = digitalRead(port);
		
		if (readValue) {
			readByte |= (1) << bitPosition;
		}
		bitPosition++;
	}

	return readByte;
}

void EEPROMReaderWriter::setDatapinMode(const uint8_t mode) const
{
	for(uint8_t port: dataPins) {
		pinMode(port, mode);
	}
}
