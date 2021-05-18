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
		bool _normalOn : 1;
		bool _highZ : 1;
	public:		
        Operation_DigitalPinWrite(EmbeddedIOServices::IDigitalService *digitalService, uint16_t pin, const bool normalOn, const bool highZ);

		void Execute(bool x) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut, const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif