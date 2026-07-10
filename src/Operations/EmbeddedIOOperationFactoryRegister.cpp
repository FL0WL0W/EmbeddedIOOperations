#include "Operations/EmbeddedIOOperationFactoryRegister.h"
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

using namespace OperationArchitecture;

#ifdef EMBEDDEDIOOPERATIONFACTORYREGISTER_H
namespace EmbeddedIOOperations
{
    void EmbeddedIOOperationFactoryRegister::Register(uint32_t idOffset, OperationFactory *factory, const ServiceRegistry *serviceRegistry)
    {
        if(serviceRegistry->TryGet<EmbeddedIOServices::IAnalogService>() != 0) factory->Register(idOffset + 1, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_AnalogPinRead::Create(config, sizeOut, serviceRegistry); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::IDigitalService>() != 0) factory->Register(idOffset + 2, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_DigitalPinRead::Create(config, sizeOut, serviceRegistry); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::IDigitalService>() != 0 && serviceRegistry->TryGet<EmbeddedIOServices::ITimerService>() != 0) factory->Register(idOffset + 3, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_DigitalPinInterruptRecord::Create(config, sizeOut, serviceRegistry); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::IPwmService>() != 0) factory->Register(idOffset + 4, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_DutyCyclePinRead::Create(config, sizeOut, serviceRegistry); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::IPwmService>() != 0) factory->Register(idOffset + 5, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_FrequencyPinRead::Create(config, sizeOut, serviceRegistry); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::IPwmService>() != 0) factory->Register(idOffset + 6, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_PulseWidthPinRead::Create(config, sizeOut, serviceRegistry); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::IDigitalService>() != 0) factory->Register(idOffset + 7, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_DigitalPinWrite::Create(config, sizeOut, serviceRegistry); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::IPwmService>() != 0) factory->Register(idOffset + 8, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_PwmPinWrite::Create(config, sizeOut, serviceRegistry); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::ITimerService>() != 0) factory->Register(idOffset + 9, Operation_GetTick::Create(serviceRegistry));
        if(serviceRegistry->TryGet<EmbeddedIOServices::ITimerService>() != 0) factory->Register(idOffset + 10, Operation_SecondsToTicks::Create(serviceRegistry));
        if(serviceRegistry->TryGet<EmbeddedIOServices::ITimerService>() != 0) factory->Register(idOffset + 11, Operation_TicksToSeconds::Create(serviceRegistry));
        if(serviceRegistry->TryGet<EmbeddedIOServices::ITimerService>() != 0) factory->Register(idOffset + 12, [serviceRegistry, factory](const void *config, size_t &sizeOut) { return Operation_Record<float>::Create(config, sizeOut, serviceRegistry, factory); });
        factory->Register(idOffset + 13, Operation_FIRFilter<float>::Create);
        if(serviceRegistry->TryGet<EmbeddedIOServices::ITimerService>() != 0) factory->Register(idOffset + 14, [serviceRegistry, factory](const void *config, size_t &sizeOut) { return Operation_Interval::Create(config, sizeOut, serviceRegistry, factory); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::ICANService>() != 0) factory->Register(idOffset + 15, [serviceRegistry, factory](const void *config, size_t &sizeOut) { return Operation_CANReadData::Create(config, sizeOut, serviceRegistry, factory); });
        if(serviceRegistry->TryGet<EmbeddedIOServices::ICANService>() != 0) factory->Register(idOffset + 16, [serviceRegistry](const void *config, size_t &sizeOut) { return Operation_CANWriteData::Create(config, sizeOut, serviceRegistry); });
        factory->Register(idOffset + 17, Operation_CANParseData::Create);
        factory->Register(idOffset + 18, Operation_CANPackData::Create);
    }
}
#endif