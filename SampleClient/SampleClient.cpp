#include "stdafx.h"

using namespace System;
using namespace System::IO;
using namespace PipeMan;

int main(array<System::String ^> ^args)
{
	String^ ChannelName = "Testing";
	Server^ rServer = gcnew Server(ChannelName, 10, 0x1000);

	for(int i = 0; i < 12; i++)
	{
		BinaryWriter^ writer = gcnew BinaryWriter(rServer->Link);
		writer->Write("Hello world!");
		if(!rServer->Flip(100))
			break;
	}

	Client^ rClient = gcnew Client(ChannelName);

	array<Byte>^ buf = gcnew array<Byte>(100);
	while(rClient->Flip(0))
	{
		BinaryReader^ reader = gcnew BinaryReader(rClient->Link);
		String^ rStr = reader->ReadString();
		System::Console::WriteLine(rStr);
	}

    return 0;
}
