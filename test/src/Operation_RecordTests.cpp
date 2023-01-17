#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Record.h"
#include "MockDigitalService.h"
#include "MockTimerService.h"
#include "Config.h"
#include "Operations/OperationFactory.h"
#include "Operations/MockOperation.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_RecordTests : public Test
	{
		protected:
		MockDigitalService _digitalService;
		MockTimerService _timerService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		MockOperation<float> _operationSample;
		OperationFactory _operationFactory;
		AbstractOperation *_operationSampleOnExecute;
		AbstractOperation *_operationSampleOnInterval;
		callback_t _callBack = 0;
		Record<bool> *_record;
        size_t _expectedSize = 0;
        size_t _buildSizeSampleOnExecute = 0;
        size_t _buildSizeSampleOnInterval = 0;
        size_t _sizeSampleOnExecute = 0;
        size_t _sizeSampleOnInterval = 0;

		Operation_RecordTests() 
		{
        	_operationFactory.Register(5, &_operationSample);
			_embeddedIOServiceCollection.DigitalService = &_digitalService;
			_embeddedIOServiceCollection.TimerService = &_timerService;

			_expectedSize = sizeof(float);
			Config::AlignAndAddSize<uint16_t>(_expectedSize);
			Config::AlignAndAddSize<uint32_t>(_expectedSize);
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			//sampleRate
			Config::AssignAndOffset<float>(buildConfig, _buildSizeSampleOnExecute, 0);
			//length
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSizeSampleOnExecute, 8);
			//operationSample
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSizeSampleOnExecute, 5);

			EXPECT_CALL(_timerService, GetTicksPerSecond()).Times(2).WillRepeatedly(Return(10));
			_operationSampleOnExecute = Operation_Record<float>::Create(config, _sizeSampleOnExecute, &_embeddedIOServiceCollection, &_operationFactory);


			config = malloc(_expectedSize);
			buildConfig = config;
			//sampleRate
			Config::AssignAndOffset<float>(buildConfig, _buildSizeSampleOnInterval, 1);
			//length
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSizeSampleOnInterval, 8);
			//operationSample
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSizeSampleOnInterval, 5);

			EXPECT_CALL(_timerService, ScheduleCallBack(10)).Times(1);
			EXPECT_CALL(_timerService, GetTicksPerSecond()).Times(2).WillRepeatedly(Return(10));
			EXPECT_CALL(_timerService, GetTick()).Times(1).WillRepeatedly(Return(0));
			_operationSampleOnInterval = Operation_Record<float>::Create(config, _sizeSampleOnInterval, &_embeddedIOServiceCollection, &_operationFactory);
		}
	};

	TEST_F(Operation_RecordTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSizeSampleOnExecute);
		ASSERT_EQ(_expectedSize, _sizeSampleOnExecute);
		ASSERT_EQ(_expectedSize, _buildSizeSampleOnInterval);
		ASSERT_EQ(_expectedSize, _sizeSampleOnInterval);
	}

	TEST_F(Operation_RecordTests, WhenExecutingSampleOnExecuteThenSampleIsRecordedOnExecute)
	{
		EXPECT_CALL(_timerService, GetTick()).Times(2).WillRepeatedly(Return(10));
		_operationSample.ReturnValue = 15;
        Record<float> record = _operationSampleOnExecute->Execute<Record<float>>();
		ASSERT_EQ(1, record.Last);
		ASSERT_EQ(true, record.Frames[record.Last].Valid);
		ASSERT_FLOAT_EQ(_operationSample.ReturnValue, record.Frames[record.Last].State);
		ASSERT_EQ(10, record.Frames[record.Last].Tick);

		EXPECT_CALL(_timerService, GetTick()).Times(2).WillRepeatedly(Return(20));
		_operationSample.ReturnValue = 25;
        record = _operationSampleOnExecute->Execute<Record<float>>();
		ASSERT_EQ(2, record.Last);
		ASSERT_EQ(true, record.Frames[record.Last].Valid);
		ASSERT_FLOAT_EQ(_operationSample.ReturnValue, record.Frames[record.Last].State);
		ASSERT_EQ(20, record.Frames[record.Last].Tick);
	}

	TEST_F(Operation_RecordTests, WhenExecutingSampleOnIntervalThenSampleIsRecordedOnInterval)
	{
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillRepeatedly(Return(0));
        Record<float> record = _operationSampleOnInterval->Execute<Record<float>>();
		ASSERT_EQ(0, record.Last);

		EXPECT_CALL(_timerService, ScheduleCallBack(21)).Times(1);
		EXPECT_CALL(_timerService, GetTick()).WillRepeatedly(Return(21));
		_operationSample.ReturnValue = 15;
		_timerService.ReturnCallBackPrivateFunction();
		_timerService.ReturnCallBackPrivateFunction();//call twice to make sure we stay on interval
		EXPECT_CALL(_timerService, GetTick()).Times(2).WillRepeatedly(Return(21));
        record = _operationSampleOnInterval->Execute<Record<float>>();
        record = _operationSampleOnInterval->Execute<Record<float>>();//call twice to make sure we stay on interval
		ASSERT_EQ(1, record.Last);
		ASSERT_EQ(true, record.Frames[record.Last].Valid);
		ASSERT_FLOAT_EQ(_operationSample.ReturnValue, record.Frames[record.Last].State);
		ASSERT_EQ(21, record.Frames[record.Last].Tick);

		EXPECT_CALL(_timerService, ScheduleCallBack(31)).Times(1);
		EXPECT_CALL(_timerService, GetTick()).WillRepeatedly(Return(45));
		_operationSample.ReturnValue = 25;
		_timerService.ReturnCallBackPrivateFunction();
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillRepeatedly(Return(45));
        record = _operationSampleOnInterval->Execute<Record<float>>();
		ASSERT_EQ(2, record.Last);
		ASSERT_EQ(true, record.Frames[record.Last].Valid);
		ASSERT_FLOAT_EQ(_operationSample.ReturnValue, record.Frames[record.Last].State);
		ASSERT_EQ(45, record.Frames[record.Last].Tick);

		EXPECT_CALL(_timerService, ScheduleCallBack(60)).Times(1);
		EXPECT_CALL(_timerService, GetTick()).WillRepeatedly(Return(60));
		_operationSample.ReturnValue = 35;
		_timerService.ReturnCallBackPrivateFunction();
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillRepeatedly(Return(60));
        record = _operationSampleOnInterval->Execute<Record<float>>();
		ASSERT_EQ(3, record.Last);
		ASSERT_EQ(true, record.Frames[record.Last].Valid);
		ASSERT_FLOAT_EQ(_operationSample.ReturnValue, record.Frames[record.Last].State);
		ASSERT_EQ(60, record.Frames[record.Last].Tick);

		//invalidate all frames
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillRepeatedly(Return(10));
        record = _operationSampleOnInterval->Execute<Record<float>>();
		ASSERT_EQ(3, record.Last);
		ASSERT_EQ(false, record.Frames[record.Last].Valid);
	}
}
