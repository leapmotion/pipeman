#include "stdafx.h"

using namespace System;
using namespace PipeMan;

int main(array<System::String ^> ^args)
{
	Server^ rServer = gcnew Server("Testing", 0x1000);

	Client^ rClient = gcnew Client("Testing");

    return 0;
}
