#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"
#include "Operations/OperationFactory.h"
#include "Record.h"
#include "Config.h"

#ifndef OPERATION_RECORD_H
#define OPERATION_RECORD_H
namespace EmbeddedIOOperations
{
	template<typename state_t>
	class Operation_Record : public OperationArchitecture::IOperation<Record<state_t>>
	{
	protected:
		EmbeddedIOServices::ITimerService *_timerService;
		EmbeddedIOServices::Task *_sampleTask;
		const EmbeddedIOServices::tick_t _sampleRateTicks;
		Record<state_t> _record;
		OperationArchitecture::IOperationBase *_sampleOperation;
	public:		
        Operation_Record(EmbeddedIOServices::ITimerService *timerService, const float sampleRate, const uint16_t length, OperationArchitecture::IOperationBase *sampleOperation) :
			_timerService(timerService),
			_record(length, timerService->GetTicksPerSecond()),
			_sampleRateTicks(sampleRate * timerService->GetTicksPerSecond()),
			_sampleOperation(sampleOperation)
		{
			//if sample rate ticks is greater than 0 it means we sample on an interval
			if(_sampleRateTicks > 0)
			{
				_sampleTask = new EmbeddedIOServices::Task([this]() 
				{
					this->Sample(); 
#ifdef ALLOW_TASK_TO_SCHEDULE_IN_CALLBACK 
//this allows us to sample faster than the main loop speed
					this->_timerService->ScheduleTask(this->_sampleTask, this->_sampleTask->ScheduledTick + this->_sampleRateTicks);
#endif
				});
				_timerService->ScheduleTask(_sampleTask, _timerService->GetTick() + _sampleRateTicks);
			}
		}
		Record<state_t> Execute() override 
		{
			const uint16_t last = _record.Last;
			const EmbeddedIOServices::tick_t tick = _timerService->GetTick();
			if(EmbeddedIOServices::ITimerService::TickLessThanTick(tick, _record.Frames[last].Tick))
			{
				for(frameindex_t i = 0; i < _record.Length; i++)
				{
					_record.Frames[i].Valid = false;
				}
			}

			//if sample rate ticks is 0 it means we sample on execute
			if(_sampleRateTicks == 0)
			{
				Sample();
			}
#ifndef ALLOW_TASK_TO_SCHEDULE_IN_CALLBACK
//this method cannot sample faster than the main loop speed so we have to do some calculations to acount for this
			//else schedule the next sample
			else if(!_sampleTask->Scheduled)
			{
				//if nextSampleTick is before the previous Frame if valid or before tick if not valid, then set nextSampleTick to now;
				EmbeddedIOServices::tick_t nextSampleTick = _sampleTask->ScheduledTick + _sampleRateTicks;
				const Frame<float> *previousFrame = &_record.Frames[Record<float>::Subtract(last, 1, _record.Length)];
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
#endif

			if(!_record.Frames[last].Valid)
				return _record;

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

		static OperationArchitecture::IOperationBase *Create(const void *config, size_t &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection, OperationArchitecture::OperationFactory *factory) 
		{
			const float sampleRate = OperationArchitecture::Config::CastAndOffset<float>(config, sizeOut);
			const uint16_t length = OperationArchitecture::Config::CastAndOffset<uint16_t>(config, sizeOut);

			size_t size = 0;
			OperationArchitecture::IOperationBase *sampleOperation = factory->Create(config, size);
			OperationArchitecture::Config::OffsetConfig(config, sizeOut, size);

			return new Operation_Record(embeddedIOServiceCollection->TimerService, sampleRate, length, sampleOperation);
		}
	};
}
#endif