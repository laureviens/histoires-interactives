/*
			///||================================---2018/05/14---================================||\\\
\\\||================================---Tentative de cadre pour fiction interactive---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>            //Librairie comprenant les fonctions d'entr�e et de sortie de base
#include <fcntl.h>             //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons vect
# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/fonction_find_maison.cpp"   //Pour la fonction find()


//1) Gros brainstorm
/*

	//i) De quoi je veux parler?
		Simplement une fille qui lit les journaux sur son ordinateur dans sa chambre, la porte entrouverte.
		Le chat de la maison [Crocus; ou nom al�atoire] entre. 
				***Peut-�tre, si tout se passe bien, poursuivre en d�veloppant une personalit� � Crocus??? (timide, arrogant, etc.)
		En fait, l'histoire commence par : "Tu l'entends avant de le voir" ou quelque chose de clich�, suivi des MAOOWww...
				*** BTW, si tout se passe bien, les miaulements pourraient appara�trent en parall�le au reste du texte? De fa�on � le couper...
						1) Je desc 
						2) Je descends
						        MIAAAAW
						3) Je descends
						        MIAAAAWWwouuuu				
	                                   l'escalier
						3) Je descends
						        MIAAAAWWwouuuuuuuuuuhhhh h h h h -h.				
	                                   l'escalier en �vitant soigneusement la colle d'attention qui s'entre-faufile � mes pieds.
		Le but du jeu serait simplement de faire taire le chat.
		*** BTW il serait int�ressant de jouer avec les couleurs, par exemple en ouvrant les rideaux ferm�s, faisant passer le background
			ou le texte de gris clair � blanc
		Prioriser des actions simples, � r�p�ter parfois (genre flatter le chat), qui ne m�nent pas � de grandes narrations, mais qui changent les �tats.
		Flatter le chat, Ignorer le chat, Ouvrir les rideaux, Fermer les rideaux, Se lever, Tasser le chat, 
	
	//ii) Quels sont les buts de l'exercice?
		Au strict minimum, j'aimerais pouvoir simplement copier BOREALIS, avec une structure simple + plus modulaire (moins d'embranchement,
		plus de phrases � placer partout).
		
		Au minimum, j'aimerais pouvoir avoir un jeu dynamique, dans lequel le bon moment peut passer sans que tu fasses quoi que ce soit.
		Qui n'a pas besoin d'attendre apr�s lu joueuxe tout le temps; mais qui PEUX le faire quand c'est b�n�fique � l'exp�rience.
		� la limite, faire un semblant de "Far Cry 4", o� la situation peut se r�gler si tu ne fais absolument rien (le chat se tanne).
		
		Pour du d�fi, j'aimerais que certaines sorties d'�criture se fassent en parall�le (voir ci-dessus).
		
		Pour compl�ter le portrait, j'aimerais pouvoir multiplier les caract�ristiques "costumisables", pour des exp�riences diff�rentes chaque fois.
		
	
	//iii) Quelle est une structure projet�e?

		-Compteurs � la vol�e
		
				-Compteur de temps:
					-Depuis l'arr�t de l'ex�cution de n'importe quelle fonction
					-Depuis certains moments sp�cifiques (biblioth�que de toutes les fonctions d�funtes et leur temps d'arr�t?)
					-Depuis l'�criture de la derni�re lettre de ce parall�le
					
				-	
		
		-Classe � cr�er (toutes)
				
				-Classe : phrase + conditions d'application
				
				-Classe : phrases/mots alternatives � utiliser?
				
				-Classe : Organisation des ordres d'apparition des phrases
							ex: "Il fait beau! Comment tu vas?" vs "Comment tu vas? Il fait beau!"
							
						//Va falloir DESSINER ce genre de choses pour pouvoir �tablir une structure claire.		 
				 
				
				-Classe : personnage + toutes ses caract�ristiques al�atoires
				
		-Objets � cr�er (minimaux)
		
				-Objet conservant les diff�rentes phrases (blocs de base) (avec chacune un ID unique)
				
				-Objet conservant les diff�rentes structures
				
				-Objet compilant o� on en est dans la strucutre
							==Peut �tre int�gr� � l'objet conservant les structures!
							Genre; Structure 1: -Choisie? -Quels sont les phrases propos�es (et leur ordre)? Quel est l'indexation actuelle (0,1,2,etc.)?
				
				-Objet compilant quelle id�e (bloc de structures) a �t� pr�sent�e � date (on en est o� dans l'histoire)
							==Peut �tre int�gr� dans l'objet conservant les blocs de structures!
							Genre; Id�e 1: -Faite? -Quels sont les blocs propos�s?  
									==Int�grer �galement, dans l'objet conservant les blocs de structures,
									un marqueur d'� quel "thread" appartient l'objet.
				
				

*/
