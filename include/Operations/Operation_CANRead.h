#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_CANREAD_H
#define OPERATION_CANREAD_H
namespace EmbeddedIOOperations
{
	class Operation_CANRead : public OperationArchitecture::Operation<void>
	{
	protected:
		EmbeddedIOServices::ICANService *_canService;
		OperationArchitecture::AbstractOperation *_operation;
		EmbeddedIOServices::can_receive_callback_map_t::iterator _iterator;
		uint8_t _data[8];
		bool _dataChanged = false;
	public:		
        Operation_CANRead(EmbeddedIOServices::ICANService *canService, const uint32_t identifier, OperationArchitecture::AbstractOperation *operation);
		~Operation_CANRead();
		void Execute();
		void Sample(const uint8_t data[8]);

		AbstractOperation *Create(const void *config, size_t  &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection, OperationArchitecture::OperationFactory *factory);
	};
}
#endif