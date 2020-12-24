#include <dataobjects/IDataObject.h>
#include <utils/Utils.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

IDataObject::IDataObject(QObject * aParent) :
	QObject(aParent),
	mPayloadSize(0),
	mPayload(nullptr)
{

}

IDataObject::~IDataObject()
{
	mPayloadSize = 0;
	mPayload = nullptr;
}

bool IDataObject::serialize()
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
	mCrc = Utils::crc16(mSerialized.mData, mSerialized.mSize - sizeof(mCrc));

	mSerialized.mData[MessageStructure::CRC_BYTE_1_FIELD + mPayloadSize] = (mCrc & 0xFF);
	mSerialized.mData[MessageStructure::CRC_BYTE_2_FIELD + mPayloadSize] = (mCrc >> 8);

	return true;
}

bool IDataObject::deserialize(uint8_t * aData, uint8_t aSize)
{
	if (!onDeserialize(aData, aSize))
	{
		return false;
	}

	return true;
}

