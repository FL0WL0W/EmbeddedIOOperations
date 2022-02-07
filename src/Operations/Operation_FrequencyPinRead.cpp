#include "Operations/Operation_FrequencyPinRead.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_FREQUENCYPINREAD_H
namespace EmbeddedIOOperations
{
	Operation_FrequencyPinRead::Operation_FrequencyPinRead( IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency) :
		_pwmService(pwmService),
		_pin(pin),
		_minFrequency(minFrequency)
	{
		_pwmService->InitPin(_pin, In, _minFrequency);
	}

	float Operation_FrequencyPinRead::Execute()
	{
		return 1 / _pwmService->ReadPin(_pin).Period;
	}

	IOperationBase *Operation_FrequencyPinRead::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = Config::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_FrequencyPinRead(embeddedIOServiceCollection->PwmService, pin, minFrequency);
	}
}
#endif