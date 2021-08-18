#include "Operations/Operation_DigitalPinRecord.h"
#include "Config.h"

using namespace EmbeddedIOServices;

#ifdef OPERATION_DIGITALPINRECORD_H
namespace OperationArchitecture
{
	Operation_DigitalPinRecord::Operation_DigitalPinRecord(EmbeddedIOServices::IDigitalService *digitalService, EmbeddedIOServices::ITimerService *timerService, uint16_t pin, bool inverted, uint16_t length) :
		_digitalService(digitalService),
		_timerService(timerService),
		_pin(pin),
		_inverted(inverted)
	{
		_record.Initialize(length);
		_record.TicksPerSecond = _timerService->GetTicksPerSecond();

		_digitalService->AttachInterrupt(_pin, [this]() { this->InterruptCallBack(); });
	}

	Record Operation_DigitalPinRecord::Execute()
	{
		const uint16_t last = _record.Last;
		if(!_record.Frames[last].Valid)
			return _record;

		const tick_t tick = _timerService->GetTick();
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
		const uint16_t last = (_record.Last + 1) % _record.Length;
		_record.Frames[last].State = _digitalService->ReadPin(_pin)  ^ _inverted;
		_record.Frames[last].Tick = _timerService->GetTick();
		//only record toggles
		if(_record.Frames[last].State == _record.Frames[_record.Last].State && _record.Frames[_record.Last].Valid)
			return;
		_record.Frames[last].Valid = true;
		_record.Last = last;
	}

	IOperationBase *Operation_DigitalPinRecord::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const bool inverted = Config::CastAndOffset<bool>(config, sizeOut);
		const uint16_t length = Config::CastAndOffset<uint16_t>(config, sizeOut);
					
		Operation_DigitalPinRecord *operation = new Operation_DigitalPinRecord(embeddedIOServiceCollection->DigitalService, embeddedIOServiceCollection->TimerService, pin, inverted, length);

		return operation;
	}
}
#endif
