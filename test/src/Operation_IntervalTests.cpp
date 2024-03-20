#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Interval.h"
#include "MockTimerService.h"
#include "Operations/MockOperation.h"
#include "Config.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_IntervalTests : public Test
	{
		protected:
		MockOperation<void, uint8_t> _mockOperation;
		AbstractOperation *_operation;
		MockTimerService _timerService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		OperationFactory _operationFactory;
        size_t _expectedSize = 0;
        size_t _buildSize = 0;
        size_t _size = 0;

		Operation_IntervalTests() 
		{
			_embeddedIOServiceCollection.TimerService = &_timerService;
			_operationFactory.Register(1, &_mockOperation);

			_expectedSize = sizeof(float); // interval time
			Config::AlignAndAddSize<uint32_t>(_expectedSize); // operationid
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			//interval time
			Config::AssignAndOffset<float>(buildConfig, _buildSize, 0.5f);
			//opertaion id
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSize, 1);

			EXPECT_CALL(_timerService, GetTicksPerSecond()).Times(1).WillOnce(Return(10));
			_operation = Operation_Interval::Create(config, _size, &_embeddedIOServiceCollection, &_operationFactory);
		}
	};

	TEST_F(Operation_IntervalTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
	}

	TEST_F(Operation_IntervalTests, WhenExecutingOperation_WrappedOperationIsOnlyExecutedOnInterval)
	{
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(100000));
		_operation->Execute(1);
		ASSERT_EQ(std::get<0>(_mockOperation.Parameters), 1);
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(0));
		_operation->Execute(2);
		ASSERT_EQ(std::get<0>(_mockOperation.Parameters), 2);
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(2));
		_operation->Execute(3);
		ASSERT_EQ(std::get<0>(_mockOperation.Parameters), 2);
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(3));
		_operation->Execute(4);
		ASSERT_EQ(std::get<0>(_mockOperation.Parameters), 2);
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(5));
		_operation->Execute(5);
		ASSERT_EQ(std::get<0>(_mockOperation.Parameters), 5); 
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(8));
		_operation->Execute(6);
		ASSERT_EQ(std::get<0>(_mockOperation.Parameters), 5);
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(10));
		_operation->Execute(7);
		ASSERT_EQ(std::get<0>(_mockOperation.Parameters), 7);
	}
}
