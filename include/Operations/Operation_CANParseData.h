#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_CANPARSEDATA_H
#define OPERATION_CANPARSEDATA_H
namespace EmbeddedIOOperations
{
	struct Operation_CANParseDataConfig 
	{
		float Multiplier;
		float Adder;
		uint8_t BitLocation;
		uint8_t BitLength;
		bool CastToBool : 1;
		bool CastToInt : 1;
	};

	class Operation_CANParseData : public OperationArchitecture::AbstractOperation
	{
	protected:
		const Operation_CANParseDataConfig *_configs;
	public:		
        Operation_CANParseData(const uint8_t numberOfVariables, const Operation_CANParseDataConfig *configs);
		void AbstractExecute(OperationArchitecture::Variable **variables);

		static AbstractOperation *Create(const void *config, size_t  &sizeOut);
	};
}
#endif