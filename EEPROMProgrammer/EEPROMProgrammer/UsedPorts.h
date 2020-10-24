/*
 * GlobalConstants.h
 *
 * Created: 24/10/2020 16:48:40
 *  Author: Maurice Hieronymus
 */ 


#ifndef GLOBALCONSTANTS_H_
#define GLOBALCONSTANTS_H_

namespace Ports {
	uint8_t const SHIFT_DATA = 2;
	uint8_t const SHIFT_CLK = 3;
	uint8_t const SHIFT_LATCH = 4;
	
	uint8_t const EEPROM_D0 = 5;
	uint8_t const EEPROM_D7 = 12;
	uint8_t const EEPROM_DATAPINS[8] = { 5, 6, 7, 8, 9, 10, 11, 12 };
	uint8_t const EEPROM_WE = 13;
}

#endif /* GLOBALCONSTANTS_H_ */