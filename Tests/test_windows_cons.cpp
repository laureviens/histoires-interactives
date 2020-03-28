#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

#include <windows.h>


//UPDATE:::  (2020-03-26)

/*

https://stackoverflow.com/questions/21154060/how-to-change-window-size-in-c

#DaveWalley:

	This works for me:

	HWND hwnd = GetConsoleWindow();
	if( hwnd != NULL ){ MoveWindow(hwnd ,340,550 ,680,150 ,TRUE); }

#Reply:

	If your looking for changing the screen buffer then :
	
	HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sizeOfBuff;
	sizeOfBuff.X=150;
	sizeOfBuff.Y=100;
	SetConsoleScreenBufferSize(buff,sizeOfBuff);
	
	To resize the screen use DaveWalley's solution.
	
	Or you could do this (only for resizing)
	
	HWND hwnd = GetConsoleWindow();
	if( hwnd != NULL ){ SetWindowPos(hwnd ,0,0,0 ,1000,300 ,SWP_SHOWWINDOW|SWP_NOMOVE); }

*/
		//Si je comprends bien, y'a vraiment une diff�rence entre la fen�tre et le buffer...

			//Et c'est �a que j'observais aussi quand je runnais mon programme: ma fen�tre ne changeais pas de taille EN COURS D'EX�CUTION.
					//Si j'utilisais les fonctions pr�sentes dans le fichier actuel � l'int�rieur d'un menu, une barre de d�filement appara�ssait dans ma fen�tre (indiquant que j'avais une ligne de plus), sans que la fen�tre bouge.
					//Et si je tentais de faire fitter manuellement la fen�tre, c'�tait dur d'avoir quelque chose de beau.
				
				//Fait que peut-�tre essayer d'enroler "MoveWindow()" dans mes plans? Genre, � la limite, de CHANGE BUFFER, et d'ensuite GET BUFFER INFO, pour ensuite utiliser buffer info pour MOVE WINDOWS?
			
	
//----------------------------------------------------------------------------		//From     http://www.cplusplus.com/forum/windows/10731/
struct console
  {
  console( unsigned width, unsigned height )
    {
    SMALL_RECT r;
    COORD      c;
    hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (!GetConsoleScreenBufferInfo( hConOut, &csbi ))
      throw runtime_error( "You must be attached to a human." );

    r.Left   =
    r.Top    = 0;
    r.Right  = width -1;
    r.Bottom = height -1;
    SetConsoleWindowInfo( hConOut, TRUE, &r );

    c.X = width;
    c.Y = height;
    SetConsoleScreenBufferSize( hConOut, c );
    }

  ~console()
    {
    SetConsoleTextAttribute(    hConOut,        csbi.wAttributes );
    SetConsoleScreenBufferSize( hConOut,        csbi.dwSize      );
    SetConsoleWindowInfo(       hConOut, TRUE, &csbi.srWindow    );
    }

  void color( WORD color = 0x07 )
    {
    SetConsoleTextAttribute( hConOut, color );
    }

  HANDLE                     hConOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  };

//----------------------------------------------------------------------------
console con( 40, 40 );

//----------------------------------------------------------------------------
int main()
  {
  con.color( 0x1B );
  cout << "Press ";
  con.color( 0x5E );
  cout << " ENTER ";
  con.color( 0x1B );
  cout << " to quit.";

  cin.ignore( numeric_limits <streamsize> ::max(), '\n' );

  return 0;
  }
