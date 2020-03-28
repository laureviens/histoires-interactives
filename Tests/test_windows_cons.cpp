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
		//Si je comprends bien, y'a vraiment une différence entre la fenêtre et le buffer...

			//Et c'est ça que j'observais aussi quand je runnais mon programme: ma fenêtre ne changeais pas de taille EN COURS D'EXÉCUTION.
					//Si j'utilisais les fonctions présentes dans le fichier actuel à l'intérieur d'un menu, une barre de défilement apparaîssait dans ma fenêtre (indiquant que j'avais une ligne de plus), sans que la fenêtre bouge.
					//Et si je tentais de faire fitter manuellement la fenêtre, c'était dur d'avoir quelque chose de beau.
				
				//Fait que peut-être essayer d'enroler "MoveWindow()" dans mes plans? Genre, à la limite, de CHANGE BUFFER, et d'ensuite GET BUFFER INFO, pour ensuite utiliser buffer info pour MOVE WINDOWS?
			
	
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
