/* 
* InstructionWriter.h
*
* Created: 27/12/2020 16:10:12
* Author: Maurice Hieronymus
*/


#ifndef __INSTRUCTIONWRITER_H__
#define __INSTRUCTIONWRITER_H__

#include "EEPROMWriter.h"


class InstructionWriter
{
//variables
public:
const size_t bytesToWrite = 128; // 2 ^ 7 (3 Microcounter, 4 Instruction)

enum Side {
	Left,
	Right
	};

protected:
private:
const EEPROMWriter& writer;
const InstructionWriter::Side side;

//functions
public:
	InstructionWriter(const EEPROMWriter& writer, const InstructionWriter::Side side) : writer(writer), side(side) { }
	~InstructionWriter() { }
	bool write();
	bool writeInstruction(const uint8_t instruction, const uint16_t ui3, const uint16_t ui4, const uint16_t ui5);
	bool writeInstructionFetch();
	uint8_t getSideValue(const uint16_t value);
protected:
private:
	InstructionWriter( const InstructionWriter &c );
	InstructionWriter& operator=( const InstructionWriter &c );

}; //InstructionWriter

#endif //__INSTRUCTIONWRITER_H__
