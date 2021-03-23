#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_DigitalPinRead.h"
#include "MockDigitalService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_DigitalPinReadTests : public Test
	{
		protected:
		MockDigitalService _digitalService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		IOperationBase *_operationInverted;
		IOperationBase *_operationUninverted;
        unsigned int _sizeInverted = 0;
        unsigned int _sizeUnInverted = 0;

		Operation_DigitalPinReadTests() 
		{
			_embeddedIOServiceCollection.DigitalService = &_digitalService;

			void *configUninverted = malloc(sizeof(uint16_t) + sizeof(bool));
			void *buildConfig = configUninverted;

			//pin 1
			*((uint16_t *)buildConfig) = 1;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);

			*((bool *)buildConfig) = false;
			buildConfig = (void *)(((bool *)buildConfig) + 1);
			
			void *configInverted = malloc(sizeof(uint16_t) + sizeof(bool));
			buildConfig = configInverted;

			//pin 2
			*((uint16_t *)buildConfig) = 2;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);

			*((bool *)buildConfig) = true;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			EXPECT_CALL(_digitalService, InitPin(1, In)).Times(1);
			EXPECT_CALL(_digitalService, InitPin(2, In)).Times(1);
			_operationUninverted = Operation_DigitalPinRead::Create(&_embeddedIOServiceCollection, configUninverted, _sizeInverted);
			_operationInverted = Operation_DigitalPinRead::Create(&_embeddedIOServiceCollection, configInverted, _sizeUnInverted);
		}
	};

	TEST_F(Operation_DigitalPinReadTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(3, _sizeUnInverted);
		ASSERT_EQ(3, _sizeInverted);
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
