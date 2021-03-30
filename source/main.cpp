#include <iostream>
#include "text.h"
#include "textlink.h"
using namespace std;

int main()
{
	TTextLink::InitMemSystem();
	TText txt;
	txt.SetLine("work1");
//	cout << txt.GetLine()<<endl;
	txt.InsNextLine("very well!");
	txt.GoNextLink();
	txt.SetLine("Very Well!!!");
//	cout << txt.GetLine() << endl;
	//txt.GetLine();
	//txt.Print();
	txt.Print();


}