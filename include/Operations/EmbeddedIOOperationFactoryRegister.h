#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef EMBEDDEDIOOPERATIONFACTORYREGISTER_H
#define EMBEDDEDIOOPERATIONFACTORYREGISTER_H
namespace EmbeddedIOOperations
{
	class EmbeddedIOOperationFactoryRegister
	{
		public:
		static void Register(uint32_t idOffset, OperationArchitecture::OperationFactory *factory, const EmbeddedIOOperations::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif