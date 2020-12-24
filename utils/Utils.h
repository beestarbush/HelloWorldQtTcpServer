#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

class Utils
{
	public:
		static uint16_t crc16(const uint8_t* data_p, uint8_t length);

	private:
		Utils();
};

#endif // UTILS_H
