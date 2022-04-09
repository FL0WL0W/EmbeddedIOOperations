#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_DUTYCYCLEPINREAD_H
#define OPERATION_DUTYCYCLEPINREAD_H
namespace EmbeddedIOOperations
{
	class Operation_DutyCyclePinRead : public OperationArchitecture::IOperation<float>
	{
	protected:
		EmbeddedIOServices::IPwmService *_pwmService;
		uint16_t _pin;
		uint16_t _minFrequency;
	public:		
        Operation_DutyCyclePinRead(EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency);
		float Execute() override;

		static OperationArchitecture::IOperationBase *Create(const void *config, size_t &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif