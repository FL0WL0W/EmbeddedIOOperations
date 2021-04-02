#include "Operations/Operation_DigitalPinRecord.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_DIGITALPINRECORD_H
namespace OperationArchitecture
{
	Operation_DigitalPinRecord::Operation_DigitalPinRecord(EmbeddedIOServices::IDigitalService *digitalService, EmbeddedIOServices::ITimerService *timerService, uint16_t pin, bool inverted, uint16_t length)
	{
		_digitalService = digitalService;
		_timerService = timerService;
		_pin = pin;
		_inverted = inverted;
		_record.Initialize(length);
		_record.TicksPerSecond = _timerService->GetTicksPerSecond();

		_digitalService->ScheduleRecurringInterrupt(_pin, new EmbeddedIOServices::CallBack<Operation_DigitalPinRecord>(this, &Operation_DigitalPinRecord::InterruptCallBack));
	}

	Record Operation_DigitalPinRecord::Execute()
	{
		const uint16_t last = _record.Last;
		if(!_record.Frames[last].Valid)
			return _record;

		const uint32_t tick = _timerService->GetTick();
		if(EmbeddedIOServices::ITimerService::TickLessThanTick(tick, _record.Frames[last].Tick))
		{
			for(int i = 0; i < _record.Length; i++)
			{
				 _record.Frames[last].Valid = false;
			}
		}

		return _record;
	}

	void Operation_DigitalPinRecord::InterruptCallBack()
	{
		bool state = _digitalService->ReadPin(_pin);
		const uint32_t tick = _timerService->GetTick();
		if(_inverted)
			state = !state;
		uint16_t last = _record.Last;
		//only record toggles
		if(state == _record.Frames[last].State && _record.Frames[last].Valid)
			return;
		last++;
		if(last >= _record.Length)
			last = 0;
		_record.Frames[last].State = state;
		_record.Frames[last].Tick = tick;
		_record.Frames[last].Valid = true;
		_record.Last = last;
	}

	IOperationBase *Operation_DigitalPinRecord::Create(const EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const bool inverted = Config::CastAndOffset<bool>(config, sizeOut);
		uint32_t length = Config::CastAndOffset<uint16_t>(config, sizeOut);
					
		Operation_DigitalPinRecord *operation = new Operation_DigitalPinRecord(embeddedIOServiceCollection->DigitalService, embeddedIOServiceCollection->TimerService, pin, inverted, length);

		return operation;
	}
}
#endif
