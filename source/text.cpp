#include "text.h"
#include "textlink.h"
#include <fstream>
#define BufLength 80

static char StrBuf[BufLength + 1]; // буфер для ввода строк
static int TextLevel;            // номер текущего уровня текста
TText::TText(PTTextLink pl) {
    if (pl == nullptr)
        pl = new TTextLink();
    pFirst = pl;
    pCurrent = pFirst;
}

//навигация
void TText::GoFirstLink() { // переход к первой строке
    while (!Path.empty())
        Path.pop(); // очистка стека
    pCurrent = pFirst;
    if (pCurrent == nullptr)
        throw TextError;                  //поменять на SetRetCode
}

void TText::GoDownLink(void) //переход к след. строке по Down
{
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pNext == nullptr)
        throw TextError;
    Path.push(pCurrent);
    pCurrent = pCurrent->pNext;
}

void TText::GoNextLink() // переход к следующей строке по Next
{
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pNext == nullptr)
        throw TextError;
    Path.push(pCurrent);
    pCurrent = pCurrent->pNext;
}

void TText::GoPrevLink()     //переход к предыдущей позиции в тексте
{
    if (Path.empty())
        throw TextNoPrev;
    pCurrent = Path.top();
    Path.pop();
}

//доступ
std::string TText::GetLine()   //чтение текущей строки
{
    if (pCurrent == nullptr)
        return std::string("");
    else
        return std::string(pCurrent->Str);
}
void TText::SetLine(std::string s) { // замена текущей строки
    if (pCurrent == nullptr)
        throw TextError;
    strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength - 1] = '\0';
}


//модификация
void TText::InsDownLine(std::string s)  //вставка строки в подуровень
{
    if (pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pDown;
    PTTextLink pl = new TTextLink("", pd, nullptr);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength - 1] = '\0';
    pCurrent->pDown = pl;
}

void TText::InsDownSection(std::string s) { // вставка раздела в подуровень
    if (pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pDown;
    PTTextLink pl = new TTextLink("", nullptr, pd);
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength - 1] = '\0';
    pCurrent->pDown = pl;
}

void::TText::InsNextLine(std::string s) //вставка строки в том же уровне
{
    if (pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pNext;
    PTTextLink pl = new TTextLink("", pd, nullptr); // :-\
    strncpy(pl->Str, s.c_str(), TextLineLength);
    pl->Str[TextLineLength - 1] = '\0';
    pCurrent->pNext = pl;
}

void TText::InsNextSection(std::string s) // вставка раздела в том же уровне
{
    if (pCurrent == nullptr)
        throw TextError;
    PTTextLink pd = pCurrent->pNext;
    PTTextLink pl = new TTextLink("", nullptr, pd);
    strncpy(pl->Str, s.c_str(), TextLineLength);
}

void TText::DelDownLine()  //удаление строи в подуровне
{
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pDown != nullptr)
    {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        if (pl1->pDown == nullptr)
            pCurrent->pDown = pl2;
    }
}

void TText::DelDownSection()
{
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pDown != nullptr)
    {
        PTTextLink pl1 = pCurrent->pDown;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pDown = pl2;
    }
}

void TText::DelNextSection() { // удаление раздела в том же уровне
    if (pCurrent == nullptr)
        throw TextError;
    if (pCurrent->pNext != nullptr) {
        PTTextLink pl1 = pCurrent->pNext;
        PTTextLink pl2 = pl1->pNext;
        pCurrent->pNext = pl2;
    }
    // 
}


// печать текста

void TText::PrintText(PTTextLink ptl) 
{
    if (ptl != nullptr) {
        for (int i = 0; i < TextLevel; i++)
            std::cout << " ";
        std::cout << " ";
        ptl->Print(std::cout);
        std::cout << std::endl;
        TextLevel++;
        PrintText(ptl->GetDown());
        TextLevel--;
        PrintText(ptl->GetNext());
    }
}
void TText::Print()
{
    TextLevel = 0;
    PrintText(pFirst);
}