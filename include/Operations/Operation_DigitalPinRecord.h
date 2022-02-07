#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_DIGITALPINRECORD_H
#define OPERATION_DIGITALPINRECORD_H
namespace EmbeddedIOOperations
{
	typedef uint16_t frameindex_t;
	struct Frame
	{
		public:
		EmbeddedIOServices::tick_t Tick;
		bool State : 1;
		bool Valid : 1;
	};
	struct Record
	{
		public:
		Record() 
		{
			Length = 0;
		}
		void Initialize(frameindex_t length)
		{
			Length = length;
			Last = 0;
			Frames = (Frame *)calloc(length, sizeof(Frame));
		}
		static frameindex_t Subtract(const frameindex_t &val1, frameindex_t val2, const frameindex_t &length)
		{
			val2 %= length;
			if(val2 > val1)
				return length - (val2 - val1);
			return val1 - val2;
		}
		static frameindex_t Add(const frameindex_t &val1, frameindex_t val2, const frameindex_t &length)
		{
			val2 %= length;
			if(val1 + val2 > length)
				return (val1 + val2) - length;
			return val1 + val2;
		}

		frameindex_t Length; //Don't modify this -_-
		frameindex_t Last;
		EmbeddedIOServices::tick_t TicksPerSecond;
		Frame *Frames;
	};

	class Operation_DigitalPinRecord : public OperationArchitecture::IOperation<Record>
	{
	protected:
		EmbeddedIOServices::IDigitalService *_digitalService;
		EmbeddedIOServices::ITimerService *_timerService;
		uint16_t _pin;
		bool _inverted;
		Record _record;
	public:	
        Operation_DigitalPinRecord(EmbeddedIOServices::IDigitalService *digitalService, EmbeddedIOServices::ITimerService *timerService, uint16_t pin, bool inverted, uint16_t length);
		Record Execute() override;
		void InterruptCallBack();

		static OperationArchitecture::IOperationBase *Create(const void *config, size_t &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif