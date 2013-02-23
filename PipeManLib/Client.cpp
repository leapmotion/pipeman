#include "StdAfx.h"
#include "Client.h"
#include "ControlBlock.h"
#include <utility>

using namespace std;

CClient::CClient(wstring&& name):
	CEndpoint(forward<wstring>(name))
{
}

CClient::~CClient(void)
{
}

long long CClient::GetAvailable(void) const
{
	return m_pControlBlock->llQueueLength;
}

void* CClient::Get(void) const
{
	return m_pFirstBuffer + m_pControlBlock->llReaderIndex * m_pControlBlock->llBufferSize;
}

bool CClient::Flip(int timeout)
{
	// Is there another buffer outstanding to be read?
	while(!GetAvailable())
		if(WaitForSingleObject(m_hWriteEvent, timeout) != WAIT_OBJECT_0)
			return false;

	// Advance our last-read offset and decrement the queue length:
	m_pControlBlock->llReaderIndex = (m_pControlBlock->llReaderIndex + 1) % m_pControlBlock->llBufferCount;
	m_pControlBlock->llQueueLength--;

	// Signal that a read operation has just completed:
	SetEvent(m_hReadEvent);
	return true;
}