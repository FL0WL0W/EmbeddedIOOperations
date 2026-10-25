#include "Operations/Operation.h"
#include "ServiceRegistry.h"
#include "Operations/OperationFactory.h"
#include "Record.h"
#include "Config.h"

#ifndef OPERATION_RECORD_H
#define OPERATION_RECORD_H
namespace EmbeddedIOOperations
{
	template<typename state_t>
	class Operation_Record : public OperationArchitecture::Operation<Record<state_t>>
	{
	protected:
		EmbeddedIOServices::ITimerService * const _timerService;
		OperationArchitecture::AbstractOperation * const _sampleOperation;
		EmbeddedIOServices::Task * const _sampleTask = 0;
		Record<state_t> _record;
		const EmbeddedIOServices::tick_t _sampleRateTicks;
	public:		
        Operation_Record(EmbeddedIOServices::ITimerService * const timerService, OperationArchitecture::AbstractOperation * const sampleOperation, const float sampleRate, const uint16_t length) :
			_timerService(timerService),
			_sampleOperation(sampleOperation),
			_sampleTask( sampleRate > 0 ? new EmbeddedIOServices::Task([this]() { this->Sample(); }) : 0),
			_record(length, timerService->GetTicksPerSecond()),
			_sampleRateTicks(sampleRate * timerService->GetTicksPerSecond())
		{
			//if sample rate ticks is greater than 0 it means we sample on an interval
			if(_sampleRateTicks > 0)
				_timerService->ScheduleTask(_sampleTask, _timerService->GetTick() + _sampleRateTicks);
		}
		~Operation_Record()
		{
			if(_sampleTask != 0)
			{
				_timerService->UnScheduleTask(_sampleTask);
				delete _sampleTask;
			}
			delete _sampleOperation;
		}
		Record<state_t> Execute() override 
		{
			const uint16_t last = _record.Last;
			const uint16_t length = _record.Length;
			const EmbeddedIOServices::tick_t tick = _timerService->GetTick();
			if(EmbeddedIOServices::ITimerService::TickLessThanTick(tick, _record.Frames[last].Tick))
			{
				for(frameindex_t i = 0; i < length; i++)
				{
					_record.Frames[i].Valid = false;
				}
			}

			//if sample rate ticks is 0 it means we sample on execute
			if(_sampleRateTicks == 0)
			{
				Sample();
			}
			//this method cannot sample faster than the main loop speed so we have to do some calculations to acount for this
			//else schedule the next sample
			else if(!_sampleTask->Scheduled)
			{
				//if nextSampleTick is before the previous Frame if valid or before tick if not valid, then set nextSampleTick to now;
				EmbeddedIOServices::tick_t nextSampleTick = _sampleTask->ScheduledTick + _sampleRateTicks;
				const Frame<state_t> *previousFrame = &_record.Frames[Record<state_t>::Subtract(last, 1, length)];
				if(previousFrame->Valid)
				{
					if(EmbeddedIOServices::ITimerService::TickLessThanTick(nextSampleTick, previousFrame->Tick))
						nextSampleTick = tick;
				}
				else if(EmbeddedIOServices::ITimerService::TickLessThanTick(nextSampleTick, tick))
				{
					nextSampleTick = tick;
				}
				_timerService->ScheduleTask(_sampleTask, nextSampleTick);
			}

			return _record;
		}
		void Sample() 
		{
			const uint16_t last = (_record.Last + 1) % _record.Length;
			_record.Frames[last].State = _sampleOperation->Execute<state_t>();
			_record.Frames[last].Tick = _timerService->GetTick();
			_record.Frames[last].Valid = true;
			_record.Last = last;
		}

		static OperationArchitecture::AbstractOperation *Create(const void *config, size_t &sizeOut, const ServiceRegistry *serviceRegistry, OperationArchitecture::OperationFactory *factory)
		{
			const float sampleRate = OperationArchitecture::Config::CastAndOffset<float>(config, sizeOut);
			const uint16_t length = OperationArchitecture::Config::CastAndOffset<uint16_t>(config, sizeOut);

			size_t size = 0;
			//we own this operation now. Operation_Record must delete it
			OperationArchitecture::AbstractOperation *sampleOperation = factory->Create(config, size);
			OperationArchitecture::Config::OffsetConfig(config, sizeOut, size);

			return new Operation_Record(serviceRegistry->TryGet<EmbeddedIOServices::ITimerService>(), sampleOperation, sampleRate, length);
		}
	};
}
#endif
