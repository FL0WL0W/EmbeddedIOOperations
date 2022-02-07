#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_DigitalPinWrite.h"
#include "MockDigitalService.h"
#include "Config.h"
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

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
		size_t _sizeNormalOff = 0;
		size_t _sizeNormalOn = 0;
		size_t _sizeNormalOffHighZ = 0;
		size_t _sizeNormalOnHighZ = 0;
		size_t _expectedSize = 0;
		size_t _buildSizeNormalOff = 0;
		size_t _buildSizeNormalOn = 0;
		size_t _buildSizeNormalOffHighZ = 0;
		size_t _buildSizeNormalOnHighZ = 0;

		Operation_DigitalPinWriteTests() 
		{
			_embeddedIOServiceCollection.DigitalService = &_digitalService;

			_expectedSize = sizeof(uint16_t);
			Config::AlignAndAddSize<uint8_t>(_expectedSize);

			void *configNormalOff = malloc(_expectedSize);
			void *buildConfig = configNormalOff;

			//pin 1
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSizeNormalOff, 1);
			//NormalOn / HighZ
			Config::AssignAndOffset<uint8_t>(buildConfig, _buildSizeNormalOff, 0x00);
			
			EXPECT_CALL(_digitalService, InitPin(1, Out)).Times(1);
			EXPECT_CALL(_digitalService, WritePin(1, false)).Times(1);
			_operationNormalOff = Operation_DigitalPinWrite::Create(configNormalOff, _sizeNormalOff, &_embeddedIOServiceCollection);

			void *configNormalOn = malloc( _expectedSize);
			buildConfig = configNormalOn;

			//pin 2
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSizeNormalOn, 2);
			//NormalOn / HighZ
			Config::AssignAndOffset<uint8_t>(buildConfig, _buildSizeNormalOn, 0x01);

			EXPECT_CALL(_digitalService, InitPin(2, Out)).Times(1);
			EXPECT_CALL(_digitalService, WritePin(2, true)).Times(1);
			_operationNormalOn = Operation_DigitalPinWrite::Create(configNormalOn, _sizeNormalOn, &_embeddedIOServiceCollection);

			void *configNormalOffHighZ = malloc(_expectedSize);
			buildConfig = configNormalOffHighZ;

			//pin 3
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSizeNormalOffHighZ, 3);
			//NormalOn / HighZ
			Config::AssignAndOffset<uint8_t>(buildConfig, _buildSizeNormalOffHighZ, 0x02);

			EXPECT_CALL(_digitalService, InitPin(3, Out)).Times(1);
			EXPECT_CALL(_digitalService, WritePin(3, false)).Times(1);
			_operationNormalOffHighZ = Operation_DigitalPinWrite::Create(configNormalOffHighZ, _sizeNormalOffHighZ, &_embeddedIOServiceCollection);

			void *configNormalOnHighZ = malloc(_expectedSize);
			buildConfig = configNormalOnHighZ;

			//pin 4
			Config::AssignAndOffset<uint16_t>(buildConfig, _buildSizeNormalOnHighZ, 4);
			//NormalOn / HighZ
			Config::AssignAndOffset<uint8_t>(buildConfig, _buildSizeNormalOnHighZ, 0x03);

			EXPECT_CALL(_digitalService, InitPin(4, In)).Times(1);
			_operationNormalOnHighZ = Operation_DigitalPinWrite::Create(configNormalOnHighZ, _sizeNormalOnHighZ, &_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_DigitalPinWriteTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSizeNormalOff);
		ASSERT_EQ(_expectedSize, _buildSizeNormalOn);
		ASSERT_EQ(_expectedSize, _buildSizeNormalOffHighZ);
		ASSERT_EQ(_expectedSize, _buildSizeNormalOnHighZ);
		ASSERT_EQ(_expectedSize, _sizeNormalOff);
		ASSERT_EQ(_expectedSize, _sizeNormalOn);
		ASSERT_EQ(_expectedSize, _sizeNormalOffHighZ);
		ASSERT_EQ(_expectedSize, _sizeNormalOnHighZ);
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
