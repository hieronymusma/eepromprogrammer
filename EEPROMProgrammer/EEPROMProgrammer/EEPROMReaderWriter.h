/* 
* EEPROMReaderWriter.h
*
* Created: 24/10/2020 16:34:48
* Author: Maurice Hieronymus
*/
#include <Arduino.h>
#include "AddressAndModeSetter.h"

#ifndef __EEPROMREADERWRITER_H__
#define __EEPROMREADERWRITER_H__


class EEPROMReaderWriter
{
//variables
public:
protected:
private:
	const AddressAndModeSetter addressAndModeSetter;
	const uint8_t writeEnablePin;
	const uint8_t (&dataPins)[8];
	
//functions
public:
	EEPROMReaderWriter(const uint8_t shiftDataPin, const uint8_t shiftClockPin,	const uint8_t shiftLatchPin, const uint8_t writeEnablePin, const uint8_t (&dataPins)[8]);
	~EEPROMReaderWriter();
	void write(uint16_t address, uint8_t value) const;
	uint8_t read(uint16_t address) const;
protected:
private:
	void setDatapinMode(uint8_t mode) const;

}; //EEPROMReaderWriter

#endif //__EEPROMREADERWRITER_H__
