#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>
#include <MessageDefinitions.h>

#define SYNC_BYTE_CONSTANT 0x7E

struct RawPacket {
	uint8_t * mData;
	uint8_t mSize;
};

class Message
{
public:
	Message();
	~Message();

	bool serialize();
	virtual bool onSerialize() = 0;

	bool deserialize(uint8_t * aData, uint8_t aSize);
	virtual bool onDeserialize(uint8_t * aData, uint8_t aSize) = 0;

protected:
	uint16_t mPayloadSize;
	uint8_t* mPayload;

private:
	uint16_t crc16(const uint8_t* data_p, uint8_t length);

	uint8_t mSyncByte;
	MessageType mType;
	uint16_t mCrc;
	RawPacket mSerialized;
};

#endif // MESSAGE_H
