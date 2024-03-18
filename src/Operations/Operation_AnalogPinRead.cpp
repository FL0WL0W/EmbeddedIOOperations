#include "Operations/Operation_AnalogPinRead.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_ANALOGPINREAD_H
namespace EmbeddedIOOperations
{
	Operation_AnalogPinRead::Operation_AnalogPinRead( IAnalogService *analogService, const uint16_t pin) :
		_analogService(analogService),
		_pin(pin)
	{
		_analogService->InitPin(_pin);
	}

	float Operation_AnalogPinRead::Execute()
	{
		return _analogService->ReadPin(_pin);
	}

	AbstractOperation *Operation_AnalogPinRead::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		return new Operation_AnalogPinRead(embeddedIOServiceCollection->AnalogService, Config::CastAndOffset<uint16_t>(config, sizeOut));
	}
}
#endif