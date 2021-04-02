#include "Operations/EmbeddedIOOperationFactory.h"

using namespace EmbeddedIOServices;

#ifdef EMBEDDEDIOOPERATIONFACTORY_H

namespace OperationArchitecture
{
    EmbeddedIOOperationFactory::EmbeddedIOOperationFactory(const EmbeddedIOServiceCollection *embeddedIOServiceCollection)
    {
        _embeddedIOServiceCollection = embeddedIOServiceCollection;
        _idOffset = 0;
    }

    EmbeddedIOOperationFactory::EmbeddedIOOperationFactory(const EmbeddedIOServiceCollection *embeddedIOServiceCollection, const uint32_t idOffset)
    {
        _embeddedIOServiceCollection = embeddedIOServiceCollection;
        _idOffset = idOffset;
    }
    
    void EmbeddedIOOperationFactory::Register(const uint32_t id, IOperationBase*(*factory)(const EmbeddedIOServiceCollection *, const void *, unsigned int &))
    {
		if(_factories.find(id) != _factories.end())
			Unregister(id);
		_factories.insert(std::pair<uint32_t, IOperationBase*(*)(const EmbeddedIOServiceCollection *, const void *, unsigned int &)>(id, factory));
    }

	void EmbeddedIOOperationFactory::Unregister(const uint32_t id)
	{
		const std::map<uint32_t, IOperationBase*(*)(const EmbeddedIOServiceCollection *, const void *, unsigned int &)>::iterator it = _factories.find(id);
		if (it != _factories.end())
			_factories.erase(it);
	}

    IOperationBase *EmbeddedIOOperationFactory::Create(const void *config, unsigned int &sizeOut)
    {
        const uint32_t factoryId = *reinterpret_cast<const uint32_t *>(config) - _idOffset;
        IOperationBase*(*factory)(const EmbeddedIOServiceCollection *, const void *, unsigned int &);
		const std::map<uint32_t, IOperationBase*(*)(const EmbeddedIOServiceCollection *, const void *, unsigned int &)>::iterator it = _factories.find(factoryId);
		if (it != _factories.end())
			factory = it->second;
        else 
            return 0;

        return factory(_embeddedIOServiceCollection, config, sizeOut);
    }
}

#endif