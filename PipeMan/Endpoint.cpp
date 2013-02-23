#include "stdafx.h"
#include "Endpoint.h"
#include "../PipeManLib/ControlBlock.h"
#include "../PipeManLib/Endpoint.h"
#include <string>

using namespace std;
using namespace PipeMan;

Endpoint::Endpoint(CEndpoint* pEndpoint):
	m_pEndpoint(pEndpoint)
{
}

Endpoint::~Endpoint(void)
{
	delete m_pEndpoint;
}

long long Endpoint::Available::get(void)
{
	return m_pEndpoint->GetAvailable();
}

String^ Endpoint::Name::get(void)
{
	return gcnew String(m_pEndpoint->GetName().c_str());
}

long long Endpoint::BufferCount::get(void)
{
	return m_pEndpoint->GetControlBlock().llBufferCount;
}

long long Endpoint::BufferSize::get(void)
{
	return m_pEndpoint->GetControlBlock().llBufferSize;
}

bool Endpoint::Flip(int timeout)
{
	if(!m_pEndpoint->Flip(timeout))
	{
		Link->Seek(0, SeekOrigin::Begin);
		return false;
	}

	// Create the new memory stream:
	Link = gcnew UnmanagedMemoryStream(m_pEndpoint->Get(), BufferSize, BufferSize, FileAccess::Write);
	return true;
}