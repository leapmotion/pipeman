#include "StdAfx.h"
#include "Server.h"
#include "ControlBlock.h"
#include <utility>

CServer::CServer(wstring& name, long long bufferCount, long long bufferSize):
	CEndpoint(std::forward<wstring>(name)),
	m_writeOffset(-bufferSize)
{
	// Create our mapping:
	long long desiredSize = bufferCount * bufferSize + 256;
	
	{
		wstring subname = m_name + L"-file";
		m_hSection = CreateFileMapping(nullptr, nullptr, PAGE_READWRITE, desiredSize >> 32, desiredSize & ~0L, subname.c_str());
	
		// Now actually map things in
		m_pControlBlock = (SCONTROLBLOCK*)MapViewOfFile(m_hSection, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		m_pFirstBuffer = (LPBYTE)(m_pControlBlock + 1);
	}

	// Assign our properties to the control block:
	m_pControlBlock->llAllocationSize = bufferCount * bufferSize;
	m_pControlBlock->llBufferCount = bufferCount;
	m_pControlBlock->llBufferSize = bufferSize;
	m_pControlBlock->llQueueLength = -1;
	m_pControlBlock->llReaderIndex = 0;
	m_pControlBlock->bStale = false;

	// This will release the reader when it's eventually constructed:
	SetEvent(m_hWriteEvent);
	
	// Prime the output stream:
	Flip(INFINITE);
}

CServer::~CServer(void)
{
	// Server is now gone, mark this as stale
	m_pControlBlock->bStale = true;

	// Wake up the client so it can notice that we're stale now
	SetEvent(m_hWriteEvent);
}

long long CServer::GetAvailable(void) const
{
	return m_pControlBlock->llBufferCount - m_pControlBlock->llQueueLength;
}

unsigned char* CServer::Get(void) const
{
	return (unsigned char*)m_pFirstBuffer + m_writeOffset;
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