#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_DIGITALPINREAD_H
#define OPERATION_DIGITALPINREAD_H
namespace EmbeddedIOOperations
{
	class Operation_DigitalPinRead : public OperationArchitecture::IOperation<bool>
	{
	protected:
		EmbeddedIOServices::IDigitalService *_digitalService;
		uint16_t _pin;
		bool _inverted;
	public:		
        Operation_DigitalPinRead(EmbeddedIOServices::IDigitalService *digitalService, uint16_t pin, bool inverted);
		bool Execute() override;

		static OperationArchitecture::IOperationBase *Create(const void *config, size_t &sizeOut, const EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif