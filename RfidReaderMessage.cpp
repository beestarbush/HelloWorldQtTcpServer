#include <RfidReaderMessage.h>
#include <iostream>

RfidReaderMessage::RfidReaderMessage() :
Message(),
mReaderId(0),
mCardId()
{

}

bool RfidReaderMessage::onSerialize()
{
	this->mPayloadSize = sizeof(mReaderId) + sizeof(mCardId);
	this->mPayload = (uint8_t*)&mReaderId;

	return true;
}

bool RfidReaderMessage::onDeserialize(uint8_t *aData, uint8_t aSize)
{
	if (aSize < sizeof(mReaderId) + sizeof(mCardId) ||
		aSize > sizeof(mReaderId) + sizeof(mCardId))
	{
		std::cerr << "Size of payload is incorrect." << std::endl;
		return false;
	}

	mReaderId = aData[0];
	mCardId[CARD_ID_FIELD_ONE] = aData[1];
	mCardId[CARD_ID_FIELD_TWO] = aData[2];
	mCardId[CARD_ID_FIELD_THREE] = aData[3];
	mCardId[CARD_ID_FIELD_FOUR] = aData[4];

	return false;
}

void RfidReaderMessage::setReaderId(const uint8_t &aId)
{
	mReaderId = aId;
}

void RfidReaderMessage::setCardIdField(const CardIdField aField, const uint8_t aValue)
{
	mCardId[aField] = aValue;
}

uint8_t RfidReaderMessage::getReaderId() const
{
	return mReaderId;
}

uint8_t *RfidReaderMessage::getCardId()
{
	return mCardId;
}
