#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockCANService.h"
#include "Operations/Operation_CANParseData.h"
#include "Operations/MockOperation.h"
#include "Config.h"
#include <tuple>
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_CANParseDataTests : public ::testing::Test 
	{
		protected:
		AbstractOperation *_operation;
        size_t _expectedSize = 0;
        size_t _buildSize = 0;
        size_t _size = 0;

		Operation_CANParseDataTests()
		{
			_expectedSize = sizeof(uint8_t);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(_expectedSize);
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			// number of variables
			Config::AssignAndOffset<uint8_t>(buildConfig, _buildSize, 15);
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 0, 3, false, true }); // Engine Torque Reduction Failure Status
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 3, 1, true, false }); // Engine Torque Actual Extended Range Invalid
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 0.5, -848, 4, 12, false, false }); // Engine Torque Actual Extended Range
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 17, 1, true, false }); // Powertrain Regulated Generator Control Active
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 18, 1, true, false }); // Accelerator Effective Position Invalid
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 19, 1, true, false }); // Engine Torque Driver Requested Extended Range Invalid
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 0.5, -848, 20, 12, false, false }); // Engine Torque Driver Requested Extended Range
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 100.0f/255, 0, 32, 8, false, false }); // Fuel Filter Remaining Life
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 40, 1, true, false }); // Generator Current Invalid
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 41, 7, false, true }); // Generator Current
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 100.0f/255, 0, 48, 8, false, false }); // Accelerator Effective Position
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 56, 1, true, false }); // Engine Driver Preference Mode Switch 1 Enabled
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 57, 1, true, false }); // Engine Driver Preference Mode Switch 1 Active
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 58, 1, true, false }); // Economy Mode Active Indication On
			Config::AssignAndOffset<Operation_CANParseDataConfig>(buildConfig, _buildSize, { 1, 0, 59, 1, true, false }); // Economy Mode Request Denied Indication On

			_operation = Operation_CANParseData::Create(config, _size);
		}
	};

	TEST_F(Operation_CANParseDataTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
	}

	TEST_F(Operation_CANParseDataTests, ExecutingOperationParsesCANDataCorrectly)
	{
		CANData_t data;
		data.Data[0] = 0x31;
		data.Data[1] = 0x23;
		data.Data[2] = 0xD2;
		data.Data[3] = 0x34;
		data.Data[4] = 0x55;
		data.Data[5] = 0x11;
		data.Data[6] = 0x44;
		data.Data[7] = 0x1F;

		const uint8_t arrayLength = 16;
		Variable variables[arrayLength];
		Variable *variablePtrs[arrayLength];
		for(uint8_t i = 0; i < arrayLength; i++) variablePtrs[i] = &variables[i];
		variables[15] = data;
		_operation->AbstractExecute(variablePtrs);

		ASSERT_EQ(variables[0], 1);
		ASSERT_EQ(variables[1], true);
		ASSERT_EQ(variables[2], -702.5);
		ASSERT_EQ(variables[3], true);
		ASSERT_EQ(variables[4], false);
		ASSERT_EQ(variables[5], true);
		ASSERT_EQ(variables[6], -566);
		ASSERT_FLOAT_EQ(variables[7], 33.333332);
		ASSERT_EQ(variables[8], false);
		ASSERT_EQ(variables[9], 17);
		ASSERT_FLOAT_EQ(variables[10], 26.666668);
		ASSERT_EQ(variables[11], false);
		ASSERT_EQ(variables[12], false);
		ASSERT_EQ(variables[13], false);
		ASSERT_EQ(variables[14], true);
	}
}
