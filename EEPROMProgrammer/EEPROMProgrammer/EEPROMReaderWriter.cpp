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
	digitalWrite(writeEnablePin, HIGH);
	pinMode(writeEnablePin, OUTPUT);
	
	setDatapinMode(INPUT);
} //EEPROMReaderWriter

// default destructor
EEPROMReaderWriter::~EEPROMReaderWriter()
{
} //~EEPROMReaderWriter

void EEPROMReaderWriter::write(uint16_t address, uint8_t value) const
{
	setDatapinMode(OUTPUT);
	
	addressAndModeSetter.writeToAddress(address);
	
	for(uint8_t port: dataPins) {
		digitalWrite(port, value & 0x01);
		value = value >> 1;
	}
	
	// Wait for data setup time
	Helper::ExecuteNops(1);
	
	digitalWrite(writeEnablePin, HIGH);
	digitalWrite(writeEnablePin, LOW);
	
	Helper::ExecuteNops(3);
	
	digitalWrite(writeEnablePin, HIGH);
	
	delay(10);
	setDatapinMode(INPUT);
}

uint8_t EEPROMReaderWriter::read(uint16_t address) const
{
	setDatapinMode(INPUT);
	
	// Toggle output enable to trigger read of EEPROM
	addressAndModeSetter.readFromAddress(address);
	// Wait until address lines are stable
	Helper::ExecuteNops(3);

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

void EEPROMReaderWriter::setDatapinMode(uint8_t mode) const
{
	for(uint8_t port: dataPins) {
		pinMode(port, mode);
	}
}
