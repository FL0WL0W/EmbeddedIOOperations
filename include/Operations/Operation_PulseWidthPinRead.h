#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "IPwmService.h"

#ifndef OPERATION_PULSEWIDTHPINREAD_H
#define OPERATION_PULSEWIDTHPINREAD_H
namespace EmbeddedIOOperations
{
	class Operation_PulseWidthPinRead : public OperationArchitecture::Operation<float>
	{
	protected:
		EmbeddedIOServices::IPwmService *_pwmService;
		uint16_t _pin;
		uint16_t _minFrequency;
	public:		
        Operation_PulseWidthPinRead(EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency);
		float Execute() override;

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut, const ServiceRegistry *serviceRegistry);
	};
}
#endif