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

		static IOperationBase *Create(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut);
	};
}
#endif