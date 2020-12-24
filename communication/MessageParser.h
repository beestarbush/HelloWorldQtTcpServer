#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <stdint.h>
#include <dataobjects/IDataObject.h>
#include "communication/MessageDefinitions.h"
#include <map>

class MessageParser
{
public:
	MessageParser();

	void registerDataObject(MessageType aType, IDataObject * aDataObject);
	bool parse(uint8_t * aData, uint8_t aSize);

private:
	std::map<MessageType, IDataObject *> mDataObjects;
};

#endif // MESSAGEPARSER_H
