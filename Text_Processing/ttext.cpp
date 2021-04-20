constexpr auto BufLenght = 80;
#include<conio.h>
#include "ttext.h"

static char StrBuf[(BufLenght + 1)];
static int TextLevel;

TText::TText(PTTextLink pl) {
	if (pl == NULL) pl = new TTextLink();
	pFirst = pl;

}
int TText::GoFirstLink(void) {
	while (!Path.empty())Path.pop();
	pCurrent = pFirst;
	if (pCurrent == NULL)SetRetCode(TextError); else SetRetCode(TextOK);
	return RetCode;
}
int TText::GoDownLink(void) {
	SetRetCode(TextError);
	if (pCurrent != NULL)
		if (pCurrent->pDown != NULL) 
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pDown;
			SetRetCode(TextOK);
		}
	return RetCode;
}
int TText::GoNextLink(void)
{
	SetRetCode(TextError);
	if (pCurrent->pNext != NULL)
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->pNext;
		SetRetCode(TextOK);
	}
	return RetCode;
}

int TText::GoPrevLink(void) {
	if (Path.empty()) SetRetCode(TextNoPrev);
	else {
		pCurrent = Path.top();
		Path.pop();
		SetRetCode(TextOK);
	}
	return RetCode;
}

void TText::SetLine(string s) {
	if (pCurrent == NULL)SetRetCode(TextError);
	else strncpy_s(pCurrent->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = '\0';
}
string TText::GetLine(void) {
	if (pCurrent == NULL)return string("");
	else return string(pCurrent->Str);
}
void  TText::InsDownLine(string s) {
	if (pCurrent == NULL)SetRetCode(TextError);
	else {
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", pd, NULL);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
		SetRetCode(TextOK);
	}
}
void TText::InsDownSection(string s)
{
	if (pCurrent == NULL)SetRetCode(TextError);
	else {
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink("", NULL, pd);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
		SetRetCode(TextOK);
	}
}
void TText::InsNextLine(string s) // докодить!
{
	if (pCurrent->pNext != NULL)SetRetCode(TextError);
	else {
		PTTextLink pd = pCurrent->pNext;
		PTTextLink pl = new TTextLink("", pd, NULL);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
		SetRetCode(TextOK);
	}
}
void TText::InsNextSection(string s) // докодить!
{
	if (pCurrent->pNext != NULL)SetRetCode(TextError);
	else {
		PTTextLink pd = pCurrent->pNext;
		PTTextLink pl = new TTextLink("", NULL, pd);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
		SetRetCode(TextOK);
	}
}

void TText::DelDownLine(void) {
	SetRetCode(TextOK);
	if (pCurrent == NULL)SetRetCode(TextError);
	else if (pCurrent->pDown != NULL)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		if (pl1->pDown == NULL) pCurrent->pDown = pl2;
	}
}
void TText::DelDownSection(void) {
	SetRetCode(TextOK);
	if (pCurrent == NULL)SetRetCode(TextError);
	else if (pCurrent->pDown != NULL)
	{
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		pCurrent->pDown = pl2;
	}
}

void TText::DelNextLine(void) // докодить!
{
	SetRetCode(TextOK);
	if (pCurrent->pNext == NULL)SetRetCode(TextError);
	else if (pCurrent->pNext != NULL)
	{
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pDown;
		if (pl1->pNext == NULL) pCurrent->pNext = pl2;
	}
}
void TText::DelNextSection(void) // докодить!
{
	SetRetCode(TextOK);
	if (pCurrent->pNext == NULL)SetRetCode(TextError);
	else if (pCurrent->pNext != NULL)
	{
		PTTextLink pl1 = pCurrent->pNext;
		PTTextLink pl2 = pl1->pDown;
		pCurrent->pNext = pl2;
	}
}

//итератор
int TText::Reset(void) {
	while (!St.empty())St.pop();
	pCurrent = pFirst;
	if (pCurrent != NULL)
	{
		St.push(pCurrent);
		if (pCurrent->pNext != NULL) St.push(pCurrent->pNext);
		if (pCurrent->pDown != NULL)St.push(pCurrent->pDown);
	}
	return IsTextEnded();

}
int TText::IsTextEnded(void) const
{
	return !St.size();
}
int TText::GoNext(void) {
	if (!IsTextEnded()) {
		pCurrent = St.top(); St.pop();
			if (pCurrent != pFirst) {
				if (pCurrent->pNext != NULL) St.push(pCurrent->pNext);
				if (pCurrent->pDown != NULL) St.push(pCurrent->pDown);

			}
	}
	return IsTextEnded();
}

PTTextLink TText::GetFirstAtom(PTTextLink pl) {
	PTTextLink tmp = pl;
	while (!tmp->IsAtom()) {
		St.push(tmp); tmp = tmp->GetDown();
	}
	return tmp;
}

PTText TText::GetCopy() {
	PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;

	if (pFirst != NULL) {
		while (!St.empty())St.pop();
		while (true) {
			if (pl != NULL) {
				pl = GetFirstAtom(pl); St.push(pl);
				pl = pl->GetDown();

			}
			else if (St.empty())break;
			else 
			{
				pl1 = St.top(); St.pop();
				if (strstr(pl1->Str, "Copy") == NULL) {
					pl2 = new TTextLink("Copy", pl1, cpl);
				}



			}
		}
	}
	return new TText(cpl);
}
void TText::Print() {
	TextLevel = 0;
	PrintText(pFirst);
}
void TText::PrintText(PTTextLink ptl) {
	if (ptl != NULL) {
		cout << " ";
		for (int i = 0; i < TextLevel; i++)cout << " ";
		cout << " " << *ptl << endl;
		TextLevel++; PrintText(ptl->GetDown());
		TextLevel--; PrintText(ptl->GetNext());
	}
}

void TText::Read(const char* pFileName) {
	ifstream TxtFile(pFileName);
	TextLevel = 0;
	if (TxtFile.is_open()) pFirst = ReadText(TxtFile);
}

PTTextLink TText::ReadText(ifstream& TxtFile) {
	PTTextLink pHead, ptl;
	pHead = ptl = new TTextLink();
	while (TxtFile.eof() == 0)
	{
		TxtFile.getline(StrBuf, TextLineLength);
		if (StrBuf[0] == '}') { TextLevel--; break; }
		else if (StrBuf[0] == '{') 
		{
			TextLevel++; ptl->pDown = ReadText(TxtFile);
		}
		else {

			
			ptl->pNext = new TTextLink(StrBuf, NULL, NULL);
			ptl = ptl->pNext;
			strncpy_s(ptl->Str, StrBuf, TextLineLength);
		}
	}
	ptl = pHead;
	if (pHead->pDown == NULL) {
		pHead = pHead->pNext; delete ptl;
	}
	return pHead;
}