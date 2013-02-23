#include "stdafx.h"
#include "../PipeManLib/Client.h"
#include <iostream>

using namespace std;

int main(int argc, const char* argv[])
{
	// Give the server a small amount of time to start up
	CClient client((wstring)L"Testing", 10000);

	while(client.Flip(INFINITE))
	{
		void* pPtr = client.Get();

		// Read the length first:
		size_t len = *(char*)pPtr;
		cout.write((char*)pPtr + 1, len);
		cout << endl;
	}

    return 0;
}
