/*
* AddressAndModeSetter.h
*
* Created: 24/10/2020 00:00:59
* Author: Maurice Hieronymus
*/

#include <Arduino.h>
#include "ShiftRegisterWriter.h"

#ifndef __ADDRESSANDMODESETTER_H__
#define __ADDRESSANDMODESETTER_H__

enum Mode {
	Read,
	Write
};

class AddressAndModeSetter
{
	//variables
	public:
	protected:
	private:
	const ShiftRegisterWriter<uint16_t> shiftRegisterWriter;

	//functions
	public:
	AddressAndModeSetter(const uint8_t dataPin, const uint8_t clockPin, const uint8_t latchPin);
	~AddressAndModeSetter();
	void writeToAddress(uint16_t address) const;
	void readFromAddress(uint16_t address) const;
	protected:
	private:
	void outputState(uint16_t address, Mode mode) const;

}; //AddressAndModeSetter

#endif //__ADDRESSANDMODESETTER_H__
