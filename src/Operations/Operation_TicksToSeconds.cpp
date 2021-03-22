#include "Operations/Operation_TicksToSeconds.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_TICKSTOSECONDS_H
namespace OperationArchitecture
{
	Operation_TicksToSeconds *Operation_TicksToSeconds::_instance = 0;
	Operation_TicksToSeconds::Operation_TicksToSeconds(EmbeddedIOServices::ITimerService *timerService)
	{
		_timerService = timerService;
	}

	float Operation_TicksToSeconds::Execute(uint32_t ticks)
	{
		return static_cast<float>(ticks) / _timerService->GetTicksPerSecond();
	}

	IOperationBase * Operation_TicksToSeconds::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut)
	{
		if(_instance == 0)
			_instance = new Operation_TicksToSeconds(embeddedIOServiceCollection->TimerService);
		return _instance;
	}
}
#endif