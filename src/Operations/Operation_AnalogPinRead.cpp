#include "Operations/Operation_AnalogPinRead.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_ANALOGPINREAD_H
namespace OperationArchitecture
{
	Operation_AnalogPinRead::Operation_AnalogPinRead( EmbeddedIOServices::IAnalogService *analogService, const uint16_t pin)
	{
		_analogService = analogService;
		_pin = pin;

		_analogService->InitPin(_pin);
	}

	float Operation_AnalogPinRead::Execute()
	{
		return _analogService->ReadPin(_pin);
	}

	IOperationBase *Operation_AnalogPinRead::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut)
	{
		return new Operation_AnalogPinRead(embeddedIOServiceCollection->AnalogService, Config::CastAndOffset<uint16_t>(config, sizeOut));
	}
}
#endif