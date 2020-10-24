/* 
* ShiftRegisterWriter.cpp
*
* Created: 23/10/2020 23:44:44
* Author: Maurice Hieronymus
*/


#include "ShiftRegisterWriter.h"

template <typename T>
void ShiftRegisterWriter<T>::write(T value) const {
	
	auto byteSize = sizeof(T) - 1;
	
	for (int8_t bytePosition = byteSize; bytePosition >= 0; bytePosition--) {
		uint8_t byteToWrite = value >> (8 * bytePosition);
		shiftOut(dataPin, clockPin, MSBFIRST, byteToWrite);
	}
	
	digitalWrite(latchPin, LOW);
	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin, LOW);
}

// default constructor
template <typename T>
ShiftRegisterWriter<T>::ShiftRegisterWriter(const uint8_t clockPin, const uint8_t dataPin, const uint8_t latchPin)
: clockPin(clockPin), dataPin(dataPin), latchPin(latchPin)
{
	digitalWrite(latchPin, LOW);
	
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
} //ShiftRegisterWriter

// default destructor
template <typename T>
ShiftRegisterWriter<T>::~ShiftRegisterWriter()
{
} //~ShiftRegisterWriter

template class ShiftRegisterWriter<uint8_t>;
template class ShiftRegisterWriter<uint16_t>;
template class ShiftRegisterWriter<uint32_t>;
template class ShiftRegisterWriter<uint64_t>;