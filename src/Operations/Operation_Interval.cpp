#include "Operations/Operation_Interval.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_INTERVAL_H
namespace EmbeddedIOOperations
{
	Operation_Interval::Operation_Interval(ITimerService * const timerService, AbstractOperation * const operation, const float intervalTime) :
		_timerService(timerService),
		_operation(operation),
		_intervalTick(intervalTime * timerService->GetTicksPerSecond())
	{ }

	Operation_Interval::~Operation_Interval()
	{
		delete _operation;
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

	AbstractOperation *Operation_Interval::Create(const void *config, size_t  &sizeOut, const ServiceRegistry *serviceRegistry, OperationFactory *factory)
	{
		const float intervalTime = Config::CastAndOffset<float>(config, sizeOut);
		//we own this operation now. Operation_Interval must delete it
		AbstractOperation * const operation = factory->Create(config, sizeOut);
		return new Operation_Interval(serviceRegistry->TryGet<EmbeddedIOServices::ITimerService>(), operation, intervalTime);
	}
}
#endif