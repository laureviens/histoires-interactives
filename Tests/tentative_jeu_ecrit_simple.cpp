/*
			///||================================---2018/05/14---================================||\\\
\\\||================================---Tentative de cadre pour fiction interactive---================================||///
*/

//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>            //Librairie comprenant les fonctions d'entrée et de sortie de base
#include <fcntl.h>             //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons vect
# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/fonction_find_maison.cpp"   //Pour la fonction find()


//1) Gros brainstorm
/*

	//i) De quoi je veux parler?
		Simplement une fille qui lit les journaux sur son ordinateur dans sa chambre, la porte entrouverte.
		Le chat de la maison [Crocus; ou nom aléatoire] entre. 
				***Peut-être, si tout se passe bien, poursuivre en développant une personalité à Crocus??? (timide, arrogant, etc.)
		En fait, l'histoire commence par : "Tu l'entends avant de le voir" ou quelque chose de cliché, suivi des MAOOWww...
				*** BTW, si tout se passe bien, les miaulements pourraient apparaîtrent en parallèle au reste du texte? De façon à le couper...
						1) Je desc 
						2) Je descends
						        MIAAAAW
						3) Je descends
						        MIAAAAWWwouuuu				
	                                   l'escalier
						3) Je descends
						        MIAAAAWWwouuuuuuuuuuhhhh h h h h -h.				
	                                   l'escalier en évitant soigneusement la colle d'attention qui s'entre-faufile à mes pieds.
		Le but du jeu serait simplement de faire taire le chat.
		*** BTW il serait intéressant de jouer avec les couleurs, par exemple en ouvrant les rideaux fermés, faisant passer le background
			ou le texte de gris clair à blanc
		Prioriser des actions simples, à répéter parfois (genre flatter le chat), qui ne mènent pas à de grandes narrations, mais qui changent les états.
		Flatter le chat, Ignorer le chat, Ouvrir les rideaux, Fermer les rideaux, Se lever, Tasser le chat, 
	
	//ii) Quels sont les buts de l'exercice?
		Au strict minimum, j'aimerais pouvoir simplement copier BOREALIS, avec une structure simple + plus modulaire (moins d'embranchement,
		plus de phrases à placer partout).
		
		Au minimum, j'aimerais pouvoir avoir un jeu dynamique, dans lequel le bon moment peut passer sans que tu fasses quoi que ce soit.
		Qui n'a pas besoin d'attendre après lu joueuxe tout le temps; mais qui PEUX le faire quand c'est bénéfique à l'expérience.
		À la limite, faire un semblant de "Far Cry 4", où la situation peut se régler si tu ne fais absolument rien (le chat se tanne).
		
		Pour du défi, j'aimerais que certaines sorties d'écriture se fassent en parallèle (voir ci-dessus).
		
		Pour compléter le portrait, j'aimerais pouvoir multiplier les caractéristiques "costumisables", pour des expériences différentes chaque fois.
		
	
	//iii) Quelle est une structure projetée?

		-Compteurs à la volée
		
				-Compteur de temps:
					-Depuis l'arrêt de l'exécution de n'importe quelle fonction
					-Depuis certains moments spécifiques (bibliothèque de toutes les fonctions défuntes et leur temps d'arrêt?)
					-Depuis l'écriture de la dernière lettre de ce parallèle
					
				-	
		
		-Classe à créer (toutes)
				
				-Classe : phrase + conditions d'application
				
				-Classe : phrases/mots alternatives à utiliser?
				
				-Classe : Organisation des ordres d'apparition des phrases
							ex: "Il fait beau! Comment tu vas?" vs "Comment tu vas? Il fait beau!"
							
						//Va falloir DESSINER ce genre de choses pour pouvoir établir une structure claire.		 
				 
				
				-Classe : personnage + toutes ses caractéristiques aléatoires
				
		-Objets à créer (minimaux)
		
				-Objet conservant les différentes phrases (blocs de base) (avec chacune un ID unique)
				
				-Objet conservant les différentes structures
				
				-Objet compilant où on en est dans la strucutre
							==Peut être intégré à l'objet conservant les structures!
							Genre; Structure 1: -Choisie? -Quels sont les phrases proposées (et leur ordre)? Quel est l'indexation actuelle (0,1,2,etc.)?
				
				-Objet compilant quelle idée (bloc de structures) a été présentée à date (on en est où dans l'histoire)
							==Peut être intégré dans l'objet conservant les blocs de structures!
							Genre; Idée 1: -Faite? -Quels sont les blocs proposés?  
									==Intégrer également, dans l'objet conservant les blocs de structures,
									un marqueur d'à quel "thread" appartient l'objet.
				
				

*/
