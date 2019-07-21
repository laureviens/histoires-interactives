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
	2019-06-22:
				La fonction pour afficher l'input semble avoir de la difficulté à gérer les accents.
				Les bouts de texte écrits dans le script s'affichent correctement,
				mais le unicode utilisé pour getch() ne semble pas correspondre aux bons symboles.
				Bon.
				Même quand j'associe manuellement le code numérique aux bon char, ça garde la même erreur.
				Comme si les char provenant de l'user input était différents de ceux du script?
				
				Bon, c'est officiel, la liste de if() else() dans out() ne reconnaît pas les char provenant du clavier.
				Je ne sais pas quoi y faire. Est-ce que ça va chier aussi la reconnaissance dans "find()"???
				
				C'est vraiment étrange.
				
*/

/*
	2019-06-22:
				En passant: Quand on active un canal, ou qu'on le reset, va falloir resetter son nxtt (timer) aussi. Bien y penser.
*/

/*
	2019-07-05:
				Dans les fonctions integration() et UserInputInterpret(),
				j'utilise beaucoup d'indexation. Ça devient difficile à lire.
				Je pense que ça n'alourdirait pas trop l'exécution de créer un objet temporaire pour chaque chainon (rendrait le tout plus clair).
				J'ai par contre peur que ça fuck avec les pointeurs, que les objets soient modifiés (sont tous par & référence), etc.
					Je conserve donc cette idée quand j'aurai minimalement une version testée, qui fonctionne.
					
				Aussi, j'utilise beaucoup la synthaxe .pt[], pour accéder aux objets StaticVect.
				Je ne pense pas que ce soit une très bonne idée (même si cela semble être la seule possible en ce moment??????),
				car il y aura un décalement avec les objets réellement voulus si debut != 0.
				Je devrais créer une classe parallèle à StaticVect, mais qui ne comporte pas de suppression, à la place.
				Juste pour être safe.	

*/


//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent (??? Optionnel?)
#include <windows.h>           //Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>            //Nécessaire pour savoir la position du curseur sur Windows
#include <winuser.h>		   //Nécessaire pour savoir la position du curseur sur Windows
#include <conio.h>             //Nécessaire pour enregistrer les inputs du clavier
#include <io.h>				   //Nécessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>			   //Nécessaire pour décrypter les accents en unicode
#include <stdlib.h>     	   //Nécessaire pour jouer avec des nombres aléatoires  /* srand, rand */

/*
	2019-07-05:
A typical way to generate trivial pseudo-random numbers in a determined range using rand is to use the modulo of the returned value 
		by the range span and add the initial value of the range:

v1 = rand() % 100;         // v1 in the range 0 to 99
v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 
*/


using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Classes-contenantes générales
	
	//i) classe : StringAsVect ; permet un simulâcre d'allocation dynamique de mémoire, avec la magie de voir plus grand + indexation
	class StringAsVect {
	//Comment ça marche:
			//L'array est d'abord créé plus gros que nécessaire. On ne supprime pas vraiment les valeurs qui y passent,
			//on ne fait que s'étendre dans l'array:
				//On supprime chaque position depuis le début;
				//On ajoute chaque nouvelle position à la fin.
			//Lorsque l'array est rendu à sa capacité maximale, 
				//on refait l'array au complet.	
		//Valeurs membres	
		public:
			static const int TailleBase = 200;       //Taille de base des objets 
			char* pt;     //Déclarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
			int nb;       //Déclarer le nombre d'objets de l'array
			int debut;    //Déclarer la position de la première valeur
			int fin;      //Déclarer la position de la dernière valeur
			int longueur; //Longueur de la partie active, du début à la fin
		//Constructeurs	
			StringAsVect() : nb(TailleBase), debut(0), fin(0), longueur(0) {  //Défaut
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace					
			}
			StringAsVect(char nxt) : nb(TailleBase), debut(0), fin(1), longueur(1) {  //À partir d'une seule valeur
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
				pt[0] = nxt;
			}
			StringAsVect(char nxt[], int nbpos) : nb(nbpos + TailleBase), debut(0), fin(nbpos), longueur(nbpos) {   //À partir d'un array
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
					for(int pos=0; pos<fin; pos++) pt[pos] = nxt[pos];
			}
			StringAsVect(std::string nxt) : nb(nxt.length() + TailleBase), debut(0), fin(nxt.length()), longueur(nxt.length()) {      //À partir d'un string
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
					for(int pos=0; pos<fin; pos++) pt[pos] = nxt[pos];
			}	
		//Destructeur
			~StringAsVect() {delete[] pt;}	
		//Copy constructor  
			StringAsVect(const StringAsVect& nxt) : nb(nxt.nb), debut(0), fin(nxt.longueur), longueur(nxt.longueur) {
					try{pt = new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt = new char [nb];             	//Vraiment allouer l'espace		
				int nxtpos = nxt.debut; for(int pos=0; pos<fin; pos++) pt[pos] = nxt.pt[nxtpos++];        //Copier le contenu (en remettant le début à 0)	//ATTENTION J'AI CHANGÉ CETTE LIGNE RISQUE DE BUG				
			}
		//Copy assignment
			StringAsVect& operator= (const StringAsVect& nxt) {
				nb = nxt.nb; debut = 0; fin = nxt.longueur;	longueur = nxt.longueur;			
				delete[] pt;     //Effacer l'array vers lequel je pointe actuellement
					try{pt = new char [nb];}  //Essayer d'allouer l'espace 
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)				
				pt = new char [nb];		     		//Vraiment allouer un nouvel espace pour le nouvel objet
				int nxtpos = nxt.debut; for(int pos=0; pos<fin; pos++) pt[pos] = nxt.pt[nxtpos++];        //Copier le contenu (en remettant le début à 0)	//ATTENTION J'AI CHANGÉ CETTE LIGNE RISQUE DE BUG				
				return *this;                        //???????? Pourquoi retourner quelque chose dans un = ?
			}	
		//Move constructor
			StringAsVect(StringAsVect&& nxt) : nb(nxt.nb), debut(nxt.debut), fin(nxt.fin), longueur(nxt.longueur), pt(nxt.pt) {nxt.pt = nullptr;}  //Copie seulement le pointeur (pas son contenu), et efface le temporaire
		//Move assignement
			StringAsVect& operator= (StringAsVect&& nxt) {
				delete[] pt;
				nb = nxt.nb; debut = nxt.debut; fin = nxt.fin; longueur = nxt.longueur;
				pt = nxt.pt;         //Copier seulement le pointeur, sans faire une copie du contenu
				nxt.pt = nullptr;    //Rendre nul le pointeur temporaire
				return *this;
			}
   		//Opérateur d'accès : []
		   char operator[] (int pos) {return(pt[debut + pos]);}
		//Fonction de modification : ajout          //Ajoute les valeurs en right-hand à la SUITE des valeurs déjà contenues
		   void ajout (char nxt) {
		   		if(fin + 1 < nb) {      //Pas besoin de ré-allouer la mémoire
		   			pt[fin] = nxt; fin++; longueur++; 
				} else {                //Besoin de ré-allouer
					nb = longueur + TailleBase;             	//Déterminer le nombre d'éléments du prochain bloc de mémoire
						try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 
					  	catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de mémoire à l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de mémoire des vieux éléments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					nwpt[posNeuf] = nxt;                        //Ajouter le nouvel élément
					debut = 0; fin = longueur + 1;	           //Ré-initialiser les compteurs de position
					longueur++;
					delete[] pt;       							//Supprimer les éléments contenus dans le viel array						
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }
		   void ajout (const string& nxt) {
		   		if(fin + nxt.length() < nb) {      //Pas besoin de ré-allouer la mémoire
		   			int nbnxt = nxt.length();
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt[posnxt];   
					 fin+=nwend; longueur+=nbnxt;
				} else {                //Besoin de ré-allouer
					int nbnxt = nxt.length();    
					nb = longueur + TailleBase;             	//Déterminer le nombre d'éléments du prochain bloc de mémoire
						try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 					
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de mémoire à l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de mémoire des vieux éléments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[posNeuf++] = nxt[posnxt]; //Ajouter les nouveaux éléments
					debut = 0; fin = longueur + nbnxt;          //Ré-initialiser les compteurs de position
					longueur += nbnxt;
					delete[] pt;       							//Supprimer les éléments contenus dans le viel array	
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }		   
		   void ajout (const StringAsVect& nxt) {
		   		if(fin + nxt.nb < nb) {      //Pas besoin de ré-allouer la mémoire
		   			int nbnxt = nxt.nb;
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt.pt[posnxt+nxt.debut];   
					 fin+=nwend; longueur+=nbnxt;
				} else {                //Besoin de ré-allouer
					int nbnxt = nxt.nb;    
					nb = longueur + TailleBase;             	//Déterminer le nombre d'éléments du prochain bloc de mémoire
							try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 					
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de mémoire à l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de mémoire des vieux éléments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[posNeuf++] = nxt.pt[posnxt+nxt.debut]; //Ajouter les nouveaux éléments
					debut = 0; fin = longueur + nbnxt;          //Ré-initialiser les compteurs de position
					longueur += nbnxt;
					delete[] pt;       							//Supprimer les éléments contenus dans le viel array	
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }
		//Opérateur de modification : suppression          //"Supprime" le nombre de positions en right-hand AU DÉBUT des valeurs déjà contenues
			void suppression (int nb) {
				if(nb > fin-debut) debut = fin; else debut+=nb; 
				longueur--;
			}
	};		

	//ii) classe : StaticVect ; sauvegarde un array "semi-dynamique", où la mémoire utilisée est fixe, mais les fonctionnalités sont les mêmes que StringAsVect.
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
				bool ajout(Type nxt, int pos) {
					if(fin+1 <= taille) {
						for(int ptpos = fin; ptpos>pos; ptpos--) pt[ptpos] = pt[ptpos-1];
						pt[pos] = nxt; fin++; longueur++;
						return(true);
					} else return(false);
				}
				bool ajout(Type* nxt, int nb) {
					if(fin+longueur <= taille) {
						int nouvfin = fin + nb; int posnxt = 0;
						for(int pos=fin; pos<nouvfin; pos++) {pt[pos] = nxt[posnxt++];}
						fin+=nb; longueur+=nb; 
						return(true);
					} else return(false);
				}
			//Fonction de modification : remplacement()
				int remplacement(Type nxt) {debut = 0; fin = 1; pt[0] = nxt; return(true);}  	
				int remplacement(Type* nxt, int nb) {
					if(longueur <= taille) {
						debut = 0; fin = nb; longueur = nb;
						for(int pos=0; pos<nb; pos++) pt[pos] = nxt[pos];	
						return(true);			
					} else return(false);
				}
				int remplacement(StaticVect<Type,Taille>& nxt) {
					if(nxt.longueur <= taille) {
						debut = 0; fin = nxt.longueur; longueur = nxt.longueur;
						int pos = 0; for(int posnxt=0; posnxt<nxt.longueur; posnxt++) pt[pos++] = nxt[posnxt];		
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
			};	

			
//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) Fonctions et objets pour interagir avec la console

	//i) Fonction : timems ; avoir le temps actuel en millisecondes (depuis l'epoch, soit 1er janvier 1970)
	int timems (void) {
		return(std::chrono::duration_cast< std::chrono::milliseconds >(
	    	std::chrono::system_clock::now().time_since_epoch()
			).count());
	}	

	//ii) Objets : divers objets de windows ; permet de modifier le texte affiché dans la console   	            	//WINDOWS ONLY
	HANDLE TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);        //Objet permettant de modifier le texte affiché dans la console 
	COORD CursorPosition;                                     	//Objet permettant de se situer sur la console
	CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;                //Objet permettant de connaître la position du curseur dans la console
	CONSOLE_CURSOR_INFO CursorInfo;	                            //Objet permettant de modifier le curseur
	HWND DimConsole = GetConsoleWindow();                       //Objet permettant de modifier les dimensions + la position de la console

	//iii) Fonction: curspos ; déplacer le curseur sur la console                                                          //WINDOWS ONLY
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(TxtConsole,CursorPosition);
	}	
		
	//iv) Fonction: cursoron ; affiche ou cache le curseur                        		                                   //WINDOWS ONLY
	void curson(bool visible) // set bool visible = 0 - invisible, bool visible = 1 - visible
	{
		CursorInfo.bVisible = visible; CursorInfo.dwSize = 20;
		SetConsoleCursorInfo(TxtConsole,&CursorInfo);
	}		
		
	//v) Fonction : out ; affiche le caractère dans la console
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
	void out(StringAsVect phrase){
		for(int pos=0; pos<phrase.longueur; pos++){
			out(phrase[pos]);
		}
	}
	template<int Taille>
	void out(StaticVect<char,Taille> phrase){
		for(int pos=0; pos<phrase.longueur; pos++){
			out(phrase[pos]);
		}
	}
	void out(int chiffre) {std::wcout << chiffre;}
	void out(double chiffre) {std::wcout << chiffre;}
	//void out(bool boule) {if(boule==true) std::wcout << "true"; else std::wcout << "false";}      //????? Capte aussi les strings????


	//vi) Fonction : chgcol ; change la couleur du texte à entrer
	void chgcol(string color) {
		WORD code;                                            //Voir Internet pour la légende
		if(color=="vert sombre") code = 0x02;         
			else if(color=="rouge sombre") code = 0x04;
			else if(color=="brun") code = 0x06;
			else if(color=="gris") code = 0x07;
			else if(color=="gris sombre") code = 0x08;
			else if(color=="vert") code = 0x0A;
			else if(color=="cyan") code = 0x0B;
			else if(color=="rouge") code =0x0C;
			else if(color=="blanc") code =0x0F;
		SetConsoleTextAttribute(TxtConsole, code);
	}

	//vii) Fonction : strtobool ; interprète un string pour renvoyer un booléen (similaire à stoi() ou stod() )
	bool strtobool(string str) {
		if(str[0]=='0') {return(false);
		} else if(str[0]=='f'&str[1]=='a'&str[2]=='l'&str[3]=='s'&str[4]=='e') {return(false);
		} else if(str[0]=='F'&str[1]=='A'&str[2]=='L'&str[3]=='S'&str[4]=='e') {return(false);
		} else if(str[0]=='1') {return(true);
		} else if(str[0]=='t'&str[1]=='r'&str[2]=='u'&str[3]=='e') {return(true);
		} else if(str[0]=='T'&str[1]=='R'&str[2]=='U'&str[3]=='E') {return(true);
		} else {out("\n\nTentative d'évaluer \""); for(int pos = 0; pos<str.length(); pos++) {out(str[pos]);} out("\" comme un booléen."); abort();}
	}
	
	//viii) Fonction : ColNameFind ; trouve une (la première rencontrée) position d'indexation dans un StaticVect<string,Taille> qui correspond exactement à un string
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
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Classes-contenantes spécialisées (canaux et autres)

	//i) classe : memoire ; permet de sauvegarder la "mémoire" de la console, c'est-à-dire tous le texte s'y étant déjà inscrit
		
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
					try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
				souvenir = new char* [nbcol];   //Créer un premier array contenant des pointers
				//Créer les lignes pour chaque colonne, et les remplir d'espace
				for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}
			}
			//Constructeur pour avoir le bon nombre de colonnes
			memoire(int ncol) {
				nbcol = ncol;
				frontline = 1;                         //Ce qui suit semble être la seule manière de créer des arrays dynamiques
				nbligne = TailleBase;            
					try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
				souvenir = new char* [nbcol];   //Créer un premier array contenant des pointers
				//Créer les lignes pour chaque colonne, et les remplir d'espace
				for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}
			}			//Destructeur
			~memoire() {
				for(int col=0; col<nbcol ; col++) delete[] souvenir[col] ; delete[] souvenir;   //Bien déconstruire tout proprement
			}
			//Fonction d'accès : retourner certaines positions
			char acces (int posx, int posy) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(souvenir[posx][posy]);
			}
			//Fonction de modification : newline ; ajouter une ligne à la suite de la position spécifiée (Opérateur +) 
			void newline (int pos) {
				if(frontline+1<nbligne) {
					int emptypos = pos + 1;   //Calculer la position qui sera vide
					//Déplacer de 1 tout ce qui vient ensuite, en commençant par la fin
					for(int lin = frontline; lin > pos; lin--) for(int col = 0; col < nbcol; col++) souvenir[col][lin+1]=souvenir[col][lin]; 
					for(int col = 0; col < nbcol; col++) souvenir[col][emptypos] = ' ';   //Remplir la position vide d'espace
					frontline++;   //Noter qu'on ajoute une ligne
				} else {
					int emptypos = pos + 1;   //Calculer la position qui sera vide
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

	
	//ii) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant à lire, la vitesse, etc.
	class canal {
		//Membres
		public:
			int nxtt;           //Déclarer le moment où la prochaine entrée sera traitée         
			int pausedt;	    //Différence entreposée entre nxtt et currentt, dans le cas où l'exécution est arrêtée (ex: faire apparaître un menu)				
			int delay;          //Déclarer le délai de base entre chaque entrée
			int posx, posy;		//Déclarer les coordonnées de la dernière entrée dans la mémoire (la précédente)   
								//les positions de la consoles sont définies en décalant ces dernières
			StringAsVect txt;   //Déclarer le texte qui reste à lire  				
			bool actif;			//Déclarer le compteur d'activité
			double vit;         //Déclarer la vitesse actuelle de défilement et de pauses (toujours par rapport à la base, 1)
		//Constructeur
		canal() : delay(400), posx(-1), posy(0), actif(false), vit(1) {nxtt = timems();}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
	};

	//iii) Classe : fen ; permet de sauvegarder les paramètres relatifs aux caractéristiques de la fenêtre de sortie (console)
	class fen {
		//Membres
		public:
			int posfenx, posfeny;     //Positions de la fenêtre sur l'écran                                                    //WINDOWS ONLY
			int sizefenx, sizefeny;   //Taille de la fenêtre en pixel														   //WINDOWS ONLY
			int limfenx, limfeny;     //Dimensions de la fenêtre en terme de nombre de caractères pouvant y être contenus
			int limtxtx, limtxty;     //Dimensions de la portion où le texte s'affiche en terme de nombre de caractères pouvant y être contenus
			int consy;             //Facteur de décalement de la console où apparaît le texte avec la mémoire, où il est stocké
			bool refoule;          //Flag pour voir si le facteur de décalement entre en compte
			string couleur;           //Couleur de base du texte
		//Constructeurs
		     //Constructeur pour initialiser tous les paramètres automatiquement (à mettre dans le main())
		fen(int posx, int posy, int sizex, int sizey) : posfenx(posx), posfeny(posy), sizefenx(sizex), sizefeny(sizey), consy(0), refoule(false), couleur("gris") {
				//MoveWindow(window_handle, x, y, width, height, redraw_window);       //Les unités sont en pixels!
			MoveWindow(DimConsole, posx, posy, sizex, sizey, TRUE);                    //Créer la fenêtre de la bonne taille          //WINDOWS ONLY
			GetConsoleScreenBufferInfo(TxtConsole, &ScreenBufferInfo);                 //Accéder à la taille de la console            //WINDOWS ONLY
			curson(false);                                                     		   //Faire disparaître le curseur                 //WINDOWS ONLY
			chgcol(couleur);														   //Mettre le texte de la couleur par défaut
    		_setmode(_fileno(stdout), _O_U16TEXT);									   //Permettre l'affichage de l'UNICODE           //WINDOWS ONLY  
			limfenx = ScreenBufferInfo.srWindow.Right + 1; limfeny = ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations
			limtxtx = limfenx; limtxty = limfeny - 1;
		}                  //JE PROFITE DE CETTE FONCTION POUR ÉGALEMENT CHANGER LES PARAMÈTRES DE BASE! ATTENTION!
		fen(int x, int y) {limtxtx = x; limtxty = y; consy = 0; refoule = false;}      //Constructeur permettant d'aligner manuellement les dimensions de la fenêtre avec la réalité	
	};
		
		
	//iv) classe : input ; sauvegarde les informations relatives aux inputs
	class input {
		//Valeurs membres
		public:
			StaticVect<char,200> commande;          	//Phrase que contient le buffer         //Peut-il devenir un StringAsVect?
			int inputpos;                   //Position d'indexation du prochain caractère    == StaticVect.fin? Non! Car ça peut bouger!
			bool accepted;                  //Flag concernant la dernière commande; utile pour l'affichage visuel
			bool busy;						//Flag concernant la dernière commande; utile pour l'affichage visuel
		//Constructeur par défaut
			input() : inputpos(0), accepted(false), busy(false) {}
	};							
						
	//v) classe : inputecho ; permet l'affichage résiduel des commandes (acceptées ou refusées)	
	class inputecho {
		//Valeurs membres
		public:
			StaticVect<char,200> commande;
			StaticVect<int,50> clignote;               //Conserve les instructions pour le clignotement : positif = affiche, négatif = pause.	
			string couleur;                            //Conserve la couleur du clignotement
			bool actif;							       //Compteur d'activité
			int nxtt;         						   //Moment où la prochaine entrée sera traitée         
			int pausedt;							   //Différence entreposée entre nxtt et currentt, dans le cas où l'exécution est arrêtée (ex: faire apparaître un menu)				
		//Constructeur par défaut
		inputecho() : couleur("gris sombre"), actif(false) {nxtt = timems();}	
	};


	//vi) classe : bibliotheque ; permet de stocker tous les status (bool et int) modifiables
	class bibliotheque {
		//Valeurs membres
		public:
			static const int nbrayons = 5;
			static const int nblivres = 30;
			StaticVect<StaticVect<int,nblivres>,nbrayons> rayon;
			StaticVect<string,nbrayons> nomrayon; StaticVect<StaticVect<string,nblivres>,nbrayons> nomlivre;
		//Fonction d'accès : acces ; retourner la valeur à certaines positions
		int acces(int posrayon, int poslivre) {return(rayon[posrayon][poslivre]);}
		//Fonction de modification : modif ; modifie la valeur à certaines positions
		void modif(int posrayon, int poslivre, int value) {rayon[posrayon][poslivre] = value;}
	};

	//vii) classe : inteval ; contient l'expression à évaluer (la plus simple) ; constructeur transforme les noms de "livre" en position d'indexation
	class inteval {
		//Valeurs membres
		public:
			int rayonpos;   		//Position d'indexation de la "famille" de l'argument comparé à gauche					
			int livrepos;			//Position d'indexation de l'argument comparé à gauche, à l'intérieur de sa "famille"
			int boolval; int intval;
			int constbool; int constint;      //TRUE si les valeurs sont booléennes ou int, à la place d'évaluées.
		//Constructeur
		inteval () {}; //Constructeur par défaut : vide. 
		template<int Taille>
		inteval(StaticVect<char,Taille> exp, bibliotheque& biblio) : constbool(false), constint(false) {
			string rayon, livre;    //Initier un string, dans lequel seront insérés seulement les noms des rayons/livres
			int strpos, pos; strpos = 0; pos = 0; while(exp[pos]!='¶'&pos<exp.longueur) rayon += exp[pos++];
			//Évaluer si le string contient des noms ou une valeur
			if(pos==exp.fin) {   	
				if(rayon[0]=='F'||rayon[0]=='f'||rayon[0]=='T'||rayon[0]=='t') {constbool = true; boolval = strtobool(rayon);} else {constint = true; intval = stoi(rayon);}
			} else {
				//Transformer le nom du rayon en position d'indexation
				rayonpos = ColNameFind(rayon,biblio.nomrayon);				
				//Recueillir le string + transformer le nom du  livre en position d'indexation	
				strpos = 0; pos++; while(pos<exp.longueur) livre += exp[pos++];
				livrepos = ColNameFind(livre,biblio.nomlivre[rayonpos]);
			}
		}
		//Fonction d'accès : eval()	
		int eval(bibliotheque& biblio) {if(constbool) return(boolval); else if(constint) return(intval); else return(biblio.acces(rayonpos,livrepos));}	
	};	

	//viii) classe : intoper ; contient les opérations d'expressions booléennes évaluables
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
		intoper () {}; //Constructeur par défaut : vide. 
		template<int Taille>
		intoper(StaticVect<char,Taille> exp, bibliotheque& biblio) : Lcompos(false), Rcompos(false) {
			StaticVect<char,Taille> LH;									
			StaticVect<char,Taille> RH;			
			int posPAR; bool trouvPAR = false; int nbPAR = 0;
			int posAD; bool trouvAD = false;
			int posMU; bool trouvMU = false; 
			int pos = 0;
			if(exp[0]=='(') {
				while(!trouvPAR&&pos<exp.fin) {
					if(exp[pos]=='(') nbPAR++;	//Gère les parenthèses imbriquées 
					if(exp[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
					pos++;
				} if(!trouvPAR) out("\n\nLa parenthèse n'est pas refermée dans: "); out(exp); abort();
				if(trouvPAR&&pos==exp.fin) {exp = exp.intervalle(1,exp.longueur-1); trouvPAR = false; pos = 0;   //Supprimer la parenthèse et remettre les compteurs à 0, pour continuer		
				} else Lcompos = true;		//Noter l'expression à droite comme composite (car elle contient au minimum une parenthèse), et continuer à partir d'après la parenthèse
			} else { 							
			//Cas général : on cherche '+' ou '-', car '*' et '/' ont la priorité d'opération
				while(!trouvAD&pos<exp.fin) {
					if(exp[pos]=='+'|exp[pos]=='-') {posAD = pos; trouvAD = true;}
					if(!trouvMU&&(exp[pos]=='*'|exp[pos]=='/')) {posMU = pos; trouvMU = true;}
					pos++;							
				}
				if(trouvAD) {
					operateur = exp[posAD]; 					
					LH = exp.intervalle(0,posAD);					//Définir les limites de l'expression à gauche						
					RH = exp.intervalle(posAD+1,exp.longueur);		//Définir les limites de l'expression à droite						
					if(trouvMU) Lcompos = true; //(car '*''/' ont la priorité d'opération sur '+''-')
					while(!Rcompos&&pos<exp.fin) {if(exp[pos]=='+'|exp[pos]=='-'|exp[pos]=='*'|exp[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite
				} else if(trouvMU) {
					operateur = exp[posMU];  
					LH = exp.intervalle(0,posMU);					//Définir les limites de l'expression à gauche						
					RH = exp.intervalle(posMU+1,exp.longueur);		//Définir les limites de l'expression à droite
					pos = posMU + 1; while(!Rcompos&&pos<exp.fin) {if(exp[pos]=='*'|exp[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite				
				} else {
					operateur = ' '; LH = exp;   //Aucune opération, seulement une évaluation				
				}		
			}			
			//Assigner les valeurs aux membres
			if(Lcompos) {LHcompos = new intoper (LH,biblio); LHsimple = nullptr;} else {LHsimple = new inteval(LH,biblio); LHcompos = nullptr;}
			if(operateur!=' ') {if(Rcompos) {RHcompos = new intoper (RH,biblio); RHsimple = nullptr;} else {RHsimple = new inteval(RH,biblio); RHcompos = nullptr;}}
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


	//ix) classe : boolcompar ; contient les comparaisons d'expressions booléennes évaluables
	class boolcompar {
		//Valeurs membres
		public:
			char comparateur;      //Opérateur de comparaison
			intoper* LH;
			intoper* RH;
			bool constbool;			   //TRUE si l'argument à gauche doit être comparé à un booléen implicite
			bool boolval;		
		//Constructeur ;
		boolcompar () {}; //Constructeur par défaut : vide. 
		template<int Taille>
		boolcompar(StaticVect<char,Taille>& exp, bibliotheque& biblio) : constbool(false), boolval(0) {
			if(exp.longueur==0) {comparateur = ' ';}        //Cas spécial: retourne TRUE automatiquement
			//Recueillir l'opérateur			
			int posEX; bool trouvEX = false;    //point d'EXclamation
			int posPE; bool trouvPE = false; 	//plus PEtit
			int posGR; bool trouvGR = false;	//plus GRand
			int posEG; bool trouvEG = false;	//EGal
			int poscomparateur;
			int pos = 0;
			bool erreur = false;
			while(pos<exp.longueur) {
					if(!trouvEX&exp[pos]=='!') {posEX = pos; trouvEX = true;}
					if(!trouvPE&exp[pos]=='<') {posPE = pos; trouvPE = true;}				
					if(!trouvGR&exp[pos]=='>') {posGR = pos; trouvGR = true;}				
					if(!trouvEG&exp[pos]=='=') {posEG = pos; trouvEG = true;}
					pos++;
			}
			if(trouvEX) {
				if(posEX==0) {constbool = true; boolval = false; comparateur = '=';	poscomparateur = exp.longueur; //Cas spécial réchappé de la fonction précédente (si jamais elle en laisse passer un)
				} else {poscomparateur = posEX;	comparateur = '!'; if(trouvEG&posEG!=posEX+1) erreur = true;}		//!=
			} else if(trouvPE) {poscomparateur = posPE; if(trouvEG&posEG==posPE+1) {comparateur = '«';    			//<=
				} else if(!trouvEG) comparateur = '<'; else erreur = true;											//<	
			} else if(trouvGR) {poscomparateur = posGR;	if(trouvEG&posGR==posGR+1) {comparateur = '»';   			//>=
				} else if(!trouvEG) comparateur = '>'; else erreur = true;											//>	
			} else if(trouvEG) {poscomparateur = posEG; if(exp[posEG+1]) comparateur = '='; else erreur = true;		//==	
			} else {constbool = true; boolval = true; comparateur = '=';	poscomparateur = exp.longueur;} //Cas spécial : "comparaison implicite de la valeur à true"
			//Message d'erreur
			if(erreur) {out("\n\nL'opérateur n'est pas complet dans: "); for(int exppos = exp.debut; exppos<exp.fin; exppos++) {out(exp[exppos]);} abort();}
			//Créer les objets intoper
			LH = new intoper(exp.intervalle(0,poscomparateur),biblio);
			if(!constbool){
				if(comparateur=='='||comparateur=='!'||comparateur=='«'||comparateur=='»') RH = new intoper(exp.intervalle(poscomparateur+2,exp.longueur),biblio); else RH = new intoper(exp.intervalle(poscomparateur+1,exp.longueur),biblio);	
			}			
		}
		//Fonction d'accès : eval
		bool eval(bibliotheque& biblio) {
			if(comparateur=='=') {
				if(constbool) return(LH->eval(biblio)==boolval); else return(LH->eval(biblio)==RH->eval(biblio));			// ==
			} else if(comparateur=='!') {LH->eval(biblio)!=RH->eval(biblio);												// !=
			} else if(comparateur=='<') {LH->eval(biblio)<RH->eval(biblio);												// <
			} else if(comparateur=='«') {LH->eval(biblio)<=RH->eval(biblio);												// <=
			} else if(comparateur=='<') {LH->eval(biblio)>RH->eval(biblio);												// >
			} else if(comparateur=='»') {LH->eval(biblio)>=RH->eval(biblio);												// >=
			}
		}
	};


	//x) classe : boolcompos ; permet de stoker des expressions booléennes évaluables; (LH = "left hand", à gauche ; RH = "Right hand", à droite)
	class boolcompos {
		//Valeurs membres
		public:
			char compositeur;   //'&' ou '|' ou '!' (==false) ou ' ' (==true, sans comparaison)
			boolcompar* LHsimple; boolcompos* LHcompos; 
			boolcompar* RHsimple; boolcompos* RHcompos;
			bool Lcompos; bool Rcompos;	
		//Constructeur
		boolcompos () {}; //Constructeur par défaut : vide. 
		template<int Taille>		
		boolcompos (StaticVect<char,Taille>& exp, bibliotheque& biblio) : Lcompos(false), Rcompos(false)	{    //false : valeurs par défaut qui pourront changer à l'intérieur du constructeur
			StaticVect<char,Taille> LH;
			StaticVect<char,Taille> RH;
			int posPAR; bool trouvPAR = false; int nbPAR = 0;
			int posOU; bool trouvOU = false; 
			int posET; bool trouvET = false;
			int pos = 0;
	        if(exp[0]=='!') {  
			//Cas spécial : compositeur '!'
	       		compositeur = '!'; 							//le (opérateur + RH) deviennent : "==false" : régler ce cas particulier tout de suite
				while(!trouvOU&pos<exp.fin) {
					if(!trouvET&exp[pos]=='&') {posET = pos; trouvET = true;}
					if(!trouvOU&exp[pos]=='|') {posOU = pos; trouvOU = true;}		
					pos++;		
				}
				LH = exp.intervalle(1,exp.longueur);		//Définir les limites de l'expression à gauche					
				if(trouvET|trouvOU) Lcompos = true;     //Définir si LH est composiple
		    } else if(exp[0]=='(') {
				while(!trouvPAR&pos<exp.fin) {
					if(exp[pos]=='(') nbPAR++;	//Gère les parenthèses imbriquées 
					if(exp[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
					pos++;
				} if(!trouvPAR) out("\n\nLa parenthèse n'est pas refermée dans: "); out(exp); abort();
				if(trouvPAR&pos==exp.fin) {exp = exp.intervalle(1,exp.longueur-1); trouvPAR = false; pos = 0;   //Supprimer la parenthèse et remettre les compteurs à 0, pour continuer		
				} else Lcompos = true;		//Noter l'expression à droite comme composite (car elle contient au minimum une parenthèse), et continuer à partir d'après la parenthèse
			} else { 							
			//Cas général : on cherche '|', car '&' a la priorité d'opération
				while(!trouvOU&pos<exp.fin) {
					if(exp[pos]=='|') {posOU = pos; trouvOU = true;}
					if(!trouvET&exp[pos]=='&') {posET = pos; trouvET = true;}
					pos++;							
				}
				if(trouvOU) {
					compositeur = '|';
					LH = exp.intervalle(0,posOU);					//Définir les limites de l'expression à gauche						
					RH = exp.intervalle(posOU+1,exp.longueur);		//Définir les limites de l'expression à droite						
					if(trouvET) Lcompos = true; //(car '&' a la priorité d'opération sur '|')
					while(!Rcompos&pos<exp.fin) {if(exp[pos]=='&'|exp[pos]=='|') Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite
				} else if(trouvET) {  
					compositeur = '&';
					LH = exp.intervalle(0,posET);					//Définir les limites de l'expression à gauche						
					RH = exp.intervalle(posET+1,exp.longueur);		//Définir les limites de l'expression à droite
					pos = posET + 1; while(!Rcompos&pos<exp.fin) {if(exp[pos]=='&') Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite				
				} else {
					compositeur = ' '; StaticVect<char,Taille> LH = exp;   //Aucune comparaison, seulement une évaluation				
				}		
			}			
			//Assigner les valeurs aux membres
			if(Lcompos) {LHcompos = new boolcompos (LH,biblio); LHsimple = nullptr;} else {LHsimple = new boolcompar(LH,biblio); LHcompos = nullptr;}
			if(compositeur!='!'&&compositeur!=' ') {if(Rcompos) {RHcompos = new boolcompos (RH,biblio); RHsimple = nullptr;} else {RHsimple = new boolcompar(RH,biblio); RHcompos = nullptr;}}		
		}
		//Fonction d'accès : eval
		bool eval(bibliotheque& biblio) {
			if(Lcompos){
				if(Rcompos) {
					if(compositeur=='&') {return(LHcompos->eval(biblio)&&RHcompos->eval(biblio)); 
					} else if(compositeur=='|') {return (LHcompos->eval(biblio)||RHcompos->eval(biblio));
					} else if(compositeur=='!') {return(!LHcompos->eval(biblio));
					} else if(compositeur==' ') return(LHcompos->eval(biblio));					
				} else {
					if(compositeur=='&') {return(LHcompos->eval(biblio)&&RHsimple->eval(biblio)); 
					} else if(compositeur=='|') {return (LHcompos->eval(biblio)||RHsimple->eval(biblio));
					} else if(compositeur=='!') {return(!LHcompos->eval(biblio));
					} else if(compositeur==' ') return(LHcompos->eval(biblio));
				}
			} else {
				if(Rcompos) {
					if(compositeur=='&') {return(LHsimple->eval(biblio)&&RHcompos->eval(biblio)); 
					} else if(compositeur=='|') {return (LHsimple->eval(biblio)||RHcompos->eval(biblio));
					} else if(compositeur=='!') {return(!LHsimple->eval(biblio));
					} else if(compositeur==' ') return(LHsimple->eval(biblio));
				} else {
					if(compositeur=='&') {return(LHsimple->eval(biblio)&&RHsimple->eval(biblio)); 
					} else if(compositeur=='|') {return (LHsimple->eval(biblio)||RHsimple->eval(biblio));
					} else if(compositeur=='!') {return(!LHsimple->eval(biblio));
					} else if(compositeur==' ') return(LHsimple->eval(biblio));
				}
			}
		}		
	};


//xi) classe : commande ; permet le stockage de "mots de passe" pour les commandes, à chercher dans le USERINPT
	class commande {
		//Valeurs membres
		public:
			static const int tailledifferentes = 5;
			static const int taillegroupes = 5;
			StaticVect<StaticVect<StaticVect<string,12>,taillegroupes>,tailledifferentes> inclus;		//Mots qui doivent être inclus dans l'expression
					//Niveau le plus extérieur: Différentes façon de dire la commande (ex: manger le concombre / se nourrir / mastiquer) ... Genre?
					//Niveau médian: Différents groupes de mots qui doivent être inclus (ex: manger / concombre)
					//Niveau le plus intérieur: Différents synonymes à l'intérieur du groupe de mots (ex: manger/absorber/grignoter/engouffrer/avaler)
			StaticVect<StaticVect<string,4>,tailledifferentes> exclus;						//Mots qui doivent être absents de l'expression
					//Niveau le plus extérieur: Différentes façon de dire la commande
					//Niveau le plus intérieur: Différents mots qui ne doivent pas se retrouver dans la commande
			StaticVect<string,5> exact;										//Expressions qui doivent exactement être recopiées, sans faute (soit seule manière d'appeler, soit confirmation si ambiguité; voir UserInputInterpret())
			bool ifexact;													//TRUE si une expression exacte est nécessairement recherchée
		//Constructeur
		commande() : ifexact(false) {};	
	};		
	
	
	//xii) classe : chainonauto ; permet le stockage du texte et des conditions d'apparition (automatique)
	class chainonauto {
		//Membres
		public:
			bool fini;		//OBSOLÈTE? OU NON?
			StaticVect<string,10> maille;						//Texte à lire
			StaticVect<StaticVect<int,10>,10> enchainement;  	//int réfère aux positions des mailles         
			StaticVect<intoper,10> enchaineprob;        	 	//Avec le même ordre d'indexation que enchaînement
			boolcompos condition;								//Conditions à respecter pour l'ajout au canal sans UserInput 
			StaticVect<string,10> codespeciauxdebut;
			StaticVect<string,10> codespeciauxfin;
			StaticVect<int,10> override;						//Position d'indexation des canaux à overrider
			int canal;											//Position du canal dans lequel écrire le texte
		//Constructeur
		chainonauto() : fini(false) {};
	};
	
	//xii) classe : chainonmanu ; permet le stockage du texte et des conditions d'apparition (manuelle)
	class chainonmanu {
		//Membres
		public:
			bool fini;		//OBSOLÈTE? OU NON?
			StaticVect<string,10> maille;						//Texte à lire
			StaticVect<StaticVect<int,10>,10> enchainement;  	//int réfère aux positions des mailles         
			StaticVect<intoper,10> enchaineprob;        	 	//Avec le même ordre d'indexation que enchaînement
			boolcompos condition;								//Conditions à respecter pour l'ajout au canal avec UserInput				
			string codespeciauxdebut;
			string codespeciauxfin;
			StaticVect<int,10> override;						//Position d'indexation des canaux à overrider
			int canal;											//Position du canal dans lequel écrire le texte
			commande commandes;                					//Mots à rechercher pour l'ajout au canal à partir du UserInput			
			bool getbusy;                                       //TRUE si le UserInput devient bloqué après que ce chaînon ait été appelé
		//Constructeur
		chainonmanu() : fini(false), getbusy(true) {};	
	};
	
	//xiii) classe : fil ; permet de stocker toutes les textes + commandes selon des catégories (ex: chapitres), pour faciliter la recherche
	class fil {
		//Membres
		public:
			static const int taille = 1;												//Nombre de "chapitre" actuellement disponibles
			static const int taillechapitre = 40;
			StaticVect<StaticVect<chainonmanu,taillechapitre>,taille> chainemanu;		//Groupes de textes + commandes ("chapitres") pour activation manuelle
			StaticVect<StaticVect<chainonauto,taillechapitre>,taille> chaineauto;		//Groupes de textes + commandes ("chapitres") pour activation automatique
			StaticVect<boolcompar,taille> cadenas;										//Conditions d'activation des "chapitres"
	};

//------------------------------------------------------------------------------------------------------------------------------------------------------
//4) Fonction spécialisées de petite taille

	//i) Fonction : CodeSpecialLong ; retourne la longueur d'un code spécial ('§' compris)
	int CodeSpecialLongueur(const StringAsVect& str){
		int longueur = 1;               //Initier l'objet à retourner
		bool fini = false;              
		for(int pos = str.debut + 1; !fini&pos<str.fin ; pos++) {longueur++; if(str.pt[pos]=='§') fini = true;} 		
		return(longueur);		
	}

	//ii) Fonction : CodeSpecialExtract ; extrait une valeur numérique d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
	double CodeSpecialExtractDouble(const StringAsVect& str, int longueur){
		string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
		int longmax = longueur - 1 + str.debut;      //Le dernier caractère étant le '§'		
		for(int pos=2+str.debut; pos<longmax; pos++) nbonly += str.pt[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)	
		return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}		
	int CodeSpecialExtractInt(StringAsVect& str, int longueur){
		string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
		int longmax = longueur - 1;      //Le dernier caractère étant le '§'
		int nbonlypos = 0; for(int pos=2; pos<longmax; pos++) nbonly[nbonlypos++] += str.pt[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)
		return(stoi(nbonly));           //La fonction stoi convertit les strings en int (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}		

	//iii) Fonction : UserInputEcho ; validant graphiquement l'acceptation ou le refus des commandes envoyées
	void UserInputEcho(input& inp, inputecho& inpecho, const fen& base) {	
		chgcol(inpecho.couleur);
		//Clignoter
		if(inpecho.clignote[0]>0){
			curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
		} else {
			curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(' ');			
		}
		chgcol(base.couleur);                       //Revenir à la couleur de base	
		inpecho.nxtt += abs(inpecho.clignote[0]);        //Updater le "next time"
		inpecho.clignote.suppression(1);            //Passer à la prochaine instruction
		if(inpecho.clignote.debut==inpecho.clignote.fin) inpecho.actif = false;			//Vérifier s'il reste toujours du stock à passer dans le canal	
		}	
	
	//iv) Fonction : pause ; arrête les compteurs des canaux
	template <int Taille> 
	void pause(StaticVect<canal,Taille>& canaux) {
		int currentt = timems();
		for(int poscan=0; poscan<canaux.longueur; poscan++) canaux.pt[poscan].pausedt = canaux.pt[poscan].nxtt - currentt;			
	}
	template <int Taille>
	void unpause(StaticVect<canal,Taille>& canaux) {
		int currentt = timems();
		for(int poscan=0; poscan<canaux.longueur; poscan++) canaux.pt[poscan].nxtt = currentt + canaux.pt[poscan].pausedt + canaux.pt[poscan].delay * 5;					
	}
	
	//vi) Fonction : integration ; ajoute un chainon à un canal
	template <int Taille>
	void integration(int chapitrepos, int chainonpos, StaticVect<canal,Taille>& canaux, fil& histoire, bibliotheque& biblio) {
		//Overloader les canaux
		int currentt = timems();		
		for(int posover=0; posover<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].override.longueur; posover++) {    //Pour chaque canaux à overloader
			canaux.pt[histoire.chainemanu.pt[chapitrepos].pt[chainonpos].override.pt[posover]].nxtt = currentt + canaux.pt[histoire.chainemanu.pt[chapitrepos].pt[chainonpos].override.pt[posover]].delay * 5;
			canaux.pt[histoire.chainemanu.pt[chapitrepos].pt[chainonpos].override.pt[posover]].txt.vide();
		}
		//Choisir l'enchaînement à insérer dans le canal
		int sumprob = 0; StaticVect<int,10> vectprob;
		for(int posprob=0; posprob<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].enchaineprob.longueur; posprob++) {	//Évaluer chaque probabilité
			sumprob += histoire.chainemanu.pt[chapitrepos].pt[chainonpos].enchaineprob.pt[posprob].eval(biblio); vectprob.pt[posprob] = sumprob; 
		}
		int randval = rand() % sumprob;  //Obtenir une valeur aléatoire entre [0,sumprob[
		int choix; 
		for(int posprob=0; posprob<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].enchaineprob.longueur; posprob++) {
			if(randval<vectprob[posprob]) {choix = posprob; break;}
		}	
		//Ajouter le texte au canal
		canaux.pt[histoire.chainemanu.pt[chapitrepos].pt[chainonpos].canal].txt.ajout(histoire.chainemanu.pt[chapitrepos].pt[chainonpos].codespeciauxdebut); 
		for(int posench=0; posench<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].enchainement.pt[choix].longueur; posench++) {
			canaux.pt[histoire.chainemanu.pt[chapitrepos].pt[chainonpos].canal].txt.ajout(histoire.chainemanu.pt[chapitrepos].pt[chainonpos].maille.pt[histoire.chainemanu.pt[chapitrepos].pt[chainonpos].enchainement.pt[choix].pt[posench]]);
		}		
		canaux.pt[histoire.chainemanu.pt[chapitrepos].pt[chainonpos].canal].txt.ajout(histoire.chainemanu.pt[chapitrepos].pt[chainonpos].codespeciauxfin);		
	}
	
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//5) Fonction LireCanal()
template<int Taille>
void LireCanal(StaticVect<canal,Taille>& canaux, int canpos, fen& base, memoire& mem) {
	//Updater le "next time"
	canaux.pt[canpos].nxtt += canaux.pt[canpos].delay;
	//Interpréter les "codes spéciaux" (§...§)
	if(canaux.pt[canpos].txt[0]=='§'){		
		//Déterminer la longueur du code spécial
			int CodeSpecialLong = CodeSpecialLongueur(canaux.pt[canpos].txt);			
		//Lire le code spécial		
			if(canaux.pt[canpos].txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture		
				double val = CodeSpecialExtractDouble(canaux.pt[canpos].txt,CodeSpecialLong);       //Extraire le temps que durera la pause
				canaux.pt[canpos].nxtt += round(val * canaux.pt[canpos].vit);                    //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					
			} else if(canaux.pt[canpos].txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = CodeSpecialExtractDouble(canaux.pt[canpos].txt,CodeSpecialLong);       //Extraire la nouvelle vitesse
				canaux.pt[canpos].vit = val;
			}  //EN AJOUTER UN (code spécial) POUR PLACER LE CURSEUR À LA FIN DE LA CONSOLE	
		//Effacer le code spécial du canal
		canaux.pt[canpos].txt.suppression(CodeSpecialLong);                 
	} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
		//Dealer avec la situation où on a à sauter une ligne (créer les lignes supplémentaires et updater les diverses positions)
			bool jump = false;
			if(canaux.pt[canpos].txt[0]=='\n'|canaux.pt[canpos].posx>=base.limtxtx-1) jump = true;     //base.limtxtx - 1 ; car c'est en integer, et canaux.pt[canpos].posx commence à 0!
			if(jump) {	
				mem.newline(canaux.pt[canpos].posy);                     //Introduit une nouvelle ligne à la suite de la position qui lui est fournie	
				//Updater le correctif de décalage de la console par rapport à la mémoire
					if(base.refoule) base.consy++; else if(mem.frontline>base.limtxty) {base.refoule = true; base.consy++;} 						
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore saturée: on pousse vers le bas!
						if(canaux.pt[canpos].posy!=mem.frontline-1) {                             //S'il y a d'autres lignes à repousser vers le bas
							//Ré-écrire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,canaux.pt[canpos].posy+1);  //Mettre le curseur au début de la reconstruction
								for(int county = canaux.pt[canpos].posy + 1 ; county <= mem.frontline ; county++) {   
									for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est saturée: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "reléguant ce qui y était déjà vers le haut")
							curspos(0,canaux.pt[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
						//Tout ré-écrire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county <= canaux.pt[canpos].posy; county++){             //base.consy : facteur de décalage de la console
								for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}	
				//Updater les positions dans les autres canaux    //Parce que leur position dans la mémoire a bougé //la position dans la console est quant à elle gérée par base.consy
				for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {
					if(countcan==canpos) continue;                                    //la mémoire refoule toujours vers le bas!
					if(canaux.pt[countcan].posy > canaux.pt[canpos].posy) canaux.pt[countcan].posy++; else if(canaux.pt[countcan].posy == canaux.pt[canpos].posy) canaux.pt[countcan].posy+=2;
				}       // == : Si deux canaux se situe sur la même ligne, le canal qui change de ligne va couper l'autre en deux, et le renvoyer après sa propre ligne.    	        
				//Updater les positions dans le canal actuel
				if(canaux.pt[canpos].txt[0]=='\n') {canaux.pt[canpos].posx = -1;} else canaux.pt[canpos].posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
				canaux.pt[canpos].posy++;	  																					   //en y 		
			} else {canaux.pt[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caractère       //À partir d'ici, les posx et posy sont la position du charactère actuel (dans la mémoire)!		
		if(canaux.pt[canpos].txt[0]!='\n') {
			curspos(canaux.pt[canpos].posx,canaux.pt[canpos].posy-base.consy) ; out(canaux.pt[canpos].txt[0]);     //Inscrire dans la console
			mem.souvenir[canaux.pt[canpos].posx][canaux.pt[canpos].posy] = canaux.pt[canpos].txt[0];   //Inscrire dans la mémoire			
		}	
		canaux.pt[canpos].txt.suppression(1);       //Effacer le caractère du canal     	   
	}
	if(canaux.pt[canpos].txt.debut==canaux.pt[canpos].txt.fin) canaux.pt[canpos].actif = false;			//Vérifier s'il reste toujours du texte à passer dans le canal
}	
					
          
         
//------------------------------------------------------------------------------------------------------------------------------------------------------
//6) Fonction : UserInputInterpret ; vérifie si la commande entrée correspond à une des actions actuellement autorisée
	template<int Taille>
	void UserInputInterpret(const StaticVect<char,Taille>& command, bibliotheque& biblio, fil& histoire, const fen& base, input& inp, memoire& mem) {
		//
		
		
		/* Donc. Qu'est-ce que je fais?
				1. Vérifier quelle chaine est active
				2. Pour toutes les chaines actives:
				
					A. Vérifier quels chaînons sont actifs? 			Nan, juste inclure un if() au début de la loop for(chainon).
						a) Pour tous les chaînons actifs :
							I. Vérifier si elle demande une expression exacte. Si oui, vérifier de façon rigide si command == expression
							II. Si non, pour toutes les différentes façons de dire la commande:
								i) Vérifier si un des mots du premier groupe est présent. Si oui, garder la position. Vérifier si un des mots du prochain groupe est présent. etc.
								ii) Si tout fonctionne, vérifier si un des mots interdits est présent.
								
						b) Je peux soit vérifier TOUS les chaînon, et me ramasser avec une liste des possibles à la fin.
							Ou bien simplement choisir le premier qui est valide dans la liste.
							
							Dans un monde idéal, je prendrais le premier, car les commandes ne seraient pas ambigues.
							Pourtant, l'erreur étant humaine, je préfère me donner une "failsafe".
								Ce serait plus demandant à chaque enter, par contre.
								Mais puisque le "enter" n'est pas appuyé souvent, je pense que ça vaudrait le coup.
							Donc, je pourrais seulement écrire une courte description de la commande idéale pour chaque chaînon qui en demande.
							Et, dans le cas d'ambiguité, demander : "Vouliez-vous dire XXX ou XXX?"
								Et stocker cette courte description dans la case "exact" de la classe commande, qui est utilisée ainsi si exact == TRUE.
								Bingo. Recyclage d'objet.
								
						c) S'il y a une ambiguité, vérifier les expressions exactes des chaînons. 
							I. Si aucune ne correspond, geler l'écran (ça va être plus simple à gérer), faire une rectangle vide de la bonne taille,
								et demander "Vouliez-vous dire...?". 
							II. Si la commande de confirmation ne correspond pas à une des expressions exactes; Too bad, ça reprend pareil, comme si rien n'avait été entré.
									Ou peut-être donner deux chances?
								
								
				3. S'il y en a seulement un, envoyer la fonction qui poune le texte + les codes spéciaux dans le canal approprié (et qui override les nécessaire, etc.)	
				
			
				
					
		*/
		
			
			//IDÉE:
			//		PEUT-ÊTRE INCLURE DIRECTEMENT DANS L'ÉVALUATION LA MISE EN MAJUSCULE AUTOMATIQUE DU PREMIER MOT?
			//		POUR NE PAS PRENDRE TROP DE PLACE DANS LA MÉMOIRE...? MAIS EN MÊME TEMPS, LE TOTAL N'EST PAS DRAMATIQUE... MAIS ÇA ME PERMETTRAIT DE NE PAS M'EN SOUCIER. VENDU.
			//		
			
					//CE N'EST PAS ENCORE FAIT!!! IL SERAIT IMPORTANT DE L'INTÉGRER!!!
			
			
			
		//Créer des compteurs
		StaticVect<int,histoire.taille> bonchapitre;	  //Créer des StaticVect pour noter la position des chainons qui correspondent à la commande
		StaticVect<int,histoire.taillechapitre> bonchainon;
		StaticVect<bool,commande.taillegroupes> groupebon; 	   	 //Créer un StaticVect pour noter si chaque groupe de mot est bon
		int diffpos; bool exactbon; int commpos; bool exactmauvais; 	//Créer les compteurs pour les expressions exactes
		int groupepos; int synpos; int motpos; int precedpos; bool inclusbon; bool exclusbon;	//Créer les compteurs pour les mots à inclure/exclure	
		//Pour chaque chapitre
		for(int chapitrepos=0; chapitrepos<histoire.taille; chapitrepos++) { if(histoire.cadenas[chapitrepos].eval(biblio)) {			
			//Pour chaque chainon dans l'histoire
			for(int chainonpos=0; chainonpos<histoire.chainemanu.pt[chapitrepos].longueur; chainonpos++) {if(histoire.chainemanu.pt[chapitrepos].pt[chainonpos].condition.eval(biblio)) {
				if(histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.ifexact) {	//Si une commande exacte est nécessaire
					diffpos = 0; exactbon = false;
					while(diffpos<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.exact.longueur&&!exactbon) {
						commpos = 0; exactmauvais = false;
						while(!exactmauvais&&commpos<command.longueur) {if(command[commpos]!=histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.exact.pt[diffpos].pt[commpos]) exactmauvais = true; else commpos++;}	
						if(exactmauvais==false) exactbon = true; else diffpos++;
					}
					if(exactbon)	{integration(chapitrepos,chainonpos,canaux); return();}            //Intégrer tout de suite le bon chaînon dans le canal					
				} else {								//Si plusieurs mots clés doivent être présents
					inclusbon = false; diffpos = 0;
					//Pour chaque façon différente de dire la commande
					while(diffpos<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.inclus.longueur&&!inclusbon) {
						//Vérifier si les mots à être inclus sont présents
							groupepos = 0;  precedpos = 0;   														//Remettre tous les groupes de mots comme incorrects jusqu'à preuve du contraire
							groupebon.remplacement(false); for(int clearpos=1; clearpos<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.inclus.pt[diffpos].longueur; clearpos++) groupebon.ajout(false); 
							//Pour chaque groupe de mots
							while(groupepos<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.inclus.pt[diffpos].longueur) {    
								synpos=0;
								//Pour chaque synonyme
								while(synpos<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.inclus.pt[diffpos].pt[groupepos].longueur&&!groupebon[groupepos]) {		
									commpos = precedpos;
									motpos = 0;
									//Pour chaque lettre
									while(commpos<command.longueur&&!groupebon[groupepos]) {																					
										if(command[commpos++]==histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.inclus.pt[diffpos].pt[groupepos].pt[synpos][motpos++]) {
											if(motpos==histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.inclus.pt[diffpos].pt[groupepos].pt[synpos].longueur) {groupebon[groupepos] = true; precedpos = commpos;}
										} else motpos = 0;
									}
								}					
							}	
							//Maintenant, on a l'information sur quel groupe de mots, dans l'intervalle [0,longueur_de_cette_differente_façon], a un membre qui est présent dans la commande.
							groupepos=0 ; while(groupebon[groupepos++]) if(groupepos==histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.inclus.pt[diffpos].longueur) inclusbon = true;
						//Vérifier si les mots à être exclus sont absents
						if(inclusbon) {
							synpos=0; exclusbon = true;
							//Pour chaque synonyme
							while(synpos<histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.exclus.pt[diffpos].longueur&&exclusbon) {
								commpos = 0;
								motpos = 0;
								//Pour chaque lettre
								while(commpos<command.longueur&&exclusbon) {		//Si le mot est retrouvé, la commande ne correspond pas au chaînon																			
									if(command[commpos++]==histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.exclus.pt[diffpos].pt[synpos].pt[motpos++]) {
										if(motpos==histoire.chainemanu.pt[chapitrepos].pt[chainonpos].commandes.inclus.pt[diffpos].pt[synpos].longueur) exclusbon = false;	
									} else motpos = 0;
								}
							}
						}
					}
					if(inclusbon&&exclusbon) {bonchapitre.ajout(chapitrepos); bonchainon.ajout(chainonpos);}
				}		
			}}
		}}
		//Maintenant, on a l'information sur quels chaînons correspondent (sans expression exacte) à la commande
		if(bonchainon.longueur==0) {
			inp.accepted = false; return();
		} else if(bonchainon.longueur==1) {
			inp.accepted = true; if(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input					
			integration(bonchapitre[0],bonchainon[0],canaux); return();            //Intégrer le bon chaînon dans le canal
		} else {
			//Déterminer si la commande correspond à une expression exacte
			int bonpos = 0; exactbon = false; 
			while(bonpos<bonchainon.longueur&&!exactbon) {
				exactmauvais = false; commpos = 0;
					while(!exactmauvais&&commpos<command.longueur) {if(command[commpos]!=histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0][commpos]) exactmauvais = true; else commpos++;}	
					if(exactmauvais==false) {
						exactbon = true; 	
						inp.accepted = true; if(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].getbusy) inp.busy = true;							
						integration(bonchapitre[bonpos],bonchainon[bonpos],canaux); return();}            //Intégrer tout de suite le bon chaînon dans le canal	
			}	
			//Si l'ambiguité demeure: mettre le jeu sur pause, et faire apparaître les options	
			
			
			
				//FONCTION POUR METTRE LE JEU SUR PAUSE
							//IL LA MANQUE TOUJOURS!!!
									
			
			
			
			chgcol("gris sombre"); curspos(0,0);		//Recopier tout le texte affiché dans la console, mais en gris foncé (background)
			for(int county = base.consy ; county <= mem.frontline ; county++) {   
				for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
			}			
			chgcol("blanc"); curspos(5,3); cursorposy = 3;
			out("Vouliez-vous dire (recopiez la ligne qui correspond à votre choix) :");
			for(int bonpos=0; bonpos<bonchainon.longueur; bonpos++) {
				if(bonpos==bonchainon.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy); out("ou");}}
				cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy);; out(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0]);}
				if(bonpos==bonchainon.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy); out("              ?");}}				
			}		//IL SERAIT BIEN ÉGALEMENT D'ÉGRENNER LE TEXTE, COMME DANS UN CANAL
			string reformulation;
			cin >> reformulation;
				//Vérifier de nouveau
				int bonpos = 0; exactbon = false; 
				while(bonpos<bonchainon.longueur&&!exactbon) {
					exactmauvais = false; commpos = 0;
						while(!exactmauvais&&commpos<reformulation.lenght) {if(reformulation[commpos]!=histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0][commpos]) mauvais = true; else commpos++;}	
						if(exactmauvais==false) {
							exactbon = true; 
							inp.accepted = true; if(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input							
							//METTRE DES CHOSES, GENRE PRENDRE UN TEMPS EN PAUSE POUR SE DIRE: "OK, J'AI COMPRIS".
							integration(bonchapitre[bonpos],bonchainon[bonpos],canaux); return();}            //Intégrer tout de suite le bon chaînon dans le canal	
				}				
			//Si l'ambiguité persiste: le demander une dernière fois
			curspos(3,3); out("Vouliez-vous dire (recopiez EXACTEMENT la ligne qui correspond à votre choix) :");
			cin >> reformulation;	
				//Vérifier de nouveau
				int bonpos = 0; exactbon = false; 
				while(bonpos<bonchainon.longueur&&!exactbon) {
					exactmauvais = false; commpos = 0;
						while(!exactmauvais&&commpos<reformulation.lenght) {if(reformulation[commpos]!=histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0][commpos]) mauvais = true; else commpos++;}	
						if(exactmauvais==false) {
							exactbon = true; 
							inp.accepted = true; if(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input
							//METTRE DES CHOSES, GENRE PRENDRE UN TEMPS EN PAUSE POUR SE DIRE: "OK, J'AI COMPRIS".
							integration(bonchapitre[bonpos],bonchainon[bonpos],canaux); return();}            //Intégrer tout de suite le bon chaînon dans le canal	
				}				
			//Si l'ambiguité est insolvable
			
			//METTRE DES CHOSES, COMME UN MESSAGE DE "TOO BAD" ET ON PASSE À D'AUTRE CHOSE
			inp.accepted = false; return();				
		}
	}        


//------------------------------------------------------------------------------------------------------------------------------------------------------
//7) Fonction UserInput()
void UserInput(input& inp, inputecho& inpecho, const fen& base) {
	if(_kbhit()){
	//i) Capter la lettre tapée
	bool enter = false;
	char key = _getch();                  		//Enregistrer quelle touche a été pressée
			if (key == 0 || key == -32 || key == 224) {      //La valeur est spéciale: elle nécessite de la ré-examiner
				key = _getch();                              //Examiner une deuxième valeur pour identifier
				if(key == 75) {     								 				 //flèche gauche : reculer dans la commande tapée 
					if(inp.inputpos!=0) {
						if(inp.inputpos!=inp.commande.longueur) {
							curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						}          //Remettre en gris la position précédente
						inp.inputpos--;  
					}
				}
				else if (key == 77) {											 	 //flèche droite : avancer dans la commande tapée				
					if(inp.inputpos!=inp.commande.longueur) {
						curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						inp.inputpos++;		
					}			//Remettre en gris la position précédente
				} 
				else if (key == 72)  ;  											 //Flèche du haut   ... Rien ne se passe?
				else if (key == 80)  ;  											 //Flèche du bas    ... Rien ne se passe?
				else if (key == 83) {                                                //Delete : supprimer un caractère de la commande actuelle
					if(inp.inputpos!=inp.commande.longueur) {
						inp.commande.supprposition(inp.inputpos);    
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);    
						out(' ');
					}
				}
			} else 	{                                        //La valeur est "normale"
				//Touches-fonctions
				if(key == 27) {														 //Escape : terminer le programme
					curspos(0,base.limtxty); out("Vous avez entré ESC, le programme se ferme donc."); abort(); 
				} else if(key == 13) {												 //Enter : envoyer la commande
					enter = true;
				} else if(key == 8) {                                                //Backspace : supprimer le caractère précédent
					if(inp.inputpos!=0) {
						inp.inputpos--;
						inp.commande.supprposition(inp.inputpos);   
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);   
						out(' ');    					
					}
					///////////////ICI, JE GÈRE LES ACCENTS MANUELLEMENT, COMME ILS SEMBLENT POSER PROBLÈME!
					//NE MARCHE MÊME PAS, CAR MÊME LE CODE NUMÉRIQUE NE SEMBLE PAS ÊTRE RECONNU!!!
					
				} else if(key==183) {key = 'À'; cout << "test";} else if(key==133) {key = 'à'; cout << "test";} else if(key==128) {key = 'Ç'; cout << "test";} else if(key==135) {key = 'ç'; cout << "test";
				} else if(key==144) {key = 'É'; cout << "test";} else if(key==130) {key = 'é'; cout << "test";} else if(key==212) {key = 'È'; cout << "test";} else if(key==138) {key = 'è'; cout << "test";
				} else if(key==210) {key = 'Ê'; cout << "test";} else if(key==136) {key = 'ê'; cout << "test";} else if(key==215) {key = 'Î'; cout << "test";} else if(key==140) {key = 'î'; cout << "test";
				} else if(key==216) {key = 'Ï'; cout << "test";} else if(key==139) {key = 'ï'; cout << "test";} else if(key==226) {key = 'Ô'; cout << "test";} else if(key==147) {key = 'ô'; cout << "test";
				} else if(key==235) {key = 'Ù'; cout << "test";} else if(key==151) {key = 'ù'; cout << "test";} else if(key==234) {key = 'Û'; cout << "test";} else if(key==150) {key = 'û'; cout << "test";
				} else {															 //Caractère normal : l'ajouter à la commande	
					if(inp.commande.longueur<base.limtxtx-1){
						inp.commande.ajout(key,inp.inputpos);
						inp.inputpos++;
						curspos(inp.inputpos-1,base.limtxty);	                    
						for(int pos=inp.inputpos-1; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);
						if(inp.commande.longueur==inpecho.commande.fin) inpecho.actif = false;                   //Désactiver le canal d'écho si la commande actuelle le dépasse
					}
						
								//BTW: FAUDRAIT AUSSI TOUT UN PAN DE CODE POUR GÉRER LES COMMANDES TROP LONGUES, POUR FAIRE RECULER LE TEXTE
										//Pour l'instant, je restreint l'espace à la largeur de la console, simplement.
							
				}
			}	
		//Remettre la lettre sélectionnée en surbrillance
		if(inp.inputpos!=inp.commande.longueur) {chgcol("blanc"); curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); chgcol(base.couleur);}
			
		//Évaluer la commande		
		if(enter) {								//BTW: Faire changer la vitesse/frénésie du clignotage avec la vitesse globale. Tu veux ça plus vite? Ça va être plus agressant aussi!
			
							//FAIRE UNE FONCTION À PART POUR ÉVALUER LA CORRESPONDANCE DE LA COMMANDE AVEC LES POSSIBILITÉS;
														//ICI, SIMPLEMENT S'OCCUPER DE L'AFFICHAGE (EFFETS GRAPHIQUES DIFFÉRENTS SI C'EST ACCEPTÉ OU NON...)!														
			inpecho.commande.remplacement(inp.commande);						
			inpecho.actif = true; inpecho.nxtt = timems();          							 //Mettre à l'heure le "nexttime"											
			if(inp.accepted) {
				if(inp.busy) {			//Conserver le texte en place, en plus pâle, pendant quelques secondes. Peut être effacé progressivement par une nouvelle commande
					inpecho.couleur = "gris sombre";
					int clignarr [2] {3000,-1};
					inpecho.clignote.remplacement(clignarr, 2);
				} else {				//Faire clignoter le texte, en plus pâle, pendant quelques secondes.
					inpecho.couleur = "gris sombre";
					int clignarr [6] {500,-500,500,-500,500,-1};
					inpecho.clignote.remplacement(clignarr, 6);
				}                				
			} else{						//Faire clignoter le texte, en rouge foncé, pendant quelques secondes.
				
				inpecho.couleur = "rouge sombre";
				int clignarr [8] {500,-500,500,-500,500,-500,500,-1};				
				inpecho.clignote.remplacement(clignarr,8);	
			}
			curspos(0,base.limtxty); for(int pos=0; pos < base.limfenx-1; pos++) out(' ');    //Nettoyer la ligne avant de la faire flasher
			inp.inputpos = 0; inp.commande.vide();                               //Nettoyer l'objet input			
		}	
	}
}     


//------------------------------------------------------------------------------------------------------------------------------------------------------
//8) Aire de tests
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
	//x, y, width, height,
	fen base(600,30,500,500);                                           //Crée également l'objet dans lequel ces paramètres sont définis
	
	//Créer l'objet de mémoire, qui stockera tous les caractères utilisés
	memoire mem {base.limtxtx};

	//Créer les objets d'input
	input entree; inputecho entreeecho;

	//Créer les canaux utilisés
	canal can1;
	canal can2;
	
	//Test: changer les délais manuellement
	can1.delay = 140;
	can2.delay = 230;
	
	//Ajouter du texte aux canaux
	string txt0 = "Celà est du texte!\nJe dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	string txt1 = "§p1000§\nLe canal 1 \n           est sooooo boring. Ark.§p1000§\n§p1000§Je suis le canal 2.";
	can1.txt.ajout(txt0); can2.txt.ajout(txt1);
	
	//Rendre manuellement les canaux actifs
	can1.actif = true; can2.actif = true;	
	
	//Ajouter les canaux dans l'objet StaticVect<canal>
	canal canx [2] = {can1,can2};
	StaticVect<canal,2> canaux (canx,2);          

	//Faire une boucle pour que les canaux s'expriment!
	bool gogogo = true;
	int currentt;
	while(gogogo){
			currentt = timems();
			if(canaux.pt[0].actif&canaux.pt[0].nxtt<currentt) LireCanal(canaux,0,base,mem);
			if(canaux.pt[1].actif&canaux.pt[1].nxtt<currentt) LireCanal(canaux,1,base,mem);
			UserInput(entree,entreeecho,base);
			
			if(entreeecho.actif&entreeecho.nxtt<currentt) {UserInputEcho(entree,entreeecho,base);}
			
			//if(!canaux.pt[0].actif&!canaux.pt[1].actif) gogogo = false;
		}		
		
	curspos(0,13);


}								
