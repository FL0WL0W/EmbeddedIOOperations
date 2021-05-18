#include "Operations/Operation_SecondsToTicks.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_SECONDSTOTICKS_H
namespace OperationArchitecture
{
	Operation_SecondsToTicks *Operation_SecondsToTicks::_instance = 0;
	Operation_SecondsToTicks::Operation_SecondsToTicks(EmbeddedIOServices::ITimerService *timerService)
	{
		_timerService = timerService;
	}

	uint32_t Operation_SecondsToTicks::Execute(float seconds)
	{
		return _timerService->GetTicksPerSecond() * seconds;
	}

	IOperationBase * Operation_SecondsToTicks::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		if(_instance == 0)
			_instance = new Operation_SecondsToTicks(embeddedIOServiceCollection->TimerService);
		return _instance;
	}
}
#endif