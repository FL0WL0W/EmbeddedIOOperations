#include "CommunicationHandlers/CommunicationHandler_GetVariable.h"

using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

#ifdef COMMUNICATIONHANDLER_GETVARIABLE_H
namespace EmbeddedIOOperations
{	
	CommunicationHandler_GetVariable::CommunicationHandler_GetVariable(GeneratorMap<Variable> *variableMap) :
		_variableMap(variableMap)
	{
	}

	size_t CommunicationHandler_GetVariable::Receive(communication_send_callback_t sendCallBack, const void *data, size_t length)
	{
		if(length < sizeof(uint32_t))//make sure there are enough bytes to process a request
			return 0;

		const uint32_t variableID = *reinterpret_cast<const uint32_t *>(data); //grab variable ID from data
		data = reinterpret_cast<const uint32_t *>(data) + 1; //ofset data
		
		std::map<uint32_t, Variable*>::iterator it = _variableMap->find(variableID); //get the variable
		size_t size = 0;
		if (it != _variableMap->end() && (size = it->second->Size()) > 0)
		{
			uint8_t variableBuff[sizeof(VariableType) + size];//create a buffer for the returned message
			variableBuff[0] = it->second->Type;//type is the first byte returned
			if(it->second->Type == POINTER || it->second->Type == BIGOTHER)//if it is a pointer
			{
				//unknown pointer size
				if(size == 0)
				{
					if(length < sizeof(uint32_t) + sizeof(uint8_t))//make sure there are enough bytes to process a request
						return 0;
					const uint8_t offset = *reinterpret_cast<const uint8_t *>(data); //grab offset from data
					data = reinterpret_cast<const uint8_t *>(data) + 1; //ofset data
					
					std::memcpy(&variableBuff[sizeof(VariableType)], reinterpret_cast<uint64_t *>(it->second->POINTERValue) + offset, sizeof(uint64_t));
					//send the message back
					sendCallBack(variableBuff, sizeof(VariableType) + sizeof(uint64_t));
					return sizeof(uint32_t) + sizeof(uint8_t);//return number of bytes handled
				}
				//known pointer size
				else
				{
					std::memcpy(&variableBuff[sizeof(VariableType)], it->second->POINTERValue, size);
					//send the message back
					sendCallBack(variableBuff, sizeof(VariableType) + size);
				}
			}
			else
			{
				std::memcpy(&variableBuff[sizeof(VariableType)], it->second->ValueArray, size);
				//send the message back
				sendCallBack(variableBuff, sizeof(VariableType) + size);
			}
		}
		else
		{
			uint8_t variableBuff[sizeof(VariableType)];//create a buffer for the returned message
			variableBuff[0] = VOID;
			//send the message back
			sendCallBack(variableBuff, sizeof(VariableType));
		}

		return sizeof(uint32_t);//return number of bytes handled
	}
}
#endif