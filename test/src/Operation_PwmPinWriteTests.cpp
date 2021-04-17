#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_PwmPinWrite.h"
#include "MockPwmService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_PwmPinWriteTests : public Test
	{
		protected:
		MockPwmService _pwmService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		IOperationBase *_operation;
        unsigned int _size = 0;

		Operation_PwmPinWriteTests() 
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

			EXPECT_CALL(_pwmService, InitPin(1, Out, 2)).Times(1);
			_operation = Operation_PwmPinWrite::Create(config, _size, &_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_PwmPinWriteTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(4, _size);
	}

	TEST_F(Operation_PwmPinWriteTests, WhenWritingValue_ThenCorrectValueIsWritten)
	{
		PwmValue pwmValue = { 0.1f, 0.05f };
		EXPECT_CALL(_pwmService, WritePin(1, pwmValue)).Times(1);
		_operation->Execute(pwmValue.Period, pwmValue.PulseWidth);

		pwmValue = { 0.025f, 0.004f };
		EXPECT_CALL(_pwmService, WritePin(1, pwmValue)).Times(1);
		_operation->Execute(pwmValue.Period, pwmValue.PulseWidth);

		pwmValue = { 0.05f, 0.04f };
		EXPECT_CALL(_pwmService, WritePin(1, pwmValue)).Times(1);
		_operation->Execute(pwmValue.Period, pwmValue.PulseWidth);

		pwmValue = { 0.05333333333333f, 0.04f };
		EXPECT_CALL(_pwmService, WritePin(1, pwmValue)).Times(1);
		_operation->Execute(pwmValue.Period, pwmValue.PulseWidth);
	}
}
