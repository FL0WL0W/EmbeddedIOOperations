#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_INTERVAL_H
#define OPERATION_INTERVAL_H
namespace EmbeddedIOOperations
{
	class Operation_Interval : public OperationArchitecture::AbstractOperation
	{
	protected:
		EmbeddedIOServices::ITimerService *_timerService;
		const EmbeddedIOServices::tick_t _intervalTick;
		OperationArchitecture::AbstractOperation *_operation;
		EmbeddedIOServices::tick_t _startTick;
	public:		
        Operation_Interval(EmbeddedIOServices::ITimerService *timerService, float intervalTime, OperationArchitecture::AbstractOperation *operation);
		void AbstractExecute(OperationArchitecture::Variable **variables) override;

		static AbstractOperation *Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection, OperationArchitecture::OperationFactory *factory);
	};
}
#endif