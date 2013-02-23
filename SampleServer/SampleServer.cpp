#include "stdafx.h"

using namespace PipeMan;
using namespace System;
using namespace System::IO;

int main(array<System::String ^> ^args)
{
	String^ ChannelName = "Testing";
	Server^ rServer = gcnew Server(ChannelName, 10, 0x1000);

	for(int i = 0; i < 12; i++)
	{
		BinaryWriter^ writer = gcnew BinaryWriter(rServer->Link);
		writer->Write("Hello world!");
		rServer->Flip(100);
	}

	delete rServer;
    return 0;
}
