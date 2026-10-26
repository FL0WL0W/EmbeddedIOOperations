#include "Operations/Operation.h"
#include "Operations/OperationFactory.h"
#include "ICANService.h"

#ifndef OPERATION_CANCRCJ1850_H
#define OPERATION_CANCRCJ1850_H
namespace EmbeddedIOOperations
{
	class Operation_CANCRCJ1850 : public OperationArchitecture::AbstractOperation
	{
	protected:
		const uint8_t _start;
		const uint8_t _length;
		const uint8_t _offset;
	public:		
        Operation_CANCRCJ1850(const uint8_t start, const uint8_t length, const uint8_t offset);
		void AbstractExecute(OperationArchitecture::Variable **variables);

		static AbstractOperation *Create(const void *config, size_t  &sizeOut);
	};
}
#endif