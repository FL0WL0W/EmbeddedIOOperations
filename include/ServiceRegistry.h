#ifndef SERVICEREGISTRY_H
#define SERVICEREGISTRY_H

#include <cstdint>
#include <map>

namespace EmbeddedIOOperations
{
	class ServiceRegistry
	{
	public:
		static constexpr uint32_t DefaultServiceId = 0;

		template<typename SERVICE>
		bool Register(SERVICE *service)
		{
			return Register<SERVICE>(DefaultServiceId, service);
		}

		template<typename SERVICE>
		bool Register(uint32_t id, SERVICE *service)
		{
			if (service == nullptr)
				return false;

			ServiceMap &services = _services[TypeKey<SERVICE>()];
			return services.insert(ServiceMap::value_type(id, service)).second;
		}

		template<typename SERVICE>
		SERVICE *TryGet() const
		{
			return TryGet<SERVICE>(DefaultServiceId);
		}

		template<typename SERVICE>
		SERVICE *TryGet(uint32_t id) const
		{
			typename RegistryMap::const_iterator type = _services.find(TypeKey<SERVICE>());
			if (type == _services.end())
				return nullptr;

			ServiceMap::const_iterator service = type->second.find(id);
			if (service == type->second.end())
				return nullptr;

			return static_cast<SERVICE *>(service->second);
		}

		template<typename SERVICE>
		bool Contains() const
		{
			return TryGet<SERVICE>() != nullptr;
		}

		template<typename SERVICE>
		bool Contains(uint32_t id) const
		{
			return TryGet<SERVICE>(id) != nullptr;
		}

	private:
		typedef std::map<uint32_t, void *> ServiceMap;
		typedef std::map<const void *, ServiceMap> RegistryMap;

		template<typename SERVICE>
		static const void *TypeKey()
		{
			static const uint8_t key = 0;
			return &key;
		}

		RegistryMap _services;
	};
}

#endif
