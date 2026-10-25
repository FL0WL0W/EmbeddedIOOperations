#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "IDigitalService.h"

#ifndef OPERATION_DIGITALPINREAD_H
#define OPERATION_DIGITALPINREAD_H
namespace EmbeddedIOOperations
{
	class Operation_DigitalPinRead : public OperationArchitecture::Operation<bool>
	{
	protected:
		EmbeddedIOServices::IDigitalService * const _digitalService;
		const uint16_t _pin;
		const bool _inverted;
	public:		
        Operation_DigitalPinRead(EmbeddedIOServices::IDigitalService * const digitalService, uint16_t pin, bool inverted);
		bool Execute() override;

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut, const ServiceRegistry *serviceRegistry);
	};
}
#endif