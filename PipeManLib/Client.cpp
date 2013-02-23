#include "StdAfx.h"
#include "Client.h"
#include "ControlBlock.h"
#include <utility>

using namespace std;

CClient::CClient(wstring&& name, int timeout):
	CEndpoint(forward<wstring>(name))
{
	if(WaitForSingleObject(m_hWriteEvent, timeout) != WAIT_OBJECT_0)
		throw new exception("The server did not start before the timeout expired");

	wstring subname = m_name + L"-file";

	// Wait on the read event before we try to open the mapping:
	m_hSection = OpenFileMapping(GENERIC_ALL, false, subname.c_str());

	// Now we just map the whole space:
	m_pControlBlock = (SCONTROLBLOCK*)MapViewOfFile(m_hSection, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	m_pFirstBuffer = (LPBYTE)(m_pControlBlock + 1);
}

CClient::~CClient(void)
{
}

long long CClient::GetAvailable(void) const
{
	return m_pControlBlock->llQueueLength;
}

unsigned char* CClient::Get(void) const
{
	return (unsigned char*)m_pFirstBuffer + m_pControlBlock->llReaderIndex * m_pControlBlock->llBufferSize;
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
	return !IsStale();
}