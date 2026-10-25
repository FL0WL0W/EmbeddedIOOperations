#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "ITimerService.h"

#ifndef OPERATION_TICKSTOSECONDS_H
#define OPERATION_TICKSTOSECONDS_H
namespace EmbeddedIOOperations
{
	class Operation_TicksToSeconds : public OperationArchitecture::Operation<float, uint32_t>
	{
	protected:
		EmbeddedIOServices::ITimerService * const _timerService;
	public:		
        Operation_TicksToSeconds(EmbeddedIOServices::ITimerService * const timerService);
		float Execute(uint32_t ticks) override;

		static OperationArchitecture::AbstractOperation *Create(const ServiceRegistry *serviceRegistry);
	};
}
#endif