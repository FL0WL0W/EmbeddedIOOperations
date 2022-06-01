#include "CommunicationHandlers/CommunicationHandler_GetVariable.h"

using namespace EmbeddedIOServices;
using namespace OperationArchitecture;

#ifdef COMMUNICATIONHANDLER_GETVARIABLE_H
namespace EFIGenie
{	
		CommunicationHandler_GetVariable::CommunicationHandler_GetVariable(ICommunicationService *communicationService, GeneratorMap<Variable> *variableMap, const void *metadata) :
			_communicationService(communicationService),
			_variableMap(variableMap),
			_metadata(metadata)
		{
			_communicationReceiveCallBack = [this](void *data, size_t length) { return this->Receive(data, length); };
			_communicationService->RegisterReceiveCallBack(&_communicationReceiveCallBack);
		}

		CommunicationHandler_GetVariable::~CommunicationHandler_GetVariable()
		{
			_communicationService->UnRegisterReceiveCallBack(&_communicationReceiveCallBack);
		}

		size_t CommunicationHandler_GetVariable::Receive(void *data, size_t length)
		{
			if(length < sizeof(uint32_t))//make sure there are enough bytes to process a request
				return 0;

			uint32_t variableID = *reinterpret_cast<uint32_t *>(data); //grab variable ID from data
			data = reinterpret_cast<uint32_t *>(data) + 1; //ofset data

			if(variableID == METADATA_VARIABLEID)
			{
				if(length < sizeof(uint32_t) + sizeof(uint32_t))//make sure there are enough bytes to process a request
					return 0;
				uint8_t offset = *reinterpret_cast<uint32_t *>(data); //grab offset from data
				data = reinterpret_cast<uint32_t *>(data) + 1; //ofset data

				//If security is an issue, then this function allows users to read memory with 0 oversight
				//send metadata in 64 byte blocks at a time. the second variable is the block index
				_communicationService->Send(reinterpret_cast<const uint8_t *>(_metadata) + offset * 64, 64);

				return sizeof(uint32_t) + sizeof(uint32_t);//return number of bytes handled
			}

			if(length < sizeof(uint32_t) + sizeof(uint8_t))//make sure there are enough bytes to process a request
				return 0;
			uint8_t offset = *reinterpret_cast<uint8_t *>(data); //grab offset from data
			data = reinterpret_cast<uint8_t *>(data) + 1; //ofset data
			
			uint8_t variableBuff[sizeof(VariableType) + sizeof(uint64_t)];//create a buffer for the returned message

			std::map<uint32_t, Variable*>::iterator it = _variableMap->find(variableID); //get the variable
			if (it != _variableMap->end())
			{
				variableBuff[0] = it->second->Type;//type is the first byte returned
				if(it->second->Type == POINTER || it->second->Type == BIGOTHER)//if it is a pointer
				{
					//If security is an issue, then this function allows users to read memory with 0 oversight
					//return the value of the address location of the variable + offset
					std::memcpy(&variableBuff[1], reinterpret_cast<uint64_t *>(it->second->Value) + offset, sizeof(uint64_t));
					//send the message back
					_communicationService->Send(variableBuff, sizeof(variableBuff));
				}
				else
				{
					//otherwise copy the value of the variable
					std::memcpy(&variableBuff[1], &it->second->Value, sizeof(uint64_t));
					//send the message back
					_communicationService->Send(variableBuff, sizeof(VariableType) + VariableTypeSizeOf(it->second->Type));
				}
			}
			else
			{
				variableBuff[0] = VOID;
				std::memcpy(&variableBuff[1], &variableID, sizeof(uint32_t));
				std::memcpy(&variableBuff[1 + sizeof(uint32_t)], &offset, sizeof(uint8_t));
				//send the message back
				_communicationService->Send(variableBuff, sizeof(VariableType) + sizeof(uint32_t) + sizeof(uint8_t));
			}

			return sizeof(uint32_t) + sizeof(uint8_t);//return number of bytes handled
		}
}
#endif