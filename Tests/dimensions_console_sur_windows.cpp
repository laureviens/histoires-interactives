#include <iostream>
                                              //From http://www.cplusplus.com/forum/beginner/1481/
//the following line is necessary for the
//  GetConsoleWindow() function to work!
//it basically says that you are running this
//  program on Windows 2000 or higher
#define _WIN32_WINNT 0x0500

//it is important that the above line be typed
//  BEFORE <windows.h> is included
#include <windows.h>

using namespace std;

int main (void)
{
  HWND console = GetConsoleWindow();
  RECT r;
  GetWindowRect(console, &r); //stores the console's current dimensions

  //MoveWindow(window_handle, x, y, width, height, redraw_window);
  MoveWindow(console, 500, 250, 200, 200, TRUE);                   //Les unités sont en pixels!
  for (int j = 1; j <= 13; ++j)                         //200 pixels ~ 13 lignes; 27 colonnes
    {
    	if(j<3|j>11) {for (int i =1; i<=27 ; i++) cout << '-';};
    	if(j>=3&j<=11) {for (int i =1; i<=27 ; i++) cout << '~';};
    }
  Sleep(1000);
  //MoveWindow(console, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);
}
             //AFAIK, the console can't go beyond 800 pixels, so when you specify the width, it has to be 800 or less.
             
             
    //Le seul problème avec spécifiquement ça:
		/*
		C'est seulement que le curseur bouge à la prochaine position après avoir terminé une ligne. 
		Et tout le texte bouge à sa suite, bien entendu. Donc il manque une ligne.
		Pour éviter, il suffirait simplement de laisser un espace vide dans la dernière colonne (systématiquement),
		et ensuite simplement ne rien écrire à la dernière case. On pourrait même généraliser pour mettre une bordure nulle tout le tour:
		 ________________
		|               |
		| ------------- |
		| ------------- |
		| ------------- |
		| ------------- |
		|_______________|
		*/                 
