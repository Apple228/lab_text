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
	PTTextLink pFirst;        // указатель корня дерева
	PTTextLink pCurrent;      // указатель текущей строки
	std::stack< PTTextLink > Path; // стек траектории движения по тексту
	std::stack< PTTextLink > St;   // стек для итератора
	PTTextLink GetFirstAtom(PTTextLink pl); // поиск первого атома
	void PrintText(PTTextLink ptl);         // печать текста со звена ptl
	PTTextLink ReadText(std::ifstream& TxtFile); // чтение текста из файла
public:
	TText(PTTextLink pl = nullptr);
	~TText() { pFirst = nullptr; }
	PTText GetCopy();

	// навигация (переделал в void из int)
	void GoFirstLink(); // переход к первой строке
	void GoDownLink();  // переход к следующей строке по Down
	void GoNextLink();  // переход к следующей строке по Next
	void GoPrevLink();  // переход к предыдущей позиции в тексте

	// доступ
	std::string GetLine(void);   // чтение текущей строки
	void SetLine(std::string s); // замена текущей строки 

	// модификация
	void InsDownLine(std::string s);    // вставка строки в подуровень
	void InsDownSection(std::string s); // вставка раздела в подуровень
	void InsNextLine(std::string s);    // вставка строки в том же уровне
	void InsNextSection(std::string s); // вставка раздела в том же уровне
	void DelDownLine(void);        // удаление строки в подуровне
	void DelDownSection(void);     // удаление раздела в подуровне
	void DelNextLine(void);        // удаление строки в том же уровне
	void DelNextSection(void);     // удаление раздела в том же уровне

	// итератор
	int Reset(void);               // установить на первую звапись
	int IsTextEnded() const { return !St.size(); };  // текст завершен?
	int GoNext(void);              // переход к следующей записи

	// работа с файлами
	void Read(char* pFileName);   // ввод текста из файла
	void Write(char* pFileName);  // вывод текста в файл

	// печать
	void Print(void);              // печать текста
};

#endif