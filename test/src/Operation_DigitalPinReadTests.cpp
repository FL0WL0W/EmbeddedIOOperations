#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_DigitalPinRead.h"
#include "MockDigitalService.h"
#include "Config.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_DigitalPinReadTests : public Test
	{
		protected:
		MockDigitalService _digitalService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		AbstractOperation *_operationInverted;
		AbstractOperation *_operationUninverted;
        size_t _sizeInverted = 0;
        size_t _sizeUnInverted = 0;
        size_t _expectedSize = 0;
        size_t _buildSizeInverted = 0;
        size_t _buildSizeUnInverted = 0;

		Operation_DigitalPinReadTests() 
		{
			_embeddedIOServiceCollection.DigitalService = &_digitalService;

			_expectedSize = sizeof(uint16_t);
			Config::AlignAndAddSize<bool>(_expectedSize);
			void *configUninverted = malloc(_expectedSize);
			void *buildConfig = configUninverted;

			//pin 1
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSizeUnInverted, 1);
			//inverted false
			Config::AssignAndOffset<bool>(buildConfig, _buildSizeUnInverted, false);
			
			void *configInverted = malloc(_expectedSize);
			buildConfig = configInverted;

			//pin 2
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSizeInverted, 2);
			//inverted true
			Config::AssignAndOffset<bool>(buildConfig, _buildSizeInverted, true);

			EXPECT_CALL(_digitalService, InitPin(1, In)).Times(1);
			EXPECT_CALL(_digitalService, InitPin(2, In)).Times(1);
			_operationUninverted = Operation_DigitalPinRead::Create(configUninverted, _sizeInverted, &_embeddedIOServiceCollection);
			_operationInverted = Operation_DigitalPinRead::Create(configInverted, _sizeUnInverted, &_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_DigitalPinReadTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSizeUnInverted);
		ASSERT_EQ(_expectedSize, _buildSizeInverted);
		ASSERT_EQ(_expectedSize, _sizeUnInverted);
		ASSERT_EQ(_expectedSize, _sizeInverted);
	}

	TEST_F(Operation_DigitalPinReadTests, WhenGettingHighForUninverted_ThenTrueIsReturned)
	{
		EXPECT_CALL(_digitalService, ReadPin(1)).Times(1).WillOnce(Return(true));
		ASSERT_EQ(true, _operationUninverted->Execute<bool>());
	}

	TEST_F(Operation_DigitalPinReadTests, WhenGettingLowForUninverted_ThenFalseIsReturned)
	{
		EXPECT_CALL(_digitalService, ReadPin(1)).Times(1).WillOnce(Return(false));
		ASSERT_EQ(false, _operationUninverted->Execute<bool>());
	}

	TEST_F(Operation_DigitalPinReadTests, WhenGettingHighForInverted_ThenFalseIsReturned)
	{
		EXPECT_CALL(_digitalService, ReadPin(2)).Times(1).WillOnce(Return(true));
		ASSERT_EQ(false, _operationInverted->Execute<bool>());
	}

	TEST_F(Operation_DigitalPinReadTests, WhenGettingLowForInverted_ThenTrueIsReturned)
	{
		EXPECT_CALL(_digitalService, ReadPin(2)).Times(1).WillOnce(Return(false));
		ASSERT_EQ(true, _operationInverted->Execute<bool>());
	}
}
