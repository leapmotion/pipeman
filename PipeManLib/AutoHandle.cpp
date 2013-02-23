#include "StdAfx.h"
#include "AutoHandle.h"


CAutoHandle::CAutoHandle(HANDLE hHnd):
	m_hHnd(hHnd)
{
}

CAutoHandle::~CAutoHandle(void)
{
	CloseHandle(m_hHnd);
}
