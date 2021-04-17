#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_DIGITALPINREAD_H
#define OPERATION_DIGITALPINREAD_H
namespace OperationArchitecture
{
	class Operation_DigitalPinRead : public IOperation<bool>
	{
	protected:
		EmbeddedIOServices::IDigitalService *_digitalService;
		uint16_t _pin;
		bool _inverted;
	public:		
        Operation_DigitalPinRead(EmbeddedIOServices::IDigitalService *digitalService, uint16_t pin, bool inverted);

		bool Execute() override;

		static IOperationBase *Create(const void *config, unsigned int &sizeOut, const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif