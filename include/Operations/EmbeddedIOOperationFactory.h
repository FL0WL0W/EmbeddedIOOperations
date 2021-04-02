#include <map>
#include "Operations/IOperation.h"
#include "EmbeddedIOServiceCollection.h"
#include "Operations/IOperationFactory.h"

#ifndef EMBEDDEDIOOPERATIONFACTORY_H
#define EMBEDDEDIOOPERATIONFACTORY_H
namespace OperationArchitecture
{
	class EmbeddedIOOperationFactory : public IOperationFactory
	{
	protected:
		std::map<uint32_t, IOperationBase*(*)(const EmbeddedIOServices::EmbeddedIOServiceCollection *, const void *, unsigned int &)> _factories;
		const EmbeddedIOServices::EmbeddedIOServiceCollection *_embeddedIOServiceCollection;
		uint32_t _idOffset;
	public:
		EmbeddedIOOperationFactory(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection);
		EmbeddedIOOperationFactory(const EmbeddedIOServices::EmbeddedIOServiceCollection *embeddedIOServiceCollection, const uint32_t idOffset);
		void Register(const uint32_t id, IOperationBase*(*factory)(const EmbeddedIOServices::EmbeddedIOServiceCollection *, const void *, unsigned int &));
		void Unregister(const uint32_t id);
		IOperationBase *Create(const void *config, unsigned int &sizeOut) override;
	};
}
#endif