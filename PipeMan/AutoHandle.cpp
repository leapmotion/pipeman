#include "stdafx.h"
#include "AutoHandle.h"


CAutoHandle::CAutoHandle(HANDLE hnd):
	m_hnd(hnd)
{
}

CAutoHandle::~CAutoHandle(void)
{
	CloseHandle(m_hnd);
}