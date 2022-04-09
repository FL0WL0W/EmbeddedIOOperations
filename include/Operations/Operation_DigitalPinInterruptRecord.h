#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"
#include "Record.h"

#ifndef OPERATION_DIGITALPININTERRUPTRECORD_H
#define OPERATION_DIGITALPININTERRUPTRECORD_H
namespace EmbeddedIOOperations
{
	class Operation_DigitalPinInterruptRecord : public OperationArchitecture::IOperation<Record<bool>>
	{
	protected:
		EmbeddedIOServices::IDigitalService *_digitalService;
		EmbeddedIOServices::ITimerService *_timerService;
		uint16_t _pin;
		bool _inverted;
		Record<bool> _record;
	public:	
        Operation_DigitalPinInterruptRecord(EmbeddedIOServices::IDigitalService *digitalService, EmbeddedIOServices::ITimerService *timerService, uint16_t pin, bool inverted, uint16_t length);
		Record<bool> Execute() override;
		void Sample();

		static OperationArchitecture::IOperationBase *Create(const void *config, size_t &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif