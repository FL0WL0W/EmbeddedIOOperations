#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_TicksToSeconds.h"
#include "MockTimerService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_TicksToSecondsTests : public Test
	{
		protected:
		IOperationBase *_operation;
		MockTimerService _timerService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		size_t _size = 0;

		Operation_TicksToSecondsTests() 
		{
			_embeddedIOServiceCollection.TimerService = &_timerService;

			EXPECT_CALL(_timerService, GetTicksPerSecond()).WillRepeatedly(Return(5000));
			_operation = Operation_TicksToSeconds::Create(&_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_TicksToSecondsTests, WhenGettingValues_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(0.0F, _operation->Execute<float>(0));

		ASSERT_FLOAT_EQ(0.1f, _operation->Execute<float>(500));
	}
}
