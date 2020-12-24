#include "MessageParser.h"
#include "MessageDefinitions.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <RfidReaderMessage.h>

MessageParser::MessageParser() :
	mMessage(nullptr)
{

}

bool MessageParser::parse(uint8_t *aData, uint8_t aSize)
{
	if (!aData || aData == nullptr)
	{
		std::cerr << "Data is not valid, referencing to NULL/nullptr" << std::endl;
		return false;
	}

	uint8_t lSize = aSize;
	if (lSize < MessageStructure::FIELD_COUNT) // sync_byte (1) + type(1) + payloadsize (2) + crc (2)
	{
		std::cerr << "Size of raw data is incorrect." << std::endl;
		return false;
	}

	uint8_t * lData = (uint8_t *) malloc(lSize);
	memcpy(lData, aData, aSize);

	if (aData[MessageStructure::SYNC_BYTE_FIELD] != SYNC_BYTE_CONSTANT)
	{
		std::cerr << "Sync byte not found in data." << std::endl;
		return false;
	}

	if (aData[MessageStructure::TYPE_FIELD] == MessageType::NONE ||
		aData[MessageStructure::TYPE_FIELD] >= MessageType::MESSAGE_TYPE_COUNT)
	{
		std::cerr << "Message type incorrect." << std::endl;
		return false;
	}

	uint16_t lPayloadSize = ((uint16_t)aData[MessageStructure::PAYLOAD_SIZE_BYTE_2_FIELD] << 8) | aData[MessageStructure::PAYLOAD_SIZE_BYTE_1_FIELD];
	uint16_t lReceivedCrc = ((uint16_t)aData[MessageStructure::CRC_BYTE_2_FIELD + lPayloadSize] << 8) | aData[MessageStructure::CRC_BYTE_1_FIELD + lPayloadSize];

	uint16_t lCalculatedCrc = MessageParser::crc16(lData, lSize - sizeof(uint16_t));

	if (lReceivedCrc != lCalculatedCrc)
	{
		std::cerr << "CRC is incorrect." << std::endl;
		return false;
	}

	switch(static_cast<MessageType>(aData[MessageStructure::TYPE_FIELD]))
	{
		case MessageType::NONE:
		{
			break;
		}
		case MessageType::RAW_MESSAGE_TYPE:
		{
			break;
		}
		case MessageType::RFID_READER_MESSAGE_TYPE:
		{
			mMessage = new RfidReaderMessage;
			if (!mMessage->deserialize(lData, lPayloadSize))
			{
				std::cerr << "Failed to deserialize RFID reader message.";
				return false;
			}
			break;
		}
		default:
		{
			break;
		}
	}

	return true;
}


uint16_t MessageParser::crc16(const uint8_t* data_p, uint8_t length)
{
	uint8_t x;
	uint16_t crc = 0xFFFF;

	while (length--){
		x = crc >> 8 ^ *data_p++;
		x ^= x>>4;
		crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
	}
	return crc;
}
