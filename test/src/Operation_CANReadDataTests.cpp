#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockCANService.h"
#include "Operations/Operation_CANReadData.h"
#include "Operations/MockOperation.h"
#include "Config.h"
#include <tuple>
using namespace testing;
using namespace EmbeddedIOServices;
using namespace OperationArchitecture;
using namespace EmbeddedIOOperations;

namespace UnitTests
{
	class Operation_CANReadDataTests : public ::testing::Test 
	{
		protected:
		MockOperation<void, CANData_t> _mockOperation;
		MockCANService _canService;
		EmbeddedIOServiceCollection _embeddedIOServiceCollection;
		OperationFactory _operationFactory;
		AbstractOperation *_operation;
        size_t _expectedSize = 0;
        size_t _buildSize = 0;
        size_t _size = 0;

		Operation_CANReadDataTests()
		{
			_embeddedIOServiceCollection.CANService = &_canService;
			_operationFactory.Register(1, &_mockOperation);

			_expectedSize = sizeof(uint32_t); // can identifier
			Config::AlignAndAddSize<uint32_t>(_expectedSize); // operationid
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			//can identifier
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSize, 1);
			//opertaion id
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSize, 1);

			_operation = Operation_CANReadData::Create(config, _size, &_embeddedIOServiceCollection, &_operationFactory);
		}
	};

	TEST_F(Operation_CANReadDataTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
	}

	TEST_F(Operation_CANReadDataTests, CallingIdentifierNotSubscribedDoesNotCallOperation)
	{
		std::get<0>(_mockOperation.Parameters) = { 1 };
		_canService.Receive({2, 0}, { 2 });
		_operation->Execute();

	 	ASSERT_EQ(1, std::get<0>(_mockOperation.Parameters).data[0]) << "Operation called";	
	}

	TEST_F(Operation_CANReadDataTests, CallingIdentifierSubscribedCallsOperationOnce)
	{
		std::get<0>(_mockOperation.Parameters) = { 1 };
		_canService.Receive({1, 0}, { 2 });
		_operation->Execute();

	 	ASSERT_EQ(2, std::get<0>(_mockOperation.Parameters).data[0]) << "Operation not called";	

		std::get<0>(_mockOperation.Parameters) = { 1 };
		_operation->Execute();
	 	ASSERT_EQ(1, std::get<0>(_mockOperation.Parameters).data[0]) << "Operation called twice";	
	}
}
