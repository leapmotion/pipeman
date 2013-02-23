#pragma once
#include "Endpoint.h"

class CClient:
	public CEndpoint
{
public:
	CClient(wstring&& name);
	~CClient(void);

private:

public:
	void* CClient::Get(void) const;
	long long GetAvailable(void) const;
	bool Flip(int timeout = INFINITE);
};

