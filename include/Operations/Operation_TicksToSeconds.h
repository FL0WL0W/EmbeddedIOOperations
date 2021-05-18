#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_TICKSTOSECONDS_H
#define OPERATION_TICKSTOSECONDS_H
namespace OperationArchitecture
{
	class Operation_TicksToSeconds : public IOperation<float, uint32_t>
	{
	protected:
		static Operation_TicksToSeconds *_instance;
		EmbeddedIOServices::ITimerService *_timerService;
	public:		
        Operation_TicksToSeconds(EmbeddedIOServices::ITimerService *timerService);

		float Execute(uint32_t ticks) override;

		static IOperationBase *Create(const void *config, size_t  &sizeOut, const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif