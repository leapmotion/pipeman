#include "stdafx.h"
#include "Endpoint.h"
#include "ControlBlock.h"

using namespace PipeMan;

Endpoint::Endpoint(String^ name, long long desiredSize):
	m_name(name)
{
	// Now we generate the name of the various important structures:
	{
		pin_ptr<const wchar_t> ptr = PtrToStringChars(name + "-evt");
		m_hEvent = CreateEventW(nullptr, false, false, ptr);
	}
	{
		pin_ptr<const wchar_t> ptr = PtrToStringChars(name + "-lock");
		m_hLock = CreateMutex(nullptr, false, ptr);
	}
	{
		pin_ptr<const wchar_t> ptr = PtrToStringChars(name + "-file");
		desiredSize += 256;
		m_hSection =
			desiredSize ?
			CreateFileMapping(nullptr, nullptr, PAGE_READWRITE, desiredSize >> 32, desiredSize & ~0L, ptr) :
			OpenFileMapping(PAGE_READWRITE, false, ptr);
	}
}

Endpoint::~Endpoint(void)
{
	CloseHandle(m_hEvent);
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

void Endpoint::Flip(void)
{
}