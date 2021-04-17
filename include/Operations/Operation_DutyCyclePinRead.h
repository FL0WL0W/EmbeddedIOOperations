#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_DUTYCYCLEPINREAD_H
#define OPERATION_DUTYCYCLEPINREAD_H
namespace OperationArchitecture
{
	class Operation_DutyCyclePinRead : public IOperation<float>
	{
	protected:
		EmbeddedIOServices::IPwmService *_pwmService;
		uint16_t _pin;
		uint16_t _minFrequency;
	public:		
        Operation_DutyCyclePinRead(EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency);

		float Execute() override;

		static IOperationBase *Create(const void *config, unsigned int &sizeOut, const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif