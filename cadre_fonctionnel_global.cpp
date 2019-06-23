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
				
				
				
				En plus:
						Je n'arrive pas à bien remplacement() les staticvect contenus dans input et inputecho,
						à partir d'autres staticvect.
						
						Hors de ces classes, pourtant, ça marche.
						Hors de la fonction d'écriture, même, ça semble marcher.
						Est-ce que ça a à voir avec le type d'argument?
				
*/

/*
	2019-06-22:
				En passant: Quand on active un canal, ou qu'on le reset, va falloir resetter son nxtt aussi. Bien y penser.
*/

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent
#include <windows.h>           //Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>            //Nécessaire pour savoir la position du curseur sur Windows
#include <winuser.h>		   //Nécessaire pour savoir la position du curseur sur Windows
#include <conio.h>             //Nécessaire pour enregistrer les inputs du clavier
#include <io.h>				   //Nécessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>			   //Nécessaire pour décrypter les accents en unicode
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
		//Constructeurs	
			StringAsVect() : nb(TailleBase), debut(0), fin(0) {  //Défaut
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace					
			}
			StringAsVect(char nxt) : nb(TailleBase), debut(0), fin(1) {  //À partir d'une seule valeur
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
				pt[0] = nxt;
			}
			StringAsVect(char nxt[], int nbpos) : nb(nbpos + TailleBase), debut(0), fin(nbpos) {   //À partir d'un array
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
					for(int pos=0; pos<fin; pos++) pt[pos] = nxt[pos];
			}
			StringAsVect(std::string nxt) : nb(nxt.length() + TailleBase), debut(0), fin(nxt.length()) {      //À partir d'un string
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
					for(int pos=0; pos<fin; pos++) pt[pos] = nxt[pos];
			}	
		//Destructeur
			~StringAsVect() {delete[] pt;}	
		//Copy constructor  
			StringAsVect(const StringAsVect& nxt) : nb(nxt.nb), debut(nxt.debut), fin(nxt.fin) {
					try{pt = new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt = new char [nb];             	//Vraiment allouer l'espace		
				for(int pos=debut; pos<fin; pos++) pt[pos] = nxt.pt[pos];        //Copier le contenu					
			}
		//Copy assignment
			StringAsVect& operator= (const StringAsVect& nxt) {
				nb = nxt.nb; debut = nxt.debut; fin = nxt.fin;				
				delete[] pt;     //Effacer l'array vers lequel je pointe actuellement
					try{pt = new char [nb];}  //Essayer d'allouer l'espace 
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)				
				pt = new char [nb];		     		//Vraiment allouer un nouvel espace pour le nouvel objet
				for(int pos=debut; pos<fin; pos++) pt[pos] = nxt.pt[pos];        //Copier le contenu
				return *this;                        //???????? Pourquoi retourner quelque chose dans un = ?
			}	
		//Move constructor
			StringAsVect(StringAsVect&& nxt) : nb(nxt.nb), debut(nxt.debut), fin(nxt.fin), pt(nxt.pt) {nxt.pt = nullptr;}  //Copie seulement le pointeur (pas son contenu), et efface le temporaire
		//Move assignement
			StringAsVect& operator= (StringAsVect&& nxt) {
				delete[] pt;
				nb = nxt.nb; debut = nxt.debut; fin = nxt.fin;
				pt = nxt.pt;         //Copier seulement le pointeur, sans faire une copie du contenu
				nxt.pt = nullptr;    //Rendre nul le pointeur temporaire
				return *this;
			}
   		//Opérateur d'accès : []
		   char operator[] (int pos) {return(pt[debut + pos]);}
		//Fonction d'accès : nbactif
			int nbactif (void) {return(debut-fin);}		
		//Fonction de modification : ajout          //Ajoute les valeurs en right-hand à la SUITE des valeurs déjà contenues
		   void ajout (char nxt) {
		   		if(fin + 1 < nb) {      //Pas besoin de ré-allouer la mémoire
		   			pt[fin] = nxt; fin++;
				} else {                //Besoin de ré-allouer
					int NombreActifVieux = debut - fin;      	//Déterminer le nombre d'éléments actifs déjà contenus dans l'objet
					int NombreActifNeuf = NombreActifVieux + 1; //Déterminer le nombre d'éléments actifs à contenir dans l'objet
					nb = NombreActifNeuf + TailleBase;             	//Déterminer le nombre d'éléments du prochain bloc de mémoire
						try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 
					  	catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de mémoire à l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de mémoire des vieux éléments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					nwpt[posNeuf] = nxt;                        //Ajouter le nouvel élément
					debut = 0; fin = NombreActifNeuf;           //Ré-initialiser les compteurs de position
					delete[] pt;       							//Supprimer les éléments contenus dans le viel array						
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }
		   void ajout (string nxt) {
		   		if(fin + nxt.length() < nb) {      //Pas besoin de ré-allouer la mémoire
		   			int nbnxt = nxt.length();
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt[posnxt];   
					 fin+=nwend;
				} else {                //Besoin de ré-allouer
					int nbnxt = nxt.length();    
					int NombreActifVieux = debut - fin;      	//Déterminer le nombre d'éléments actifs déjà contenus dans l'objet
					int NombreActifNeuf = NombreActifVieux + nbnxt; //Déterminer le nombre d'éléments actifs à contenir dans l'objet
					nb = NombreActifNeuf + TailleBase;             	//Déterminer le nombre d'éléments du prochain bloc de mémoire
						try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 					
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de mémoire à l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de mémoire des vieux éléments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[posNeuf++] = nxt[posnxt]; //Ajouter les nouveaux éléments
					debut = 0; fin = NombreActifNeuf;           //Ré-initialiser les compteurs de position
					delete[] pt;       							//Supprimer les éléments contenus dans le viel array	
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }		   
		   void ajout (StringAsVect nxt) {
		   		if(fin + nxt.nb < nb) {      //Pas besoin de ré-allouer la mémoire
		   			int nbnxt = nxt.nb;
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt[posnxt];   
					 fin+=nwend;
				} else {                //Besoin de ré-allouer
					int nbnxt = nxt.nb;    
					int NombreActifVieux = debut - fin;      	//Déterminer le nombre d'éléments actifs déjà contenus dans l'objet
					int NombreActifNeuf = NombreActifVieux + nbnxt; //Déterminer le nombre d'éléments actifs à contenir dans l'objet
					nb = NombreActifNeuf + TailleBase;             	//Déterminer le nombre d'éléments du prochain bloc de mémoire
							try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 					
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de mémoire à l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de mémoire des vieux éléments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[posNeuf++] = nxt[posnxt]; //Ajouter les nouveaux éléments
					debut = 0; fin = NombreActifNeuf;           //Ré-initialiser les compteurs de position
					delete[] pt;       							//Supprimer les éléments contenus dans le viel array	
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }
		//Opérateur de modification : suppression          //"Supprime" le nombre de positions en right-hand AU DÉBUT des valeurs déjà contenues
			void suppression (int nb) {
				if(nb > fin-debut) debut = fin; else debut+=nb; 
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
			//Constructeurs	:
				StaticVect<Type,Taille>() : debut(0), fin(0) {}  //Défaut 
				StaticVect<Type,Taille>(Type nxt) : debut(0), fin(1) {pt[0] = nxt;}  //Une seule valeur
				StaticVect<Type,Taille>(Type* ptarr, int longueur) : debut(0), fin(longueur) {for(int pos=0;pos<longueur;pos++) pt[pos] = ptarr[pos];}   //Array
	   		//Opérateur d'accès : []
			   Type operator[] (int pos) {
			   		return(pt[debut + pos]);
			   }
			//Fonction de modification : nouvelarray()
				void nouvelarray(Type* ptarr, int taillearr) {taille = taillearr; debut = 0; fin = 0; pt = ptarr;} 
			//Fonction de modification : ajout()
				bool ajout(Type nxt) {if(fin+1 <= taille) {pt[fin] = nxt; fin++; return(true);} else return(false);}       //Fonction de retour pour communiquer la réussite ou non!				
				bool ajout(Type nxt, int pos) {
					if(fin+1 <= taille) {
						for(int ptpos = fin; ptpos>pos; ptpos--) pt[ptpos] = pt[ptpos-1];
						pt[pos] = nxt; fin++; 
						return(true);
					} else return(false);
				}
				bool ajout(Type* nxt, int longueur) {
					if(fin+longueur <= taille) {
						int nouvfin = fin + longueur; int posnxt = 0;
						for(int pos=fin; pos<nouvfin; pos++) {pt[pos] = nxt[posnxt++];}
						fin=nouvfin;
						return(true);
					} else return(false);
				}
			//Fonction de modification : remplacement()
				int remplacement(Type nxt) {debut = 0; fin = 1; pt[0] = nxt; return(true);}  	
				int remplacement(Type* nxt, int longueur) {
					if(longueur <= taille) {
						debut = 0; fin = longueur;
						for(int pos=0; pos<longueur; pos++) pt[pos] = nxt[pos];	
						return(true);			
					} else return(false);
				}
				int remplacement(StaticVect<Type,Taille>& nxt) {
					if(nxt.fin-nxt.debut <= taille) {
						debut = 0; fin = nxt.fin;
						int longueurnxt = nxt.fin-nxt.debut;
						int pos = 0; for(int posnxt=0; posnxt<longueurnxt; posnxt++) pt[pos++] = nxt[posnxt];		
						return(true);
					} else return(false);
				}
			//Fonction de modification : vide()
				void vide(void) {debut = 0; fin = 0;}
			//Fonction de modification : suppression          //"Supprime" le nombre de positions en right-hand AU DÉBUT des valeurs déjà contenues
				void suppression (int nb) {
					if(nb > fin-debut) debut = fin; else debut+=nb; 
				}
			//Fonction de modification : supprposition       //Supprime l'entrée à la position indiquée
				void supprposition (int pos) {
					if(pos >= debut & pos < fin) {
						for(int ptpos = pos; ptpos < fin-1; ptpos++) {pt[ptpos] = pt[ptpos+1];}
						fin--;
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
	void out(int chiffre) {std::wcout << chiffre;}

	//vi) Fonction : chgcol ; change la couleur du texte à entrer
	void chgcol(string color) {
		WORD code;                                            //Voir la bibliothèque pour la légende
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
								//Attention: Cette classe contient des membres StaticVect.
								//À cause de son orthographe particulier, cette classe nécessite de voler son pointeur à un array permanent.
								//Il est donc nécessaire de pairer chaque objet StaticVect avec un array.
								//L'array occupera la place dans la mémoire, et le StaticVect facilitera les modifications sur la mémoire.
								//Cela est nécessaire pour éviter de mettre un template <int taille> aux StaticVect, allourdissant leur utilisation dans des fonctions.
	class input {
		//Valeurs membres
		public:
			StaticVect<char,200> commande;          	//Phrase que contient le buffer
			int inputpos;                   //Position d'indexation du prochain caractère    == StaticVect.fin? Non! Car ça peut bouger!
			int inputlong;                  //Nombre de caractères total de la commande actuelle (0 : inputpos = 0)   //== StaticVect.fin - StaticVect.debut
			bool accepted;                  //Flag concernant la dernière commande; utile pour l'affichage visuel
			bool busy;						//Flag concernant la dernière commande; utile pour l'affichage visuel
		//Constructeur par défaut
			input() : inputpos(0), inputlong(0), accepted(false), busy(false) {}
	};							
						
	//v) classe : inputecho ; permet l'affichage résiduel des commandes (acceptées ou refusées)
								//Attention: Cette classe contient des membres StaticVect.
								//À cause de son orthographe particulier, cette classe nécessite de voler son pointeur à un array permanent.
								//Il est donc nécessaire de pairer chaque objet StaticVect avec un array.
								//L'array occupera la place dans la mémoire, et le StaticVect facilitera les modifications sur la mémoire.
								//Cela est nécessaire pour éviter de mettre un template <int taille> aux StaticVect, allourdissant leur utilisation dans des fonctions.	
	class inputecho {
		//Valeurs membres
		public:
			StaticVect<char,200> commande;
			StaticVect<int,50> clignote;              	   //Conserve les instructions pour le clignotement : positif = affiche, négatif = pause.	
			string couleur;                            //Conserve la couleur du clignotement
			bool actif;							       //Compteur d'activité
			int nxtt;         						   //Moment où la prochaine entrée sera traitée         				
		//Constructeur par défaut
		inputecho() : couleur("gris sombre"), actif(false) {nxtt = timems();}	
	};
	
	//vi) classe : expression : permet de structurer diverses évaluation d'objets
	
/*	
	//vii) classe : chainon : permet le stockage du texte et des conditions d'apparition
	class chainon {
		//Membres
		public:
			bool pret;
			bool fini;
			StaticVect<expression,30> cond;
			StaticVect<staticvect<int,10>,10> enchainement;   //int réfère aux positions des mailles              //?????? COMMENT LE TRAITER???? STRUCTURE SPÉCIALE????
			StaticVect<expression,10> enchaineprob;        //Avec le même ordre d'indexation que enchaînement
			StaticVect<string,10> maille;
			StaticVect<string,10> commandes                             //PROBABLEMENT FAIRE UNE STRUCTURE PERSONALISÉE AVEC & ET | ET !=
			StaticVect<string,10> codespeciauxdebut;
			StaticVect<string,10> codespeciauxfin;
			StaticVect<int,10> override;
			StaticVect<string,10> overridename;
			int canal;
			string canalname;
	};
*/

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

	//iii) fonction : UserInputEcho ; canal spécial validant graphiquement l'acceptation ou le refus des commandes envoyées
	void UserInputEcho(input& inp, inputecho& inpecho, const fen& base) {	
		chgcol(inpecho.couleur);
		//Clignoter
		if(inpecho.clignote[0]>0){
			curspos(inp.inputlong,base.limtxty); for(int pos=inp.inputlong; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
		} else {
			curspos(inp.inputlong,base.limtxty); for(int pos=inp.inputlong; pos < inpecho.commande.fin; pos++) out(' ');			
		}
		chgcol(base.couleur);                       //Revenir à la couleur de base	
		inpecho.nxtt += abs(inpecho.clignote[0]);        //Updater le "next time"
		inpecho.clignote.suppression(1);            //Passer à la prochaine instruction
		if(inpecho.clignote.debut==inpecho.clignote.fin) inpecho.actif = false;			//Vérifier s'il reste toujours du stock à passer dans le canal	
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
//6) Fonction UserInput()
void UserInput(input& inp, inputecho& inpecho, const fen& base) {
	if(_kbhit()){
	//i) Capter la lettre tapée
	bool enter = false;
	char key = _getch();                  		//Enregistrer quelle touche a été pressée
			if (key == 0 || key == -32 || key == 224) {      //La valeur est spéciale: elle nécessite de la ré-examiner
				key = _getch();                              //Examiner une deuxième valeur pour identifier
				if(key == 75) {     								 				 //flèche gauche : reculer dans la commande tapée 
					if(inp.inputpos!=0) {
						if(inp.inputpos!=inp.inputlong) {
							curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						}          //Remettre en gris la position précédente
						inp.inputpos--;  
					}
				}
				else if (key == 77) {											 	 //flèche droite : avancer dans la commande tapée				
					if(inp.inputpos!=inp.inputlong) {
						curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						inp.inputpos++;		
					}			//Remettre en gris la position précédente
				} 
				else if (key == 72)  ;  											 //Flèche du haut   ... Rien ne se passe?
				else if (key == 80)  ;  											 //Flèche du bas    ... Rien ne se passe?
				else if (key == 83) {                                                //Delete : supprimer un caractère de la commande actuelle
					if(inp.inputpos!=inp.inputlong) {
						inp.inputlong--;
						inp.commande.supprposition(inp.inputpos);    
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.inputlong; pos++) out(inp.commande[pos]);    
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
						inp.inputpos--; inp.inputlong--;
						inp.commande.supprposition(inp.inputpos);   
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.inputlong; pos++) out(inp.commande[pos]);   
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
					if(inp.inputlong<base.limtxtx-1){
						inp.commande.ajout(key,inp.inputpos);
						inp.inputpos++; inp.inputlong++;
						curspos(inp.inputpos-1,base.limtxty);	                    
						for(int pos=inp.inputpos-1; pos<inp.inputlong; pos++) out(inp.commande[pos]);
						if(inp.inputlong==inpecho.commande.fin) inpecho.actif = false;                   //Désactiver le canal d'écho si la commande actuelle le dépasse
					}
						
								//BTW: FAUDRAIT AUSSI TOUT UN PAN DE CODE POUR GÉRER LES COMMANDES TROP LONGUES, POUR FAIRE RECULER LE TEXTE
										//Pour l'instant, je restreint l'espace à la largeur de la console, simplement.
							
				}
			}	
		//Remettre la lettre sélectionnée en surbrillance
		if(inp.inputpos!=inp.inputlong) {chgcol("blanc"); curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); chgcol(base.couleur);}
			
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
			inp.inputpos = 0; inp.inputlong = 0; inp.commande.vide();                               //Nettoyer l'objet input			
		}	
	}
}               


//------------------------------------------------------------------------------------------------------------------------------------------------------
//7) Aire de tests
							
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
