#include "Operations/Operation_DutyCyclePinRead.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_DUTYCYCLEPINREAD_H
namespace OperationArchitecture
{
	Operation_DutyCyclePinRead::Operation_DutyCyclePinRead( EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency) :
		_pwmService(pwmService),
		_pin(pin),
		_minFrequency(minFrequency)
	{
		_pwmService->InitPin(_pin, In, _minFrequency);
	}

	float Operation_DutyCyclePinRead::Execute()
	{
		const PwmValue value = _pwmService->ReadPin(_pin);
		return value.PulseWidth / value.Period;
	}

	IOperationBase *Operation_DutyCyclePinRead::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = Config::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_DutyCyclePinRead(embeddedIOServiceCollection->PwmService, pin, minFrequency);
	}
}
#endif