#include "Operations/Operation_PwmPinWrite.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_PWMPINWRITE_H
namespace OperationArchitecture
{
	Operation_PwmPinWrite::Operation_PwmPinWrite( EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency)
	{
		_pwmService = pwmService;
		_pin = pin;
		_minFrequency = minFrequency;

		_pwmService->InitPin(_pin, Out, _minFrequency);
	}

	void Operation_PwmPinWrite::Execute(float period, float pulseWidth)
	{
		_pwmService->WritePin(_pin, { period, pulseWidth });
	}

	IOperationBase *Operation_PwmPinWrite::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const uint16_t minFrequency = Config::CastAndOffset<uint16_t>(config, sizeOut);
		return new Operation_PwmPinWrite(embeddedIOServiceCollection->PwmService, pin, minFrequency);
	}
}
#endif