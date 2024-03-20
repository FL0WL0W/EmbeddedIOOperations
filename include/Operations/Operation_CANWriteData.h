#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_CANWRITEDATA_H
#define OPERATION_CANWRITEDATA_H
namespace EmbeddedIOOperations
{
	class Operation_CANWriteData : public OperationArchitecture::Operation<void, EmbeddedIOServices::CANData_t>
	{
	protected:
		EmbeddedIOServices::ICANService *_canService;
		const EmbeddedIOServices::CANIdentifier_t _identifier;
	public:		
        Operation_CANWriteData(EmbeddedIOServices::ICANService *canService, const EmbeddedIOServices::CANIdentifier_t identifier);
		void Execute(EmbeddedIOServices::CANData_t data);

		static AbstractOperation *Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif