#include "Operations/Operation_TicksToSeconds.h"
#include "Config.h"

using namespace OperationArchitecture;

#ifdef OPERATION_TICKSTOSECONDS_H
namespace EmbeddedIOOperations
{
	Operation_TicksToSeconds::Operation_TicksToSeconds(EmbeddedIOServices::ITimerService *timerService) : _timerService(timerService) { }

	float Operation_TicksToSeconds::Execute(uint32_t ticks)
	{
		return static_cast<float>(ticks) / _timerService->GetTicksPerSecond();
	}

	AbstractOperation * Operation_TicksToSeconds::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		return new Operation_TicksToSeconds(embeddedIOServiceCollection->TimerService);
	}
}
#endif