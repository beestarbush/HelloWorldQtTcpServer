#include "NodeInfoDataObject.h"

NodeInfoDataObject::NodeInfoDataObject() :
	IDataObject(),
	mMacAddress()
{
}

bool NodeInfoDataObject::onSerialize()
{
	this->mPayloadSize = sizeof(mMacAddress);
	this->mPayload = (uint8_t*)&mMacAddress;

	return true;
}

bool NodeInfoDataObject::onDeserialize(uint8_t * aData, uint8_t aSize)
{
	if (aSize < sizeof(mMacAddress) ||
		aSize > sizeof(mMacAddress))
	{
		return false;
	}

	setMacAddress(MAC_ADDRESS_OCTET_ONE, aData[0]);
	setMacAddress(MAC_ADDRESS_OCTET_TWO, aData[1]);
	setMacAddress(MAC_ADDRESS_OCTET_THREE, aData[2]);
	setMacAddress(MAC_ADDRESS_OCTET_FOUR, aData[3]);
	setMacAddress(MAC_ADDRESS_OCTET_FIVE, aData[4]);
	setMacAddress(MAC_ADDRESS_OCTET_SIX, aData[5]);

	return true;
}

void NodeInfoDataObject::setMacAddress(const NodeInfoDataObject::MacAddressField aField, const uint8_t aValue)
{
	mMacAddress[aField] = aValue;
	emit macAddressChanged();
}

uint8_t * NodeInfoDataObject::getMacAddress()
{
	return mMacAddress;
}

QString NodeInfoDataObject::getMacAddressString()
{
	QString lMacAddress;
	for (auto lPart : mMacAddress)
	{
		lMacAddress += QString::number(lPart, 16);
	}
	return lMacAddress;
}

bool NodeInfoDataObject::getReadyForUse()
{
	uint8_t lEmptyMac[MAC_ADDRESS_OCTET_COUNT] = { 0 };
	if (memcmp(mMacAddress, lEmptyMac, MAC_ADDRESS_OCTET_COUNT) == 0)
	{
		return false;
	}

	return true;
}
