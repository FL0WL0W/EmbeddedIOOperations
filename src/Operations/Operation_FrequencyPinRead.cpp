#include "Operations/Operation_FrequencyPinRead.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_FREQUENCYPINREAD_H
namespace OperationArchitecture
{
	Operation_FrequencyPinRead::Operation_FrequencyPinRead( EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency)
	{
		_pwmService = pwmService;
		_pin = pin;
		_minFrequency = minFrequency;

		_pwmService->InitPin(_pin, In, _minFrequency);
	}

	float Operation_FrequencyPinRead::Execute()
	{
		return 1 / _pwmService->ReadPin(_pin).Period;
	}

	IOperationBase *Operation_FrequencyPinRead::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = Config::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_FrequencyPinRead(embeddedIOServiceCollection->PwmService, pin, minFrequency);
	}
}
#endif