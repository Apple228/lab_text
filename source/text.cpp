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
int TText::GoFirstLink() { // переход к первой строке
    while (!Path.empty())
        Path.pop(); // очистка стека
    pCurrent = pFirst;
    if (pCurrent == nullptr)
        throw TextError;
}


void TText::SetLine(std::string s) { // замена текущей строки
    if (pCurrent == nullptr)
        throw TextError;
    strncpy(pCurrent->Str, s.c_str(), TextLineLength);
    pCurrent->Str[TextLineLength - 1] = '\0';
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