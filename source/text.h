#ifndef _TTEXT_H
#define _TTEXT_H

#include <stack>
#include <fstream>
#include <string>
#include "datacom.h"
#include"textLink.h"
#include "texters.h"
#define BufLength 80

class TText;
typedef TText* PTText;

class TText : public TDataCom
{
protected:
	PTTextLink pFirst;        // ��������� ����� ������
	PTTextLink pCurrent;      // ��������� ������� ������
	std::stack< PTTextLink > Path; // ���� ���������� �������� �� ������
	std::stack< PTTextLink > St;   // ���� ��� ���������
	PTTextLink GetFirstAtom(PTTextLink pl); // ����� ������� �����
	void PrintText(PTTextLink ptl);         // ������ ������ �� ����� ptl
	PTTextLink ReadText(std::ifstream& TxtFile); // ������ ������ �� �����
public:
	TText(PTTextLink pl = nullptr);
	~TText() { pFirst = nullptr; }
	PTText GetCopy();

	// ���������
	int GoFirstLink(); // ������� � ������ ������
	int GoDownLink();  // ������� � ��������� ������ �� Down
	int GoNextLink();  // ������� � ��������� ������ �� Next
	int GoPrevLink();  // ������� � ���������� ������� � ������

	// ������
	std::string GetLine(void);   // ������ ������� ������
	void SetLine(std::string s); // ������ ������� ������ 

	// �����������
	void InsDownLine(std::string s);    // ������� ������ � ����������
	void InsDownSection(std::string s); // ������� ������� � ����������
	void InsNextLine(std::string s);    // ������� ������ � ��� �� ������
	void InsNextSection(std::string s); // ������� ������� � ��� �� ������
	void DelDownLine(void);        // �������� ������ � ���������
	void DelDownSection(void);     // �������� ������� � ���������
	void DelNextLine(void);        // �������� ������ � ��� �� ������
	void DelNextSection(void);     // �������� ������� � ��� �� ������

	// ��������
	int Reset(void);               // ���������� �� ������ �������
	int IsTextEnded() const { return !St.size(); };  // ����� ��������?
	int GoNext(void);              // ������� � ��������� ������

	// ������ � �������
	void Read(char* pFileName);   // ���� ������ �� �����
	void Write(char* pFileName);  // ����� ������ � ����

	// ������
	void Print(void);              // ������ ������
};

#endif