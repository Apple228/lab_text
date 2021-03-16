#include <iostream>
#include "text.h"
#include "textlink.h"
using namespace std;

int main()
{
	TTextLink::InitMemSystem();
	TText txt;
	txt.SetLine("work1");
	txt.Print();
	txt.SetLine("work2");
	txt.Print();
	txt.GoFirstLink();
	//txt.PrintFreeLink();
}