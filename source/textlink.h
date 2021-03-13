#ifndef __TEXTLINK_H
#define __TEXTLINK_H

//#include <alloc.h>
#include <string.h>
#include <iostream>
#include "texters.h"
#include "datvalue.h"
#define TextLineLength 20
#define MemSize 20

class TTextMem
{
	PTTextLink pFirst; //��������� �� ������ �����
	PTTextLink pLast; //��������� �� ��������� �����
	PTTextLink pFree; //��������� �� ������ ��������� �����
	friend class TTextLink;
};
typedef TTextMem* PTTextMem;

class TTextLink : public TDatValue 
{
protected:
	TStr Str;
	PTTextLink pNext, pDown;
	static TTextMem MemHeader;//������� ���������� �������
public:
	static void InitMemSystem(int size = MemSize); // ������������� ������
	static void PrintFreeLink(void);               // ������ ��������� �������
	void* operator new (size_t size);			   // ��������� �����
	//void operator delete (void* pM);			   // ������������ �����
	//static void MemCleaner(const TText& txt);	   // ������ ������
public:
	TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL)
	{
		pNext = pn; pDown = pd;
		if (s != NULL) strcpy(Str, s);
		else Str[0] = '\0';
	}
	~TTextLink(){}
	int IsAtom() { return pDown == NULL; } // �������� ����������� �����
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	TDatValue* GetCopy() { return new TTextLink(Str, pNext, pDown); }
protected:
	virtual void Print(std::ostream& os) { os << Str; }
friend class TText;
};
#endif // !__TEXTLINK_H