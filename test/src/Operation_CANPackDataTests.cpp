#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockCANService.h"
#include "Operations/Operation_CANPackData.h"
#include "Operations/MockOperation.h"
#include "Config.h"
#include <tuple>
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_CANPackDataTests : public ::testing::Test 
	{
		protected:
		AbstractOperation *_operation;
        size_t _expectedSize = 0;
        size_t _buildSize = 0;
        size_t _size = 0;

		Operation_CANPackDataTests()
		{
			_expectedSize = sizeof(CANData_t);
			Config::AlignAndAddSize<uint8_t>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(_expectedSize);
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			// number of variables
			Config::AssignAndOffset<CANData_t>(buildConfig, _buildSize, { 0, 0, 0x80, 0, 0, 0, 0, 0x0F });
			Config::AssignAndOffset<uint8_t>(buildConfig, _buildSize, 15);
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 0, 3, false }); // Engine Torque Reduction Failure Status
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 3, 1, true }); // Engine Torque Actual Extended Range Invalid
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 0.5, -848, 4, 12, false }); // Engine Torque Actual Extended Range
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 17, 1, true }); // Powertrain Regulated Generator Control Active
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 18, 1, true }); // Accelerator Effective Position Invalid
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 19, 1, true }); // Engine Torque Driver Requested Extended Range Invalid
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 0.5, -848, 20, 12, false }); // Engine Torque Driver Requested Extended Range
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 100.0f/255, 0, 32, 8, false }); // Fuel Filter Remaining Life
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 40, 1, true }); // Generator Current Invalid
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 41, 7, false }); // Generator Current
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 100.0f/255, 0, 48, 8, false }); // Accelerator Effective Position
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 56, 1, true }); // Engine Driver Preference Mode Switch 1 Enabled
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 57, 1, true }); // Engine Driver Preference Mode Switch 1 Active
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 58, 1, true }); // Economy Mode Active Indication On
			Config::AssignAndOffset<Operation_CANPackDataConfig>(buildConfig, _buildSize, { 1, 0, 59, 1, true }); // Economy Mode Request Denied Indication On

			_operation = Operation_CANPackData::Create(config, _size);
		}
	};

	TEST_F(Operation_CANPackDataTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
	}

	TEST_F(Operation_CANPackDataTests, ExecutingOperationPacksCANDataCorrectly)
	{
		CANData_t data = _operation->Execute<CANData_t>(1, true, -711.5f, true, false, true, -575.0f, 33.4f, false, 17, 26.7f, false, false, false, true);
		ASSERT_EQ(data.Data[0], 0x31);
		ASSERT_EQ(data.Data[1], 0x11);
		ASSERT_EQ(data.Data[2], 0xD2);
		ASSERT_EQ(data.Data[3], 0x22);
		ASSERT_EQ(data.Data[4], 0x55);
		ASSERT_EQ(data.Data[5], 0x11);
		ASSERT_EQ(data.Data[6], 0x44);
		ASSERT_EQ(data.Data[7], 0x1F);
	}
}
