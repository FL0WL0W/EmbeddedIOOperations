#include "Operations/Operation_PulseWidthPinRead.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_PULSEWIDTHPINREAD_H
namespace EmbeddedIOOperations
{
	Operation_PulseWidthPinRead::Operation_PulseWidthPinRead(IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency) :
		_pwmService(pwmService),
		_pin(pin),
		_minFrequency(minFrequency)
	{
		_pwmService->InitPin(_pin, In, _minFrequency);
	}

	float Operation_PulseWidthPinRead::Execute()
	{
		return _pwmService->ReadPin(_pin).PulseWidth;
	}

	AbstractOperation *Operation_PulseWidthPinRead::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = Config::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_PulseWidthPinRead(embeddedIOServiceCollection->PwmService, pin, minFrequency);
	}
}
#endif