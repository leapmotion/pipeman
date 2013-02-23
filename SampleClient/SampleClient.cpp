#include "stdafx.h"

using namespace System;
using namespace System::IO;
using namespace PipeMan;

int main(array<System::String ^> ^args)
{
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
