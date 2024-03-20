#include "Operations/Operation_CANPackData.h"
#include "Config.h"

using namespace OperationArchitecture;
using namespace EmbeddedIOServices;

#ifdef OPERATION_CANPACKDATA_H
namespace EmbeddedIOOperations
{
	Operation_CANPackData::Operation_CANPackData(const CANData_t *baseData, const uint8_t numberOfVariables, const Operation_CANPackDataConfig *configs) :
		AbstractOperation(1, numberOfVariables),
		_baseData(baseData),
		_configs(configs)
	{
	}

	void Operation_CANPackData::AbstractExecute(Variable **variables)
	{
		uint64_t dataAsInt = 0;
		for(uint8_t i = 0; i < NumberOfParameters; i++)
		{
			uint64_t rawValue;
			if(_configs[i].CastToBool)
			{
				rawValue = static_cast<bool>(*variables[i+1]);
			}
			else
			{
				rawValue = (*variables[i+1] - _configs[i].Adder) / _configs[i].Multiplier;
			}
			dataAsInt |= (rawValue & (0xFFFFFFFFFFFFFFFF >> (64 - _configs[i].BitLength))) << (64 - (_configs[i].BitLocation + _configs[i].BitLength));
		}
		CANData_t data = *_baseData;
		for(int i = 7; i >= 0; i--)
		{
			data.Data[i] |= dataAsInt & 0xFF;
			dataAsInt >>= 8;
		}
		*variables[0] = data;
	}

	AbstractOperation *Operation_CANPackData::Create(const void *config, size_t  &sizeOut)
	{
		const CANData_t *baseData = Config::CastAndOffsetPointer<CANData_t>(config, sizeOut);
		const uint8_t numberOfVariables = Config::CastAndOffset<uint8_t>(config, sizeOut);
		const Operation_CANPackDataConfig *configs = Config::CastAndOffsetPointer<Operation_CANPackDataConfig>(config, sizeOut);
		for(uint8_t i = 1; i < numberOfVariables; i++)
			Config::AlignAndAddSize<Operation_CANPackDataConfig>(sizeOut);
		return new Operation_CANPackData(baseData, numberOfVariables, configs);
	}
}
#endif