/* 
* ShiftRegisterWriter.h
*
* Created: 23/10/2020 23:44:44
* Author: Maurice Hieronymus
*/

#include <Arduino.h>

#ifndef __SHIFTREGISTERWRITER_H__
#define __SHIFTREGISTERWRITER_H__

template <typename T>
class ShiftRegisterWriter
{
//variables
public:
protected:
private:
	const uint8_t dataPin;
	const uint8_t clockPin;
	const uint8_t latchPin;

//functions
public:
	ShiftRegisterWriter(const uint8_t dataPin, const uint8_t clockPin, const uint8_t latchPin);
	~ShiftRegisterWriter();
	void write(T value) const;
protected:
private:

}; //ShiftRegisterWriter

#endif //__SHIFTREGISTERWRITER_H__
