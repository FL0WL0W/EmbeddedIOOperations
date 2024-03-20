#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_CANREADDATA_H
#define OPERATION_CANREADDATA_H
namespace EmbeddedIOOperations
{
	class Operation_CANReadData : public OperationArchitecture::Operation<void>
	{
	protected:
		EmbeddedIOServices::ICANService *_canService;
		OperationArchitecture::AbstractOperation *_operation;
		EmbeddedIOServices::can_receive_callback_map_t::iterator _iterator;
		EmbeddedIOServices::CANData_t _data;
		bool _dataChanged = false;
	public:		
        Operation_CANReadData(EmbeddedIOServices::ICANService *canService, const EmbeddedIOServices::CANIdentifier_t identifier, OperationArchitecture::AbstractOperation *operation);
		~Operation_CANReadData();
		void Execute();
		void Sample(const EmbeddedIOServices::CANData_t data);

		static AbstractOperation *Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection, OperationArchitecture::OperationFactory *factory);
	};
}
#endif