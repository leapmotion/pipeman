#include "stdafx.h"
#include "Server.h"
#include "ControlBlock.h"
#include "AutoLocker.h"

using namespace PipeMan;

Server::Server(String^ name, long long bufferCount, long long bufferSize):
	Endpoint(name, bufferCount * bufferSize)
{
	// Assign our properties to the control block:
	m_pControlBlock->llAllocationSize = bufferCount * bufferSize;
	m_pControlBlock->llBufferCount = bufferCount;
	m_pControlBlock->llBufferSize = bufferSize;

	// Prime the output stream:
	Sink = gcnew UnmanagedMemoryStream(m_pFirstBuffer, bufferSize, bufferSize, FileAccess::Write);
}

Server::~Server(void)
{

}

long long  Server::Available::get(void)
{
	return m_pControlBlock->llBufferCount - m_pControlBlock->llQueueLength;
}

void Server::Flip(void)
{
	// First, obtain the lock:
	CAutoLocker lk(m_hLock);

	// Advance our write destination
	m_writeOffset = (m_writeOffset + m_pControlBlock->llBufferSize) % m_pControlBlock->llAllocationSize;
	m_pControlBlock->llQueueLength++;

	// Delay until enough space becomes available:
	while(!Available)
		WaitForSingleObject(m_hReadEvent, INFINITE);

	// Create the new memory stream:
	Sink = gcnew UnmanagedMemoryStream(m_pFirstBuffer + m_writeOffset, BufferSize, BufferSize, FileAccess::Write);
}