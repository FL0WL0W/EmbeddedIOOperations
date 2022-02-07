#include "Operations/Operation_SecondsToTicks.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_SECONDSTOTICKS_H
namespace EmbeddedIOOperations
{
	Operation_SecondsToTicks::Operation_SecondsToTicks(ITimerService *timerService) : _timerService(timerService) { }

	tick_t Operation_SecondsToTicks::Execute(float seconds)
	{
		return static_cast<tick_t>(_timerService->GetTicksPerSecond() * seconds);
	}

	IOperationBase * Operation_SecondsToTicks::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		return new Operation_SecondsToTicks(embeddedIOServiceCollection->TimerService);
	}
}
#endif