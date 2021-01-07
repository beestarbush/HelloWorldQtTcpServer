#ifndef RFIDREADERDATAOBJECT_H
#define RFIDREADERDATAOBJECT_H

#include <dataobjects/IDataObject.h>

class RfidReaderDataObject : public IDataObject
{
	Q_OBJECT
	Q_PROPERTY(QString qReaderId READ getReaderIdString NOTIFY readerIdChanged)
	Q_PROPERTY(QString qCardId READ getCardIdString NOTIFY cardIdChanged)

	public:
		enum CardIdField {
			CARD_ID_FIELD_ONE = 0,
			CARD_ID_FIELD_TWO,
			CARD_ID_FIELD_THREE,
			CARD_ID_FIELD_FOUR,
			CARD_ID_FIELD_COUNT
		};

		RfidReaderDataObject();

		bool onSerialize();
		bool onDeserialize(uint8_t *aData, uint8_t aSize);

		void setReaderId(const uint8_t &aId);
		uint8_t getReaderId() const;
		QString getReaderIdString();

		void setCardIdField(const CardIdField aField, const uint8_t aValue);
		uint8_t * getCardId();
		QString getCardIdString();
		bool isCardIdEmpty();

	signals:
		void readerIdChanged();
		void cardIdChanged();

	private:
		uint8_t mReaderId;
		uint8_t mCardId[CARD_ID_FIELD_COUNT];

};

#endif // RFIDREADERDATAOBJECT_H
