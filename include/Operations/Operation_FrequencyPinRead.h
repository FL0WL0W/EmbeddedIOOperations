#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "IPwmService.h"

#ifndef OPERATION_FREQUENCYPINREAD_H
#define OPERATION_FREQUENCYPINREAD_H
namespace EmbeddedIOOperations
{
	class Operation_FrequencyPinRead : public OperationArchitecture::Operation<float>
	{
	protected:
		EmbeddedIOServices::IPwmService * const _pwmService;
		const uint16_t _pin;
	public:		
        Operation_FrequencyPinRead(EmbeddedIOServices::IPwmService * const pwmService, const uint16_t pin, const uint16_t minFrequency);
		float Execute() override;

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut, const ServiceRegistry *serviceRegistry);
	};
}
#endif