#include "Operations/EmbeddedIOOperationFactoryRegister.h"
#include "Operations/Operation_AnalogPinRead.h"
#include "Operations/Operation_DigitalPinRead.h"
#include "Operations/Operation_DigitalPinRecord.h"
#include "Operations/Operation_DutyCyclePinRead.h"
#include "Operations/Operation_FrequencyPinRead.h"
#include "Operations/Operation_PulseWidthPinRead.h"
#include "Operations/Operation_DigitalPinWrite.h"
#include "Operations/Operation_PwmPinWrite.h"
#include "Operations/Operation_GetTick.h"
#include "Operations/Operation_SecondsToTicks.h"
#include "Operations/Operation_TicksToSeconds.h"

using namespace OperationArchitecture;

#ifdef EMBEDDEDIOOPERATIONFACTORYREGISTER_H
namespace EmbeddedIOOperations
{
    void EmbeddedIOOperationFactoryRegister::Register(uint32_t idOffset, OperationFactory *factory, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
    {
        factory->Register(idOffset + 1, [embeddedIOServiceCollection](const void *config, size_t &sizeOut) { return Operation_AnalogPinRead::Create(config, sizeOut, embeddedIOServiceCollection); });
        factory->Register(idOffset + 2, [embeddedIOServiceCollection](const void *config, size_t &sizeOut) { return Operation_DigitalPinRead::Create(config, sizeOut, embeddedIOServiceCollection); });
        factory->Register(idOffset + 3, [embeddedIOServiceCollection](const void *config, size_t &sizeOut) { return Operation_DigitalPinRecord::Create(config, sizeOut, embeddedIOServiceCollection); });
        factory->Register(idOffset + 4, [embeddedIOServiceCollection](const void *config, size_t &sizeOut) { return Operation_DutyCyclePinRead::Create(config, sizeOut, embeddedIOServiceCollection); });
        factory->Register(idOffset + 5, [embeddedIOServiceCollection](const void *config, size_t &sizeOut) { return Operation_FrequencyPinRead::Create(config, sizeOut, embeddedIOServiceCollection); });
        factory->Register(idOffset + 6, [embeddedIOServiceCollection](const void *config, size_t &sizeOut) { return Operation_PulseWidthPinRead::Create(config, sizeOut, embeddedIOServiceCollection); });
        factory->Register(idOffset + 7, [embeddedIOServiceCollection](const void *config, size_t &sizeOut) { return Operation_DigitalPinWrite::Create(config, sizeOut, embeddedIOServiceCollection); });
        factory->Register(idOffset + 8, [embeddedIOServiceCollection](const void *config, size_t &sizeOut) { return Operation_PwmPinWrite::Create(config, sizeOut, embeddedIOServiceCollection); });
        factory->Register(idOffset + 9, Operation_GetTick::Create(embeddedIOServiceCollection));
        factory->Register(idOffset + 10, Operation_SecondsToTicks::Create(embeddedIOServiceCollection));
        factory->Register(idOffset + 11, Operation_TicksToSeconds::Create(embeddedIOServiceCollection));
    }
}
#endif