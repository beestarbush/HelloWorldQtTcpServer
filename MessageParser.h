#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <stdint.h>
#include <Message.h>

class MessageParser
{
public:
	MessageParser();
	bool parse(uint8_t * aData, uint8_t aSize);

	static uint16_t crc16(const uint8_t* data_p, uint8_t length);

private:
	Message * mMessage;
};

#endif // MESSAGEPARSER_H
