#include "stdafx.h"
#include "PipeManC.h"
#include "../PipeManLib/Server.h"

void* Server_Create(const wchar_t* name, long long buffercount, long long bufferSize)
{
	return new CServer(wstring(name), buffercount, bufferSize);
}

void Server_Destroy(int handle)
{
	CServer* server = (CServer*)handle;
	delete server;
}

void Server_SendData(int handle, const void* data, size_t bytes)
{
	CServer* server = (CServer*)handle;
	int* pBuf = (int*)server->Get();

	if(server->GetAvailable() > 0)
	{
		// Buffer size is the first dword:
		*pBuf = (int)bytes;
		memcpy_s(
			pBuf + 1,
			(rsize_t)server->GetBufferSize() - sizeof(*pBuf),
			data,
			bytes
		);
	}
	else
		printf("Failed to write, no buffer available\n");
}

bool Server_Flip(int handle, int timeout)
{
	CServer* server = (CServer*)handle;
	return server->Flip(timeout);
}

bool Server_Flip_NoTimeout(int handle)
{
	CServer* server = (CServer*)handle;
	return server->Flip();
}