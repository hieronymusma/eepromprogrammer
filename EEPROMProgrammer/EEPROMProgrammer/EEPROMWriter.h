/* 
* EEPROMWriter.h
*
* Created: 24/10/2020 19:42:34
* Author: Maurice Hieronymus
*/

#include "EEPROMReaderWriter.h"

#ifndef __EEPROMWRITER_H__
#define __EEPROMWRITER_H__


class EEPROMWriter
{
//variables
public:
protected:
private:
const EEPROMReaderWriter eepromReaderWriter;

//functions
public:
	EEPROMWriter(const uint8_t shiftDataPin, const uint8_t shiftClockPin, const uint8_t shiftLatchPin, const uint8_t writeEnablePin, const uint8_t (&dataPins)[8]);
	~EEPROMWriter();
	void writeData(uint8_t *data, size_t len) const;
	void printData(size_t bytes) const;
protected:
private:
	bool validate(uint8_t *data, size_t len) const;

}; //EEPROMWriter

#endif //__EEPROMWRITER_H__
