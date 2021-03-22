#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_ANALOGPINREAD_H
#define OPERATION_ANALOGPINREAD_H
namespace OperationArchitecture
{
	class Operation_AnalogPinRead : public IOperation<float>
	{
	protected:
		EmbeddedIOServices::IAnalogService *_analogService;
		uint16_t _pin;
	public:		
        Operation_AnalogPinRead(EmbeddedIOServices::IAnalogService *analogService, const uint16_t pin);

		float Execute() override;

		static IOperationBase *Create(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut);
	};
}
#endif