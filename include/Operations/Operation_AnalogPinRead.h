#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "IAnalogService.h"

#ifndef OPERATION_ANALOGPINREAD_H
#define OPERATION_ANALOGPINREAD_H
namespace EmbeddedIOOperations
{
	class Operation_AnalogPinRead : public OperationArchitecture::Operation<float>
	{
	protected:
		EmbeddedIOServices::IAnalogService *_analogService;
		uint16_t _pin;
	public:		
        Operation_AnalogPinRead(EmbeddedIOServices::IAnalogService *analogService, const uint16_t pin);
		float Execute() override;

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut, const ServiceRegistry *serviceRegistry);
	};
}
#endif