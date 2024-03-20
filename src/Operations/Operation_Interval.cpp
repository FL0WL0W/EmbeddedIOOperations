#include "Operations/Operation_Interval.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_INTERVAL_H
namespace EmbeddedIOOperations
{
	Operation_Interval::Operation_Interval( ITimerService *timerService, const float intervalTime, AbstractOperation *operation) :
		AbstractOperation(operation->NumberOfReturnVariables, operation->NumberOfParameters),
		_timerService(timerService),
		_intervalTick(intervalTime * timerService->GetTicksPerSecond()),
		_operation(operation)
	{
	}

	void Operation_Interval::AbstractExecute(Variable **variables)
	{
		const tick_t tick = _timerService->GetTick();
		if(tick - _startTick > _intervalTick * 2)
		{
			_startTick = tick;
		}
		else if (tick - _startTick < _intervalTick)
		{
			return;
		}
		else
		{
			_startTick += _intervalTick;
		}

		_operation->AbstractExecute(variables);
	}

	AbstractOperation *Operation_Interval::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection, OperationFactory *factory)
	{
		const float intervalTime = Config::CastAndOffset<float>(config, sizeOut);
		AbstractOperation * const operation = factory->Create(config, sizeOut);
		return new Operation_Interval(embeddedIOServiceCollection->TimerService, intervalTime, operation);
	}
}
#endif