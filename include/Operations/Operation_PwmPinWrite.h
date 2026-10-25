#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "IPwmService.h"

#ifndef OPERATION_PWMPINWRITE_H
#define OPERATION_PWMPINWRITE_H
namespace EmbeddedIOOperations
{
	class Operation_PwmPinWrite : public OperationArchitecture::Operation<void, float, float>
	{
	protected:
		EmbeddedIOServices::IPwmService * const _pwmService;
		const uint16_t _pin;
	public:		
        Operation_PwmPinWrite(EmbeddedIOServices::IPwmService * const pwmService, const uint16_t pin, const uint16_t minFrequency);
		void Execute(float period, float pulseWidth) override;

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut, const ServiceRegistry *serviceRegistry);
	};
}
#endif