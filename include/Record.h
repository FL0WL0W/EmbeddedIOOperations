#include "ITimerService.h"

#ifndef RECORD_H
#define RECORD_H
namespace EmbeddedIOOperations
{
	template<typename state_t>
	struct Frame
	{
		public:
		EmbeddedIOServices::tick_t Tick;
		state_t State;
		bool Valid : 1;
	};
	template<>
	struct Frame<bool>
	{
		public:
		EmbeddedIOServices::tick_t Tick;
		bool State : 1;
		bool Valid : 1;
	};
	typedef uint16_t frameindex_t;
	template<typename state_t>
	struct Record
	{
		public:
		Record() : Record(0, 0) { }
		Record(frameindex_t length) : Record(length, 0) { }
		Record(frameindex_t length, EmbeddedIOServices::tick_t ticksPerSecond) : TicksPerSecond(ticksPerSecond) { Initialize(length); }
		void Initialize(frameindex_t length)
		{
			Length = length;
			Last = 0;
			Frames = (Frame<state_t> *)calloc(length, sizeof(Frame<state_t>));
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
		Frame<state_t> *Frames;
	};
}
#endif