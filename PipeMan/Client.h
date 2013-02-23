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
	};
}
