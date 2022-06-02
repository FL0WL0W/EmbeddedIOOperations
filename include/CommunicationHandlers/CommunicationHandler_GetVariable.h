#include "Variable.h"
#include "GeneratorMap.h"
#include "ICommunicationService.h"

#ifndef COMMUNICATIONHANDLER_GETVARIABLE_H
#define COMMUNICATIONHANDLER_GETVARIABLE_H
#define METADATA_VARIABLEID 4294967295
namespace EFIGenie
{	
	class CommunicationHandler_GetVariable : public EmbeddedIOServices::ICommunicationHandler
	{
	protected:
		OperationArchitecture::GeneratorMap<OperationArchitecture::Variable> *_variableMap;
		const void *_metadata;
	public:
		CommunicationHandler_GetVariable(OperationArchitecture::GeneratorMap<OperationArchitecture::Variable> *variableMap, const void *metadata);
		size_t Receive(EmbeddedIOServices::communication_send_callback_t sendCallBack, void* buf, size_t length);
	};
}
#endif