#include "StdAfx.h"
#include "Endpoint.h"
#include "ControlBlock.h"

CEndpoint::CEndpoint(wstring&& name, long long desiredSize):
	m_name(name)
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
	{
		wstring subname = m_name + L"-file";
		if(desiredSize)
		{
			desiredSize += 256;
			m_hSection = CreateFileMapping(nullptr, nullptr, PAGE_READWRITE, desiredSize >> 32, desiredSize & ~0L, subname.c_str());
		}
		else
			m_hSection = OpenFileMapping(GENERIC_ALL, false, subname.c_str());

		m_pControlBlock = (SCONTROLBLOCK*)MapViewOfFile(m_hSection, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		m_pFirstBuffer = (LPBYTE)(m_pControlBlock + 1);
	}
}

CEndpoint::~CEndpoint(void)
{
	CloseHandle(m_hWriteEvent);
	CloseHandle(m_hReadEvent);
	CloseHandle(m_hLock);
	CloseHandle(m_hSection);
	UnmapViewOfFile(m_pControlBlock);
}
