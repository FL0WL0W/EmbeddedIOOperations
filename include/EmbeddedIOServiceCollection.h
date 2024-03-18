#include "PinDirection.h"
#include "IDigitalService.h"
#include "IPwmService.h"
#include "IAnalogService.h"
#include "ITimerService.h"
#include "ICANService.h"

#ifndef EMBEDDEDIOSERVICECOLLECTION_H
#define EMBEDDEDIOSERVICECOLLECTION_H
namespace EmbeddedIOOperations
{
	struct EmbeddedIOServiceCollection
	{
	public:
		EmbeddedIOServices::IDigitalService *DigitalService;
		EmbeddedIOServices::IPwmService *PwmService;
		EmbeddedIOServices::IAnalogService *AnalogService;
		EmbeddedIOServices::ITimerService *TimerService;
		EmbeddedIOServices::ICANService *CANService;
	};
}
#endif
