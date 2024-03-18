#include "Operations/Operation_CANRead.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_CANREAD_H
namespace EmbeddedIOOperations
{
	Operation_CANRead::Operation_CANRead( ICANService *canService, const uint32_t identifier, AbstractOperation *operation) :
		_canService(canService),
		_operation(operation)
	{
		_iterator = _canService->RegisterReceiveCallBack(identifier, [this](can_send_callback_t send, const CANData_t data) { this->Sample(data); });
	}

	Operation_CANRead::~Operation_CANRead()
	{
		_canService->UnRegisterReceiveCallBack(_iterator);
	}

	void Operation_CANRead::Execute()
	{
		//if data hasn't changed, do nothing
		if(!_dataChanged)
			return;

		CANData_t data;
		//put this in a while loop in case CAN sample comes in while we are copying data to temporary buffer
		while(_dataChanged)
		{
			_dataChanged = false;
			std::memcpy(&data, &_data, sizeof(CANData_t));
		}

		//we have our data, feed it to our operation
		_operation->Execute(data);
	}

	void Operation_CANRead::Sample(const CANData_t data)
	{
		if(std::memcmp(&data, &_data, sizeof(CANData_t)) == 0)
			return;
		std::memcpy(&_data, &data, sizeof(CANData_t));
		_dataChanged = true;
	}

	AbstractOperation *Operation_CANRead::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection, OperationFactory *factory)
	{
		const uint32_t identifier = Config::CastAndOffset<uint32_t>(config, sizeOut);
		AbstractOperation * const operation = factory->Create(config, sizeOut); //this should be an operation that takes data[8] as a parameter and returns nothing. should probably do some sort of checking here
		return new Operation_CANRead(embeddedIOServiceCollection->CANService, identifier, operation);
	}
}
#endif