// Trying to figure out how the `<chrono> library works

#include <chrono>
#include <iostream>   //Pour les entr�es/sorties


int ms = std::chrono::duration_cast< std::chrono::milliseconds >(
    std::chrono::system_clock::now().time_since_epoch()
).count();

		//Ok! Pour commenter:
		/*
			duration_cast<METTREUNTYPEICI>() va convertir le temps, - donn� en secondes par now().time_since_ephoch() -, en millisecondes
			.cout() va convertir l'objet "duration" r�sultant en un integer.
		*/

		//Je crois que de pr�ciser le time_since_epoch est... optionnel?
/*int ms_flou = std::chrono::duration_cast< std::chrono::milliseconds >(
    std::chrono::system_clock::now()
).count();/*                             Nope, pas optionnel; cette derni�re ligne ne fonctionne pas!
 

int main()
{
  std::cout << "Hello World!";
  std::cout << "Depuis le 1er janvier 1970, " << ms << " millisecondes sont mortes!";
}
