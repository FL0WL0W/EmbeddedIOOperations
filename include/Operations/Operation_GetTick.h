#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_GETTICK_H
#define OPERATION_GETTICK_H
namespace OperationArchitecture
{
	class Operation_GetTick : public IOperation<uint32_t>
	{
	protected:
		static Operation_GetTick *_instance;
		EmbeddedIOServices::ITimerService *_timerService;
	public:		
        Operation_GetTick(EmbeddedIOServices::ITimerService *timerService);

		uint32_t Execute() override;

		static IOperationBase *Create(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut);
	};
}
#endif