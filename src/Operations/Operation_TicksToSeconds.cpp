#include "Operations/Operation_TicksToSeconds.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_TICKSTOSECONDS_H
namespace OperationArchitecture
{
	Operation_TicksToSeconds::Operation_TicksToSeconds(EmbeddedIOServices::ITimerService *timerService) : _timerService(timerService) { }

	float Operation_TicksToSeconds::Execute(uint32_t ticks)
	{
		return static_cast<float>(ticks) / _timerService->GetTicksPerSecond();
	}

	IOperationBase * Operation_TicksToSeconds::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		return new Operation_TicksToSeconds(embeddedIOServiceCollection->TimerService);
	}
}
#endif