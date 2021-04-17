#include "Operations/EmbeddedIOOperationFactoryRegister.h"
#include "CreateWithParameters.h"
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

using namespace EmbeddedIOServices;

#ifdef EMBEDDEDIOOPERATIONFACTORYREGISTER_H

namespace OperationArchitecture
{
    void EmbeddedIOOperationFactoryRegister::Register(uint32_t idOffset, OperationFactory *factory, const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
    {
        factory->Register(idOffset + 1, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_AnalogPinRead::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 2, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_DigitalPinRead::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 3, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_DigitalPinRecord::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 4, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_DutyCyclePinRead::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 5, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_FrequencyPinRead::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 6, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_PulseWidthPinRead::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 7, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_DigitalPinWrite::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 8, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_PwmPinWrite::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 9, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_GetTick::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 10, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_SecondsToTicks::Create, embeddedIOServiceCollection));
        factory->Register(idOffset + 11, new CreateWithParameters<const EmbeddedIOServiceCollection *>(Operation_TicksToSeconds::Create, embeddedIOServiceCollection));
    }
}

#endif