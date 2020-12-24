#include <dataobjects/RfidReaderDataObject.h>

RfidReaderDataObject::RfidReaderDataObject() :
IDataObject(),
mReaderId(0),
mCardId()
{

}

bool RfidReaderDataObject::onSerialize()
{
	this->mPayloadSize = sizeof(mReaderId) + sizeof(mCardId);
	this->mPayload = (uint8_t*)&mReaderId;

	return true;
}

bool RfidReaderDataObject::onDeserialize(uint8_t *aData, uint8_t aSize)
{
	if (aSize < sizeof(mReaderId) + sizeof(mCardId) ||
		aSize > sizeof(mReaderId) + sizeof(mCardId))
	{
		return false;
	}

	mReaderId = aData[0];
	mCardId[CARD_ID_FIELD_ONE] = aData[1];
	mCardId[CARD_ID_FIELD_TWO] = aData[2];
	mCardId[CARD_ID_FIELD_THREE] = aData[3];
	mCardId[CARD_ID_FIELD_FOUR] = aData[4];

	return true;
}

void RfidReaderDataObject::setReaderId(const uint8_t &aId)
{
	mReaderId = aId;
}

void RfidReaderDataObject::setCardIdField(const CardIdField aField, const uint8_t aValue)
{
	mCardId[aField] = aValue;
}

uint8_t RfidReaderDataObject::getReaderId() const
{
	return mReaderId;
}

QString RfidReaderDataObject::getReaderIdString()
{
	return QString::number(mReaderId);
}

uint8_t *RfidReaderDataObject::getCardId()
{
	return mCardId;
}

QString RfidReaderDataObject::getCardIdString()
{
	QString lCardId;
	for (auto lCardIdPart : mCardId)
	{
		lCardId += QString::number(lCardIdPart, 16);
	}
	return lCardId;
}
