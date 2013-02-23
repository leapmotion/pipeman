#include "stdafx.h"

using namespace System;
using namespace System::IO;
using namespace PipeMan;

int main(array<System::String ^> ^args)
{
	Server^ rServer = gcnew Server("Testing", 10, 0x1000);

	for(int i = 0; i < 12; i++)
	{
		BinaryWriter^ writer = gcnew BinaryWriter(rServer->Sink);
		writer->Write("Hello world!");
		rServer->Flip();
	}

	Client^ rClient = gcnew Client("Testing");

    return 0;
}
