#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_GetTick.h"
#include "MockTimerService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_GetTickTests : public Test
	{
		protected:
		AbstractOperation *_operation;
		MockTimerService _timerService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;

		Operation_GetTickTests() 
		{
			_embeddedIOServiceCollection.TimerService = &_timerService;

			_operation = Operation_GetTick::Create(&_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_GetTickTests, WhenGettingValues_ThenCorrectValueIsReturned)
	{
		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(0));
		ASSERT_EQ(0, _operation->Execute<uint32_t>());

		EXPECT_CALL(_timerService, GetTick()).Times(1).WillOnce(Return(500));
		ASSERT_EQ(500, _operation->Execute<uint32_t>());
	}
}
