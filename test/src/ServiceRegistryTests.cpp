#include "gtest/gtest.h"
#include "ServiceRegistry.h"

using namespace EmbeddedIOOperations;

namespace UnitTests
{
	namespace
	{
		struct ServiceA
		{
			int Value;
		};

		struct ServiceB
		{
			int Value;
		};
	}

	TEST(ServiceRegistryTests, DefaultServiceUsesIdZero)
	{
		ServiceRegistry registry;
		ServiceA service = { 1 };

		ASSERT_TRUE(registry.Register<ServiceA>(&service));
		ASSERT_EQ(&service, registry.TryGet<ServiceA>());
		ASSERT_EQ(&service, registry.TryGet<ServiceA>(ServiceRegistry::DefaultServiceId));
	}

	TEST(ServiceRegistryTests, MultipleServicesAreSelectedById)
	{
		ServiceRegistry registry;
		ServiceA defaultService = { 1 };
		ServiceA secondService = { 2 };

		ASSERT_TRUE(registry.Register<ServiceA>(&defaultService));
		ASSERT_TRUE(registry.Register<ServiceA>(7, &secondService));
		ASSERT_EQ(&defaultService, registry.TryGet<ServiceA>());
		ASSERT_EQ(&secondService, registry.TryGet<ServiceA>(7));
		ASSERT_EQ(nullptr, registry.TryGet<ServiceA>(8));
	}

	TEST(ServiceRegistryTests, ServiceTypesHaveIndependentIdNamespaces)
	{
		ServiceRegistry registry;
		ServiceA serviceA = { 1 };
		ServiceB serviceB = { 2 };

		ASSERT_TRUE(registry.Register<ServiceA>(3, &serviceA));
		ASSERT_TRUE(registry.Register<ServiceB>(3, &serviceB));
		ASSERT_EQ(&serviceA, registry.TryGet<ServiceA>(3));
		ASSERT_EQ(&serviceB, registry.TryGet<ServiceB>(3));
	}

	TEST(ServiceRegistryTests, NullAndDuplicateRegistrationsAreRejected)
	{
		ServiceRegistry registry;
		ServiceA first = { 1 };
		ServiceA duplicate = { 2 };

		ASSERT_FALSE(registry.Register<ServiceA>(nullptr));
		ASSERT_TRUE(registry.Register<ServiceA>(4, &first));
		ASSERT_FALSE(registry.Register<ServiceA>(4, &duplicate));
		ASSERT_EQ(&first, registry.TryGet<ServiceA>(4));
	}
}
