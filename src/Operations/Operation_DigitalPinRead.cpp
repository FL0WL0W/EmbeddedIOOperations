#include "Operations/Operation_DigitalPinRead.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_DIGITALPINREAD_H
namespace OperationArchitecture
{
	Operation_DigitalPinRead::Operation_DigitalPinRead(EmbeddedIOServices::IDigitalService *digitalService, const uint16_t pin, const bool inverted)
	{
		_digitalService = digitalService;
		_pin = pin;
		_inverted = inverted;

		_digitalService->InitPin(_pin, In);
	}

	bool Operation_DigitalPinRead::Execute()
	{
		if (_inverted)
			return !_digitalService->ReadPin(_pin);
		return _digitalService->ReadPin(_pin);
	}

	IOperationBase *Operation_DigitalPinRead::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const bool inverted = Config::CastAndOffset<bool>(config, sizeOut);
		return new Operation_DigitalPinRead(embeddedIOServiceCollection->DigitalService, pin, inverted);
	}
}
#endif