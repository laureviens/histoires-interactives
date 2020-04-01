
/*
			///||================================---2018/06/15---================================||\\\
\\\||================================---Cadre fonctionnel global pour lire des histoires---================================||///
*/

//------------------------------------------------------------------------------------------------------------------------------------------------------
//-1) Liste de choses en suspend
/*
	2019-06-18:
				Mon moyen de manipuler la console est en conflit avec le fonctionnement par défaut de la console.
				Je suppose une fenêtre fixe, pour toujours prise dans ses premières lignes.
				Pourtant, dans la console de base, si largeur en x est finie et fixe, la hauteur en y est infinie.
				 
				Pour arriver à contourner cela, il me faut éviter de déplacer automatiquement la fenêtre de la console,
				question de toujours rester entre [0,maxy] en y. 
				Pour éviter de déplacer, il faut éviter de créer une nouvelle ligne à partir de la dernière ligne (maxy).
				
				Pour le moment, le code en tant que tel n'est vraiment pas adapté pour faire face à cette exception.
				Mon moyen de contournement, c'est d'utiliser la dernière ligne de la console pour afficher le texte entré
				(puisque je ne peux pas me fier sur les entrées standardisées de type cin -pour pouvoir entrer le texte n'importe quand-
				pour faire apparaître le input qui est tapé). Ce que j'allais faire de toute façon.
				
				Il serait pourtant safe d'intégrer des "safe-gards" directement dans la fonction lire(), genre printer une erreur et aborter
				le processus si on change de ligne à partir de la dernière. Something like that.
				
				Aussi, pour parvenir à faire fonctionner mon bricolage, je suis parvenue expérimentalement à la ligne:
					curspos(0,canaux.pt[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 
				qui est ma foi un peu patantée. Je ne sais pas pourquoi elle marche, mais c'est la seule qui marche. À revérifier plus tard.
*/

/*
	2020-01-23:
				Maintenant que la démo marche, j'observe que créer une nouvelle ligne quand la console est pleine (ce qui implique de réécrire toute
				la fenêtre au complet) prend un peu de temps et crée un "mini lag". Il serait peut-être bénéfique de revoir les interactions avec la console
				au complet.
				Puisque le code interne de la console semble n'avoir aucun problème avec le changement de ligne "en douceur", je pourrais peut-être simplement 
				l'exploiter: laisser la console passer une ligne (avec '\n'), puis simplement ré-écrire la ligne de commandes.
				Je pense que ça aurait également l'avantage de laisser explorer toute la mémoire, qui resterait écrire dans la console.
				Rendant donc l'objet "mémoire" un peu obsolète (non, car si je veux ajouter des effets "bugs", je dois avoir une sauvegarde du texte)?
					Bref, jouer AVEC la console par défaut, plutôt que contre.
						Contre l'utilisation d'une mémoire (à long terme):
							-Les effets "bugs" peuvent très bien enregistrer la lettre remplacée, déjà qu'ils enregistrent sa position et le remplacement
							-Les interruptions (ajout d'une ligne en plein milieu) et les menus "pause" nécessitent de connaître le texte présent dans la console...
								peut être soit une mémoire à court terme, soit une fonction pour "aller chercher" le texte de la console
								(les deux sont assez rares et "interrompant" pour que le léger lag créer ne pose aucun problème)
								
								
				//Pour plus d'infos sur les possibilités, voir https://docs.microsoft.com/en-us/windows/console/scrolling-a-screen-buffer-s-contents			
								
*/

/*
	2019-07-13:
				Ce qu'il me reste à faire:
					-Vérifier si ça fonctionne comme du monde quand la console est pleine de msn / y'a trop de msn pour la taille de messagerie.
					-En ce moment, pour les commandes mots-clés, si on ne met pas de parenthèses, ça ne marche pas. Messemble dans la fonction de remplissage c'était supposé marcher?
					-Peut-être changer la mémoire de "long terme, finie" à "court terme, infinie" en sauvant moins de lignes mais en écrivant par-dessus?
					-Retravailler le "menu" de quand la commande est ambigüe, pour la mettre plus en ligne avec le reste des menus
							(à la limite, j'pense sérieusement à simplement avoir une sélection de "peser sur ENTER entre des icônes" pour éviter les erreurs connes de frappe)
							(genre, c'est supposé NE PAS ARRIVER, les ambiguité, si l'histoire est si mal écrite que ça, j'pense que ça va pas déranger de perdre un peu) 
							( d' "immersion"  en sélectionnant un bouton à la place de recopier lettre à lettre un mot. Also, c'est plus facile à coder pour moi.)
					-Le système de "lock" d'arrière-plan semble fonctionner à l'envers de ce qu'il devrait être?
							C'est pas trop grave pour le moment; mais éventuellement faudrait régler ça
					-La manière actuelle de gérer la diversité à l'intérieur des motifs n'est pas à la hauteur de mes ambitions...
							Mon plan :
										-Changer la méthode par défaut, carrément.
										-Conserver les mailles (segments de texte)
										-Limiter l'usage conjoint d'enchaînements (écrits manuellement) + probabilités à cas spéciaux (ex: test de chance)
										-Pour le "bulk", y aller en deux étapes:
											-a) Vérifier si on devrait écrire quoi que ce soit du motif at all (odd de n'écrire rien par défaut : 0 (le motif est toujours joué) )
															//Ça, ça donne l'opportunité d'avoir plusieurs motifs "parallèles" qui concernent la même action, mais d'en jouer juste, disons, 2 out of 24 (en moyenne); au hasard.
											-b) Si on écrit, compteur le nombre d'enchaînements possible total, puis piger un nombre parmi celui-ci pour sélectionner (tous les enchaînements ont probabilité égale)
															//Moins lourd à écrire + lire + taxe moins la mémoire dynamique (avec les probs...)
															
										-Le nombre d'enchaînements total consisterait en:
											Les enchaînements définis manuellement (même objet qui serait utilisé si on avait des probs) + les enchaînements définis automatiquement
											-Pour les enchaînements auto (trouver un autre nom... mécanisés?) n'interpréter que lorsque le motif est lu (pour sauver de la place de stockage; et puisque ce n'est pas souvent...)!
												-ex: 1-2-3/4-5/6-7;   serait un enchaînement mécanisé, qui comprend les possibilités: 1-2-3-5-7, 1-2-3-6-7, 1-2-4-5-7, 1-2-4-6-7.  
														On pourrait en définir plusieurs, pour quand même avoir une flexibilité dans les compatibilités.
														Donc en gros, si on a:
															digit : 1-2-3/4-5/6-7; 2-7-9/10 		//nan, j'aime pas digit/analg... Trop sexuel.   Mécan + main? Nan. Pas "main". Mécan + bricol. Tiens.
															analg : 2-9
																En tout, on a (2^2) + (2^1) + 1 = 7 possibilités.
						//Techniquement, c'est écrit.
								//À l'intérieur de "integration()", du moins (manu + auto).
						
						//Il ne reste plus qu'à ajouter des fonctions d'écriture (genre la partie où j'remplie les motifs), et... à TESTER.
									//Fonctions d'écriture + erreurs de compilation réglées! FAUT TESTER MAINTENANT!!!
*/					

/*
	2019-09-04:
				Liste des séparateurs maison:
					'§' sert à séparer les codes spéciaux du reste dans le texte à lire
					';' sert à séparer les genres (féminin;non binaire/neutre;masculin)
					'µ' sert à séparer les segments de texte (mailles) dans la construction d'un motif
					';' sert à séparer les différents enchaînements
					'-' sert à séparer les chiffres d'un même enchaînement
					';' sert à séparer les différentes probabilités d'enchaînement (pratique mais ± logique; considérer un changement?)
					Dans les commandes, '|' sépare les synonymes, '&' sépare les groupes de mots, "[]" dénote les mots à exclure et "()" séparent les façons de le dire
					'µ' sert à marquer les cellules transparentes dans les dessins (présentement : dans les titres des menus)
*/

/*
	2020-02-22:
				J'ai retrouvé la légende pour la couleur:
					FOREGROUND_BLUE 		Text color contains blue.
					FOREGROUND_GREEN 		Text color contains green.
					FOREGROUND_RED 			Text color contains red.
					FOREGROUND_INTENSITY 	Text color is intensified.
					BACKGROUND_BLUE 		Background color contains blue.
					BACKGROUND_GREEN 		Background color contains green.
					BACKGROUND_RED 			Background color contains red.
					BACKGROUND_INTENSITY	Background color is intensified.
			
					// colors are 0=black 1=blue 2=green, 3=aqua, 4=red, 5=pink, 6=yellow, 7=white; et on rajoute une autre couche de 8 couleurs en changeant l'intensité.  
					// colorattribute = foreground + background * 16
					// to get red text on yellow use 4 + 14*16 = 228
					// light red on yellow would be 12 + 14*16 = 236		
	*/
	
	
/*
	2020-03-08:
	
				De l'info par rapport à jouer avec la fenêtre:
				
					//The .srWindow property gives the answer to the size of the console window, i.e. visible rows and cols. This doesn't say what is the actual available screen buffer width and height, which could be larger if window contains scroll bars. If this is the case, use .dwSize:
					
					CONSOLE_SCREEN_BUFFER_INFO sbInfo;
					GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &sbInfo);
					int availableColumns = sbInfo.dwSize.X;
					int availableRows = sbInfo.dwSize.Y;				
					
									//voir aussi pour scroller : https://docs.microsoft.com/en-us/windows/console/scrolling-a-screen-buffer-s-contents			
					
					//On Linux, use the following instead (borrowed from here):
					
					#include <sys/ioctl.h>
					#include <stdio.h>
					#include <unistd.h>
					
					int main (int argc, char **argv)
					{
					    struct winsize w;
					    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
					
					    printf ("lines %d\n", w.ws_row);
					    printf ("columns %d\n", w.ws_col);
					    return 0;  // make sure your main returns int
					}
						
*/	

/*
	2020-03-28:
				BTW: On peut changer les 16 couleurs qui s'affichent dans la console! On est encore limitées à 16, mais ça peut être n'importe lesquelles!!!!
				https://docs.microsoft.com/en-us/windows/console/console-screen-buffer-infoex
				
				BTW: On peut aussi changer le titre de la fenêtre, avec des UNICODES! J'joue pas avec ça pour le moment, though, parce qu'il faudrait que j'aille une fonction pour convertir mes strings
					en unicodes, un peu comme je le faisais avec "out()"...
				https://docs.microsoft.com/en-us/windows/console/setconsoletitle
				
					BTW: restant de ma vielle fonction, qui n'était pas nécessaire finalement:			
						//SetConsoleWindowInfo(console, TRUE, &rectconsactu);					//Spécifie la taille de la "fenêtre intérieure" allouée au texte à l'intérieur de la fenêtre qu'on voit (ne change pas les dimensions de la fenêtre qu'on voit)
						//SetConsoleScreenBufferSize(console,tailleconsactu);					//Spécifie la taille (lignes + colonnes) de l'espace alloué pour écrire du texte ("console screen buffer")						
							
*/

/*
	2020-04-01:
				Plan pour pouvoir "rejouer" des sessions pour voir les réactions des joueuses / carrément juste avoir un système de sauvegarde:
					Simplement y aller en notant quand chaque commande a été entrée.
				
				a) Noter le nom du jeu + la version (faudra ajouter ça comme membre à "univers")
				b) Noter la "random seed", qui est simplement le TIMESINCEEPOCH auquel le jeu a commencé
				c) Corriger les changements de vitesse ([HAUT] et [BAS]) pour qu'ils modifient aussi les nxtt (pour que le défilement soit 100% prévisible)
				d) Ajouter un compteur de temps relatif à la boucle jouer():
					if( (currentt - lastrelativet) * vit >= 1000 ) relativet += round((currentt - lastrelativet) * vit);		(1000 : pour avoir assez de résolution à haute vitesse)
						//Ajouter aussi cet update de relativet à chaque fois que : [ENTER], [ESCAPE], [HAUT] et [BAS] sont appuyés.
						//Inclure également relativet dans "pauseall()".
						
					//Dans le fichier de sauvegarde créé, utiliser simplement les changements de lignes comme séparateurs:
					Sur les toîts		//nom
					1.04				//version
					193940293940294		//seed
					
					4322				//Temps relatif où la première commande a été envoyée
					Skip				//Première commande
					40253
					avancer
					44885
					Grimper sur la clôture
*/	

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard

#define _USE_MATH_DEFINES		//Nécessaire pour aller chercher la valeur de pi
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent (??? Optionnel?)
#include <windows.h>			//Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>				//Nécessaire pour savoir la position du curseur sur Windows
#include <winuser.h>			//Nécessaire pour savoir la position du curseur sur Windows
#include <conio.h>				//Nécessaire pour enregistrer les inputs du clavier
#include <io.h>					//Nécessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>				//Nécessaire pour décrypter les accents en unicode
#include <stdlib.h>				//Nécessaire pour jouer avec des nombres aléatoires  /* srand, rand */

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Fonctions et objets pour interagir avec la console (Attention: séparé entre Windows et Linux) 	//WINDOWS SEULEMENT EST FAIT!!!

		//1) Fonctions et objets pour interagir avec la console (Attention: séparé entre Windows et Linux) 	//WINDOWS SEULEMENT EST FAIT!!!		
		
			//i) Classe : consoleobjet ; divers objets permettant de modifier le texte affiché dans la console   	            	//WINDOWS ONLY
			class fenetre {
				//Membres
				private:
					HWND desktop;											//Objet référent à toute l'information sur l'écran de base (genre sa taille)
					HWND window;											//Objet référent à toute l'information sur la fenêtre de jeu (genre sa taille)
					HANDLE console;									        //Objet référant à toute l'information sur le texte affiché dans la console ("console screen buffer"): sa taille, son contenu, son style, sa couleur...
					COORD CursorPosition;                                     	//Objet permettant de se situer sur la console
					CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;                //Objet permettant de connaître la position du curseur dans la console, ainsi que toutes les autres infos de "console"
					CONSOLE_CURSOR_INFO CursorInfo;	                            //Objet permettant de modifier le curseur
					COORD tailleconsactu;
					COORD tailleconsmin;
					COORD tailleconsmax;
					int charwidth; int charheight;	//"résolution" de l'écran, calculée à partir de la taille de la fenêtre de jeu (en pixels) et du nombre de caractères qu'elle contient
					RECT desktopwindow;				//Tailles des différentes fenêtres à connaître
					RECT taillewindowactu;
					RECT tailleclientactu;
				public:
					int limfenx, limfeny;     	//Dimensions de la fenêtre en terme de nombre de caractères pouvant y être contenus
					int milieufenx, milieufeny;	//Point au milieu, ou un caractère en haut (dans le cas de dimensions paires), de toute la fenêtre
					int limtxtx, limtxty;     	//Dimensions de la portion où le texte s'affiche en terme de nombre de caractères pouvant y être contenus
					int consy;            	 	//Facteur de décalement de la console où apparaît le texte avec la mémoire, où il est stocké
					bool refoule;          		//Flag pour voir si le facteur de décalement entre en compte																							
				//Fonctions membres
					//i) Fonction: curspos ; déplacer le curseur sur la console                                                          //WINDOWS ONLY
					void curspos(int x, int y) { 
						CursorPosition.X = x; CursorPosition.Y = y; 
						SetConsoleCursorPosition(console,CursorPosition);
					}
					//ii) Fonction : chgcol ; change la couleur du texte à entrer                        		                                   //WINDOWS ONLY
					void chgcol(int txtcol, int bgcol) {
						SetConsoleTextAttribute(console, txtcol + 16*bgcol);		//Voir l'entrée du 2020-02-22 pour la légende!
					}
					//iii) Fonction : modifdim ; change les dimensions de la fenêtre, un caractère à la fois
					void modifdim(bool plus, bool ligne) {
						//Modifier les valeurs
						if(ligne) {
							if(plus) {if(tailleconsactu.Y!=tailleconsmax.Y) {tailleconsactu.Y++; taillewindowactu.bottom+=charheight;}} else if(tailleconsactu.Y!=tailleconsmin.Y) {tailleconsactu.Y--; taillewindowactu.bottom-=charheight;}
						} else if(plus) {if(tailleconsactu.X!=tailleconsmax.X) {tailleconsactu.X++; taillewindowactu.right+=charwidth;}} else if(tailleconsactu.X!=tailleconsmin.X) {tailleconsactu.X--; taillewindowactu.right-=charwidth;}
					    //Bouger la fenêtre
						MoveWindow(window,floor((desktopwindow.right-taillewindowactu.right)/2),floor((desktopwindow.bottom-taillewindowactu.bottom)/2),
									taillewindowactu.right,taillewindowactu.bottom,true);			//Spécifie la taille de la fenêtre de jeu en entier, ainsi que sa position (centrée)
						//Obtenir directement les limites de la fenêtre
						GetConsoleScreenBufferInfo(console, &ScreenBufferInfo);           				//Accéder à la taille de la console
						limfenx = ScreenBufferInfo.srWindow.Right + 1; limfeny = ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations
						milieufenx = round(limfenx/2); milieufeny = round(limfeny/2); limtxtx = limfenx; limtxty = limfeny - 1;				
						//Corriger la taille de la zone de texte (afin d'obtenir une barre de défilement constante à travers toutes les tailles de fenêtres)
						SetConsoleScreenBufferSize(console,ScreenBufferInfo.dwSize);
						//Cacher le curseur (ce qui clignote)
						SetConsoleCursorInfo(console,&CursorInfo);
					}
					//iv) Fonction : dimmin ; définit les dimensions minimales de la fenêtre (à faire en fonction du background du menu principal, genre : le plus petit dessin acceptable)
					void dimmin(int x, int y) {tailleconsmin.X = x; tailleconsmin.Y = y;}
					//v) Fonction : dimdef ; définit les dimensions par défaut de la fenêtre (à faire en fonction du bg du menu principal, genre : le plus beau dessin)
					void dimdef(int x, int y) {tailleconsactu.X = x; tailleconsactu.Y = y;}					
					//vi) Fonction : defaultwin ; initie les paramètres et la fenêtre de base avec Windows
					void defaultwin() {
						//Faire les choses de base	
						desktop = GetDesktopWindow(); 													//Aller chercher le bon objet pour l'écran de base
						window = GetConsoleWindow();													//Aller chercher le bon objet pour la fenêtre actuelle
						console = GetStdHandle(STD_OUTPUT_HANDLE);										//Aller chercher le bon objet pour le texte à l'intérieur de la fenêtre actuelle
						_setmode(_fileno(stdout), _O_U16TEXT);												//Permettre l'affichage de l'UNICODE         					
						//Obtenir les tailles de référence
						GetWindowRect(desktop,&desktopwindow);						//Taille de l'écran de base: utile pour centrer la fenêtre
						GetWindowRect(window,&taillewindowactu);					//Taille de la fenêtre de jeu: toute la fenêtre; utile pour pouvoir la resizer + la déplacer
						if(taillewindowactu.left!=0) {taillewindowactu.right = taillewindowactu.right - taillewindowactu.left; taillewindowactu.left = 0;}	//Changer le coin bottom-right pour qu'il signifie les dimensions de la console plutôt qu'une position
						if(taillewindowactu.top!=0) {taillewindowactu.bottom = taillewindowactu.bottom - taillewindowactu.top; taillewindowactu.top = 0;}
						GetClientRect(window,&tailleclientactu);					//Taille de la portion de la fenêtre de jeu où les lettres s'inscrivent: utile pour connaître les dimensions d'un caractère
						tailleconsmax = GetLargestConsoleWindowSize(console);		//Taille maximale déterminée objectivement par les limites de la console
						GetConsoleScreenBufferInfo(console, &ScreenBufferInfo);           				//Accéder à la taille de la console directement
						limfenx = ScreenBufferInfo.srWindow.Right + 1; limfeny = ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations quant à la taille de la console
						charwidth = floor(tailleclientactu.right / limfenx);												//En pixels
						charheight = floor(tailleclientactu.bottom / limfeny);												//En pixels
						//Positionner la fenêtre de jeu au milieu de l'écran
						MoveWindow(window,floor((desktopwindow.right-taillewindowactu.right)/2),floor((desktopwindow.bottom-taillewindowactu.bottom)/2),
									taillewindowactu.right,taillewindowactu.bottom,true);
						//Faire apparaître une fenêtre de la taille par défaut
						while(limfenx!=tailleconsactu.X&&limfeny!=tailleconsactu.Y) {
							if(limfenx<tailleconsactu.X) taillewindowactu.right+=charwidth; else if(limfenx>tailleconsactu.X) taillewindowactu.right-=charwidth;
							if(limfeny<tailleconsactu.Y) taillewindowactu.bottom+=charheight; else if(limfeny>tailleconsactu.Y) taillewindowactu.bottom-=charheight;
							MoveWindow(window,floor((desktopwindow.right-taillewindowactu.right)/2),floor((desktopwindow.bottom-taillewindowactu.bottom)/2),
										taillewindowactu.right,taillewindowactu.bottom,true);							
							GetConsoleScreenBufferInfo(console, &ScreenBufferInfo);           				//Accéder à la taille de la console directement
							limfenx = ScreenBufferInfo.srWindow.Right + 1; limfeny = ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations quant à la taille de la console
						}	
						//Corriger la taille de la zone de texte (afin d'obtenir une barre de défilement constante à travers toutes les tailles de fenêtres)
						SetConsoleScreenBufferSize(console,ScreenBufferInfo.dwSize);
						//Noter où est le milieu
						milieufenx = round(limfenx/2); milieufeny = round(limfeny/2); limtxtx = limfenx; limtxty = limfeny - 1;		//En nombre de char
						//Cacher le curseur (ce qui clignote)
						CursorInfo.bVisible = false; CursorInfo.dwSize = 1; SetConsoleCursorInfo(console,&CursorInfo);
					}
				//Constructeurs
					//Constructeur par défaut
					fenetre() {tailleconsactu.X = 40; tailleconsactu.Y = 20;}		//Taille par défaut arbitraire; peut être changée avec la fonction dimdef()
			};

		

//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) Classes et fonctions générales

	//i) Classes-contenantes	----------------------------------------------------------------------
	
		//a) classe : StaticVect ; sauvegarde un array "semi-dynamique", où la mémoire utilisée est fixe, mais les fonctionnalités sont les mêmes que StringAsVect.
		template <class Type, int Taille>
			class StaticVect {
				//Valeurs membres	
				public:
					Type pt [Taille];   //Déclarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
					int taille = Taille; //Nombre d'objets de l'array
					int debut;  //Position actuelle de début
					int fin;    //Position actuelle de fin
					int longueur;       //Nombre d'objets entre le début et la fin
				//Constructeurs	:
					StaticVect<Type,Taille>() : debut(0), fin(0), longueur(0) {}  //Défaut 
					StaticVect<Type,Taille>(Type nxt) : debut(0), fin(1), longueur(0) {pt[0] = nxt;}  //Une seule valeur
					StaticVect<Type,Taille>(Type* ptarr, int nb) : debut(0), fin(nb), longueur(nb) {for(int pos=0;pos<nb;pos++) pt[pos] = ptarr[pos];}   //Array
					StaticVect<Type,Taille>(const StaticVect<Type,Taille>& nxt) : debut(0), fin(nxt.longueur), longueur(nxt.longueur) {for(int pos=0;pos<nxt.longueur;pos++) pt[pos] = nxt.pt[nxt.debut + pos];}    //POURRAIT ÊTRE MIEUX ÉCRIT???
				//Copy assignement :
					StaticVect<Type,Taille>& operator = (const StaticVect<Type,Taille>& nxt) {
						debut = 0; fin = nxt.longueur; longueur = nxt.longueur;
						for(int pos=0;pos<nxt.longueur;pos++) pt[pos] = nxt.pt[nxt.debut + pos];
						return(*this);			
					}	
		   		//Opérateur d'accès : []
				   Type& operator[] (int pos) {
				   		return(pt[debut + pos]);
				   }
				//Fonction d'accès : intervalle()
					StaticVect<Type,Taille> intervalle(int posdebut, int posfin) {
						if(posfin <= longueur) {
							StaticVect<Type,Taille> returnvect;
							returnvect.debut = 0; returnvect.longueur = posfin - posdebut; returnvect.fin = returnvect.longueur;
							int returnpos = 0; for(int pos = posdebut; pos<posfin; pos++) {returnvect.pt[returnpos++] = pt[pos+debut];}
							return(returnvect);				
						} else {std::wcout<<"intervalle() de "; std::wcout<<posdebut; std::wcout<<" à "; std::wcout<<posfin; std::wcout<<" dans \""; for(int pos=0; pos<fin; pos++) std::wcout<<pt[pos+debut]; std::wcout<<"\", dépassant donc la longueur"; abort();}
					}
				//Fonction de modification : ajout()
					bool ajout(Type nxt) {if(fin+1 <= taille) {pt[fin] = nxt; fin++; longueur++; return(true);} else return(false);}       //Fonction de retour pour communiquer la réussite ou non!				
					bool ajout(Type nxt, int pos) {			//Ajoute l'entrée à une position précise
						if(fin+1 <= taille) {
							for(int ptpos = fin; ptpos>pos; ptpos--) pt[ptpos] = pt[ptpos-1];
							pt[pos] = nxt; fin++; longueur++;
							return(true);
						} else return(false);
					}
					bool ajout(Type* nxt, int nb) {			//Ajoute un array à la suite du StaticVect
						if(fin+nb <= taille) {
							int nouvfin = fin + nb; int posnxt = 0;
							for(int pos=fin; pos<nouvfin; pos++) {pt[pos] = nxt[posnxt++];}
							fin+=nb; longueur+=nb; 
							return(true);
						} else return(false);
					}
				//Fonction de modification : remplacement()
					bool remplacement(Type nxt) {debut = 0; fin = 1; pt[0] = nxt; return(true);}  	
					bool remplacement(Type* nxt, int nb) {
						if(nb <= taille) {
							debut = 0; fin = nb; longueur = nb;
							for(int pos=0; pos<nb; pos++) pt[pos] = nxt[pos];	
							return(true);			
						} else return(false);
					}
					bool remplacement(StaticVect<Type,Taille>& nxt) {
						if(nxt.longueur <= taille) {
							debut = 0; fin = nxt.longueur; longueur = nxt.longueur;
							for(int pos=0; pos<longueur; pos++) pt[pos] = nxt[pos];		
							return(true);
						} else return(false);
					}
				//Fonction de modification : vide()
					void vide(void) {debut = 0; fin = 0; longueur = 0;}
				//Fonction de modification : suppression          //"Supprime" le nombre de positions en right-hand AU DÉBUT des valeurs déjà contenues
					void suppression (int nb) {
						if(nb > fin-debut) debut = fin; else debut+=nb; 
						longueur-=nb;
					}
				//Fonction de modification : supprposition       //Supprime l'entrée à la position indiquée
					void supprposition (int pos) {
						if(pos >= debut & pos < fin) {
							for(int ptpos = pos; ptpos < fin-1; ptpos++) {pt[ptpos] = pt[ptpos+1];}
							fin--; longueur--;
						}
					}
				//Fonction d'"ajout" : ajoutvide           //Sert à noter le passage à une entrée supérieure sans ajouter directement un élément (ex: dans StaticVect<TAILLE2,StaticVect<TAILLE1,TYPE>>)			
					void ajoutvide (void) {fin++; longueur++;}
				};		
			
	//ii) Fonctions de conversion	----------------------------------------------------------------------
		
		//a) Fonction : majuscule ; retourne le char, mais en majuscule
		char majuscule(char chr) {
			if(chr=='a') return('A'); else if(chr=='à') return('À'); else if(chr=='â') return('Â'); else if(chr=='ä') return('Ä'); else{
			} if(chr=='b') return('B'); else if(chr=='c') return('C'); else if(chr=='ç') return('Ç'); else if(chr=='d') return('D'); else{
			} if(chr=='e') return('E'); else if(chr=='é') return('É'); else if(chr=='è') return('È'); else if(chr=='ê') return('Ê'); else if(chr=='ë') return('Ê'); else{
			} if(chr=='f') return('F'); else if(chr=='g') return('G'); else if(chr=='h') return('H'); else if(chr=='i') return('I'); else if(chr=='ì') return('Ì'); else if(chr=='î') return('Î'); else if(chr=='ï') return('Ï'); else {
			} if(chr=='j') return('J'); else if(chr=='k') return('K'); else if(chr=='l') return('L'); else if(chr=='m') return('M'); else{
			} if(chr=='n') return('N'); else if(chr=='o') return('O'); else if(chr=='ò') return('Ò'); else if(chr=='ô') return('Ô'); else if(chr=='ö') return('Ö'); else{	
			} if(chr=='p') return('P'); else if(chr=='q') return('Q'); else if(chr=='r') return('R'); else if(chr=='s') return('S'); else{
			} if(chr=='t') return('T'); else if(chr=='u') return('U'); else if(chr=='ù') return('Ù'); else if(chr=='û') return('Û'); else if(chr=='ü') return('Ü'); else{		
			} if(chr=='v') return('V'); else if(chr=='w') return('W'); else if(chr=='x') return('X'); else if(chr=='y') return('Y'); else{
			} if(chr=='z') return('Z'); else return(chr);
		}
				
		//b) Fonction : strintervalle ; retourne un string
		string strintervalle(string str, int deb, int fin) {		//Le début et la fin sont INCLUSIVES!!!
			string nwstr;
			for(int pos=deb;pos<=fin;pos++) nwstr+=str[pos];          
			return(nwstr);
		}			
				
		//c) Fonction : CodeSpecialLong ; retourne la longueur d'un code spécial (les deux '§' étant compris)
		int CodeSpecialLongueur(string str){
			int longueur = 1;               //Initier l'objet à retourner
			bool fini = false; int pos = 0;
			int strnb = str.length();
			while(!fini&&pos<strnb) {
				longueur++; pos++;
				if(str[pos]=='§') fini = true;
			}              
			return(longueur);		
		}
		int CodeSpecialLongueurInv(string str){								//Part de la fin du string (pour les msn qui reculent)
			int longueur = 1;               //Initier l'objet à retourner
			bool fini = false; int pos = str.length()-1;
			while(!fini&&pos>0) {
				longueur++; pos--;
				if(str[pos]=='§') fini = true;
			}              
			return(longueur);		
		}
	
		//d) Fonction : CodeSpecialExtract ; extrait une valeur numérique d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
		double CodeSpecialExtractDouble(string str, int longueur){
			string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
			for(int pos=2; pos<longueur-1; pos++) nbonly += str[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)	
			return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
		}		
		int CodeSpecialExtractInt(string str, int longueur){
			string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
			for(int pos=2; pos<longueur-1; pos++) nbonly += str[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)	
			return(stoi(nbonly));           //La fonction stoi convertit les strings en int (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
		}					
		
		//e) Fonction : out ; affiche le caractère dans la console			//Change des char en unicode, genre, un peu?
		void out(char lettre){
			if(lettre=='À') std::wcout << L"\u00C0";
			else if(lettre=='à') std::wcout << L"\u00E0";
			else if(lettre=='Ç') std::wcout << L"\u00C7";		
			else if(lettre=='ç') std::wcout << L"\u00E7";
			else if(lettre=='É') std::wcout << L"\u00C9";		
			else if(lettre=='é') std::wcout << L"\u00E9";
			else if(lettre=='È') std::wcout << L"\u00C8";
			else if(lettre=='è') std::wcout << L"\u00E8";
			else if(lettre=='Ê') std::wcout << L"\u00CA";
			else if(lettre=='ê') std::wcout << L"\u00EA";
			else if(lettre=='Î') std::wcout << L"\u00CE";
			else if(lettre=='î') std::wcout << L"\u00EE";
			else if(lettre=='Ï') std::wcout << L"\u00CF";
			else if(lettre=='ï') std::wcout << L"\u00EF";						
			else if(lettre=='Ô') std::wcout << L"\u00D4";
			else if(lettre=='ô') std::wcout << L"\u00F4";
			else if(lettre=='Ù') std::wcout << L"\u00D9";
			else if(lettre=='ù') std::wcout << L"\u00F9";	
			else if(lettre=='Û') std::wcout << L"\u00DB";
			else if(lettre=='û') std::wcout << L"\u00FB";	
			else {std::wcout << lettre;}
		}
		void out(string phrase){
			for(int pos=0; pos<phrase.length(); pos++){
				out(phrase[pos]);
			}
		}
		template<int Taille>
		void out(StaticVect<char,Taille> phrase){
			for(int pos=0; pos<phrase.longueur; pos++){
				out(phrase[pos]);
			}
		}
		void out(int chiffre) {out(to_string(chiffre));}
		void out(unsigned chiffre) {out(to_string(chiffre));}
		void out(double chiffre) {out(to_string(chiffre));}
								
		//f) Fonction : strtobool ; interprète un string pour renvoyer un booléen (similaire à stoi() ou stod() )
		bool strtobool(string str) {
			if(str[0]=='0') {return(false);
			} else if(str[0]=='f'&&str[1]=='a'&&str[2]=='l'&&str[3]=='s'&&str[4]=='e') {return(false);
			} else if(str[0]=='F'&&str[1]=='A'&&str[2]=='L'&&str[3]=='S'&&str[4]=='e') {return(false);
			} else if(str[0]=='1') {return(true);
			} else if(str[0]=='t'&&str[1]=='r'&&str[2]=='u'&&str[3]=='e') {return(true);
			} else if(str[0]=='T'&&str[1]=='R'&&str[2]=='U'&&str[3]=='E') {return(true);
			} else {out("\n\nTentative d'évaluer \""); for(int pos = 0; pos<str.length(); pos++) {out(str[pos]);} out("\" comme un booléen."); abort();}
		}									
								
		//g) Fonction : ColNameFind ; trouve une (la première rencontrée) position d'indexation dans un StaticVect<string,Taille> qui correspond exactement à un string
		template<int Taille>
		int ColNameFind(string& str, StaticVect<string,Taille>& col) {
			int stringlength = str.length();
			for(int pos=0; pos<col.longueur; pos++) {
				if(stringlength==col[pos].length()) {
					int strpos = 0;
					while(strpos<stringlength) {if(str[strpos]!=col[pos][strpos]) break; strpos++;}
					if(strpos==stringlength) return(pos);
				}
			}
			//Failsafe: Si aucune itération de "str" n'a été trouvée
			out("Aucune itération de \""); out(str); out("\" n'a été trouvée dans {");
			for(int poscol = 0; poscol<col.longueur; poscol++) {out("\""); out(col[poscol]); out("\""); out(" ; ");} out("}"); abort();
		}
		template<int Taille>
		int ColNameFind(const string& str, StaticVect<string,Taille>& col) {
			int stringlength = str.length();
			for(int pos=0; pos<col.longueur; pos++) {
				if(stringlength==col[pos].length()) {
					int strpos = 0;
					while(strpos<stringlength) {if(str[strpos]!=col[pos][strpos]) break; strpos++;}
					if(strpos==stringlength) return(pos);
				}
			}
			//Failsafe: Si aucune itération de "str" n'a été trouvée
			out("Aucune itération de \""); out(str); out("\" n'a été trouvée dans {");
			for(int poscol = 0; poscol<col.longueur; poscol++) {out("\""); out(col[poscol]); out("\""); out(" ; ");} out("}"); abort();
		}
										
		//h) Fonction : max ; retourne la valeur maximale entre deux valeurs
		int max(int vala, int valb) {
			if(vala>valb) return(vala); else return(valb);
		}

		//i) Fonction : min ; retourne la valeur minimale entre deux valeurs
		int min(int vala, int valb) {
			if(vala<valb) return(vala); else return(valb);
		}
			
		//j) Fonction : floor ; retourne la valeur arrondie à l'entier inférieur
		//int floor(double val){
		//	if(val==round(val)) return(round(val)); else return(round(val)-1);
		//}

		//j) Fonction : ceiling ; retourne la valeur arrondie à l'entier supérieur
		int ceiling(double val){
			if(val==floor(val)) return(val); else return(floor(val)+1);
		}
								
	//iii) Fonctions et classe de manipulation du temps	----------------------------------------------------------------------
	
		//a) Classe : horloge ; permet de stocker le temps depuis le début du programme
		class horloge {
			private:
				unsigned debutt;
			public:
				unsigned currentt;	 
			//Constructeur
			horloge() {debutt = std::chrono::duration_cast< std::chrono::milliseconds >(
		    	std::chrono::system_clock::now().time_since_epoch()
				).count(); currentt = 0;}
			//Fonction de modification : reglerheure ; ré-initie currentt
			void reglerheure() {currentt = std::chrono::duration_cast< std::chrono::milliseconds >(
		    	std::chrono::system_clock::now().time_since_epoch()
				).count() - debutt;}
			//Fonction d'accès
			int getdebutt() {return(debutt);}	
			//Fonctions de statis
			void stop(int val);
			void egrener(string str, int delay);
		};
	
		//b) Fonction : stop ; arrête manuellement l'exécution d'un programme. À utiliser seulement dans un menu!
		void horloge::stop(int val) {
			int targett = currentt + val;
			while(TRUE) {this->reglerheure(); if(currentt>targett) return;}
		}
	
		//c) Fonction : egrener ; fait apparaître le texte manuellement, comme s'il était dans un canal. À utiliser seulement dans un menu!
		void horloge::egrener(string str, int delay) {
			for(int pos=0; pos<str.length(); pos++) {out(str[pos]); stop(delay);}
		}

	//iv) Classes et fonctions de randomisation	----------------------------------------------------------------------		
	
		//a) Fonction : randseed ; initie le générateur de nombre aléatoire rand() avec le "time since epoch" (1er janvier 1970), en millisecondes
		void randseed(horloge clock) {
			srand(abs(clock.getdebutt() -	1583418000));		//La soustraction ici est simplement le temps à l'heure où j'écris cette ligne; pour être sûre que ça bug pas si le nombre est trop grand
		}
	  
		//b) Fonction : randunif ; retourne un integer entre [min, max] (les valeurs sont comprises; "inclusivement")
		int randunif(int min, int max) {
			return(rand() % (max+1) + min);
		}

		//c) Classe : normdist ; construit et conserve une distribution de probabilités approximée, afin d'en tirer des nombres aléatoires à l'aide seulement de la fonction rand()
			class normdist{
				//Membres
				private:
					static const int range = 1000;
					static const int originmean = 500;
					static const int originsd = 165;
					static const unsigned resolution = 10000;
					unsigned prob[range];
					unsigned sumprob;
				//Fonctions
				public:
					//Constructeur
					normdist() {		//Par défaut; permet de construire la distribution de probabilités
						//Donner une probabilité à chaque valeur de 'x' (les 'x' sont les positions de l'array "prob")
							//Je me base sur la définition de la distribution normale pour faire ça, qui va un peu comme suit:
							// f(x) = 1/(sd*(2*pi)^(1/2)) * e^((-1/2)*((x-mean)/sd)^2)
							//Je multiplie les probabilités données ici par la résolution, pour n'avoir que des integer de taille sensible
						double yconst = 1/(originsd*pow(2*M_PI,1/2));		//M_PI, c'est la valeur de pi
						sumprob = 0;
						for(int x=0; x<range; x++){
							prob[x] = round(yconst * exp(-pow(x-originmean,2)/pow(2*originsd,2)) * resolution);
							sumprob += prob[x];				//J'en profite pour aller chercher le total exact des probabilités, qui devrait tendre vers "résolution"
						}
					}						
					//Fonction d'accès : randnormapprox ; retourne un integer aléatoire respectant une distribution normale de (mean,sd)
					int randnormapprox(int mean, int sd){						
						int randprob = randunif(1,sumprob);
						int sumprobnow = 0; int x = -1;
						while(sumprobnow<randprob) sumprobnow += prob[++x];
						//Maintenant, on a obtenu un nombre aléatoire 'x' grâce à une distribution normale de mean = originmean et sd = originsd						
						return(round((x-originmean)*sd/originsd + mean));
					}
			};
		
//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Classes-contenantes spécialisées (canaux et autres)

	//i) Classe de sauvegarde des informations	----------------------------------------------------------------------		

		//a) classe : bibliotheque ; permet de stocker tous les status (int) modifiables
		class bibliotheque {
			//Valeurs membres
			public:
				static const int nbrayons = 5;		//static: un seul membre partagé par tous les objets de cette classe; const: ce nombre ne chagera pas (défini à la compilation)
				static const int nblivres = 30;
				StaticVect<StaticVect<int,nblivres>,nbrayons> rayon;	//c'est le répertoire de valeurs qui va être utilisé
				StaticVect<string,nbrayons> nomrayon; StaticVect<StaticVect<string,nblivres>,nbrayons> nomlivre;     //Liste des noms des rayons et des livres
				static const int nbrayonsfixes = 3;		//Nombre de rayons dont le nom a déjà été fixé (rayons obligatoires)
				static const int posmenu = 0;
				static const int poscouleur = 1;
				static const int posgenre = 2;
			//Constructeur par défaut
			bibliotheque() {
				//Mettre tous les livres à 0 par défaut
				for(int countray=0; countray<nbrayons; countray++) for(int countli=0; countli<nblivres; countli++) rayon[countray][countli] = 0;
				//Ajouter le rayon des menus			//Contient le status actuel des menus					
				rayon.ajoutvide();	
				nomrayon.ajout("menu");
					rayon[posmenu].ajoutvide();	nomlivre[posmenu].ajout("");
				//Ajouter le rayon des couleurs			//Contient les différentes couleurs de la console
				rayon.ajoutvide();	
				nomrayon.ajout("couleur");
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("actutxt"); this->modif("couleur","actutxt",7);			//Blanc foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("actubg"); this->modif("couleur","actubg",0);				//Noir foncé			
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("cantxt"); this->modif("couleur","cantxt",7);				//Blanc foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("canbg"); this->modif("couleur","canbg",0);				//Noir foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("msntxt"); this->modif("couleur","msntxt",15);			//Blanc clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("msnbg"); this->modif("couleur","msnbg",0);				//Noir foncé	
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commtxt"); this->modif("couleur","commtxt",8);			//Gris clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbg"); this->modif("couleur","commbg",0);				//Noir foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbontxt"); this->modif("couleur","commbontxt",7);		//Blanc foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbonbg"); this->modif("couleur","commbonbg",0);		//Noir foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbusytxt"); this->modif("couleur","commbusytxt",4);	//Rouge foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbusybg"); this->modif("couleur","commbusybg",0);		//Noir foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commmauvtxt"); this->modif("couleur","commmauvtxt",12);	//Rouge clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commmauvbg"); this->modif("couleur","commmauvbg",0);		//Noir foncé												
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commpostxt"); this->modif("couleur","commpostxt",15);	//Blanc clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commposbg"); this->modif("couleur","commposbg",0);		//Noir foncé	
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menutxt"); this->modif("couleur","menutxt",15);			//Blanc clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menubg"); this->modif("couleur","menubg",0);				//Noir foncé						
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menuselecttxt"); this->modif("couleur","menuselecttxt",0);	//Noir foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menuselectbg"); this->modif("couleur","menuselectbg",15);	//Blanc clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menuarrplantxt"); this->modif("couleur","menuarrplantxt",7);	//Blanc foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menuarrplanbg"); this->modif("couleur","menuarrplanbg",0);	//Noir foncé
				//Ajouter le rayon des genres			//Contient le genre de chaque personnage: 0 = féminin, 1 = non binaire, 2 = masculin
				rayon.ajoutvide();
				nomrayon.ajout("genre");
					rayon[posgenre].ajoutvide(); nomlivre[posgenre].ajout("tu"); this->modif("genre","tu",0);		//Lu joueuxe, cellui qui est appelé.e "tu" tout le long!			
			};
			//Fonction d'accès : acces ; retourner la valeur à certaines positions
			int acces(int posrayon, int poslivre) {return(rayon[posrayon][poslivre]);}
			int acces(int posrayon, string livrestr) {int poslivre = ColNameFind(livrestr,nomlivre[posrayon]); return(rayon[posrayon][poslivre]);}	//Pour les rayons fixes
			//Fonction de modification : modif ; modifie la valeur à certaines positions
			void modif(int posrayon, int poslivre, int value) {rayon[posrayon][poslivre] = value;}
			void modif(int posrayon, string livrestr, int value) {int poslivre = ColNameFind(livrestr,nomlivre[posrayon]); rayon[posrayon][poslivre] = value;}	//Pour les rayons fixes
			void modif(string rayonstr, string livrestr, int value) {
				int posrayon = ColNameFind(rayonstr,nomrayon); 
				int poslivre = ColNameFind(livrestr,nomlivre[posrayon]);
				rayon[posrayon][poslivre] = value;
			}
		};

		//b) classe : memoire ; permet de sauvegarder la "mémoire" de la console, c'est-à-dire tous le texte s'y étant déjà inscrit
			class memoire{
				//Membres
				public: 
					static const int TailleBase = 500;       //Nombre de ligne de base des objets 
					int nbcol;                  //Nombre de colonnes (fixe)
					int nbligne;                //Nombre de lignes totales de stockage (pour éviter de ré-allouer la mémoire tout le temps)
					int frontline;              //Ligne à laquelle est rendue l'écriture
					char** souvenir;            //L'objet contient, en façades, des pointeurs pointant à d'autres pointeurs
				//Constructeur par défaut
				memoire() {
					nbcol = 1;
					frontline = 0;                         //Ce qui suit semble être la seule manière de créer des arrays dynamiques
					nbligne = TailleBase;            
					//Tester si on a assez de mémoire dynamique       
						try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
					souvenir = new char* [nbcol];   //Créer un premier array contenant des pointers
					//Créer les lignes pour chaque colonne, et les remplir d'espace
					for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}
				}
				//Constructeur pour avoir le bon nombre de colonnes
				memoire(int ncol) {
					nbcol = ncol;
					frontline = 0;                         //Ce qui suit semble être la seule manière de créer des arrays dynamiques
					nbligne = TailleBase;            
					//Tester si on a assez de mémoire dynamique       
						try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
					souvenir = new char* [nbcol];   //Créer un premier array contenant des pointers
					//Créer les lignes pour chaque colonne, et les remplir d'espace
					for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}
				}			
				//Destructeur
				~memoire() {
					for(int col=0; col<nbcol ; col++) delete[] souvenir[col] ; delete[] souvenir;   //Bien déconstruire tout proprement
				}
				//Fonction d'accès : retourner certaines positions
				char acces (int posx, int posy) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
					return(souvenir[posx][posy]);
				}
				int accesfrontline() {return(frontline);}
				//Fonction de modification : met quelque chose dans la position
				void modif (int posx, int posy, char caract) { 
					souvenir[posx][posy] = caract;
				}				
				//Fonction de modification : setsize ; défaire la mémoire construite par défaut pour en fabriquer une de bonnes dimensions
				void setsize(int ncol) {
					for(int col=0; col<nbcol ; col++) delete[] souvenir[col] ; delete[] souvenir;   //Bien déconstruire tout proprement ce qui était là avant d'aller plus loin					
					nbcol = ncol;					//Réinitialiser les paramètres
					frontline = 0;                         
					nbligne = TailleBase;            
					//Tester si on a assez de mémoire dynamique       
						try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
					souvenir = new char* [nbcol];   //Créer un premier array contenant des pointers
					//Créer les lignes pour chaque colonne, et les remplir d'espace
					for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}					
				}
				//Fonction de modification : newline ; ajouter une ligne à la suite de la position spécifiée
				void newline (int pos) {
					if(frontline+1<nbligne) {
						int emptypos = pos + 1;   //Calculer la position qui sera vide
						//Déplacer de 1 tout ce qui vient ensuite, en commençant par la fin
						for(int lin = frontline; lin > pos; lin--) for(int col = 0; col < nbcol; col++) souvenir[col][lin+1]=souvenir[col][lin]; 
						for(int col = 0; col < nbcol; col++) souvenir[col][emptypos] = ' ';   //Remplir la position vide d'espace
						frontline++;   //Noter qu'on ajoute une ligne
					} else {
						int emptypos = pos + 1;   //Calculer la position qui sera vide
							//Tester si on a assez de mémoire dynamique       				
							try{char** nwsouv = new char* [nbcol] ; for(int col = 0; col<nbcol ; col++) {nwsouv [col] = new char [nbligne+TailleBase];}}  //Tenter d'allouer l'espace
						  	catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)
						char** nwsouv = new char* [nbcol] ; for(int col = 0; col<nbcol ; col++) {nwsouv [col] = new char [nbligne+TailleBase];}  //Initialiser le nouveau bloc de mémoire à l'aide d'un pointeur temporaire
						int oldpos = 0;  //Déclarer un compteur pour les vieilles positions				
						for(int nwpos=0; nwpos < frontline; nwpos++) {  //Remplir, en laissant une position vide
							if(nwpos==emptypos) {for(int xpos = 0; xpos<nbcol ; xpos++) nwsouv[xpos][nwpos] = ' '; continue;}  //Cette ligne remplit d'espace, puis saute les autres instructions jusqu'à la fin de la boucle 
							for(int xpos = 0; xpos<nbcol ; xpos++) {nwsouv[xpos][nwpos] = souvenir[xpos][oldpos];}
							oldpos++;
						}
						frontline++;   //Noter qu'on ajoute une ligne
						for(int col=0; col<nbcol ; col++) delete[] souvenir[col] ; delete[] souvenir;  //Supprimer le contenu du viel array
						souvenir = nwsouv;  //Copier seulement le pointeur, sans faire une copie du contenue
						for(int col=0; col<nbcol ; col++) nwsouv[col] = nullptr; nwsouv = nullptr;    //Rendre nuls les pointeurs temporaires
					}
				}
			};
	
		//c) classe : msnmemoire ; permet de sauvegarder les positions occupées par les msn
			class msnmemoire{
				//Membres
				public: 
					int nbcol;                  //Nombre de colonnes (fixe)
					int nbligne;                //Nombre de lignes (fixe)
					bool** caselibre;           //L'objet contient, en façades, des pointeurs pointant à d'autres pointeurs		//Pour savoir quelle case est occupée
					bool* lignelibre;			//Pour savoir quelle ligne est occupée
				//Constructeur par défaut
				msnmemoire() {
					nbcol = 1; nbligne = 1;
					//Tester si on a assez de mémoire dynamique       
						try{caselibre = new bool* [nbcol+1]; for(int col=0; col<nbcol+1 ; col++) {caselibre[col] = new bool [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
					//Créer l'objet caselibre 
						caselibre = new bool* [nbcol];   //Créer un premier array contenant des pointers
						//Créer les lignes pour chaque colonne, et les remplir de "TRUE"
						for(int col=0; col<nbcol; col++) {caselibre[col] = new bool [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) caselibre[col][ligne] = true;}
					//Créer l'objet lignelibre, et le remplir de "TRUE"
						lignelibre = new bool [nbligne];  for(int ligne=0; ligne<nbligne; ligne++) lignelibre[ligne] = true;	
				}
				//Constructeur pour avoir le bon nombre de colonnes et de lignes
				msnmemoire(int ncol, int nligne) {
					nbcol = ncol; nbligne = nligne;            
					//Tester si on a assez de mémoire dynamique       
						try{caselibre = new bool* [nbcol+1]; for(int col=0; col<nbcol+1 ; col++) {caselibre[col] = new bool [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
					//Créer l'objet caselibre 
						caselibre = new bool* [nbcol];   //Créer un premier array contenant des pointers
						//Créer les lignes pour chaque colonne, et les remplir de "TRUE"
						for(int col=0; col<nbcol; col++) {caselibre[col] = new bool [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) caselibre[col][ligne] = true;}
					//Créer l'objet lignelibre, et le remplir de "TRUE"
						lignelibre = new bool [nbligne];  for(int ligne=0; ligne<nbligne; ligne++) lignelibre[ligne] = true;	
				}			
				//Destructeur
				~msnmemoire() {
					for(int col=0; col<nbcol ; col++) delete[] caselibre[col] ; delete[] caselibre; delete[] lignelibre;  //Bien déconstruire tout proprement
				}
				//Fonction de modification : setsize ; défaire la mémoire construite par défaut pour en fabriquer une de bonnes dimensions
				void setsize(int ncol, int nligne) {
					for(int col=0; col<nbcol ; col++) delete[] caselibre[col] ; delete[] caselibre; delete[] lignelibre;  //Bien déconstruire tout proprement avant d'aller plus loin					
					nbcol = ncol; nbligne = nligne;            	//Mettre les bonnes valeurs aux paramètres
					//Tester si on a assez de mémoire dynamique       
						try{caselibre = new bool* [nbcol+1]; for(int col=0; col<nbcol+1 ; col++) {caselibre[col] = new bool [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
					//Créer l'objet caselibre 
						caselibre = new bool* [nbcol];   //Créer un premier array contenant des pointers
						//Créer les lignes pour chaque colonne, et les remplir de "TRUE"
						for(int col=0; col<nbcol; col++) {caselibre[col] = new bool [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) caselibre[col][ligne] = true;}
					//Créer l'objet lignelibre, et le remplir de "TRUE"
						lignelibre = new bool [nbligne];  for(int ligne=0; ligne<nbligne; ligne++) lignelibre[ligne] = true;					
				}
				//Fonction de modification : met quelque chose dans la position
				void modifcase (int posx, int posy, bool val) { 
					caselibre[posx][posy] = val;
				}
				void modifligne (int posy, bool val) { 
					lignelibre[posy] = val;
				}
				//Fonctions d'accès : retourner certaines positions
				bool accescase (int posx, int posy) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
					return(caselibre[posx][posy]);
				}
				bool accesligne (int posy) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
					return(lignelibre[posy]);
				}
			};
	
	//ii) Classes de sauvegarde des expressions mathématiques et logiques	----------------------------------------------------------------------		
	
		//a) classe : inteval ; contient l'expression à évaluer (la plus simple) ; constructeur transforme les noms de "livre" en position d'indexation
		class inteval {
			//Valeurs membres
			public:
				int rayonpos;   		//Position d'indexation de la "famille" de l'argument comparé à gauche					
				int livrepos;			//Position d'indexation de l'argument comparé à gauche, à l'intérieur de sa "famille"
				int boolval; int intval;
				int constbool; int constint;      //TRUE si les valeurs sont booléennes ou int, à la place d'évaluées.
			//Constructeur
			inteval ()  : constbool(0), constint(0) {}; //Constructeur par défaut : vide. 
			//Fonction de modification : clean() ; permet de remettre l'objet à l'état initial, dans le but de le "set()" de nouveau
			void clean(void) {
				rayonpos = -1; livrepos = -1;
				boolval = 0; intval = 0;
				constbool = 0; constint = 0;
			}
			//Fonction de modification : set() ; permet de construire l'objet avec une expression
			void set(string str, bibliotheque& biblio) {
				int strnb = str.length();
				string rayon, livre;    //Initier un string, dans lequel seront insérés seulement les noms des rayons/livres
				int strpos, pos; strpos = 0; pos = 0; while(str[pos]!='¶'&&pos<strnb) rayon += str[pos++];
				//Évaluer si le string contient des noms ou une valeur														//CHANGER CETE LIGNE??????
				if(pos==strnb) {   	
					if(rayon[0]=='F'||rayon[0]=='f'||rayon[0]=='T'||rayon[0]=='t') {constbool = true; boolval = strtobool(rayon);} else {constint = true; intval = stoi(rayon);}   //EST-CE QUE CETTE LIGNE A DU SENS?????
				} else {
					//Transformer le nom du rayon en position d'indexation							
					rayonpos = ColNameFind(rayon,biblio.nomrayon);				
					//Recueillir le nom du livre + le transformer en position d'indexation	
					strpos = 0; pos++; while(pos<strnb) livre += str[pos++];
					livrepos = ColNameFind(livre,biblio.nomlivre[rayonpos]);
				}
			}
			//Fonction d'accès : eval()	
			int eval(bibliotheque& biblio) {if(constbool) return(boolval); else if(constint) return(intval); else return(biblio.acces(rayonpos,livrepos));}					
		};	
	
		//b) classe : intoper ; contient les opérations d'expressions booléennes évaluables
		class intoper {
			//Valeurs membres
			public:
				char operateur;      	//Opérateur
				intoper* LHcompos;
				intoper* RHcompos;
				inteval* LHsimple;
				inteval* RHsimple;
				bool Lcompos; bool Rcompos;				//TRUE si les valeurs sont composites
			//Constructeur
			intoper ()  : Lcompos(false), Rcompos(false) {}; //Constructeur par défaut : vide. 
			//Destructeur
			~intoper(){
				if(Lcompos) delete LHcompos; else delete LHsimple;
				if(Rcompos) delete RHcompos; else delete RHsimple;
			}		
			//Fonction de modification : clean() ; permet de remettre l'objet à l'état initial, dans le but de le "set()" de nouveau
			void clean(void) {
				if(Lcompos) delete LHcompos; else delete LHsimple;
				if(Rcompos) delete RHcompos; else delete RHsimple;
				Lcompos = false; Rcompos = false; operateur = ' ';
			}
			//Fonction de modification : set() ; permet de construire l'objet avec une expression
			void set(string str, bibliotheque& biblio){
				int strnb = str.length();
				string LH;									
				string RH;			
				int posPAR; bool trouvPAR = false; int nbPAR = 0;
				int posAD; bool trouvAD = false;
				int posMU; bool trouvMU = false; 
				int pos = 0;
				if(str[0]=='(') {
					while(!trouvPAR&&pos<strnb) {
						if(str[pos]=='(') nbPAR++;	//Gère les parenthèses imbriquées 
						if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
						pos++;
					} if(!trouvPAR) out("\n\nLa parenthèse n'est pas refermée dans: "+str); abort();
					if(trouvPAR&&pos==strnb) {str = strintervalle(str,1,strnb-2); trouvPAR = false; pos = 0;   //Supprimer la parenthèse et remettre les compteurs à 0, pour continuer		
					} else Lcompos = true;		//Noter l'expression à droite comme composite (car elle contient au minimum une parenthèse), et continuer à partir d'après la parenthèse
				} else { 							
				//Cas général : on cherche '+' ou '-', car '*' et '/' ont la priorité d'opération (s'appliquent d'abord à l'échelle locale)
					while(!trouvAD&&pos<strnb) {
						if(str[pos]=='+'||str[pos]=='-') {posAD = pos; trouvAD = true;}
						if(!trouvMU&&(str[pos]=='*'||str[pos]=='/')) {posMU = pos; trouvMU = true;}
						pos++;							
					}
					if(trouvAD) {
						operateur = str[posAD]; 					
						LH = strintervalle(str,0,posAD-1);					//Définir les limites de l'expression à gauche						
						RH = strintervalle(str,posAD+1,strnb-1);		//Définir les limites de l'expression à droite						
						if(trouvMU) Lcompos = true; //(car '*''/' ont la priorité d'opération sur '+''-')
						while(!Rcompos&&pos<strnb) {if(str[pos]=='+'||str[pos]=='-'||str[pos]=='*'||str[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite
					} else if(trouvMU) {
						operateur = str[posMU];  
						LH = strintervalle(str,0,posMU-1);					//Définir les limites de l'expression à gauche						
						RH = strintervalle(str,posMU+1,strnb-1);		//Définir les limites de l'expression à droite
						pos = posMU + 1; while(!Rcompos&&pos<strnb) {if(str[pos]=='*'||str[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite				
					} else {
						operateur = ' '; LH = str;   //Aucune opération, seulement une évaluation				
					}		
				}			
				//Assigner les valeurs aux membres
				if(Lcompos) {LHcompos = new intoper; LHcompos->set(LH,biblio); LHsimple = nullptr;} else {LHsimple = new inteval; LHsimple->set(LH,biblio); LHcompos = nullptr;}
				if(operateur!=' ') {if(Rcompos) {RHcompos = new intoper; RHcompos->set(RH,biblio); RHsimple = nullptr;} else {RHsimple = new inteval; RHsimple->set(RH,biblio); RHcompos = nullptr;}}
			}			
			//Fonction d'accès : eval()				
			int eval(bibliotheque& biblio) {
				if(Lcompos){
					if(Rcompos) {
						if(operateur=='+') {return(LHcompos->eval(biblio)+RHcompos->eval(biblio)); 
						} else if(operateur=='-') {return (LHcompos->eval(biblio)-RHcompos->eval(biblio));
						} else if(operateur=='*') {return(LHcompos->eval(biblio))*RHcompos->eval(biblio);
						} else if(operateur=='/') {return(LHcompos->eval(biblio)/RHcompos->eval(biblio));					
						} else if(operateur==' ') return(LHcompos->eval(biblio));					
					} else {
						if(operateur=='+') {return(LHcompos->eval(biblio)+RHsimple->eval(biblio)); 
						} else if(operateur=='-') {return (LHcompos->eval(biblio)-RHsimple->eval(biblio));
						} else if(operateur=='*') {return(LHcompos->eval(biblio)*RHsimple->eval(biblio));
						} else if(operateur=='/') {return(LHcompos->eval(biblio)/RHsimple->eval(biblio));
						} else if(operateur==' ') return(LHcompos->eval(biblio));
					}
				} else {
					if(Rcompos) {
						if(operateur=='+') {return(LHsimple->eval(biblio)+RHcompos->eval(biblio)); 
						} else if(operateur=='-') {return (LHsimple->eval(biblio)-RHcompos->eval(biblio));
						} else if(operateur=='*') {return(LHsimple->eval(biblio)*RHcompos->eval(biblio));
						} else if(operateur=='/') {return(LHsimple->eval(biblio)/RHcompos->eval(biblio));
						} else if(operateur==' ') return(LHsimple->eval(biblio));
					} else {
						if(operateur=='+') {return(LHsimple->eval(biblio)+RHsimple->eval(biblio)); 
						} else if(operateur=='-') {return (LHsimple->eval(biblio)-RHsimple->eval(biblio));
						} else if(operateur=='*') {return(LHsimple->eval(biblio)*RHsimple->eval(biblio));
						} else if(operateur=='/') {return(LHsimple->eval(biblio)/RHsimple->eval(biblio));
						} else if(operateur==' ') return(LHsimple->eval(biblio));
					}
				}
			}	
		};
	
		//c) classe : boolcompar ; contient les comparaisons d'expressions booléennes évaluables
		class boolcompar {
			//Valeurs membres
			public:
				char comparateur;      //Opérateur de comparaison
				intoper* LH;
				intoper* RH;
				bool constbool;			   //TRUE si l'argument à gauche doit être comparé à un booléen implicite
				bool boolval;		
			//Constructeur ;
			boolcompar () : constbool(false), boolval(0) {}; //Constructeur par défaut : vide. 
			//Destructeur
			~boolcompar(){
				delete LH;
				if(!constbool) delete RH;
			}		
			//Fonction de modification : clean() ; permet de remettre l'objet à l'état initial, dans le but de le "set()" de nouveau
			void clean(void) {
				delete LH;
				if(!constbool) delete RH;
				constbool = false; boolval = 0; comparateur = ' ';
			}
			//Fonction de modification : set() ; permet de construire l'objet avec une expression
			void set(string str, bibliotheque& biblio) {
				int strnb = str.length();
				if(strnb==0) {comparateur = ' ';}        //Cas spécial: retourne TRUE automatiquement
				//Recueillir l'opérateur			
				int posEX; bool trouvEX = false;    //point d'EXclamation
				int posPE; bool trouvPE = false; 	//plus PEtit
				int posGR; bool trouvGR = false;	//plus GRand
				int posEG; bool trouvEG = false;	//EGal
				int poscomparateur;
				int pos = 0;
				bool erreur = false;
				while(pos<strnb) {
						if(!trouvEX&&str[pos]=='!') {posEX = pos; trouvEX = true;}
						if(!trouvPE&&str[pos]=='<') {posPE = pos; trouvPE = true;}				
						if(!trouvGR&&str[pos]=='>') {posGR = pos; trouvGR = true;}				
						if(!trouvEG&&str[pos]=='=') {posEG = pos; trouvEG = true;}
						pos++;
				}
				if(trouvEX) {
					if(posEX==0) { //Cas spécial réchappé de la fonction précédente (si jamais elle en laisse passer un)
						constbool = true; boolval = false; comparateur = '=';	poscomparateur = strnb;  //ÉCRIT COMME CELA, ÇA NE MARCHE PAS, CAR ÇA N'EFFACE PAS LE '!' (À LA FIN, LH EST DÉFINI COMME [0, strnb])
						out("Le string \""); out(str); out("\" a été passé à la fonction boolcompar(), le compositeur '!' n'ayant pas été détecté par la fonction boolcompos. Cette partie du code n'est donc pas bonne.''"); abort();			
					} else {poscomparateur = posEX;	comparateur = '!'; if(trouvEG&&posEG!=posEX+1) erreur = true;}		//!=
				} else if(trouvPE) {poscomparateur = posPE; if(trouvEG&&posEG==posPE+1) {comparateur = '«';    			//<=
					} else if(!trouvEG) comparateur = '<'; else erreur = true;											//<	
				} else if(trouvGR) {poscomparateur = posGR;	if(trouvEG&&posGR==posGR+1) {comparateur = '»';   			//>=
					} else if(!trouvEG) comparateur = '>'; else erreur = true;											//>	
				} else if(trouvEG) {poscomparateur = posEG; if(str[posEG+1]=='=') comparateur = '='; else erreur = true;		//==	
				} else {constbool = true; boolval = true; comparateur = '=';	poscomparateur = strnb;} //Cas spécial : "comparaison implicite de la valeur à true"
				//Message d'erreur
				if(erreur) {out("\n\nL'opérateur n'est pas complet dans: "+str); abort();}
				//Créer les objets intoper
				LH = new intoper; LH->set(strintervalle(str,0,poscomparateur-1),biblio);
				if(!constbool){
					RH = new intoper;
					if(comparateur=='='||comparateur=='!'||comparateur=='«'||comparateur=='»') RH->set(strintervalle(str,poscomparateur+2,strnb-1),biblio); else RH->set(strintervalle(str,poscomparateur+1,strnb-1),biblio);	
				}			
			}
			//Fonction d'accès : eval
			bool eval(bibliotheque& biblio) {
				if(comparateur=='=') {
					if(constbool) return(LH->eval(biblio)==boolval); else return(LH->eval(biblio)==RH->eval(biblio));				// ==
				} else if(comparateur=='!') {
					if(constbool) return(LH->eval(biblio)!=boolval); else return(LH->eval(biblio)!=RH->eval(biblio));				// !=
				} else if(comparateur=='<') {
					if(constbool) return(LH->eval(biblio)<boolval); else return(LH->eval(biblio)<RH->eval(biblio));					// <
				} else if(comparateur=='«') {
					if(constbool) return(LH->eval(biblio)<=boolval); else return(LH->eval(biblio)<=RH->eval(biblio));				// <=
				} else if(comparateur=='<') {
				if(constbool) return(LH->eval(biblio)>boolval); else return(LH->eval(biblio)>RH->eval(biblio));						// >
				} else if(comparateur=='»') {
				if(constbool) return(LH->eval(biblio)>=boolval); else return(LH->eval(biblio)>=RH->eval(biblio));					// >=
				}
			}
		};
	
	
		//d) classe : boolcompos ; permet de stoker des expressions booléennes évaluables; (LH = "left hand", à gauche ; RH = "Right hand", à droite)
		class boolcompos {
			//Valeurs membres
			public:
				char compositeur;   //'&' ou '|' ou '!' (==false) ou ' ' (==true, sans comparaison)
				boolcompar* LHsimple; boolcompos* LHcompos; 
				boolcompar* RHsimple; boolcompos* RHcompos;
				bool Lcompos; bool Rcompos;	
			//Constructeur
			boolcompos () : Lcompos(false), Rcompos(false)	{}; //Constructeur par défaut : vide. 
			//Destructeur
			~boolcompos(){
				if(Lcompos) delete LHcompos; else delete LHsimple;
				if(Rcompos) delete RHcompos; else delete RHsimple;
			}
			//Fonction de modification : clean() ; permet de remettre l'objet à l'état initial, dans le but de le "set()" de nouveau
			void clean(void) {
				if(Lcompos) delete LHcompos; else delete LHsimple;
				if(Rcompos) delete RHcompos; else delete RHsimple;
				Lcompos = false; Rcompos = false; compositeur = ' ';
			}
			//Fonction de modification : set() ; permet de construire l'objet avec une expression		
			void set(string str, bibliotheque& biblio) {    //false : valeurs par défaut qui pourront changer à l'intérieur du constructeur
				int strnb = str.length();
				string LH;
				string RH;
				int posPAR; bool trouvPAR = false; int nbPAR = 0;
				int posOU; bool trouvOU = false; 
				int posET; bool trouvET = false;
				int posEX; bool trouvEX = false;
				int pos = 0;
				bool general = true;
				if(str[0]=='(') {  
				//Cas spécial: l'expression commence par une parenthèse (ex: "( 0==4 | 5<2 )"  ou  "(3>=5) & 3==7" ) 			
					while(!trouvPAR&&pos<strnb) {
						if(str[pos]=='(') nbPAR++;	//Gère les parenthèses imbriquées 
						if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
						pos++;
					} if(!trouvPAR) {out("\n\nLa parenthèse n'est pas refermée dans : \""); out(str); out("\""); abort();}
					if(trouvPAR&&pos==strnb) {str = strintervalle(str,1,strnb-2); trouvPAR = false; pos = 0;   //L'expression entière est entre parenthèses : Supprimer celles-ci et remettre les compteurs à 0, pour continuer au cas général
					} else Lcompos = true;		//Noter l'expression à gauche comme composite (car elle contient au minimum une parenthèse), et continuer au cas général à partir d'après la parenthèse
				} else if(str[0]=='!'&&str[1]=='(') {  
				//Cas spécial: l'expression commence par "le contraire" d'une parenthèse (ex: "!( 6<2 | 4==4 )"  ou  "!( 6>3 | 5<6) & 1==3" )			
					while(!trouvPAR&&pos<strnb) {
						if(str[pos]=='(') nbPAR++;	//Gère les parenthèses imbriquées 
						if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
						pos++;
					} if(!trouvPAR) {out("\n\nLa parenthèse n'est pas refermée dans : \""); out(str); out("\""); abort();}
					if(trouvPAR&&pos==strnb) {compositeur = '!'; LH = strintervalle(str,2,strnb-2); Lcompos = true; general = false;   //L'expression entière est "contraire" : passer le cas général		
					} else Lcompos = true;		//Noter l'expression à gauche comme composite (car elle contient un "contraire"), et continuer au cas général à partir d'après la parenthèse	
				}
				if(general) {
				//Cas général : on cherche '|', car '!' et '&' ont la priorité d'opération (s'appliquent d'abord à l'échelle locale)
					while(!trouvOU&&pos<strnb) {
						if(str[pos]=='|') {posOU = pos; trouvOU = true;}
						if(!trouvET&&str[pos]=='&') {posET = pos; trouvET = true;}
						if(!trouvEX&&str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=') {posEX = pos; trouvEX = true;}   //Si '!' agit bien comme compositeur, c'est-à-dire qu'il n'est pas accolé à un '='
						pos++;							
					}
					if(trouvOU) {
						compositeur = '|';
						LH = strintervalle(str,0,posOU-1);					//Définir les limites de l'expression à gauche	
						RH = strintervalle(str,posOU+1,strnb-1);		//Définir les limites de l'expression à droite						
						if(trouvEX||trouvET) Lcompos = true; //(car '!' et '&' ont la priorité d'opération sur '|')
						while(!Rcompos&&pos<strnb) {if(str[pos]=='|'||str[pos]=='&'||(str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=')) Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite
					} else if(trouvET) {  
						compositeur = '&';
						LH = strintervalle(str,0,posET-1);					//Définir les limites de l'expression à gauche		
						RH = strintervalle(str,posET+1,strnb-1);		//Définir les limites de l'expression à droite
						if(trouvEX) Lcompos = true;   //(car '!' a la priorité d'opération sur '&')
						pos = posET + 1; while(!Rcompos&&pos<strnb) {if(str[pos]=='&'||(str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=')) Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite				
					} else if(trouvEX) {
						if(posEX==0){						
							compositeur = '!';
							LH = strintervalle(str,1,strnb-1);					//Définir les limites de l'expression à gauche	
																				//Il n'y a pas d'expression à droite
						} else {out("\n\nLe symbole de contraire, '!', n'est pas en position [0] dans : \""); out(str); out("\", mais bien en position "); out(posEX); abort();}
					} else {
						compositeur = ' '; LH = str;   //Aucune comparaison, seulement une évaluation (et il n'y a pas d'expression à droite)						
					}		
				}			
				//Assigner les valeurs aux membres
				if(Lcompos) {LHcompos = new boolcompos; LHcompos->set(LH,biblio); LHsimple = nullptr;} else {LHsimple = new boolcompar; LHsimple->set(LH,biblio); LHcompos = nullptr;}
				if(compositeur!='!'&&compositeur!=' ') {if(Rcompos) {RHcompos = new boolcompos; RHcompos->set(RH,biblio); RHsimple = nullptr;} else {RHsimple = new boolcompar; RHsimple->set(RH,biblio); RHcompos = nullptr;}}		
			}
			//Fonction d'accès : eval
			bool eval(bibliotheque& biblio) {
				if(Lcompos){
					if(Rcompos) {
						if(compositeur=='&') {return(LHcompos->eval(biblio)&&RHcompos->eval(biblio)); 
						} else if(compositeur=='|') return (LHcompos->eval(biblio)||RHcompos->eval(biblio));
					} else {
						if(compositeur=='&') {return(LHcompos->eval(biblio)&&RHsimple->eval(biblio)); 
						} else if(compositeur=='|') {return (LHcompos->eval(biblio)||RHsimple->eval(biblio));
						} else if(compositeur=='!') {return(!LHcompos->eval(biblio));
						} else if(compositeur==' ') return(LHcompos->eval(biblio));
					}
				} else {
					if(Rcompos) {
						if(compositeur=='&') {return(LHsimple->eval(biblio)&&RHcompos->eval(biblio)); 
						} else if(compositeur=='|') return (LHsimple->eval(biblio)||RHcompos->eval(biblio));
					} else {
						if(compositeur=='&') {return(LHsimple->eval(biblio)&&RHsimple->eval(biblio)); 
						} else if(compositeur=='|') {return (LHsimple->eval(biblio)||RHsimple->eval(biblio));
						} else if(compositeur=='!') {return(!LHsimple->eval(biblio));
						} else if(compositeur==' ') return(LHsimple->eval(biblio));
					}
				}
			}		
		};
		
	//iii) Classes portant les textes qui s'affichent à l'écran (à court terme)	----------------------------------------------------------------------		
	
		//a) Classe : canal ; porte les textes composant le corps de la fiction, qui seront affichés comme fond de la console (vraiment à la base)
		class canal {
			//Membres
			public:
				unsigned nxtt;       						//Moment où la prochaine entrée sera traitée         
				unsigned pausedt;	    					//Différence entreposée entre nxtt et currentt, dans le cas où l'exécution est arrêtée (ex: faire apparaître un menu)				
				unsigned delay;								//Délai de base entre chaque entrée
				int posx, posy;								//Coordonnées de la dernière entrée dans la mémoire (la précédente)   
															//les positions de la consoles sont définies en décalant ces dernières
				int alinea;									//Nombre d'espace depuis la marge droite qui viendront s'ajouter à chaque nouvelle ligne					
				string txt;   								//Texte qui reste à lire  				
				bool actif;									//Compteur d'activité
				bool pause;									//Compteur qui s'active si le canal est arrêté par un processus indépendant (ex: un menu, ou le code spécial "freeze")
				bool frozen;								//Compteur pour différencier les pauses initiés par le code spécial "freeze" de celles initiées par un menu
				string nom;									//Nom que porte le canal
				string terminaison;							//Texte à placer juste après toute interruption ("override"), pour en quelque sorte terminer sur une belle note. Peut être changé à tout moment par le code spécial "§t§".
			//Constructeur						
			canal() : delay(150), posx(-1), posy(0), alinea(0), actif(false), nom("defaut"), terminaison(""), nxtt(0), pausedt(0), pause(false), frozen(false) {}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
		};

		//b) Classe : msn ; permet d'afficher des messages instantannés par-dessus le texte du "fond de la console", qui s'effacent d'eux-mêmes après un moment
		class msn {
			//Membres
			public:
				int posdebx, posdeby;							//Coordonnées de la première entrée dans la mémoire
				int posx, posy;         						//Coordonnées de la dernière entrée dans la mémoire
				unsigned nxtt;									//Moment où la prochaine entrée sera traitée
				unsigned pausedt;								//Différence entreposée entre nxtt et currentt, dans le cas où l'exécution est arrêtée (ex: faire apparaître un menu)
				unsigned delay;									//Délai de base entre chaque entrée
				string txt;										//Texte intégral de la messagerie
				int postxt;										//Position de la prochaine lettre qui va être lue / prochaine lettre qui va être effacée
				int nbysupp;									//Nombre de lignes (donc en 'y') ajoutées à la ligne de départ
				bool construire;								//Compteur qui dit s'il est temps de construire le message (ou d'effacer le texte)
				bool attente;									//Compteur qui s'active s'il n'y a pas de place pour ajouter une autre ligne
				bool pause;										//Compteur qui s'active si le msn est arrêté par un processus indépendant (ex: un menu, ou le code spécial "freeze")
				bool frozen;									//Compteur pour différencier les pauses initiés par le code spécial "freeze" de celles initiées par un menu
			//Constructeur
			msn() : posdebx(0), posdeby(0), posx(-1), posy(0), delay(80), postxt(0), nbysupp(0), construire(true), attente(false), nxtt(0), pausedt(0), pause(false), frozen(false) {}	//Constructeur par défaut
		};

	//iv) Classes gérant les entrées de la joueuse	----------------------------------------------------------------------		
	
		//a) classe : input ; sauvegarde les informations relatives à ce qu'écrit la joueuse
		class input {
			//Valeurs membres
			public:
				StaticVect<char,200> commande;          	//Phrase que contient le buffer        
				int inputpos;                   //Position d'indexation du prochain caractère    == StaticVect.fin? Non! Car ça peut bouger!
				bool accepted;                  //Flag concernant la dernière commande; utile pour l'affichage visuel
				bool reserve;					//Flag concernant la dernière commande; met le motif en réserve et bloque l'acceptation de nouvelles commandes
				int reservechap;				//Position du chapitre du motif à mettre en réserve
				int reservemotif;				//Position du motif à mettre en réserve (à l'intérieur de son chapitre)
				double vit;						//Multiplicateur de délais de défilement du texte, pour modifier la vitesse de lecture			
			//Constructeur par défaut
				input() : inputpos(0), accepted(false), reserve(false), vit(1) {}
		};							
							
		//b) classe : inputecho ; permet l'affichage résiduel des commandes (acceptées ou refusées)	
		class inputecho {
			//Valeurs membres
			public:
				StaticVect<char,200> commande;
				StaticVect<int,50> clignote;               //Conserve les instructions pour le clignotement : positif = affiche, négatif = pause.	
				int txtcol; int bgcol;                     //Conservent la couleur du clignotement actuel
				bool actif;							       //Compteur d'activité
				int nxtt;         						   //Moment où la prochaine entrée sera traitée         
				int pausedt;							   //Différence entreposée entre nxtt et currentt, dans le cas où l'exécution est arrêtée (ex: faire apparaître un menu)				
			//Constructeur par défaut
			inputecho() : txtcol(8), bgcol(0), actif(false), nxtt(0) {}			//Couleur par défaut: gris sombre sur noir
		};

	//v) Classes gérant les conditions d'apparition du texte	----------------------------------------------------------------------		
			
		//a) classe : commande ; permet le stockage de "mots de passe" pour les commandes
		class commande {
			//Valeurs membres
			public:
				static const int tailledifferentes = 5;
				static const int taillegroupes = 5;
				static const int taillesynonymes = 12;
				StaticVect<StaticVect<StaticVect<string,taillesynonymes>,taillegroupes>,tailledifferentes> inclus;		//Mots qui doivent être inclus dans l'expression
						//Niveau le plus extérieur: Différentes façon de dire la commande (ex: manger le concombre / se nourrir / mastiquer) ... Genre?
						//Niveau médian: Différents groupes de mots qui doivent être inclus (ex: manger / concombre)
						//Niveau le plus intérieur: Différents synonymes à l'intérieur du groupe de mots (ex: manger/absorber/grignoter/engouffrer/avaler)
				StaticVect<StaticVect<string,taillesynonymes>,tailledifferentes> exclus;						//Mots qui doivent être absents de l'expression
						//Niveau le plus extérieur: Différentes façon de dire la commande
						//Niveau le plus intérieur: Différents mots qui ne doivent pas se retrouver dans la commande
				StaticVect<string,taillegroupes> exact;										//Expressions qui doivent exactement être recopiées, sans faute (soit seule manière d'appeler, soit confirmation si ambiguité; voir UserInputInterpret())
			//Constructeur
			commande() {};	
		};		
				
		//b) classe : motifauto ; permet le stockage du texte et des conditions d'apparition (automatique)
		class motifauto {
			//Membres
			public:
				StaticVect<string,10> maille;						//Texte à lire
				int oddsofsound; int oddsofsilence;					//Chances que le motif soit lu à son intégration (par défaut: 100%) - sert à gérer la diversité de façon de dire une même information
				string ordre;								//Ordre dans lequel placer les mailles (segments du texte à lire); gros volume possible, mais tous les enchaînements ont une chance égale de se produire - sera interprété seulement lorsque le motif sera intégré
				bool ordreavecodds;									//Si TRUE, l'ordre va être défini par des enchaînements (ordrespecifique) associés à des probabilités (ordrespecifiqueodds): certains auront plus de chances de se produire
				static const int tailleordrespecifique = 12;
				StaticVect<StaticVect<int,8>,tailleordrespecifique> ordrespecifique;		//Ordre dans lequel placer les mailles - bricolé à la main, avec attention. Pour des enchaînements plus spécifiques, ou pour associer les enchaînements à des probabilités.
				StaticVect<intoper,tailleordrespecifique> ordrespecifiqueodds;	//Probabilités que chaque enchaînement soit joué; peut référer à des rayons de la bibliothèque, et donc évoluer dynamiquement avec le jeu!								
				boolcompos condition;								//Conditions à respecter pour l'ajout au canal sans UserInput 
				string codespeciauxdebut;
				string codespeciauxfin;
				bool override;										//TRUE si l'activation de motif vide instantannément le canal utilisé
				bool encours;										//Va changer dynamiquement, permet de ne pas dédoubler le même motif (± un temps d'attente obligatoire)
				int canal;											//Position du canal dans lequel écrire le texte
				bool msn;											//Si TRUE, le motif va activer un nouveau msn à la place de s'inscrire dans un canal
			//Constructeur
			motifauto() : override(false), encours(false), msn(false), oddsofsound(1), oddsofsilence(0), ordreavecodds(false) {};
		};
		
		//c) classe : motifmanu ; permet le stockage du texte et des conditions d'apparition (manuelle)
		class motifmanu {
			//Membres
			public:
				StaticVect<string,10> maille;						//Texte à lire
				int oddsofsound; int oddsofsilence;					//Chances que le motif soit lu à son intégration (par défaut: 100%) - sert à gérer la diversité de façon de dire une même information
				string ordre;								//Ordre dans lequel placer les mailles (segments du texte à lire); gros volume possible, mais tous les enchaînements ont une chance égale de se produire - sera interprété seulement lorsque le motif sera intégré
				bool ordreavecodds;									//Si TRUE, l'ordre va être défini par des enchaînements (ordrespecifique) associés à des probabilités (ordrespecifiqueodds): certains auront plus de chances de se produire
				static const int tailleordrespecifique = 12;
				StaticVect<StaticVect<int,8>,tailleordrespecifique> ordrespecifique;		//Ordre dans lequel placer les mailles - bricolé à la main, avec attention. Pour des enchaînements plus spécifiques, ou pour associer les enchaînements à des probabilités.
				StaticVect<intoper,tailleordrespecifique> ordrespecifiqueodds;	//Probabilités que chaque enchaînement soit joué; peut référer à des rayons de la bibliothèque, et donc évoluer dynamiquement avec le jeu!				
				boolcompos condition;								//Conditions à respecter pour l'ajout au canal avec UserInput				
				string codespeciauxdebut;
				string codespeciauxfin;
				bool override;										//TRUE si l'activation de motif vide instantannément le canal utilisé
				int canal;											//Position du canal dans lequel écrire le texte
				bool msn;											//Si TRUE, le motif va activer un nouveau msn à la place de s'inscrire dans un canal			
				commande commandes;                					//Mots à rechercher pour l'ajout au canal à partir du UserInput			
				bool reserve;                                       //TRUE si le UserInput devient bloqué après que ce motif ait été appelé (le motif est stocké en réserve, jusqu'à son activation)
				string titre;										//Sert à identifier le motif + à savoir quel motif est appelé en cas d'ambiguité de la commande
			//Constructeur
			motifmanu() : reserve(false), override(false), msn(false), oddsofsound(1), oddsofsilence(0), ordreavecodds(false) {};	
		};
		
		//d) classe : ouvrage ; permet de stocker toutes les textes + commandes selon des catégories (ex: chapitres), pour faciliter la recherche
		class ouvrage {
			//Membres
			public:
				static const int taille = 2;												//Nombre de "chapitre" actuellement disponibles
				static const int taillechapitre = 40;
				StaticVect<StaticVect<motifmanu,taillechapitre>,taille> filmanu;		//Groupes de textes + commandes ("chapitres") pour activation manuelle
				StaticVect<StaticVect<motifauto,taillechapitre>,taille> filauto;		//Groupes de textes + commandes ("chapitres") pour activation automatique
				StaticVect<boolcompos,taille> cadenas;										//Conditions d'activation des "chapitres"
		};

		//e) classe : menu ; permet de naviguer, faire des choix et mettre le jeux en pause
		class menu{
			//Membres
			public:
				int largeurbouton;
				int hauteurbouton;
				int espacebouton;
				static const int nombrebouton = 5;
				int selectdelay;				//Délai total de l'animation de sélection ([HAUT] ou [BAS]), en millisecondes
				int enterdelay;				//Délai total de l'animation de confirmation ([ENTER] ou [ESCAPE]), en millisecondes
				StaticVect<string,nombrebouton> boutons;
				StaticVect<string,nombrebouton> effets;
				string effetescape;
				bool isbgdessin;			//TRUE si le background est un dessin; FALSE si le background est simplement ce que contient la mémoire (mémoire des canaux + msn + etc.)
				string bgdessin; int bgdessinnbligne;
				int bgptinteretx; int bgptinterety;													//Points du dessin qu'on va tenter de placer à un position précise
				double bgposinteretx; double bgposinterety;											//Position (en fraction de la fenêtre) souhaitée pour les points d'intérêt
				bool bgleftlocked; bool bgrightlocked; bool bgtoplocked; bool bgbottomlocked;		//Côtés fixés aux limites du dessin dans l'agrandissement de la fenêtre (si la fenêtre est plus grande, mettre des espaces aux côtés non fixes)				
				string titretxt;
				string titredessin; int titredessinnbligne;
				bool istitredessin;			//TRUE si le titre est un dessin; FALSE si le titre est du texte
				double titrehauteur;		//La fraction de la hauteur à laquelle on veut que le titre commence
				bool actif;
				int posactu; int pospreced;
				int selectpos; int selectneg; int selectesc; int selectenter;			//Compteurs des animations
				int selectpost; int selectnegt; int selectesct; int selectentert;		//Compteurs de temps pour les animations
			//Constructeur
			menu() : actif(false), posactu(0), pospreced(0), isbgdessin(false), istitredessin(false), titretxt(""), effetescape("§a§"),
				largeurbouton(19), hauteurbouton(3), espacebouton(2), selectdelay(400), enterdelay(900) {}
		};

//------------------------------------------------------------------------------------------------------------------------------------------------------
//4) Mettre tout dans un seul objet

	//i) Classes contenant tous les objets utiles	----------------------------------------------------------------------		
	class univers {
		//Membres
		public:
			//Membres pour la console
			fenetre base;
			//Membres de sauvegarde
			bibliotheque biblio;
			memoire mem;
			msnmemoire msnmem;
			//Membres d'affichage à court terme
			static const int taillecanaux = 2;			//Taille des objets de type StaticVect<canal,Taille>				
			static const int taillemessagerie = 15;		//Taille des objets de type StaticVect<msn,Taille>
			static const int taillegroupes = 5;			//Taille des groupes de mots qui doivent être bons dans une commande; copie de la ligne présente dans "class commande"; pas idéal
			static const int tailleordrespecifique = 12;//Taille des enchaînements dans lesquelles les mailles peuvent être jouées; copie de la ligne présente dans "class motif..."; pas idéal
			StaticVect<canal,taillecanaux> canaux;
			StaticVect<string,taillecanaux> nomcanaux;
			StaticVect<msn,taillemessagerie> messagerie;
			//Membres de menus
			static const int taillemenus = 8;
			StaticVect<menu,taillemenus> menus;
			StaticVect<string,taillemenus> nommenus;
			static const int nombrebouton = 5;			//Nombre maximal de boutons; copie de la ligne présente dans "class menu"; pas idéal			
			static const int menunblignesmax = 5;		//Nombre maximal de lignes différente pouvant être toléré dans le titre ou le bouton d'un menu; nécessaire pour créer des StaticVect<int, menunblignesmax> dans LireMenus()
			string quelmenuingameescape;				//Nom du menu à appeler lorsque la touche [ESCAPE] est enfoncée à l'intérieur de la fonction jouer(). Par défaut (""), la touche n'appelle aucun menu et ferme le programme
			StaticVect<string,5> menupreced;			//Noms des menus précédents (quand un menu appelle un autre menu)
			//Membres d'entrées par la joueuse 
			input inp;
			inputecho inpecho;
			//Membre de conditions d'affichage	
			ouvrage histoire;	
			//Membre permettant d'utiliser une distribution normale	
			normdist normbase;
			//Membre donnant l'heure
			horloge clock;
		//Constructeurs
			//Constructeur par défaut
			univers() {
				randseed(clock);			//Poser un départ unique (basé sur l'heure d'exécution du programme) au générateur de nombres aléatoires
			};
		//Fonctions de jeu
			//Fonctions pour modifier la taille de la fenêtre
				void setfenetredefaut(int x, int y); void setfenetremin(int x, int y);
			//Fonctions de petite taille
				void configmemoire();
				void pausecan(int poscan); void pausemsn(int posmsn); void pauseall(); 
				void unpausecan(int poscan); void unpausemsn(int posmsn); void unpauseall();
				void UserInputEcho();
				void overridecanal(int canpos);
				void ReecrireMemoire();
				void ReecrireMsn(int msnpos); void EffacerMsn(int msnpos);
				void chgcolcan(); void chgcolmsn(); void chgcolcommande(); void chgcolmenu(); void chgcolmenuselect(); void chgcolmenuarrplan(); 
				void ReecrireTout(); void ReecrireToutAvecCouleurs();
			//Fonctions pour transférer le texte d'un motif vers un canal ou un msn	
				void integrationmanu(int chapitrepos, int motifpos);
				void integrationauto(int chapitrepos, int motifpos);
				void AutoInterpret();
			//Fonctions pour lire les canaux/messagerie et appliquer leurs effets sur la console	
				void LireCanaux();
				void LireMessagerie();
			//Fonctions pour recevoir et interpréter les commandes de la joueuse	
				void UserInputInterpret(); 
			    void UserInput();
			//Fonction pour utiliser les menus
				void LireMenus(string nommenu); 
			//Fonction pour tout coordonner harmonieusement
				void jouer();
				void debuter(const string& str);
		//Fonction de remplissage aisé
			//Fonctions pour nommer les livres et les rayons de la bibliothèque
				void nvrayon(const string& str);
				void nvlivre(const string& str);
			//Fonctions pour créer de nouveaux canaux et les personaliser
				void nvcanal(const string& str);
				void canaldelai(int val);
				void canalalinea(int val);
				void canalterminaison(const string& str);
			//Fonctions pour organiser les chapitres et les motifs (permettent l'activation des textes)	
				void nvchapt();
				void ccond(const string& str);
				void nvmanu(const string& str);
				void nvauto(); 
			//Fonctions pour remplir les motifs	
				void mcanal(const string& str); void acanal(const string& str);
				void mtexte(const string& str);	void atexte(const string& str);
				void mordre(const string& str); void aordre(const string& str);
				void mordrespecifique(const string& str); void aordrespecifique(const string& str);				
				void mordrespecifiqueodds(const string& str); void aordrespecifiqueodds(const string& str); 
				void mdeb(const string& str); void adeb(const string& str);												
				void mfin(const string& str); void afin(const string& str);	
				void mcond(const string& str); void acond(const string& str);
				void mover(); void aover();
				void mreserve();
				void mcomm(const string& str); 
				void mcommexact(const string& str);
			//Fonctions pour remplir les menus
				void nvmenu(const string& str);
				void menubg(const string& str, int nbligne); void menubgpointinteret(int coordx, int coordy, double fractionfenetrex, double fractionfenetrey); void menubglock(const string& str);
				void menutitretxt(const string& str); void menutitredessin(const string& str, int nbligne); void menutitrehauteur(double val);
				void menuhauteurbouton(int val); void menulargeurbouton(int val); void menuespacebouton(int val);	
				void menuselectdelay(int val); void menuenterdelay(int val);		
				void menunvbouton(const string& strbout, const string& streff);
				void menuescape(const string& str);
				void menuingameescape(const string& str);
			//Fonctions pour tester le contenu
				void menchainetest();	void aenchainetest();
	};
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//5) Fonctions spécialisées pour la bonne marche du jeu

	//i) Fonctions pour modifier la taille de la fenêtre	----------------------------------------------------------------------		

		//a) Fonction : setfenetredefaut ; configure une taille par défaut de la fenêtre de jeu -> à choisir en fonction du plus beau dessin de background pour le menu principal!
		void univers::setfenetredefaut(int x, int y) {base.dimdef(x,y);}
	
		//b) Fonction : setfenetremin ; configure une taille par défaut de la fenêtre de jeu -> à choisir en fonction du plus petit dessin possible pour le menu principal!
		void univers::setfenetremin(int x, int y) {base.dimmin(x,y);}

	//ii) Fonctions de petite taille	----------------------------------------------------------------------		

		//a) Fonction : configmemoire ; initie les objets de mémoire avec des tailles qui cadrent avec la fenêtre actuelle
		void univers::configmemoire() {
			mem.setsize(base.limtxtx);
			msnmem.setsize(base.limtxtx,base.limtxty);	
		}
		
		//b) Fonction : UserInputEcho ; validant graphiquement l'acceptation ou le refus des commandes envoyées
		void univers::UserInputEcho() {	
			if(inpecho.actif&&inpecho.nxtt<clock.currentt) {
				base.chgcol(inpecho.txtcol,inpecho.bgcol);
				//Clignoter
				if(inpecho.clignote[0]>0){
					base.curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
				} else {
					base.curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(' ');		
				}
				base.chgcol(biblio.acces(biblio.poscouleur,"actutxt"),biblio.acces(biblio.poscouleur,"actubg"));                       //Revenir à la couleur de base	
				inpecho.nxtt = clock.currentt + round(abs(inpecho.clignote[0])*pow(inp.vit,1/2));        //Updater le "next time"		//vit ^ (1/2), pour ne pas TROP modifier la vitesse...
				inpecho.clignote.suppression(1);            //Passer à la prochaine instruction
				if(inpecho.clignote.longueur==0) inpecho.actif = false;			//Vérifier s'il reste toujours du stock à passer dans le canal	
			}	
		}
		
		//c) Fonction : pauseall/unpauseall ; arrête les compteurs des tous les canaux et msn, et les repart
		void univers::pausecan(int poscan) {if(!canaux[poscan].pause) {canaux[poscan].pause = true; canaux[poscan].pausedt = abs(canaux[poscan].nxtt - clock.currentt);}}
		void univers::pausemsn(int posmsn) {if(!messagerie[posmsn].pause) {messagerie[posmsn].pause = true; messagerie[posmsn].pausedt = abs(messagerie[posmsn].nxtt - clock.currentt);}}
		void univers::pauseall() {
			for(int poscan=0; poscan<canaux.longueur; poscan++) pausecan(poscan);
			for(int posmsn=0; posmsn<messagerie.longueur; posmsn++) pausemsn(posmsn);
		}
		void univers::unpausecan(int poscan) {if(canaux[poscan].pause) {canaux[poscan].pause = false; canaux[poscan].nxtt = clock.currentt + canaux[poscan].pausedt + round(canaux[poscan].delay * 5 * inp.vit);}}
		void univers::unpausemsn(int posmsn) {if(messagerie[posmsn].pause) {messagerie[posmsn].pause = false; messagerie[posmsn].nxtt = clock.currentt + messagerie[posmsn].pausedt + round(messagerie[posmsn].delay * 5 * inp.vit);}}
		void univers::unpauseall() {
			for(int poscan=0; poscan<canaux.longueur; poscan++) if(!canaux[poscan].frozen) unpausecan(poscan);
			for(int posmsn=0; posmsn<messagerie.longueur; posmsn++) if(!messagerie[posmsn].frozen) unpausemsn(posmsn);
		}
		
		//d) Fonction : overridecanal() ; vide le canal, en appliquant cependant les codes spéciaux sélectionnés qui s'y trouvent
		void univers::overridecanal(int canpos) {
			//Passer tous les codes spéciaux importants
			int strnb = canaux[canpos].txt.length(); bool cdsp = false;
			for(int txtpos=0; txtpos<strnb; txtpos++) { 
				if(cdsp) {		//Si l'on est dans un code spécial
					if(canaux[canpos].txt[txtpos]=='m'){		//'m' pour "motif" -> marquer le motif automatique comme n'étant plus en cours
						string poschap; string posmotif; 
						txtpos++; while(canaux[canpos].txt[txtpos] != ';') poschap += canaux[canpos].txt[txtpos++]; 
						txtpos++; while(canaux[canpos].txt[txtpos] != '§') posmotif += canaux[canpos].txt[txtpos++];
						histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //Désigner le motif signalé comme n'étant plus en cours
					} else while(canaux[canpos].txt[txtpos] != '§') txtpos++;
					txtpos++; cdsp = false;      //Terminer le code spécial actuel
				} else if(canaux[canpos].txt[txtpos]=='§') cdsp = true;          //Si l'on n'est pas dans un code spécial
			}
			if(canaux[canpos].txt.length()==0) canaux[canpos].txt = canaux[canpos].terminaison;     //Remplacer ce qui était dans le canal par la "terminaison" de ce canal (par défaut, c'est "" - c'est à dire rien)
			if(canaux[canpos].txt.length()==0) canaux[canpos].actif = false;           //Désactiver le canal, si le canal est vide
		}

		//e) Fonction ReecrireMemoire()			
		void univers::ReecrireMemoire() {
			base.curspos(0,0);   //Commencer en haut, puis descendre naturellement
			for(int county = base.consy; county < base.limtxty; county++){             //base.consy : facteur de décalage de la console
				for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
			}	
		}
		
		//f) Fonction ReecrireMsn()			
		void univers::ReecrireMsn(int msnpos) {
			//Créer un raccourci pour la position à laquelle on est rendue (la "suivante")
			int posrc = messagerie[msnpos].postxt;		//rc pour raccourci
			//Ré-écrire depuis le début, jusqu'à la "position précédente"
			int posx = messagerie[msnpos].posdebx -1; int posy = messagerie[msnpos].posdeby;		//S'initie à la même position que dans la fonction Integration()
			int counttxt = 0;
			while(counttxt<posrc) {
				if(messagerie[msnpos].txt[counttxt]=='§') {
					counttxt += CodeSpecialLongueur(strintervalle(messagerie[msnpos].txt,counttxt,messagerie[msnpos].txt.length()-1));	//Skipper les codes spéciaux						
				} else {
					//Dealer avec les sauts de lignes
					if(posx>=base.limtxtx-1) {posy++; posx = -1;}
					if(messagerie[msnpos].txt[counttxt]=='\n') {posy++;}	
					posx++;			//Updater le posx
					if(messagerie[msnpos].txt[counttxt]!='\n') {base.curspos(posx,posy); out(messagerie[msnpos].txt[counttxt]);}
					counttxt++;									
				}
			}		
		}
							
		//g) Fonction EffacerMsn()				//Pour ré-écrire par-dessus à l'aide de la mémoire!
		void univers::EffacerMsn(int msnpos) {
			//Créer un raccourci pour la position à laquelle on est rendue (la "suivante")
			int posrc = messagerie[msnpos].postxt;		//rc pour raccourci
			//Ré-écrire depuis le début, jusqu'à la "position précédente"
			int posx = messagerie[msnpos].posdebx-1; int posy = messagerie[msnpos].posdeby;		//S'initie à la même position que dans la fonction Integration()
			int counttxt = 0;
			while(counttxt<posrc) {
				if(messagerie[msnpos].txt[counttxt]=='§') {
					counttxt += CodeSpecialLongueur(strintervalle(messagerie[msnpos].txt,counttxt,messagerie[msnpos].txt.length()-1));	//Skipper les codes spéciaux						
				} else {
					//Dealer avec les sauts de lignes
					if(posx>=base.limtxtx-1) {posy++; posx = -1;}
					if(messagerie[msnpos].txt[counttxt]=='\n') {posy++;}	
					posx++;			//Updater le posx
					if(messagerie[msnpos].txt[counttxt]!='\n') {base.curspos(posx,posy); out(mem.acces(posx,posy+base.consy));}
					counttxt++;	
				}
			}		
		}         

		//h) Fonction chgcolcan/msn/commande
		void univers::chgcolcan(){
			if(biblio.acces(biblio.poscouleur,"actutxt")!=biblio.acces(biblio.poscouleur,"cantxt")||biblio.acces(biblio.poscouleur,"actubg")!=biblio.acces(biblio.poscouleur,"canbg")) {
				base.chgcol(biblio.acces(biblio.poscouleur,"cantxt"),biblio.acces(biblio.poscouleur,"canbg"));		//Mettre la couleur des canaux
				biblio.modif(biblio.poscouleur,"actutxt",biblio.acces(biblio.poscouleur,"cantxt")); biblio.modif(biblio.poscouleur,"actubg",biblio.acces(biblio.poscouleur,"canbg"));
			}
		}
		void univers::chgcolmsn(){
			if(biblio.acces(biblio.poscouleur,"actutxt")!=biblio.acces(biblio.poscouleur,"msntxt")||biblio.acces(biblio.poscouleur,"actubg")!=biblio.acces(biblio.poscouleur,"msnbg")) {
				base.chgcol(biblio.acces(biblio.poscouleur,"msntxt"),biblio.acces(biblio.poscouleur,"msnbg"));		//Mettre la couleur des msn
				biblio.modif(biblio.poscouleur,"actutxt",biblio.acces(biblio.poscouleur,"msntxt")); biblio.modif(biblio.poscouleur,"actubg",biblio.acces(biblio.poscouleur,"msnbg"));
			}
		}
		void univers::chgcolcommande(){
			if(biblio.acces(biblio.poscouleur,"actutxt")!=biblio.acces(biblio.poscouleur,"commtxt")||biblio.acces(biblio.poscouleur,"actubg")!=biblio.acces(biblio.poscouleur,"commbg")) {
				base.chgcol(biblio.acces(biblio.poscouleur,"commtxt"),biblio.acces(biblio.poscouleur,"commbg"));		//Mettre la couleur des commandes
				biblio.modif(biblio.poscouleur,"actutxt",biblio.acces(biblio.poscouleur,"commtxt")); biblio.modif(biblio.poscouleur,"actubg",biblio.acces(biblio.poscouleur,"commbg"));
			}
		}
		void univers::chgcolmenu(){
			if(biblio.acces(biblio.poscouleur,"actutxt")!=biblio.acces(biblio.poscouleur,"menutxt")||biblio.acces(biblio.poscouleur,"actubg")!=biblio.acces(biblio.poscouleur,"menubg")) {
				base.chgcol(biblio.acces(biblio.poscouleur,"menutxt"),biblio.acces(biblio.poscouleur,"menubg"));		//Mettre la couleur des commandes
				biblio.modif(biblio.poscouleur,"actutxt",biblio.acces(biblio.poscouleur,"menutxt")); biblio.modif(biblio.poscouleur,"actubg",biblio.acces(biblio.poscouleur,"menubg"));
			}
		}
		void univers::chgcolmenuselect(){
			if(biblio.acces(biblio.poscouleur,"actutxt")!=biblio.acces(biblio.poscouleur,"menuselecttxt")||biblio.acces(biblio.poscouleur,"actubg")!=biblio.acces(biblio.poscouleur,"menuselectbg")) {
				base.chgcol(biblio.acces(biblio.poscouleur,"menuselecttxt"),biblio.acces(biblio.poscouleur,"menuselectbg"));		//Mettre la couleur des commandes
				biblio.modif(biblio.poscouleur,"actutxt",biblio.acces(biblio.poscouleur,"menuselecttxt")); biblio.modif(biblio.poscouleur,"actubg",biblio.acces(biblio.poscouleur,"menuselectbg"));
			}
		}
		void univers::chgcolmenuarrplan(){
			if(biblio.acces(biblio.poscouleur,"actutxt")!=biblio.acces(biblio.poscouleur,"menuarrplantxt")||biblio.acces(biblio.poscouleur,"actubg")!=biblio.acces(biblio.poscouleur,"menuarrplanbg")) {
				base.chgcol(biblio.acces(biblio.poscouleur,"menuarrplantxt"),biblio.acces(biblio.poscouleur,"menuarrplanbg"));		//Mettre la couleur des commandes
				biblio.modif(biblio.poscouleur,"actutxt",biblio.acces(biblio.poscouleur,"menuarrplantxt")); biblio.modif(biblio.poscouleur,"actubg",biblio.acces(biblio.poscouleur,"menuarrplanbg"));
			}
		}		
		
		//i) Fonction ReecrireTout()			//Pour ré-écrire tous les éléments affichés à l'écran lors de l'histoire!
		void univers::ReecrireTout() {
			ReecrireMemoire(); 																					//Canaux
			for(int msncount=0; msncount<messagerie.longueur; msncount++) ReecrireMsn(msncount); 				//Msn
			base.curspos(0,base.limfeny-1); for(int poscount=0; poscount<base.limfenx-1; poscount++) out(' ');	//Commandes
		}
		void univers::ReecrireToutAvecCouleurs() {
			chgcolcan(); ReecrireMemoire(); 																					//Canaux
			chgcolmsn(); for(int msncount=0; msncount<messagerie.longueur; msncount++) ReecrireMsn(msncount); 					//Msn
			chgcolcommande(); base.curspos(0,base.limfeny-1); for(int poscount=0; poscount<base.limfenx-1; poscount++) out(' ');	//Commandes
		}
		
	//iii) Fonctions pour transférer le texte d'un motif vers un canal ou un msn	----------------------------------------------------------------------		
		
		//a) Fonction : integration ; ajoute un motif à un canal
		void univers::integrationmanu(int chapitrepos, int motifpos) {
			//Vérifier d'abord si on doit mettre le motif en réserve
			if(histoire.filmanu[chapitrepos][motifpos].reserve&&!inp.reserve) {		//La fonction integrationmanu() ne sera jamais lancée si la réserve est pleine, hormis dans le cas du code spécial "§r§". Donc c'est safe.
				inp.reservechap = chapitrepos; inp.reservemotif = motifpos; inp.reserve = true;
			} else {
				inp.reserve = false;
				bool msnbool = histoire.filmanu[chapitrepos][motifpos].msn;
				bool msnskip = false; bool silenceskip = false;
				int xpos; int ypos; int randval;
				//Vérifier si le motif produit du son ou du silence (il peut avoir une probabilité qu'il ne s'intègre pas finalement - mécanisme intégré pour accomoder plus de variété dans le texte affiché)
				if(histoire.filmanu[chapitrepos][motifpos].oddsofsilence>0) {
					randval = randunif(0,histoire.filmanu[chapitrepos][motifpos].oddsofsilence+histoire.filmanu[chapitrepos][motifpos].oddsofsound-1);  //Obtenir un integer aléatoire entre [0,oddsofsilence+oddsofsound[				
					if(randval<histoire.filmanu[chapitrepos][motifpos].oddsofsilence) silenceskip = true;
				}
				//Vérifier s'il y a de la place pour un nouveau msn (si c'est un msn qui est updaté)
				if(!silenceskip&&msnbool) {
					//Choisir le msn qui sera utilisé
					bool msnvide = false; bool lignelibrechoisie = false;
					if(messagerie.longueur<messagerie.taille) msnvide = true;
					if(msnvide) {
						//Choisir la position de départ!
							xpos = round(min(max(normbase.randnormapprox(25,12),0),80)*base.limtxtx/100);		//Dist normale(mean=0.25,sd=0.15), bornée à 0% et 80% de la console
							ypos = round(min(max(normbase.randnormapprox(28,16),0),80)*base.limtxty/100);
							//Choisir une ligne de départ non occupée
							lignelibrechoisie = true; 
							if(!msnmem.accesligne(ypos)) {
								lignelibrechoisie = false; int countligne = 1;
								while(!lignelibrechoisie) {
									if(ypos+countligne<base.limtxty&&msnmem.accesligne(ypos+countligne)) { ypos += countligne; lignelibrechoisie = true;
									} else if(ypos-countligne>=0&&msnmem.accesligne(ypos-countligne)) { ypos -= countligne; lignelibrechoisie = true;}
									countligne++;
									if(ypos+countligne>=base.limtxty&&ypos-countligne<0) break;		//Si on arrive hors des limites à la fois vers le haut et vers le bas, aucune ligne n'est libre
								}
							}
					}
					if(!msnvide||!lignelibrechoisie) {msnskip = true; inp.accepted = false;}	//Aucune ligne ou msn n'est libre : refuser d'intégrer le motif, même si la commande est bonne			
				} 
				if(!silenceskip&&!msnskip){
					//Définir le texte à insérer
					string txtmotif;
					txtmotif += histoire.filmanu[chapitrepos][motifpos].codespeciauxdebut;   //Codes spéciaux début
						//Choisir l'enchaînement à insérer
						if(histoire.filmanu[chapitrepos][motifpos].ordreavecodds) {		//Chaque enchaînement peut avoir une probabilité différente!
							int sumprob = 0; StaticVect<int,tailleordrespecifique> vectprob;
							for(int posprob=0; posprob<histoire.filmanu[chapitrepos][motifpos].ordrespecifiqueodds.longueur; posprob++) {	//Évaluer chaque probabilité
								sumprob += histoire.filmanu[chapitrepos][motifpos].ordrespecifiqueodds[posprob].eval(biblio); vectprob[posprob] = sumprob; 
							}
							randval = randunif(0,sumprob-1);  //Obtenir un integer aléatoire entre [0,sumprob[
							int choix; 
							for(int posprob=0; posprob<histoire.filmanu[chapitrepos][motifpos].ordrespecifiqueodds.longueur; posprob++) {
								if(randval<vectprob[posprob]) {choix = posprob; break;}
							}	
							for(int posench=0; posench<histoire.filmanu[chapitrepos][motifpos].ordrespecifique[choix].longueur; posench++) {
								txtmotif += histoire.filmanu[chapitrepos][motifpos].maille[histoire.filmanu[chapitrepos][motifpos].ordrespecifique[choix][posench]];
							}	
						} else {		//Chaque enchaînement a une probabilité égale
							//Trouver le nombre d'enchaînements possible total
							int nbstr = histoire.filmanu[chapitrepos][motifpos].ordre.length();
							int enchainetot = 0; int nbrench = 1; int nbrpossible = 1;
							for(int countstr = 0; countstr<=nbstr; countstr++) {
								if(countstr<nbstr) {
									if(histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='/'||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='|') {nbrpossible++;}	//Deux ortographes possibles pour le "ou"
									if(histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='-'||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]==',') {nbrench *= nbrpossible; nbrpossible = 1;}	//Deux ortographes possibles pour le "et"								
								}
								if(countstr==nbstr||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]==';') {nbrench *= nbrpossible; enchainetot += nbrench; nbrench = 1; nbrpossible = 1;}		//Une seule ortographe pour "aussi" + le dernier bout
							}
							enchainetot += histoire.filmanu[chapitrepos][motifpos].ordrespecifique.longueur;	//Ajouter le nombre d'enchaînements bricolés
							//Choisir un des groupes d'enchaînements
							int randval = randunif(0,enchainetot-1);  //Obtenir un integer aléatoire entre [0,sumprob[
							bool choixmecan = false;
							int enchainesum =0; int debchoixstr = 0; int finchoixstr = nbstr; 
							nbrench = 1; nbrpossible = 1;
							for(int countstr = 0; countstr<=nbstr; countstr++) {
								if(countstr<nbstr) {
									if(histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='/'||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='|') {nbrpossible++;}	//Deux ortographes possibles pour le "ou"
									if(histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='-'||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]==',') {nbrench *= nbrpossible; nbrpossible = 1;}	//Deux ortographes possibles pour le "et"								
								}
								if(countstr==nbstr||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]==';') {			//Une seule ortographe pour "aussi" + le dernier bout de la fin
									nbrench *= nbrpossible; enchainesum += nbrench; nbrench = 1; nbrpossible = 1;		//Ajouter le nombre d'enchaînements de ces combinaisons à la somme d'enchaînements
									if(randval<enchainesum) {finchoixstr = countstr; choixmecan = true;} else debchoixstr = countstr+1;
								}	
							}						
							if(choixmecan) {	//Le choix se situe parmi les "ordres mécaniques"; on l'intègre au fur et à mesure, et on décide sur le coup à chaque fois qu'on est confrontée à un choix
								string posmaille; int debpossiblestr = 0; int finpossiblestr; int debpossiblechoisi; int finpossiblechoisi;
								nbrpossible = 1;
								for(int countstr = debchoixstr; countstr<=finchoixstr; countstr++) {
									//Simplement prendre en note qu'un choix s'en vient
									if(countstr<finchoixstr&&(histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='/'||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='|')) {nbrpossible++;}	//Deux ortographes possibles pour le "ou"
									//Ajouter une maille au texte à lire!
									if(countstr==finchoixstr||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]=='-'||histoire.filmanu[chapitrepos][motifpos].ordre[countstr]==',') {	//Deux ortographes possibles pour le "et" + le dernier bout de la fin
										finpossiblestr = countstr-1;
										if(nbrpossible==1) { txtmotif += histoire.filmanu[chapitrepos][motifpos].maille[stoi(strintervalle(histoire.filmanu[chapitrepos][motifpos].ordre,debpossiblestr,finpossiblestr))-1];		//C'est facile: ajouter la maille spécifiée		//-1, parce qu'on doit respecter l'ordre de c++ qui commence par 0!
										} else {					//Choisir entre les différentes possibilités la maille à ajouter
											randval = randunif(0,nbrpossible-1);  //Obtenir un integer aléatoire entre [0,nbrpossible[
											debpossiblechoisi = debpossiblestr; finpossiblechoisi = finpossiblestr; nbrpossible = 0;	//nbrpossible va ici agir comme compteur pour le choix
											//Trouver les bornes du nombre indiqué
											for(int countstrposs = debpossiblestr; countstrposs<=finpossiblestr; countstrposs++) {
												if(histoire.filmanu[chapitrepos][motifpos].ordre[countstrposs]=='/'||histoire.filmanu[chapitrepos][motifpos].ordre[countstrposs]=='|') {
													if(randval==nbrpossible) {finpossiblechoisi = countstrposs-1; break;} else debpossiblechoisi = countstrposs+1;
													nbrpossible++;
												}
											}
											//Ajouter la maille sélectionnée
											txtmotif += histoire.filmanu[chapitrepos][motifpos].maille[stoi(strintervalle(histoire.filmanu[chapitrepos][motifpos].ordre,debpossiblechoisi,finpossiblechoisi))-1];	//Ajouter le texte de la position spécifiée		//-1, parce qu'on doit respecter l'ordre de c++ qui commence par 0!								
										}
										nbrpossible = 1;	//Remettre le compteur à la valeur par défaut
									}
								}
							} else {	//Le choix se situe parmi les "ordres bricolés"; on l'intègre de la même manière que si les enchaînements étaient liés à des probabilités!
								int poschoix = randval - enchainesum;		//Enlever les enchaînements mécanisés: ça donne la position!
								for(int countench=0; countench<histoire.filmanu[chapitrepos][motifpos].ordrespecifique[poschoix].longueur; countench++) {
									txtmotif += histoire.filmanu[chapitrepos][motifpos].maille[histoire.filmanu[chapitrepos][motifpos].ordrespecifique[poschoix][countench]];
								}							
							}
						}
					txtmotif += histoire.filmanu[chapitrepos][motifpos].codespeciauxfin;		//Codes spéciaux fin
					//Updater le canal/msn 
					if(msnbool) {
						messagerie.ajoutvide();																					//Ajouter officiellement un objet msn à la messagerie
						messagerie[messagerie.longueur-1].posdebx = xpos; messagerie[messagerie.longueur-1].posdeby = ypos;		//Définir les positions de départ
						msnmem.modifligne(ypos,false);																			//Définir la ligne comme occupée
						messagerie[messagerie.longueur-1].posx = xpos-1; messagerie[messagerie.longueur-1].posy = ypos;			//Définir les positions du curseur (avant la première entrée)
						messagerie[messagerie.longueur-1].postxt = 0;															//Remettre au début du texte
						messagerie[messagerie.longueur-1].construire = true; messagerie[messagerie.longueur-1].nbysupp = 0;		//Remettre les autres compteurs à leur position initiale
						messagerie[messagerie.longueur-1].delay = normbase.randnormapprox(110,10);								//Mettre un délai aléatoire
						messagerie[messagerie.longueur-1].txt += txtmotif;														//Ajouter le texte				
						messagerie[messagerie.longueur-1].nxtt = clock.currentt; 														//Updater le nxtt pour qu'il commence à partir de l'intégration
					} else {
						if(histoire.filmanu[chapitrepos][motifpos].override) overridecanal(histoire.filmanu[chapitrepos][motifpos].canal);	//Overloader le canal si nécessaire			//Ne s'applique pas aux msn			
						canaux[histoire.filmanu[chapitrepos][motifpos].canal].txt += txtmotif;																			//Ajouter le texte				
						if(!canaux[histoire.filmanu[chapitrepos][motifpos].canal].actif) canaux[histoire.filmanu[chapitrepos][motifpos].canal].nxtt = clock.currentt; 		//Updater le nxtt pour qu'il commence à partir de l'intégration
						if(canaux[histoire.filmanu[chapitrepos][motifpos].canal].txt.length()>0) canaux[histoire.filmanu[chapitrepos][motifpos].canal].actif = true;	//Marquer le canal comme actif
					}	
				}			
			}
		}
		void univers::integrationauto(int chapitrepos, int motifpos) {
			bool msnbool = histoire.filauto[chapitrepos][motifpos].msn;
			bool msnskip = false; bool silenceskip = false;
			int xpos; int ypos; int randval;
			//Vérifier si le motif produit du son ou du silence (il peut avoir une probabilité qu'il ne s'intègre pas finalement - mécanisme intégré pour accomoder plus de variété dans le texte affiché)
			if(histoire.filauto[chapitrepos][motifpos].oddsofsilence>0) {
				randval = randunif(0,histoire.filauto[chapitrepos][motifpos].oddsofsilence+histoire.filauto[chapitrepos][motifpos].oddsofsound-1);  //Obtenir un integer aléatoire entre [0,oddsofsilence+oddsofsound[				
				if(randval<histoire.filauto[chapitrepos][motifpos].oddsofsilence) silenceskip = true;
			}
			//Vérifier s'il y a de la place pour un nouveau msn (si c'est un msn qui est updaté)
			if(!silenceskip&&msnbool) {
				//Choisir le msn qui sera utilisé
				bool msnvide = false; bool lignelibrechoisie = false;
				if(messagerie.longueur<messagerie.taille) msnvide = true;
				if(msnvide) {
					//Choisir la position de départ!
						xpos = round(min(max(normbase.randnormapprox(25,12),0),80)*base.limtxtx/100);		//Dist normale(mean=0.25,sd=0.15), bornée à 0% et 80% de la console
						ypos = round(min(max(normbase.randnormapprox(28,16),0),80)*base.limtxty/100);
						//Choisir une ligne de départ non occupée
						lignelibrechoisie = true; 
						if(!msnmem.accesligne(ypos)) {
							lignelibrechoisie = false; int countligne = 1;
							while(!lignelibrechoisie) {
								if(ypos+countligne<base.limtxty&&msnmem.accesligne(ypos+countligne)) { ypos += countligne; lignelibrechoisie = true;
								} else if(ypos-countligne>=0&&msnmem.accesligne(ypos-countligne)) { ypos -= countligne; lignelibrechoisie = true;}
								countligne++;
								if(ypos+countligne>=base.limtxty&&ypos-countligne<0) break;		//Si on arrive hors des limites à la fois vers le haut et vers le bas, aucune ligne n'est libre
							}
						}
				}
				if(!msnvide||!lignelibrechoisie) {msnskip = true; }	//Aucune ligne ou msn n'est libre : attendre pour jouer le motif (ne pas l'intégrer)			
			} 
			if(!silenceskip&&!msnskip){
				//Définir le texte à insérer
				string txtmotif;
				txtmotif += histoire.filauto[chapitrepos][motifpos].codespeciauxdebut;   //Codes spéciaux début
					//Choisir l'enchaînement à insérer
					if(histoire.filauto[chapitrepos][motifpos].ordreavecodds) {		//Chaque enchaînement peut avoir une probabilité différente!
						int sumprob = 0; StaticVect<int,tailleordrespecifique> vectprob;
						for(int posprob=0; posprob<histoire.filauto[chapitrepos][motifpos].ordrespecifiqueodds.longueur; posprob++) {	//Évaluer chaque probabilité
							sumprob += histoire.filauto[chapitrepos][motifpos].ordrespecifiqueodds[posprob].eval(biblio); vectprob[posprob] = sumprob; 
						}
						randval = randunif(0,sumprob-1);  //Obtenir un integer aléatoire entre [0,sumprob[
						int choix; 
						for(int posprob=0; posprob<histoire.filauto[chapitrepos][motifpos].ordrespecifiqueodds.longueur; posprob++) {
							if(randval<vectprob[posprob]) {choix = posprob; break;}
						}	
						for(int posench=0; posench<histoire.filauto[chapitrepos][motifpos].ordrespecifique[choix].longueur; posench++) {
							txtmotif += histoire.filauto[chapitrepos][motifpos].maille[histoire.filauto[chapitrepos][motifpos].ordrespecifique[choix][posench]];
						}	
					} else {		//Chaque enchaînement a une probabilité égale
					
					
					
						//DEBUGGG
						//out("DEBUG"); abort();
					
					
						//Trouver le nombre d'enchaînements possible total
						int nbstr = histoire.filauto[chapitrepos][motifpos].ordre.length();
						int enchainetot = 0; int nbrench = 1; int nbrpossible = 1;
						for(int countstr = 0; countstr<=nbstr; countstr++) {
							if(countstr<nbstr) {
								if(histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='/'||histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='|') {nbrpossible++;}	//Deux ortographes possibles pour le "ou"
								if(histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='-'||histoire.filauto[chapitrepos][motifpos].ordre[countstr]==',') {nbrench *= nbrpossible; nbrpossible = 1;}	//Deux ortographes possibles pour le "et"								
							}
							if(countstr==nbstr||histoire.filauto[chapitrepos][motifpos].ordre[countstr]==';') {nbrench *= nbrpossible; enchainetot += nbrench; nbrench = 1; nbrpossible = 1;}		//Une seule ortographe pour "aussi" + le dernier bout
						}
						enchainetot += histoire.filauto[chapitrepos][motifpos].ordrespecifique.longueur;	//Ajouter le nombre d'enchaînements bricolés
						//Choisir un des groupes d'enchaînements
						int randval = randunif(0,enchainetot-1);  //Obtenir un integer aléatoire entre [0,sumprob[
						bool choixmecan = false;
						int enchainesum =0; int debchoixstr = 0; int finchoixstr = nbstr; 
						nbrench = 1; nbrpossible = 1;
						for(int countstr = 0; countstr<=nbstr; countstr++) {
							if(countstr<nbstr) {
								if(histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='/'||histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='|') {nbrpossible++;}	//Deux ortographes possibles pour le "ou"
								if(histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='-'||histoire.filauto[chapitrepos][motifpos].ordre[countstr]==',') {nbrench *= nbrpossible; nbrpossible = 1;}	//Deux ortographes possibles pour le "et"								
							}
							if(countstr==nbstr||histoire.filauto[chapitrepos][motifpos].ordre[countstr]==';') {			//Une seule ortographe pour "aussi" + le dernier bout de la fin
								nbrench *= nbrpossible; enchainesum += nbrench; nbrench = 1; nbrpossible = 1;		//Ajouter le nombre d'enchaînements de ces combinaisons à la somme d'enchaînements
								if(randval<enchainesum) {finchoixstr = countstr; choixmecan = true;} else debchoixstr = countstr+1;
							}	
						}						
						if(choixmecan) {	//Le choix se situe parmi les "ordres mécaniques"; on l'intègre au fur et à mesure, et on décide sur le coup à chaque fois qu'on est confrontée à un choix
							string posmaille; int debpossiblestr = 0; int finpossiblestr; int debpossiblechoisi; int finpossiblechoisi;
							nbrpossible = 1;
							for(int countstr = debchoixstr; countstr<=finchoixstr; countstr++) {
								//Simplement prendre en note qu'un choix s'en vient
								if(countstr<finchoixstr&&(histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='/'||histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='|')) {nbrpossible++;}	//Deux ortographes possibles pour le "ou"
								//Ajouter une maille au texte à lire!
								if(countstr==finchoixstr||histoire.filauto[chapitrepos][motifpos].ordre[countstr]=='-'||histoire.filauto[chapitrepos][motifpos].ordre[countstr]==',') {	//Deux ortographes possibles pour le "et" + le dernier bout de la fin
									finpossiblestr = countstr-1;
									if(nbrpossible==1) { txtmotif += histoire.filauto[chapitrepos][motifpos].maille[stoi(strintervalle(histoire.filauto[chapitrepos][motifpos].ordre,debpossiblestr,finpossiblestr))-1];		//C'est facile: ajouter la maille spécifiée		//-1, parce qu'on doit respecter l'ordre de c++ qui commence par 0!
									} else {					//Choisir entre les différentes possibilités la maille à ajouter
										randval = randunif(0,nbrpossible-1);  //Obtenir un integer aléatoire entre [0,nbrpossible[
										debpossiblechoisi = debpossiblestr; finpossiblechoisi = finpossiblestr; nbrpossible = 0;	//nbrpossible va ici agir comme compteur pour le choix
										//Trouver les bornes du nombre indiqué
										for(int countstrposs = debpossiblestr; countstrposs<=finpossiblestr; countstrposs++) {
											if(histoire.filauto[chapitrepos][motifpos].ordre[countstrposs]=='/'||histoire.filauto[chapitrepos][motifpos].ordre[countstrposs]=='|') {
												if(randval==nbrpossible) {finpossiblechoisi = countstrposs-1; break;} else debpossiblechoisi = countstrposs+1;
												nbrpossible++;
											}
										}
										//Ajouter la maille sélectionnée
										txtmotif += histoire.filauto[chapitrepos][motifpos].maille[stoi(strintervalle(histoire.filauto[chapitrepos][motifpos].ordre,debpossiblechoisi,finpossiblechoisi))-1];	//Ajouter le texte de la position spécifiée				//-1, parce qu'on doit respecter l'ordre de c++ qui commence par 0!								
									}
									nbrpossible = 1;	//Remettre le compteur à la valeur par défaut
									debpossiblestr = countstr + 1;	//Updater le début du prochain string
								}
							}							
						} else {	//Le choix se situe parmi les "ordres bricolés"; on l'intègre de la même manière que si les enchaînements étaient liés à des probabilités!
							int poschoix = randval - enchainesum;		//Enlever les enchaînements mécanisés: ça donne la position!
							for(int countench=0; countench<histoire.filauto[chapitrepos][motifpos].ordrespecifique[poschoix].longueur; countench++) {
								txtmotif += histoire.filauto[chapitrepos][motifpos].maille[histoire.filauto[chapitrepos][motifpos].ordrespecifique[poschoix][countench]];
							}							
						}
					}
				txtmotif += histoire.filauto[chapitrepos][motifpos].codespeciauxfin;		//Codes spéciaux fin
				txtmotif += "§a" + to_string(chapitrepos) + ';' + to_string(motifpos) +'§';		//Code spécial permettant d'enlever le status en cours du motif     //Faut convertir les int en string...
				//Marquer le motif comme "en cours"
				histoire.filauto[chapitrepos][motifpos].encours = true;     
				//Updater le canal/msn 
				if(msnbool) {
					messagerie.ajoutvide();																					//Ajouter officiellement un objet msn à la messagerie
					messagerie[messagerie.longueur-1].posdebx = xpos; messagerie[messagerie.longueur-1].posdeby = ypos;		//Définir les positions de départ
					msnmem.modifligne(ypos,false);																			//Définir la ligne comme occupée
					messagerie[messagerie.longueur-1].posx = xpos-1; messagerie[messagerie.longueur-1].posy = ypos;			//Définir les positions du curseur (avant la première entrée)
					messagerie[messagerie.longueur-1].postxt = 0;															//Remettre au début du texte
					messagerie[messagerie.longueur-1].construire = true; messagerie[messagerie.longueur-1].nbysupp = 0;		//Remettre les autres compteurs à leur position initiale
					messagerie[messagerie.longueur-1].attente = false; messagerie[messagerie.longueur-1].pause = false;
					messagerie[messagerie.longueur-1].delay = normbase.randnormapprox(100,10);								//Mettre un délai aléatoire
					messagerie[messagerie.longueur-1].txt = txtmotif;														//Ajouter le texte				
					messagerie[messagerie.longueur-1].nxtt = clock.currentt; 												//Updater le nxtt pour qu'il commence à partir de l'intégration
				} else {
					if(histoire.filauto[chapitrepos][motifpos].override) overridecanal(histoire.filauto[chapitrepos][motifpos].canal);	//Overloader le canal si nécessaire			//Ne s'applique pas aux msn			
					canaux[histoire.filauto[chapitrepos][motifpos].canal].txt += txtmotif;																			//Ajouter le texte				
					if(!canaux[histoire.filauto[chapitrepos][motifpos].canal].actif) canaux[histoire.filauto[chapitrepos][motifpos].canal].nxtt = clock.currentt; 		//Updater le nxtt pour qu'il commence à partir de l'intégration
					if(canaux[histoire.filauto[chapitrepos][motifpos].canal].txt.length()>0) canaux[histoire.filauto[chapitrepos][motifpos].canal].actif = true;	//Marquer le canal comme actif
					canaux[histoire.filauto[chapitrepos][motifpos].canal].pause = false;
				}	
			}
		}

		//b) Fonction : AutoInterpret ; permet de vérifier si les conditions d'application des motifs automatiques sont remplies
		void univers::AutoInterpret() {
			//Pour chaque chapitre
			for(int chapitrepos=0; chapitrepos<histoire.filauto.longueur; chapitrepos++) { if(histoire.cadenas[chapitrepos].eval(biblio)) {			
				//Pour chaque motif dans l'histoire
				for(int motifpos=0; motifpos<histoire.filauto[chapitrepos].longueur; motifpos++) {if(histoire.filauto[chapitrepos][motifpos].condition.eval(biblio)&&!histoire.filauto[chapitrepos][motifpos].encours) {
					integrationauto(chapitrepos,motifpos);            //Intégrer tout de suite le motif dans le canal	
				}}
			}}
		}		
	
	//iii) Fonctions pour lire les canaux/messagerie et appliquer leurs effets sur la console	----------------------------------------------------------------------		

		//a) Fonction LireCanaux()
		void univers::LireCanaux() {
			//Lire tous les canaux, si ils sont prêts
			for(int canpos=0; canpos<canaux.longueur; canpos++) {if(canaux[canpos].actif&&canaux[canpos].nxtt<clock.currentt&&(!canaux[canpos].pause)) {
				//Interpréter les "codes spéciaux" (§...§)
				if(canaux[canpos].txt[0]=='§'){		
					//Déterminer la longueur du code spécial
						int CodeSpecialLong = CodeSpecialLongueur(canaux[canpos].txt);			
					//Lire le code spécial	
						if(canaux[canpos].txt[1]=='a'){		//'a' pour "automatique" -> marquer le motif automatique comme n'étant plus en cours			
							string poschap; string posmotif; int posSpecial = 2;
							while(canaux[canpos].txt[posSpecial] != ';') poschap += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(canaux[canpos].txt[posSpecial] != '§') posmotif += canaux[canpos].txt[posSpecial++];
							histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //Désigner le motif signalé comme n'étant plus en cours
						} else if(canaux[canpos].txt[1]=='b'){		//'b' pour "biblio" -> modifier la bibliothèque
							string nomrayon; string nomlivre; string val;
							int posSpecial = 2; if(canaux[canpos].txt[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
							while(canaux[canpos].txt[posSpecial] != '¶') nomrayon += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(!(canaux[canpos].txt[posSpecial] == '~' && canaux[canpos].txt[posSpecial+1] == '>')) nomlivre += canaux[canpos].txt[posSpecial++];  //ex: "§bintro¶desuet~>1§"
							posSpecial+=2; while(canaux[canpos].txt[posSpecial] != '§') val += canaux[canpos].txt[posSpecial++];							
							biblio.modif(nomrayon,nomlivre,stoi(val));	
							AutoInterpret();      //Vérifier si un motif automatique doit être intégré aux canaux/msn					
						} else if(canaux[canpos].txt[1]=='c'){		//'c' pour "cut" -> descendre le canal dans la dernière ligne possible, en coupant en deux le canal qui l'occupe.
							//Crée deux nouvelles lignes, une pour le canal qui coupe et une pour le canal coupé
							mem.newline(mem.accesfrontline()); mem.newline(mem.accesfrontline());                   
							//Updater le correctif de décalage de la console par rapport à la mémoire
							if(base.refoule) base.consy++; else if(mem.accesfrontline()>=base.limtxty) {base.refoule = true; base.consy++;} 				
							if(base.refoule) base.consy++; else if(mem.accesfrontline()>=base.limtxty) {base.refoule = true; base.consy++;} 				
							//Sauter deux lignes dans la console
							if(base.refoule) {                         //La console est saturée: on pousse le texte vers le haut!
								chgcolcan();	//Mettre la bonne couleur					
								//Effacer toute les deux lignes avec des espaces (en "reléguant ce qui y était déjà vers le haut")
									base.curspos(0,mem.accesfrontline()-base.consy-1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
									base.curspos(0,mem.accesfrontline()-base.consy); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout ré-écrire la mémoire, mais une ligne plus haut
			    					base.curspos(0,0);   //Commencer en haut, puis descendre naturellement
									for(int county = base.consy; county <= mem.accesfrontline()-2; county++){             //base.consy : facteur de décalage de la console
										for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
									}	
								//Ré-écrire tous les msn
									chgcolmsn();	//Mettre la bonne couleur					
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) ReecrireMsn(countmsn);										      
							}	   	        
							//Updater les positions dans le canal actuel
							canaux[canpos].posx = -1;						//en x    //-1 est une position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
							canaux[canpos].posy = mem.accesfrontline()-1;			//en y 	
							//Updater les positions dans l'ancien canal de frontline
							for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {if(canaux[countcan].posy == mem.accesfrontline()-2) canaux[countcan].posy+=2;}
						} else if(canaux[canpos].txt[1]=='d'){      //'d' pour "délai" -> changer le délai entre chaque lettre, donc la vitesse de lecture
							int val = CodeSpecialExtractInt(canaux[canpos].txt,CodeSpecialLong);       //Extraire le temps entre les lettres		
							canaux[canpos].delay = val;													
						} else if(canaux[canpos].txt[1]=='f') {		//'f' pour "freeze" -> mettre en pause tous les canaux et msn, sauf celui-ci
							if(canaux[canpos].txt[2]=='1')	{		//FREEZE
								for(int countcan=0; countcan<canaux.longueur; countcan++) if(countcan!=canpos) {pausecan(countcan); canaux[countcan].frozen = true;}
								for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) {pausemsn(countmsn); messagerie[countmsn].frozen = true;}
							} else if(canaux[canpos].txt[2]=='0')	{		//UN-FREEZE
								for(int countcan=0; countcan<canaux.longueur; countcan++) if(countcan!=canpos) {unpausecan(countcan); canaux[countcan].frozen = false;}
								for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) {unpausemsn(countmsn); messagerie[countmsn].frozen = false;}
							}
						} else if(canaux[canpos].txt[1]=='g'){		//'g' pour "gender" -> choisir le bon accord   format: §gNomAGenrer(féminin;non binaire/neutre;masculin)§
							int genreselect;										 //Sélectionner le genre
								string NomAGenrer;
								int posSpecial = 2; if(canaux[canpos].txt[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
								while(posSpecial<CodeSpecialLong) {
									if(canaux[canpos].txt[posSpecial]=='~') {posSpecial++; break; 			//Sortir de la boucle si on a atteint la fin du Nom-À-Genrer           
									} else NomAGenrer += canaux[canpos].txt[posSpecial];
									posSpecial++;
								} 
								genreselect = biblio.acces(biblio.posgenre,ColNameFind(NomAGenrer,biblio.nomlivre[biblio.posgenre]));		//Le rayon "genre" de la bibliothèque contient le genre de tous les personnages (0 = féminin, 1 = non binaire, 2 = masculin)
							int genreactuel = 0;										//Aller chercher le bon accord
								int posdebut = posSpecial; int posfin = CodeSpecialLong - 2;		//Valeurs par défauts		//Code spécial Long -2 : pour ne pas avoir ")§" à la fin!
								while(posSpecial<CodeSpecialLong) {				 //Délimiter le bon accord				
									if(canaux[canpos].txt[posSpecial]==';') {
										genreactuel++;
										if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect+1) posfin = posSpecial - 1;
									}
									posSpecial++;
								}
							string temporairetxt;										//Ajouter le bon accord à la suite du code spécial 
								temporairetxt  += strintervalle(canaux[canpos].txt,0,CodeSpecialLong-1); 		//Ajouter le code spécial
								temporairetxt += strintervalle(canaux[canpos].txt,posdebut,posfin); 		//Ajouter le bon accord
								temporairetxt += strintervalle(canaux[canpos].txt,CodeSpecialLong,canaux[canpos].txt.length()-1);	//Ajouter le reste du texte	
								canaux[canpos].txt = temporairetxt;
						} else if(canaux[canpos].txt[1]=='m'){		//'m' pour "manuel" -> forcer l'intégration d'un motif manuel (quand ça fait trop longtemps qu'on attend pour une commande)
							string titremotif; 
							int posSpecial = 2; if(canaux[canpos].txt[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
							while(canaux[canpos].txt[posSpecial] != '§') titremotif += canaux[canpos].txt[posSpecial++];
							//Rechercher quel motif correspond à ce titre
							bool exacttrouve = false; int chapitrepos=0; int motifpos=0;
							bool exactmauvais = false; int titrepos = 0; int titrelong = titremotif.length();
							while(!exacttrouve&&chapitrepos<histoire.filmanu.longueur) {		//Pour chaque chapitre	
								if(histoire.cadenas[chapitrepos].eval(biblio)) {	
									while(!exacttrouve&&motifpos<histoire.filmanu[chapitrepos].longueur) {	//Pour chaque motif dans l'histoire
										if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)&&titrelong==histoire.filmanu[chapitrepos][motifpos].titre.length()) {
											exactmauvais = false; titrepos = 0;
											while(!exactmauvais&&titrepos<titrelong) if(titremotif[titrepos]!=histoire.filmanu[chapitrepos][motifpos].titre[titrepos]) exactmauvais = true; else titrepos++;
											if(titrepos==titrelong) exacttrouve = true; else motifpos++;			//Si on se rend jusque là, c'est qu'on a pas trouvé d'erreur									
										} else motifpos++;
									}
								if(!exacttrouve) chapitrepos++;
								} else chapitrepos++;
							}
							integrationmanu(chapitrepos,motifpos);			//Intégrer le motif
							if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);			//Ré-intégrer, au cas où le motif entrait en réserve					
						} else if(canaux[canpos].txt[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionné
							string canaloverr = strintervalle(canaux[canpos].txt,2,CodeSpecialLong-2);   //Obtenir le nom du canal à overrider
							overridecanal(ColNameFind(canaloverr,nomcanaux)); 						
						} else if(canaux[canpos].txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture		
							int val = CodeSpecialExtractInt(canaux[canpos].txt,CodeSpecialLong);       //Extraire le temps que durera la pause
							canaux[canpos].nxtt = clock.currentt + round(val * inp.vit);      //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					
						} else if(canaux[canpos].txt[1]=='r'){		//'r' pour "réserve" -> intégrer les motifs manuels qui attendent dans la réserve; sert à ne pas couper une phrase en deux
							if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);		
						} else if(canaux[canpos].txt[1]=='s'){		//'s' pour "skip" -> descendre le canal dans la dernière ligne possible, sans couper le canal qui l'occupe.
							//Crée une nouvelle ligne pour que le texte puisse vraiment descendre
							mem.newline(mem.accesfrontline());                   
							//Updater le correctif de décalage de la console par rapport à la mémoire
							if(base.refoule) base.consy++; else if(mem.accesfrontline()>=base.limtxty) {base.refoule = true; base.consy++;} 				
							//Sauter une ligne dans la console
							if(base.refoule) {                         //La console est saturée: on pousse le texte vers le haut!
								chgcolcan();	//Mettre la bonne couleur
								//Effacer toute la ligne avec des espaces (en "reléguant ce qui y était déjà vers le haut")
									base.curspos(0,mem.accesfrontline()-base.consy); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout ré-écrire, mais une ligne plus haut
			    					base.curspos(0,0);   //Commencer en haut, puis descendre naturellement
									for(int county = base.consy; county <= mem.accesfrontline()-1; county++){             //base.consy : facteur de décalage de la console
										for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
									}	
								//Ré-écrire tous les msn
									chgcolmsn();	//Mettre la bonne couleur								
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) ReecrireMsn(countmsn);										                 
							}	   	        
							//Updater les positions dans le canal actuel
							canaux[canpos].posx = -1;						//en x     //-1 est une position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
							canaux[canpos].posy = mem.accesfrontline();			//en y 	

						} else if(canaux[canpos].txt[1]=='t'){      //'t' pour "terminaison" -> changer le texte de terminaison, qui sera ajouté après chaque override (si du texte a effectivement été effacé)
							string nomcanal; string terminaison; 
							int posSpecial = 2; if(canaux[canpos].txt[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
							while(canaux[canpos].txt[posSpecial] != '¶') nomcanal += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(canaux[canpos].txt[posSpecial] != '§') terminaison += canaux[canpos].txt[posSpecial++];							
							canaux[ColNameFind(nomcanal,nomcanaux)].terminaison = terminaison;
						} else if(canaux[canpos].txt[1]=='z'){      //'z' pour ... rien, en fait. "menu" (mais 'm' était déjà pris) -> ouvrir le menu spécifié!
							string titremenu; 
							int posSpecial = 2; if(canaux[canpos].txt[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
							while(canaux[canpos].txt[posSpecial] != '§') titremenu += canaux[canpos].txt[posSpecial++];
							LireMenus(titremenu);
						}	
					//Effacer le code spécial du canal
					canaux[canpos].txt = strintervalle(canaux[canpos].txt,CodeSpecialLong,canaux[canpos].txt.length()-1);
				} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
					//Updater le "next time"
						canaux[canpos].nxtt = clock.currentt + round(canaux[canpos].delay * inp.vit);
					//Dealer avec la situation où on a à sauter une ligne (créer les lignes supplémentaires et updater les diverses positions)
						bool jump = false;
						if(canaux[canpos].txt[0]=='\n'|canaux[canpos].posx>=base.limtxtx-1) jump = true;     //base.limtxtx - 1 ; car c'est en integer, et canaux[canpos].posx commence à 0!
						if(jump) {	
							mem.newline(canaux[canpos].posy);                     //Introduit une nouvelle ligne à la suite de la position qui lui est fournie	
							//Updater le correctif de décalage de la console par rapport à la mémoire
							if(base.refoule) base.consy++; else if(mem.accesfrontline()>=base.limtxty) {base.refoule = true; base.consy++;} 				
							//Sauter une ligne dans la console
							if(!base.refoule) {          //La console n'est pas encore saturée: on pousse vers le bas!
								if(canaux[canpos].posy<mem.accesfrontline()) {                             //S'il y a d'autres lignes à repousser vers le bas
									//Ré-écrire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
										chgcolcan();	//Mettre la bonne couleur					
										base.curspos(0,canaux[canpos].posy+1);  //Mettre le curseur au début de la reconstruction
										for(int county = canaux[canpos].posy + 1 ; county <= mem.accesfrontline() ; county++) {   
											for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
										}
									//Ré-écrire tous les msn
										chgcolmsn();	//Mettre la bonne couleur									
										for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) ReecrireMsn(countmsn);	
								}
							} else {                         //La console est saturée: on pousse le texte vers le haut!
								chgcolcan();	//Mettre la bonne couleur					
								//Effacer toute la ligne avec des espaces (en "reléguant ce qui y était déjà vers le haut")								
									base.curspos(0,canaux[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout ré-écrire, mais une ligne plus haut
			    					base.curspos(0,0);   //Commencer en haut, puis descendre naturellement
									for(int county = base.consy; county <= canaux[canpos].posy; county++){             //base.consy : facteur de décalage de la console
										for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
									}				                 
								//Ré-écrire tous les msn
									chgcolmsn();	//Mettre la bonne couleur
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) ReecrireMsn(countmsn);		
							}	
							//Updater les positions dans les autres canaux    //Parce que leur position dans la mémoire a bougé //la position dans la console est quant à elle gérée par base.consy
							for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {
								if(countcan==canpos) continue;                                    //la mémoire refoule toujours vers le bas!
								if(canaux[countcan].posy > canaux[canpos].posy) canaux[countcan].posy++; else if(canaux[countcan].posy == canaux[canpos].posy) canaux[countcan].posy+=2;
							}       // == : Si deux canaux se situe sur la même ligne, le canal qui change de ligne va couper l'autre en deux, et le renvoyer après sa propre ligne.    	        
							//Updater les positions dans le canal actuel
							if(canaux[canpos].txt[0]=='\n') {canaux[canpos].posx = -1;} else canaux[canpos].posx = 0;			       //en x    
												//-1 est une position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
							canaux[canpos].posy++;	  																					   //en y 		
						} else {canaux[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
					//Inscrire le caractère       //À partir d'ici, les posx et posy sont la position du charactère actuel (dans la mémoire)!
					if(canaux[canpos].txt[0]!='\n') {
						chgcolcan();	//Mettre la bonne couleur
						if(canaux[canpos].posx==0){	if(canaux[canpos].alinea>0) {										//Mettre l'alinéa
							for(int alinpos=0; alinpos<canaux[canpos].alinea; alinpos++){
								if(msnmem.accescase(alinpos,canaux[canpos].posy-base.consy)) {base.curspos(alinpos,canaux[canpos].posy-base.consy) ; out(' ');}  //Inscrire dans la console seulement si la place n'est pas déjà prise par un msn
								mem.modif(alinpos,canaux[canpos].posy,' '); 		
								canaux[canpos].posx++;
							}
						}}
						//Inscrire le caractère dans la console seulement si la place n'est pas déjà prise par un msn
						if(msnmem.accescase(canaux[canpos].posx,canaux[canpos].posy-base.consy)) {base.curspos(canaux[canpos].posx,canaux[canpos].posy-base.consy) ; out(canaux[canpos].txt[0]);} 
						mem.modif(canaux[canpos].posx, canaux[canpos].posy, canaux[canpos].txt[0]);   //Inscrire le caractère dans la mémoire
					}	
					canaux[canpos].txt = strintervalle(canaux[canpos].txt,1,canaux[canpos].txt.length()-1);       //Effacer le caractère du canal     	   
				}
				if(canaux[canpos].txt.length()==0) canaux[canpos].actif = false;			//Vérifier s'il reste toujours du texte à passer dans le canal
			}}
		}	
				
		//b) Fonction LireMessagerie()
		void univers::LireMessagerie() {
			//Lire toutes les messageries, si elles sont prêtes
			for(int msnpos=0; msnpos<messagerie.longueur; msnpos++) {if(messagerie[msnpos].nxtt<clock.currentt&&(!messagerie[msnpos].pause)) {	
				//Créer un raccourci pour la position du texte à lire
				int posrc = messagerie[msnpos].postxt;		//rc pour raccourci
				//Interpréter les "codes spéciaux" (§...§)
				if(messagerie[msnpos].txt[posrc]=='§'){
					if(messagerie[msnpos].construire) {
						//Créer un raccourci du texte à lire à partir du code spécial
						string txtrc = strintervalle(messagerie[msnpos].txt,posrc,messagerie[msnpos].txt.length()-1);
						//Déterminer la longueur du code spécial
						int CodeSpecialLong = CodeSpecialLongueur(txtrc);			
						//Lire le code spécial	
							if(txtrc[1]=='a'){		//'a' pour "automatique" -> marquer le motif automatique comme n'étant plus en cours			
								string poschap; string posmotif;
								int posSpecial = 2;
								while(txtrc[posSpecial] != ';') poschap += txtrc[posSpecial++]; 
								posSpecial++; while(txtrc[posSpecial] != '§') posmotif += txtrc[posSpecial++];
								histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //Désigner le motif signalé comme n'étant plus en cours						
							} else if(txtrc[1]=='b'){		//'b' pour "biblio" -> modifier la bibliothèque
								string nomrayon; string nomlivre; string val;
								int posSpecial = 2; if(txtrc[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
								while(txtrc[posSpecial] != '¶') nomrayon += txtrc[posSpecial++]; 
								posSpecial++; while(!(txtrc[posSpecial] == '~' && txtrc[posSpecial+1] == '>')) nomlivre += txtrc[posSpecial++];
								posSpecial+=2; while(txtrc[posSpecial] != '§') val += txtrc[posSpecial++];							
								biblio.modif(nomrayon,nomlivre,stoi(val));	
								AutoInterpret();      //Vérifier si un motif automatique doit être intégré aux canaux/msn							
							} else if(txtrc[1]=='d'){      //'d' pour "délai" -> changer le délai entre chaque lettre, donc la vitesse de lecture
								int val = CodeSpecialExtractInt(txtrc,CodeSpecialLong);       //Extraire le temps entre les lettres		
								messagerie[msnpos].delay = val;			
							} else if(txtrc[1]=='f') {		//'f' pour "freeze" -> mettre en pause tous les canaux et msn, sauf celui-ci
								if(txtrc[2]=='1'){				//FREEZE
									for(int countcan=0; countcan<canaux.longueur; countcan++) {pausecan(countcan); canaux[countcan].frozen = true;}												
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) {pausemsn(countmsn);	messagerie[countmsn].frozen = true;}
								} else if(txtrc[2]=='0'){		//UN-FREEZE
									for(int countcan=0; countcan<canaux.longueur; countcan++) {unpausecan(countcan); canaux[countcan].frozen = false;}
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) {unpausemsn(countmsn); messagerie[countmsn].frozen = false;}
								}
							} else if(txtrc[1]=='g'){		//'g' pour "gender" -> choisir le bon accord   format: §gNomAGenrer(féminin;non binaire/neutre;masculin)§
								int genreselect;										 //Sélectionner le genre
									string NomAGenrer;
									int posSpecial = 2; if(txtrc[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
									while(posSpecial<CodeSpecialLong) {
										if(txtrc[posSpecial]=='~') {posSpecial++; break; 			//Sortir de la boucle si on a atteint la fin du Nom-À-Genrer           
										} else NomAGenrer += txtrc[posSpecial];
										posSpecial++;
									} 
									genreselect = biblio.acces(biblio.posgenre,ColNameFind(NomAGenrer,biblio.nomlivre[biblio.posgenre]));		//Le rayon "genre" de la bibliothèque contient le genre de tous les personnages (0 = féminin, 1 = non binaire, 2 = masculin)
								int genreactuel = 0;										//Aller chercher le bon accord
									int posdebut = posSpecial; int posfin = CodeSpecialLong - 2;		//Valeurs par défauts		//Code spécial Long -2 : pour ne pas avoir ")§" à la fin!
									while(posSpecial<CodeSpecialLong) {				 //Délimiter le bon accord				
										if(txtrc[posSpecial]==';') {
											genreactuel++;
											if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect+1) posfin = posSpecial - 1;
										}
										posSpecial++;
									}
								string temporairetxt;										//Ajouter le bon accord à la place du code spécial dans le texte à lire
									temporairetxt += strintervalle(messagerie[msnpos].txt, 0, posrc);	//Ajouter le texte avant le code spécial
									temporairetxt += strintervalle(txtrc, posdebut, posfin);			//Ajouter le bon accord
									temporairetxt += strintervalle(txtrc,CodeSpecialLong,messagerie[msnpos].txt.length()-1);				//Ajouter le reste du texte
									messagerie[msnpos].txt = temporairetxt;
									messagerie[msnpos].postxt -= (CodeSpecialLong);					//Neutraliser l'avancement de la position qui va venir après, puisqu'on a supprimé le code spécial
							} else if(txtrc[1]=='m'){		//'m' pour "manuel" -> forcer l'intégration d'un motif manuel (quand ça fait trop longtemps qu'on attend pour une commande)
								string titremotif; 
								int posSpecial = 2; if(txtrc[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
								while(txtrc[posSpecial] != '§') titremotif += txtrc[posSpecial++];
								//Rechercher quel motif correspond à ce titre
								bool exacttrouve = false; int chapitrepos=0; int motifpos=0;
								bool exactmauvais = false; int titrepos = 0; int titrelong = titremotif.length();
								while(!exacttrouve&&chapitrepos<histoire.filmanu.longueur) {		//Pour chaque chapitre	
									if(histoire.cadenas[chapitrepos].eval(biblio)) {	
										while(!exacttrouve&&motifpos<histoire.filmanu[chapitrepos].longueur) {	//Pour chaque motif dans l'histoire
											if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)&&titrelong==histoire.filmanu[chapitrepos][motifpos].titre.length()) {
												exactmauvais = false; titrepos = 0;
												while(!exactmauvais&&titrepos<titrelong) if(titremotif[titrepos]!=histoire.filmanu[chapitrepos][motifpos].titre[titrepos]) exactmauvais = true; else titrepos++;
												if(titrepos==titrelong) exacttrouve = true; else motifpos++;			//Si on se rend jusque là, c'est qu'on a pas trouvé d'erreur									
											} else motifpos++;
										}
									if(!exacttrouve) chapitrepos++;
									} else chapitrepos++;
								}
								integrationmanu(chapitrepos,motifpos);			//Intégrer le motif
								if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);			//Ré-intégrer, au cas où le motif entrait en réserve																
							} else if(txtrc[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture		
								double val = CodeSpecialExtractInt(txtrc,CodeSpecialLong);       //Extraire le temps que durera la pause
								messagerie[msnpos].nxtt = clock.currentt + round(val * inp.vit);     //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					
							} else if(txtrc[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionné
								string canaloverr = strintervalle(txtrc,2,CodeSpecialLong-2);   //Obtenir le nom du canal à overrider
								overridecanal(ColNameFind(canaloverr,nomcanaux)); 																
							} else if(txtrc[1]=='r'){		//'r' pour "réserve" -> intégrer les motifs manuels qui attendent dans la réserve; sert à ne pas couper une phrase en deux
								if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);									
							} else if(txtrc[1]=='t'){      //'t' pour "terminaison" -> changer le texte de terminaison, qui sera ajouté après chaque override (si du texte a effectivement été effacé)
								string nomcanal; string terminaison; int posSpecial = 2;
								while(txtrc[posSpecial] != '¶') nomcanal += txtrc[posSpecial++]; 
								posSpecial++; while(txtrc[posSpecial] != '§') terminaison += txtrc[posSpecial++];							
								canaux[ColNameFind(nomcanal,nomcanaux)].terminaison = terminaison;
							} else if(txtrc[1]=='z'){      //'z' pour ... rien, en fait. "menu" (mais 'm' était déjà pris) -> ouvrir le menu spécifié!
								string titremenu; 
								int posSpecial = 2; if(txtrc[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
								while(txtrc[posSpecial] != '§') titremenu += txtrc[posSpecial++];
								LireMenus(titremenu);
							}		
						//Passer à la prochaine position du texte à lire
						messagerie[msnpos].postxt += (CodeSpecialLong);
					} else 	messagerie[msnpos].postxt -= CodeSpecialLongueurInv(strintervalle(messagerie[msnpos].txt,0,posrc));		//Si le msn est en déconstruction 			
				} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
					//Updater le "next time"
						if(messagerie[msnpos].construire) {messagerie[msnpos].nxtt = clock.currentt + round(messagerie[msnpos].delay * inp.vit);
						} else messagerie[msnpos].nxtt = clock.currentt + round((messagerie[msnpos].delay * inp.vit)*messagerie[msnpos].postxt/messagerie[msnpos].txt.length() );	//Ça s'efface de plus en plus vite (mais pas trop)!
					//Dealer avec les sauts de lignes
						if(messagerie[msnpos].construire) {			//Si on est en train d'écrire
							bool jump = false;
							if(messagerie[msnpos].posx>=base.limtxtx-1) {messagerie[msnpos].posx = -1; jump = true;}
							if(messagerie[msnpos].txt[posrc]=='\n') {jump = true;}
							if(jump||messagerie[msnpos].attente) {
								bool sautdelignereussi = false;
								//Vérifier si le changement de ligne empiète sur un autre msn ou sur la ligne de commandes (située à limtxty)
								if(messagerie[msnpos].posy==base.limtxty||!msnmem.accesligne(messagerie[msnpos].posy+1)){
									//Vérifier s'il y a de l'espace pour refouler vers le bas
									bool refoulebaspossible = false; int poslibrebas;
									for(int countligne=messagerie[msnpos].posy; countligne<base.limtxty; countligne++) if(msnmem.accesligne(countligne)) {refoulebaspossible = true; poslibrebas = countligne; break;}
									if(refoulebaspossible) {
										//Refouler jusqu'à atteindre la position libre (peut conduire à réaction en chaîne)
										int posrefoule = messagerie[msnpos].posy + 1;
										int msnrefoule;
										while(posrefoule<poslibrebas) {
											//Trouver quel msn refouler vers le bas
											for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(posrefoule==messagerie[countmsn].posdeby) {msnrefoule = countmsn; break;}
											//Ré-écrire le msn, mais une ligne plus bas
											messagerie[msnrefoule].posdeby++; messagerie[msnrefoule].posy++;		//descendre ses positions en y d'une ligne
											ReecrireMsn(msnrefoule);					//Ré-écrire le msn, maintenant une ligne plus bas
											posrefoule += messagerie[msnrefoule].nbysupp + 1;		//Passer à l'espace juste après ce msn 
										}
										sautdelignereussi = true;
										msnmem.modifligne(poslibrebas, false);		//Marquer la ligne comme maintenant occupée
									} else {	//Il n'y a pas d'espace pour refouler vers le bas: vérifier s'il est possible de refouler vers le haut
										bool refoulehautpossible = false; int poslibrehaut;
										for(int countligne=messagerie[msnpos].posy; countligne>=0; countligne--) if(msnmem.accesligne(countligne)) {refoulebaspossible = true; poslibrehaut = countligne; break;}
										if(refoulehautpossible){
											//Refouler jusqu'à atteindre la position libre (peut conduire à réaction en chaîne)
											int posrefoule = messagerie[msnpos].posy;			//Oui, ça désigne le msn à [msnpos] comme le premier à être refoulé; c'est normal.
											int msnrefoule;
											while(posrefoule>poslibrehaut) {
												//Trouver quel msn refouler vers le haut
												for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(posrefoule==messagerie[countmsn].posdeby+messagerie[countmsn].nbysupp) {msnrefoule = countmsn; break;}
												//Ré-écrire le msn, mais une ligne plus haut
												messagerie[msnrefoule].posdeby--; messagerie[msnrefoule].posy--;		//monter ses positions en y d'une ligne
												ReecrireMsn(msnrefoule);					//Ré-écrire le msn, maintenant une ligne plus haut
												posrefoule -= messagerie[msnrefoule].nbysupp + 1;		//Passer à l'espace juste après ce msn 
											}
											sautdelignereussi = true;			
											msnmem.modifligne(poslibrehaut, false);	//Marquer la ligne comme maintenant occupée					
										} else {	//Il n'y a pas d'espace pour refouler, ni vers le bas ni vers le haut : attendre qu'il s'en libère
											messagerie[msnpos].attente = true;
											//Vérifier si tous les msn sont en attente
											bool attentepossible = false;
											for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(!messagerie[msnpos].pause&&!messagerie[countmsn].attente) {attentepossible = true; break;}
											if(!attentepossible) {	//Tous les msn sont en attente qu'une ligne se libère : forcer celui qui est le plus près de la fin à terminer prématurément
												//Trouver quel msn est le plus près de la fin
												int mintxt = messagerie[msnpos].txt.length() - messagerie[msnpos].postxt;
												int msnoverr;
												for(int countmsn=0; countmsn<messagerie.longueur;countmsn++) {	//Si plusieurs msn ont le même nombre de caractères restant, le dernier dans la liste l'emporte
													if((messagerie[countmsn].txt.length()-messagerie[countmsn].postxt)<=mintxt) {
														mintxt = messagerie[countmsn].txt.length()-messagerie[countmsn].postxt; msnoverr = countmsn;	
													}
												}
												//Activer les codes spéciaux restants s'ils modifient la bibliothèque
												int counttxt=messagerie[msnoverr].postxt;
												while(counttxt<messagerie[msnoverr].txt.length()){
													if(messagerie[msnpos].txt[counttxt]=='§'){
														//Créer un raccourci pour la position du texte à lire
														string txtrc = strintervalle(messagerie[msnpos].txt,counttxt,messagerie[msnpos].txt.length()-1); //Créer un raccourci du texte à lire à partir du code spécial												
														int CodeSpecialLong = CodeSpecialLongueur(txtrc);	//Déterminer la longueur du code spécial		
														if(txtrc[1]=='a'){		//'a' pour "automatique" -> marquer le motif automatique comme n'étant plus en cours			
															string poschap; string posmotif;
															int posSpecial = 2;
															while(txtrc[posSpecial] != ';') poschap += txtrc[posSpecial++]; 
															posSpecial++; while(txtrc[posSpecial] != '§') posmotif += txtrc[posSpecial++];
															histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //Désigner le motif signalé comme n'étant plus en cours
														} else if(txtrc[1]=='b'){		//'b' pour "biblio" -> modifier la bibliothèque
															string nomrayon; string nomlivre; string val;
															int posSpecial = 2; if(txtrc[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
															while(txtrc[posSpecial] != '¶') nomrayon += txtrc[posSpecial++]; 
															posSpecial++; while(!(txtrc[posSpecial] == '~' && txtrc[posSpecial+1] == '>')) nomlivre += txtrc[posSpecial++];
															posSpecial+=2; while(txtrc[posSpecial] != '§') val += txtrc[posSpecial++];							
															biblio.modif(nomrayon,nomlivre,stoi(val));	
															AutoInterpret();      //Vérifier si un motif automatique doit être intégré aux canaux/msn	
														} else if(txtrc[1]=='f') {		//'f' pour "freeze" -> mettre en pause tous les canaux et msn, sauf celui-ci
															if(txtrc[2]=='1'){				//FREEZE
																for(int countcan=0; countcan<canaux.longueur; countcan++) {pausecan(countcan); canaux[countcan].frozen = true;}
																for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) {pausemsn(countmsn); messagerie[countmsn].frozen = true;}
															} else if(txtrc[2]=='0'){		//UN-FREEZE
																for(int countcan=0; countcan<canaux.longueur; countcan++) {unpausecan(countcan); canaux[countcan].frozen = false;}
																for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) {unpausemsn(countmsn); messagerie[countmsn].frozen = false;}
															}
														} else if(txtrc[1]=='m'){		//'m' pour "manuel" -> forcer l'intégration d'un motif manuel (quand ça fait trop longtemps qu'on attend pour une commande)
															string titremotif; 
															int posSpecial = 2; if(txtrc[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
															while(txtrc[posSpecial] != '§') titremotif += txtrc[posSpecial++];
															//Rechercher quel motif correspond à ce titre
															bool exacttrouve = false; int chapitrepos=0; int motifpos=0;
															bool exactmauvais = false; int titrepos = 0; int titrelong = titremotif.length();
															while(!exacttrouve&&chapitrepos<histoire.filmanu.longueur) {		//Pour chaque chapitre	
																if(histoire.cadenas[chapitrepos].eval(biblio)) {	
																	while(!exacttrouve&&motifpos<histoire.filmanu[chapitrepos].longueur) {	//Pour chaque motif dans l'histoire
																		if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)&&titrelong==histoire.filmanu[chapitrepos][motifpos].titre.length()) {
																			exactmauvais = false; titrepos = 0;
																			while(!exactmauvais&&titrepos<titrelong) if(titremotif[titrepos]!=histoire.filmanu[chapitrepos][motifpos].titre[titrepos]) exactmauvais = true; else titrepos++;
																			if(titrepos==titrelong) exacttrouve = true; else motifpos++;			//Si on se rend jusque là, c'est qu'on a pas trouvé d'erreur									
																		} else motifpos++;
																	}
																if(!exacttrouve) chapitrepos++;
																} else chapitrepos++;
															}
															integrationmanu(chapitrepos,motifpos);			//Intégrer le motif
															if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);			//Ré-intégrer, au cas où le motif entrait en réserve	
														} else if(txtrc[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionné
															string canaloverr = strintervalle(txtrc,2,CodeSpecialLong-1);   //Obtenir le nom du canal à overrider
															overridecanal(ColNameFind(canaloverr,nomcanaux)); 																
														} else if(txtrc[1]=='r'){		//'r' pour "réserve" -> intégrer les motifs manuels qui attendent dans la réserve; sert à ne pas couper une phrase en deux
															if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);																										
														} else if(txtrc[1]=='z'){      //'z' pour ... rien, en fait. "menu" (mais 'm' était déjà pris) -> ouvrir le menu spécifié!
															string titremenu; 
															int posSpecial = 2; if(txtrc[2]==' ') posSpecial = 3;		//Ignorer l'espace du début
															while(txtrc[posSpecial] != '§') titremenu += txtrc[posSpecial++];
															LireMenus(titremenu);
														}																
													} else counttxt++;
												}
												//Mettre le msn en "déconstruction"
												messagerie[msnoverr].construire = false; messagerie[msnoverr].attente = false; messagerie[msnoverr].pause = false;
											}
										}
									}
								} else {sautdelignereussi = true; msnmem.modifligne(messagerie[msnpos].posy, false);}	//Si l'on ne refoule pas, passer simplement à la prochaine ligne
								if(sautdelignereussi) {
									messagerie[msnpos].posy++;		
									messagerie[msnpos].nbysupp++;		//le msn occupe une ligne de plus à partir de sa ligne de départ
									if(messagerie[msnpos].attente) messagerie[msnpos].attente = false;		//Enlever l'attente, puisqu'on a réussi à atteindre une position libre
								}
							}
						} else {									//Si on est en train d'effacer
							if(messagerie[msnpos].posx==0) {messagerie[msnpos].posy--; messagerie[msnpos].posx = base.limtxtx;}
							if(messagerie[msnpos].txt[posrc]=='\n') messagerie[msnpos].posy--;					
						}								
					if(!messagerie[msnpos].attente){		//Si le msn n'est pas en attente, inscrire simplement le caractère
						//Updater le posx
						if(messagerie[msnpos].construire) messagerie[msnpos].posx++; else messagerie[msnpos].posx--;		
						//Inscrire le caractère       //À partir d'ici, les posx et posy sont la position du caractère actuel!
						if(messagerie[msnpos].txt[posrc]!='\n') {
							if(messagerie[msnpos].construire) {			//Si on est en train d'écrire							
								chgcolmsn();	//Mettre la bonne couleur
								base.curspos(messagerie[msnpos].posx,messagerie[msnpos].posy); out(messagerie[msnpos].txt[posrc]);	//Inscrire le caractère dans la console
								msnmem.modifcase(messagerie[msnpos].posx, messagerie[msnpos].posy, false); 						//Noter que la position est prise par un msn				
							} else {									//Si on est en train d'effacer
								chgcolcan();	//Mettre la bonne couleur
								base.curspos(messagerie[msnpos].posx,messagerie[msnpos].posy); out(mem.acces(messagerie[msnpos].posx,messagerie[msnpos].posy+base.consy));     //Remettre la console comme elle était
								msnmem.modifcase(messagerie[msnpos].posx, messagerie[msnpos].posy, true); 						//Noter que la position est maintenant libre															
							}
						}	
						if(messagerie[msnpos].construire) messagerie[msnpos].postxt++; else messagerie[msnpos].postxt--;       //Passer à la prochaine position du texte à lire	   
					}	
				}
				if(messagerie[msnpos].construire&&messagerie[msnpos].postxt==messagerie[msnpos].txt.length()) {			//Vérifier s'il reste toujours du texte à lire		
					messagerie[msnpos].construire = false; 
					//Replacer les compteurs pour repartir à la bonne place
					messagerie[msnpos].postxt--; messagerie[msnpos].posx++;		//on fait posx++, pour être à la "position précédente", mais à l'envers (genre plus à droite de ce qui va être effacé à un moment donné)										
				} else if(!messagerie[msnpos].construire&&messagerie[msnpos].postxt<0) {		//Vérifier s'il reste toujours du texte à effacer
					for(int countsupp=1; countsupp<=messagerie[msnpos].nbysupp; countsupp++) msnmem.modifligne(messagerie[msnpos].posdeby+countsupp,true);	//Libérer les lignes dans la mémoire
					messagerie.supprposition(msnpos);	//"Supprimer" le msn
				}
			}}
		}	
								
          
	//iv) Fonctions pour recevoir et interpréter les commandes de la joueuse	----------------------------------------------------------------------		
                  
		//a) Fonction : UserInputInterpret ; vérifie si la commande entrée correspond à une des actions actuellement autorisée
			void univers::UserInputInterpret() {
				//Créer des compteurs
				StaticVect<int,20> bonchapitre;	  //Créer des StaticVect pour noter la position des motifs qui correspondent à la commande
				StaticVect<int,20> bonmotif;											//Taille arbitraire de 20; j'espère qu'aucune commande n'appelera simultannément 20 maillons
				StaticVect<bool,taillegroupes> groupebon; 	   	 //Créer un StaticVect pour noter si chaque groupe de mot est bon
				int diffpos; bool exactbon; int commpos; bool exactmauvais; 	//Créer les compteurs pour les expressions exactes
				int groupepos; int synpos; int motpos; int precedpos; bool inclusbon; bool exclusbon;	//Créer les compteurs pour les mots à inclure/exclure	
				//Pour chaque chapitre
				for(int chapitrepos=0; chapitrepos<histoire.filmanu.longueur; chapitrepos++) if(histoire.cadenas[chapitrepos].eval(biblio)) {			
					//Pour chaque motif dans l'histoire
					for(int motifpos=0; motifpos<histoire.filmanu[chapitrepos].longueur; motifpos++) if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)) {
						//Passer d'abord les commandes exactes, pour voir si elles correspondent
							diffpos = 0; exactbon = false;
							while(diffpos<histoire.filmanu[chapitrepos][motifpos].commandes.exact.longueur&&!exactbon) {
								commpos = 0; exactmauvais = false;
								while(!exactmauvais&&commpos<inp.commande.longueur) {if(inp.commande[commpos]!=histoire.filmanu[chapitrepos][motifpos].commandes.exact[diffpos][commpos]) exactmauvais = true; else commpos++;}	
								if(exactmauvais==false) exactbon = true; else diffpos++;
							}
							if(exactbon)	{         //Intégrer tout de suite le bon motif dans le canal					
								inp.accepted = true;	//Envoyer le bon message au gestionnaire d'Input				
								integrationmanu(chapitrepos,motifpos); return;            //Intégrer le bon motif dans le canal
							}   
						//Passer maintenant aux mots-clés	
						inclusbon = false; diffpos = 0;
						//Cas spécial: Aucun mot exact ni mot-clé à inclure fourni, mais des mots à éviter: accepter n'importe quand, tant que l'interdit n'est pas présent
						if(histoire.filmanu[chapitrepos][motifpos].commandes.inclus.longueur==0&&histoire.filmanu[chapitrepos][motifpos].commandes.exact.longueur==0) {
							//Vérifier si les mots à être exclus sont absents		
							while(diffpos<histoire.filmanu[chapitrepos][motifpos].commandes.exclus.longueur&&!exclusbon) {	
								synpos=0; exclusbon = true;
								//Pour chaque synonyme
								while(synpos<histoire.filmanu[chapitrepos][motifpos].commandes.exclus[diffpos].longueur&&exclusbon) {
									commpos = 0;
									motpos = 0;
									//Pour chaque lettre
									while(commpos<inp.commande.longueur&&exclusbon) {		//Si le mot est retrouvé, la commande ne correspond pas au motif																			
										if(inp.commande[commpos++]==histoire.filmanu[chapitrepos][motifpos].commandes.exclus[diffpos][synpos][motpos++]) {
											if(motpos==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][synpos].longueur) exclusbon = false; inclusbon = false;	
										} else motpos = 0;
									}
									synpos++;
								}
								diffpos++;
							}
							if(exclusbon) {bonchapitre.ajout(chapitrepos); bonmotif.ajout(motifpos);}						
						} else {
						//Mots-clés à inclure	
						 	//Pour chaque façon différente de dire la commande
							while(diffpos<histoire.filmanu[chapitrepos][motifpos].commandes.inclus.longueur&&!(inclusbon&&exclusbon)) {
								//Vérifier si les mots à être inclus sont présents
									groupepos = 0;  precedpos = 0;   														//Remettre tous les groupes de mots comme incorrects jusqu'à preuve du contraire
									groupebon.remplacement(false); for(int clearpos=1; clearpos<histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos].longueur; clearpos++) groupebon.ajout(false); 
									//Pour chaque groupe de mots
									while(groupepos<histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos].longueur) {    
										synpos=0;
										//Pour chaque synonyme
										while(synpos<histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos].longueur&&!groupebon[groupepos]) {		
											commpos = precedpos;
											motpos = 0;
											//Pour chaque lettre
											while(commpos<inp.commande.longueur&&!groupebon[groupepos]) {						//DONC, ICI, L'ORDRE EST IMPORTANT DANS LA COMMANDE. PARCE QU'ON PART DE LA POSITION PRÉCÉDENTE. CHANGER ÇA? GARDER ÇA?	
												//PUISQUE L'ORDRE EST IMPORTANT, LA CONVERSION EN MAJUSCULE NE SERA EFFECTUÉE QUE POUR LE PREMIER GROUPE DE MOT (ET POUR LA PREMIÈRE LETTRE DE LA COMMANDE)
												if(commpos==0&&groupepos==0&&motpos==0)	{			//Première lettre de la commande
													if(inp.commande[commpos]==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos][motpos]||inp.commande[commpos]==majuscule(histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos][motpos])) {
													commpos++; motpos++; if(motpos==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos].length()) {groupebon[groupepos] = true; precedpos = commpos;}	
													} else {commpos++;}
												} else {                 //Toutes autres lettres																	
													if(inp.commande[commpos++]==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos][motpos++]) {
														if(motpos==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos].length()) {groupebon[groupepos] = true; precedpos = commpos;}
													} else motpos = 0;
												}
											}
											synpos++;
										}
										groupepos++;					
									}	
									//Maintenant, on a l'information sur quel groupe de mots, dans l'intervalle [0,longueur_de_cette_differente_façon], a un membre qui est présent dans la commande.
									groupepos=0 ; while(groupebon[groupepos++]) if(groupepos==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos].longueur) inclusbon = true;
								if(inclusbon) {
								//Vérifier si les mots à être exclus sont absents
									synpos=0; exclusbon = true;
									//Pour chaque synonyme
									while(synpos<histoire.filmanu[chapitrepos][motifpos].commandes.exclus[diffpos].longueur&&exclusbon) {
										commpos = 0;
										motpos = 0;
										//Pour chaque lettre
										while(commpos<inp.commande.longueur&&exclusbon) {		//Si le mot est retrouvé, la commande ne correspond pas au motif																			
											if(inp.commande[commpos++]==histoire.filmanu[chapitrepos][motifpos].commandes.exclus[diffpos][synpos][motpos++]) {
												if(motpos==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][synpos].longueur) exclusbon = false; inclusbon = false;	
											} else motpos = 0;
										}
										synpos++;
									}
								}
								diffpos++;
							}
							if(inclusbon&&exclusbon) {bonchapitre.ajout(chapitrepos); bonmotif.ajout(motifpos);}	
						}
					}
				}
				//Maintenant, on a l'information sur quels motifs correspondent (sans expression exacte) à la commande
				if(bonmotif.longueur==0) {
					inp.accepted = false; 			
					return;
				} else if(bonmotif.longueur==1) {	
					inp.accepted = true;	//Envoyer le bon message au gestionnaire d'Input					
					integrationmanu(bonchapitre[0],bonmotif[0]); return;            //Intégrer le bon motif dans le canal
				} else {
					//Déterminer si la commande correspond au titre d'un canal
					int bonpos = 0; exactbon = false; 
					while(bonpos<bonmotif.longueur&&!exactbon) {
						exactmauvais = false; commpos = 0;
							while(!exactmauvais&&commpos<inp.commande.longueur) {if(inp.commande[commpos]!=histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre[commpos]) exactmauvais = true; else commpos++;}	
							if(exactmauvais==false) {
								exactbon = true; 	
								inp.accepted = true;							
								integrationmanu(bonchapitre[bonpos],bonmotif[bonpos]); return;}            //Intégrer tout de suite le bon motif dans le canal	
					}	
					//Si l'ambiguité demeure : les commandes sont mal écrites;
					
								//DÉCIDER QUOI FAIRE DANS CE CAS!
								
									//INTÉGRER UN MSN CUSTOM (genre qui vient vraiment avec la base, et qui dit simplement que le code a été mal fait, et que "commande"
									// pouvait dire "", "", ou ""?)
									
									//SIMPLEMENT REFUSER (c'est ça qui arrive présentement)?
									
					inp.accepted = false; return;				
				}
			}        

		//b) Fonction UserInput()				//Enregistre quelle touche est pressée et sauvegarde la commande actuelle
		void univers::UserInput() {
			if(_kbhit()){
			//i) Capter la lettre tapée
			bool enter = false;
			char charkey; int intkey = _getch();                  		//Enregistrer quelle touche a été pressée
					if (intkey == 0 || intkey == -32 || intkey == 224) {      //La valeur est spéciale: elle nécessite de la ré-examiner
						intkey = _getch();                              //Examiner une deuxième valeur pour identifier
						if(intkey == 75) {     								 				 	//flèche gauche : reculer dans la commande tapée 
							if(inp.inputpos!=0) {
								if(inp.inputpos!=inp.commande.longueur) {
									base.curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
								}          //Remettre en gris la position précédente
								inp.inputpos--;  
							}
						}
						else if (intkey == 77) {											 	 //flèche droite : avancer dans la commande tapée				
							if(inp.inputpos!=inp.commande.longueur) {
								base.curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
								inp.inputpos++;		
							}			//Remettre en gris la position précédente
						} 
						else if (intkey == 72) {									  			 //Flèche du haut : accélérer la vitesse de défilement
							if(inp.vit > 0.25) {
								if(inp.vit >= 0.5) {
									if(inp.vit >= 1) {
										if(inp.vit >= 2) {
											inp.vit -= 0.2; 
										}else inp.vit -= 0.1;	
									} else inp.vit -= 0.05;
								} else inp.vit -= 0.025;						
							}
						}
						else if (intkey == 80) {									  			 //Flèche du bas : rallentir la vitesse de défilement
							if(inp.vit < 4) {
								if(inp.vit < 2) {
									if(inp.vit < 1) {
										if(inp.vit < 0.5) {
											inp.vit += 0.025;
										} else inp.vit += 0.05; 									
									} else inp.vit += 0.1; 
								} else inp.vit += 0.2;	
							}
						}				 
						else if (intkey == 83) {                                                //Delete : supprimer un caractère de la commande actuelle
							if(inp.inputpos!=inp.commande.longueur) {
								inp.commande.supprposition(inp.inputpos);    
								base.curspos(inp.inputpos,base.limtxty);
								for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);    
								out(' ');
							}
						}
					} else 	{                                        //La valeur est "normale"
						//Touches-fonctions
						if(intkey == 27) {														 //Escape : appeler le menu de pause (ou ferme le programme - ça, c'est l'option par défaut (quelmenuingameescape = "")) 
							if(quelmenuingameescape.length()==0) abort();
							pauseall();
							LireMenus(quelmenuingameescape);
						} else if(intkey == 13) {												 //Enter : envoyer la commande
							enter = true;
						} else if(intkey == 8) {                                                //Backspace : supprimer le caractère précédent
							if(inp.inputpos!=0) {
								inp.inputpos--;
								inp.commande.supprposition(inp.inputpos);   
								base.curspos(inp.inputpos,base.limtxty);
								for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);   
								out(' ');    					
							}				
						} else {							//Caractère non ASCII
							if(intkey==183) charkey = 'À'; else if(intkey==133) charkey = 'à'; else if(intkey==128) charkey = 'Ç'; else if(intkey==135) {charkey = 'ç';
							} else if(intkey==144) charkey = 'É'; else if(intkey==130) charkey = 'é'; else if(intkey==212) charkey = 'È'; else if(intkey==138) {charkey = 'è';
							} else if(intkey==210) charkey = 'Ê'; else if(intkey==136) charkey = 'ê'; else if(intkey==215) charkey = 'Î'; else if(intkey==140) {charkey = 'î';
							} else if(intkey==216) charkey = 'Ï'; else if(intkey==139) charkey = 'ï'; else if(intkey==226) charkey = 'Ô'; else if(intkey==147) {charkey = 'ô';
							} else if(intkey==235) charkey = 'Ù'; else if(intkey==151) charkey = 'ù'; else if(intkey==234) charkey = 'Û'; else if(intkey==150) {charkey = 'û';
							} else charkey = intkey;		//Caractère ASCII		 
						//Caractère normal : l'ajouter à la commande	
							if(inp.commande.longueur<base.limtxtx-1){
								inp.commande.ajout(charkey,inp.inputpos);
								inp.inputpos++;
								chgcolcommande();	//Mettre la bonne couleur
								base.curspos(inp.inputpos-1,base.limtxty);	                    
								for(int pos=inp.inputpos-1; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);
								if(inp.commande.longueur==inpecho.commande.fin) inpecho.actif = false;                   //Désactiver le canal d'écho si la commande actuelle le dépasse
							}
						}
					}	
				//Remettre la lettre sélectionnée en surbrillance
				if(inp.inputpos!=inp.commande.longueur) {base.chgcol(biblio.acces(biblio.poscouleur,"commpostxt"),biblio.acces(biblio.poscouleur,"commposbg"));  base.curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); base.chgcol(biblio.acces(biblio.poscouleur,"actutxt"),biblio.acces(biblio.poscouleur,"actubg"));}
				//Évaluer la commande		
				if(enter) {
					bool dejareserve = false;
					if(inp.reserve) dejareserve = true; else UserInputInterpret();		//Interpréter la commande seulement s'il n'y a pas déjà un motif en réserve
					inpecho.commande.remplacement(inp.commande);						
					inpecho.actif = true; inpecho.nxtt = clock.currentt;          							 //Mettre à l'heure le "nexttime"					
					if(dejareserve)	{		//Faire clignoter le texte lentement pendant quelques secondes
							inpecho.txtcol = biblio.acces(biblio.poscouleur,"commbusytxt"); inpecho.bgcol = biblio.acces(biblio.poscouleur,"commbusybg");
							int clignarr [4] {1000,-1000,1000,-1};
							inpecho.clignote.remplacement(clignarr, 4);						
					} else if(inp.accepted) {
						if(inp.reserve) {			//Conserver le texte en place pendant quelques secondes. Peut être effacé progressivement par une nouvelle commande
							inpecho.txtcol = biblio.acces(biblio.poscouleur,"commbontxt"); inpecho.bgcol = biblio.acces(biblio.poscouleur,"commbonbg");
							int clignarr [2] {3000,-1};
							inpecho.clignote.remplacement(clignarr, 2);
						} else {				//Faire clignoter le texte pendant quelques secondes.
							inpecho.txtcol = biblio.acces(biblio.poscouleur,"commbontxt"); inpecho.bgcol = biblio.acces(biblio.poscouleur,"commbonbg");
							int clignarr [6] {500,-500,500,-500,500,-1};
							inpecho.clignote.remplacement(clignarr, 6);
						}                				
					} else{						//Faire clignoter le texte pendant quelques secondes.    
						inpecho.txtcol = biblio.acces(biblio.poscouleur,"commmauvtxt"); inpecho.bgcol = biblio.acces(biblio.poscouleur,"commmauvbg");
						int clignarr [8] {500,-500,500,-500,500,-500,500,-1};				
						inpecho.clignote.remplacement(clignarr,8);	
					}
					base.curspos(0,base.limtxty); for(int pos=0; pos < base.limfenx-1; pos++) out(' ');    //Nettoyer la ligne avant de la faire flasher
					inp.inputpos = 0; inp.commande.vide();                               //Nettoyer l'objet input			
				}	
			}
		}     


	//v) Fonction pour activer les menus	----------------------------------------------------------------------		

		//a) Fonction : LireMenu ; permet aux menus de fonctionner
		void univers::LireMenus(string nommenu){
			
			//Initier les compteurs
			int posmenu = ColNameFind(nommenu,nommenus);
			menus[posmenu].actif = true;
			int selectpos = 0; int selectneg = 0; int selectesc = 0; int selectenter = 0;			//Compteurs des animations
			int selectpost = 0; int selectnegt = 0; int selectesct = 0; int selectentert = 0;		//Compteurs de temps pour les animations			
			string effetalire;
			//Créer des raccourcis pour les coins en haut à droite de chaque bouton
			int postopleftx = base.milieufenx-floor(menus[posmenu].largeurbouton/2);
			StaticVect<int,nombrebouton> postoplefty;											
			if(menus[posmenu].boutons.longueur%2==1) {			//Si le nombre de boutons au menu est impair
				for(int boutcount=0; boutcount<menus[posmenu].boutons.longueur; boutcount++){
					postoplefty.ajout((base.milieufeny+1)-(floor(menus[posmenu].boutons.longueur/2)-boutcount)*(menus[posmenu].hauteurbouton+menus[posmenu].espacebouton));
				}
			} else {											//Si le nombre de boutons au menu est pair
				for(int boutcount=0; boutcount<menus[posmenu].boutons.longueur; boutcount++){
					postoplefty.ajout((base.milieufeny-1)-(menus[posmenu].boutons.longueur/2-boutcount)*(menus[posmenu].hauteurbouton+menus[posmenu].espacebouton));
				}
			}
			//Créer un array pour chaque bouton, pour les dessiner plus rapidement
			char dessinbout[menus[posmenu].nombrebouton][menus[posmenu].hauteurbouton][menus[posmenu].largeurbouton];		//Créer un array pour chaque bouton
			for(int countbout=0; countbout<menus[posmenu].boutons.longueur; countbout++) {
				//Trouver le texte comporte combien de lignes, et la longueur de chaque ligne
				int nblignetxt = 1; int nbchartxt = 0; StaticVect<int,menunblignesmax> longueurlignetxt;
				for(int strpos=0; strpos<menus[posmenu].boutons[countbout].length(); strpos++) {
					if(menus[posmenu].boutons[countbout][strpos]=='\n') {nblignetxt++; longueurlignetxt.ajout(nbchartxt); nbchartxt=0;} else nbchartxt++;
				} longueurlignetxt.ajout(nbchartxt);								
				//Faire la première ligne
				dessinbout[countbout][0][0] = '|'; dessinbout[countbout][0][menus[posmenu].largeurbouton-1] = '|'; for(int countchar=1; countchar<menus[posmenu].largeurbouton-1; countchar++) dessinbout[countbout][0][countchar] = '¯';
				//Faire la dernière ligne
				dessinbout[countbout][menus[posmenu].hauteurbouton-1][0] = '|'; dessinbout[countbout][menus[posmenu].hauteurbouton-1][menus[posmenu].largeurbouton-1] = '|'; for(int countchar=1; countchar<menus[posmenu].largeurbouton-1; countchar++) dessinbout[countbout][menus[posmenu].hauteurbouton-1][countchar] = '_';
				//Centrer le texte
				int beginpos = floor(((menus[posmenu].hauteurbouton-2)-nblignetxt)/2) + 1 ; int strpos = 0;
				for(int lignecount=1; lignecount<menus[posmenu].hauteurbouton-1; lignecount++) {
					dessinbout[countbout][lignecount][0] = '|'; dessinbout[countbout][menus[posmenu].hauteurbouton-1-lignecount][1] = ' ';
					dessinbout[countbout][lignecount][menus[posmenu].largeurbouton-1] = '|'; dessinbout[countbout][menus[posmenu].hauteurbouton-1-lignecount][menus[posmenu].largeurbouton-2] = ' ';
					if(lignecount<beginpos||lignecount>=beginpos+(nblignetxt)) {	//Si on doit remplir avec des espaces
						for(int charpos = 2; charpos<menus[posmenu].largeurbouton-2; charpos++) dessinbout[countbout][lignecount][charpos] = ' ';
					} else {
						for(int charpos = 2; charpos<menus[posmenu].largeurbouton-2; charpos++) {	//Si on doit remplir avec le nom du bouton
							if(charpos>=ceiling((menus[posmenu].largeurbouton-longueurlignetxt[lignecount-beginpos])/2)&&charpos<floor((menus[posmenu].largeurbouton-longueurlignetxt[lignecount-beginpos])/2)+longueurlignetxt[lignecount-beginpos]&&strpos < menus[posmenu].boutons[countbout].length()) {
								dessinbout[countbout][lignecount][charpos] = menus[posmenu].boutons[countbout][strpos]; strpos++;
							} else dessinbout[countbout][lignecount][charpos] = ' ';
						}
						strpos++;		//Faire avancer le texte à la fin de la ligne, car on tombe sur un '\n' qu'on ne veut pas printer!
					}
				}
			}
			//Afficher le menu
				//Afficher l'arrière plan
				chgcolmenuarrplan();	//Mettre la bonne couleur
				if(menus[posmenu].isbgdessin) {
					int nbcolbg = menus[posmenu].bgdessin.length()/menus[posmenu].bgdessinnbligne;
					//Placer le dessin correctement en fonction de la taille de la fenêtre
					int bgdecalx = 0; int bgdecaly = 0;				//L'origine du dessin, soit le coin "top-left", en haut à gauche, va être décalé pour placer le point d'intérêt à la bonne place
						//Commencer par les coordonnées en "x"
						int bgdiffx = base.limfenx-nbcolbg;
						int bgposinteretx = round(menus[posmenu].bgposinteretx*base.limfenx);	//Idéalement, on veut que le point d'intérêt soit exactement à ces coordonnées!
						if(bgdiffx<0) {							//La fenêtre est plus petite que l'image totale: décaler pour positionner le point d'intérêt
							for(int countdiff=0; countdiff<abs(bgdiffx); countdiff++) {		//Défiler l'image jusqu'à atteindre sa limite droite
								//tirer graduellement l'image vers la gauche, pour laisser apparaître la partie de droite à la fenêtre
								if(menus[posmenu].bgptinteretx - bgdecalx > bgposinteretx) bgdecalx++; else break;
							}
						} else if(bgdiffx>0) {					//La fenêtre est plus grande que l'image totale: agrandir pour positionner le point d'intérêt
							if(!menus[posmenu].bgleftlocked&&!menus[posmenu].bgrightlocked) {		//Augmenter l'espace à gauche seulement si c'est permis
								for(int countdiff=0; countdiff<bgdiffx; countdiff++) {		//Tasser l'image vers la droite en la gardant tout de même entière en tout temps
									if(menus[posmenu].bgptinteretx - bgdecalx < bgposinteretx) bgdecalx--; else break;
								}
							} else if(menus[posmenu].bgrightlocked) bgdecalx = bgdiffx; else if(menus[posmenu].bgleftlocked) bgdecalx = 0;		//Valeurs automatiques si un côté est bloqué (ne peut pas s'agrandir)
							//Le trou qui n'a pas été comblé en décalant va être rempli par des espaces à droite					
						}								
						//Poursuivre avec les coordonnées en "y"
						int bgdiffy = base.limfeny-menus[posmenu].bgdessinnbligne;
						int bgposinterety = round(menus[posmenu].bgposinterety*base.limfeny);	//Idéalement, on veut que le point d'intérêt soit exactement à ces coordonnées!
						if(bgdiffy<0) {							//La fenêtre est plus petite que l'image totale: décaler pour positionner le point d'intérêt
							for(int countdiff=0; countdiff<abs(bgdiffy); countdiff++) {		//Défiler vers le haut jusqu'à atteindre sa limite en bas
								//tirer graduellement l'image vers le haut, pour laisser apparaître la partie basse à la fenêtre
								if(menus[posmenu].bgptinterety - bgdecaly > bgposinterety) bgdecaly++; else break;
							}
						} else if(bgdiffx>0) {					//La fenêtre est plus grande que l'image totale: agrandir pour positionner le point d'intérêt
							if(!menus[posmenu].bgtoplocked&&!menus[posmenu].bgbottomlocked) {		//Augmenter l'espace en haut seulement si c'est permis
								for(int countdiff=0; countdiff<bgdiffy; countdiff++) {		//Tasser l'image vers le bas en la gardant tout de même entière en tout temps
									if(menus[posmenu].bgptinterety - bgdecaly < bgposinterety) bgdecaly--; else break;
								}	
							} else if(menus[posmenu].bgbottomlocked) bgdecaly = bgdiffy; else if(menus[posmenu].bgtoplocked) bgdecaly = 0;		//Valeurs automatiques si un côté est bloqué (ne peut pas s'agrandir)
							//Le trou qui n'a pas été comblé en décalant va être rempli par des espaces en bas					
						}				
					//Dessiner le background
					int posdessinx = bgdecalx; int posdessiny = bgdecaly;
					for(int countligne=0; countligne<base.limfeny; countligne++) {
						base.curspos(0,countligne);
						posdessinx = bgdecalx;
						for(int countcol=0; countcol<base.limfenx; countcol++) {
							if(countligne==base.limfeny-1&&countcol==base.limfenx-1) continue;		//Ne pas remplir le dernier coin (en bas à droite), pour éviter de changer de ligne automatiquement et de déborder de la fenêtre
							if(posdessinx>=0&&posdessinx<nbcolbg&&posdessiny>=0&&posdessiny<menus[posmenu].bgdessinnbligne) { 
								out(menus[posmenu].bgdessin[posdessinx+posdessiny*nbcolbg]); 
							} else out(' ');		//Si les positions excèdent les limites du dessin, remplir par des espaces vides							
							posdessinx++;
						}
						posdessiny++;
					}
				} else {	//La mémoire de l'histoire comme background
					ReecrireTout();
				}
				//Ajouter le titre
				chgcolmenu();			//Mettre la bonne couleur
				int titretoplefty = floor(base.limfeny*menus[posmenu].titrehauteur);
				int titrestrpos = 0;					
				if(menus[posmenu].istitredessin) {		//Si le titre est un dessin
					int nbcoltitre = menus[posmenu].titredessin.length()/menus[posmenu].titredessinnbligne;
					int titretopleftx = floor((base.limfenx-nbcoltitre)/2);
					for(int countligne=0; countligne<menus[posmenu].titredessinnbligne; countligne++) {
						base.curspos(titretopleftx, titretoplefty+countligne);		//Mettre le curseur au début de la ligne
						for(int countcol=0; countcol<nbcoltitre; countcol++) {
							if(menus[posmenu].titredessin[titrestrpos]!='µ') out(menus[posmenu].titredessin[titrestrpos]); 		//'µ' est le caractère transparent pour les dessins (laisse paraître le background).
							titrestrpos++;
						}			//Pas besoin d'avancer de 1 à la fin de la ligne, car toutes les lignes sont de la même longueur, qui est connue
					}
				} else {				//Si le titre est simplement du texte
					//Trouver le texte comporte combien de lignes, et la longueur de chaque ligne
					int nblignetxt = 1; int nbchartxt = 0; StaticVect<int,menunblignesmax> longueurlignetxt;		
					while(titrestrpos<menus[posmenu].titretxt.length()){
						if(menus[posmenu].titretxt[titrestrpos]=='\n') {nblignetxt++; longueurlignetxt.ajout(nbchartxt); nbchartxt=0;} else nbchartxt++;
					} longueurlignetxt.ajout(nbchartxt);	
					//Écrire le titre	
					for(int countligne=0; countligne<nblignetxt; countligne++) {
						base.curspos(floor((base.limfenx-longueurlignetxt[countligne])/2), titretoplefty+countligne);		//Mettre le curseur au début de la ligne
						for(int countcol=0; countcol<longueurlignetxt[countligne]; countcol++) {
							out(menus[posmenu].titretxt[titrestrpos]); titrestrpos++;
						}
						titrestrpos++;		//À la fin d'une ligne, avancer quand même de 1, car on veut dépasser le '\n' qui change de ligne (et qu'on ne veut pas printer)
					}
				}
				//Afficher les boutons		//Chaque bouton est 3 char de haut, et 19 char de large; avec un espace de 2 char entre chaque
				for(int boutcount=0; boutcount<menus[posmenu].boutons.longueur; boutcount++) {
					if(boutcount==menus[posmenu].posactu) chgcolmenuselect(); else chgcolmenu();		//Mettre le bouton de la bonne couleur
					for(int lignecount=0; lignecount<menus[posmenu].hauteurbouton; lignecount++) {
						base.curspos(postopleftx,postoplefty[boutcount]+lignecount); 
						for(int charpos=0; charpos<menus[posmenu].largeurbouton; charpos++) out(dessinbout[boutcount][lignecount][charpos]);
					}
				}			
			//Permettre le choix de différents boutons
			while(menus[posmenu].actif){
				clock.reglerheure();
				//Afficher l'effet de sélection positive		//Un contour sélectionné qui s'expend vers l'intérieur
				if(selectpos>0&&selectpost<clock.currentt){
					chgcolmenuselect(); 
					for(int bouty=0; bouty<menus[posmenu].hauteurbouton; bouty++) {
						for(int boutx=0; boutx<menus[posmenu].largeurbouton; boutx++) {
							if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) > selectpos-2) {	//Équation d'un cercle de rayon de sélectpos (-2, parce qu'on ne se rend pas à selectpos==0)!
								base.curspos(postopleftx+boutx,postoplefty[menus[posmenu].posactu]+bouty); out(dessinbout[menus[posmenu].posactu][bouty][boutx]);
							}
						}
					}
					selectpos--; selectpost = clock.currentt + round(menus[posmenu].selectdelay/(menus[posmenu].largeurbouton/2));
				}		
				//Afficher l'effet de sélection négative		//Un centre non sélectionné qui s'expend vers l'extérieur
				if(selectneg>0&&selectnegt<clock.currentt){
					chgcolmenu(); 
					for(int bouty=0; bouty<menus[posmenu].hauteurbouton; bouty++) {
						for(int boutx=0; boutx<menus[posmenu].largeurbouton; boutx++) {
							if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) <= pow(pow(menus[posmenu].hauteurbouton/2,2)+pow(menus[posmenu].largeurbouton/2,2),0.5)-selectneg+1) {	//Équation d'un cercle de rayon de l'hypothénuse entre la 1/2 hauteur et la 1/2 largeur!
								base.curspos(postopleftx+boutx,postoplefty[menus[posmenu].pospreced]+bouty); out(dessinbout[menus[posmenu].pospreced][bouty][boutx]);																	//+1, car on ne se rend pas à selectneg == 0.
							}
						}
					}
					selectneg--; selectnegt = clock.currentt + round(menus[posmenu].selectdelay/(menus[posmenu].largeurbouton/2));	
				}
				//Afficher l'effet de "enter"		//Une vague non sélectionnée depuis l'intérieur, vers l'extérieur
				if(selectenter>0&&selectentert<clock.currentt){
					chgcolmenu(); 
					for(int bouty=0; bouty<menus[posmenu].hauteurbouton; bouty++) {
						for(int boutx=0; boutx<menus[posmenu].largeurbouton; boutx++) {
							if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) <= pow(pow(menus[posmenu].hauteurbouton/2,2)+pow(menus[posmenu].largeurbouton/2,2),0.5)-selectenter+4) {			//petit cercle non sélectionné
								if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) <= pow(pow(menus[posmenu].hauteurbouton/2,2)+pow(menus[posmenu].largeurbouton/2,2),0.5)-selectenter+1) {		//centre sélectionné qui prend le dessus
									chgcolmenuselect();			//L'intérieur qui va éventuellement prendre le dessus est de couleur sélectionnée
								} else chgcolmenu();		//La bande de 3 char de large va être de couleur non sélectionnée
								base.curspos(postopleftx+boutx,postoplefty[menus[posmenu].pospreced]+bouty); out(dessinbout[menus[posmenu].pospreced][bouty][boutx]);
							}
						}
					}
					if(selectenter!=1) {		//La dernière fois, il ne faut pas updater, pour que la fin de la boucle puisse comprendre le message!
						selectenter--;
						selectentert = clock.currentt + round(menus[posmenu].enterdelay/(menus[posmenu].largeurbouton/2+3));						
					}			
				}				
				//Afficher l'effet de "escape"					//Une vague sélectionnée depuis l'extérieur, vers le centre, suivit d'une couronne non sélectionnée, mais sur tous les boutons!
				if(selectesc>0&&selectesct<clock.currentt){
					for(int boutcount=0; boutcount<menus[posmenu].boutons.longueur; boutcount++) {		//Propager l'effet à tous les boutons, éventuellement!
						for(int bouty=0; bouty<menus[posmenu].hauteurbouton; bouty++) {
							for(int boutx=0; boutx<menus[posmenu].largeurbouton; boutx++) {
								if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) > selectesc - 2*abs(boutcount-menus[posmenu].posactu)-5) {		//Faire l'arc le plus près du centre (va finir par disparaître)
									if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) > selectesc - 2*abs(boutcount-menus[posmenu].posactu)-2) {		//Faire l'arc éloigné du centre		
										chgcolmenu();		//L'arc le plus éloigné, qui va éventuellement prendre le dessus, est de couleur non sélectionnée		//- 2*abs(boutcount-menus[posmenu].posactu) : c'est pour faire que les boutons les plus loins "se ferment" plus vite
									} else chgcolmenuselect();		//La bande de 3 char de large va être de couleur sélectionnée: invisible pour le posactu, visible pour les autres boutons.
									base.curspos(postopleftx+boutx,postoplefty[boutcount]+bouty); out(dessinbout[boutcount][bouty][boutx]);
								} 
							}
						}
					}
					if(selectesc!=1)  { 		//La dernière fois, il ne faut pas updater, pour que la fin de la boucle puisse comprendre le message!
						selectesc--;
						selectesct = clock.currentt + round(menus[posmenu].enterdelay/(menus[posmenu].largeurbouton/2+3+2*max(abs(menus[posmenu].posactu),abs(menus[posmenu].posactu-menus[posmenu].nombrebouton))));
					}
				}			
				//Être à l'affut de touches du clavier
				if(selectenter==0&&selectesc==0&&selectpos==0&&selectneg==0) {
					if(_kbhit()){
						char charkey; int intkey = _getch();                  		//Enregistrer quelle touche a été pressée
						if (intkey == 0 || intkey == -32 || intkey == 224) {      //La valeur est spéciale: elle nécessite de la ré-examiner
							intkey = _getch();                              //Examiner une deuxième valeur pour identifier				
							if (intkey == 72) {				//Flèche du haut : passer au bouton d'en haut
								if(menus[posmenu].posactu>0) {
									selectpos = floor(menus[posmenu].largeurbouton/2); selectpost = clock.currentt;	selectneg = floor(menus[posmenu].largeurbouton/2); selectnegt = clock.currentt;		//Enclencher les effets de sélection
									menus[posmenu].pospreced = menus[posmenu].posactu; menus[posmenu].posactu--;
								}
							} else if (intkey == 80) {		//Flèche du bas : passer au bouton d'en bas
								if(menus[posmenu].posactu<menus[posmenu].boutons.longueur-1) {
									selectpos = floor(menus[posmenu].largeurbouton/2); selectpost = clock.currentt;	selectneg = floor(menus[posmenu].largeurbouton/2); selectnegt = clock.currentt;		//Enclencher les effets de sélection
									menus[posmenu].pospreced = menus[posmenu].posactu; menus[posmenu].posactu++;
								}						
							}
						} else {			//Si la valeur n'est pas "spéciale"
							if(intkey == 27) {
								selectesc = floor(menus[posmenu].largeurbouton/2) + 2*max(abs(menus[posmenu].posactu),abs(menus[posmenu].posactu-menus[posmenu].nombrebouton)); 
								menus[posmenu].pospreced = menus[posmenu].posactu; selectesct = clock.currentt;		 //Escape : annuler le menu (va envoyer à l'effet assigné correspondant)
							} else if(intkey == 13) {
								selectenter = floor(menus[posmenu].largeurbouton/2) + 3; 
								menus[posmenu].pospreced = menus[posmenu].posactu; selectentert = clock.currentt;}	 //Enter : confirmer le choix (va envoyer à l'effet assigné correspondant)				
						}
					}		
				}
				//Réaliser l'effet de "enter" / "escape"
				if((selectesc==1&&selectesct<clock.currentt)||(selectenter==1&&selectentert<clock.currentt)) {	
					menus[posmenu].actif = false;			//Fermer ce menu-ci
					if(selectesc==1) effetalire = menus[posmenu].effetescape; else effetalire = menus[posmenu].effets[menus[posmenu].posactu];		//Décider d'où on prend les effets à lire
					int counteffet = 0; int effetnb = effetalire.length();
					while(counteffet<effetnb) {
						if(effetalire[counteffet]=='§') {
							if(effetalire[counteffet+1]=='a') {				//'a' pour "abort()" -> force la fin du programme
								abort();
							} else if(effetalire[counteffet+1]=='b') {		//'b' pour "biblio" -> modifie une des valeurs de la bibliothèque!
								string nomrayon; string nomlivre; string val;
								int posSpecial = counteffet+2;
								while(effetalire[posSpecial] != '¶') nomrayon += effetalire[posSpecial++]; 
								posSpecial++; while(!(effetalire[posSpecial] == '~' && effetalire[posSpecial+1] == '>')) nomlivre += effetalire[posSpecial++];
								posSpecial+=2; while(effetalire[posSpecial] != '§') val += effetalire[posSpecial++];							
								biblio.modif(nomrayon,nomlivre,stoi(val));	
							} else if(effetalire[counteffet+1]=='c') {		//'c' pour "clear" -> ré-initialise toute la bibliothèque à zéro (sauf les rayons fixes)
								for(int rayonpos=biblio.nbrayonsfixes; rayonpos<biblio.rayon.longueur; rayonpos++) {
									for(int livrepos=0; livrepos<biblio.rayon[rayonpos].longueur; livrepos++) {
										biblio.modif(rayonpos,livrepos,0);			//Tout remettre à 0.
									}
								}
							} else if(effetalire[counteffet+1]=='f') {		//'f' pour "fenêtre" -> Changer la taille de la fenêtre de jeu
								bool hautcons; bool agrandcons;
								if(effetalire[counteffet+2]=='h') hautcons = true; else if(effetalire[counteffet+2]=='l') hautcons = false; else {out("LE CODE SPÉCIAL \""); out(strintervalle(effetalire,counteffet,CodeSpecialLongueur(strintervalle(effetalire,counteffet,effetnb))-1)); out("\", contenu dans le menu \""); out(nommenus[posmenu]); out("\", n'a pas 'h' (pour \"hauteur\") ou 'l' (pour \"largeur\") comme deuxième argument."); abort();}
								if(effetalire[counteffet+3]=='+') agrandcons = true; else if(effetalire[counteffet+3]=='-') agrandcons = false; else {out("LE CODE SPÉCIAL \""); out(strintervalle(effetalire,counteffet,CodeSpecialLongueur(strintervalle(effetalire,counteffet,effetnb))-1)); out("\", contenu dans le menu \""); out(nommenus[posmenu]); out("\", n'a pas '+' (pour \"agrandir\") ou '-' (pour \"rapetisser\") comme troisième argument."); abort();}
								base.modifdim(agrandcons,hautcons);
							} else if(effetalire[counteffet+1]=='j') {		//'j' pour "jouer" -> checker les motifs automatiques, puis enclencher la boucle "jouer()"
								AutoInterpret();
								ReecrireToutAvecCouleurs();		//Remettre l'écran au "jeu"
								jouer();			
							} else if(effetalire[counteffet+1]=='m') {		//'m' pour "mémoire" -> ré-initie les objets de mémoires, qui gardent la trace de la progression du jeu 
								mem.setsize(base.limtxtx); msnmem.setsize(base.limtxtx,base.limtxty);		//Initier les mémoires du jeu de la bonne taille; remet également les mémoires à 0.						
							} else if(effetalire[counteffet+1]=='u') {		//'u' pour "unpause" -> remet l'écran de jeu et remet en activité les compteurs de temps
																				//ATTENTION! Ce code spécial est fait uniquement pour les menus créés directement à partir du jeu, dont la fin signifie le retour à la boucle "jouer()" déjà commencée!
								ReecrireToutAvecCouleurs();		//Remettre l'écran au "jeu"
								counteffet = effetnb;	//Être certaine d'arrêter de lire des codes spéciaux, pour sortir immédiatement de ce menu et revenir au jeu
								unpauseall();		
							} else if(effetalire[counteffet+1]=='x') {		//('x' pour "même" -> remet le menu actuel (surtout utile pour changer la taille de la fenêtre)
								LireMenus(nommenus[posmenu]);		//Relire le même menu					
							} else if(effetalire[counteffet+1]=='y') {		//('y' pour "précédent" -> remet le menu précédent, tout simplement
								if(menupreced.longueur==0){			//Oups! Est-ce une erreur? Il n'y a pas de menu précédent! Tiens... On va faire "unpause" à la place!
									ReecrireToutAvecCouleurs(); counteffet = effetnb; unpauseall();
								} else {
									string name = menupreced[menupreced.longueur-1];		//Aller chercher le nom du menu précédent
									menupreced.supprposition(menupreced.longueur-1);		//Effacer sa trace
									counteffet = effetnb;	//être certaine d'arrêter de lire des codes spéciaux, pour ne pas défaire ce que des menus ultérieurs ont fait
									LireMenus(name);		//Lire le menu précédent
								}
							} else if(effetalire[counteffet+1]=='z') {		//(§z§, 'z' pour... rien en fait. 'm' était déjà pris dans les codes spéciaux de canaux, alors j'ai pris z. Que je ré-utilise ici).
								menupreced.ajout(nommenus[posmenu]);		//Garder en mémoire le nom du menu actuel, pour pouvoir y revenir (bouton "précédent")
								string name; int charcount = counteffet+2;
								while(effetalire[charcount]!='§') {name += effetalire[charcount]; charcount++;}
								counteffet = effetnb;	//être certaine d'arrêter de lire des codes spéciaux, pour ne pas défaire ce que des menus ultérieurs ont fait
								LireMenus(name);
							}
						} else {out("Il manque un symbole '§' dans l'effet \""); out(effetalire); out("\" du menu \""); out(nommenus[posmenu]); out("\"."); abort();}
						if(counteffet < effetnb) counteffet += CodeSpecialLongueur(strintervalle(effetalire,counteffet,effetnb));
					}
				}
			}
		}
		
	//vi) Fonction pour tout coordonner harmonieusement	----------------------------------------------------------------------		
		
		//a) Fonction jouer();
		void univers::jouer(){
			while(true){				//À faire tout le temps:
				clock.reglerheure();	//Aller chercher le temps
				LireCanaux();		//Lire chaque canal, s'il est prêt	
				LireMessagerie();		//Lire chaque messagerie, si elle est prête	
				UserInputEcho();	//Afficher le fantôme de la commande précédente
				UserInput();		//Interpréter la touche jouée		
			}
		}


		//b) Fonction debuter();
		void univers::debuter(const string& str){
			base.defaultwin();			//Initier la fenêtre par défaut
			mem.setsize(base.limtxtx); msnmem.setsize(base.limtxtx,base.limtxty);		//Initier les mémoires du jeu;						
			LireMenus(str);				//Initier le menu de départ
		}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//6) Fonctions de remplissage aisé des objets utilisés
	
	//i) Fonctions pour nommer les livres et les rayons de la bibliothèque	----------------------------------------------------------------------		

		//a) Fonction pour créer un nouveau rayon et le nommer
		void univers::nvrayon(const string& str) {
			if(biblio.rayon.longueur==biblio.rayon.taille) {out("Il manque de place pour construire le rayon \""); out(str); out("\"!\n\nAgrandissez la bibliothèque pour résoudre ce problème."); abort();}
			biblio.rayon.ajoutvide();								//Passer au prochain rayon
			biblio.nomrayon.ajout(str);
		}
		
		//b) Fonction pour créer un nouveau livre et le nommer
		void univers::nvlivre(const string& str) {
			if(biblio.rayon[biblio.rayon.longueur-1].longueur==biblio.rayon[biblio.rayon.longueur-1].taille) {out("Il manque de place pour construire le livre \""); out(str); out("\"!\n\nAgrandissez la bibliothèque ou changez de rayon pour résoudre ce problème."); abort();}
			biblio.rayon[biblio.rayon.longueur-1].ajoutvide();		//Passer au prochain livre
			biblio.nomlivre[biblio.rayon.longueur-1].ajout(str); biblio.modif(biblio.rayon.longueur-1,biblio.rayon[biblio.rayon.longueur-1].longueur-1,0);		//Mettre 0 comme valeur par défaut (par défaut, tous les livres = FALSE)
		}

	//ii) Fonctions pour créer de nouveaux canaux et les personaliser	----------------------------------------------------------------------		
	
		//a) Fonction pour créer un nouveau canal et le nommer
		void univers::nvcanal(const string& str) {                    
			if(canaux.longueur==canaux.taille) {out("Il manque de place pour construire le canal \""); out(str); out("\"!\n\nAugmentez le nombre de canaux dans l'objet \"univers\" pour résoudre ce problème."); abort();}		
			canaux.ajoutvide();
			canaux[canaux.longueur-1].nom = str;
			nomcanaux.ajout(str);
		}
		
		//b) Fonction pour modifier le délai du canal    
		void univers::canaldelai(int val) {				
			canaux[canaux.longueur-1].delay = val;          
		}
		
		//c) Fonction pour modifier l'alinéa du canal (l'indentation par défaut)
		void univers::canalalinea(int val) {
			canaux[canaux.longueur-1].alinea = val;
		}

		//d) Fonction pour modifier la terminaison du canal (qui sera ajouté à la fin lorsque l'on forcera le canal à se vider - pour par exemple fermer les guillements d'une réplique)
		void univers::canalterminaison(const string& str) {
			canaux[canaux.longueur-1].terminaison = str;
		}

	//iii) Fonctions pour organiser les chapitres et les motifs (permettent l'activation des textes)	----------------------------------------------------------------------		
	
		//a) Fonction pour créer un nouveau chapitre
		void univers::nvchapt() {
			if(histoire.filauto.longueur==histoire.filauto.taille) {out("Il manque de place pour construire un nouveau chapitre à l'histoire!\n\nAugmentez le nombre de chapitres dans l'objet \"histoire\" pour résoudre ce problème."); abort();}		
			histoire.filauto.ajoutvide();		
			histoire.filmanu.ajoutvide();											
		}
		
		//b) Fonction pour définir les conditions d'activation du chapitre
		void univers::ccond(const string& str) {
			histoire.cadenas[histoire.filmanu.longueur-1].set(str,biblio);
		}
	
		//c) Fonction pour "créer" un nouveau motif et le nommer (manuel)
		void univers::nvmanu(const string& str) {
			int poschap = histoire.filmanu.longueur-1;
			if(histoire.filmanu[poschap].longueur==histoire.filmanu[poschap].taille) {out("Il manque de place pour construire le nouveau motif manuel \""); out(str); ;out("\" à l'intérieur du dernier chapitre!\n\nAugmentez le nombre de motifs dans l'objet \"histoire\", ou passez au prochain chapitre, pour résoudre ce problème."); abort();}						
			histoire.filmanu[poschap].ajoutvide();			//Passer au prochain motif
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].titre = str;     //Conserver le titre, pour y référer au cas où une même commande appelerait plusieurs motifs.
		} 
		//c)Fonction pour "créer" un nouveau motif (automatique)
		void univers::nvauto() {				
			int poschap = histoire.filauto.longueur-1;
			if(histoire.filauto[poschap].longueur==histoire.filauto[poschap].taille) {out("Il manque de place pour construire un nouveau motif automatique à l'intérieur du dernier chapitre!\n\nAugmentez le nombre de motifs dans l'objet \"histoire\", ou passez au prochain chapitre, pour résoudre ce problème."); abort();}		
			histoire.filauto[poschap].ajoutvide();			//Passer au prochain motif
		}
		
	//iv) Fonctions pour remplir les motifs	----------------------------------------------------------------------			
		
		//a) Fonction pour définir le canal du motif (manuel)		//Si le nom fourni est "msn", le motif activera un nouveau "msn" au lieu de s'inscrire dans un canal
		void univers::mcanal(const string& str) {		
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;
			if((str[0]=='m'||str[0]=='M')&&(str[1]=='s'||str[1]=='S')&&(str[2]=='n'||str[2]=='N')&&str.length()==3) { histoire.filmanu[poschap][posmotif].msn = true;	//Msn
			} else histoire.filmanu[poschap][posmotif].canal = ColNameFind(str,nomcanaux);	//Canal
		} 
		//a) Fonction pour définir le canal du motif (automatique)		//Si le nom fourni est "msn", le motif activera un nouveau "msn" au lieu de s'inscrire dans un canal
		void univers::acanal(const string& str) {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;
			if((str[0]=='m'||str[0]=='M')&&(str[1]=='s'||str[1]=='S')&&(str[2]=='n'||str[2]=='N')&&str.length()==3) { histoire.filauto[poschap][posmotif].msn = true;	//Msn
			} else histoire.filauto[poschap][posmotif].canal = ColNameFind(str,nomcanaux);  //Canal
		}	
		
		//b) Fonction pour écire le texte ("mailles") du motif (manuel)
		void univers::mtexte(const string& str) {
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;			
			int strnb = str.length();		//Aller chercher la taille du string
			int debmaille = 0;				//Créer un compteur pour le début de la maille actuelle
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='µ') {
					if(histoire.filmanu[poschap][posmotif].maille.longueur==histoire.filmanu[poschap][posmotif].maille.taille) {out("Dans le motif manuel :\n\n\""); out(str); out("\"\n\n   il y a trop de \"mailles\" différentes, c'est-à-dire de bouts de phrases séparés par 'µ'. Augmentez le nombre de mailles d'un motif manuel ou séparez celui-ci en plusieurs pour résoudre ce problème."); abort();}		
					if(countstr-debmaille>0) {
						histoire.filmanu[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,countstr-1));
					} else histoire.filmanu[poschap][posmotif].maille.ajout("");   
					debmaille = countstr+1;		//if(...) : évite les intervalles [1,0] (à la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "µµ")
				}
			}
			if(histoire.filmanu[poschap][posmotif].maille.longueur==histoire.filmanu[poschap][posmotif].maille.taille) {out("Dans le motif manuel :\n\n\""); out(str); out("\"\n\n   il y a trop de \"mailles\" différentes, c'est-à-dire de bouts de phrases séparés par 'µ'. Augmentez le nombre de mailles d'un motif manuel ou séparez celui-ci en plusieurs pour résoudre ce problème."); abort();}					
			histoire.filmanu[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,strnb-1));		//Entrer la dernière maille
			//Ajouter par défaut un enchaînement lisant l'intégralité des mailles, dans l'ordre (peut alors être écrasé par les commandes suivantes)
			if(histoire.filmanu[poschap][posmotif].ordre == "") {
				for(int countmaille = 0; countmaille<histoire.filmanu[poschap][posmotif].maille.longueur; countmaille++){
					histoire.filmanu[poschap][posmotif].ordre += to_string(countmaille); 
					if(countmaille<histoire.filmanu[poschap][posmotif].maille.longueur-1) histoire.filmanu[poschap][posmotif].ordre += '-';
				}				
			}	
		}																						
		//b) Fonction pour écire le texte ("mailles") du motif (automatique)
		void univers::atexte(const string& str) {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;			
			int strnb = str.length();		//Aller chercher la taille du string
			int debmaille = 0;				//Créer un compteur pour le début de la maille actuelle
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='µ') {										
					if(countstr-debmaille>0) {
						if(histoire.filauto[poschap][posmotif].maille.longueur==histoire.filauto[poschap][posmotif].maille.taille) {out("Dans le motif automatique :\n\n\""); out(str); out("\"\n\n   il y a trop de \"mailles\" différentes, c'est-à-dire de bouts de phrases séparés par 'µ'. Augmentez le nombre de mailles d'un motif automatique ou séparez celui-ci en plusieurs pour résoudre ce problème."); abort();}		
						histoire.filauto[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,countstr-1));
					} else histoire.filauto[poschap][posmotif].maille.ajout("");   
					debmaille = countstr+1;		//if(...) : évite les intervalles [1,0] (à la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "µµ")
				}
			}
			if(histoire.filauto[poschap][posmotif].maille.longueur==histoire.filauto[poschap][posmotif].maille.taille) {out("Dans le motif automatique :\n\n\""); out(str); out("\"\n\n   il y a trop de \"mailles\" différentes, c'est-à-dire de bouts de phrases séparés par 'µ'. Augmentez le nombre de mailles d'un motif automatique ou séparez celui-ci en plusieurs pour résoudre ce problème."); abort();}					
			histoire.filauto[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,strnb-1));		//Entrer la dernière maille
			//Ajouter par défaut un enchaînement lisant l'intégralité des mailles, dans l'ordre (peut alors être écrasé par les commandes suivantes)
			if(histoire.filauto[poschap][posmotif].ordre == "") {
				for(int countmaille = 0; countmaille<histoire.filauto[poschap][posmotif].maille.longueur; countmaille++){
					histoire.filauto[poschap][posmotif].ordre += to_string(countmaille); 
					if(countmaille<histoire.filauto[poschap][posmotif].maille.longueur-1) histoire.filauto[poschap][posmotif].ordre += '-';
				}				
			}
		}		
			
			
		//c) Fonction pour définir les enchaînements spécifiques possibles (manuel)
		void univers::mordre(const string& str) {
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;
			histoire.filmanu[poschap][posmotif].ordre = str;
		}		
		//c) Fonction pour définir les enchaînements spécifiques possibles (automatique)
		void univers::aordre(const string& str) {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;
			histoire.filauto[poschap][posmotif].ordre = str;
		}
				
		//d) Fonction pour définir les enchaînements spécifiques possibles (manuel)
		void univers::mordrespecifique(const string& str) {
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int countordre = 0;				//Créer un compteur pour l'ordre
			int debnombre = 0;				//Créer un compteur d'indexation pour le début du nombre
			histoire.filmanu[poschap][posmotif].ordrespecifique.ajoutvide();	//Créer un premier "objet" pour stocker les enchaînements
			//Ajouter les enchaînements inscrits
			for(int countstr=0; countstr<=strnb; countstr++){
				if(countstr==strnb||str[countstr]=='-'||str[countstr]==';') {
					if(histoire.filmanu[poschap][posmotif].ordrespecifique[countordre].longueur==histoire.filmanu[poschap][posmotif].ordrespecifique[countordre].taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\"\n\n   il y a trop de \"mailles\" à l'\"enchaînement\" #"); out(countordre+1); out(" ( fonction mordre() ). Augmentez le nombre de mailles par enchaînement ou faites ça moins compliqué, pour résoudre ce problème."); abort();}		
					if(countstr-debnombre>0) {
						histoire.filmanu[poschap][posmotif].ordrespecifique[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
					} else {out("L'enchaînement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing à la position "); out(countstr); out(". Changer ça svp."); abort();}			
					if(countstr!=strnb&&str[countstr]=='-') {}		//Rien ne se passe (mais je préférais l'expliciter)
					if(countstr<strnb-1&&str[countstr]==';') {		//Si ';' est le dernier caractère du string, on ne crée pas de nouvel enchaînement (parce qu'il serait complètement vide)
						if(histoire.filmanu[poschap][posmotif].ordrespecifique.longueur==histoire.filmanu[poschap][posmotif].ordrespecifique.taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\"\n\n   il y a trop d'\"enchaînements\" ( fonction mordre() ). Augmentez le nombre d'enchaînements dans un motif manuel ou mettez moins de variété, pour résoudre ce problème. N'oubliez pas d'aussi augmenter le nombre de probabilités si vous faites la première option!"); abort();}							
						countordre++; 
						histoire.filmanu[poschap][posmotif].ordrespecifique.ajoutvide();
					}
					debnombre = countstr+1;
				}
			}
		}																						
		//d) Fonction pour définir les enchaînements spécifiques possibles (automatique)
		void univers::aordrespecifique(const string& str) {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int countordre = 0;				//Créer un compteur pour l'ordre
			int debnombre = 0;				//Créer un compteur d'indexation pour le début du nombre
			histoire.filauto[poschap][posmotif].ordrespecifique.ajoutvide();	//Créer un premier "objet" pour stocker les enchaînements
			//Ajouter les enchaînements inscrits
			for(int countstr=0; countstr<=strnb; countstr++){
				if(countstr==strnb||str[countstr]=='-'||str[countstr]==';') {
					if(histoire.filauto[poschap][posmotif].ordrespecifique[countordre].longueur==histoire.filauto[poschap][posmotif].ordrespecifique[countordre].taille) {out("Dans le motif autoel :\n\n\""); out(histoire.filauto[poschap][posmotif].maille[0]); out("...\"\n\n   il y a trop de \"mailles\" à l'\"enchaînement\" #"); out(countordre+1); out(" ( fonction mordre() ). Augmentez le nombre de mailles par enchaînement ou faites ça moins compliqué, pour résoudre ce problème."); abort();}		
					if(countstr-debnombre>0) {
						histoire.filauto[poschap][posmotif].ordrespecifique[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
					} else {out("L'enchaînement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing à la position "); out(countstr); out(". Changer ça svp."); abort();}			
					if(countstr!=strnb&&str[countstr]=='-') {}		//Rien ne se passe (mais je préférais l'expliciter)
					if(countstr<strnb-1&&str[countstr]==';') {		//Si ';' est le dernier caractère du string, on ne crée pas de nouvel enchaînement (parce qu'il serait complètement vide)
						if(histoire.filauto[poschap][posmotif].ordrespecifique.longueur==histoire.filauto[poschap][posmotif].ordrespecifique.taille) {out("Dans le motif autoel :\n\n\""); out(histoire.filauto[poschap][posmotif].maille[0]); out("...\"\n\n   il y a trop d'\"enchaînements\" ( fonction mordre() ). Augmentez le nombre d'enchaînements dans un motif autoel ou mettez moins de variété, pour résoudre ce problème. N'oubliez pas d'aussi augmenter le nombre de probabilités si vous faites la première option!"); abort();}							
						countordre++; 
						histoire.filauto[poschap][posmotif].ordrespecifique.ajoutvide();
					}
					debnombre = countstr+1;
				}
			}
		}		
		
		//e) Fonction pour définir les probabilités associées avec chaque enchaînement spécifique (manuel)
		void univers::mordrespecifiqueodds(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int debench = 0;				//Noter la position d'indexation du début de l'enchaînement
			int countench = 0;				//Position de l'enchaînement visé
			//Marquer le fait qu'on va utiliser des probabilités spécifiques
			histoire.filmanu[poschap][posmotif].ordreavecodds = true;
			//Ajouter les probabilités inscrites
			for(int countstr=0; countstr<=strnb; countstr++){
				if(countstr==strnb||str[countstr]==';') {					
					histoire.filmanu[poschap][posmotif].ordrespecifiqueodds.ajoutvide();		//Noter le fait qu'on ajoute une probabilité
					if(countstr-debench>0){
						histoire.filmanu[poschap][posmotif].ordrespecifiqueodds[countench].set(strintervalle(str,debench,countstr-1),biblio);
					} else histoire.filmanu[poschap][posmotif].ordrespecifiqueodds[countench].set("1",biblio); //Si deux ';' se suivent, mettre la probabilité de l'enchaînement vide comme 1 (odds par défaut).
					debench = countstr + 1; countench++;
				}
			}
			while(countench<histoire.filmanu[poschap][posmotif].ordrespecifique.longueur-1){             //Si moins de probabilités ont été inscrites qu'il n'y a d'enchaînements
				histoire.filmanu[poschap][posmotif].ordrespecifiqueodds.ajoutvide();		//Noter le fait qu'on ajoute une probabilité				
				histoire.filmanu[poschap][posmotif].ordrespecifiqueodds[countench].set("1",biblio);
				countench++;
			}
		}
		//e) Fonction pour définir les probabilités associées avec chaque enchaînement spécifique (automatique)
		void univers::aordrespecifiqueodds(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int debench = 0;				//Noter la position d'indexation du début de l'enchaînement
			int countench = 0;				//Position de l'enchaînement visé
			//Marquer le fait qu'on va utiliser des probabilités spécifiques
			histoire.filauto[poschap][posmotif].ordreavecodds = true;
			//Ajouter les probabilités inscrites
			for(int countstr=0; countstr<=strnb; countstr++){
				if(countstr==strnb||str[countstr]==';') {					
					histoire.filauto[poschap][posmotif].ordrespecifiqueodds.ajoutvide();		//Noter le fait qu'on ajoute une probabilité
					if(countstr-debench>0){
						histoire.filauto[poschap][posmotif].ordrespecifiqueodds[countench].set(strintervalle(str,debench,countstr-1),biblio);
					} else histoire.filauto[poschap][posmotif].ordrespecifiqueodds[countench].set("1",biblio); //Si deux ';' se suivent, mettre la probabilité de l'enchaînement vide comme 1 (odds par défaut).
					debench = countstr + 1; countench++;
				}
			}
			while(countench<histoire.filauto[poschap][posmotif].ordrespecifique.longueur-1){             //Si moins de probabilités ont été inscrites qu'il n'y a d'enchaînements
				histoire.filauto[poschap][posmotif].ordrespecifiqueodds.ajoutvide();		//Noter le fait qu'on ajoute une probabilité				
				histoire.filauto[poschap][posmotif].ordrespecifiqueodds[countench].set("1",biblio);
				countench++;
			}
		}
		
		//f) Fonction pour définir les codes spéciaux appelés au début du motif (manuel)
		void univers::mdeb(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].codespeciauxdebut = str;
		}
		//f) Fonction pour définir les codes spéciaux appelés au début du motif (automatique)
		void univers::adeb(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].codespeciauxdebut = str;
		}
		
		//g) Fonction pour définir les codes spéciaux appelés à la fin du motif (manuel)
		void univers::mfin(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;
			histoire.filmanu[poschap][posmotif].codespeciauxfin = str;
		}
		//g) Fonction pour définir les codes spéciaux appelés à la fin du motif (automatique)
		void univers::afin(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;
			histoire.filauto[poschap][posmotif].codespeciauxfin = str;
		}
		
		//h) Fonction pour définir les conditions sous lesquelles le motif pourra être appelé (manuel)
		void univers::mcond(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].condition.set(str,biblio);
		}
		//h) Fonction pour définir les conditions sous lesquelles le motif pourra être appelé (automatique)
		void univers::acond(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].condition.set(str,biblio);
		}
			
		//i) Fonction pour définir que le canal sera vidé (override) dès l'activation de ce motif (manuel)   (désactivé par défaut)
		void univers::mover(){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].override = true;
		}				
		//i) Fonction pour définir que le canal sera vidé (override) dès l'activation de ce motif (automatique)   (désactivé par défaut)
		void univers::aover(){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].override = true;
		}					
					
		//j) Fonction pour définir que le canal sera mis en attente ("réserve") lorsque la bonne commande sera envoyée, et ce jusqu'à la lecture du code spécial "§r§" (manuel seulement)   (désactivé par défaut)
		void univers::mreserve(){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].reserve = true;
		}					
					
		//k) Fonction pour définir les combinaisons de mots qui appeleront le motif - les commandes (manuel)
		void univers::mcomm(const string& str){
			int poschap = histoire.filmanu.longueur-1;		//ICI, '|' SÉPARE LES SYNONYMES, '&' SÉPARE LES GROUPES DE MOTS NÉCESSAIRES, "[]" DÉNOTE LES MOTS À EXCLURE ET "()" SÉPARENT LES DIFFÉRENTES FAÇONS DE LE DIRE
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;			//NOTE: LES MOTS À EXCLURE N'ONT PAS DE GROUPES DE MOTS, ILS N'ONT QUE DES SYNONYMES!
			int strnb = str.length();
			int posfac = 0;			//Position des différentes façons de dire la commande
			int posgr = 0;          //Position des groupes de mots nécessaires
			int possyn = 0;			//Position des synonymes
			bool exclus = false;	//Marqueur pour les mots à exclure
			string mot;				//Mot à inclure/exclure dans la commande
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='('|str[countstr]=='[') {		
					if(str[countstr]=='(') {
						if(histoire.filmanu[poschap][posmotif].commandes.inclus.longueur==histoire.filmanu[poschap][posmotif].commandes.inclus.taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appelé par ::\n\n\""); out(str); out("\"\n\n   il y a trop de différentes façons d'appeler le motif (chaque façon différente est supposée être entre parenthèses). Augmentez le nombre de façons différentes dans la classe \"commande\" ou mettez moins de variété, pour résoudre ce problème. N'oubliez pas d'augmenter à la fois les mots inclus et les mots exclus, si vous faites la première option!"); abort();}
						histoire.filmanu[poschap][posmotif].commandes.inclus.ajoutvide();         //Noter qu'une nouvelle façon de dire la commande commence
						histoire.filmanu[poschap][posmotif].commandes.exclus.ajoutvide();	
					} else if(str[countstr]=='[') exclus = true;
				}else {
					if(countstr==0) {
						histoire.filmanu[poschap][posmotif].commandes.inclus.ajoutvide();         //Noter qu'une nouvelle façon de dire la commande commence
						histoire.filmanu[poschap][posmotif].commandes.exclus.ajoutvide();								//Si la première parenthèse est omise (par ex, lorsqu'il y a une seule façon de le dire)					
					}
					if(str[countstr]=='|'||str[countstr]=='&'||str[countstr]==')'||str[countstr]==']'){
						if(mot.length()>0&&!(mot.length()==1&&mot[0]==' ')) {		//Si un mot d'au moins une lettre et qui n'est pas seulement un espace a été sauvegardé				
							//Enregistrer le mot comme commande
							if(mot[0]==' ') mot = strintervalle(mot,1,mot.length()-1);		//Enlever les espaces en début et en fin de mot; permet d'espacer l'écriture des commandes au besoin
							if(mot[mot.length()]==' ') mot = strintervalle(mot,0,mot.length()-2);
							if(exclus) {
								if(histoire.filmanu[poschap][posmotif].commandes.exclus[posfac].longueur==histoire.filmanu[poschap][posmotif].commandes.exclus[posfac].taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appelé par ::\n\n\""); out(str); out("\"\n\n   il y a trop de mots à exclure dans la "); out(posfac); out("e façon de dire la commande (chaque mot à exclure est séparé par '|', et inclus entre crochets \"[]\"). Augmentez le nombre de mots à exclure dans la classe \"commande\" pour résoudre ce problème."); abort();}
								histoire.filmanu[poschap][posmotif].commandes.exclus[posfac].ajout(mot);		//Enregistrer le mot
							} else {
								if(histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].longueur==0) histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].ajoutvide();	//Noter qu'un nouveau groupe de mots commence
								if(histoire.filmanu[poschap][posmotif].commandes.inclus[posfac][posgr].longueur==histoire.filmanu[poschap][posmotif].commandes.inclus[posfac][posgr].taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appelé par ::\n\n\""); out(str); out("\"\n\n   il y a trop de synonymes dans le "); out(posgr); out("e groupe de la "); out(posfac); out("e façon de dire la commande (chaque synonyme est séparé par '|'). Augmentez le nombre synonymes dans la classe \"commande\" our supprimez les plus farfelus, pour résoudre ce problème."); abort();}
								histoire.filmanu[poschap][posmotif].commandes.inclus[posfac][posgr].ajout(mot);
							}
							mot.clear();			//Vider le string de stockage temporaire
							//Interpréter le caractère exact
							if(str[countstr]=='|') {						//Ne rien faire
							}else if(str[countstr]=='&') {
								if(histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].longueur==histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].taille)  {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appelé par ::\n\n\""); out(str); out("\"\n\n   il y a trop de groupes de mots à inclure dans la "); out(posfac); out("e façon de dire la commande (chaque façon groupe de mot à inclure est séparé par '&'). Augmentez le nombre de groupes de mots à inclure dans la classe \"commande\" ou simplifiez votre commande pour résoudre ce problème."); abort();}						
								posgr++; histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].ajoutvide();
							} else if(str[countstr]==')') {posgr=0; posfac++;
							} else if(str[countstr]==']') {exclus = false;
							}
						} 
					} else mot+=str[countstr];		//Ajouter la lettre si c'est un caractère simple	
				}
			}
		}
		
		//l) Fonction pour définir les commandes exactes qui appeleront le motif (manuel)
		void univers::mcommexact(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();
			int debmot = 0;			//Noter la position d'indexation du début du mot
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='|') {
					if(histoire.filmanu[poschap][posmotif].commandes.exact.longueur==histoire.filmanu[poschap][posmotif].commandes.exact.taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appelé par les commandes exactes :\n\n\""); out(str); out("\"\n\n   il y a trop de façons exactes d'appeler le motif (séparées par '|'). Augmentez le nombre de façons exactes différentes dans la classe \"commande\" ou changez de méthode pour des groupes de mots, ou encore divisez le motif en deux motifs différents, pour résoudre ce problème."); abort();}					
					if(countstr-debmot>0){ 
						histoire.filmanu[poschap][posmotif].commandes.exact.ajout(strintervalle(str,debmot,countstr-1));
					} else histoire.filmanu[poschap][posmotif].commandes.exact.ajout(""); //Si deux ';' se suivent, mettre *RIEN* comme commande exacte possible
					debmot = countstr + 1;
				}
			}	
			if(histoire.filmanu[poschap][posmotif].commandes.exact.longueur==histoire.filmanu[poschap][posmotif].commandes.exact.taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appelé par les commandes exactes :\n\n\""); out(str); out("\"\n\n   il y a trop de façons exactes d'appeler le motif (séparées par '|'). Augmentez le nombre de façons exactes différentes dans la classe \"commande\" ou changez de méthode pour des groupes de mots, ou encore divisez le motif en deux motifs différents, pour résoudre ce problème."); abort();}								
			if(debmot!=strnb) histoire.filmanu[poschap][posmotif].commandes.exact.ajout(strintervalle(str,debmot,strnb-1));		//Entrer le dernier mot
		}
		
	//iv) Fonctions pour remplir les menus	----------------------------------------------------------------------			
	
		//a) Fonction pour créer un nouveau menu (et lui donner un nom)
		void univers::nvmenu(const string& str) {menus.ajoutvide(); nommenus.ajout(str);}

		//b) Fonction pour ajouter un dessin en background au menu
		void univers::menubg(const string& str, int nbligne)  {
			if(str.length()%nbligne!=0) {int nbcharstr = str.length(); out("Le dessin en backgound du menu \""); out(nommenus[menus.longueur-1]); out("\" a "); out(nbligne); out(" lignes, mais possèdent "); out(nbcharstr); out(" caractères (il y a des lignes qui ne sont pas complètement remplies - il devrait y avoir "); out(ceiling(nbcharstr/nbligne)*nbligne); out(" caractères)."); abort();}
			menus[menus.longueur-1].bgdessin = str; 
			menus[menus.longueur-1].bgdessinnbligne = nbligne; 
			menus[menus.longueur-1].isbgdessin = true;
			}
		
		//c) Fonction pour définir un point d'intérêt ainsi que sa position souhaitée pour le dessin de background
		void univers::menubgpointinteret(int coordx, int coordy, double fractionfenetrex, double fractionfenetrey) {
			menus[menus.longueur-1].bgptinteretx = coordx; menus[menus.longueur-1].bgptinterety = coordy; 
			menus[menus.longueur-1].bgposinteretx = fractionfenetrex; menus[menus.longueur-1].bgposinterety = fractionfenetrey; 
		}
		
		//d) Fonction pour définir des côtés comme "bloqués" pour le dessin de background, afin qu'ils restent contre le bord de la fenêtre dans les fenêtres trop grandes
		void univers::menubglock(const string& str) {
			if(str.length()==4&&str[0]=='l'&&str[1]=='e'&&str[2]=='f'&&str[3]=='t') { menus[menus.longueur-1].bgleftlocked = true; menus[menus.longueur-1].bgrightlocked = false; 
			} else if(str.length()==5&&str[0]=='r'&&str[1]=='i'&&str[2]=='g'&&str[3]=='h'&&str[4]=='t') { menus[menus.longueur-1].bgrightlocked = true; menus[menus.longueur-1].bgleftlocked = false;
			} else if(str.length()==3&&str[0]=='t'&&str[1]=='o'&&str[2]=='p'){  menus[menus.longueur-1].bgtoplocked = true; menus[menus.longueur-1].bgbottomlocked = false;
			} else if(str.length()==6&&str[0]=='b'&&str[1]=='o'&&str[2]=='t'&&str[3]=='t'&&str[4]=='o'&&str[5]=='m') { menus[menus.longueur-1].bgbottomlocked = true; menus[menus.longueur-1].bgtoplocked = false;
			} else {out("\nLe côté bloqué du menu \""); out(nommenus[menus.longueur-1]); out("\" nommé comme \""); out(str); out("\" ne correspond pas aux valeurs admises, soit \"left\", \"right\", \"top\" ou \"bottom\"."); abort();}
		}
		
		//e) Fonction pour ajouter un titre en format texte ("string") au menu
		void univers::menutitretxt(const string& str) {menus[menus.longueur-1].titretxt = str;}
		
		//f) Fonction pour ajouter un titre en format dessin au menu
		void univers::menutitredessin(const string& str, int nbligne) {
			if(str.length()%nbligne!=0) {int nbcharstr = str.length(); out("Le dessin en titre du menu \""); out(nommenus[menus.longueur-1]); out("\" a "); out(nbligne); out(" lignes, mais possèdent "); out(nbcharstr); out(" caractères (il y a des lignes qui ne sont pas complètement remplies - il devrait y avoir "); out(ceiling(nbcharstr/nbligne)*nbligne); out(" caractères)."); abort();}
			menus[menus.longueur-1].titredessin = str; 
			menus[menus.longueur-1].titredessinnbligne = nbligne; 
			menus[menus.longueur-1].istitredessin = true;
			}
		
		//g) Fonction pour ajuster la hauteur du titre du menu
		void univers::menutitrehauteur(double val) {menus[menus.longueur-1].titrehauteur = val;}
		
		//h) Fonctions pour choisir les dimensions des boutons du menu	
		void univers::menulargeurbouton(int val) {menus[menus.longueur-1].largeurbouton = val;}
		void univers::menuhauteurbouton(int val) {menus[menus.longueur-1].hauteurbouton = val;}
		void univers::menuespacebouton(int val) {menus[menus.longueur-1].espacebouton = val;}
		
		//i) Fonctions pour choisir les vitesses de déplacement et de sélection du menu
		void univers::menuselectdelay(int val) {menus[menus.longueur-1].selectdelay = val;} 
		void univers::menuenterdelay(int val) {menus[menus.longueur-1].enterdelay = val;} 
		
		//j) Fonction pour ajouter un bouton à ce menu, et lui lier des effets
		void univers::menunvbouton(const string& strbout, const string& streff) {
			//Faire les comptes nécessaires pour voir si le texte du bouton rentre dans l'espace alloué
			int nbligne = 0; int nbcol = 0;
			for(int countstr=0; countstr<strbout.length(); countstr++) {
				if(strbout[countstr]=='\n') {nbligne++; nbcol =0;} else nbcol++;
				if(nbcol>menus[menus.longueur-1].largeurbouton - 4) {out("L'option \""); out(strbout); out("\" du menu \""); out(nommenus[menus.longueur-1]); out("\" a des lignes plus longue que "); out(menus[menus.longueur-1].largeurbouton-4); out(" caractères (soit la longueur maximale). Pour y remédier, trouver un nom plus court, mettre le nom sur davantage de lignes (en utilisant '\\n') ou agrandir tous les \"boutons\" des menus."); abort();}
				if(nbligne>menus[menus.longueur-1].hauteurbouton - 2) {out("L'option \""); out(strbout); out("\" du menu \""); out(nommenus[menus.longueur-1]); out("\" occupe plus de lignes que "); out(menus[menus.longueur-1].hauteurbouton-2); out(" (soit la hauteur maximale du texte). Pour y remédier, trouver un nom plus court, le séparer en moins de fragments (en retirant des '\\n') ou agrandir tous les \"boutons\" des menus."); abort();}				
			}
			menus[menus.longueur-1].boutons.ajout(strbout); menus[menus.longueur-1].effets.ajout(streff);
		}
		
		//k) Fonction pour définir l'effet de la touche ESC à l'intérieur de ce menu
		void univers::menuescape(const string& str) {menus[menus.longueur-1].effetescape = str;}
		
		//m) Fonction pour définir quel menu appelera la touche ESC lorsque le jeu est en cours
		void univers::menuingameescape(const string& str) {quelmenuingameescape = str;} 
	
	//v) Fonctions pour tester le contenu	----------------------------------------------------------------------		
	
		//a) Fonction pour voir tous les enchaînements
		void univers::menchainetest() {
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;			
			base.curspos(0,0);
			for(int countench=0; countench<histoire.filmanu[poschap][posmotif].ordrespecifique.longueur; countench++) {
				out(countench); out(") : ");
				for(int countmaille=0; countmaille<histoire.filmanu[poschap][posmotif].ordrespecifique[countench].longueur; countmaille++) {
					out(histoire.filmanu[poschap][posmotif].maille[histoire.filmanu[poschap][posmotif].ordrespecifique[countench][countmaille]]);
				}
				out("\n\n");						
			}
		}
		void univers::aenchainetest() {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;			
			base.curspos(0,0);
			for(int countench=0; countench<histoire.filauto[poschap][posmotif].ordrespecifique.longueur; countench++) {
				out(countench); out(") : ");
				for(int countmaille=0; countmaille<histoire.filauto[poschap][posmotif].ordrespecifique[countench].longueur; countmaille++) {
					out(histoire.filauto[poschap][posmotif].maille[histoire.filauto[poschap][posmotif].ordrespecifique[countench][countmaille]]);
				}
				out("\n\n");						
			}
		}	
//------------------------------------------------------------------------------------------------------------------------------------------------------

