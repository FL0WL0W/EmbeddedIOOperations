#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_SECONDSTOTICKS_H
#define OPERATION_SECONDSTOTICKS_H
namespace OperationArchitecture
{
	class Operation_SecondsToTicks : public IOperation<uint32_t, float>
	{
	protected:
		static Operation_SecondsToTicks *_instance;
		EmbeddedIOServices::ITimerService *_timerService;
	public:		
        Operation_SecondsToTicks(EmbeddedIOServices::ITimerService *timerService);

		uint32_t Execute(float seconds) override;

		static IOperationBase *Create(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif