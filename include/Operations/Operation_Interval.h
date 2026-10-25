#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "ServiceRegistry.h"
#include "ITimerService.h"

#ifndef OPERATION_INTERVAL_H
#define OPERATION_INTERVAL_H
namespace EmbeddedIOOperations
{
	class Operation_Interval : public OperationArchitecture::AbstractOperation
	{
	protected:
		EmbeddedIOServices::ITimerService * const _timerService;
		OperationArchitecture::AbstractOperation * const _operation;
		const EmbeddedIOServices::tick_t _intervalTick;
		EmbeddedIOServices::tick_t _startTick;
	public:		
		Operation_Interval(EmbeddedIOServices::ITimerService * const timerService, OperationArchitecture::AbstractOperation * const operation, const float intervalTime);
		~Operation_Interval();
		void AbstractExecute(OperationArchitecture::Variable **variables) override;

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t  &sizeOut, const ServiceRegistry *serviceRegistry, OperationArchitecture::OperationFactory *factory);
	};
}
#endif