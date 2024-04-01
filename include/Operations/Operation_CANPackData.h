#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_CANPACKDATA_H
#define OPERATION_CANPACKDATA_H
namespace EmbeddedIOOperations
{
	struct Operation_CANPackDataConfig 
	{
		float Multiplier;
		float Adder;
		uint8_t BitLocation;
		uint8_t BitLength;
		bool CastToBool : 1;
	};

	class Operation_CANPackData : public OperationArchitecture::AbstractOperation
	{
	protected:
		const EmbeddedIOServices::CANData_t *_baseData;
		const Operation_CANPackDataConfig *_configs;
	public:		
        Operation_CANPackData(const EmbeddedIOServices::CANData_t *baseData, const uint8_t numberOfVariables, const Operation_CANPackDataConfig *configs);
		void AbstractExecute(OperationArchitecture::Variable **variables);

		static AbstractOperation *Create(const void *config, size_t  &sizeOut);
	};
}
#endif