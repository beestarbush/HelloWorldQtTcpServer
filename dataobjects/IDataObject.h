#ifndef IDATAOBJECT_H
#define IDATAOBJECT_H

#include <stdint.h>
#include <communication/MessageDefinitions.h>
#include <QObject>

#define SYNC_BYTE_CONSTANT 0x7E

struct RawPacket {
	uint8_t * mData;
	uint8_t mSize;
};

class IDataObject : public QObject
{
	Q_OBJECT
public:
	IDataObject(QObject * aParent = nullptr);
	~IDataObject();

	bool serialize();
	virtual bool onSerialize() = 0;

	bool deserialize(uint8_t * aData, uint8_t aSize);
	virtual bool onDeserialize(uint8_t * aData, uint8_t aSize) = 0;

protected:
	uint16_t mPayloadSize;
	uint8_t* mPayload;

private:
	uint8_t mSyncByte;
	MessageType mType;
	uint16_t mCrc;
	RawPacket mSerialized;
};

#endif // IDATAOBJECT_H
