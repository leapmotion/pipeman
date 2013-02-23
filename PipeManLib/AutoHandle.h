#pragma once

class CAutoHandle
{
public:
	CAutoHandle(HANDLE hHnd);
	~CAutoHandle(void);

private:
	HANDLE m_hHnd;
};

