#include "stdafx.h"
#include "Client.h"
#include "AutoLocker.h"
#include "ControlBlock.h"

using namespace PipeMan;

Client::Client(String^ name):
	Endpoint(name, 0)
{
}


long long Client::Available::get(void)
{
	return m_pControlBlock->llQueueLength;
}

bool Client::Flip(int timeout)
{
	// Is there another buffer outstanding to be read?
	while(!Available)
		if(WaitForSingleObject(m_hWriteEvent, timeout) != WAIT_OBJECT_0)
		{
			Link->Seek(0, SeekOrigin::Begin);
			return false;
		}

	// Advance our last-read offset and decrement the queue length:
	m_pControlBlock->llReaderIndex = (m_pControlBlock->llReaderIndex + 1) % m_pControlBlock->llBufferCount;
	m_pControlBlock->llQueueLength--;

	// Signal that a read operation has just completed:
	SetEvent(m_hReadEvent);

	// Create the new memory stream:
	Link = gcnew UnmanagedMemoryStream(m_pFirstBuffer + m_pControlBlock->llReaderIndex * BufferSize, BufferSize, BufferSize, FileAccess::Read);
	return true;
}