#include <Message.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

Message::Message() :
	mPayloadSize(0),
	mPayload(nullptr)
{

}

Message::~Message()
{
	mPayloadSize = 0;
	mPayload = nullptr;
}

bool Message::serialize()
{
	if (!onSerialize())
	{
		return false;
	}

	// Define packet size, and allocate memory.
	mSerialized.mSize = sizeof(mSyncByte) + sizeof(mType) + sizeof(mPayloadSize) + mPayloadSize + sizeof(mCrc);
	mSerialized.mData = (uint8_t *) malloc(mSerialized.mSize);

	// Fill packet with data.
	mSerialized.mData[MessageStructure::SYNC_BYTE_FIELD] = mSyncByte;
	mSerialized.mData[MessageStructure::TYPE_FIELD] = mType;
	mSerialized.mData[MessageStructure::PAYLOAD_SIZE_BYTE_1_FIELD] = (mPayloadSize & 0xFF);
	mSerialized.mData[MessageStructure::PAYLOAD_SIZE_BYTE_2_FIELD] = (mPayloadSize >> 8);
	memcpy(&mSerialized.mData[4], mPayload, mPayloadSize);

	// Calculate CRC-16, and fill in at the message.
	mCrc = crc16(mSerialized.mData, mSerialized.mSize - sizeof(mCrc));

	mSerialized.mData[MessageStructure::CRC_BYTE_1_FIELD + mPayloadSize] = (mCrc & 0xFF);
	mSerialized.mData[MessageStructure::CRC_BYTE_2_FIELD + mPayloadSize] = (mCrc >> 8);

	return true;
}

bool Message::deserialize(uint8_t * aData, uint8_t aSize)
{
	if (onDeserialize(aData, aSize))
	{
		return false;
	}

	return true;
}

uint16_t Message::crc16(const uint8_t* data_p, uint8_t length)
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

