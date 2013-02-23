#pragma once

class CAutoHandle
{
public:
	CAutoHandle(HANDLE hnd);
	~CAutoHandle(void);

private:
	HANDLE m_hnd;
};

