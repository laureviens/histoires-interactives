/*
			///||================================---2018/06/15---================================||\\\
\\\||================================---Cadre fonctionnel global pour lire des histoires---================================||///
*/

//------------------------------------------------------------------------------------------------------------------------------------------------------
//-1) Liste de choses en suspend
/*
	2019-06-18:
				Mon moyen de manipuler la console est en conflit avec le fonctionnement par d�faut de la console.
				Je suppose une fen�tre fixe, pour toujours prise dans ses premi�res lignes.
				Pourtant, dans la console de base, si largeur en x est finie et fixe, la hauteur en y est infinie.
				 
				Pour arriver � contourner cela, il me faut �viter de d�placer automatiquement la fen�tre de la console,
				question de toujours rester entre [0,maxy] en y. 
				Pour �viter de d�placer, il faut �viter de cr�er une nouvelle ligne � partir de la derni�re ligne (maxy).
				
				Pour le moment, le code en tant que tel n'est vraiment pas adapt� pour faire face � cette exception.
				Mon moyen de contournement, c'est d'utiliser la derni�re ligne de la console pour afficher le texte entr�
				(puisque je ne peux pas me fier sur les entr�es standardis�es de type cin -pour pouvoir entrer le texte n'importe quand-
				pour faire appara�tre le input qui est tap�). Ce que j'allais faire de toute fa�on.
				
				Il serait pourtant safe d'int�grer des "safe-gards" directement dans la fonction lire(), genre printer une erreur et aborter
				le processus si on change de ligne � partir de la derni�re. Something like that.
				
				Aussi, pour parvenir � faire fonctionner mon bricolage, je suis parvenue exp�rimentalement � la ligne:
					curspos(0,canaux.pt[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 
				qui est ma foi un peu patant�e. Je ne sais pas pourquoi elle marche, mais c'est la seule qui marche. � rev�rifier plus tard.
*/

/*
	2019-06-22:
				La fonction pour afficher l'input semble avoir de la difficult� � g�rer les accents.
				Les bouts de texte �crits dans le script s'affichent correctement,
				mais le unicode utilis� pour getch() ne semble pas correspondre aux bons symboles.
				Bon.
				M�me quand j'associe manuellement le code num�rique aux bon char, �a garde la m�me erreur.
				Comme si les char provenant de l'user input �tait diff�rents de ceux du script?
				
				Bon, c'est officiel, la liste de if() else() dans out() ne reconna�t pas les char provenant du clavier.
				Je ne sais pas quoi y faire. Est-ce que �a va chier aussi la reconnaissance dans "find()"???
				
				C'est vraiment �trange.
				
*/


/*
	2019-07-05:
				Dans les fonctions integration() et UserInputInterpret(),
				j'utilise beaucoup d'indexation. �a devient difficile � lire.
				Je pense que �a n'alourdirait pas trop l'ex�cution de cr�er un objet temporaire pour chaque chainon (rendrait le tout plus clair).
				J'ai par contre peur que �a fuck avec les pointeurs, que les objets soient modifi�s (sont tous par & r�f�rence), etc.
					Je conserve donc cette id�e quand j'aurai minimalement une version test�e, qui fonctionne.
*/

/*
	2019-07-13:
				Ce qu'il me reste � faire:
					-Tester, avec des vraies mailles (manuelles), si le UserInputInterpret agit comme il le devrait.
						-Pour �a, faudrait changer les fonction de remplissage de boolcompar et etc., pour mettre un fct au lieu d'un constructeur
					-Cr�er un �quivalent de la fonction pour les mailles automatiques
					-Cr�er des fonctions-raccourcies afin de facilement remplir les mailles (commandes, conditions, etc).
						(Pour la commande, peut-�tre travailler avec strings + parser : aime|adore|appr�cie,fleurs|p�tales;fleurs|p�tales,favorit|pr�f�r�
					-R�gler le cas des accents.
					-D�finir une synthaxe pour les genres
						-Soit changer le texte de toutes les maillons au d�part pour les mettre du bon genre
						-Soit cr�er un code sp�cial universel qui : a) efface le code sp�cial, sauf le bon accord  b) nxtt -= delay (car ensuite, on ajoute delay); pour que le bon accord commence � s'�crire sans d�lai
								ex: �g0vacante/vacant.e/vacant�    //g pour gender  ; le chiffre repr�sente la personne : 0 = joueuxe, 1 = "je", 2 = "tu", 3-4-5.. = "iel"
									//PERSO, j'aime mieux le code sp�cial			
					-Peut-�tre remplacer le vieux "StringAsVect" dynamique par un "StaticVect"?				
*/

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entr�es/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contr�le du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //N�cessaire pour la taille de la fen�tre: informe qu'on est sur Windows 2000 ou plus r�cent (??? Optionnel?)
#include <windows.h>           //N�cessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>            //N�cessaire pour savoir la position du curseur sur Windows
#include <winuser.h>		   //N�cessaire pour savoir la position du curseur sur Windows
#include <conio.h>             //N�cessaire pour enregistrer les inputs du clavier
#include <io.h>				   //N�cessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>			   //N�cessaire pour d�crypter les accents en unicode
#include <stdlib.h>     	   //N�cessaire pour jouer avec des nombres al�atoires  /* srand, rand */

/*
	2019-07-05:
A typical way to generate trivial pseudo-random numbers in a determined range using rand is to use the modulo of the returned value 
		by the range span and add the initial value of the range:

v1 = rand() % 100;         // v1 in the range 0 to 99
v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 
*/


