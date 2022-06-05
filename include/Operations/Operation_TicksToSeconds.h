#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_TICKSTOSECONDS_H
#define OPERATION_TICKSTOSECONDS_H
namespace EmbeddedIOOperations
{
	class Operation_TicksToSeconds : public OperationArchitecture::IOperation<float, uint32_t>
	{
	protected:
		EmbeddedIOServices::ITimerService *_timerService;
	public:		
        Operation_TicksToSeconds(EmbeddedIOServices::ITimerService *timerService);
		float Execute(uint32_t ticks) override;

		static OperationArchitecture::IOperationBase *Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif