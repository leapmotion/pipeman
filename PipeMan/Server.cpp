#include "stdafx.h"
#include "Server.h"
#include "../PipeManLib/ControlBlock.h"
#include "../PipeManLib/Server.h"
#include "AutoLocker.h"
#include <string>

using namespace std;
using namespace PipeMan;

CServer* MakeServer(String^ name, long long bufferCount, long long bufferSize)
{
	pin_ptr<const wchar_t> ptr = PtrToStringChars(name);
	return new CServer((wstring)ptr, bufferCount, bufferSize);
}

Server::Server(String^ name, long long bufferCount, long long bufferSize):
	Endpoint(MakeServer(name, bufferCount, bufferSize))
{
}