using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Classes-contenantes g�n�rales
	
	//i) classe : StringAsVect ; permet un simul�cre d'allocation dynamique de m�moire, avec la magie de voir plus grand + indexation
	class StringAsVect {
	//Comment �a marche:
			//L'array est d'abord cr�� plus gros que n�cessaire. On ne supprime pas vraiment les valeurs qui y passent,
			//on ne fait que s'�tendre dans l'array:
				//On supprime chaque position depuis le d�but;
				//On ajoute chaque nouvelle position � la fin.
			//Lorsque l'array est rendu � sa capacit� maximale, 
				//on refait l'array au complet.	
		//Valeurs membres	
		public:
			static const int TailleBase = 200;       //Taille de base des objets 
			char* pt;     //D�clarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'ext�rieur 
			int nb;       //D�clarer le nombre d'objets de l'array
			int debut;    //D�clarer la position de la premi�re valeur
			int fin;      //D�clarer la position de la derni�re valeur
			int longueur; //Longueur de la partie active, du d�but � la fin
		//Constructeurs	
			StringAsVect() : nb(TailleBase), debut(0), fin(0), longueur(0) {  //D�faut
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace					
			}
			StringAsVect(char nxt) : nb(TailleBase), debut(0), fin(1), longueur(1) {  //� partir d'une seule valeur
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
				pt[0] = nxt;
			}
			StringAsVect(char nxt[], int nbpos) : nb(nbpos + TailleBase), debut(0), fin(nbpos), longueur(nbpos) {   //� partir d'un array
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
					for(int pos=0; pos<fin; pos++) pt[pos] = nxt[pos];
			}
			StringAsVect(std::string nxt) : nb(nxt.length() + TailleBase), debut(0), fin(nxt.length()), longueur(nxt.length()) {      //� partir d'un string
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
					for(int pos=0; pos<fin; pos++) pt[pos] = nxt[pos];
			}	
		//Destructeur
			~StringAsVect() {delete[] pt;}	
		//Copy constructor  
			StringAsVect(const StringAsVect& nxt) : nb(nxt.nb), debut(0), fin(nxt.longueur), longueur(nxt.longueur) {
					try{pt = new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt = new char [nb];             	//Vraiment allouer l'espace		
				int nxtpos = nxt.debut; for(int pos=0; pos<fin; pos++) pt[pos] = nxt.pt[nxtpos++];        //Copier le contenu (en remettant le d�but � 0)	//ATTENTION J'AI CHANG� CETTE LIGNE RISQUE DE BUG				
			}
		//Copy assignment
			StringAsVect& operator= (const StringAsVect& nxt) {
				nb = nxt.nb; debut = 0; fin = nxt.longueur;	longueur = nxt.longueur;			
				delete[] pt;     //Effacer l'array vers lequel je pointe actuellement
					try{pt = new char [nb];}  //Essayer d'allouer l'espace 
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)				
				pt = new char [nb];		     		//Vraiment allouer un nouvel espace pour le nouvel objet
				int nxtpos = nxt.debut; for(int pos=0; pos<fin; pos++) pt[pos] = nxt.pt[nxtpos++];        //Copier le contenu (en remettant le d�but � 0)	//ATTENTION J'AI CHANG� CETTE LIGNE RISQUE DE BUG				
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
   		//Op�rateur d'acc�s : []
		   char operator[] (int pos) {return(pt[debut + pos]);}
		//Fonction de modification : ajout          //Ajoute les valeurs en right-hand � la SUITE des valeurs d�j� contenues
		   void ajout (char nxt) {
		   		if(fin + 1 < nb) {      //Pas besoin de r�-allouer la m�moire
		   			pt[fin] = nxt; fin++; longueur++; 
				} else {                //Besoin de r�-allouer
					nb = longueur + TailleBase;             	//D�terminer le nombre d'�l�ments du prochain bloc de m�moire
						try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 
					  	catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de m�moire � l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de m�moire des vieux �l�ments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					nwpt[posNeuf] = nxt;                        //Ajouter le nouvel �l�ment
					debut = 0; fin = longueur + 1;	           //R�-initialiser les compteurs de position
					longueur++;
					delete[] pt;       							//Supprimer les �l�ments contenus dans le viel array						
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }
		   void ajout (const string& nxt) {
		   		if(fin + nxt.length() < nb) {      //Pas besoin de r�-allouer la m�moire
		   			int nbnxt = nxt.length();
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt[posnxt];   
					 fin+=nwend; longueur+=nbnxt;
				} else {                //Besoin de r�-allouer
					int nbnxt = nxt.length();    
					nb = longueur + TailleBase;             	//D�terminer le nombre d'�l�ments du prochain bloc de m�moire
						try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 					
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de m�moire � l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de m�moire des vieux �l�ments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[posNeuf++] = nxt[posnxt]; //Ajouter les nouveaux �l�ments
					debut = 0; fin = longueur + nbnxt;          //R�-initialiser les compteurs de position
					longueur += nbnxt;
					delete[] pt;       							//Supprimer les �l�ments contenus dans le viel array	
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }		   
		   void ajout (const StringAsVect& nxt) {
		   		if(fin + nxt.nb < nb) {      //Pas besoin de r�-allouer la m�moire
		   			int nbnxt = nxt.nb;
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt.pt[posnxt+nxt.debut];   
					 fin+=nwend; longueur+=nbnxt;
				} else {                //Besoin de r�-allouer
					int nbnxt = nxt.nb;    
					nb = longueur + TailleBase;             	//D�terminer le nombre d'�l�ments du prochain bloc de m�moire
							try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 					
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de m�moire � l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de m�moire des vieux �l�ments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[posNeuf++] = nxt.pt[posnxt+nxt.debut]; //Ajouter les nouveaux �l�ments
					debut = 0; fin = longueur + nbnxt;          //R�-initialiser les compteurs de position
					longueur += nbnxt;
					delete[] pt;       							//Supprimer les �l�ments contenus dans le viel array	
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }
		//Op�rateur de modification : suppression          //"Supprime" le nombre de positions en right-hand AU D�BUT des valeurs d�j� contenues
			void suppression (int nb) {
				if(nb > fin-debut) debut = fin; else debut+=nb; 
				longueur--;
			}
		//Fonction de modification : supprposition       //Supprime l'entr�e � la position indiqu�e
			void supprposition (int pos) {
				if(pos >= debut & pos < fin) {
					for(int ptpos = pos; ptpos < fin-1; ptpos++) {pt[ptpos] = pt[ptpos+1];}
					fin--; longueur--;
				}			
		//Fonction de modification : vide()
			void vide(void) {debut = 0; fin = 0; longueur = 0;}	
	};		

	//ii) classe : StaticVect ; sauvegarde un array "semi-dynamique", o� la m�moire utilis�e est fixe, mais les fonctionnalit�s sont les m�mes que StringAsVect.
	template <class Type, int Taille>
		class StaticVect {
			//Valeurs membres	
			public:
				Type pt [Taille];   //D�clarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'ext�rieur 
				int taille = Taille; //Nombre d'objets de l'array
				int debut;  //Position actuelle de d�but
				int fin;    //Position actuelle de fin
				int longueur;       //Nombre d'objets entre le d�but et la fin
			//Constructeurs	:
				StaticVect<Type,Taille>() : debut(0), fin(0), longueur(0) {}  //D�faut 
				StaticVect<Type,Taille>(Type nxt) : debut(0), fin(1), longueur(0) {pt[0] = nxt;}  //Une seule valeur
				StaticVect<Type,Taille>(Type* ptarr, int nb) : debut(0), fin(nb), longueur(nb) {for(int pos=0;pos<nb;pos++) pt[pos] = ptarr[pos];}   //Array
				StaticVect<Type,Taille>(const StaticVect<Type,Taille>& nxt) : debut(0), fin(nxt.longueur), longueur(nxt.longueur) {for(int pos=0;pos<nxt.longueur;pos++) pt[pos] = nxt.pt[nxt.debut + pos];}    //POURRAIT �TRE MIEUX �CRIT???
			//Copy assignement :
				StaticVect<Type,Taille>& operator = (const StaticVect<Type,Taille>& nxt) {
					debut = 0; fin = nxt.longueur; longueur = nxt.longueur;
					for(int pos=0;pos<nxt.longueur;pos++) pt[pos] = nxt.pt[nxt.debut + pos];
					return(*this);			
				}	
	   		//Op�rateur d'acc�s : []
			   Type& operator[] (int pos) {
			   		return(pt[debut + pos]);
			   }
			//Fonction d'acc�s : intervalle()
				StaticVect<Type,Taille> intervalle(int posdebut, int posfin) {
					if(posfin <= longueur) {
						StaticVect<Type,Taille> returnvect;
						returnvect.debut = 0; returnvect.longueur = posfin - posdebut; returnvect.fin = returnvect.longueur;
						int returnpos = 0; for(int pos = posdebut; pos<posfin; pos++) {returnvect.pt[returnpos++] = pt[pos+debut];}
						return(returnvect);				
					} else {std::wcout<<"intervalle() de "; std::wcout<<posdebut; std::wcout<<" � "; std::wcout<<posfin; std::wcout<<" dans \""; for(int pos=0; pos<fin; pos++) std::wcout<<pt[pos+debut]; std::wcout<<"\", d�passant donc la longueur"; abort();}
				}
			//Fonction de modification : ajout()
				bool ajout(Type nxt) {if(fin+1 <= taille) {pt[fin] = nxt; fin++; longueur++; return(true);} else return(false);}       //Fonction de retour pour communiquer la r�ussite ou non!				
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
			//Fonction de modification : suppression          //"Supprime" le nombre de positions en right-hand AU D�BUT des valeurs d�j� contenues
				void suppression (int nb) {
					if(nb > fin-debut) debut = fin; else debut+=nb; 
					longueur-=nb;
				}
			//Fonction de modification : supprposition       //Supprime l'entr�e � la position indiqu�e
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

	//ii) Objets : divers objets de windows ; permet de modifier le texte affich� dans la console   	            	//WINDOWS ONLY
	HANDLE TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);        //Objet permettant de modifier le texte affich� dans la console 
	COORD CursorPosition;                                     	//Objet permettant de se situer sur la console
	CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;                //Objet permettant de conna�tre la position du curseur dans la console
	CONSOLE_CURSOR_INFO CursorInfo;	                            //Objet permettant de modifier le curseur
	HWND DimConsole = GetConsoleWindow();                       //Objet permettant de modifier les dimensions + la position de la console

	//iii) Fonction: curspos ; d�placer le curseur sur la console                                                          //WINDOWS ONLY
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
		
	//v) Fonction : out ; affiche le caract�re dans la console
	void out(char lettre){
		if(lettre=='�') std::wcout << L"\u00C0";
		else if(lettre=='�') std::wcout << L"\u00E0";
		else if(lettre=='�') std::wcout << L"\u00C7";		
		else if(lettre=='�') std::wcout << L"\u00E7";
		else if(lettre=='�') std::wcout << L"\u00C9";		
		else if(lettre=='�') std::wcout << L"\u00E9";
		else if(lettre=='�') std::wcout << L"\u00C8";
		else if(lettre=='�') std::wcout << L"\u00E8";
		else if(lettre=='�') std::wcout << L"\u00CA";
		else if(lettre=='�') std::wcout << L"\u00EA";
		else if(lettre=='�') std::wcout << L"\u00CE";
		else if(lettre=='�') std::wcout << L"\u00EE";
		else if(lettre=='�') std::wcout << L"\u00CF";
		else if(lettre=='�') std::wcout << L"\u00EF";						
		else if(lettre=='�') std::wcout << L"\u00D4";
		else if(lettre=='�') std::wcout << L"\u00F4";
		else if(lettre=='�') std::wcout << L"\u00D9";
		else if(lettre=='�') std::wcout << L"\u00F9";	
		else if(lettre=='�') std::wcout << L"\u00DB";
		else if(lettre=='�') std::wcout << L"\u00FB";	
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


	//vi) Fonction : chgcol ; change la couleur du texte � entrer
	void chgcol(string color) {
		WORD code;                                            //Voir Internet pour la l�gende
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

	//vii) Fonction : strtobool ; interpr�te un string pour renvoyer un bool�en (similaire � stoi() ou stod() )
	bool strtobool(string str) {
		if(str[0]=='0') {return(false);
		} else if(str[0]=='f'&str[1]=='a'&str[2]=='l'&str[3]=='s'&str[4]=='e') {return(false);
		} else if(str[0]=='F'&str[1]=='A'&str[2]=='L'&str[3]=='S'&str[4]=='e') {return(false);
		} else if(str[0]=='1') {return(true);
		} else if(str[0]=='t'&str[1]=='r'&str[2]=='u'&str[3]=='e') {return(true);
		} else if(str[0]=='T'&str[1]=='R'&str[2]=='U'&str[3]=='E') {return(true);
		} else {out("\n\nTentative d'�valuer \""); for(int pos = 0; pos<str.length(); pos++) {out(str[pos]);} out("\" comme un bool�en."); abort();}
	}
	
	//viii) Fonction : ColNameFind ; trouve une (la premi�re rencontr�e) position d'indexation dans un StaticVect<string,Taille> qui correspond exactement � un string
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
	
	//ix Fonction : stop ; arr�te manuellement l'ex�cution d'un programme. � utiliser seulement dans un menu!
	void stop(int val) {
		int targett = timems() + val;
		while(TRUE) {if(timems()>targett) return;}
	}

	//x Fonction : egrener ; fait appara�tre le texte manuellement, comme s'il �tait dans un canal. � utiliser seulement dans un menu!
	void egrener(string str, int delay) {
		for(int pos=0; pos<str.length(); pos++) {out(str[pos]); stop(delay);}
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Classes-contenantes sp�cialis�es (canaux et autres)

	//DEBUGGG                  //But no longer debug??
	const int taillecanal = 2;
	const int taillegroupes = 5;
	

	//i) classe : memoire ; permet de sauvegarder la "m�moire" de la console, c'est-�-dire tous le texte s'y �tant d�j� inscrit
		
		class memoire{
			//Membres
			public: 
				static const int TailleBase = 500;       //Nombre de ligne de base des objets 
				int nbcol;                  //Nombre de colonnes (fixe)
				int nbligne;                //Nombre de lignes totales de stockage (pour �viter de r�-allouer la m�moire tout le temps)
				int frontline;              //Ligne � laquelle est rendue l'�criture
				char** souvenir;            //L'objet contient, en fa�ades, des pointeurs pointant � d'autres pointeurs
			//Constructeur par d�faut
			memoire() {
				nbcol = 1;
				frontline = 0;                         //Ce qui suit semble �tre la seule mani�re de cr�er des arrays dynamiques
				nbligne = TailleBase;            
					try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
				souvenir = new char* [nbcol];   //Cr�er un premier array contenant des pointers
				//Cr�er les lignes pour chaque colonne, et les remplir d'espace
				for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}
			}
			//Constructeur pour avoir le bon nombre de colonnes
			memoire(int ncol) {
				nbcol = ncol;
				frontline = 1;                         //Ce qui suit semble �tre la seule mani�re de cr�er des arrays dynamiques
				nbligne = TailleBase;            
					try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
				souvenir = new char* [nbcol];   //Cr�er un premier array contenant des pointers
				//Cr�er les lignes pour chaque colonne, et les remplir d'espace
				for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}
			}			//Destructeur
			~memoire() {
				for(int col=0; col<nbcol ; col++) delete[] souvenir[col] ; delete[] souvenir;   //Bien d�construire tout proprement
			}
			//Fonction d'acc�s : retourner certaines positions
			char acces (int posx, int posy) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(souvenir[posx][posy]);
			}
			//Fonction de modification : newline ; ajouter une ligne � la suite de la position sp�cifi�e (Op�rateur +) 
			void newline (int pos) {
				if(frontline+1<nbligne) {
					int emptypos = pos + 1;   //Calculer la position qui sera vide
					//D�placer de 1 tout ce qui vient ensuite, en commen�ant par la fin
					for(int lin = frontline; lin > pos; lin--) for(int col = 0; col < nbcol; col++) souvenir[col][lin+1]=souvenir[col][lin]; 
					for(int col = 0; col < nbcol; col++) souvenir[col][emptypos] = ' ';   //Remplir la position vide d'espace
					frontline++;   //Noter qu'on ajoute une ligne
				} else {
					int emptypos = pos + 1;   //Calculer la position qui sera vide
						try{char** nwsouv = new char* [nbcol] ; for(int col = 0; col<nbcol ; col++) {nwsouv [col] = new char [nbligne+TailleBase];}}  //Tenter d'allouer l'espace
					  	catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)
					char** nwsouv = new char* [nbcol] ; for(int col = 0; col<nbcol ; col++) {nwsouv [col] = new char [nbligne+TailleBase];}  //Initialiser le nouveau bloc de m�moire � l'aide d'un pointeur temporaire
					int oldpos = 0;  //D�clarer un compteur pour les vieilles positions				
					for(int nwpos=0; nwpos < frontline; nwpos++) {  //Remplir, en laissant une position vide
						if(nwpos==emptypos) {for(int xpos = 0; xpos<nbcol ; xpos++) nwsouv[xpos][nwpos] = ' '; continue;}  //Cette ligne remplit d'espace, puis saute les autres instructions jusqu'� la fin de la boucle 
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

	
	//ii) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant � lire, la vitesse, etc.
	class canal {
		//Membres
		public:
			static const int taillecanal = 2;
			int nxtt;           //D�clarer le moment o� la prochaine entr�e sera trait�e         
			int pausedt;	    //Diff�rence entrepos�e entre nxtt et currentt, dans le cas o� l'ex�cution est arr�t�e (ex: faire appara�tre un menu)				
			int delay;          //D�clarer le d�lai de base entre chaque entr�e
			int posx, posy;		//D�clarer les coordonn�es de la derni�re entr�e dans la m�moire (la pr�c�dente)   
								//les positions de la consoles sont d�finies en d�calant ces derni�res
			StringAsVect txt;   //D�clarer le texte qui reste � lire  				
			bool actif;			//D�clarer le compteur d'activit�
			double vit;         //D�clarer la vitesse actuelle de d�filement et de pauses (toujours par rapport � la base, 1)
		//Constructeur
		canal() : delay(400), posx(-1), posy(0), actif(false), vit(1) {nxtt = timems();}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
	};

	//iii) Classe : fen ; permet de sauvegarder les param�tres relatifs aux caract�ristiques de la fen�tre de sortie (console)
	class fen {
		//Membres
		public:
			int posfenx, posfeny;     //Positions de la fen�tre sur l'�cran                                                    //WINDOWS ONLY
			int sizefenx, sizefeny;   //Taille de la fen�tre en pixel														   //WINDOWS ONLY
			int limfenx, limfeny;     //Dimensions de la fen�tre en terme de nombre de caract�res pouvant y �tre contenus
			int limtxtx, limtxty;     //Dimensions de la portion o� le texte s'affiche en terme de nombre de caract�res pouvant y �tre contenus
			int consy;             //Facteur de d�calement de la console o� appara�t le texte avec la m�moire, o� il est stock�
			bool refoule;          //Flag pour voir si le facteur de d�calement entre en compte
			string couleur;           //Couleur de base du texte
		//Constructeurs
		     //Constructeur pour initialiser tous les param�tres automatiquement (� mettre dans le main())
		fen(int posx, int posy, int sizex, int sizey) : posfenx(posx), posfeny(posy), sizefenx(sizex), sizefeny(sizey), consy(0), refoule(false), couleur("gris") {
				//MoveWindow(window_handle, x, y, width, height, redraw_window);       //Les unit�s sont en pixels!
			MoveWindow(DimConsole, posx, posy, sizex, sizey, TRUE);                    //Cr�er la fen�tre de la bonne taille          //WINDOWS ONLY
			GetConsoleScreenBufferInfo(TxtConsole, &ScreenBufferInfo);                 //Acc�der � la taille de la console            //WINDOWS ONLY
			curson(false);                                                     		   //Faire dispara�tre le curseur                 //WINDOWS ONLY
			chgcol(couleur);														   //Mettre le texte de la couleur par d�faut
    		_setmode(_fileno(stdout), _O_U16TEXT);									   //Permettre l'affichage de l'UNICODE           //WINDOWS ONLY  
			limfenx = ScreenBufferInfo.srWindow.Right + 1; limfeny = ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations
			limtxtx = limfenx; limtxty = limfeny - 1;
		}                  //JE PROFITE DE CETTE FONCTION POUR �GALEMENT CHANGER LES PARAM�TRES DE BASE! ATTENTION!
		fen(int x, int y) {limtxtx = x; limtxty = y; consy = 0; refoule = false;}      //Constructeur permettant d'aligner manuellement les dimensions de la fen�tre avec la r�alit�	
	};
		
		
	//iv) classe : input ; sauvegarde les informations relatives aux inputs
	class input {
		//Valeurs membres
		public:
			StaticVect<char,200> commande;          	//Phrase que contient le buffer         //Peut-il devenir un StringAsVect?
			int inputpos;                   //Position d'indexation du prochain caract�re    == StaticVect.fin? Non! Car �a peut bouger!
			bool accepted;                  //Flag concernant la derni�re commande; utile pour l'affichage visuel
			bool busy;						//Flag concernant la derni�re commande; utile pour l'affichage visuel
		//Constructeur par d�faut
			input() : inputpos(0), accepted(false), busy(false) {}
	};							
						
	//v) classe : inputecho ; permet l'affichage r�siduel des commandes (accept�es ou refus�es)	
	class inputecho {
		//Valeurs membres
		public:
			StaticVect<char,200> commande;
			StaticVect<int,50> clignote;               //Conserve les instructions pour le clignotement : positif = affiche, n�gatif = pause.	
			string couleur;                            //Conserve la couleur du clignotement
			bool actif;							       //Compteur d'activit�
			int nxtt;         						   //Moment o� la prochaine entr�e sera trait�e         
			int pausedt;							   //Diff�rence entrepos�e entre nxtt et currentt, dans le cas o� l'ex�cution est arr�t�e (ex: faire appara�tre un menu)				
		//Constructeur par d�faut
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
		//Fonction d'acc�s : acces ; retourner la valeur � certaines positions
		int acces(int posrayon, int poslivre) {return(rayon[posrayon][poslivre]);}
		//Fonction de modification : modif ; modifie la valeur � certaines positions
		void modif(int posrayon, int poslivre, int value) {rayon[posrayon][poslivre] = value;}
	};

	//vii) classe : inteval ; contient l'expression � �valuer (la plus simple) ; constructeur transforme les noms de "livre" en position d'indexation
	class inteval {
		//Valeurs membres
		public:
			int rayonpos;   		//Position d'indexation de la "famille" de l'argument compar� � gauche					
			int livrepos;			//Position d'indexation de l'argument compar� � gauche, � l'int�rieur de sa "famille"
			int boolval; int intval;
			int constbool; int constint;      //TRUE si les valeurs sont bool�ennes ou int, � la place d'�valu�es.
		//Constructeur
		inteval () {}; //Constructeur par d�faut : vide. 
		//Fonction de modification : set() ; permet de construire l'objet avec une expression
		template<int Taille>
		void set(StaticVect<char,Taille> exp, bibliotheque& biblio) : constbool(false), constint(false) {
			string rayon, livre;    //Initier un string, dans lequel seront ins�r�s seulement les noms des rayons/livres
			int strpos, pos; strpos = 0; pos = 0; while(exp[pos]!='�'&pos<exp.longueur) rayon += exp[pos++];
			//�valuer si le string contient des noms ou une valeur
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
		//Fonction d'acc�s : eval()	
		int eval(bibliotheque& biblio) {if(constbool) return(boolval); else if(constint) return(intval); else return(biblio.acces(rayonpos,livrepos));}	
	};	

	//viii) classe : intoper ; contient les op�rations d'expressions bool�ennes �valuables
	class intoper {
		//Valeurs membres
		public:
			char operateur;      	//Op�rateur
			intoper* LHcompos;
			intoper* RHcompos;
			inteval* LHsimple;
			inteval* RHsimple;
			bool Lcompos; bool Rcompos;				//TRUE si les valeurs sont composites
		//Constructeur
		intoper () {}; //Constructeur par d�faut : vide. 
		//Fonction de modification : set() ; permet de construire l'objet avec une expression
		template<int Taille>
		void set(StaticVect<char,Taille> exp, bibliotheque& biblio) : Lcompos(false), Rcompos(false) {
			StaticVect<char,Taille> LH;									
			StaticVect<char,Taille> RH;			
			int posPAR; bool trouvPAR = false; int nbPAR = 0;
			int posAD; bool trouvAD = false;
			int posMU; bool trouvMU = false; 
			int pos = 0;
			if(exp[0]=='(') {
				while(!trouvPAR&&pos<exp.fin) {
					if(exp[pos]=='(') nbPAR++;	//G�re les parenth�ses imbriqu�es 
					if(exp[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
					pos++;
				} if(!trouvPAR) out("\n\nLa parenth�se n'est pas referm�e dans: "); out(exp); abort();
				if(trouvPAR&&pos==exp.fin) {exp = exp.intervalle(1,exp.longueur-1); trouvPAR = false; pos = 0;   //Supprimer la parenth�se et remettre les compteurs � 0, pour continuer		
				} else Lcompos = true;		//Noter l'expression � droite comme composite (car elle contient au minimum une parenth�se), et continuer � partir d'apr�s la parenth�se
			} else { 							
			//Cas g�n�ral : on cherche '+' ou '-', car '*' et '/' ont la priorit� d'op�ration
				while(!trouvAD&pos<exp.fin) {
					if(exp[pos]=='+'|exp[pos]=='-') {posAD = pos; trouvAD = true;}
					if(!trouvMU&&(exp[pos]=='*'|exp[pos]=='/')) {posMU = pos; trouvMU = true;}
					pos++;							
				}
				if(trouvAD) {
					operateur = exp[posAD]; 					
					LH = exp.intervalle(0,posAD);					//D�finir les limites de l'expression � gauche						
					RH = exp.intervalle(posAD+1,exp.longueur);		//D�finir les limites de l'expression � droite						
					if(trouvMU) Lcompos = true; //(car '*''/' ont la priorit� d'op�ration sur '+''-')
					while(!Rcompos&&pos<exp.fin) {if(exp[pos]=='+'|exp[pos]=='-'|exp[pos]=='*'|exp[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite
				} else if(trouvMU) {
					operateur = exp[posMU];  
					LH = exp.intervalle(0,posMU);					//D�finir les limites de l'expression � gauche						
					RH = exp.intervalle(posMU+1,exp.longueur);		//D�finir les limites de l'expression � droite
					pos = posMU + 1; while(!Rcompos&&pos<exp.fin) {if(exp[pos]=='*'|exp[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite				
				} else {
					operateur = ' '; LH = exp;   //Aucune op�ration, seulement une �valuation				
				}		
			}			
			//Assigner les valeurs aux membres
			if(Lcompos) {LHcompos = new intoper; LHcompos.set(LH,biblio); LHsimple = nullptr;} else {LHsimple = new inteval; LHsimple.set(LH,biblio); LHcompos = nullptr;}
			if(operateur!=' ') {if(Rcompos) {RHcompos = new intoper; RHcompos.set(RH,biblio); RHsimple = nullptr;} else {RHsimple = new inteval; RHsimple.set(RH,biblio); RHcompos = nullptr;}}
		}			
		//Fonction d'acc�s : eval()				
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


	//ix) classe : boolcompar ; contient les comparaisons d'expressions bool�ennes �valuables
	class boolcompar {
		//Valeurs membres
		public:
			char comparateur;      //Op�rateur de comparaison
			intoper* LH;
			intoper* RH;
			bool constbool;			   //TRUE si l'argument � gauche doit �tre compar� � un bool�en implicite
			bool boolval;		
		//Constructeur ;
		boolcompar () {}; //Constructeur par d�faut : vide. 
		template<int Taille>
		//Fonction de modification : set() ; permet de construire l'objet avec une expression
		void set(StaticVect<char,Taille>& exp, bibliotheque& biblio) : constbool(false), boolval(0) {
			if(exp.longueur==0) {comparateur = ' ';}        //Cas sp�cial: retourne TRUE automatiquement
			//Recueillir l'op�rateur			
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
				if(posEX==0) {constbool = true; boolval = false; comparateur = '=';	poscomparateur = exp.longueur; //Cas sp�cial r�chapp� de la fonction pr�c�dente (si jamais elle en laisse passer un)
				} else {poscomparateur = posEX;	comparateur = '!'; if(trouvEG&posEG!=posEX+1) erreur = true;}		//!=
			} else if(trouvPE) {poscomparateur = posPE; if(trouvEG&posEG==posPE+1) {comparateur = '�';    			//<=
				} else if(!trouvEG) comparateur = '<'; else erreur = true;											//<	
			} else if(trouvGR) {poscomparateur = posGR;	if(trouvEG&posGR==posGR+1) {comparateur = '�';   			//>=
				} else if(!trouvEG) comparateur = '>'; else erreur = true;											//>	
			} else if(trouvEG) {poscomparateur = posEG; if(exp[posEG+1]) comparateur = '='; else erreur = true;		//==	
			} else {constbool = true; boolval = true; comparateur = '=';	poscomparateur = exp.longueur;} //Cas sp�cial : "comparaison implicite de la valeur � true"
			//Message d'erreur
			if(erreur) {out("\n\nL'op�rateur n'est pas complet dans: "); for(int exppos = exp.debut; exppos<exp.fin; exppos++) {out(exp[exppos]);} abort();}
			//Cr�er les objets intoper
			LH = new intoper; LH.set(exp.intervalle(0,poscomparateur),biblio)
			if(!constbool){
				RH = new interoper;
				if(comparateur=='='||comparateur=='!'||comparateur=='�'||comparateur=='�') RH.set(exp.intervalle(poscomparateur+2,exp.longueur),biblio); else RH.set(exp.intervalle(poscomparateur+1,exp.longueur),biblio);	
			}			
		}
		//Fonction d'acc�s : eval
		bool eval(bibliotheque& biblio) {
			if(comparateur=='=') {
				if(constbool) return(LH->eval(biblio)==boolval); else return(LH->eval(biblio)==RH->eval(biblio));			// ==
			} else if(comparateur=='!') {LH->eval(biblio)!=RH->eval(biblio);												// !=
			} else if(comparateur=='<') {LH->eval(biblio)<RH->eval(biblio);												// <
			} else if(comparateur=='�') {LH->eval(biblio)<=RH->eval(biblio);												// <=
			} else if(comparateur=='<') {LH->eval(biblio)>RH->eval(biblio);												// >
			} else if(comparateur=='�') {LH->eval(biblio)>=RH->eval(biblio);												// >=
			}
		}
	};


	//x) classe : boolcompos ; permet de stoker des expressions bool�ennes �valuables; (LH = "left hand", � gauche ; RH = "Right hand", � droite)
	class boolcompos {
		//Valeurs membres
		public:
			char compositeur;   //'&' ou '|' ou '!' (==false) ou ' ' (==true, sans comparaison)
			boolcompar* LHsimple; boolcompos* LHcompos; 
			boolcompar* RHsimple; boolcompos* RHcompos;
			bool Lcompos; bool Rcompos;	
		//Constructeur
		boolcompos () {}; //Constructeur par d�faut : vide. 
		//Fonction de modification : set() ; permet de construire l'objet avec une expression		
		template<int Taille>		
		void set(StaticVect<char,Taille>& exp, bibliotheque& biblio) : Lcompos(false), Rcompos(false)	{    //false : valeurs par d�faut qui pourront changer � l'int�rieur du constructeur
			StaticVect<char,Taille> LH;
			StaticVect<char,Taille> RH;
			int posPAR; bool trouvPAR = false; int nbPAR = 0;
			int posOU; bool trouvOU = false; 
			int posET; bool trouvET = false;
			int pos = 0;
	        if(exp[0]=='!') {  
			//Cas sp�cial : compositeur '!'
	       		compositeur = '!'; 							//le (op�rateur + RH) deviennent : "==false" : r�gler ce cas particulier tout de suite
				while(!trouvOU&pos<exp.fin) {
					if(!trouvET&exp[pos]=='&') {posET = pos; trouvET = true;}
					if(!trouvOU&exp[pos]=='|') {posOU = pos; trouvOU = true;}		
					pos++;		
				}
				LH = exp.intervalle(1,exp.longueur);		//D�finir les limites de l'expression � gauche					
				if(trouvET|trouvOU) Lcompos = true;     //D�finir si LH est composiple
		    } else if(exp[0]=='(') {
				while(!trouvPAR&pos<exp.fin) {
					if(exp[pos]=='(') nbPAR++;	//G�re les parenth�ses imbriqu�es 
					if(exp[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
					pos++;
				} if(!trouvPAR) out("\n\nLa parenth�se n'est pas referm�e dans: "); out(exp); abort();
				if(trouvPAR&pos==exp.fin) {exp = exp.intervalle(1,exp.longueur-1); trouvPAR = false; pos = 0;   //Supprimer la parenth�se et remettre les compteurs � 0, pour continuer		
				} else Lcompos = true;		//Noter l'expression � droite comme composite (car elle contient au minimum une parenth�se), et continuer � partir d'apr�s la parenth�se
			} else { 							
			//Cas g�n�ral : on cherche '|', car '&' a la priorit� d'op�ration
				while(!trouvOU&pos<exp.fin) {
					if(exp[pos]=='|') {posOU = pos; trouvOU = true;}
					if(!trouvET&exp[pos]=='&') {posET = pos; trouvET = true;}
					pos++;							
				}
				if(trouvOU) {
					compositeur = '|';
					LH = exp.intervalle(0,posOU);					//D�finir les limites de l'expression � gauche						
					RH = exp.intervalle(posOU+1,exp.longueur);		//D�finir les limites de l'expression � droite						
					if(trouvET) Lcompos = true; //(car '&' a la priorit� d'op�ration sur '|')
					while(!Rcompos&pos<exp.fin) {if(exp[pos]=='&'|exp[pos]=='|') Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite
				} else if(trouvET) {  
					compositeur = '&';
					LH = exp.intervalle(0,posET);					//D�finir les limites de l'expression � gauche						
					RH = exp.intervalle(posET+1,exp.longueur);		//D�finir les limites de l'expression � droite
					pos = posET + 1; while(!Rcompos&pos<exp.fin) {if(exp[pos]=='&') Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite				
				} else {
					compositeur = ' '; StaticVect<char,Taille> LH = exp;   //Aucune comparaison, seulement une �valuation				
				}		
			}			
			//Assigner les valeurs aux membres
			if(Lcompos) {LHcompos = new boolcompos; LHcompos.set(LH,biblio); LHsimple = nullptr;} else {LHsimple = new boolcompar; LHsimple.set(LH,biblio); LHcompos = nullptr;}
			if(compositeur!='!'&&compositeur!=' ') {if(Rcompos) {RHcompos = new boolcompos; RHcompos.set(RH,biblio); RHsimple = nullptr;} else {RHsimple = new boolcompar; RHsimple.set(RH,biblio); RHcompos = nullptr;}}		
		}
		//Fonction d'acc�s : eval
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


//xi) classe : commande ; permet le stockage de "mots de passe" pour les commandes, � chercher dans le USERINPT
	class commande {
		//Valeurs membres
		public:
			static const int tailledifferentes = 5;
			static const int taillegroupes = 5;
			StaticVect<StaticVect<StaticVect<string,12>,taillegroupes>,tailledifferentes> inclus;		//Mots qui doivent �tre inclus dans l'expression
					//Niveau le plus ext�rieur: Diff�rentes fa�on de dire la commande (ex: manger le concombre / se nourrir / mastiquer) ... Genre?
					//Niveau m�dian: Diff�rents groupes de mots qui doivent �tre inclus (ex: manger / concombre)
					//Niveau le plus int�rieur: Diff�rents synonymes � l'int�rieur du groupe de mots (ex: manger/absorber/grignoter/engouffrer/avaler)
			StaticVect<StaticVect<string,4>,tailledifferentes> exclus;						//Mots qui doivent �tre absents de l'expression
					//Niveau le plus ext�rieur: Diff�rentes fa�on de dire la commande
					//Niveau le plus int�rieur: Diff�rents mots qui ne doivent pas se retrouver dans la commande
			StaticVect<string,5> exact;										//Expressions qui doivent exactement �tre recopi�es, sans faute (soit seule mani�re d'appeler, soit confirmation si ambiguit�; voir UserInputInterpret())
			bool ifexact;													//TRUE si une expression exacte est n�cessairement recherch�e
		//Constructeur
		commande() : ifexact(false) {};	
	};		
	
	
	//xii) classe : chainonauto ; permet le stockage du texte et des conditions d'apparition (automatique)
	class chainonauto {
		//Membres
		public:
			bool fini;		//OBSOL�TE? OU NON?
			StaticVect<string,10> maille;						//Texte � lire
			StaticVect<StaticVect<int,10>,10> enchainement;  	//int r�f�re aux positions des mailles         
			StaticVect<intoper,10> enchaineprob;        	 	//Avec le m�me ordre d'indexation que encha�nement
			boolcompos condition;								//Conditions � respecter pour l'ajout au canal sans UserInput 
			StaticVect<string,10> codespeciauxdebut;
			StaticVect<string,10> codespeciauxfin;
			StaticVect<int,10> override;						//Position d'indexation des canaux � overrider
			int canal;											//Position du canal dans lequel �crire le texte
		//Constructeur
		chainonauto() : fini(false) {};
	};
	
	//xii) classe : chainonmanu ; permet le stockage du texte et des conditions d'apparition (manuelle)
	class chainonmanu {
		//Membres
		public:
			bool fini;		//OBSOL�TE? OU NON?
			StaticVect<string,10> maille;						//Texte � lire
			StaticVect<StaticVect<int,10>,10> enchainement;  	//int r�f�re aux positions des mailles         
			StaticVect<intoper,10> enchaineprob;        	 	//Avec le m�me ordre d'indexation que encha�nement
			boolcompos condition;								//Conditions � respecter pour l'ajout au canal avec UserInput				
			string codespeciauxdebut;
			string codespeciauxfin;
			StaticVect<int,10> override;						//Position d'indexation des canaux � overrider
			int canal;											//Position du canal dans lequel �crire le texte
			commande commandes;                					//Mots � rechercher pour l'ajout au canal � partir du UserInput			
			bool getbusy;                                       //TRUE si le UserInput devient bloqu� apr�s que ce cha�non ait �t� appel�
		//Constructeur
		chainonmanu() : fini(false), getbusy(true) {};	
	};
	
	//xiii) classe : fil ; permet de stocker toutes les textes + commandes selon des cat�gories (ex: chapitres), pour faciliter la recherche
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
//4) Fonction sp�cialis�es de petite taille

	//i) Fonction : CodeSpecialLong ; retourne la longueur d'un code sp�cial ('�' compris)
	int CodeSpecialLongueur(const StringAsVect& str){
		int longueur = 1;               //Initier l'objet � retourner
		bool fini = false;              
		for(int pos = str.debut + 1; !fini&pos<str.fin ; pos++) {longueur++; if(str.pt[pos]=='�') fini = true;} 		
		return(longueur);		
	}

	//ii) Fonction : CodeSpecialExtract ; extrait une valeur num�rique d'une suite de caract�res encadr�s par '�' (pour extraire les codes sp�ciaux)
	double CodeSpecialExtractDouble(const StringAsVect& str, int longueur){
		string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres (2X'�' + 1 identifiant en char)
		int longmax = longueur - 1 + str.debut;      //Le dernier caract�re �tant le '�'		
		for(int pos=2+str.debut; pos<longmax; pos++) nbonly += str.pt[pos];    //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire (identifiant en char)	
		return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}		
	int CodeSpecialExtractInt(const StringAsVect& str, int longueur){
		string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres (2X'�' + 1 identifiant en char)
		int longmax = longueur - 1;      //Le dernier caract�re �tant le '�'
		int nbonlypos = 0; for(int pos=2; pos<longmax; pos++) nbonly[nbonlypos++] += str.pt[pos];    //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire (identifiant en char)
		return(stoi(nbonly));           //La fonction stoi convertit les strings en int (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}		

	//iii) Fonction : UserInputEcho ; validant graphiquement l'acceptation ou le refus des commandes envoy�es
	void UserInputEcho(input& inp, inputecho& inpecho, const fen& base) {	
		chgcol(inpecho.couleur);
		//Clignoter
		if(inpecho.clignote[0]>0){
			curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
		} else {
			curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(' ');			
		}
		chgcol(base.couleur);                       //Revenir � la couleur de base	
		inpecho.nxtt += abs(inpecho.clignote[0]);        //Updater le "next time"
		inpecho.clignote.suppression(1);            //Passer � la prochaine instruction
		if(inpecho.clignote.debut==inpecho.clignote.fin) inpecho.actif = false;			//V�rifier s'il reste toujours du stock � passer dans le canal	
		}	
	
	//iv) Fonction : pause ; arr�te les compteurs des canaux
	void pause(StaticVect<canal,taillecanal>& canaux) {
		int currentt = timems();
		for(int poscan=0; poscan<canaux.longueur; poscan++) canaux[poscan].pausedt = canaux[poscan].nxtt - currentt;			
	}
	void unpause(StaticVect<canal,taillecanal>& canaux) {
		int currentt = timems();
		for(int poscan=0; poscan<canaux.longueur; poscan++) canaux[poscan].nxtt = currentt + canaux[poscan].pausedt + canaux[poscan].delay * 5;					
	}
	
	//vi) Fonction : integration ; ajoute un chainon � un canal
	void integration(int chapitrepos, int chainonpos, StaticVect<canal,taillecanal>& canaux, fil& histoire, bibliotheque& biblio) {
		//Overloader les canaux
		int currentt = timems();		
		for(int posover=0; posover<histoire.chainemanu[chapitrepos][chainonpos].override.longueur; posover++) {    //Pour chaque canaux � overloader
			canaux[histoire.chainemanu[chapitrepos][chainonpos].override[posover]].nxtt = currentt + canaux[histoire.chainemanu[chapitrepos][chainonpos].override[posover]].delay * 5;
			canaux[histoire.chainemanu[chapitrepos][chainonpos].override[posover]].txt.vide();
		}
		//Choisir l'encha�nement � ins�rer dans le canal
		int sumprob = 0; StaticVect<int,10> vectprob;
		for(int posprob=0; posprob<histoire.chainemanu[chapitrepos][chainonpos].enchaineprob.longueur; posprob++) {	//�valuer chaque probabilit�
			sumprob += histoire.chainemanu[chapitrepos][chainonpos].enchaineprob[posprob].eval(biblio); vectprob[posprob] = sumprob; 
		}
		int randval = rand() % sumprob;  //Obtenir une valeur al�atoire entre [0,sumprob[
		int choix; 
		for(int posprob=0; posprob<histoire.chainemanu[chapitrepos][chainonpos].enchaineprob.longueur; posprob++) {
			if(randval<vectprob[posprob]) {choix = posprob; break;}
		}	
		//Ajouter le texte au canal
		canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].txt.ajout(histoire.chainemanu[chapitrepos][chainonpos].codespeciauxdebut); 
		for(int posench=0; posench<histoire.chainemanu[chapitrepos][chainonpos].enchainement[choix].longueur; posench++) {
			canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].txt.ajout(histoire.chainemanu[chapitrepos][chainonpos].maille[histoire.chainemanu[chapitrepos][chainonpos].enchainement[choix][posench]]);
		}		
		canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].txt.ajout(histoire.chainemanu[chapitrepos][chainonpos].codespeciauxfin);		
	}
	
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//5) Fonction LireCanal()
void LireCanal(StaticVect<canal,taillecanal>& canaux, int canpos, fen& base, memoire& mem) {
	//Updater le "next time"
	canaux[canpos].nxtt += canaux[canpos].delay;
	//Interpr�ter les "codes sp�ciaux" (�...�)
	if(canaux[canpos].txt[0]=='�'){		
		//D�terminer la longueur du code sp�cial
			int CodeSpecialLong = CodeSpecialLongueur(canaux[canpos].txt);			
		//Lire le code sp�cial		
			if(canaux[canpos].txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause � la lecture		
				double val = CodeSpecialExtractDouble(canaux[canpos].txt,CodeSpecialLong);       //Extraire le temps que durera la pause
				canaux[canpos].nxtt += round(val * canaux[canpos].vit);                    //Ajouter le temps d'attente        //round() est n�cessaire pour arrondir correctement					
			} else if(canaux[canpos].txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = CodeSpecialExtractDouble(canaux[canpos].txt,CodeSpecialLong);       //Extraire la nouvelle vitesse
				canaux[canpos].vit = val;
			} else if(canaux[canpos].txt[1]=='g'){		//'g' pour "gender" -> choisir le bon accord
																								 //S�lectionner le genre
				int genreselect;
				int genreactuel = 0; 
				
				
				//TENTATIVE POUR L'�CRIRE AVEC LA FONCTION supprpos (ou quelque chose comme �a) (FONCTION IMPORT�E DE "StaticVect")
						//INCONV�NIENTS: 
								//FORCE LE PROGRAMME � R��CRIRE L'OBJET ENTIER � CHAQUE FOIS (car c'est ce que fait supprpos())
				bool genrepasse = false; bool suppress = false;																				 
				for(int posSpecial=3;posSpecial<CodeSpecialLong; posSpecial++) {				 //Conserver le bon accord	
					if(canaux[canpos].txt[posSpecial]==';') {genreactuel++; suppress = true;
					} else {
						if(genreactuel==genreselect) {if(!genrepasse) genrepasse = true; } else suppress = true;
					}
					if(suppress) {
						if(!genrepasse) canaux[canpos].txt.suppression(1); else canaux[canpos].txt.supprespos(pos)				
					}	
				}
				
				
				
				//TENTATIVE	POUR L'�CRIRE AVEC LA FONCTION intervalle() (FONCTION IMPORT�E DE "StaticVect")
				int posdebut = 3; int posfin = CoeSpecialLongueur - 1;		//Valeurs par d�fauts
				for(int posSpecial=3;posSpecial<CodeSpecialLong; posSpecial++) {				 //D�limiter le bon accord				
					if(canaux[canpos].txt[posSpecial]==';') {
						genreactuel++;
						if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect-1) posfin = posSpecial - 1;
					}
				}
				StringAsVect tempcan = new StringAsVect;										//Ajouter le bon accord � la suite du code sp�cial (devient: Code sp�cial - accord - reste du canal
				tempcan.ajout(canaux[canpos].txt.intervalle(0,CodeSpecialLong)); tempcan.ajout(canaux[canpos].txt.intervalle(posdebut,posfin)); tempcan.ajout(canaux[canpos].txt.intervalle(CodeSpecialLong,canaux[canpos].txt.longueur));				
				canaux[canpos].txt.remplacement(tempcan); delete tempcan;
				canaux[canpos].nxtt -= canaux[canpos].delay;									//Ajuster le "next time" pour supprimer le d�lai entre l'interpr�tation du code et la lecture de l'accord
			}								
														
		
		
					//Faudrait l'ajouter + ajuster � StringAsVect!		 (c'est pas encore fait, malheureusement)										
	//Fonction d'acc�s : intervalle()
		StaticVect<Type,Taille> intervalle(int posdebut, int posfin) {
			if(posfin <= longueur) {
				StaticVect<Type,Taille> returnvect;
				returnvect.debut = 0; returnvect.longueur = posfin - posdebut; returnvect.fin = returnvect.longueur;
				int returnpos = 0; for(int pos = posdebut; pos<posfin; pos++) {returnvect.pt[returnpos++] = pt[pos+debut];}
				return(returnvect);				
			} else {std::wcout<<"intervalle() de "; std::wcout<<posdebut; std::wcout<<" � "; std::wcout<<posfin; std::wcout<<" dans \""; for(int pos=0; pos<fin; pos++) std::wcout<<pt[pos+debut]; std::wcout<<"\", d�passant donc la longueur"; abort();}
		}														
														
					//Faudrait aussi l'ajouter � StringAsVect        (pas fait)
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
		
					//Ishhhhh... Ce serait vraiment plus simple de simplement remplacer StringAsVect par un StaticVect. Vraiment plus simple.
							//Parce qu'elles sont rendues � avoir EXACTEMENT les m�mes fonctions, maintenant. What a joke.
								//Pis, bon. Pas besoin d'avoir une capacit� super variable si on lib�re d�s le d�but assez de place dans la m�moire.
										//Genre... 1 000 caract�res par canal? Serait-ce r�aliste?
											//Est-ce que l'�criture serait vraiment limit�e par ce nombre?
													//**Garder en t�te en passant que ce n'est pas le nombre max de caract d'un cha�non, mais bien
														//de ce qu'il y a d�j� dans le canal + le cha�non.		
					
														
														
			}  //EN AJOUTER UN (code sp�cial) POUR PLACER LE CURSEUR � LA FIN DE LA CONSOLE	
			
			
			
		//Effacer le code sp�cial du canal
		canaux[canpos].txt.suppression(CodeSpecialLong);
		
		
		
	} else {  //Interpr�ter le reste des caract�res (pas des codes sp�ciaux)
		//Dealer avec la situation o� on a � sauter une ligne (cr�er les lignes suppl�mentaires et updater les diverses positions)
			bool jump = false;
			if(canaux[canpos].txt[0]=='\n'|canaux[canpos].posx>=base.limtxtx-1) jump = true;     //base.limtxtx - 1 ; car c'est en integer, et canaux[canpos].posx commence � 0!
			if(jump) {	
				mem.newline(canaux[canpos].posy);                     //Introduit une nouvelle ligne � la suite de la position qui lui est fournie	
				//Updater le correctif de d�calage de la console par rapport � la m�moire
					if(base.refoule) base.consy++; else if(mem.frontline>base.limtxty) {base.refoule = true; base.consy++;} 						
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore satur�e: on pousse vers le bas!
						if(canaux[canpos].posy!=mem.frontline-1) {                             //S'il y a d'autres lignes � repousser vers le bas
							//R�-�crire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,canaux[canpos].posy+1);  //Mettre le curseur au d�but de la reconstruction
								for(int county = canaux[canpos].posy + 1 ; county <= mem.frontline ; county++) {   
									for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est satur�e: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")
							curspos(0,canaux[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
						//Tout r�-�crire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county <= canaux[canpos].posy; county++){             //base.consy : facteur de d�calage de la console
								for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}	
				//Updater les positions dans les autres canaux    //Parce que leur position dans la m�moire a boug� //la position dans la console est quant � elle g�r�e par base.consy
				for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {
					if(countcan==canpos) continue;                                    //la m�moire refoule toujours vers le bas!
					if(canaux[countcan].posy > canaux[canpos].posy) canaux[countcan].posy++; else if(canaux[countcan].posy == canaux[canpos].posy) canaux[countcan].posy+=2;
				}       // == : Si deux canaux se situe sur la m�me ligne, le canal qui change de ligne va couper l'autre en deux, et le renvoyer apr�s sa propre ligne.    	        
				//Updater les positions dans le canal actuel
				if(canaux[canpos].txt[0]=='\n') {canaux[canpos].posx = -1;} else canaux[canpos].posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
				canaux[canpos].posy++;	  																					   //en y 		
			} else {canaux[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du charact�re actuel (dans la m�moire)!		
		if(canaux[canpos].txt[0]!='\n') {
			curspos(canaux[canpos].posx,canaux[canpos].posy-base.consy) ; out(canaux[canpos].txt[0]);     //Inscrire dans la console
			mem.souvenir[canaux[canpos].posx][canaux[canpos].posy] = canaux[canpos].txt[0];   //Inscrire dans la m�moire			
		}	
		canaux[canpos].txt.suppression(1);       //Effacer le caract�re du canal     	   
	}
	if(canaux[canpos].txt.debut==canaux[canpos].txt.fin) canaux[canpos].actif = false;			//V�rifier s'il reste toujours du texte � passer dans le canal
}	
					
          
         
//------------------------------------------------------------------------------------------------------------------------------------------------------
//6) Fonction : UserInputInterpret ; v�rifie si la commande entr�e correspond � une des actions actuellement autoris�e
	template<int Taille>
	void UserInputInterpret(StaticVect<char,Taille>& command, StaticVect<canal,taillecanal> canaux, bibliotheque& biblio, fil& histoire, const fen& base, input& inp, memoire& mem) {
		//

			//ID�E:
			//		PEUT-�TRE INCLURE DIRECTEMENT DANS L'�VALUATION LA MISE EN MAJUSCULE AUTOMATIQUE DU PREMIER MOT?
			//		POUR NE PAS PRENDRE TROP DE PLACE DANS LA M�MOIRE...? MAIS EN M�ME TEMPS, LE TOTAL N'EST PAS DRAMATIQUE... MAIS �A ME PERMETTRAIT DE NE PAS M'EN SOUCIER. VENDU.
			//		
			
					//CE N'EST PAS ENCORE FAIT!!! IL SERAIT IMPORTANT DE L'INT�GRER!!!
			
			
			
		//Cr�er des compteurs
		StaticVect<int,histoire.taille> bonchapitre;	  //Cr�er des StaticVect pour noter la position des chainons qui correspondent � la commande
		StaticVect<int,histoire.taillechapitre> bonchainon;
		StaticVect<bool,taillegroupes> groupebon; 	   	 //Cr�er un StaticVect pour noter si chaque groupe de mot est bon
		int diffpos; bool exactbon; int commpos; bool exactmauvais; 	//Cr�er les compteurs pour les expressions exactes
		int groupepos; int synpos; int motpos; int precedpos; bool inclusbon; bool exclusbon;	//Cr�er les compteurs pour les mots � inclure/exclure	
		//Pour chaque chapitre
		for(int chapitrepos=0; chapitrepos<histoire.taille; chapitrepos++) { if(histoire.cadenas[chapitrepos].eval(biblio)) {			
			//Pour chaque chainon dans l'histoire
			for(int chainonpos=0; chainonpos<histoire.chainemanu[chapitrepos].longueur; chainonpos++) {if(histoire.chainemanu[chapitrepos][chainonpos].condition.eval(biblio)) {
				if(histoire.chainemanu[chapitrepos][chainonpos].commandes.ifexact) {	//Si une commande exacte est n�cessaire
					diffpos = 0; exactbon = false;
					while(diffpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.exact.longueur&&!exactbon) {
						commpos = 0; exactmauvais = false;
						while(!exactmauvais&&commpos<command.longueur) {if(command[commpos]!=histoire.chainemanu[chapitrepos][chainonpos].commandes.exact[diffpos][commpos]) exactmauvais = true; else commpos++;}	
						if(exactmauvais==false) exactbon = true; else diffpos++;
					}
					if(exactbon)	{integration(chapitrepos,chainonpos,canaux,histoire,biblio); return;}            //Int�grer tout de suite le bon cha�non dans le canal					
				} else {								//Si plusieurs mots cl�s doivent �tre pr�sents
					inclusbon = false; diffpos = 0;
					//Pour chaque fa�on diff�rente de dire la commande
					while(diffpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus.longueur&&!inclusbon) {
						//V�rifier si les mots � �tre inclus sont pr�sents
							groupepos = 0;  precedpos = 0;   														//Remettre tous les groupes de mots comme incorrects jusqu'� preuve du contraire
							groupebon.remplacement(false); for(int clearpos=1; clearpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos].longueur; clearpos++) groupebon.ajout(false); 
							//Pour chaque groupe de mots
							while(groupepos<histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos].longueur) {    
								synpos=0;
								//Pour chaque synonyme
								while(synpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos][groupepos].longueur&&!groupebon[groupepos]) {		
									commpos = precedpos;
									motpos = 0;
									//Pour chaque lettre
									while(commpos<command.longueur&&!groupebon[groupepos]) {																					
										if(command[commpos++]==histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos][groupepos][synpos][motpos++]) {
											if(motpos==histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos][groupepos][synpos].length()) {groupebon[groupepos] = true; precedpos = commpos;}
										} else motpos = 0;
									}
								}					
							}	
							//Maintenant, on a l'information sur quel groupe de mots, dans l'intervalle [0,longueur_de_cette_differente_fa�on], a un membre qui est pr�sent dans la commande.
							groupepos=0 ; while(groupebon[groupepos++]) if(groupepos==histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos].longueur) inclusbon = true;
						//V�rifier si les mots � �tre exclus sont absents
						if(inclusbon) {
							synpos=0; exclusbon = true;
							//Pour chaque synonyme
							while(synpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.exclus[diffpos].longueur&&exclusbon) {
								commpos = 0;
								motpos = 0;
								//Pour chaque lettre
								while(commpos<command.longueur&&exclusbon) {		//Si le mot est retrouv�, la commande ne correspond pas au cha�non																			
									if(command[commpos++]==histoire.chainemanu[chapitrepos][chainonpos].commandes.exclus[diffpos][synpos][motpos++]) {
										if(motpos==histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos][synpos].longueur) exclusbon = false;	
									} else motpos = 0;
								}
							}
						}
					}
					if(inclusbon&&exclusbon) {bonchapitre.ajout(chapitrepos); bonchainon.ajout(chainonpos);}
				}		
			}}
		}}
		//Maintenant, on a l'information sur quels cha�nons correspondent (sans expression exacte) � la commande
		if(bonchainon.longueur==0) {
			inp.accepted = false; return;
		} else if(bonchainon.longueur==1) {
			inp.accepted = true; if(histoire.chainemanu[bonchapitre[0]][bonchainon[0]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input					
			integration(bonchapitre[0],bonchainon[0],canaux,histoire,biblio); return;            //Int�grer le bon cha�non dans le canal
		} else {
			//D�terminer si la commande correspond � une expression exacte
			int bonpos = 0; exactbon = false; 
			while(bonpos<bonchainon.longueur&&!exactbon) {
				exactmauvais = false; commpos = 0;
					while(!exactmauvais&&commpos<command.longueur) {if(command[commpos]!=histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0][commpos]) exactmauvais = true; else commpos++;}	
					if(exactmauvais==false) {
						exactbon = true; 	
						inp.accepted = true; if(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].getbusy) inp.busy = true;							
						integration(bonchapitre[bonpos],bonchainon[bonpos],canaux,histoire,biblio); return;}            //Int�grer tout de suite le bon cha�non dans le canal	
			}	
			//Si l'ambiguit� demeure: mettre le jeu sur pause, et faire appara�tre les options	
			pause(canaux);
			chgcol("gris sombre"); curspos(0,0);		//Recopier tout le texte affich� dans la console, mais en gris fonc� (background)
			for(int county = base.consy ; county <= mem.frontline ; county++) {   
				for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
			}			
			chgcol("blanc"); curspos(5,3); int cursorposy = 3;
			egrener("Vouliez-vous dire (recopiez la ligne qui correspond � votre choix) :",160);
			for(int bonpos=0; bonpos<bonchainon.longueur; bonpos++) {
				if(bonpos==bonchainon.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy); egrener("ou",120);}}
				cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy);; egrener(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0],120);}
				if(bonpos==bonchainon.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy); egrener("              ?",120);}}				
			}
			string reformulation;
			cin >> reformulation;
				//V�rifier de nouveau
				bonpos = 0; exactbon = false; 
				while(bonpos<bonchainon.longueur&&!exactbon) {
					exactmauvais = false; commpos = 0;
						while(!exactmauvais&&commpos<reformulation.length()) {if(reformulation[commpos]!=histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0][commpos]) exactmauvais = true; else commpos++;}	
						if(exactmauvais==false) {
							exactbon = true; 
							curspos(3,0); chgcol("gris sombre"); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][base.consy + 3]); chgcol("blanc");
							stop(800);
							curspos(3,2); egrener("Parfait.",220);		
							stop(1500);
							curspos(0,0); for(int county = base.consy ; county <= mem.frontline ; county++) {for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);}			
							unpause(canaux);
							inp.accepted = true; if(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input							
							integration(bonchapitre[bonpos],bonchainon[bonpos],canaux,histoire,biblio); return;}            //Int�grer tout de suite le bon cha�non dans le canal	
				}				
			//Si l'ambiguit� persiste: le demander une derni�re fois
			curspos(3,0); chgcol("gris sombre"); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][base.consy + 3]); chgcol("blanc");
			curspos(3,3); egrener("Vouliez-vous dire (recopiez EXACTEMENT la ligne qui correspond � votre choix) :",200);
			cin >> reformulation;	
				//V�rifier de nouveau
				bonpos = 0; exactbon = false; 
				while(bonpos<bonchainon.longueur&&!exactbon) {
					exactmauvais = false; commpos = 0;
						while(!exactmauvais&&commpos<reformulation.length()) {if(reformulation[commpos]!=histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0][commpos]) exactmauvais = true; else commpos++;}	
						if(exactmauvais==false) {
							exactbon = true; 
							curspos(3,0); chgcol("gris sombre"); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][base.consy + 3]); chgcol("blanc");
							stop(800);
							curspos(3,2); egrener("C'est bon.",220);		
							stop(1500);
							curspos(0,0); for(int county = base.consy ; county <= mem.frontline ; county++) {for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);}			
							unpause(canaux);
							inp.accepted = true; if(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input
							integration(bonchapitre[bonpos],bonchainon[bonpos],canaux,histoire,biblio); return;}            //Int�grer tout de suite le bon cha�non dans le canal	
				}				
			//Si l'ambiguit� est insolvable
			curspos(3,0); chgcol("gris sombre"); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][base.consy + 3]); chgcol("blanc");
			stop(800);
			curspos(3,4); egrener("Ce n'est toujours pas clair.   Too bad.",240);			
			stop(3000);
			curspos(0,0); for(int county = base.consy ; county <= mem.frontline ; county++) {for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);}			
			unpause(canaux);
			inp.accepted = false; return;				
		}
	}        


