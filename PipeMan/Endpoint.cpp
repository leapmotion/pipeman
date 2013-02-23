#include "stdafx.h"
#include "Endpoint.h"
#include "ControlBlock.h"

using namespace PipeMan;

Endpoint::Endpoint(String^ name, long long desiredSize):
	m_name(name)
{
	// Now we generate the name of the various important structures:
	{
		pin_ptr<const wchar_t> ptr = PtrToStringChars(name + "-wevt");
		m_hWriteEvent = CreateEventW(nullptr, false, false, ptr);
	}
	{
		pin_ptr<const wchar_t> ptr = PtrToStringChars(name + "-revt");
		m_hReadEvent = CreateEventW(nullptr, false, false, ptr);
	}
	{
		pin_ptr<const wchar_t> ptr = PtrToStringChars(name + "-lock");
		m_hLock = CreateMutex(nullptr, false, ptr);
	}
	{
		pin_ptr<const wchar_t> ptr = PtrToStringChars(name + "-file");
		if(desiredSize)
		{
			desiredSize += 256;
			m_hSection = CreateFileMapping(nullptr, nullptr, PAGE_READWRITE, desiredSize >> 32, desiredSize & ~0L, ptr);
		}
		else
			m_hSection = OpenFileMapping(PAGE_READWRITE, false, ptr);

		m_pControlBlock = (SCONTROLBLOCK*)MapViewOfFile(m_hSection, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		m_pFirstBuffer = (LPBYTE)(m_pControlBlock + 1);
	}
}

Endpoint::~Endpoint(void)
{
	CloseHandle(m_hWriteEvent);
	CloseHandle(m_hReadEvent);
	CloseHandle(m_hLock);
	CloseHandle(m_hSection);
	UnmapViewOfFile(m_pControlBlock);
}

long long Endpoint::BufferCount::get(void)
{
	return m_pControlBlock->llBufferCount;
}

long long Endpoint::BufferSize::get(void)
{
	return m_pControlBlock->llBufferSize;
}
