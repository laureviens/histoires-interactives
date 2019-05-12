// Replace Line.cpp : main project file.   From : http://www.cplusplus.com/forum/beginner/88558/

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int, int);

int main()
{
	int line=0;
	int col=0;
	gotoXY(5,12);
	cout << "1) This is line one";
	gotoXY(5,14);
	cout << "2) This is line two";
	gotoXY(5,16);
	cout << "3) This is line three";
	
	do
	{
		gotoXY(5,20);
		cout << "Replace which line? ( 1, 2 or 3 )";
		cin >> line;
		if (line<1 || line>3)
		{
			gotoXY(5,22);
			cout << "We only have three lines..";
			Sleep(1500); 
			gotoXY(5,22);
			cout << "                           ";
		}
	} while ( line<1||line>3);

		//Remplacer la ligne � la bonne place (gotoXY est une fonction custom)
gotoXY(8,10+(line*2));
cout << "This is a new line..";

	do
	{
		gotoXY(5,20);
		cout << "Paint which color? ( red (1), blue (2) or green (3) )";
		cin >> col;
		if (col<1 || col>3)
		{
			gotoXY(5,22);
			cout << "We only have three colors..";
			Sleep(1500); 
			gotoXY(5,22);
			cout << "                           ";
		}
	} while ( col<1||col>3);
	
	
	//Changer la couleur du texte, mais juste apr�s ce qui a d�j� �t� �crit!
/*
if(col==1) {SetConsoleTextAttribute(console, FOREGROUND_RED);}   //"console" a �t� d�finie comme objet � la 9e ligne	
if(col==2) {SetConsoleTextAttribute(console, FOREGROUND_BLUE);}  	
if(col==3) {SetConsoleTextAttribute(console, FOREGROUND_GREEN);}  	
*/

//Ou encore:
if(col==1) {SetConsoleTextAttribute(console, 4);}   //Ici, �a ne fait que changer le texte (foreground).	
if(col==2) {SetConsoleTextAttribute(console, 1);}  	//Probablement parce que mon argument est numeric,
if(col==3) {SetConsoleTextAttribute(console, 2);}  	//et que �a prend du type WORD. Voir exemple plus bas.


/*
The different color codes are         //from: http://www.cplusplus.com/forum/beginner/54360/

0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/

//�crire quelque chose:
cout << "     Bravo, tu a reussi!\n";

// Para�t que system("color #") va changer la couleur de l'�cran au complet!   //from: http://www.cplusplus.com/forum/beginner/3662/



//Tenter de changer toutes les couleurs
Sleep(1000);
system("color 7");        //�a remet la couleur normale: 7 (gris clair) (partout).  
system("color B");         //�a met en cyan... Ouin, le "chiffre" � mettre est en hexad�cimales...
system("color F");        //�a met en blanc �clatant!

/*
Mais j'ai trouv� �a sur https://stackoverflow.com/questions/17125440/c-win32-console-color:

I know a bit how to do colors in Win32 C++ console. But it's not really efficient. For example:
 SYSTEM("color 01")
Slows down a lot on your process.
*/

/*                  //Mais j'ai trouv� �a sur http://www.cplusplus.com/forum/beginner/5830/    
*ahem*
Please don't tell people to use system(). If you are going to do something OS-dependant, do it the right way.
        (utilise ensuite <window.h>)   ; Para�t que c'est plus risqu�, system(), et que "people at microsoft" n'aiment pas.
*/ 

/*btw: il dit entre autre:

The wierdest parts above are the WaitForSingleObject() --which is being used pretty much like kbhit()-- 
and FlushConsoleInputBuffer() --which reads and tosses whatever key was pressed.

� propos de �a:

#include <iostream>
#include <windows.h>

int main()
{
	const WORD colors[] =
		{
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
		};

	HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  );
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	WORD   index   = 0;

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );

	// Tell the user how to stop
	SetConsoleTextAttribute( hstdout, 0xEC );
	std::cout << "Press any key to quit.\n";

	// Draw pretty colors until the user presses any key
	while (WaitForSingleObject( hstdin, 100 ) == WAIT_TIMEOUT)
	{
		SetConsoleTextAttribute( hstdout, colors[ index ] );
		std::cout << "\t\t\t\t Hello World \t\t\t\t" << std::endl;
		if (++index > sizeof(colors)/sizeof(colors[0]))
			index = 0;
	}
	FlushConsoleInputBuffer( hstdin );

	// Keep users happy
	SetConsoleTextAttribute( hstdout, csbi.wAttributes );
	return 0;
	
	*/


//Stroboscope
for(int a=0; a<1; a++){
	Sleep(400);
	system("color B");
	Sleep(400);
	system("color D");
}

gotoXY(5,20);
cout << "   Program finished!!             ";

	cin.clear();
	cin.sync();
	cin.get();
	return 0;
}

void gotoXY(int x, int y) 
{ 
CursorPosition.X = x; 
CursorPosition.Y = y; 
SetConsoleCursorPosition(console,CursorPosition); 
}
