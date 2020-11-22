/* 
* OutputmoduleWriter.h
*
* Created: 22-Nov-20 5:37:12 PM
* Author: hieronymusma
*/


#ifndef __OUTPUTMODULEWRITER_H__
#define __OUTPUTMODULEWRITER_H__

#include "EEPROMWriter.h"

class OutputmoduleWriter
{
//variables
public:
protected:
private:
const EEPROMWriter& writer;

//functions
public:
	OutputmoduleWriter(const EEPROMWriter& writer);
	bool write(uint16_t max);
	~OutputmoduleWriter();
protected:
private:
	OutputmoduleWriter( const OutputmoduleWriter &c );
	OutputmoduleWriter& operator=( const OutputmoduleWriter &c );

}; //OutputmoduleWriter

#endif //__OUTPUTMODULEWRITER_H__