//------------------------------------------------------------------------------------------------------------------------------------------------------
//7) Fonction UserInput()
void UserInput(input& inp, inputecho& inpecho, const fen& base, bibliotheque& biblio, StaticVect<canal,taillecanal>& canaux, fil& histoire, memoire mem) {
	if(_kbhit()){
	//i) Capter la lettre tap�e
	bool enter = false;
	char key = _getch();                  		//Enregistrer quelle touche a �t� press�e
			if (key == 0 || key == -32 || key == 224) {      //La valeur est sp�ciale: elle n�cessite de la r�-examiner
				key = _getch();                              //Examiner une deuxi�me valeur pour identifier
				if(key == 75) {     								 				 //fl�che gauche : reculer dans la commande tap�e 
					if(inp.inputpos!=0) {
						if(inp.inputpos!=inp.commande.longueur) {
							curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						}          //Remettre en gris la position pr�c�dente
						inp.inputpos--;  
					}
				}
				else if (key == 77) {											 	 //fl�che droite : avancer dans la commande tap�e				
					if(inp.inputpos!=inp.commande.longueur) {
						curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						inp.inputpos++;		
					}			//Remettre en gris la position pr�c�dente
				} 
				else if (key == 72)  ;  											 //Fl�che du haut   ... Rien ne se passe?
				else if (key == 80)  ;  											 //Fl�che du bas    ... Rien ne se passe?
				else if (key == 83) {                                                //Delete : supprimer un caract�re de la commande actuelle
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
					curspos(0,base.limtxty); out("Vous avez entr� ESC, le programme se ferme donc."); abort(); 
				} else if(key == 13) {												 //Enter : envoyer la commande
					enter = true;
				} else if(key == 8) {                                                //Backspace : supprimer le caract�re pr�c�dent
					if(inp.inputpos!=0) {
						inp.inputpos--;
						inp.commande.supprposition(inp.inputpos);   
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);   
						out(' ');    					
					}
					///////////////ICI, JE G�RE LES ACCENTS MANUELLEMENT, COMME ILS SEMBLENT POSER PROBL�ME!
					//NE MARCHE M�ME PAS, CAR M�ME LE CODE NUM�RIQUE NE SEMBLE PAS �TRE RECONNU!!!
					
				} else if(key==183) {key = '�'; cout << "test";} else if(key==133) {key = '�'; cout << "test";} else if(key==128) {key = '�'; cout << "test";} else if(key==135) {key = '�'; cout << "test";
				} else if(key==144) {key = '�'; cout << "test";} else if(key==130) {key = '�'; cout << "test";} else if(key==212) {key = '�'; cout << "test";} else if(key==138) {key = '�'; cout << "test";
				} else if(key==210) {key = '�'; cout << "test";} else if(key==136) {key = '�'; cout << "test";} else if(key==215) {key = '�'; cout << "test";} else if(key==140) {key = '�'; cout << "test";
				} else if(key==216) {key = '�'; cout << "test";} else if(key==139) {key = '�'; cout << "test";} else if(key==226) {key = '�'; cout << "test";} else if(key==147) {key = '�'; cout << "test";
				} else if(key==235) {key = '�'; cout << "test";} else if(key==151) {key = '�'; cout << "test";} else if(key==234) {key = '�'; cout << "test";} else if(key==150) {key = '�'; cout << "test";
				} else {															 //Caract�re normal : l'ajouter � la commande	
					if(inp.commande.longueur<base.limtxtx-1){
						inp.commande.ajout(key,inp.inputpos);
						inp.inputpos++;
						curspos(inp.inputpos-1,base.limtxty);	                    
						for(int pos=inp.inputpos-1; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);
						if(inp.commande.longueur==inpecho.commande.fin) inpecho.actif = false;                   //D�sactiver le canal d'�cho si la commande actuelle le d�passe
					}
						
								//BTW: FAUDRAIT AUSSI TOUT UN PAN DE CODE POUR G�RER LES COMMANDES TROP LONGUES, POUR FAIRE RECULER LE TEXTE
										//Pour l'instant, je restreint l'espace � la largeur de la console, simplement.
							
				}
			}	
		//Remettre la lettre s�lectionn�e en surbrillance
		if(inp.inputpos!=inp.commande.longueur) {chgcol("blanc"); curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); chgcol(base.couleur);}
			
		//�valuer la commande		
		if(enter) {								//BTW: Faire changer la vitesse/fr�n�sie du clignotage avec la vitesse globale. Tu veux �a plus vite? �a va �tre plus agressant aussi!
			UserInputInterpret(inp.commande,canaux,biblio,histoire,base,inp,mem);
							//FAIRE UNE FONCTION � PART POUR �VALUER LA CORRESPONDANCE DE LA COMMANDE AVEC LES POSSIBILIT�S;
														//ICI, SIMPLEMENT S'OCCUPER DE L'AFFICHAGE (EFFETS GRAPHIQUES DIFF�RENTS SI C'EST ACCEPT� OU NON...)!														
			inpecho.commande.remplacement(inp.commande);						
			inpecho.actif = true; inpecho.nxtt = timems();          							 //Mettre � l'heure le "nexttime"											
			if(inp.accepted) {
				if(inp.busy) {			//Conserver le texte en place, en plus p�le, pendant quelques secondes. Peut �tre effac� progressivement par une nouvelle commande
					inpecho.couleur = "gris sombre";
					int clignarr [2] {3000,-1};
					inpecho.clignote.remplacement(clignarr, 2);
				} else {				//Faire clignoter le texte, en plus p�le, pendant quelques secondes.
					inpecho.couleur = "gris sombre";
					int clignarr [6] {500,-500,500,-500,500,-1};
					inpecho.clignote.remplacement(clignarr, 6);
				}                				
			} else{						//Faire clignoter le texte, en rouge fonc�, pendant quelques secondes.
				
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

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
	//x, y, width, height,
	fen base(600,30,500,500);                                           //Cr�e �galement l'objet dans lequel ces param�tres sont d�finis
	
	//Cr�er l'objet de m�moire, qui stockera tous les caract�res utilis�s
	memoire mem {base.limtxtx};

	//Cr�er les objets d'input
	input entree; inputecho entreeecho;

	//Cr�er la biblioth�que
	bibliotheque biblio;
	
	//Cr�er le fil
	fil histoire;
	
	//Cr�er un chainon
	chainonmanu test;															//Cr�er l'objet avant de l'int�grer?
	//�crire les param�tres du cha�non 
	test.canal = 0;
					//test.commandes.inclus[0][0][0].ajout("bonjour");    //Non, on ne peut pas faire cela...? Car il faudrait d'abord .ajout les premiers niveaux?
							//Oui, non?
							
					//Eurgh. Comment faire pour g�rer les StaticVect imbriqu�s?					
	//Th�oriquement, faudrait faire un .ajout() manuel de chaque objet;
			//quoique?
		//Quand on cr�e un StaticVect, �a alloue un espace X dans la m�moire.
		//Pour des types simples (int), quand la valeur n'a pas �t� sp�cifi�e, la position retourne N'IMPORTE QUOI (al�atoire, un peu?)
		//Pour des types plus complexes, qui demandent des constructeurs... 
				//Est-ce que les constructeurs par d�faut sont call�s quand on cr�e un array???
						//Mon intuition est: probablement.
		
		//Si l'objet existe officiellement, on aurait pas besoin de l'inition � chaque fois; on aurait seulement qu'� updater fin et longueur de toute la chaine.
			//Ce serait l'id�al.		//Faudrait faire un script test pour voir si c'est le cas.
			
			//Avec �a, j'aurais seulement � faire une fonction maison dans la classe "commande" , avec quatre arguments : trois int de position, et un string.
			
			//Ou mieux encore: faire mon esp�ce de r�ve/espoir:  mettre un autre syst�me de parsing (cette fois compl�tement s�quentiel, c'est-�-dire sans priorit� d'op�ration) :
					//ex : ( Bonjour | Hello | Salut & World | Monde ) (Test)
							// () = diff�rentes fa�ons de le dire ;  & = diff�rents blocs de mots ; | = synonymes
							
					//Ouin. �a serait simplement la meilleure chose � faire.
						//Ce serait tout de m�me plus simple � coder si les StaticVect �taient d�j� construits. Donc faire le test tout de m�me.		
							
	
						
	//Pour mettre les mailles...
									//Faudrait aussi tester si on peut �crire un array en argument, genre test.maille.ajout({"1","2","3","4"},4)  .
										//Ce serait la meilleure chose, je crois.
										//Non. Pas vrai. La meilleure chose serait encore un parsing mechanism.
										
	//Pour les conditions, 
			//le probl�me c'est que, comme c'est l�, boolcompos prend juste des StaticVect � taille d�finie.
				//Donc faudrait une fonction maison pour transformer un string qu'on lui donne en un StaticVect d'une taille d�finie.
				
	
	//En bref, il vaudrait mieux � peu pr�s tout transformer en fonctions maisons, la plupart avec des �l�ments de "parsing" (interpr�tation d'un string).
	
		//� la place de mettre ces fonctions comme fonctions de classes sp�cifiques,
							//je pr�f�re mettre comme argument le cha�non. Et va falloir tout dupliquer pour auto / manu (overrider).

	//J'aurais donc (en supposant que le chainon existe d�j�) :
	
	/*
	int chapitre = 0;
	int posmanu = 0;
	
	texte(histoire.chainemanu[chapitre][posmanu],"LaLaLaLaLa\nlala � lulululu")       ici, ' � ' sert de s�parateur (pour l'exemple)
	enchainement(histoire.chainemanu[chapitre][posmanu],"1-2;1;2")              '-' pour signifier un autre �l�ment, ';' pour signifier un autre encha�nement 
	probabilites(histoire.chainemanu[chapitre][posmanu],"comptes�bobon*5;2;3")		';' pour signifier un autre encha�nement																	
	commande(histoire.chainemanu[chapitre][posmanu],"(Bonjour|Hello|Salut & World|Monde) (Test)")
	condition(histoire.chainemanu[chapitre][posmanu],"comptes�bonbon<=3")
	override(histoire.chainemanu[chapitre][posmanu],"0,1")
	
			//Ishhh. L'option d'une fonction externe rend �a difficilement lisible. J'aimerais mieux :
					// ex :  histoire.chainemanu[chapitre][posmanu].    texte("LaLaLaLaLa\nlala � lulululu")   (les espaces ne comptent pas, right?)
	
	
	histoire.chainemanu[chapitre][posmanu].canal = 1;
	histoire.chainemanu[chapitre][posmanu].codespeciauxdebut = "";
	histoire.chainemanu[chapitre][posmanu].codespeciauxfin = "";
	histoire.chainemanu[chapitre][posmanu].getbusy = true;
	
						//Mhhph. Pour garder l'esth�tique, je pense que je pr�f�re utiliser seulement des fonctions. Pour que tout soit align�.
								//Donc faire comme en haut, m�me pour cette partie.
	
	*/		
	
	
	//Cr�er les canaux utilis�s
	canal can1;
	canal can2;
	
	//Test: changer les d�lais manuellement
	can1.delay = 140;
	can2.delay = 230;
	
	//Ajouter du texte aux canaux
	string txt0 = "Cel� est du texte!\nJe dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	string txt1 = "�p1000�\nLe canal 1 \n           est sooooo boring. Ark.�p1000�\n�p1000�Je suis le canal 2.";
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
			if(canaux[0].actif&canaux[0].nxtt<currentt) LireCanal(canaux,0,base,mem);
			if(canaux[1].actif&canaux[1].nxtt<currentt) LireCanal(canaux,1,base,mem);
			UserInput(entree,entreeecho,base,biblio,canaux,histoire,mem);                   //Reste � cr�er ces objets!!!!
			
			if(entreeecho.actif&entreeecho.nxtt<currentt) {UserInputEcho(entree,entreeecho,base);}
			
			//if(!canaux[0].actif&!canaux[1].actif) gogogo = false;
		}		
		
	curspos(0,13);


}								
