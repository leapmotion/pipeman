#include "stdafx.h"
#include "Client.h"
#include "AutoLocker.h"
#include "../PipeManLib/Client.h"
#include "../PipeManLib/ControlBlock.h"

using namespace PipeMan;

CClient* MakeClient(String^ name)
{
	pin_ptr<const wchar_t> ptr = PtrToStringChars(name);
	return new CClient((wstring)ptr);
}

Client::Client(String^ name):
	Endpoint(MakeClient(name))
{
}
