#ifndef NODEINFODATAOBJECT_H
#define NODEINFODATAOBJECT_H

#include <dataobjects/IDataObject.h>

class NodeInfoDataObject : public IDataObject
{
	Q_OBJECT
	Q_PROPERTY(QString qMacAddress READ getMacAddressString NOTIFY macAddressChanged)
	Q_PROPERTY(bool qReadyForUse READ getReadyForUse NOTIFY macAddressChanged)

	public:
		enum MacAddressField {
			MAC_ADDRESS_OCTET_ONE = 0,
			MAC_ADDRESS_OCTET_TWO,
			MAC_ADDRESS_OCTET_THREE,
			MAC_ADDRESS_OCTET_FOUR,
			MAC_ADDRESS_OCTET_FIVE,
			MAC_ADDRESS_OCTET_SIX,
			MAC_ADDRESS_OCTET_COUNT
		};

		NodeInfoDataObject();

		bool onSerialize();
		bool onDeserialize(uint8_t *aData, uint8_t aSize);

		void setMacAddress(const MacAddressField aField, const uint8_t aValue);
		uint8_t * getMacAddress();
		QString getMacAddressString();
		bool getReadyForUse();

	signals:
		void macAddressChanged();

	private:
		uint8_t mMacAddress[MAC_ADDRESS_OCTET_COUNT];
};

#endif // NODEINFODATAOBJECT_H
