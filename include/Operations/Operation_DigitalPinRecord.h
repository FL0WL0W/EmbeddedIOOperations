#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"
#include "Packed.h"

#ifndef OPERATION_DIGITALPINRECORD_H
#define OPERATION_DIGITALPINRECORD_H
namespace OperationArchitecture
{
	PACK(struct Frame
	{
		public:
		uint32_t Tick;
		bool State;
		bool Valid;
	});
	struct Record
	{
		public:
		Record() 
		{
			Length = 0;
		}
		void Initialize(uint8_t length)
		{
			Length = length;
			Last = 0;
			Frames = (Frame *)calloc(length, sizeof(Frame));
		}
		static uint8_t Subtract(const uint8_t &val1, uint8_t val2, const uint8_t &length)
		{
			val2 %= length;
			if(val2 > val1)
				return length - (val2 - val1);
			return val1 - val2;
		}
		static uint8_t Add(const uint8_t &val1, uint16_t val2, const uint8_t &length)
		{
			val2 %= length;
			if(val1 + val2 > length)
				return (val1 + val2) - length;
			return val1 + val2;
		}

		uint8_t Length; //Don't modify this -_-
		uint8_t Last;
		Frame *Frames;
	};

	class Operation_DigitalPinRecord : public IOperation<Record>
	{
	protected:
		EmbeddedIOServices::IDigitalService *_digitalService;
		EmbeddedIOServices::ITimerService *_timerService;
		uint16_t _pin;
		bool _inverted;
		Record _record;
	public:	
        Operation_DigitalPinRecord(EmbeddedIOServices::IDigitalService *digitalService, EmbeddedIOServices::ITimerService *timerService, uint16_t pin, bool inverted, uint8_t length);
		Record Execute() override;
		void InterruptCallBack();

		static IOperationBase *Create(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut);
	};
}
#endif