#pragma once
#include "Endpoint.h"

using namespace System;
using namespace System::IO;

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

		/// <summary>
		/// This is the output stream used to send data to the downstream client.  This stream
		/// should not be cached, as it will be invalidated when Flip is called.
		/// </summary>
		UnmanagedMemoryStream^ Sink;

		// Inherited properties:
		property long long  Available {virtual long long  get(void) override;}

	private:
		// This is the current write offset, used when a buffer is written in multiple stages
		long long m_writeOffset;

	public:
		virtual void Flip(void) override;
	};
}
