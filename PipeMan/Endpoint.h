#pragma once
#include "AutoHandle.h"

using namespace System;

struct SCONTROLBLOCK;

namespace PipeMan
{
	public ref class Endpoint abstract
	{
	public:
		Endpoint(String^ name, long long desiredSize);

		~Endpoint(void);

		/// <summary>
		/// This is the name for the section
		/// </summary>
		property String^ Name { String^ get(void) {return m_name;}};
		
		/// <summary>
		/// This is the number of buffers that are available for communication between
		/// a single server and a single client.
		/// </summary>
		property long long BufferCount {long long get(void);}

		/// <summary>
		/// This is the size of a single buffer.
		/// </summary>
		property long long BufferSize {long long get(void);}

		/// <summary>
		/// This is a pointer to the current buffer under review.
		/// </summary>

		/// <summary>
		/// This is an instantaneous count of the number of buffers currently available.  If
		/// this value is zero, the next call to Flip may block; if Flip blocks, this value
		/// must be zero.
		/// </summary>
		property long long  Available {virtual long long  get(void) = 0;}

	protected:
		// Name of this endpoint:
		String^ m_name;

		// Handle to the event and synch lock:
		HANDLE m_hEvent;
		HANDLE m_hLock;

		// Handle to the section itself:
		HANDLE m_hSection;

		// Pointer to the actual control block:
		SCONTROLBLOCK* m_pControlBlock;

	public:
		/// <summary>
		/// The flip method will advance to the next buffer.  For writers, this will obtain
		/// an empty buffer to be written to; for readers, it will obtain a filled buffer to
		/// be processed.  In the event that there are no buffers currently available to be
		/// returned, this method will BLOCK.
		/// </summary>
		void Flip(void);
	};
}
