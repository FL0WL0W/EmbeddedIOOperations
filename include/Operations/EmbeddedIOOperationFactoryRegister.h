#include "Operations/OperationFactory.h"
#include "ServiceRegistry.h"
#include "Operations/Operation_AnalogPinRead.h"
#include "Operations/Operation_DigitalPinRead.h"
#include "Operations/Operation_DigitalPinInterruptRecord.h"
#include "Operations/Operation_DutyCyclePinRead.h"
#include "Operations/Operation_FrequencyPinRead.h"
#include "Operations/Operation_PulseWidthPinRead.h"
#include "Operations/Operation_DigitalPinWrite.h"
#include "Operations/Operation_PwmPinWrite.h"
#include "Operations/Operation_GetTick.h"
#include "Operations/Operation_SecondsToTicks.h"
#include "Operations/Operation_TicksToSeconds.h"
#include "Operations/Operation_Record.h"
#include "Operations/Operation_FIRFilter.h"
#include "Operations/Operation_Interval.h"
#include "Operations/Operation_CANReadData.h"
#include "Operations/Operation_CANWriteData.h"
#include "Operations/Operation_CANParseData.h"
#include "Operations/Operation_CANPackData.h"
#include "Operations/Operation_CANCRCJ1850.h"

#ifndef EMBEDDEDIOOPERATIONFACTORYREGISTER_H
#define EMBEDDEDIOOPERATIONFACTORYREGISTER_H
namespace EmbeddedIOOperations
{
	template<uint32_t idOffset, OperationArchitecture::OperationFactory *factory, ServiceRegistry *serviceRegistry>
	constexpr auto RegisterEmbeddedIOOperationFactory = []() {
    	return std::array<OperationArchitecture::OperationFactoryEntry, 19>{{
			{ idOffset + 1, [](const void *config, size_t &sizeOut) { return Operation_AnalogPinRead::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 2, [](const void *config, size_t &sizeOut) { return Operation_DigitalPinRead::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 3, [](const void *config, size_t &sizeOut) { return Operation_DigitalPinInterruptRecord::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 4, [](const void *config, size_t &sizeOut) { return Operation_DutyCyclePinRead::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 5, [](const void *config, size_t &sizeOut) { return Operation_FrequencyPinRead::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 6, [](const void *config, size_t &sizeOut) { return Operation_PulseWidthPinRead::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 7, [](const void *config, size_t &sizeOut) { return Operation_DigitalPinWrite::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 8, [](const void *config, size_t &sizeOut) { return Operation_PwmPinWrite::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 9, [](const void *config, size_t &sizeOut) { return Operation_GetTick::Create(serviceRegistry); } },
			{ idOffset + 10, [](const void *config, size_t &sizeOut) { return Operation_SecondsToTicks::Create(serviceRegistry); } },
			{ idOffset + 11, [](const void *config, size_t &sizeOut) { return Operation_TicksToSeconds::Create(serviceRegistry); } },
			{ idOffset + 12, [](const void *config, size_t &sizeOut) { return Operation_Record<float>::Create(config, sizeOut, serviceRegistry, factory); } },
			{ idOffset + 13, Operation_FIRFilter<float>::Create },
			{ idOffset + 14, [](const void *config, size_t &sizeOut) { return Operation_Interval::Create(config, sizeOut, serviceRegistry, factory); } },
			{ idOffset + 15, [](const void *config, size_t &sizeOut) { return Operation_CANReadData::Create(config, sizeOut, serviceRegistry, factory); } },
			{ idOffset + 16, [](const void *config, size_t &sizeOut) { return Operation_CANWriteData::Create(config, sizeOut, serviceRegistry); } },
			{ idOffset + 17, Operation_CANParseData::Create },
			{ idOffset + 18, Operation_CANPackData::Create },
			{ idOffset + 19, Operation_CANCRCJ1850::Create }
    	}};
	};
}
#endif