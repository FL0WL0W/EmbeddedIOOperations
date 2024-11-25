#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockCANService.h"
#include "Operations/Operation_CANWriteData.h"
#include "Operations/MockOperation.h"
#include "Config.h"
#include <tuple>
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_CANWriteDataTests : public ::testing::Test 
	{
		protected:
		MockCANService _canService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		AbstractOperation *_operation;
        size_t _expectedSize = 0;
        size_t _buildSize = 0;
        size_t _size = 0;

		Operation_CANWriteDataTests()
		{
			_embeddedIOServiceCollection.CANService = &_canService;

			_expectedSize = sizeof(uint32_t); // can identifier
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			//can identifier
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSize, 1);

			_operation = Operation_CANWriteData::Create(config, _size, &_embeddedIOServiceCollection);
		}
	};

	TEST_F(Operation_CANWriteDataTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
	}

	TEST_F(Operation_CANWriteDataTests, ExecutingOperationSendsDataToCANService)
	{
		CANData_t data;
		EXPECT_CALL(_canService, Send(CANIdentifier_t({1, 0}), _, 8))
			.Times(1)
			.WillOnce(SaveArg<1>(&data));

		_operation->Execute(CANData_t({0, 1, 2, 3, 4, 5, 6, 7}));
	}
}
