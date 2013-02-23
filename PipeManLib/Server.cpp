#include "StdAfx.h"
#include "Server.h"
#include "ControlBlock.h"
#include <utility>

CServer::CServer(wstring&& name, long long bufferCount, long long bufferSize):
	CEndpoint(std::forward<wstring>(name), bufferCount * bufferSize),
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

CServer::~CServer(void)
{
}

long long CServer::GetAvailable(void) const
{
	return m_pControlBlock->llBufferCount - m_pControlBlock->llQueueLength;
}

void* CServer::Get(void) const
{
	return m_pFirstBuffer + m_writeOffset;
}

bool CServer::Flip(int timeout)
{
	// Delay until enough space becomes available:
	while(!GetAvailable())
		if(WaitForSingleObject(m_hReadEvent, timeout) != WAIT_OBJECT_0)
			return false;

	// Advance our write destination
	m_writeOffset = (m_writeOffset + m_pControlBlock->llBufferSize) % m_pControlBlock->llAllocationSize;
	m_pControlBlock->llQueueLength++;

	// Signal that a new buffer is available:
	SetEvent(m_hWriteEvent);
	return true;
}