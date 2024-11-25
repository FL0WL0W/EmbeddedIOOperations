#include "Operations/Operation_CANWriteData.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_CANWRITEDATA_H
namespace EmbeddedIOOperations
{
	Operation_CANWriteData::Operation_CANWriteData( ICANService *canService, const CANIdentifier_t identifier) :
		_canService(canService),
        _identifier(identifier)
	{
	}

	void Operation_CANWriteData::Execute(CANData_t data)
	{
        _canService->Send(_identifier, data, 8);
	}

	AbstractOperation *Operation_CANWriteData::Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
	{
		const CANIdentifier_t identifier = Config::CastAndOffset<CANIdentifier_t>(config, sizeOut);
		return new Operation_CANWriteData(embeddedIOServiceCollection->CANService, identifier);
	}
}
#endif