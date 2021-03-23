#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include "MockDigitalService.h"
#include "MockTimerService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_DigitalPinRecordTests : public Test
	{
		protected:
		MockDigitalService _digitalService;
		MockTimerService _timerService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		IOperationBase *_operation;
		ICallBack *_callBack = 0;
		Record *_record;
        unsigned int _size = 0;

		Operation_DigitalPinRecordTests() 
		{
			_embeddedIOServiceCollection.DigitalService = &_digitalService;
			_embeddedIOServiceCollection.TimerService = &_timerService;

			void *config = malloc(sizeof(uint16_t) + sizeof(bool) + sizeof(uint8_t));
			void *buildConfig = config;

			//pin 1
			*((uint16_t *)buildConfig) = 1;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);
            
			//inverted
			*((bool *)buildConfig) = false;
			buildConfig = (void *)(((bool *)buildConfig) + 1);
            
			//length
			*((uint8_t *)buildConfig) = 8;
			buildConfig = (void *)(((uint8_t *)buildConfig) + 1);

			
			EXPECT_CALL(_digitalService, ScheduleRecurringInterrupt(1, _))
				.Times(1)
				.WillOnce(SaveArg<1>(&_callBack));

			_operation = Operation_DigitalPinRecord::Create(&_embeddedIOServiceCollection, config, _size);
		}
	};

	TEST_F(Operation_DigitalPinRecordTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(4, _size);
	}

	TEST_F(Operation_DigitalPinRecordTests, WhenRecordingThenNonToggleStatesDoNotTriggerAFrame)
	{
        Record record = _operation->Execute<Record>();
		ASSERT_EQ(0, record.Last);

		EXPECT_CALL(_timerService, GetTick()).Times(2).WillRepeatedly(Return(10));
	 	EXPECT_CALL(_digitalService, ReadPin(1)).Times(1).WillOnce(Return(false));
		_callBack->Execute();
        record = _operation->Execute<Record>();
		ASSERT_EQ(1, record.Last);
		ASSERT_EQ(true, record.Frames[record.Last].Valid);
		ASSERT_EQ(false, record.Frames[record.Last].State);
		ASSERT_EQ(10, record.Frames[record.Last].Tick);

		EXPECT_CALL(_timerService, GetTick()).Times(2).WillRepeatedly(Return(11));
	 	EXPECT_CALL(_digitalService, ReadPin(1)).Times(1).WillOnce(Return(false));
		_callBack->Execute();
        record = _operation->Execute<Record>();
		ASSERT_EQ(1, record.Last);
		ASSERT_EQ(true, record.Frames[record.Last].Valid);
		ASSERT_EQ(false, record.Frames[record.Last].State);
		ASSERT_EQ(10, record.Frames[record.Last].Tick);

		EXPECT_CALL(_timerService, GetTick()).Times(2).WillRepeatedly(Return(12));
	 	EXPECT_CALL(_digitalService, ReadPin(1)).Times(1).WillOnce(Return(true));
		_callBack->Execute();
        record = _operation->Execute<Record>();
		ASSERT_EQ(2, record.Last);
		ASSERT_EQ(true, record.Frames[record.Last].Valid);
		ASSERT_EQ(true, record.Frames[record.Last].State);
		ASSERT_EQ(12, record.Frames[record.Last].Tick);
	}
}
