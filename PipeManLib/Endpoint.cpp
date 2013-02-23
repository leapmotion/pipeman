#include "StdAfx.h"
#include "Endpoint.h"
#include "ControlBlock.h"

CEndpoint::CEndpoint(wstring&& name):
	m_name(name),
	m_pControlBlock(nullptr)
{
	// Now we generate the name of the various important structures:
	{
		wstring subname = m_name + L"-wevt";
		m_hWriteEvent = CreateEventW(nullptr, false, false, subname.c_str());
	}
	{
		wstring subname = m_name + L"-revt";
		m_hReadEvent = CreateEventW(nullptr, false, false, subname.c_str());
	}
	{
		wstring subname = m_name + L"-lock";
		m_hLock = CreateMutex(nullptr, false, subname.c_str());
	}
}

CEndpoint::~CEndpoint(void)
{
	CloseHandle(m_hWriteEvent);
	CloseHandle(m_hReadEvent);
	CloseHandle(m_hLock);
	CloseHandle(m_hSection);
	if(m_pControlBlock)
		UnmapViewOfFile(m_pControlBlock);
}

bool CEndpoint::IsStale(void) const
{
	return m_pControlBlock->bStale;
}