#include "stdafx.h"
#include "AutoLocker.h"

CAutoLocker::CAutoLocker(HANDLE hLock):
	m_hLock(hLock)
{
}

CAutoLocker::~CAutoLocker(void)
{
	ReleaseMutex(m_hLock);
}