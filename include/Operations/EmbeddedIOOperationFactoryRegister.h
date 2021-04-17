#include "Operations/OperationFactory.h"
#include "EmbeddedIOServiceCollection.h"

#ifndef EMBEDDEDIOOPERATIONFACTORYREGISTER_H
#define EMBEDDEDIOOPERATIONFACTORYREGISTER_H
namespace OperationArchitecture
{
	class EmbeddedIOOperationFactoryRegister
	{
		public:
		static void Register(uint32_t idOffset, OperationFactory *factory, const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
	};
}
#endif