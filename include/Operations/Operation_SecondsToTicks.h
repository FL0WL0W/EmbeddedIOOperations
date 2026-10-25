#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "ITimerService.h"

#ifndef OPERATION_SECONDSTOTICKS_H
#define OPERATION_SECONDSTOTICKS_H
namespace EmbeddedIOOperations
{
	class Operation_SecondsToTicks : public OperationArchitecture::Operation<uint32_t, float>
	{
	protected:
		EmbeddedIOServices::ITimerService * const _timerService;
	public:		
        Operation_SecondsToTicks(EmbeddedIOServices::ITimerService * const timerService);
		uint32_t Execute(float seconds) override;

		static OperationArchitecture::AbstractOperation *Create(const ServiceRegistry *serviceRegistry);
	};
}
#endif