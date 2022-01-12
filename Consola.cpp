
/* Funcoes da consola. Dez 2010 */

#include "Consola.h"                      
#include <windows.h>
#include <iostream>
#include<string>
using namespace std;

Consola::Consola() {
	hconsola = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle (STD_INPUT_HANDLE);
	hwnd = GetConsoleWindow(); // NT upwards. Nem queiram saber como seria para 95 e 98
	sizex=0;
	sizey=0;
	deslx=0;
	desly=0;
}

void Consola::gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hconsola,coord);
}
   
void Consola::clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	const COORD startCoords = {0,0};   
	DWORD dummy;
  
	GetConsoleScreenBufferInfo(hconsola,&csbi);
	FillConsoleOutputCharacter(hconsola,
                               ' ',
                               10000* 10000,
                               startCoords,
                               &dummy);    
	FillConsoleOutputAttribute(hconsola,
							   csbi.wAttributes,
                               10000 * 10000,
                               startCoords,
							   & dummy);
	gotoxy(0,0);
}

void Consola::setTextColor(WORD color) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hconsola,&csbi);
	WORD cor = csbi.wAttributes;
	cor &= 0xFFF0;
	cor |= color;
	// duvidas acerca destas duas linhas -> TI ou TAC
	SetConsoleTextAttribute(hconsola,cor);
	return;
}

void Consola::setBackgroundColor(WORD color) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hconsola,&csbi);
	WORD cor = csbi.wAttributes;
	cor &= 0xFF0F;
	cor |= (color << 4);
	// duvidas acerca destas duas linhas -> TI ou TAC
	SetConsoleTextAttribute(hconsola,cor);
}

void Consola::setScreenSize(int nLinhas, int nCols) {
	COORD tam;
	SMALL_RECT DisplayArea;

	tam.X = nCols;
	sizex=nCols;
	tam.Y = nLinhas;
	sizey=nLinhas;
	SetConsoleScreenBufferSize(hconsola, tam);   // isto muda o tamanho da matriz de caracteres

	DisplayArea.Top = 0;
	DisplayArea.Left = 0;
	DisplayArea.Bottom = nLinhas-1;
	DisplayArea.Right = nCols-1;
    SetConsoleWindowInfo(hconsola, TRUE, &DisplayArea);  // isto muda o tamanho da area da janela em caracteres
}

// usar esta de preferência a não ser que se esteja no XP ou anterior
void Consola::setTextSize(int x, int y) {
	CONSOLE_FONT_INFOEX cfont;

	cfont.cbSize=sizeof(CONSOLE_FONT_INFOEX);

	GetCurrentConsoleFontEx(hconsola, false, & cfont);
	cfont.dwFontSize.X = x;
	cfont.dwFontSize.Y = y;
	SetCurrentConsoleFontEx(hconsola, false, &cfont);
}


char Consola::getch(void) {
	INPUT_RECORD irInputRecord;
	DWORD dwEventsRead;
	CHAR cChar;

	while(ReadConsoleInputA(hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
		if (irInputRecord.EventType == KEY_EVENT
			&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
			&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
			&& irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
		{

		cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
		ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */

		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) return ESQUERDA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) return DIREITA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP) return CIMA;
		if (irInputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) return BAIXO;

		return cChar;
    }
  return EOF;
}


// setTextSize - Usar isto apenas se a outra não funcionar (XP ou menos)
// O método de funcionamento é bastante força-bruta
//   Procura uma fonte que cupra os requisitos do novo tamanho
//   e muda para essa fonte (ou seja, muda tambéma fonte)
// Funções que a MS nem se deu ao trabalho de documentar
// Help: http://blogs.microsoft.co.il/blogs/pavely/archive/2009/07/23/changing-console-fonts.aspx
typedef BOOL (WINAPI * SetConsoleFont_)(HANDLE ConsoleOutput, DWORD FontIndex); // kernel32!SetConsoleFont
typedef BOOL (WINAPI * GetConsoleFontInfo_)(HANDLE ConsoleOutput, BOOL Unknown1, DWORD Unknown2, PCONSOLE_FONT_INFO ConsoleFontInfo); // kernel32!GetConsoleFontInfo
typedef DWORD (WINAPI * GetNumberOfConsoleFonts_)(); // kernel32!GetNumberOfConsoleFonts


