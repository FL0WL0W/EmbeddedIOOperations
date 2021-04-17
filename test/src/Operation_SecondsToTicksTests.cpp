#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_SecondsToTicks.h"
#include "MockTimerService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_SecondsToTicksTests : public Test
	{
		protected:
		IOperationBase *_operation;
		MockTimerService _timerService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		unsigned int _size = 0;

		Operation_SecondsToTicksTests() 
		{
			_embeddedIOServiceCollection.TimerService = &_timerService;

			EXPECT_CALL(_timerService, GetTicksPerSecond()).WillRepeatedly(Return(5000));
			_operation = Operation_SecondsToTicks::Create(0, _size, &_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_SecondsToTicksTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(0, _size);
	}

	TEST_F(Operation_SecondsToTicksTests, WhenGettingValues_ThenCorrectValueIsReturned)
	{
		ASSERT_EQ(0, _operation->Execute<uint32_t>(0.0f));

		ASSERT_EQ(500, _operation->Execute<uint32_t>(0.1f));
	}
}
