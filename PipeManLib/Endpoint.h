#pragma once
#include <string>

using std::wstring;

struct SCONTROLBLOCK;

/// <summary>
/// Represents a single endpoint.  The endpoint may be configured for read or write.
/// </summary>
class CEndpoint
{
public:
	CEndpoint(wstring&& name);
	virtual ~CEndpoint(void);

protected:
	// Name of this endpoint:
	wstring m_name;

	// Handle to synchronization events.  The write and read events are used to signal
	// that a flip operation has been successfully executed either by the writer, or the
	// reader.
	HANDLE m_hWriteEvent;
	HANDLE m_hReadEvent;
	HANDLE m_hLock;

	// Handle to the section itself:
	HANDLE m_hSection;

	// Pointer to the actual control block:
	SCONTROLBLOCK* m_pControlBlock;

	// Pointer to the first byte of the first buffer:
	LPBYTE m_pFirstBuffer;

public:
	// Accessor methods:
	virtual long long GetAvailable(void) const = 0;
	const wstring& GetName(void) const {return m_name;}
	const SCONTROLBLOCK& GetControlBlock(void) const {return *m_pControlBlock;}
	bool IsStale(void) const;

	/// <summary>
	/// Obtains a pointer to the current buffer
	/// </summary>
	virtual unsigned char* Get(void) const = 0;

	/// <summary>
	/// Flip routine.  Blocks until another buffer becomes available, or the timeout expires.
	/// </summary>
	/// <returns>
	/// False if the timeout expired, or if the server has disappeared.  True otherwise.
	/// </returns>
	virtual bool Flip(int timeout) = 0;
};