void Consola::setTextSizeXP(int x, int y){
	// Configura acesso às funções "secretas" do Windows
    SetConsoleFont_ SetConsoleFont = reinterpret_cast<SetConsoleFont_>(GetProcAddress(GetModuleHandle("kernel32.dll"), "SetConsoleFont"));
    GetConsoleFontInfo_ GetConsoleFontInfo = reinterpret_cast<GetConsoleFontInfo_>(GetProcAddress(GetModuleHandle("kernel32.dll"), "GetConsoleFontInfo"));
    GetNumberOfConsoleFonts_ GetNumberOfConsoleFonts = reinterpret_cast<GetNumberOfConsoleFonts_>(GetProcAddress(GetModuleHandle("kernel32.dll"), "GetNumberOfConsoleFonts"));
      
    // Num de fontes
	DWORD NumFonts = GetNumberOfConsoleFonts();

    // alloca matriz de cont infos
	CONSOLE_FONT_INFO* ConsoleInfo = new CONSOLE_FONT_INFO[sizeof(CONSOLE_FONT_INFO) * NumFonts];

    // obtem info das fontes todas
	GetConsoleFontInfo(hconsola, FALSE, NumFonts, ConsoleInfo);

    // percorre-as todas. O melhor é não chamar isto muitas vezes
    for (size_t i = 0; i < NumFonts; ++i) {
		// Indaga o tamanho (suportado) da fonte. Pode não haver nenhuma para esse tamanho
		ConsoleInfo[i].dwFontSize = GetConsoleFontSize(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleInfo[i].nFont);

		// Encontrou uma. muda para essa e já está (mesmo que haja outras)
		if (ConsoleInfo[i].dwFontSize.X == x && ConsoleInfo[i].dwFontSize.Y == y) {
			// x,y = tamanho desejado (se houver)
			// muda para essa fonte e sai
			SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleInfo[i].nFont);
			break;
		}
	}

	// devolve a matriz de INFO
	delete [] ConsoleInfo;
}


void Consola::setCellcolor(int x,int y,WORD color,string tipo,int id)
{
	setTextColor(PRETO);
	setBackgroundColor(color);
	x*=2;
	y*=2;
	x+=2;
	y+=2;
	gotoxy(x,y);
	
	cout<<" ";
	gotoxy(x+1,y);
	cout<<" ";
	gotoxy(x,y);
	cout<<tipo;
	gotoxy(x,y+1);
	cout<<" ";
	gotoxy(x+1,y+1);
	gotoxy(x,y+1);
	if(id<10)
		cout<<"0"<<id;
	else
		cout<<id;
}

int Consola::getsizex(){
	return sizex;
}

int Consola::getsizey(){
	return sizey;
}

int Consola::getdeslx(){
	return deslx;
}

int Consola::getdesly(){
	return desly;
}

int Consola::setdeslx(int d,int lim){
	if(d>=deslx*-1)
	{
		if(d>0 && deslx+(sizex-2)/2-2<lim)
		{
			deslx=deslx+d;
			return 1;
		}

		if(d<0 && deslx+(sizex-2)/2-2<=lim)
		{
				deslx=deslx+d;
				return 1;
		}
	}
		return 0;
}

int Consola::setdesly(int d,int lim){
	if(d>=desly*-1)
	{
		if(d>0 && desly+(sizey-42)<lim)
		{
			desly=desly+d;
			return 1;
		}
		if(d<0 && desly+(sizey-42)<=lim)
		{
			desly=desly+d;
			return 1;
		}
	}
	return 0;
}	