#include "Variable.h"
#include "GeneratorMap.h"
#include "ICommunicationService.h"

#ifndef COMMUNICATIONHANDLER_GETVARIABLE_H
#define COMMUNICATIONHANDLER_GETVARIABLE_H
namespace EFIGenie
{	
	class CommunicationHandler_GetVariable
	{
	protected:
		EmbeddedIOServices::ICommunicationService *_communicationService;
		OperationArchitecture::GeneratorMap<OperationArchitecture::Variable> *_variableMap;
		EmbeddedIOServices::communication_receive_callback_t _communicationReceiveCallBack;
	public:
		CommunicationHandler_GetVariable(EmbeddedIOServices::ICommunicationService *communicationService, OperationArchitecture::GeneratorMap<OperationArchitecture::Variable> *variableMap);
		~CommunicationHandler_GetVariable();
		size_t Receive(void* buf, size_t length);
	};
}
#endif