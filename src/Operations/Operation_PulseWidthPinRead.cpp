#include "Operations/Operation_PulseWidthPinRead.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_PULSEWIDTHPINREAD_H
namespace OperationArchitecture
{
	Operation_PulseWidthPinRead::Operation_PulseWidthPinRead( EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency)
	{
		_pwmService = pwmService;
		_pin = pin;
		_minFrequency = minFrequency;

		_pwmService->InitPin(_pin, In, _minFrequency);
	}

	float Operation_PulseWidthPinRead::Execute()
	{
		return _pwmService->ReadPin(_pin).PulseWidth;
	}

	IOperationBase *Operation_PulseWidthPinRead::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = Config::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_PulseWidthPinRead(embeddedIOServiceCollection->PwmService, pin, minFrequency);
	}
}
#endif