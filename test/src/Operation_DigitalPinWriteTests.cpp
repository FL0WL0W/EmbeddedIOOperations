#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_DigitalPinWrite.h"
#include "MockDigitalService.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_DigitalPinWriteTests : public Test
	{
		protected:
		MockDigitalService _digitalService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		IOperationBase *_operationNormalOff;
		IOperationBase *_operationNormalOn;
		IOperationBase *_operationNormalOffHighZ;
		IOperationBase *_operationNormalOnHighZ;
		unsigned int _sizeNormalOff = 0;
		unsigned int _sizeNormalOn = 0;
		unsigned int _sizeNormalOffHighZ = 0;
		unsigned int _sizeNormalOnHighZ = 0;

		Operation_DigitalPinWriteTests() 
		{

			_embeddedIOServiceCollection.DigitalService = &_digitalService;

			void *configNormalOff = malloc(sizeof(uint16_t) + sizeof(bool) + sizeof(bool));
			void *buildConfig = configNormalOff;

			//pin 1
			*((uint16_t *)buildConfig) = 1;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);

			//NormalOn
			*((bool *)buildConfig) = false;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			//HighZ
			*((bool *)buildConfig) = false;
			buildConfig = (void *)(((bool *)buildConfig) + 1);
			
			EXPECT_CALL(_digitalService, InitPin(1, Out)).Times(1);
			EXPECT_CALL(_digitalService, WritePin(1, false)).Times(1);
			_operationNormalOff = Operation_DigitalPinWrite::Create(&_embeddedIOServiceCollection, configNormalOff, _sizeNormalOff);

			void *configNormalOn = malloc( sizeof(uint16_t) + sizeof(bool) + sizeof(bool));
			buildConfig = configNormalOn;

			//pin 2
			*((uint16_t *)buildConfig) = 2;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);

			//NormalOn
			*((bool *)buildConfig) = true;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			//HighZ
			*((bool *)buildConfig) = false;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			EXPECT_CALL(_digitalService, InitPin(2, Out)).Times(1);
			EXPECT_CALL(_digitalService, WritePin(2, true)).Times(1);
			_operationNormalOn = Operation_DigitalPinWrite::Create(&_embeddedIOServiceCollection, configNormalOn, _sizeNormalOn);

			void *configNormalOffHighZ = malloc(sizeof(uint16_t) + sizeof(bool) + sizeof(bool));
			buildConfig = configNormalOffHighZ;

			//pin 3
			*((uint16_t *)buildConfig) = 3;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);

			//NormalOn
			*((bool *)buildConfig) = false;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			//HighZ
			*((bool *)buildConfig) = true;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			EXPECT_CALL(_digitalService, InitPin(3, Out)).Times(1);
			EXPECT_CALL(_digitalService, WritePin(3, false)).Times(1);
			_operationNormalOffHighZ = Operation_DigitalPinWrite::Create(&_embeddedIOServiceCollection, configNormalOffHighZ, _sizeNormalOffHighZ);

			void *configNormalOnHighZ = malloc(sizeof(uint16_t) + sizeof(bool) + sizeof(bool));
			buildConfig = configNormalOnHighZ;

			//pin 4
			*((uint16_t *)buildConfig) = 4;
			buildConfig = (void *)(((uint16_t *)buildConfig) + 1);

			//NormalOn
			*((bool *)buildConfig) = true;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			//HighZ
			*((bool *)buildConfig) = true;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			EXPECT_CALL(_digitalService, InitPin(4, In)).Times(1);
			_operationNormalOnHighZ = Operation_DigitalPinWrite::Create(&_embeddedIOServiceCollection, configNormalOnHighZ, _sizeNormalOnHighZ);
		}
	};

	TEST_F(Operation_DigitalPinWriteTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(4, _sizeNormalOff);
		ASSERT_EQ(4, _sizeNormalOn);
		ASSERT_EQ(4, _sizeNormalOffHighZ);
		ASSERT_EQ(4, _sizeNormalOnHighZ);
	}
	
	TEST_F(Operation_DigitalPinWriteTests, WhenWritingTrueForNormalOff_ThenPinWrittenTrue)
	{
		EXPECT_CALL(_digitalService, WritePin(1, true)).Times(1);
		_operationNormalOff->Execute(true);
	}
	
	TEST_F(Operation_DigitalPinWriteTests, WhenWritingFalseForNormalOff_ThenPinWrittenFalse)
	{
		EXPECT_CALL(_digitalService, WritePin(1, false)).Times(1);
		_operationNormalOff->Execute(false);
	}
	
	TEST_F(Operation_DigitalPinWriteTests, WhenWritingTrueForNormalOn_ThenPinWrittenFalse)
	{
		EXPECT_CALL(_digitalService, WritePin(2, false)).Times(1);
		_operationNormalOn->Execute(true);
	}
	
	TEST_F(Operation_DigitalPinWriteTests, WhenWritingFalseForNormalOn_ThenPinWrittenTrue)
	{
		EXPECT_CALL(_digitalService, WritePin(2, true)).Times(1);
		_operationNormalOn->Execute(false);
	}
	
	TEST_F(Operation_DigitalPinWriteTests, WhenWritingTrueForNormalOffHighZ_ThenPinConfiguredAsInput)
	{
		EXPECT_CALL(_digitalService, InitPin(3, In)).Times(1);
		_operationNormalOffHighZ->Execute(true);
	}
	
	TEST_F(Operation_DigitalPinWriteTests, WhenWritingFalseForNormalOffHighZ_ThenPinWrittenFalse)
	{
		EXPECT_CALL(_digitalService, InitPin(3, Out)).Times(1);
		EXPECT_CALL(_digitalService, WritePin(3, false)).Times(1);
		_operationNormalOffHighZ->Execute(false);
	}
	
	TEST_F(Operation_DigitalPinWriteTests, WhenWritingTrueForNormalOnHighZ_ThenPinWrittenFalse)
	{
		EXPECT_CALL(_digitalService, InitPin(4, Out)).Times(1);
		EXPECT_CALL(_digitalService, WritePin(4, false)).Times(1);
		_operationNormalOnHighZ->Execute(true);
	}
	
	TEST_F(Operation_DigitalPinWriteTests, WhenWritingFalseForNormalOnHighZ_ThenPinConfiguredAsInput)
	{
		EXPECT_CALL(_digitalService, InitPin(4, In)).Times(1);
		_operationNormalOnHighZ->Execute(false);
	}
}
