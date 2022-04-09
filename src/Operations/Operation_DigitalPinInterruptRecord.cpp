#include "Operations/Operation_DigitalPinInterruptRecord.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_DIGITALPININTERRUPTRECORD_H
namespace EmbeddedIOOperations
{
	Operation_DigitalPinInterruptRecord::Operation_DigitalPinInterruptRecord(IDigitalService *digitalService, ITimerService *timerService, uint16_t pin, bool inverted, uint16_t length) :
		_digitalService(digitalService),
		_timerService(timerService),
		_pin(pin),
		_inverted(inverted),
		_record(length, timerService->GetTicksPerSecond())
	{
		_digitalService->AttachInterrupt(_pin, [this]() { this->Sample(); });
	}

	Record<bool> Operation_DigitalPinInterruptRecord::Execute()
	{
		const uint16_t last = _record.Last;
		if(!_record.Frames[last].Valid)
			return _record;

		const tick_t tick = _timerService->GetTick();
		if(ITimerService::TickLessThanTick(tick, _record.Frames[last].Tick))
		{
			for(frameindex_t i = 0; i < _record.Length; i++)
			{
				 _record.Frames[i].Valid = false;
			}
		}

		return _record;
	}

	void Operation_DigitalPinInterruptRecord::Sample()
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

	IOperationBase *Operation_DigitalPinInterruptRecord::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const uint16_t pin = Config::CastAndOffset<uint16_t>(config, sizeOut);
		const bool inverted = Config::CastAndOffset<bool>(config, sizeOut);
		const uint16_t length = Config::CastAndOffset<uint16_t>(config, sizeOut);
					
		Operation_DigitalPinInterruptRecord *operation = new Operation_DigitalPinInterruptRecord(embeddedIOServiceCollection->DigitalService, embeddedIOServiceCollection->TimerService, pin, inverted, length);

		return operation;
	}
}
#endif
