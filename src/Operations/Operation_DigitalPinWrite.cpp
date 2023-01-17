#include "Operations/Operation_DigitalPinWrite.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_DIGITALPINWRITE_H
namespace EmbeddedIOOperations
{
	Operation_DigitalPinWrite::Operation_DigitalPinWrite(IDigitalService *digitalService, const uint16_t pin, const bool normalOn, const bool highZ) :
		_digitalService(digitalService),
		_pin(pin),
		_normalOn(normalOn),
		_highZ(highZ)
	{
		if (_highZ && _normalOn)
		{
			_digitalService->InitPin(_pin, In);
		}
		else
		{
			_digitalService->InitPin(_pin, Out);

			_digitalService->WritePin(_pin, _normalOn);
		}
	}

	void Operation_DigitalPinWrite::Execute(bool x)
	{
		if(x) 
		{
			if (_highZ && !_normalOn)
			{
				_digitalService->InitPin(_pin, In);
			}
			else
			{
				if (_highZ)
				{
					_digitalService->InitPin(_pin, Out);
				}
				
				_digitalService->WritePin(_pin, !_normalOn);
			}
		}
		else 
		{
			if (_highZ && _normalOn)
			{
				_digitalService->InitPin(_pin, In);
			}
			else
			{
				if (_highZ)
				{
					_digitalService->InitPin(_pin, Out);
				}
				
				_digitalService->WritePin(_pin, _normalOn);
			}
		}
	}

	AbstractOperation *Operation_DigitalPinWrite::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint8_t opts = Config::CastAndOffset<uint8_t>(config, sizeOut);
		const bool normalOn = opts & 0x01;
		const bool highZ = (opts >> 1) & 0x01;
		return new Operation_DigitalPinWrite(embeddedIOServiceCollection->DigitalService, pin, normalOn, highZ);
	}
}
#endif