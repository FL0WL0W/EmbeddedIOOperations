#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_AnalogPinRead.h"
#include "MockAnalogService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_AnalogPinReadTests : public Test
	{
		protected:
		MockAnalogService _analogService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		IOperationBase *_operation;
		size_t _size = 0;

		Operation_AnalogPinReadTests() 
		{
			_embeddedIOServiceCollection.AnalogService = &_analogService;

			void *config = malloc(sizeof(uint16_t));

			//pin 1
			*reinterpret_cast<uint16_t *>(config) = 1;

			EXPECT_CALL(_analogService, InitPin(1)).Times(1);
			_operation = Operation_AnalogPinRead::Create(config, _size, &_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_AnalogPinReadTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(sizeof(uint16_t), _size);
	}

	TEST_F(Operation_AnalogPinReadTests, WhenGettingValue_ThenCorrectValueIsReturned)
	{
		EXPECT_CALL(_analogService, ReadPin(1)).Times(1).WillOnce(Return(0.0f));
		ASSERT_FLOAT_EQ(0.0f, _operation->Execute<float>());

		EXPECT_CALL(_analogService, ReadPin(1)).Times(1).WillOnce(Return(1.0f));
		ASSERT_FLOAT_EQ(1.0f, _operation->Execute<float>());

		EXPECT_CALL(_analogService, ReadPin(1)).Times(1).WillOnce(Return(0.5f));
		ASSERT_FLOAT_EQ(0.5f, _operation->Execute<float>());
	}
}
