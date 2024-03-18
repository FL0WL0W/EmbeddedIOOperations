#include "Operations/Operation_CANReadData.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_CANREADDATA_H
namespace EmbeddedIOOperations
{
	Operation_CANReadData::Operation_CANReadData( ICANService *canService, const CANIdentifier_t identifier, AbstractOperation *operation) :
		_canService(canService),
		_operation(operation)
	{
		_iterator = _canService->RegisterReceiveCallBack(identifier, [this](can_send_callback_t send, const CANData_t data) { this->Sample(data); });
	}

	Operation_CANReadData::~Operation_CANReadData()
	{
		_canService->UnRegisterReceiveCallBack(_iterator);
	}

	void Operation_CANReadData::Execute()
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

	void Operation_CANReadData::Sample(const CANData_t data)
	{
		if(std::memcmp(&data, &_data, sizeof(CANData_t)) == 0)
			return;
		std::memcpy(&_data, &data, sizeof(CANData_t));
		_dataChanged = true;
	}

	AbstractOperation *Operation_CANReadData::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection, OperationFactory *factory)
	{
		const CANIdentifier_t identifier = Config::CastAndOffset<CANIdentifier_t>(config, sizeOut);
		AbstractOperation * const operation = factory->Create(config, sizeOut); //this should be an operation that takes data[8] as a parameter and returns nothing. should probably do some sort of checking here
		return new Operation_CANReadData(embeddedIOServiceCollection->CANService, identifier, operation);
	}
}
#endif