#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_TicksToSeconds.h"
#include "MockTimerService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_TicksToSecondsTests : public ::testing::Test 
	{
		protected:
		IOperationBase *_operation;
		MockTimerService _timerService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		unsigned int _size = 0;

		Operation_TicksToSecondsTests() 
		{
			_embeddedIOServiceCollection.TimerService = &_timerService;

			EXPECT_CALL(_timerService, GetTicksPerSecond()).WillRepeatedly(Return(5000));
			_operation = Operation_TicksToSeconds::Create(&_embeddedIOServiceCollection, 0, _size);
		}
	};

	TEST_F(Operation_TicksToSecondsTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(0, _size);
	}

	TEST_F(Operation_TicksToSecondsTests, WhenGettingValues_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(0.0F, _operation->Execute<float>(0));

		ASSERT_FLOAT_EQ(0.1f, _operation->Execute<float>(500));
	}
}
