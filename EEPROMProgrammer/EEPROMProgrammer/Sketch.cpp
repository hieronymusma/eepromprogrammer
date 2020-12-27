#include <Arduino.h>
#include "EEPROMWriter.h"
#include "UsedPorts.h"
#include "OutputmoduleWriter.h"
#include "InstructionWriter.h"

void setup() {
	Serial.begin(57600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	EEPROMWriter writer(Ports::SHIFT_DATA, Ports::SHIFT_CLK, Ports::SHIFT_LATCH, Ports::EEPROM_WE, Ports::EEPROM_DATAPINS);
	// OutputmoduleWriter outputWriter(writer);
	InstructionWriter instructionWriter(writer, InstructionWriter::Side::Left);
	
	delay(5000);
	
	writer.printData(instructionWriter.bytesToWrite);
	
	Serial.println(F("Start writing!"));
	
	bool isSuccessful = instructionWriter.write();
	
	if (!isSuccessful) {
		Serial.println(F("Error writing data!"));
	} else {
		Serial.println(F("Successful!"));
	}
	
	Serial.println(F("EOF"));
}

void loop() { }