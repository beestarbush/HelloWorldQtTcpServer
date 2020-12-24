#ifndef RFIDREADERMESSAGE_H
#define RFIDREADERMESSAGE_H

#include <Message.h>

class RfidReaderMessage : public Message
{
public:
	enum CardIdField {
		CARD_ID_FIELD_ONE = 0,
		CARD_ID_FIELD_TWO,
		CARD_ID_FIELD_THREE,
		CARD_ID_FIELD_FOUR,
		CARD_ID_FIELD_COUNT
	};

	RfidReaderMessage();

	bool onSerialize();
	bool onDeserialize(uint8_t *aData, uint8_t aSize);

	void setReaderId(const uint8_t &aId);
	void setCardIdField(const CardIdField aField, const uint8_t aValue);

	uint8_t getReaderId() const;
	uint8_t * getCardId();

private:
	uint8_t mReaderId;
	uint8_t mCardId[CARD_ID_FIELD_COUNT];

};

#endif // RFIDREADERMESSAGE_H
