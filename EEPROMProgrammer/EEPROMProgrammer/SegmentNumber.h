/*
* SegmentNumber.h
*
* Created: 22-Nov-20 4:34:30 PM
*  Author: hieronymusma
*/

#ifndef SEGMENTNUMBER_H_
#define SEGMENTNUMBER_H_

namespace {
	constexpr uint8_t E = 1 << 0;
	constexpr uint8_t D = 1 << 1;
	constexpr uint8_t DP = 1 << 2;
	constexpr uint8_t C = 1 << 3;
	constexpr uint8_t G = 1 << 4;
	constexpr uint8_t B = 1 << 5;
	constexpr uint8_t F = 1 << 6;
	constexpr uint8_t A = 1 << 7;
}

namespace SegmentNumber {
	
	constexpr uint8_t Zero = A | B | C | D | E | F;
	constexpr uint8_t One = B | C;
	constexpr uint8_t Two = A | B | G | E | D;
	constexpr uint8_t Three = A | B | G | C | D;
	constexpr uint8_t Four = F | G | B | C;
	constexpr uint8_t Five = A | F | G | C | D;
	constexpr uint8_t Six = A | F | G | E | C | D;
	constexpr uint8_t Seven = A | B | C;
	constexpr uint8_t Eight = A | B | C | D | E | F | G;
	constexpr uint8_t Nine = A | F | B | G | C;
	
	constexpr uint8_t Minus = G;
	
	constexpr uint8_t Number[] = {
		Zero,
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine
	};
	
	constexpr uint8_t Nothing = 0;
}

#endif /* SEGMENTNUMBER_H_ */