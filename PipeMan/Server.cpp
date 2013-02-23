#include "stdafx.h"
#include "Server.h"
#include "ControlBlock.h"

using namespace PipeMan;

Server::Server(String^ name, long long bufferCount, long long bufferSize):
	Endpoint(name, bufferCount * bufferSize)
{
	// Assign our properties to the control block:
	m_pControlBlock->llBufferCount = bufferCount;
	m_pControlBlock->llBufferSize = bufferSize;
}

Server::~Server(void)
{

}

long long  Server::Available::get(void)
{
	return m_pControlBlock->llBufferCount - m_pControlBlock->llQueueLength;
}