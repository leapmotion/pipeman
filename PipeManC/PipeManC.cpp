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

  if( server->GetAvailable() > 0 ) {
    *outB = static_cast<unsigned char>(bytes);
    outB++; //write the size as the first byte of the buffer.
	  memcpy_s(outB, (rsize_t)server->GetBufferSize(), data, bytes);
  }
  else {
    printf("Failed to write, no buffer available\n");
  }
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