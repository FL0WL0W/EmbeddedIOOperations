#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"
#include "Operations/OperationFactory.h"
#include "Record.h"
#include "Config.h"

#ifndef OPERATION_FIRFILTER_H
#define OPERATION_FIRFILTER_H
namespace EmbeddedIOOperations
{
	struct Operation_FIRFilterConfig 
	{
	private:
		Operation_FIRFilterConfig()
		{
			
		}
		inline size_t size() const
		{
			const size_t a = alignof(float);
			size_t s = sizeof(float);
			OperationArchitecture::Config::AlignAndAddSize<uint16_t>(s);
			if(s % a > 0)
				s += a - (s % a);
			return s;
		}
		
	public:		
		size_t Size() const
		{
			size_t s = size();
			s += sizeof(float) * Order;
			return s;
		}

		const float *Coefficients() const { return reinterpret_cast<const float *>(reinterpret_cast<const uint8_t *>(this) + size()); }
		
		float SampleRate;
		uint16_t Order;
	};

	template<typename state_t>
	class Operation_FIRFilter : public OperationArchitecture::IOperation<state_t, Record<state_t>>
	{
	protected:
		const Operation_FIRFilterConfig *_firConfig;
	public:		
        Operation_FIRFilter(const Operation_FIRFilterConfig *firConfig) : _firConfig(firConfig) {}
		state_t Execute(Record<state_t> record) override 
		{
			const uint16_t length = record.Length;
			const uint16_t last = record.Last;
			const Frame<state_t> *lastFrame = &record.Frames[last];
			const uint16_t lastPlusOne = Record<state_t>::Add(last, 1, length);
			const EmbeddedIOServices::tick_t lastTick = record.Frames[last].Tick;
			const EmbeddedIOServices::tick_t sampleRateTicks = _firConfig->SampleRate * record.TicksPerSecond;
			const float *coefficents = _firConfig->Coefficients();
			state_t filteredValue = 0;
			if(lastFrame->Valid) 
			{
				filteredValue = lastFrame->State * coefficents[0];
				const Frame<state_t> *previousFrame = lastFrame;
				for(uint16_t i = 1, frameIndex = Record<state_t>::Subtract(last, 1, length); frameIndex != lastPlusOne; frameIndex = Record<state_t>::Subtract(frameIndex, 1, length))
				{
					const Frame<state_t> *frame = &record.Frames[frameIndex];
					if(!frame->Valid)
						break;
					
					//interpolation
					EmbeddedIOServices::tick_t nextCoefficientTick = lastFrame->Tick + i * sampleRateTicks;
					EmbeddedIOServices::tick_t previousFrameTick = previousFrame->Tick;
					const EmbeddedIOServices::tick_t deltaTick = frame->Tick - previousFrame->Tick;
					const state_t deltaState = ((frame->State - previousFrame->State) * deltaTick) / sampleRateTicks;
					if(EmbeddedIOServices::ITimerService::TickLessThanTick(frame->Tick, nextCoefficientTick))
					{
						filteredValue += (deltaState * coefficents[i] * (nextCoefficientTick - previousFrameTick)) / deltaTick;
						while(++i < _firConfig->Order) 
						{
							previousFrameTick = nextCoefficientTick;
							nextCoefficientTick += sampleRateTicks;
							if(EmbeddedIOServices::ITimerService::TickLessThanTick(frame->Tick, nextCoefficientTick))
							{
								filteredValue += (deltaState * coefficents[i] * (nextCoefficientTick - previousFrameTick)) / deltaTick;
							}
							else
							{
								filteredValue += (deltaState * coefficents[i] * (frame->Tick - nextCoefficientTick)) / deltaTick;
								break;
							}
						}
					}
					else 
					{
						filteredValue += deltaState * coefficents[i];
					}

					previousFrame = frame;
				}
			}

			return filteredValue;
		}

		static OperationArchitecture::IOperationBase *Create(const void *config, size_t &sizeOut) 
		{
			return new Operation_FIRFilter(OperationArchitecture::Config::CastConfigAndOffset<Operation_FIRFilterConfig>(config, sizeOut));
		}
	};
}
#endif