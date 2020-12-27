/* 
* InstructionWriter.cpp
*
* Created: 27/12/2020 16:10:12
* Author: Maurice Hieronymus
*/


#include "InstructionWriter.h"

static const uint16_t HLT =		0b1000000000000000;
static const uint16_t MI =		0b0100000000000000;
static const uint16_t RE =		0b0010000000000000;
static const uint16_t RM =		0b0001000000000000;
static const uint16_t IO =		0b0000100000000000;
static const uint16_t II =		0b0000010000000000;
static const uint16_t AI =		0b0000001000000000;
static const uint16_t AO =		0b0000000100000000;

static const uint16_t SO =		0b0000000010000000;
static const uint16_t SUB =		0b0000000001000000;
static const uint16_t BI =		0b0000000000100000;
static const uint16_t OI =		0b0000000000010000;
static const uint16_t CE =		0b0000000000001000;
static const uint16_t CO =		0b0000000000000100;
static const uint16_t JMP =		0b0000000000000010;
static const uint16_t FLAG =	0b0000000000000001;

bool InstructionWriter::write() {
	
	writer.erase(bytesToWrite);
	
	if (writeInstructionFetch() == false) {
		return false;
	}
	
	bool success[] = {
		writeInstruction(0b0000, IO | MI, RE | AI, 0), // LDA
		writeInstruction(0b0001, IO | MI, RE | BI, SO | AI), // ADD to A
		writeInstruction(0b0010, AO | OI, 0, 0), // OUT A
		writeInstruction(0b0011, HLT, 0, 0) // HLT
	};
	
	for(size_t i = 0; i < sizeof(success); i++) {
		if (success[i] == false) {
			return false;
		}
	}
	
	return true;
}

bool InstructionWriter::writeInstruction(const uint8_t instruction, const uint16_t ui3, const uint16_t ui4, const uint16_t ui5) {
	bool success1 = writer.write(getSideValue(ui3), instruction + 2);
	bool success2 = writer.write(getSideValue(ui4), instruction + 3);
	bool success3 = writer.write(getSideValue(ui5), instruction + 4);
	
	if (success1 == false || success2 == false || success3 == false) {
		Serial.println(F("Error writing instruction"));
		return false;
	}
	return true;
}


bool InstructionWriter::writeInstructionFetch() {
	for(size_t instructionStart = 0; instructionStart < bytesToWrite; instructionStart += 8) {
		bool success1 = writer.write(getSideValue(CO | MI), instructionStart);
		bool success2 = writer.write(getSideValue(CE | RE | II), instructionStart + 1);
		if (success1 == false || success2 == false)
			Serial.println(F("Error writing Instruction fetch."));
			return false;
	}
	return true;
}

uint8_t InstructionWriter::getSideValue(const uint16_t value) {
	if (side == InstructionWriter::Side::Left) {
		return (value >> 8) & 0x0000FFFF;
	} else if (side == InstructionWriter::Side::Right) {
		return value & 0x0000FFFF;
	}
	return 0;
}