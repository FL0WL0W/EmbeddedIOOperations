#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "IDigitalService.h"

#ifndef OPERATION_DIGITALPINWRITE_H
#define OPERATION_DIGITALPINWRITE_H
namespace EmbeddedIOOperations
{
	class Operation_DigitalPinWrite : public OperationArchitecture::Operation<void, bool>
	{
	protected:
		EmbeddedIOServices::IDigitalService * const _digitalService;
		const uint16_t _pin;
		const bool _normalOn : 1;
		const bool _highZ : 1;
	public:		
        Operation_DigitalPinWrite(EmbeddedIOServices::IDigitalService * const digitalService, uint16_t pin, const bool normalOn, const bool highZ);
		void Execute(bool x) override;

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut, const ServiceRegistry *serviceRegistry);
	};
}
#endif