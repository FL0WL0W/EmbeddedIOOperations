#include "Operations/Operation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_SECONDSTOTICKS_H
#define OPERATION_SECONDSTOTICKS_H
namespace EmbeddedIOOperations
{
	class Operation_SecondsToTicks : public OperationArchitecture::Operation<uint32_t, float>
	{
	protected:
		EmbeddedIOServices::ITimerService *_timerService;
	public:		
        Operation_SecondsToTicks(EmbeddedIOServices::ITimerService *timerService);
		uint32_t Execute(float seconds) override;

		static OperationArchitecture::AbstractOperation *Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif