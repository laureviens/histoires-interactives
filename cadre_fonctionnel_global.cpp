
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
*/


/*
	2019-07-05:
				Dans les fonctions integration() et UserInputInterpret(),
				j'utilise beaucoup d'indexation. Ça devient difficile à lire.
				Je pense que ça n'alourdirait pas trop l'exécution de créer un objet temporaire pour chaque motif (rendrait le tout plus clair).
				J'ai par contre peur que ça fuck avec les pointeurs, que les objets soient modifiés (sont tous par & référence), etc.
					Je conserve donc cette idée quand j'aurai minimalement une version testée, qui fonctionne.
*/

/*
	2019-07-13:
				Ce qu'il me reste à faire:
					-Peut-être changer la mémoire de "long terme, finie" à "court terme, infinie" en sauvant moins de lignes mais en écrivant par-dessus?
					-Ajouter un menu
					-Retravailler le "menu" de quand la commande est ambigüe, pour la mettre plus en ligne avec le reste des menus
							(à la limite, j'pense sérieusement à simplement avoir une sélection de "peser sur ENTER entre des icônes" pour éviter les erreurs connes de frappe)
							(genre, c'est supposé NE PAS ARRIVER, les ambiguité, si l'histoire est si mal écrite que ça, j'pense que ça va pas déranger de perdre un peu) 
							( d' "immersion"  en sélectionnant un bouton à la place de recopier lettre à lettre un mot. Also, c'est plus facile à coder pour moi.)
											
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
*/

/*
	2019-09-19:
				Oh; il serait pertinent de changer la fonction pour changer de couleur, et de mettre au lieu des références
				à la bibliothèque; genre avoir une fonction "changer couleur à" qui prend un string ou un numéro en argument;
				genre "clignotement" ou quelque chose du genre...? Genre mettre catégories comme "clair", "obscur", "normal"...?
							//Si je le mets dans la bibliothèque, faudra que ce soit en 'int': Donc séparer le back-ground et le texte?
								//Et après, à chaque fois que je change de couleur, de faire la conversion?
									//Et peut-être mettre des systèmes de vérifications à chaque fois que je dois changer la couleur;
										: Est-ce que c'était déjà setté sur 'clair'?		
*/

/*
	2020-02-22
				Les msn marchent (du premier coup! Wouhou!), mais y'a une drôle de pause qui se fait en plein milieu de ma pause.
				C'est assez mineur pour enregistrer sur Git sans le régler; je regarderai ça une autre fois (il se fait tard, et j'ai beaucoup codé).
*/


/*
	2020-02-28:
				J'avais un problème où le texte s'affichait instantannément, et j'avais de la difficulté à m'expliquer pourquoi.
				pour le régler, j'ai fini par changer le temps, qui était exprimé en int, en unsigned.
				Et là tout marche.
				Je pense que le nombre est simplement devenu trop gros pour être exprimé par int? 
						parce que c'est le temps DEPUIS une certaine date, et donc il continue de grandir.
				Pour ne plus avoir ce problème, je ferais mieux de stocker le temps en unsigned, mais aussi de changer la fonction timems() pour qu'elle donne le temps depuis l'exécution du programme
	

*/

/*
	2020-02-15:
				BTW: je relis les tutoriels de c++, et en exemple illes mettent seulement les fonction-membres les plus succintes à l'intérieur de la définition de la classe;
				pour les fonctions membres un peu plus grandes, illes les définissent par après, en-dehors (cela semble être une norme de travail pour elleux).
				Avec la synthaxe:       "void Rectangle::set_values (int x, int y) {}"             (et à l'intérieur de la classe, on retrouve "void set_values (int,int);")
				
				
				BTW, je profite de cette plateforme pour rappeler une autre éthique de travail:
							mettre la plupart des membres comme privés, et y accéder seulement à travers des fonctions-membres publiques.
							Ça permet de mieux retracer les modifications aux valeurs membres, pour éviter les "fuites".
							
							Pis j'devrais écrire "overridecanal()" comme fonction membre, aussi, ça aurait peut-être plus de sens. 
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

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
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
#include <random>				//Nécessaire pour jouer avec des distributions statistiques (uniform_int_distribution, normal_distribution, etc.)	//Nécessite c++11

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Fonctions et objets pour interagir avec la console (Attention: séparé entre Windows et Linux) 	//WINDOWS SEULEMENT EST FAIT!!!

	//i) Classe : consoleobjet ; divers objets permettant de modifier le texte affiché dans la console   	            	//WINDOWS ONLY
	class consoleobjet {
		//Membres
		public:
			HANDLE TxtConsole;									        //Objet permettant de modifier le texte affiché dans la console 
			COORD CursorPosition;                                     	//Objet permettant de se situer sur la console
			CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;                //Objet permettant de connaître la position du curseur dans la console
			CONSOLE_CURSOR_INFO CursorInfo;	                            //Objet permettant de modifier le curseur
			HWND DimConsole;		 			                      //Objet permettant de modifier les dimensions + la position de la console
		//Constructeurs
			//Constructeur par défaut			//Attention, est seulement là pour initier les objets
			consoleobjet() {			
			TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			DimConsole = GetConsoleWindow(); 
			}
	};

	//ii) Fonction: curspos ; déplacer le curseur sur la console                                                          //WINDOWS ONLY
	void curspos(consoleobjet& cons, int x, int y) { 
		cons.CursorPosition.X = x; cons.CursorPosition.Y = y; 
		SetConsoleCursorPosition(cons.TxtConsole,cons.CursorPosition);
	}	
		
	//iii) Fonction: curson ; affiche ou cache le curseur                        		                                   //WINDOWS ONLY
	void curson(consoleobjet& cons, bool visible) // set bool visible = 0 - invisible, bool visible = 1 - visible
	{
		cons.CursorInfo.bVisible = visible; cons.CursorInfo.dwSize = 20;
		SetConsoleCursorInfo(cons.TxtConsole,&cons.CursorInfo);
	}		
		
	//iv) Fonction : chgcol ; change la couleur du texte à entrer                        		                                   //WINDOWS ONLY
	void chgcol(consoleobjet& cons, int txtcol, int bgcol) {
		SetConsoleTextAttribute(cons.TxtConsole, txtcol + 16*bgcol);		//Voir l'entrée du 2020-02-22 pour la légende!
	}
	

	
	//v) Classe : fenetre ; permet de sauvegarder les paramètres relatifs aux caractéristiques de la fenêtre de sortie (console)   	            	//WINDOWS ONLY
	class fenetre {
		//Membres
		public:
			int posfenx, posfeny;     //Positions de la fenêtre sur l'écran                                                    //WINDOWS ONLY
			int sizefenx, sizefeny;   //Taille de la fenêtre en pixel														   //WINDOWS ONLY
			int limfenx, limfeny;     //Dimensions de la fenêtre en terme de nombre de caractères pouvant y être contenus
			int limtxtx, limtxty;     //Dimensions de la portion où le texte s'affiche en terme de nombre de caractères pouvant y être contenus
			int consy;             //Facteur de décalement de la console où apparaît le texte avec la mémoire, où il est stocké
			bool refoule;          //Flag pour voir si le facteur de décalement entre en compte													
		//Constructeurs
			//Constructeur par défaut			//Attention, est seulement là pour initier l'objet hors de la fonction "int main(){}"
			fenetre() {}
		//Fonction de modification : nouvfenetre ; permet de créer une fenêtre de la taille désirée		//Attention! À mettre obligatoirement dans le main()!
		void nouvfenetre(consoleobjet& cons, int posx, int posy, int sizex, int sizey) {
				//MoveWindow(window_handle, x, y, width, height, redraw_window);       //Les unités sont en pixels!
			MoveWindow(cons.DimConsole, posx, posy, sizex, sizey, TRUE);                    //Créer la fenêtre de la bonne taille          //WINDOWS ONLY
			GetConsoleScreenBufferInfo(cons.TxtConsole, &cons.ScreenBufferInfo);                 //Accéder à la taille de la console            //WINDOWS ONLY
			curson(cons,false);                                                     		   //Faire disparaître le curseur                 //WINDOWS ONLY
    		_setmode(_fileno(stdout), _O_U16TEXT);									   //Permettre l'affichage de l'UNICODE           //WINDOWS ONLY  
			limfenx = cons.ScreenBufferInfo.srWindow.Right + 1; limfeny = cons.ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations
			limtxtx = limfenx; limtxty = limfeny - 1;
		}                  //JE PROFITE DE CETTE FONCTION POUR ÉGALEMENT CHANGER LES PARAMÈTRES DE BASE! ATTENTION!	
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
		string strintervalle(string str, int deb, int fin) {
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

	//iv) Fonctions de randomisation	----------------------------------------------------------------------		
	
		//a) Fonction : randseed ; construit un générateur de nombres aléatoires à partir de l'heure d'exécution du programme (volé à http://www.cplusplus.com/reference/random/normal_distribution/operator()/)
		default_random_engine randseed() {
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine rand_nb_gen (seed);
			return(rand_nb_gen);
		}
	  
		//b) Fonction : randunif ; retourne un integer entre [min, max] (les valeurs sont comprises; "inclusivement")
		int randunif(int min, int max, default_random_engine rand_nb_gen) {
			uniform_int_distribution<int> distr(min,max);	//Initier l'objet de classe "uniform_int_distribution"
			return(distr(rand_nb_gen));
		}
		
		//c) Fonction : randnorm ; retourne un integer d'une distribution normale (mean, sd)
		int randnorm(int mean, int sd, default_random_engine rand_nb_gen) {
			normal_distribution<double> distr(mean,sd);	//Initier l'objet de classe "normal_distribution"
			return(round(distr(rand_nb_gen)));
		}
		
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
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("actutxt"); this->modif("couleur","actutxt",8);			//Gris foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("actubg"); this->modif("couleur","actubg",0);				//Noir				
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("cantxt"); this->modif("couleur","cantxt",8);				//Gris foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("canbg"); this->modif("couleur","canbg",0);				//Noir
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("msntxt"); this->modif("couleur","msntxt",7);				//Gris clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("msnbg"); this->modif("couleur","msnbg",0);				//Noir	
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbontxt"); this->modif("couleur","commbontxt",8);		//Gris foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbonbg"); this->modif("couleur","commbonbg",0);		//Noir
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbusytxt"); this->modif("couleur","commbusytxt",4);	//Rouge foncé
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbusybg"); this->modif("couleur","commbusybg",0);		//Noir
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commmauvtxt"); this->modif("couleur","commmauvtxt",12);	//Rouge clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commmauvbg"); this->modif("couleur","commmauvbg",0);		//Noir												
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commpostxt"); this->modif("couleur","commpostxt",15);	//Blanc
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commposbg"); this->modif("couleur","commposbg",0);		//Noir		
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
			
			
			//DEBUGGGGGGG
			void test(bibliotheque& biblio) {if(constbool) out(boolval); else if(constint) out(constint); else out(biblio.acces(rayonpos,livrepos));}
			
				
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
			
			
		//DEBUGGGG	
			void test(bibliotheque& biblio) {
				if(Lcompos){
					if(Rcompos) {
						if(operateur==' ') {LHcompos->test(biblio);} else {LHcompos->test(biblio); out(operateur); RHcompos->test(biblio);}				
					} else {
						if(operateur==' ') {LHcompos->test(biblio);} else {LHcompos->test(biblio); out(operateur); RHsimple->test(biblio);}				
					}
				} else {
					if(Rcompos) {
						if(operateur==' ') {LHsimple->test(biblio);} else {LHsimple->test(biblio); out(operateur); RHcompos->test(biblio);}				
					} else {
						if(operateur==' ') {LHsimple->test(biblio);} else {LHsimple->test(biblio); out(operateur); RHsimple->test(biblio);}				
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
			
			
			//DEBUGGGG
			bool test(bibliotheque& biblio) {
					if(constbool) {LH->test(biblio); out(comparateur); out(comparateur); out(boolval);} else {LH->test(biblio); out(comparateur); out(comparateur); RH->test(biblio);}	
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
			

		//DEBUGGG	
			void test(bibliotheque& biblio) {		
				if(compositeur==' '||compositeur=='!'){
					out(compositeur); if(Lcompos) LHcompos->test(biblio); else LHsimple->test(biblio);
				} else {
					if(Lcompos){
						LHcompos->test(biblio); out(compositeur); 
						if(Rcompos) RHcompos->test(biblio); else RHsimple->test(biblio);
					} else {
						LHsimple->test(biblio); out(compositeur);
						if(Rcompos) RHcompos->test(biblio); else RHsimple->test(biblio);
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
				string nom;									//Nom que porte le canal
				string terminaison;							//Texte à placer juste après toute interruption ("override"), pour en quelque sorte terminer sur une belle note. Peut être changé à tout moment par le code spécial "§t§".
			//Constructeur						
			canal() : delay(150), posx(-1), posy(0), alinea(0), actif(false), nom("defaut"), terminaison(""), nxtt(0), pausedt(0), pause(false) {}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
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
			//Constructeur
			msn() : posdebx(0), posdeby(0), posx(-1), posy(0), delay(80), postxt(0), nbysupp(0), construire(true), attente(false), nxtt(0), pausedt(0), pause(false) {}	//Constructeur par défaut
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
				bool ifexact;													//TRUE si une expression exacte est nécessairement recherchée
			//Constructeur
			commande() : ifexact(false) {};	
		};		
				
		//b) classe : motifauto ; permet le stockage du texte et des conditions d'apparition (automatique)
		class motifauto {
			//Membres
			public:
				StaticVect<string,10> maille;						//Texte à lire
				StaticVect<StaticVect<int,10>,10> enchainement;  	//int réfère aux positions des mailles         
				StaticVect<intoper,10> enchaineprob;        	 	//Avec le même ordre d'indexation que enchaînement
				boolcompos condition;								//Conditions à respecter pour l'ajout au canal sans UserInput 
				string codespeciauxdebut;
				string codespeciauxfin;
				bool override;										//TRUE si l'activation de motif vide instantannément le canal utilisé
				bool encours;										//Va changer dynamiquement, permet de ne pas dédoubler le même motif (± un temps d'attente obligatoire)
				int canal;											//Position du canal dans lequel écrire le texte
				bool msn;											//Si TRUE, le motif va activer un nouveau msn à la place de s'inscrire dans un canal
			//Constructeur
			motifauto() : override(false), encours(false), msn(false) {};
		};
		
		//c) classe : motifmanu ; permet le stockage du texte et des conditions d'apparition (manuelle)
		class motifmanu {
			//Membres
			public:
				StaticVect<string,10> maille;						//Texte à lire
				StaticVect<StaticVect<int,10>,10> enchainement;  	//int réfère aux positions des mailles         
				StaticVect<intoper,10> enchaineprob;        	 	//Avec le même ordre d'indexation que enchaînement
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
			motifmanu() : reserve(true), override(false), msn(false) {};	
		};
		
		//d) classe : ouvrage ; permet de stocker toutes les textes + commandes selon des catégories (ex: chapitres), pour faciliter la recherche
		class ouvrage {
			//Membres
			public:
				static const int taille = 1;												//Nombre de "chapitre" actuellement disponibles
				static const int taillechapitre = 40;
				StaticVect<StaticVect<motifmanu,taillechapitre>,taille> filmanu;		//Groupes de textes + commandes ("chapitres") pour activation manuelle
				StaticVect<StaticVect<motifauto,taillechapitre>,taille> filauto;		//Groupes de textes + commandes ("chapitres") pour activation automatique
				StaticVect<boolcompos,taille> cadenas;										//Conditions d'activation des "chapitres"
		};

//------------------------------------------------------------------------------------------------------------------------------------------------------
//4) Mettre tout dans un seul objet

	//i) Classes contenant tous les objets utiles	----------------------------------------------------------------------		
	class univers {
		//Membres
		public:
			//Membres pour la console
			consoleobjet cons;
			fenetre base;
			//Membres de sauvegarde
			bibliotheque biblio;
			memoire mem;
			msnmemoire msnmem;
			//Membres d'affichage à court terme
			static const int taillecanaux = 2;			//Taille des objets de type StaticVect<canal,Taille>				
			static const int taillemessagerie = 15;		//Taille des objets de type StaticVect<msn,Taille>
			static const int taillegroupes = 5;			//Taille des groupes de mots qui doivent être bons dans une commande; copie de la ligne présente dans "class commande"; pas idéal			
			StaticVect<canal,taillecanaux> canaux;
			StaticVect<string,taillecanaux> nomcanaux;
			StaticVect<msn,taillemessagerie> messagerie;	
			//Membres d'entrées par la joueuse 
			input inp;
			inputecho inpecho;
			//Membre de conditions d'affichage	
			ouvrage histoire;	
			//Membre permettant la randomisation	
			default_random_engine rand_nb_gen;
			//Membre donnant l'heure
			horloge clock;
		//Constructeurs
			//Constructeur par défaut
			univers() {
				default_random_engine rand_nb_gen = randseed();			//Poser un départ unique (basé sur l'heure d'exécution du programme) au générateur de nombres aléatoires
			};
		//Fonctions de jeu
			//Fonctions de petite taille
				void MettreDansLeMain(int posx, int posy, int sizex, int sizey); void MettreDansLeMain();
				void pausecan(int poscan); void pausemsn(int posmsn); void pauseall(); 
				void unpausecan(int poscan); void unpausemsn(int posmsn); void unpauseall();
				void UserInputEcho();
				void overridecanal(int canpos);
				void ReecrireMemoire();
				void ReecrireMsn(int msnpos); void EffacerMsn(int msnpos);
				void chgcolcan(); void chgcolmsn();
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
			//Fonction pour tout coordonner harmonieusement
				void jouer();	
		//Fonction de remplissage aisé
			//Fonctions pour nommer les livres et les rayons de la bibliothèque
				void nvrayon(const string& str);
				void nvlivre(const string& str);
			//Fonctions pour créer de nouveaux canaux et les personaliser
				void nvcanal(const string& str);
				void canaldelai(int val);
				void canalalinea(int val);
			//Fonctions pour organiser les chapitres et les motifs (permettent l'activation des textes)	
				void nvchapt();
				void ccond(const string& str);
				void nvmanu(const string& str);
				void nvauto(); 
			//Fonctions pour remplir les motifs	
				void mcanal(const string& str); void acanal(const string& str);
				void mtexte(const string& str);	void atexte(const string& str);
				void mordre(const string& str); void aordre(const string& str);
				void mprob(const string& str); void aprob(const string& str); 
				void mdeb(const string& str); void adeb(const string& str);												
				void mfin(const string& str); void afin(const string& str);	
				void mcond(const string& str); void acond(const string& str);
				void mover(); void aover();
				void mreserve();
				void mcomm(const string& str); 
				void mcommexact(const string& str);
	};
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//5) Fonctions spécialisées pour la bonne marche du jeu

	//i) Fonctions de petite taille	----------------------------------------------------------------------		

		//a) Fonction : MettreDansLeMain ; Configure la fenêtre de jeu, ainsi que les objets de sauvegarde qui en dépendent		//À exécuter à l'intérieur du "int main() {}"
		void univers::MettreDansLeMain(int posx, int posy, int sizex, int sizey) {
			base.nouvfenetre(cons, posx, posy, sizex, sizey);
			mem.setsize(base.limtxtx);
			msnmem.setsize(base.limtxtx,base.limtxty);	
		}		
		void univers::MettreDansLeMain() {
			base.nouvfenetre(cons, 600, 30, 500, 500);	//Positions par défaut, qui marchaient bien quand je testais
			mem.setsize(base.limtxtx);
			msnmem.setsize(base.limtxtx,base.limtxty);	
		}
		
		//b) Fonction : UserInputEcho ; validant graphiquement l'acceptation ou le refus des commandes envoyées
		void univers::UserInputEcho() {	
			if(inpecho.actif&&inpecho.nxtt<clock.currentt) {
				chgcol(cons,inpecho.txtcol,inpecho.bgcol);
				//Clignoter
				if(inpecho.clignote[0]>0){
					curspos(cons,inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
				} else {
					curspos(cons,inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(' ');		
				}
				chgcol(cons,biblio.acces(biblio.poscouleur,"actutxt"),biblio.acces(biblio.poscouleur,"actubg"));                       //Revenir à la couleur de base	
				inpecho.nxtt = clock.currentt + round(abs(inpecho.clignote[0])*pow(inp.vit,1/2));        //Updater le "next time"		//vit ^ (1/2), pour ne pas TROP modifier la vitesse...
				inpecho.clignote.suppression(1);            //Passer à la prochaine instruction
				if(inpecho.clignote.longueur==0) inpecho.actif = false;			//Vérifier s'il reste toujours du stock à passer dans le canal	
			}	
		}
		
		//c) Fonction : pauseall/unpauseall ; arrête les compteurs des tous les canaux et msn, et les repart
		void univers::pausecan(int poscan) {canaux[poscan].pause = true; canaux[poscan].pausedt = abs(canaux[poscan].nxtt - clock.currentt);}
		void univers::pausemsn(int posmsn) {messagerie[posmsn].pause = true; messagerie[posmsn].pausedt = abs(messagerie[posmsn].nxtt - clock.currentt);}
		void univers::pauseall() {
			for(int poscan=0; poscan<canaux.longueur; poscan++) pausecan(poscan);
			for(int posmsn=0; posmsn<messagerie.longueur; posmsn++) pausemsn(posmsn);
		}
		void univers::unpausecan(int poscan) {canaux[poscan].pause = false; canaux[poscan].nxtt = clock.currentt + canaux[poscan].pausedt + round(canaux[poscan].delay * 5 * inp.vit);}
		void univers::unpausemsn(int posmsn) {messagerie[posmsn].pause = false; messagerie[posmsn].nxtt = clock.currentt + messagerie[posmsn].pausedt + round(messagerie[posmsn].delay * 5 * inp.vit);}
		void univers::unpauseall() {
			for(int poscan=0; poscan<canaux.longueur; poscan++) unpausecan(poscan);
			for(int posmsn=0; posmsn<messagerie.longueur; posmsn++) unpausemsn(posmsn);
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
			canaux[canpos].txt = canaux[canpos].terminaison;      //Remplacer ce qui était dans le canal par la "terminaison" de ce canal (par défaut, c'est "" - c'est à dire rien)
			if(canaux[canpos].txt.length()==0) canaux[canpos].actif = false;           //Désactiver le canal, si le canal est vide
		}

		//e) Fonction ReecrireMemoire()			
		void univers::ReecrireMemoire() {
			curspos(cons,0,0);   //Commencer en haut, puis descendre naturellement
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
				if(messagerie[msnpos].txt[counttxt]=='§') counttxt += CodeSpecialLongueur(strintervalle(messagerie[msnpos].txt,counttxt,messagerie[msnpos].txt.length()-1));	//Skipper les codes spéciaux						
				//Dealer avec les sauts de lignes
				if(posx>=base.limtxtx-1) {posy++; posx = -1;}
				if(messagerie[msnpos].txt[counttxt]=='\n') {posy++;}	
				posx++;			//Updater le posx
				if(messagerie[msnpos].txt[counttxt]!='\n') {curspos(cons,posx,posy); out(messagerie[msnpos].txt[counttxt]);}
				counttxt++;				
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
				if(messagerie[msnpos].txt[counttxt]=='§') counttxt += CodeSpecialLongueur(strintervalle(messagerie[msnpos].txt,counttxt,messagerie[msnpos].txt.length()-1));	//Skipper les codes spéciaux						
				//Dealer avec les sauts de lignes
				if(posx>=base.limtxtx-1) {posy++; posx = -1;}
				if(messagerie[msnpos].txt[counttxt]=='\n') {posy++;}	
				posx++;			//Updater le posx
				if(messagerie[msnpos].txt[counttxt]!='\n') {curspos(cons,posx,posy); out(mem.acces(posx,posy+base.consy));}
				counttxt++;
			}		
		}         

		//h) Fonction chgcolcan/msn
		void univers::chgcolcan(){
			if(biblio.acces(biblio.poscouleur,"actutxt")!=biblio.acces(biblio.poscouleur,"cantxt")||biblio.acces(biblio.poscouleur,"actubg")!=biblio.acces(biblio.poscouleur,"canbg")) {
				chgcol(cons,biblio.acces(biblio.poscouleur,"cantxt"),biblio.acces(biblio.poscouleur,"canbg"));		//Mettre la couleur des canaux
				biblio.modif(biblio.poscouleur,"actutxt",biblio.acces(biblio.poscouleur,"cantxt")); biblio.modif(biblio.poscouleur,"actubg",biblio.acces(biblio.poscouleur,"canbg"));
			}
		}
		void univers::chgcolmsn(){
			if(biblio.acces(biblio.poscouleur,"actutxt")!=biblio.acces(biblio.poscouleur,"msntxt")||biblio.acces(biblio.poscouleur,"actubg")!=biblio.acces(biblio.poscouleur,"msnbg")) {
				chgcol(cons,biblio.acces(biblio.poscouleur,"msntxt"),biblio.acces(biblio.poscouleur,"msnbg"));		//Mettre la couleur des msn
				biblio.modif(biblio.poscouleur,"actutxt",biblio.acces(biblio.poscouleur,"msntxt")); biblio.modif(biblio.poscouleur,"actubg",biblio.acces(biblio.poscouleur,"msnbg"));
			}
		}


	//ii) Fonctions pour transférer le texte d'un motif vers un canal ou un msn	----------------------------------------------------------------------		
		
		//a) Fonction : integration ; ajoute un motif à un canal
		void univers::integrationmanu(int chapitrepos, int motifpos) {
			//Vérifier d'abord si on doit mettre le motif en réserve
			if(histoire.filmanu[chapitrepos][motifpos].reserve&&!inp.reserve) {		//La fonction integrationmanu() ne sera jamais lancée si la réserve est pleine, hormis dans le cas du code spécial "§r§". Donc c'est safe.
				inp.reservechap = chapitrepos; inp.reservemotif = motifpos; inp.reserve = true;
			} else {
				bool msnbool = histoire.filmanu[chapitrepos][motifpos].msn;
				bool msnskip = false; 
				int xpos; int ypos;
				//Vérifier s'il y a de la place pour un nouveau msn (si c'est un msn qui est updaté)
				if(msnbool) {
					//Choisir le msn qui sera utilisé
					bool msnvide = false; bool lignelibrechoisie = false;
					if(messagerie.longueur<messagerie.taille) msnvide = true;
					if(msnvide) {
						//Choisir la position de départ!
							xpos = round(min(max(randnorm(25,15,rand_nb_gen),0),80)*base.limtxtx/100);		//Dist normale(mean=0.25,sd=0.15), bornée à 0% et 80% de la console
							ypos = round(min(max(randnorm(30,20,rand_nb_gen),0),75)*base.limtxty/100);
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
				if(!msnskip){
					//Choisir l'enchaînement à insérer
					int sumprob = 0; StaticVect<int,10> vectprob;
					for(int posprob=0; posprob<histoire.filmanu[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {	//Évaluer chaque probabilité
						sumprob += histoire.filmanu[chapitrepos][motifpos].enchaineprob[posprob].eval(biblio); vectprob[posprob] = sumprob; 
					}
					int randval = randunif(0,sumprob-1,rand_nb_gen);  //Obtenir un integer aléatoire entre [0,sumprob[
					int choix; 
					for(int posprob=0; posprob<histoire.filmanu[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {
						if(randval<vectprob[posprob]) {choix = posprob; break;}
					}	
					//Définir le texte à insérer
					string txtmotif;
					txtmotif += histoire.filmanu[chapitrepos][motifpos].codespeciauxdebut;   //Codes spéciaux début
					for(int posench=0; posench<histoire.filmanu[chapitrepos][motifpos].enchainement[choix].longueur; posench++) {
						txtmotif += histoire.filmanu[chapitrepos][motifpos].maille[histoire.filmanu[chapitrepos][motifpos].enchainement[choix][posench]];
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
						messagerie[messagerie.longueur-1].delay = randnorm(110,10,rand_nb_gen);									//Mettre un délai aléatoire
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
			bool msnskip = false;
			int xpos; int ypos;			
			//Vérifier s'il y a de la place pour un nouveau msn (si c'est un msn qui est updaté)
			if(msnbool) {
				//Choisir le msn qui sera utilisé
				bool msnvide = false; bool lignelibrechoisie = false;
				if(messagerie.longueur<messagerie.taille) msnvide = true;
				if(msnvide) {
					//Choisir la position de départ!
						xpos = round(min(max(randnorm(25,15,rand_nb_gen),0),80)*base.limtxtx/100);		//Dist normale(mean=0.25,sd=0.15), bornée à 0% et 80% de la console
						ypos = round(min(max(randnorm(30,20,rand_nb_gen),0),75)*base.limtxty/100);
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
			if(!msnskip){
				//Choisir l'enchaînement à insérer
				int sumprob = 0; StaticVect<int,10> vectprob;
				for(int posprob=0; posprob<histoire.filauto[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {	//Évaluer chaque probabilité
					sumprob += histoire.filauto[chapitrepos][motifpos].enchaineprob[posprob].eval(biblio); vectprob[posprob] = sumprob; 
				}
				int randval = randunif(0,sumprob-1,rand_nb_gen);  //Obtenir un integer aléatoire entre [0,sumprob[
				int choix; 
				for(int posprob=0; posprob<histoire.filauto[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {
					if(randval<vectprob[posprob]) {choix = posprob; break;}
				}	
				//Définir le texte à insérer
				string txtmotif;
				txtmotif += histoire.filauto[chapitrepos][motifpos].codespeciauxdebut;   //Codes spéciaux début
				for(int posench=0; posench<histoire.filauto[chapitrepos][motifpos].enchainement[choix].longueur; posench++) {
					txtmotif += histoire.filauto[chapitrepos][motifpos].maille[histoire.filauto[chapitrepos][motifpos].enchainement[choix][posench]];
				}		
				txtmotif += histoire.filauto[chapitrepos][motifpos].codespeciauxfin;		//Codes spéciaux fin
				txtmotif += "§m" + to_string(chapitrepos) + ';' + to_string(motifpos) +'§';		//Code spécial permettant d'enlever le status en cours du motif     //Faut convertir les int en string...
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
					messagerie[messagerie.longueur-1].delay = randnorm(100,10,rand_nb_gen);									//Mettre un délai aléatoire
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
						if(canaux[canpos].txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture		
							int val = CodeSpecialExtractInt(canaux[canpos].txt,CodeSpecialLong);       //Extraire le temps que durera la pause
							canaux[canpos].nxtt = clock.currentt + round(val * inp.vit);      //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					
						} else if(canaux[canpos].txt[1]=='d'){      //'d' pour "délai" -> changer le délai entre chaque lettre, donc la vitesse de lecture
							int val = CodeSpecialExtractInt(canaux[canpos].txt,CodeSpecialLong);       //Extraire le temps entre les lettres		
							canaux[canpos].delay = val;
						} else if(canaux[canpos].txt[1]=='t'){      //'t' pour "terminaison" -> changer le texte de terminaison, qui sera ajouté après chaque override (si du texte a effectivement été effacé)
							string nomcanal; string terminaison; int posSpecial = 2;
							while(canaux[canpos].txt[posSpecial] != '¶') nomcanal += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(canaux[canpos].txt[posSpecial] != '§') terminaison += canaux[canpos].txt[posSpecial++];							
							canaux[ColNameFind(nomcanal,nomcanaux)].terminaison = terminaison;
						} else if(canaux[canpos].txt[1]=='g'){		//'g' pour "gender" -> choisir le bon accord   format: §gNomAGenrer(féminin;non binaire/neutre;masculin)§
							int genreselect;										 //Sélectionner le genre
								string NomAGenrer;
								for(int posSpecial=2;posSpecial<CodeSpecialLong;posSpecial++) {
									if(canaux[canpos].txt[posSpecial]=='(') {break; 			//Sortir de la boucle si on a atteint la fin du Nom-À-Genrer           
									} else NomAGenrer += canaux[canpos].txt[posSpecial];							//PEUT-ÊTRE OPTIMISER CETTE BOUCLE AVEC strintervalle()????????
								}
								genreselect = biblio.acces(biblio.posgenre,ColNameFind(NomAGenrer,biblio.nomlivre[biblio.posgenre]));		//Le rayon "genre" de la bibliothèque contient le genre de tous les personnages (0 = féminin, 1 = non binaire, 2 = masculin)
							int genreactuel = 0;										//Aller chercher le bon accord
								int posdebut = 3; int posfin = CodeSpecialLong - 2;		//Valeurs par défauts		//Code spécial Long -2 : pour ne pas avoir ")§" à la fin!
								for(int posSpecial=3;posSpecial<CodeSpecialLong; posSpecial++) {				 //Délimiter le bon accord				
									if(canaux[canpos].txt[posSpecial]==';') {
										genreactuel++;
										if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect+1) posfin = posSpecial - 1;
									}
								}
							string temporairetxt;										//Ajouter le bon accord à la suite du code spécial 
								temporairetxt  += strintervalle(canaux[canpos].txt,0,CodeSpecialLong-1); 		//Ajouter le code spécial
								temporairetxt += strintervalle(canaux[canpos].txt,posdebut,posfin); 		//Ajouter le bon accord
								temporairetxt += strintervalle(canaux[canpos].txt,CodeSpecialLong,canaux[canpos].txt.length()-1);	//Ajouter le reste du texte	
								canaux[canpos].txt = temporairetxt;
						} else if(canaux[canpos].txt[1]=='b'){		//'b' pour "biblio" -> modifier la bibliothèque
							string nomrayon; string nomlivre; string val;
							int posSpecial = 2;
							while(canaux[canpos].txt[posSpecial] != '¶') nomrayon += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(canaux[canpos].txt[posSpecial] != '=') nomlivre += canaux[canpos].txt[posSpecial++];
							posSpecial++; while(canaux[canpos].txt[posSpecial] != '§') val += canaux[canpos].txt[posSpecial++];							
							biblio.modif(nomrayon,nomlivre,stoi(val));	
							AutoInterpret();      //Vérifier si un motif automatique doit être intégré aux canaux/msn	
						} else if(canaux[canpos].txt[1]=='m'){		//'m' pour "motif" -> marquer le motif automatique comme n'étant plus en cours			
							string poschap; string posmotif;
							int posSpecial = 2;
							while(canaux[canpos].txt[posSpecial] != ';') poschap += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(canaux[canpos].txt[posSpecial] != '§') posmotif += canaux[canpos].txt[posSpecial++];
							histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //Désigner le motif signalé comme n'étant plus en 
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
									curspos(cons,0,mem.accesfrontline()-base.consy); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout ré-écrire, mais une ligne plus haut
			    					curspos(cons,0,0);   //Commencer en haut, puis descendre naturellement
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
									curspos(cons,0,mem.accesfrontline()-base.consy-1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
									curspos(cons,0,mem.accesfrontline()-base.consy); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout ré-écrire la mémoire, mais une ligne plus haut
			    					curspos(cons,0,0);   //Commencer en haut, puis descendre naturellement
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
						} else if(canaux[canpos].txt[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionné
							string canaloverr = strintervalle(canaux[canpos].txt,2,CodeSpecialLong-2);   //Obtenir le nom du canal à overrider
							overridecanal(ColNameFind(canaloverr,nomcanaux)); 						
						} else if(canaux[canpos].txt[1]=='f') {		//'f' pour "freeze" -> mettre en pause tous les canaux et msn, sauf celui-ci
							if(canaux[canpos].txt[2]=='1')	{		//FREEZE
								for(int countcan=0; countcan<canaux.longueur; countcan++) if(countcan!=canpos) pausecan(countcan);
								for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) pausemsn(countmsn);				
							} else if(canaux[canpos].txt[2]=='0')	{		//UN-FREEZE
								for(int countcan=0; countcan<canaux.longueur; countcan++) if(countcan!=canpos) unpausecan(countcan);
								for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) unpausemsn(countmsn);
							}
						}
						   //AUTRE CODE SPÉCIAL?
					//Effacer le code spécial du canal
					canaux[canpos].txt = strintervalle(canaux[canpos].txt,CodeSpecialLong,canaux[canpos].txt.length()-1);				//J'COMPRENDS PAS LE "+1" DANS "CodeSpecialLong+1"!!!!!!
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
										curspos(cons,0,canaux[canpos].posy+1);  //Mettre le curseur au début de la reconstruction
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
									curspos(cons,0,canaux[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout ré-écrire, mais une ligne plus haut
			    					curspos(cons,0,0);   //Commencer en haut, puis descendre naturellement
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
								if(msnmem.accescase(alinpos,canaux[canpos].posy-base.consy)) {curspos(cons,alinpos,canaux[canpos].posy-base.consy) ; out(' ');}  //Inscrire dans la console seulement si la place n'est pas déjà prise par un msn
								mem.modif(alinpos,canaux[canpos].posy,' '); 		
								canaux[canpos].posx++;
							}
						}}
						//Inscrire le caractère dans la console seulement si la place n'est pas déjà prise par un msn
						if(msnmem.accescase(canaux[canpos].posx,canaux[canpos].posy-base.consy)) {curspos(cons,canaux[canpos].posx,canaux[canpos].posy-base.consy) ; out(canaux[canpos].txt[0]);} 
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
							if(txtrc[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture		
								double val = CodeSpecialExtractInt(txtrc,CodeSpecialLong);       //Extraire le temps que durera la pause
								messagerie[msnpos].nxtt = clock.currentt + round(val * inp.vit);     //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					
							} else if(txtrc[1]=='d'){      //'d' pour "délai" -> changer le délai entre chaque lettre, donc la vitesse de lecture
								int val = CodeSpecialExtractInt(txtrc,CodeSpecialLong);       //Extraire le temps entre les lettres		
								messagerie[msnpos].delay = val;					
							} else if(txtrc[1]=='t'){      //'t' pour "terminaison" -> changer le texte de terminaison, qui sera ajouté après chaque override (si du texte a effectivement été effacé)
								string nomcanal; string terminaison; int posSpecial = 2;
								while(txtrc[posSpecial] != '¶') nomcanal += txtrc[posSpecial++]; 
								posSpecial++; while(txtrc[posSpecial] != '§') terminaison += txtrc[posSpecial++];							
								canaux[ColNameFind(nomcanal,nomcanaux)].terminaison = terminaison;
							} else if(txtrc[1]=='g'){		//'g' pour "gender" -> choisir le bon accord   format: §gNomAGenrer(féminin;non binaire/neutre;masculin)§
								int genreselect;										 //Sélectionner le genre
									string NomAGenrer;
									for(int posSpecial=2;posSpecial<CodeSpecialLong;posSpecial++) {
										if(txtrc[posSpecial]=='(') {break; 			//Sortir de la boucle si on a atteint la fin du Nom-À-Genrer           
										} else NomAGenrer += txtrc[posSpecial];							//PEUT-ÊTRE OPTIMISER CETTE BOUCLE AVEC strintervalle()????????
									}
									genreselect = biblio.acces(biblio.posgenre,ColNameFind(NomAGenrer,biblio.nomlivre[biblio.posgenre]));		//Le rayon "genre" de la bibliothèque contient le genre de tous les personnages (0 = féminin, 1 = non binaire, 2 = masculin)
								int genreactuel = 0;										//Aller chercher le bon accord
									int posdebut = 3; int posfin = CodeSpecialLong - 2;		//Valeurs par défauts			//Code spécial Long -2 : pour ne pas avoir ")§" à la fin!
									for(int posSpecial=3;posSpecial<CodeSpecialLong; posSpecial++) {				 //Délimiter le bon accord				
										if(txtrc[posSpecial]==';') {
											genreactuel++;
											if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect+1) posfin = posSpecial - 1;
										}
									}
								string temporairetxt;										//Ajouter le bon accord à la place du code spécial dans le texte à lire
									temporairetxt += strintervalle(messagerie[msnpos].txt, 0, posrc);	//Ajouter le texte avant le code spécial
									temporairetxt += strintervalle(txtrc, posdebut, posfin);			//Ajouter le bon accord
									temporairetxt += strintervalle(txtrc,CodeSpecialLong,messagerie[msnpos].txt.length()-1);				//Ajouter le reste du texte
									messagerie[msnpos].txt = temporairetxt;
									messagerie[msnpos].postxt -= (CodeSpecialLong);					//Neutraliser l'avancement de la position qui va venir après, puisqu'on a supprimé le code spécial
							} else if(txtrc[1]=='b'){		//'b' pour "biblio" -> modifier la bibliothèque
								string nomrayon; string nomlivre; string val;
								int posSpecial = 2;
								while(txtrc[posSpecial] != '¶') nomrayon += txtrc[posSpecial++]; 
								posSpecial++; while(txtrc[posSpecial] != '=') nomlivre += txtrc[posSpecial++];
								posSpecial++; while(txtrc[posSpecial] != '§') val += txtrc[posSpecial++];							
								biblio.modif(nomrayon,nomlivre,stoi(val));	
								AutoInterpret();      //Vérifier si un motif automatique doit être intégré aux canaux/msn	
							} else if(txtrc[1]=='m'){		//'m' pour "motif" -> marquer le motif automatique comme n'étant plus en cours			
								string poschap; string posmotif;
								int posSpecial = 2;
								while(txtrc[posSpecial] != ';') poschap += txtrc[posSpecial++]; 
								posSpecial++; while(txtrc[posSpecial] != '§') posmotif += txtrc[posSpecial++];
								histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //Désigner le motif signalé comme n'étant plus en cours
							} else if(txtrc[1]=='r'){		//'r' pour "réserve" -> intégrer les motifs manuels qui attendent dans la réserve; sert à ne pas couper une phrase en deux
								if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);									
										//Pas de codes spéciaux 's' ou 'c', car les msn ne s'inscrivent pas dans la mémoire
							} else if(txtrc[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionné
								string canaloverr = strintervalle(txtrc,2,CodeSpecialLong-2);   //Obtenir le nom du canal à overrider
								overridecanal(ColNameFind(canaloverr,nomcanaux)); 						
							} else if(txtrc[1]=='f') {		//'f' pour "freeze" -> mettre en pause tous les canaux et msn, sauf celui-ci
								if(txtrc[2]=='1'){				//FREEZE
									for(int countcan=0; countcan<canaux.longueur; countcan++) pausecan(countcan);													
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) pausemsn(countmsn);	
								} else if(txtrc[2]=='0'){		//UN-FREEZE
									for(int countcan=0; countcan<canaux.longueur; countcan++) unpausecan(countcan);
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) unpausemsn(countmsn);
								}
							}
							   //AUTRE CODE SPÉCIAL?				
						//Passer à la prochaine position du texte à lire
						messagerie[msnpos].postxt += (CodeSpecialLong);
					} else 	messagerie[msnpos].postxt -= CodeSpecialLongueurInv(strintervalle(messagerie[msnpos].txt,0,posrc));		//Si le msn est en déconstruction 			
				} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
					//Updater le "next time"
						if(messagerie[msnpos].construire) {messagerie[msnpos].nxtt = clock.currentt + round(messagerie[msnpos].delay * inp.vit);
						} else messagerie[msnpos].nxtt = clock.currentt + round((messagerie[msnpos].delay * inp.vit)*pow(messagerie[msnpos].postxt/messagerie[msnpos].txt.length(),1/2) );	//Ça s'efface de plus en plus vite (mais pas trop)!
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
														if(txtrc[1]=='b'){		//'b' pour "biblio" -> modifier la bibliothèque
															string nomrayon; string nomlivre; string val;
															int posSpecial = 2;
															while(txtrc[posSpecial] != '¶') nomrayon += txtrc[posSpecial++]; 
															posSpecial++; while(txtrc[posSpecial] != '=') nomlivre += txtrc[posSpecial++];
															posSpecial++; while(txtrc[posSpecial] != '§') val += txtrc[posSpecial++];							
															biblio.modif(nomrayon,nomlivre,stoi(val));	
															AutoInterpret();      //Vérifier si un motif automatique doit être intégré aux canaux/msn	
														} else if(txtrc[1]=='m'){		//'m' pour "motif" -> marquer le motif automatique comme n'étant plus en cours			
															string poschap; string posmotif;
															int posSpecial = 2;
															while(txtrc[posSpecial] != ';') poschap += txtrc[posSpecial++]; 
															posSpecial++; while(txtrc[posSpecial] != '§') posmotif += txtrc[posSpecial++];
															histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //Désigner le motif signalé comme n'étant plus en cours
														} else if(txtrc[1]=='r'){		//'r' pour "réserve" -> intégrer les motifs manuels qui attendent dans la réserve; sert à ne pas couper une phrase en deux
															if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);																										
														} else if(txtrc[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionné
															string canaloverr = strintervalle(txtrc,2,CodeSpecialLong-1);   //Obtenir le nom du canal à overrider
															overridecanal(ColNameFind(canaloverr,nomcanaux)); 	
														} else if(txtrc[1]=='f') {		//'f' pour "freeze" -> mettre en pause tous les canaux et msn, sauf celui-ci
															if(txtrc[2]=='1'){				//FREEZE
																for(int countcan=0; countcan<canaux.longueur; countcan++) pausecan(countcan);
																for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) pausemsn(countmsn);					
															} else if(txtrc[2]=='0'){		//UN-FREEZE
																for(int countcan=0; countcan<canaux.longueur; countcan++) unpausecan(countcan);
																for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) unpausemsn(countmsn);
															}
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
								curspos(cons,messagerie[msnpos].posx,messagerie[msnpos].posy); out(messagerie[msnpos].txt[posrc]);	//Inscrire le caractère dans la console
								msnmem.modifcase(messagerie[msnpos].posx, messagerie[msnpos].posy, false); 						//Noter que la position est prise par un msn				
							} else {									//Si on est en train d'effacer
								chgcolcan();	//Mettre la bonne couleur
								curspos(cons,messagerie[msnpos].posx,messagerie[msnpos].posy); out(mem.acces(messagerie[msnpos].posx,messagerie[msnpos].posy+base.consy));     //Remettre la console comme elle était
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
								
          
	//iii) Fonctions pour recevoir et interpréter les commandes de la joueuse	----------------------------------------------------------------------		
                  
		//a) Fonction : UserInputInterpret ; vérifie si la commande entrée correspond à une des actions actuellement autorisée
			void univers::UserInputInterpret() {
				//Créer des compteurs
				StaticVect<int,20> bonchapitre;	  //Créer des StaticVect pour noter la position des motifs qui correspondent à la commande
				StaticVect<int,20> bonmotif;											//Taille arbitraire de 20; j'espère qu'aucune commande n'appelera simultannément 20 maillons
				StaticVect<bool,taillegroupes> groupebon; 	   	 //Créer un StaticVect pour noter si chaque groupe de mot est bon
				int diffpos; bool exactbon; int commpos; bool exactmauvais; 	//Créer les compteurs pour les expressions exactes
				int groupepos; int synpos; int motpos; int precedpos; bool inclusbon; bool exclusbon;	//Créer les compteurs pour les mots à inclure/exclure	
				//Pour chaque chapitre
				for(int chapitrepos=0; chapitrepos<histoire.filmanu.longueur; chapitrepos++) { if(histoire.cadenas[chapitrepos].eval(biblio)) {			
					//Pour chaque motif dans l'histoire
					for(int motifpos=0; motifpos<histoire.filmanu[chapitrepos].longueur; motifpos++) {if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)) {
						if(histoire.filmanu[chapitrepos][motifpos].commandes.ifexact) {	//Si une commande exacte est nécessaire
							diffpos = 0; exactbon = false;
							while(diffpos<histoire.filmanu[chapitrepos][motifpos].commandes.exact.longueur&&!exactbon) {
								commpos = 0; exactmauvais = false;
								while(!exactmauvais&&commpos<inp.commande.longueur) {if(inp.commande[commpos]!=histoire.filmanu[chapitrepos][motifpos].commandes.exact[diffpos][commpos]) exactmauvais = true; else commpos++;}	
								if(exactmauvais==false) exactbon = true; else diffpos++;
							}
							if(exactbon)	{         //Intégrer tout de suite le bon motif dans le canal					
								inp.accepted = true; if(histoire.filmanu[bonchapitre[0]][bonmotif[0]].reserve) inp.reserve = true;		//Envoyer le bon message au gestionnaire d'Input					
								integrationmanu(chapitrepos,motifpos); return;            //Intégrer le bon motif dans le canal
							}   
						} else {								//Si plusieurs mots clés doivent être présents
							inclusbon = false; diffpos = 0;
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
					}}
				}}
				//Maintenant, on a l'information sur quels motifs correspondent (sans expression exacte) à la commande
				if(bonmotif.longueur==0) {
					inp.accepted = false; 			
					return;
				} else if(bonmotif.longueur==1) {	
					inp.accepted = true; if(histoire.filmanu[bonchapitre[0]][bonmotif[0]].reserve) inp.reserve = true;		//Envoyer le bon message au gestionnaire d'Input					
					integrationmanu(bonchapitre[0],bonmotif[0]); return;            //Intégrer le bon motif dans le canal
				} else {
					//Déterminer si la commande correspond au titre d'un canal
					int bonpos = 0; exactbon = false; 
					while(bonpos<bonmotif.longueur&&!exactbon) {
						exactmauvais = false; commpos = 0;
							while(!exactmauvais&&commpos<inp.commande.longueur) {if(inp.commande[commpos]!=histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre[commpos]) exactmauvais = true; else commpos++;}	
							if(exactmauvais==false) {
								exactbon = true; 	
								inp.accepted = true; if(histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].reserve) inp.reserve = true;							
								integrationmanu(bonchapitre[bonpos],bonmotif[bonpos]); return;}            //Intégrer tout de suite le bon motif dans le canal	
					}	
					//Si l'ambiguité demeure: mettre le jeu sur pause, et faire apparaître les options	
					pauseall();
					chgcol(cons,8,0); curspos(cons,0,0);		//Recopier tout le texte affiché dans la console, mais en gris foncé (background)
					for(int county = base.consy ; county <= mem.accesfrontline(); county++) {   
						for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
					}			
					chgcol(cons,15,0); curspos(cons,5,3); int cursorposy = 3;
					clock.egrener("Vouliez-vous dire (recopiez la ligne qui correspond à votre choix) :",160);
					for(int bonpos=0; bonpos<bonmotif.longueur; bonpos++) {
						if(bonpos==bonmotif.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(cons,2,cursorposy); clock.egrener("ou",120);}}
						cursorposy+=2; if(cursorposy<base.limtxty) {curspos(cons,2,cursorposy);; clock.egrener(histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre,120);}
						if(bonpos==bonmotif.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(cons,2,cursorposy); clock.egrener("              ?",120);}}				
					}
					string reformulation;
					cin >> reformulation;
						//Vérifier de nouveau
						bonpos = 0; exactbon = false; 
						while(bonpos<bonmotif.longueur&&!exactbon) {
							exactmauvais = false; commpos = 0;
								while(!exactmauvais&&commpos<reformulation.length()) {if(reformulation[commpos]!=histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre[commpos]) exactmauvais = true; else commpos++;}	
								if(exactmauvais==false) {
									exactbon = true; 
									curspos(cons,3,0); chgcol(cons,8,0); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,base.consy + 3)); chgcol(cons,15,0);
									clock.stop(800);
									curspos(cons,3,2); clock.egrener("Parfait.",220);		
									clock.stop(1500);
									curspos(cons,0,0); for(int county = base.consy ; county <= mem.accesfrontline() ; county++) {for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));}			
									unpauseall();
									inp.accepted = true; if(histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].reserve) inp.reserve = true;		//Envoyer le bon message au gestionnaire d'Input							
									integrationmanu(bonchapitre[bonpos],bonmotif[bonpos]); return;}            //Intégrer tout de suite le bon motif dans le canal	
						}				
					//Si l'ambiguité persiste: le demander une dernière fois
					curspos(cons,3,0); chgcol(cons,8,0); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,base.consy + 3)); chgcol(cons,15,0);
					curspos(cons,3,3); clock.egrener("Vouliez-vous dire (recopiez EXACTEMENT la ligne qui correspond à votre choix) :",200);
					cin >> reformulation;	
						//Vérifier de nouveau
						bonpos = 0; exactbon = false; 
						while(bonpos<bonmotif.longueur&&!exactbon) {
							exactmauvais = false; commpos = 0;
								while(!exactmauvais&&commpos<reformulation.length()) {if(reformulation[commpos]!=histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre[commpos]) exactmauvais = true; else commpos++;}	
								if(exactmauvais==false) {
									exactbon = true; 
									curspos(cons,3,0); chgcol(cons,8,0); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,base.consy + 3)); chgcol(cons,15,0);
									clock.stop(800);
									curspos(cons,3,2); clock.egrener("C'est bon.",220);		
									clock.stop(1500);
									curspos(cons,0,0); for(int county = base.consy ; county <= mem.accesfrontline() ; county++) {for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));}			
									unpauseall();
									inp.accepted = true; if(histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].reserve) inp.reserve = true;		//Envoyer le bon message au gestionnaire d'Input
									integrationmanu(bonchapitre[bonpos],bonmotif[bonpos]); return;}            //Intégrer tout de suite le bon motif dans le canal	
						}				
					//Si l'ambiguité est insolvable
					curspos(cons,3,0); chgcol(cons,15,0); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,base.consy + 3)); chgcol(cons,15,0);
					clock.stop(800);
					curspos(cons,3,4); clock.egrener("Ce n'est toujours pas clair.   Too bad.",240);			
					clock.stop(3000);
					chgcol(cons,biblio.acces(biblio.poscouleur,"cantxt"),biblio.acces(biblio.poscouleur,"canbg")); ReecrireMemoire();		
					unpauseall();
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
									curspos(cons,inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
								}          //Remettre en gris la position précédente
								inp.inputpos--;  
							}
						}
						else if (intkey == 77) {											 	 //flèche droite : avancer dans la commande tapée				
							if(inp.inputpos!=inp.commande.longueur) {
								curspos(cons,inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
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
								curspos(cons,inp.inputpos,base.limtxty);
								for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);    
								out(' ');
							}
						}
					} else 	{                                        //La valeur est "normale"
						//Touches-fonctions
						if(intkey == 27) {														 //Escape : terminer le programme
							curspos(cons,0,base.limtxty); out("Vous avez entré ESC, le programme se ferme donc."); abort(); 
						} else if(intkey == 13) {												 //Enter : envoyer la commande
							enter = true;
						} else if(intkey == 8) {                                                //Backspace : supprimer le caractère précédent
							if(inp.inputpos!=0) {
								inp.inputpos--;
								inp.commande.supprposition(inp.inputpos);   
								curspos(cons,inp.inputpos,base.limtxty);
								for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);   
								out(' ');    					
							}
						
						//DEBUGGG	
						} else if(intkey==14) {														//Ctrl + n : Donne la vitesse actuelle
							curspos(cons,2,20); out("Voici la vitesse actuelle : "); out(inp.vit);				
						
						//DEBUGGG	
						} else if(intkey==11) {														//Ctrl + k : Vérifie manuellement s'il y a des mailles automatiques à intégrer
							AutoInterpret();   					
						
						//DEBUGGG	
						} else if(intkey==20) {														//Ctrl + t : Donne le status des conditions de chaque motif manuel
							curspos(cons,2,8); out("Voici les conditions des "); out(histoire.filmanu[0].longueur); out(" chaînons manu :");
							for(int posmotif=0; posmotif<histoire.filmanu[0].longueur; posmotif++) {
								curspos(cons,2,9+posmotif); out("     Chaînon "); out(posmotif); out(" : ");
								histoire.filmanu[0][posmotif].condition.test(biblio); 
								if(histoire.filmanu[0][posmotif].condition.eval(biblio)) out("  : TRUE"); else out("  : FALSE");
							}
							//abort();
			
						//DEBUGGG	
						} else if(intkey==25) {														//Ctrl + y : Donne le status des conditions de chaque motif automatique
							curspos(cons,2,8); out("Voici les conditions des "); out(histoire.filauto[0].longueur); out(" chaînons auto :");
							for(int posmotif=0; posmotif<histoire.filauto[0].longueur; posmotif++) {
								curspos(cons,2,9+posmotif); out("     Chaînon "); out(posmotif); out(" : ");
								histoire.filauto[0][posmotif].condition.test(biblio); 
								if(histoire.filauto[0][posmotif].condition.eval(biblio)) out("  : TRUE"); else out("  : FALSE");						
								out("    ; en cours: "); if(histoire.filauto[0][posmotif].encours) out("TRUE"); else out("FALSE");
							}
							//abort();
		
						//DEBUGGG	
						} else if(intkey==2) {														//Ctrl + b : Donne la valeur de chaque livre de la bibliothèque
							curspos(cons,2,18); out("Voici les valeurs stockées dans la bibliothèque:");
							int nombrelivres = 0;
							for(int posrayon=0; posrayon<biblio.nomrayon.longueur; posrayon++) {
								curspos(cons,2,19+posrayon+nombrelivres); out("    "); out(biblio.nomrayon[posrayon]); out(" :   ("); out(biblio.nomlivre[posrayon].longueur); out(" rayons)");
								for(int poslivre=0; poslivre<biblio.nomlivre[posrayon].longueur; poslivre++) {
									nombrelivres++;
									curspos(cons,2,19+posrayon+nombrelivres); out("                      "); out(biblio.nomlivre[posrayon][poslivre]); out(" : "); out(biblio.acces(posrayon,poslivre));
								}
							}
							//abort();
							
						//DEBUGGG	
						} else if(intkey==10) {														//Ctrl + j : Donne le texte inscrit dans le premier canal
							curspos(cons,2,28); out("Voici le texte restant dans le premier canal : \"");
							out(canaux[0].txt); out("\"");
							//abort();
							
											
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
								curspos(cons,inp.inputpos-1,base.limtxty);	                    
								for(int pos=inp.inputpos-1; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);
								if(inp.commande.longueur==inpecho.commande.fin) inpecho.actif = false;                   //Désactiver le canal d'écho si la commande actuelle le dépasse
							}
						}
					}	
				//Remettre la lettre sélectionnée en surbrillance
				if(inp.inputpos!=inp.commande.longueur) {chgcol(cons,biblio.acces(biblio.poscouleur,"commpostxt"),biblio.acces(biblio.poscouleur,"commposbg"));  curspos(cons,inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); chgcol(cons,biblio.acces(biblio.poscouleur,"actutxt"),biblio.acces(biblio.poscouleur,"actubg"));}
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
					curspos(cons,0,base.limtxty); for(int pos=0; pos < base.limfenx-1; pos++) out(' ');    //Nettoyer la ligne avant de la faire flasher
					inp.inputpos = 0; inp.commande.vide();                               //Nettoyer l'objet input			
				}	
			}
		}     

	//iv) Fonction pour tout coordonner harmonieusement	----------------------------------------------------------------------		
		
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

//------------------------------------------------------------------------------------------------------------------------------------------------------
//6) Fonctions de remplissage aisé des objets utilisés
	
	//i) Fonctions pour nommer les livres et les rayons de la bibliothèque	----------------------------------------------------------------------		

		//a) Fonction pour créer un nouveau rayon et le nommer
		void univers::nvrayon(const string& str) {
			biblio.rayon.ajoutvide();								//Passer au prochain rayon
			biblio.nomrayon.ajout(str);
		}
		
		//b) Fonction pour créer un nouveau livre et le nommer
		void univers::nvlivre(const string& str) {
			biblio.rayon[biblio.rayon.longueur-1].ajoutvide();		//Passer au prochain livre
			biblio.nomlivre[biblio.rayon.longueur-1].ajout(str); biblio.modif(biblio.rayon.longueur-1,biblio.rayon[biblio.rayon.longueur-1].longueur-1,0);		//Mettre 0 comme valeur par défaut (par défaut, tous les livres = FALSE)
		}

	//ii) Fonctions pour créer de nouveaux canaux et les personaliser	----------------------------------------------------------------------		
	
		//a) Fonction pour créer un nouveau canal et le nommer
		void univers::nvcanal(const string& str) {                    
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

	//iii) Fonctions pour organiser les chapitres et les motifs (permettent l'activation des textes)	----------------------------------------------------------------------		
	
		//a) Fonction pour créer un nouveau chapitre
		void univers::nvchapt() {
			histoire.filauto.ajoutvide();											//ATTENTION! ICI, LES CHAPITRES SONT THÉORIQUEMENT SÉPARÉS ENTRE MANUELS ET AUTOMATIQUES,
			histoire.filmanu.ajoutvide();												//MAIS LE CODE LES TRAITE EN TOUT TEMPS COMME LA MÊME ENTITÉ! LE GARDER EN TÊTE!
		}
		
		//b) Fonction pour définir les conditions d'activation du chapitre
		void univers::ccond(const string& str) {
			histoire.cadenas[histoire.filmanu.longueur-1].set(str,biblio);
		}
	
		//c) Fonction pour "créer" un nouveau motif et le nommer (manuel)
		void univers::nvmanu(const string& str) {		
			int poschap = histoire.filmanu.longueur-1;
			histoire.filmanu[poschap].ajoutvide();			//Passer au prochain motif
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].titre = str;     //Conserver le titre, pour y référer au cas où une même commande appelerait plusieurs motifs.
		} 
		//c)Fonction pour "créer" un nouveau motif (automatique)
		void univers::nvauto() {		
			int poschap = histoire.filauto.longueur-1;
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
					if(countstr-debmaille>0) {
						histoire.filmanu[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,countstr-1));
					} else histoire.filmanu[poschap][posmotif].maille.ajout("");   
					debmaille = countstr+1;		//if(...) : évite les intervalles [1,0] (à la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "µµ")
				}
			}
			histoire.filmanu[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,strnb-1));		//Entrer la dernière maille
			//Ajouter par défaut un enchaînement lisant l'intégralité des mailles, dans l'ordre, avec une probabilité de 1 (peut alors être écrasé par les commandes suivantes)
			histoire.filmanu[poschap][posmotif].enchainement.ajoutvide();      //Créer le premier enchaînement
			for(int countmaille = 0; countmaille<histoire.filmanu[poschap][posmotif].maille.longueur; countmaille++){
				histoire.filmanu[poschap][posmotif].enchainement[0].ajout(countmaille);	
			}
			histoire.filmanu[poschap][posmotif].enchaineprob.ajoutvide();      //Créer la première probabilité
			histoire.filmanu[poschap][posmotif].enchaineprob[0].set("1",biblio);	
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
						histoire.filauto[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,countstr-1));
					} else histoire.filauto[poschap][posmotif].maille.ajout("");   
					debmaille = countstr+1;		//if(...) : évite les intervalles [1,0] (à la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "µµ")
				}
			}
			histoire.filauto[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,strnb-1));		//Entrer la dernière maille
			//Ajouter par défaut un enchaînement lisant l'intégralité des mailles, dans l'ordre, avec une probabilité de 1 (peut alors être écrasé par les commandes suivantes)
			histoire.filauto[poschap][posmotif].enchainement.ajoutvide();      //Créer le premier enchaînement
			for(int countmaille = 0; countmaille<histoire.filauto[poschap][posmotif].maille.longueur; countmaille++){
				histoire.filauto[poschap][posmotif].enchainement[0].ajout(countmaille);	
			}
			histoire.filauto[poschap][posmotif].enchaineprob.ajoutvide();      //Créer la première probabilité
			histoire.filauto[poschap][posmotif].enchaineprob[0].set("1",biblio);	
		}		
			
		//c) Fonction pour définir les enchaînements possibles (manuel)
		void univers::mordre(const string& str) {
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int countordre = 0;				//Créer un compteur pour l'ordre
			int debnombre = 0;				//Créer un compteur d'indexation pour le début du nombre
			//Effacer les enchaînements déjà existants (celles par défaut)
			histoire.filmanu[poschap][posmotif].enchainement[0].vide();        //Conserve quand même le fait qu'un premier enchaînement a été créé
			histoire.filmanu[poschap][posmotif].enchaineprob[0].clean();        //Conserve quand même le fait qu'une première probabilité a été créée    
			//Ajouter les enchaînements inscrits
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='-'||str[countstr]==';') {
					if(countstr-debnombre>0) {
						histoire.filmanu[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
					} else {out("L'enchaînement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing à la position "); out(countstr); out(". Changer ça svp."); abort();}			
					if(str[countstr]=='-') {}
					if(str[countstr]==';') {countordre++; histoire.filmanu[poschap][posmotif].enchainement.ajoutvide();}
					debnombre = countstr+1;
				}
			}
			histoire.filmanu[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,strnb-1))-1);		//Entrer le dernier chiffre	
			//Ajouter par défaut une probabilité de 1 pour tous les enchaînements inscrits (peut alors être écrasé par la commande suivante)
			for(int countench = 0; countench<histoire.filmanu[poschap][posmotif].enchainement.longueur; countench++){
				histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("1",biblio);	
			}		
		}																						
		//c) Fonction pour définir les enchaînements possibles (automatique)
		void univers::aordre(const string& str) {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int countordre = 0;				//Créer un compteur pour l'ordre
			int debnombre = 0;				//Créer un compteur d'indexation pour le début du nombre
			//Effacer les enchaînements déjà existants (celles par défaut)
			histoire.filauto[poschap][posmotif].enchainement[0].vide();        //Conserve quand même le fait qu'un premier enchaînement a été créé
			histoire.filauto[poschap][posmotif].enchaineprob[0].clean();        //Conserve quand même le fait qu'une première probabilité a été créée    
			//Ajouter les enchaînements inscrits
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='-'||str[countstr]==';') {
					if(countstr-debnombre>0) {
						histoire.filauto[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
					} else {out("L'enchaînement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing à la position "); out(countstr); out(". Changer ça svp."); abort();}			
					if(str[countstr]=='-') {}
					if(str[countstr]==';') {countordre++; histoire.filauto[poschap][posmotif].enchainement.ajoutvide();}
					debnombre = countstr+1;
				}
			}
			histoire.filauto[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,strnb-1))-1);		//Entrer le dernier chiffre	
			//Ajouter par défaut une probabilité de 1 pour tous les enchaînements inscrits (peut alors être écrasé par la commande suivante)
			for(int countench = 0; countench<histoire.filauto[poschap][posmotif].enchainement.longueur; countench++){
				histoire.filauto[poschap][posmotif].enchaineprob[countench].set("1",biblio);	
			}		
		}			
		
		//d) Fonction pour définir les probabilités associées avec chaque enchaînement (manuel)
		void univers::mprob(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int debench = 0;				//Noter la position d'indexation du début de l'enchaînement
			int countench = 0;				//Position de l'enchaînement visé
			//Effacer les probabilités déjà existantes (celles par défaut)
			for(int countench = 0; countench<histoire.filmanu[poschap][posmotif].enchainement.longueur; countench++){
				histoire.filmanu[poschap][posmotif].enchaineprob[countench].clean();				//Conserve le fait que les probabilités ont été créées en nombre égal au nombre d'enchaînements
			}				
			//Ajouter les probabilités inscrites
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]==';') {
					if(countstr-debench>0){
						histoire.filmanu[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,countstr-1),biblio);
					} else histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("0",biblio); //Si deux ';' se suivent, mettre la probabilité de l'enchaînement vide comme 0. Ça lui apprendra.
					debench = countstr + 1; countench++;
				}
			}
			if(debench!=strnb) {		//Entrer le dernier chiffre
			histoire.filmanu[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,strnb-1),biblio);
			}
			while(countench++<histoire.filmanu[poschap][posmotif].enchainement.longueur-1){             //Si moins de probabilités ont été inscrites qu'il n'y a d'enchaînements
				histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("0",biblio);
			}
		}
		//d) Fonction pour définir les probabilités associées avec chaque enchaînement (automatique)
		void univers::aprob(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int debench = 0;				//Noter la position d'indexation du début de l'enchaînement
			int countench = 0;				//Position de l'enchaînement visé
			//Effacer les probabilités déjà existantes (celles par défaut)
			for(int countench = 0; countench<histoire.filauto[poschap][posmotif].enchainement.longueur; countench++){
				histoire.filauto[poschap][posmotif].enchaineprob[countench].clean();				//Conserve le fait que les probabilités ont été créées en nombre égal au nombre d'enchaînements
			}				
			//Ajouter les probabilités inscrites
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]==';') {
					if(countstr-debench>0){
						histoire.filauto[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,countstr-1),biblio);
					} else histoire.filauto[poschap][posmotif].enchaineprob[countench].set("0",biblio); //Si deux ';' se suivent, mettre la probabilité de l'enchaînement vide comme 0. Ça lui apprendra.
					debench = countstr + 1; countench++;
				}
			}
			if(debench!=strnb) {		//Entrer le dernier chiffre
			histoire.filauto[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,strnb-1),biblio);
			}
			while(countench++<histoire.filauto[poschap][posmotif].enchainement.longueur-1){             //Si moins de probabilités ont été inscrites qu'il n'y a d'enchaînements
				histoire.filauto[poschap][posmotif].enchaineprob[countench].set("0",biblio);
			}
		}
		
		//e) Fonction pour définir les codes spéciaux appelés au début du motif (manuel)
		void univers::mdeb(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].codespeciauxdebut = str;
		}
		//e) Fonction pour définir les codes spéciaux appelés au début du motif (automatique)
		void univers::adeb(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].codespeciauxdebut = str;
		}
		
		//f) Fonction pour définir les codes spéciaux appelés à la fin du motif (manuel)
		void univers::mfin(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;
			histoire.filmanu[poschap][posmotif].codespeciauxfin = str;
		}
		//f) Fonction pour définir les codes spéciaux appelés à la fin du motif (automatique)
		void univers::afin(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;
			histoire.filauto[poschap][posmotif].codespeciauxfin = str;
		}
		
		//g) Fonction pour définir les conditions sous lesquelles le motif pourra être appelé (manuel)
		void univers::mcond(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].condition.set(str,biblio);
		}
		//g) Fonction pour définir les conditions sous lesquelles le motif pourra être appelé (automatique)
		void univers::acond(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].condition.set(str,biblio);
		}
			
		//h) Fonction pour définir que le canal sera vidé (override) dès l'activation de ce motif (manuel)   (désactivé par défaut)
		void univers::mover(){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].override = true;
		}				
		//h) Fonction pour définir que le canal sera vidé (override) dès l'activation de ce motif (automatique)   (désactivé par défaut)
		void univers::aover(){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].override = true;
		}					
					
		//i) Fonction pour définir que le canal sera mis en attente ("réserve") lorsque la bonne commande sera envoyée, et ce jusqu'à la lecture du code spécial "§r§" (manuel seulement)   (désactivé par défaut)
		void univers::mreserve(){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].reserve = true;
		}					
					
		//j) Fonction pour définir les combinaisons de mots qui appeleront le motif - les commandes (manuel)
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
							if(exclus) {histoire.filmanu[poschap][posmotif].commandes.exclus[posfac].ajout(mot);		//Enregistrer le mot
							} else {
								if(histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].longueur==0) histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].ajoutvide();	//Noter qu'un nouveau groupe de mots commence
								histoire.filmanu[poschap][posmotif].commandes.inclus[posfac][posgr].ajout(mot);
							}
							mot.clear();			//Vider le string de stockage temporaire
							//Interpréter le caractère exact
							if(str[countstr]=='|') {						//Ne rien faire
							}else if(str[countstr]=='&') {posgr++; histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].ajoutvide();
							} else if(str[countstr]==')') {posgr=0; posfac++;
							} else if(str[countstr]==']') {exclus = false;								//ATTENTION!!! 	METTRE MESSAGE D'ERREUR + abort() SI ON SE REND
							}																				//AU-DELÀ DES LIMITES!!! À FAIRE!!!
						} 
					} else mot+=str[countstr];		//Ajouter la lettre si c'est un caractère simple	
				}
			}
		}
		
		//k) Fonction pour définir les commandes exactes qui appeleront le motif (manuel)
		void univers::mcommexact(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();
			int debmot = 0;			//Noter la position d'indexation du début du mot
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='|') {
					if(countstr-debmot>0){ 
						histoire.filmanu[poschap][posmotif].commandes.exact.ajout(strintervalle(str,debmot,countstr-1));
					} else histoire.filmanu[poschap][posmotif].commandes.exact.ajout(""); //Si deux ';' se suivent, mettre *RIEN* comme commande exacte possible
					debmot = countstr + 1;
				}
			}	
			if(debmot!=strnb) histoire.filmanu[poschap][posmotif].commandes.exact.ajout(strintervalle(str,debmot,strnb-1));		//Entrer le dernier mot
		}
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//7) Aire de tests


/*
				
	int main() {

	//Déclarer l'objet contenant tout
	univers un;		

	//Construire l'univers; puisque ce sont des "member functions", celles-ci doivent obligatoirement être dans le "main"		
			
		//Construire la bibliothèque
			un.nvrayon("intro");
				un.nvlivre("desuet");	
				un.nvlivre("jeprem");
				un.nvlivre("jedeux");
				un.nvlivre("saraprem");
				un.nvlivre("saradeux");
				un.nvlivre("jetrois");
				un.nvlivre("saratrois");
				un.nvlivre("jequatre");
				un.nvlivre("saraquatre");
				un.nvlivre("jecinq");	
				
		//Construire les canaux
			un.nvcanal("je"); un.canaldelai(80); 
			un.nvcanal("sara"); un.canaldelai(130); un.canalalinea(6);
				
		//Débuter un chapitre
		un.nvchapt();
			un.ccond("!intro¶desuet");        //Rendre le premier chapitre accessible seulement quand c'est l'intro 
				
		//Construire les motifs
			//Motif automatique : Juste le début
				un.nvauto(); un.acanal("je");	                                    	
				un.acond("intro¶jeprem");	
				un.adeb("§bintro¶jeprem=0§");
				un.afin("§bintro¶saraprem=1§");
				un.aover(0);						//N'override pas le canal à son début
				un.atexte("T'as froid aux joues.§p1400§"
				"\n§d0§                     §d80§Pis aux cuisses."
				"\nEn fait t'as juste le goût de râler de la marde pour pouvoir agrandir le temps qu'il faut pour trouver l'erreur, les erreurs, à la fois avec le msn qui bug (mais tu crois que tu en a trouvé une bonne?) et avec le texte qui s'affice instantannément.'");	
				
			//Motif automatique : Juste le début
				un.nvauto(); un.acanal("msn");	                                    	
				un.acond("intro¶jeprem");	
				un.adeb("");
				un.afin("§p1000§");
				un.aover(0);						//N'override pas le canal à son début
				un.atexte("YoYoYo! Les msn marchent!");				

	//Débuter le jeu
			
		//Ouvrir une fenêtre de bonnes dimensions et initialiser les objets de sauvegarde
		un.MettreDansLeMain();
			
		//Enclencher le premier motif (oui, j'fais ça manuellement pour garder l'uniformité dans mes enclenchements)
			un.biblio.modif("intro","jeprem",1);
			
		//Vérifier une toute première fois la disponibilité des motifs automatiques
			un.AutoInterpret();
			
		//Faire une boucle pour que les canaux s'expriment!
			un.jouer();				
			curspos(un.cons,0,13);			//Mettre le curseur dans un bel endroit à la fin		
	}		

*/		
