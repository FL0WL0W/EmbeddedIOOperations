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

#ifdef EMBEDDEDIOOPERATIONFACTORYREGISTER_H

namespace OperationArchitecture
{
    void EmbeddedIOOperationFactoryRegister::Register(EmbeddedIOOperationFactory *factory)
    {
        factory->Register(1, Operation_AnalogPinRead::Create);
        factory->Register(2, Operation_DigitalPinRead::Create);
        factory->Register(3, Operation_DigitalPinRecord::Create);
        factory->Register(4, Operation_DutyCyclePinRead::Create);
        factory->Register(5, Operation_FrequencyPinRead::Create);
        factory->Register(6, Operation_PulseWidthPinRead::Create);
        factory->Register(7, Operation_DigitalPinWrite::Create);
        factory->Register(8, Operation_PwmPinWrite::Create);
        factory->Register(9, Operation_GetTick::Create);
        factory->Register(10, Operation_SecondsToTicks::Create);
        factory->Register(11, Operation_TicksToSeconds::Create);
    }
}

#endif