#include "Operations/Operation_CANCRCJ1850.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_CANCRCJ1850_H
namespace EmbeddedIOOperations
{
	static constexpr std::array<uint8_t, 256> makeCRCJ1850Table() {
		std::array<uint8_t, 256> table{};
		for (int i = 0; i < 256; ++i) {
			uint8_t crc = static_cast<uint8_t>(i);
			for (int bit = 0; bit < 8; ++bit) {
				crc = (crc & 0x80)  ? static_cast<uint8_t>((crc << 1) ^ 0x1D)
									: static_cast<uint8_t>(crc << 1);
			}
			table[i] = crc;
		}
		return table;
	}

	static constexpr auto crcJ1850Table = makeCRCJ1850Table();

	Operation_CANCRCJ1850::Operation_CANCRCJ1850(const uint8_t start, const uint8_t length, const uint8_t offset) :
		_start(start),
		_length(length),
		_offset(offset)
	{ }

	void Operation_CANCRCJ1850::AbstractExecute(Variable **variables)
	{
		//this is fun optimization, we use the same input variable as the output variable
		CANData_t data = *variables[0];

		//_start is offset in bits, we need to go through bit by bit creating a byte and then calculating the CRC
		uint8_t crc = 0xFF;
		for(uint8_t i = _start; i < _start + _length; i+=8)
		{
			const uint8_t byteIndex = i / 8;
			const uint8_t bitIndex = i % 8;
			const uint8_t byteValue = bitIndex == 0 ? data.Data[byteIndex] : (data.Data[byteIndex] >> bitIndex) | (data.Data[byteIndex + 1] << (8 - bitIndex)); 
			crc = crcJ1850Table[crc ^ byteValue];
		}

		//now place the crc into the data at the offset
		const uint8_t crcByteIndex = _offset / 8;
		const uint8_t crcBitIndex = _offset % 8;
		if(crcBitIndex == 0)
		{
			data.Data[crcByteIndex] = crc;
		}
		else
		{
			data.Data[crcByteIndex] &= ~(0xFF << crcBitIndex);
			data.Data[crcByteIndex] |= (crc << crcBitIndex);
			data.Data[crcByteIndex + 1] &= ~(0xFF >> (8 - crcBitIndex));
			data.Data[crcByteIndex + 1] |= (crc >> (8 - crcBitIndex));
		}

		*variables[0] = data;
	}

	AbstractOperation *Operation_CANCRCJ1850::Create(const void *config, size_t  &sizeOut)
	{
		const uint8_t start = Config::CastAndOffset<uint8_t>(config, sizeOut);
		const uint8_t length = Config::CastAndOffset<uint8_t>(config, sizeOut);
		const uint8_t offset = Config::CastAndOffset<uint8_t>(config, sizeOut);
		return new Operation_CANCRCJ1850(start, length, offset);
	}
}
#endif