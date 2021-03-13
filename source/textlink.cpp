#include <conio.h>
#include "textlink.h"
#include "ttext.h"

TTextMem TTextLink::MemHeader;

void TTextLink::InitMemSystem(int size) //инициализация памяти
{
	char Line[100];
	MemHeader.pFirst = (PTTextLink) new char[sizeof(TTextLink) * size];
	MemHeader.pFree = MemHeader.pFirst;
	MemHeader.pLast = MemHeader.pFirst + (size - 1);
	PTTextLink pLink = MemHeader.pFirst;
	for (int i = 0; i < size - 1; i++, pLink++) //размерка памяти
	{
		pLink->pNext = pLink + 1;
	}
	pLink->pNext = NULL;
}
void TTextLink::PrintFreeLink() // печать свободных звеньев
{ 
	std::cout << "List of free links" << std::endl;
	for (PTTextLink pLink = MemHeader.pFree; pLink != nullptr; pLink = pLink->pNext)
		std::cout << pLink->Str << std::endl;
}
void* TTextLink::operator new(size_t size) // выделение звена
{ 
	PTTextLink pLink = MemHeader.pFree;
	if (MemHeader.pFree != nullptr)
		MemHeader.pFree = pLink->pNext;
	return pLink;
}
