#include "Operations/Operation_GetTick.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_GETTICK_H
namespace EmbeddedIOOperations
{
	Operation_GetTick::Operation_GetTick(ITimerService *timerService) : _timerService(timerService) {}

	tick_t Operation_GetTick::Execute()
	{
		return _timerService->GetTick();
	}

	AbstractOperation * Operation_GetTick::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		return new Operation_GetTick(embeddedIOServiceCollection->TimerService);
	}
}
#endif