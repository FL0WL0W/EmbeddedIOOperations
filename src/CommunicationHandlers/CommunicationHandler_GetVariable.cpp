#include "CommunicationHandlers/CommunicationHandler_GetVariable.h"

using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

#ifdef COMMUNICATIONHANDLER_GETVARIABLE_H
namespace EFIGenie
{	
		CommunicationHandler_GetVariable::CommunicationHandler_GetVariable(GeneratorMap<Variable> *variableMap) :
			_variableMap(variableMap)
		{
		}

		size_t CommunicationHandler_GetVariable::Receive(communication_send_callback_t sendCallBack, void *data, size_t length)
		{
			if(length < sizeof(uint32_t))//make sure there are enough bytes to process a request
				return 0;

			uint32_t variableID = *reinterpret_cast<uint32_t *>(data); //grab variable ID from data
			data = reinterpret_cast<uint32_t *>(data) + 1; //ofset data
			
			uint8_t variableBuff[sizeof(VariableType) + VARIABLE_VALUE_SIZE];//create a buffer for the returned message

			std::map<uint32_t, Variable*>::iterator it = _variableMap->find(variableID); //get the variable
			if (it != _variableMap->end())
			{
				variableBuff[0] = it->second->Type;//type is the first byte returned
				size_t size = it->second->Size();
				if(it->second->Type == POINTER)//if it is a pointer
				{
					//unknown pointer size
					if(size == 0)
					{
						if(length < sizeof(uint32_t) + sizeof(uint8_t))//make sure there are enough bytes to process a request
							return 0;
						uint8_t offset = *reinterpret_cast<uint8_t *>(data); //grab offset from data
						data = reinterpret_cast<uint8_t *>(data) + 1; //ofset data
						std::memcpy(&variableBuff[sizeof(VariableType)], reinterpret_cast<uint64_t *>(it->second->Value) + offset, sizeof(uint64_t));
						//send the message back
						sendCallBack(variableBuff, sizeof(VariableType) + sizeof(uint64_t));
					}
					//known pointer size
					else
					{
						std::memcpy(&variableBuff[sizeof(VariableType)], reinterpret_cast<uint64_t *>(it->second->Value), size);
						//send the message back
						sendCallBack(variableBuff, sizeof(VariableType) + size);
					}
				}
				else
				{
					std::memcpy(&variableBuff[sizeof(VariableType)], &it->second->Value, size);
					//send the message back
					sendCallBack(variableBuff, sizeof(VariableType) + size);
				}
			}
			else
			{
				variableBuff[0] = VOID;
				std::memcpy(&variableBuff[sizeof(VariableType)], &variableID, sizeof(uint32_t));
				//send the message back
				sendCallBack(variableBuff, sizeof(VariableType) + sizeof(uint32_t));
			}

			return sizeof(uint32_t) + sizeof(uint8_t);//return number of bytes handled
		}
}
#endif