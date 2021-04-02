#include "Operations/Operation_DutyCyclePinRead.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_DUTYCYCLEPINREAD_H
namespace OperationArchitecture
{
	Operation_DutyCyclePinRead::Operation_DutyCyclePinRead( EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency)
	{
		_pwmService = pwmService;
		_pin = pin;
		_minFrequency = minFrequency;

		_pwmService->InitPin(_pin, In, _minFrequency);
	}

	float Operation_DutyCyclePinRead::Execute()
	{
		const PwmValue value = _pwmService->ReadPin(_pin);
		return value.PulseWidth / value.Period;
	}

	IOperationBase *Operation_DutyCyclePinRead::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = Config::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_DutyCyclePinRead(embeddedIOServiceCollection->PwmService, pin, minFrequency);
	}
}
#endif