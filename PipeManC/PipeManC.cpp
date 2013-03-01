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

void Server_SendData(int handle, void* data, int bytes)
{
	CServer* server = (CServer*)handle;
	unsigned char* outB = server->Get();

	memcpy_s(outB, (rsize_t)server->GetAvailable(), data, bytes);
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