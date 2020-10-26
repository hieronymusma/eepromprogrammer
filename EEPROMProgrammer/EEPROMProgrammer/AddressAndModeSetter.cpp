/*
* AddressAndModeSetter.cpp
*
* Created: 24/10/2020 00:00:59
* Author: Maurice Hieronymus
*/


#include "AddressAndModeSetter.h"

void AddressAndModeSetter::outputState(const uint16_t address, const Mode mode) const
{
	uint16_t state = address & 0x1ffff;
	state |= mode == Read ? 0x0 : 0x2000;
	shiftRegisterWriter.write(state);
}

// default constructor
AddressAndModeSetter::AddressAndModeSetter(const uint8_t dataPin, const uint8_t clockPin, const uint8_t latchPin)
: shiftRegisterWriter(ShiftRegisterWriter<uint16_t>(dataPin, clockPin, latchPin))
{
} //AddressAndModeSetter

// default destructor
AddressAndModeSetter::~AddressAndModeSetter()
{
} //~AddressAndModeSetter

void AddressAndModeSetter::writeToAddress(const uint16_t address) const
{
	outputState(address, Write);
}

void AddressAndModeSetter::readFromAddress(const uint16_t address) const
{
	outputState(address, Write);
	outputState(address, Read);
}
