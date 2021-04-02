#include <map>
#include "Operations/EmbeddedIOOperationFactory.h"

#ifndef EMBEDDEDIOOPERATIONFACTORYREGISTER_H
#define EMBEDDEDIOOPERATIONFACTORYREGISTER_H
namespace OperationArchitecture
{
	class EmbeddedIOOperationFactoryRegister
	{
		static void Register(EmbeddedIOOperationFactory *factory);
	};
}
#endif