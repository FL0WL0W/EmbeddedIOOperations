#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "ICANService.h"

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
		uint8_t Reserved;
	};

	class Operation_CANPackData : public OperationArchitecture::AbstractOperation
	{
	protected:
		const EmbeddedIOServices::CANData_t * const _baseData;
		const Operation_CANPackDataConfig * const _configs;
		const uint8_t _numberOfVariables;
	public:		
        Operation_CANPackData(const EmbeddedIOServices::CANData_t * const baseData, const uint8_t numberOfVariables, const Operation_CANPackDataConfig * const configs);
		void AbstractExecute(OperationArchitecture::Variable **variables);

		static AbstractOperation *Create(const void *config, size_t  &sizeOut);
	};
}
#endif