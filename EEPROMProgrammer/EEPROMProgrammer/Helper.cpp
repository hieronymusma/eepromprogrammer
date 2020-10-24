/* 
* Helper.cpp
*
* Created: 24/10/2020 18:00:00
* Author: Maurice Hieronymus
*/


#include "Helper.h"

void Helper::ExecuteNops(uint8_t times)
{
	for(int16_t i = times; i > 0; i--) {
		_NOP();
	}
}
