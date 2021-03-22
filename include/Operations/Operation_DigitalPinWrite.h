#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef OPERATION_DIGITALPINWRITE_H
#define OPERATION_DIGITALPINWRITE_H
namespace OperationArchitecture
{
	class Operation_DigitalPinWrite : public IOperation<void, bool>
	{
	protected:
		EmbeddedIOServices::IDigitalService *_digitalService;
		uint16_t _pin;
		bool _normalOn;
		bool _highZ;
	public:		
        Operation_DigitalPinWrite(EmbeddedIOServices::IDigitalService *digitalService, uint16_t pin, const bool normalOn, const bool highZ);

		void Execute(bool x) override;

		static IOperationBase *Create(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection, const void *config, unsigned int &sizeOut);
	};
}
#endif