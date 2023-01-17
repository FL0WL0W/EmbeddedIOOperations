#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_PulseWidthPinRead.h"
#include "MockPwmService.h"
#include "Config.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_PulseWidthPinReadTests : public Test
	{
		protected:
		MockPwmService _pwmService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		AbstractOperation *_operation;
        size_t _size = 0;
        size_t _buildSize = 0;
        size_t _expectedSize = 0;

		Operation_PulseWidthPinReadTests() 
		{
			_embeddedIOServiceCollection.PwmService = &_pwmService;

			_expectedSize = sizeof(uint16_t);
			Config::AlignAndAddSize<uint16_t>(_expectedSize);
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			//pin 3
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSize, 1);
			//minFrequency 2
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSize, 2);

			EXPECT_CALL(_pwmService, InitPin(1, In, 2)).Times(1);
			_operation = Operation_PulseWidthPinRead::Create(config, _size, &_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_PulseWidthPinReadTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
	}

	TEST_F(Operation_PulseWidthPinReadTests, WhenGettingValue_ThenCorrectValueIsReturned)
	{
		PwmValue pwmValue = { 0.1f, 0.05f };
		EXPECT_CALL(_pwmService, ReadPin(1)).Times(1).WillOnce(Return(pwmValue));
		ASSERT_NEAR(0.05f, _operation->Execute<float>(), 0.001f);

		pwmValue = { 0.025f, 0.004f };
		EXPECT_CALL(_pwmService, ReadPin(1)).Times(1).WillOnce(Return(pwmValue));
		ASSERT_NEAR(0.004f, _operation->Execute<float>(), 0.001f);

		pwmValue = { 0.05f, 0.04f };
		EXPECT_CALL(_pwmService, ReadPin(1)).Times(1).WillOnce(Return(pwmValue));
		ASSERT_NEAR(0.04f, _operation->Execute<float>(), 0.001f);

		pwmValue = { 0.05333333333333f, 0.04f };
		EXPECT_CALL(_pwmService, ReadPin(1)).Times(1).WillOnce(Return(pwmValue));
		ASSERT_NEAR(0.04f, _operation->Execute<float>(), 0.001f);
	}
}
