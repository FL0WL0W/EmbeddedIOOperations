#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_FrequencyPinRead.h"
#include "MockPwmService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_FrequencyPinReadTests : public Test
	{
		protected:
		MockPwmService _pwmService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		IOperationBase *_operation;
        unsigned _size = 0;

		Operation_FrequencyPinReadTests() 
		{
			_embeddedIOServiceCollection.PwmService = &_pwmService;

			void *config = malloc(sizeof(uint16_t) + sizeof(uint16_t));
			void *buildConfig = config;

			//pin 1
			*((uint16_t *)buildConfig) = 1;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);

			//minFrequency 2
			*((uint16_t *)buildConfig) = 2;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);

			EXPECT_CALL(_pwmService, InitPin(1, In, 2)).Times(1);
			_operation = Operation_FrequencyPinRead::Create(&_embeddedIOServiceCollection, config, _size);
		}
	};

	TEST_F(Operation_FrequencyPinReadTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(4, _size);
	}

	TEST_F(Operation_FrequencyPinReadTests, WhenGettingValue_ThenCorrectValueIsReturned)
	{
		PwmValue pwmValue = { 0.1f, 0.05f };
		EXPECT_CALL(_pwmService, ReadPin(1)).Times(1).WillOnce(Return(pwmValue));
		ASSERT_FLOAT_EQ(10, _operation->Execute<float>());

		pwmValue = { 0.025f, 0.004f };
		EXPECT_CALL(_pwmService, ReadPin(1)).Times(1).WillOnce(Return(pwmValue));
		ASSERT_FLOAT_EQ(40, _operation->Execute<float>());

		pwmValue = { 0.05f, 0.04f };
		EXPECT_CALL(_pwmService, ReadPin(1)).Times(1).WillOnce(Return(pwmValue));
		ASSERT_NEAR(20, _operation->Execute<float>(), 0.001f);

		pwmValue = { 0.05333333333333f, 0.04f };
		EXPECT_CALL(_pwmService, ReadPin(1)).Times(1).WillOnce(Return(pwmValue));
		ASSERT_NEAR(18.75f, _operation->Execute<float>(), 0.001f);
	}
}
