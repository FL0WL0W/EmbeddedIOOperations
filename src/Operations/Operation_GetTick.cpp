#include "Operations/Operation_GetTick.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_GETTICK_H
namespace OperationArchitecture
{
	Operation_GetTick::Operation_GetTick(EmbeddedIOServices::ITimerService *timerService) : _timerService(timerService) {}

	uint32_t Operation_GetTick::Execute()
	{
		return _timerService->GetTick();
	}

	IOperationBase * Operation_GetTick::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		return new Operation_GetTick(embeddedIOServiceCollection->TimerService);
	}
}
#endif