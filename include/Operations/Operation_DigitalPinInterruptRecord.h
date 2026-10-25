#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "Record.h"
#include "IDigitalService.h"

#ifndef OPERATION_DIGITALPININTERRUPTRECORD_H
#define OPERATION_DIGITALPININTERRUPTRECORD_H
namespace EmbeddedIOOperations
{
	class Operation_DigitalPinInterruptRecord : public OperationArchitecture::Operation<Record<bool>>
	{
	protected:
		EmbeddedIOServices::IDigitalService * const _digitalService;
		EmbeddedIOServices::ITimerService * const _timerService;
		const uint16_t _pin;
		const bool _inverted;
		Record<bool> _record;
	public:	
        Operation_DigitalPinInterruptRecord(EmbeddedIOServices::IDigitalService * const digitalService, EmbeddedIOServices::ITimerService * const timerService, uint16_t pin, bool inverted, uint16_t length);
		~Operation_DigitalPinInterruptRecord();
		Record<bool> Execute() override;
		void Sample();

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut, const ServiceRegistry *serviceRegistry);
	};
}
#endif