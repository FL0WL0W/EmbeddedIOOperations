#include "Operations/Operation_PwmPinWrite.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_PWMPINWRITE_H
namespace EmbeddedIOOperations
{
	Operation_PwmPinWrite::Operation_PwmPinWrite(IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency) :
		_pwmService(pwmService),
		_pin(pin),
		_minFrequency(minFrequency)
	{
		_pwmService->InitPin(_pin, Out, _minFrequency);
	}

	void Operation_PwmPinWrite::Execute(float period, float pulseWidth)
	{
		_pwmService->WritePin(_pin, { period, pulseWidth });
	}

	IOperationBase *Operation_PwmPinWrite::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = Config::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_PwmPinWrite(embeddedIOServiceCollection->PwmService, pin, minFrequency);
	}
}
#endif