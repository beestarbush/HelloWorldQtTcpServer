#include "communication/MessageParser.h"
#include <string.h>
#include <utils/Utils.h>
#include <QDebug>

MessageParser::MessageParser() :
	mDataObjects()
{

}

void MessageParser::registerDataObject(MessageType aType, IDataObject * aDataObject)
{
	mDataObjects.insert(std::pair<MessageType, IDataObject*>(aType, aDataObject));
}

bool MessageParser::parse(uint8_t *aData, uint8_t aSize)
{
	if (!aData || aData == nullptr)
	{
		qDebug() << "Data is not valid, referencing to NULL/nullptr";
		return false;
	}

	uint8_t lSize = aSize;
	if (lSize < MessageStructure::FIELD_COUNT) // sync_byte (1) + type(1) + payloadsize (2) + crc (2)
	{
		qDebug() << "Size of raw data is incorrect.";
		return false;
	}

	if (aData[MessageStructure::SYNC_BYTE_FIELD] != SYNC_BYTE_CONSTANT)
	{
		qDebug() << "Sync byte not found in data.";
		return false;
	}

	if (aData[MessageStructure::TYPE_FIELD] == MessageType::NONE ||
		aData[MessageStructure::TYPE_FIELD] >= MessageType::MESSAGE_TYPE_COUNT)
	{
		qDebug() << "Message type incorrect.";
		return false;
	}

	uint16_t lPayloadSize = ((uint16_t)aData[MessageStructure::PAYLOAD_SIZE_BYTE_2_FIELD] << 8) | aData[MessageStructure::PAYLOAD_SIZE_BYTE_1_FIELD];
	uint16_t lReceivedCrc = ((uint16_t)aData[MessageStructure::CRC_BYTE_2_FIELD + lPayloadSize] << 8) | aData[MessageStructure::CRC_BYTE_1_FIELD + lPayloadSize];

	uint8_t * lData = (uint8_t *) malloc(lSize);
	memcpy(lData, aData, aSize);
	uint16_t lCalculatedCrc = Utils::crc16(lData, lSize - sizeof(uint16_t));

	if (lReceivedCrc != lCalculatedCrc)
	{
		qDebug() << "CRC is incorrect.";
		return false;
	}

	MessageType lType = static_cast<MessageType>(aData[MessageStructure::TYPE_FIELD]);
	if (mDataObjects.find(lType) == mDataObjects.end())
	{
		qDebug() << "No object registered for this datatype.";
		return false;
	}
	if (!mDataObjects[lType]->deserialize(lData, lPayloadSize))
	{
		qDebug() << "Failed to deserialize dataobject for type: " << lType;
		return false;
	}

	return true;
}

