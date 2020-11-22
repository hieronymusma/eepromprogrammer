/* 
* OutputmoduleWriter.cpp
*
* Created: 22-Nov-20 5:37:12 PM
* Author: hieronymusma
*/


#include "OutputmoduleWriter.h"
#include "SegmentNumber.h"

// default constructor
OutputmoduleWriter::OutputmoduleWriter(const EEPROMWriter& writer) : writer(writer)
{
} //OutputmoduleWriter

bool OutputmoduleWriter::write(uint16_t max)
{
	bool isSuccessful = true;
	
	uint16_t tenthAddressBit = 1 << 8;
	uint16_t hundredAddressBit = 1 << 9;
	
	for(uint16_t number = 0; number < max; number++) {
		char buf[20];
		sprintf(buf, "Write %u", number);
		Serial.println(buf);
		
		uint8_t oneth = number % 100 % 10;
		uint8_t tenth = number % 100 / 10;
		uint8_t hundreds = number / 100;
		
		// ONES
		uint8_t dataOnes = SegmentNumber::Number[oneth];
		isSuccessful = isSuccessful ? writer.write(dataOnes, number) : false;
		
		// TENTH
		uint8_t dataTenths = SegmentNumber::Number[tenth];
		if (number < 10) {
			dataTenths = SegmentNumber::Nothing;
		}
		isSuccessful = isSuccessful ? writer.write(dataTenths, number | tenthAddressBit) : false;
		
		// HUNDREDS
		uint8_t dataHundreds = SegmentNumber::Number[hundreds];
		if (number < 100) {
			dataHundreds = SegmentNumber::Nothing;
		}
		isSuccessful = isSuccessful ? writer.write(dataHundreds, number | hundredAddressBit) : false;
	}
	
	return isSuccessful;
}

// default destructor
OutputmoduleWriter::~OutputmoduleWriter()
{
} //~OutputmoduleWriter
