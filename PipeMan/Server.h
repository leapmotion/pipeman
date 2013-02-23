#pragma once
#include "Endpoint.h"

using namespace System;

namespace PipeMan
{
	public ref class Server:
		public Endpoint
	{
	public:
		/// <summary>
		/// Creates a new server with the specified name.  The name is used to
		/// derive both the name of the shared section, and also the name of the
		/// lock used to control access to the section.
		/// </summary>
		Server(String^ name, long long bufferCount, long long bufferSize);

		~Server(void);

		// Inherited properties:
		property long long  Available {virtual long long  get(void) override;}

	public:

	private:
	};
}
