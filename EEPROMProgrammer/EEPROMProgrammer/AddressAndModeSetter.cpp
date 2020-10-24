/*
* AddressAndModeSetter.cpp
*
* Created: 24/10/2020 00:00:59
* Author: Maurice Hieronymus
*/


#include "AddressAndModeSetter.h"

void AddressAndModeSetter::setAddress(uint16_t address, bool outputEnable) const {
		// Output enable is low active
		
		uint16_t target = address & 0x1fff;
		
		// 4 bit is outputEnable bit
		target |= outputEnable ? 0x0 : 0x2000;
		
		this->shiftRegisterWriter.write(target);
}

// default constructor
AddressAndModeSetter::AddressAndModeSetter(const uint8_t dataPin, const uint8_t clockPin, const uint8_t latchPin)
: dataPin(dataPin), clockPin(clockPin), latchPin(latchPin), shiftRegisterWriter(ShiftRegisterWriter<uint16_t>(clockPin, dataPin, latchPin))
{
} //AddressAndModeSetter

// default destructor
AddressAndModeSetter::~AddressAndModeSetter()
{
} //~AddressAndModeSetter
