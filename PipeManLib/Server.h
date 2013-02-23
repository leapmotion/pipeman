#pragma once
#include "Endpoint.h"
#include <string>

using namespace std;

class CServer:
	public CEndpoint
{
public:
	CServer(wstring&& name, long long bufferCount, long long bufferSize);
	~CServer(void);

private:
	// This is the current write offset from the beginning of the buffer space
	long long m_writeOffset;

public:
	virtual unsigned char* Get(void) const;
	virtual long long GetAvailable(void) const;

	bool Flip(int timeout = INFINITE);
};

