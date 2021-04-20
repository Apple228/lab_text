// Text_Processing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdlib.h>
#include<conio.h>
#pragma hdrstop
#include"ttext.h"
#include <windows.h>
#include "pch.h"
#pragma argsused

string strs[100];
int ns, nl;
void TextTyper(TText& txt)
{
    clrscr();
    gotoxy(1, 2);
    txt.Print();
    ns = 0;
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
        strs[ns++] = txt.GetLine();
    txt.GoFirstLink();
    nl = 2;
    gotoxy(1, nl);
    cout << '\333';
}
void TextLineMark(TText& txt)
{
    string st = txt.GetLine();
    gotoxy(1, nl);
    cout << " ";
    for (nl = 0; nl < ns; nl++)
        if (st == strs[nl])break;
    nl += 2;
    gotoxy(1, nl);
    cout << "\333";
}
#define HOME 71
#define DOWN 80
#define NEXT 77
#define UP 72
#define ESC 27
#define INS 82
#define DEL 83
#define ENTER 13
void TextProcessor(TText& txt)
{
    int dir, unit;
    string st;
    char ch;
    do 
    {
        gotoxy(1, 1);
        cout << ">,v,^,Home,Ins,Del,Enter,Esc";
        ch = _getch();
        if (ch == ESC)break;
        if (ch != ENTER)ch = _getch();
        switch (ch) {
        case ENTER:
            gotoxy(1, 1); system("cls"); //clreol();
            cout << "Line (withous blanks): "; cin >> st;
            txt.SetLine(st);
            TextTyper(txt);     break;
        case HOME:
            txt.GoFirstLink(); break;
        case DOWN:
            
            txt.GoDownLink(); break;
        case NEXT:
            txt.GoNextLink(); break;
        case UP:
            txt.GoPrevLink(); break;
        case INS:

        case DEL:
            gotoxy(1, 1); system("cls");//clreol();
            cout << "Direction: 0 - Down, 1 - Next "; cin >> dir;
            gotoxy(1, 1); system("cls");//clreol();
            cout << "Unit: 0 - Line, 1 - Section "; cin >> unit;
            if (ch == INS)
            {
                gotoxy(1, 1); system("cls"); //clreol();
                cout << "Line(without blanks): "; cin >> st;
                if (dir == 0)
                    if (unit == 0) txt.InsDownLine(st); else txt.InsDownSection(st);
                else
                    if (unit == 0) txt.InsNextLine(st); else txt.InsDownSection(st);
            }
            else {
                if (dir == 0)
                    if (unit == 0) txt.DelDownLine(); else txt.DelDownSection();
                else
                    if (unit == 0) txt.DelNextLine(); else txt.DelNextSection();
            
            }
            TextTyper(txt);
            break;
        }
        TextLineMark(txt);
    } while (ch != ESC);
}
TTextMem TTextLink::MemHeader;
int main()
{
    setlocale(LC_ALL, "rus");
    TTextLink::InitMemSystem();
    TText txt, * pText;
    txt.Read("tt.txt");
    TextTyper(txt);
    TextProcessor(txt);
    cout << "Final Printing" << endl;
    txt.Print();
    TTextLink::MemClear(txt);//MemClaener
    TTextLink::PrintFreeLink();
    
    cout << "printing by iterator" << endl;
    for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
        cout << txt.GetLine() << endl;

    pText=txt.GetCopy();
    cout<<"text copy"<<endl;
    pText->Print();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
