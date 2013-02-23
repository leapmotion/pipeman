#include "stdafx.h"
#include "Server.h"
#include "ControlBlock.h"
#include "AutoLocker.h"

using namespace PipeMan;

Server::Server(String^ name, long long bufferCount, long long bufferSize):
	Endpoint(name, bufferCount * bufferSize),
	m_writeOffset(-bufferSize)
{
	// Assign our properties to the control block:
	m_pControlBlock->llAllocationSize = bufferCount * bufferSize;
	m_pControlBlock->llBufferCount = bufferCount;
	m_pControlBlock->llBufferSize = bufferSize;
	m_pControlBlock->llQueueLength = -1;
	m_pControlBlock->llReaderIndex = 0;

	// Prime the output stream:
	Flip(INFINITE);
}

Server::~Server(void)
{

}

long long  Server::Available::get(void)
{
	return m_pControlBlock->llBufferCount - m_pControlBlock->llQueueLength;
}

bool Server::Flip(int timeout)
{
	// Delay until enough space becomes available:
	while(!Available)
		if(WaitForSingleObject(m_hReadEvent, timeout) != WAIT_OBJECT_0)
		{
			Link->Seek(0, SeekOrigin::Begin);
			return false;
		}

	// Advance our write destination
	m_writeOffset = (m_writeOffset + m_pControlBlock->llBufferSize) % m_pControlBlock->llAllocationSize;
	m_pControlBlock->llQueueLength++;

	// Signal that a new buffer is available:
	SetEvent(m_hWriteEvent);

	// Create the new memory stream:
	Link = gcnew UnmanagedMemoryStream(m_pFirstBuffer + m_writeOffset, BufferSize, BufferSize, FileAccess::Write);
	return true;
}