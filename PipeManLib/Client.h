#pragma once
#include "Endpoint.h"

class CClient:
	public CEndpoint
{
public:
	CClient(wstring& name, int timeout = INFINITE);
	~CClient(void);

private:

public:
	unsigned char* CClient::Get(void) const;
	long long GetAvailable(void) const;
	bool Flip(int timeout = INFINITE);
};

class CClientNative:
	public CClient
{
public:
	CClientNative(const wchar_t* pwszName, int timeout = INFINITE):
		CClient(wstring(pwszName), timeout)
	{}
};