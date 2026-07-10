#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "ITimerService.h"

#ifndef OPERATION_GETTICK_H
#define OPERATION_GETTICK_H
namespace EmbeddedIOOperations
{
	class Operation_GetTick : public OperationArchitecture::Operation<EmbeddedIOServices::tick_t>
	{
	protected:
		EmbeddedIOServices::ITimerService *_timerService;
	public:		
        Operation_GetTick(EmbeddedIOServices::ITimerService *timerService);
		EmbeddedIOServices::tick_t Execute() override;

		static OperationArchitecture::AbstractOperation *Create(const ServiceRegistry *serviceRegistry);
	};
}
#endif