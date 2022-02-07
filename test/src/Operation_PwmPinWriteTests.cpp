#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_PwmPinWrite.h"
#include "MockPwmService.h"
#include "Config.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_PwmPinWriteTests : public Test
	{
		protected:
		MockPwmService _pwmService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		IOperationBase *_operation;
        size_t _size = 0;
        size_t _buildSize = 0;
        size_t _expectedSize = 0;


		Operation_PwmPinWriteTests() 
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

			EXPECT_CALL(_pwmService, InitPin(1, Out, 2)).Times(1);
			_operation = Operation_PwmPinWrite::Create(config, _size, &_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_PwmPinWriteTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
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
