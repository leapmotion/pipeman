#include "stdafx.h"
#include "Client.h"
#include "ControlBlock.h"

using namespace PipeMan;

Client::Client(String^ name):
	Endpoint(name, 0)
{
}


long long Client::Available::get(void)
{
	return m_pControlBlock->llQueueLength;
}