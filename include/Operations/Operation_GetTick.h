#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_GETTICK_H
#define OPERATION_GETTICK_H
namespace EmbeddedIOOperations
{
	class Operation_GetTick : public OperationArchitecture::IOperation<EmbeddedIOServices::tick_t>
	{
	protected:
		static Operation_GetTick *_instance;
		EmbeddedIOServices::ITimerService *_timerService;
	public:		
        Operation_GetTick(EmbeddedIOServices::ITimerService *timerService);

		EmbeddedIOServices::tick_t Execute() override;

		static OperationArchitecture::IOperationBase *Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif