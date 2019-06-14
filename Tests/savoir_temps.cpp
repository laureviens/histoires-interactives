// Trying to figure out how the `<chrono> library works

#include <chrono>
#include <iostream>   //Pour les entrées/sorties


int ms = std::chrono::duration_cast< std::chrono::milliseconds >(
    std::chrono::system_clock::now().time_since_epoch()
).count();

		//Ok! Pour commenter:
		/*
			duration_cast<METTREUNTYPEICI>() va convertir le temps, - donné en secondes par now().time_since_ephoch() -, en millisecondes
			.cout() va convertir l'objet "duration" résultant en un integer.
		*/

		//Je crois que de préciser le time_since_epoch est... optionnel?
/*int ms_flou = std::chrono::duration_cast< std::chrono::milliseconds >(
    std::chrono::system_clock::now()
).count();/*                             Nope, pas optionnel; cette dernière ligne ne fonctionne pas!
 

int main()
{
  std::cout << "Hello World!";
  std::cout << "Depuis le 1er janvier 1970, " << ms << " millisecondes sont mortes!";
}
