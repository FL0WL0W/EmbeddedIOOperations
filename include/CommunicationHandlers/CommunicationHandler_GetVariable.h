#include "Variable.h"
#include "GeneratorMap.h"
#include "ICommunicationService.h"

#ifndef COMMUNICATIONHANDLER_GETVARIABLE_H
#define COMMUNICATIONHANDLER_GETVARIABLE_H
#define METADATA_VARIABLEID 4294967295
namespace EFIGenie
{	
	class CommunicationHandler_GetVariable
	{
	protected:
		OperationArchitecture::GeneratorMap<OperationArchitecture::Variable> *_variableMap;
	public:
		CommunicationHandler_GetVariable(OperationArchitecture::GeneratorMap<OperationArchitecture::Variable> *variableMap);
		size_t Receive(EmbeddedIOServices::communication_send_callback_t sendCallBack, const void* buf, size_t length);
	};
}
#endif