#include "Operations/Operation_CANParseData.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_CANPARSEDATA_H
namespace EmbeddedIOOperations
{
	Operation_CANParseData::Operation_CANParseData(const uint8_t numberOfVariables, const Operation_CANParseDataConfig *configs) :
		AbstractOperation(numberOfVariables, 1),
		_configs(configs)
	{
	}

	void Operation_CANParseData::AbstractExecute(Variable **variables)
	{
		const CANData_t data = *variables[NumberOfReturnVariables];
		uint64_t dataAsInt = data.Data[0];
		for(int i = 1; i < 8; i++)
		{
			dataAsInt <<= 8;
			dataAsInt |= data.Data[i];
		}
		for(uint8_t i = 0; i < NumberOfReturnVariables; i++)
		{
			const uint64_t rawValue = (dataAsInt >> (64 - (_configs[i].BitLocation + _configs[i].BitLength))) & (0xFFFFFFFFFFFFFFFF >> (64 - _configs[i].BitLength));
			if(_configs[i].CastToBool)
			{
				*variables[i] = static_cast<bool>(rawValue);
			}
			else if(_configs[i].CastToInt)
			{
				*variables[i] = Variable::Int64ToVariable(rawValue * _configs[i].Multiplier + _configs[i].Adder, UINT8);
			}
			else
			{
				*variables[i] = rawValue * _configs[i].Multiplier + _configs[i].Adder;
			}
		}
	}

	AbstractOperation *Operation_CANParseData::Create(const void *config, size_t  &sizeOut)
	{
		const uint8_t numberOfVariables = Config::CastAndOffset<uint8_t>(config, sizeOut);
		const Operation_CANParseDataConfig *configs = Config::CastAndOffsetPointer<Operation_CANParseDataConfig>(config, sizeOut);
		for(uint8_t i = 1; i < numberOfVariables; i++)
			Config::AlignAndAddSize<Operation_CANParseDataConfig>(sizeOut);
		return new Operation_CANParseData(numberOfVariables, configs);
	}
}
#endif