#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_PWMPINWRITE_H
#define OPERATION_PWMPINWRITE_H
namespace OperationArchitecture
{
	class Operation_PwmPinWrite : public IOperation<void, float, float>
	{
	protected:
		EmbeddedIOServices::IPwmService *_pwmService;
		uint16_t _pin;
		uint16_t _minFrequency;
	public:		
        Operation_PwmPinWrite(EmbeddedIOServices::IPwmService *pwmService, const uint16_t pin, const uint16_t minFrequency);

		void Execute(float period, float pulseWidth) override;

		static IOperationBase *Create(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut);
	};
}
#endif