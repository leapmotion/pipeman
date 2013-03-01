// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PIPEMANC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PIPEMANC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#define EXPORT_API __declspec(dllexport)
extern "C" {
	EXPORT_API void* Server_Create(const wchar_t* name, long long buffercount, long long bufferSize);
	EXPORT_API void Server_Destroy(void* handle);
	EXPORT_API void Server_SendData(void* handle, void* data, int bytes);
	EXPORT_API bool Server_Flip(void* handle, int timeout);
	EXPORT_API bool Server_Flip_NoTimeout(void* handle);
}