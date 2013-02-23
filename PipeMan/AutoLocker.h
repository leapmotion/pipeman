#pragma once

class CAutoLocker
{
public:
	CAutoLocker(HANDLE hLock);
	~CAutoLocker(void);

private:
	HANDLE m_hLock;
};



