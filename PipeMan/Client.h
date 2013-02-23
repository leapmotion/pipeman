#pragma once
#include "Endpoint.h"

using namespace System;

namespace PipeMan
{
	public ref class Client:
		public Endpoint
	{
	public:
		Client(String^ name);
		
		// Inherited properties:
		property long long  Available {virtual long long get(void) override;}
	};
}
