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
					curspos(0,canaux.pt[canpos].posy-base.consy+1); for(int countx = 0; countx < base.charx ; countx++) out(' '); 
				qui est ma foi un peu patantée. Je ne sais pas pourquoi elle marche, mais c'est la seule qui marche. À revérifier plus tard.
*/
	


//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round()
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent
#include <windows.h>           //Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)





//Debbugg: pour avoir l'option de "sleep"
#include <unistd.h>

	//i) Fonction : timems ; avoir le temps actuel en millisecondes (depuis l'epoch, soit 1er janvier 1970)
	int timems (void) {
		return(std::chrono::duration_cast< std::chrono::milliseconds >(
	    	std::chrono::system_clock::now().time_since_epoch()
			).count());
	}	

	//ii) Objets : TxtConsole et CursorPosition ; permet de modifier le texte affiché dans la console   	            	//WINDOWS ONLY
	HANDLE TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);        //Objet permettant de modifier le texte affiché dans la console 
	COORD CursorPosition;                                     	//Objet permettant de se situer sur la console

	//iii) Objet : DimConsole ; permet de modifier les dimensions et la position de la console  			            	//WINDOWS ONLY
	HWND DimConsole = GetConsoleWindow();                       //Objet permettant de modifier les dimensions + la position de la console

	//iv) Fonction: curspos ; déplacer le curseur sur la console                                                            //WINDOWS ONLY
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(TxtConsole,CursorPosition);
	}



		//Debug
		int mempushbackcount = 0;



//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Définir les classes-contenantes dynamiques
	
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
		//Opérateur de modification : supprim          //"Supprime" le nombre de positions en right-hand AU DÉBUT des valeurs déjà contenues
			void supprim (int pos) {
				if(pos > fin-debut) debut = fin; else debut+=pos; 
			}
	};		

	//ii) classe : memoire ; permet de sauvegarder la "mémoire" de la console, c'est-à-dire tous le texte s'y étant déjà inscrit
		
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
				
				mempushbackcount++;
				/*
					//DEBUGINGG: afficher la mémoire, pour voir c'que ça donne.
						curspos(0,0);
						for(int posy=0; posy<13; posy++){
							cout << posy;
							for(int posx=0; posx<27; posx++) cout << souvenir[posx][posy];
							}
							cout << "\nLa position de la ligne repoussee est: " << pos;
							abort();
						Sleep(4000);				
				
											//Ok. Là, la mémoire est vide. C'est un peu flippant. 
				*/
				
				
				if(frontline+1<nbligne) {
					int emptypos = pos + 1;   //Calculer la position qui sera vide
					//Déplacer de 1 tout ce qui vient ensuite, en commençant par la fin
					for(int lin = frontline; lin > pos; lin--) for(int col = 0; col < nbcol; col++) souvenir[col][lin+1]=souvenir[col][lin]; 
					for(int col = 0; col < nbcol; col++) souvenir[col][emptypos] = ' ';   //Remplir la position vide d'espace
					frontline++;   //Noter qu'on ajoute une ligne
					
		
		
		
	/*	
				if(mempushbackcount==3){
				
					//DEBUGINGG: afficher la mémoire, pour voir c'que ça donne.
						curspos(0,0);
						for(int posy=0; posy<=frontline; posy++){
							cout << posy;
							for(int posx=0; posx<27; posx++) cout << souvenir[posx][posy];
							}
							cout << "\nLa position de la ligne vide (celle qui a ete effacee) est: " << emptypos;
							cout << "\nLe frontline de la mémoire est maintenant rendu: " << frontline; 
							abort();
				}
	*/			
					
					
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

//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) Définir les fonctions et objets de manipulation

/*


	//i) Fonction : timems ; avoir le temps actuel en millisecondes (depuis l'epoch, soit 1er janvier 1970)
	int timems (void) {
		return(std::chrono::duration_cast< std::chrono::milliseconds >(
	    	std::chrono::system_clock::now().time_since_epoch()
			).count());
	}	

	//ii) Objets : TxtConsole et CursorPosition ; permet de modifier le texte affiché dans la console   	            	//WINDOWS ONLY
	HANDLE TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);        //Objet permettant de modifier le texte affiché dans la console 
	COORD CursorPosition;                                     	//Objet permettant de se situer sur la console

	//iii) Objet : DimConsole ; permet de modifier les dimensions et la position de la console  			            	//WINDOWS ONLY
	HWND DimConsole = GetConsoleWindow();                       //Objet permettant de modifier les dimensions + la position de la console

	//iv) Fonction: curspos ; déplacer le curseur sur la console                                                            //WINDOWS ONLY
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(TxtConsole,CursorPosition);
	}	
	
	
	
*/	
	
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

	//vi) Fonction : CodeSpecialLong ; retourne la longueur d'un code spécial ('§' compris)
	int CodeSpecialLongueur(const StringAsVect& str){
		int longueur = 1;               //Initier l'objet à retourner
		bool fini = false;              
		for(int pos = str.debut + 1; !fini&pos<str.fin ; pos++) {longueur++; if(str.pt[pos]=='§') fini = true;} 		
		return(longueur);		
	}

	//vii) Fonction : CodeSpecialExtract ; extrait une valeur numérique d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
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

//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Définir les classes-contenantes statiques
	
	//i) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant à lire, la vitesse, etc.
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
		canal() {nxtt = timems() ; delay = 400 ; posx = -1; posy = 0; actif = false; vit = 1;}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
	};


	//ii) Classe : fen ; permet de sauvegarder les paramètres relatifs aux caractéristiques de la fenêtre de sortie (console)
	class fen {
		//Membres
		public:
			int charx, chary;     //Déclarer les dimensions de la fenêtre en terme de nombre de caractères pouvant y être contenus
			int consy;             //Déclarer le facteur de décalement de la console où apparaît le texte avec la mémoire, où il est stocké
			bool refoule;          //Déclarer le flag pour voir si le facteur de décalement entre en compte
		//Constructeurs
		fen() {charx = 1; chary = 1; consy = 0; refoule = false;}      //Créer un constructeur par défaut, pour initialiser tous les paramètres
					//À RETRAVAILLER POUR Y METTRE UNE FONCTION PERMETTANT DE DEVINER AUTOMATIQUEMENT LES DIMENSIONS DE LA FENÊTRE!
								//Au pire, simplement en utilisant fonction genre GetCursPos(); et en notant c'est après combien de ++ qu'on revient à 0.
		fen(int x, int y) {charx = x; chary = y; consy = 0; refoule = false;}      //Créer un constructeur permettant d'assigner manuellement les dimensions de la fenêtre	
	};
	

	//iii) classe : arr ; sauvegarde un array avec son nombre d'éléments
						//Les membres spéciaux ont été copiés de : http://www.cplusplus.com/doc/tutorial/classes2/
	template <class Type>
		class arr {
			//Valeurs membres	
			public:
				Type* pt;  //Déclarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
				int nb;  //Déclarer le nombre d'objets de l'array
			//Constructeurs	:
				arr<Type>() : nb(0), pt(nullptr) {cout << "\nAttention: cet objet arr<> est vide (nullptr)";}  //Défaut 
				arr<Type>(Type nxt) : nb(1), pt(nxt) {}  //Une seule valeur
				arr<Type>(Type* nxt, int nbpos) : nb(nbpos), pt(nxt) {}  //Array pré-existant
	   		//Opérateur d'accès : []
			   Type operator[] (int pos) {
			   		return(pt[pos]);
			   }			
		};	

//------------------------------------------------------------------------------------------------------------------------------------------------------
//4) Écrire la fonction lire()
lire(arr<canal>& canaux, int canpos, fen& base, memoire& mem) {
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
		canaux.pt[canpos].txt.supprim(CodeSpecialLong);                 
	} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
		//Dealer avec la situation où on a à sauter une ligne (créer les lignes supplémentaires et updater les diverses positions)
			bool jump = false;
			if(canaux.pt[canpos].txt[0]=='\n'|canaux.pt[canpos].posx>=base.charx-1) jump = true;     //base.charx - 1 ; car c'est en integer, et canaux.pt[canpos].posx commence à 0!
			if(jump) {	
			
			/*
			
							//DEBUGINGG: afficher la mémoire, pour voir c'que ça donne.
						curspos(0,0);
						for(int posy=0; posy<13; posy++){
							cout << posy;
							for(int posx=0; posx<27; posx++) cout << mem.souvenir[posx][posy];
							}
							abort();
						Sleep(4000);
			*/
			
			
				//Sauter une ligne dans la mémoire
				//for(int countx = canaux.pt[canpos].posx + 1; countx < base.charx ; countx++) mem.souvenir[countx][canaux.pt[canpos].posy] = ' ';     //Effacer le reste de la ligne avec des espaces    
				
								//Ha-ah! Voici la ligne coupable!!!
										//Ah-haha!
										//Voici-voilà!
										
								//Bon. Pourquoi elle était là, déjà? Et à quoi elle sert?
										
							//Faut bien se rendre compte que tout marchait avant. Avec cette ligne. Voyons donc voir ce qui se passe si on l'enlève.			
								
						//Je l'ai enlevé, et tout marche encore.
								//Pourquoi était-elle là, déjà? Pour quel cas spécial est-ce qu'on touche à la mémoire?
											//Plus j'y pense, plus je trouve ça étrange...
											
									//Gode. Pourquoi?
										//Ce que ça fait... Ce que ça fait, c'est que ça efface le reste de la ligne qui va être sauté.
												//Mais DANS LA MÉMOIRE????
										//Pourquoi faire cela?
												//Pourquoi effacer LA MÉMOIRE, chose qui est censée ne pas être modifiable?
														//Bon. Je laisse tout ce texte comme note (avec la ligne en commentaire),
															//je l'effacerai après le prochain commit.				
										
				
				
				mem.newline(canaux.pt[canpos].posy);                     //Introduit une nouvelle ligne à la suite de la position qui lui est fournie	
				//Updater le correctif de décalage de la console par rapport à la mémoire
					if(base.refoule) base.consy++; else if(mem.frontline>base.chary) {base.refoule = true; base.consy++;} 		
					
					
	//J'ai mis la vieille ligne en commentaire! Et tente maintenant de faire une nouvelle ligne?
					//if(base.refoule&mem.frontline>base.chary) {base.refoule = true; base.consy++;} 					
							//Brrh, c'est pas fonctionnel comme ça.
					
								
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore saturée: on pousse vers le bas!
						if(canaux.pt[canpos].posy==mem.frontline-1) {               //Si le canal gère la dernière ligne de la console, c'est plus simple    //-1 : à cause de [0]		
							if(canaux.pt[canpos].posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-même!   //-1 : à cause de [0]
						} else {                             //S'il y a d'autres lignes à repousser vers le bas
							if(canaux.pt[canpos].posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-même!   //-1 : à cause de [0]
							//Ré-écrire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,canaux.pt[canpos].posy+1);  //Mettre le curseur au début de la reconstruction
								for(int county = canaux.pt[canpos].posy + 1 ; county <= mem.frontline ; county++) {   
									for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est saturée: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "reléguant ce qui y était déjà vers le haut")
							curspos(0,canaux.pt[canpos].posy-base.consy+1); for(int countx = 0; countx < base.charx ; countx++) out(' '); 
							
						
							
							//curspos(0,canaux.pt[canpos].posy-base.consy+1); cout << "TESTESTESTEST";
			/*				
							if(mempushbackcount==2) {
							curspos(0,canaux.pt[canpos].posy-base.consy) ; cout << "posy = " << canaux.pt[canpos].posy << ", consy = " << base.consy;
							curspos(0,22); cout << "Test."	;          //S'écrit bel et bien, même si c'est "en dehors des limites".
								curspos(0,0);
								abort();}	
								//WATCHER CETTE LIGNE!
										//Une version semblable était mal faite (effaçais la ligne dans la mémoire?) en haut;
												//Mais ce n'est probablement pas ça.	
												
											//En fait, la ligne qui s'en rapproche plus est celle de la reconstruction:
													//"//Ré-écrire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse"	
										
			*/							
							
							
												
						//Tout ré-écrire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county <= canaux.pt[canpos].posy; county++){             //base.consy : facteur de décalage de la console
										//VÉRIFIER L'INITIATION DE COUNTY: ÇA SEMBLE UN BEL ADON QUE base.consy, UN "count" EN INTEGER SIMPLE,
										//S'EMBOÎTE PARFAITEMENT AVEC L'INDEXATION QUI COMMENCE À 0!
								for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}	
				//Updater les positions dans les autres canaux    //Parce que leur position dans la mémoire a bougé //la position dans la console est quant à elle gérée par base.consy
				for(int countcan = 0 ; countcan < canaux.nb ; countcan++) {
					if(countcan==canpos) continue;                                    //la mémoire refoule toujours vers le bas!
					if(canaux.pt[countcan].posy > canaux.pt[canpos].posy) canaux.pt[countcan].posy++; else if(canaux.pt[countcan].posy == canaux.pt[canpos].posy) canaux.pt[countcan].posy+=2;
				}       // == : Si deux canaux se situe sur la même ligne, le canal qui change de ligne va couper l'autre en deux, et le renvoyer après sa propre ligne.    	        

								//ATTENTION: J'me trouvais bien bonne en écrivant cette ligne, rendant le processus de "coupage" super simple,
									//mais je n'ai rien changé dans la mémoire. Donc la mémoire ne suit pas. Fuck. 
								
									//En même temps, la mémoire a été écrite pour pousser l'espace vide dans la ligne D'APRÈS.
											//Attends, non. Est-ce vraiment ça qui fuck?	
										//Bon, alors le problème, c'que que la position de la ligne qui change update dans la console,
											//mais pas dans la mémoire.
										
										//En fait, descriptif:
											//A) Pour X raison, la ligne qui est coupée "perd sa place" dans la mémoire:
													//la ligne de départ est vide (aucune trace de la ligne coupée).
											//B) Le canal coupé n'est pas pushed-back. Enfin, pas bien.
											
		/*
				Ceci est                       <--- Pas sauvegardée dans la mémoire??? Comment ça se fait????    //Réglé! C'était une "stray-line",
				Le canal 1 est sooooo borin																		//qui effaçait la mémoire hors de la mémoire
						 du texte! Je dis d    <--- Pas "pushed back" par le saut de ligne qui s'en vient!
															//Pourquoi?	
		*/									//Mhh....
														//Techniquement, les positions sont assez éloignées pour que ça soit pushed-back.

		/*
				//Ce que ça fait après le push-back:    (coupé juste après le push-back du 'g' du canal 1)
		
					Console:
					
				Ceci est
				Le canal 1 est sooooo borin
				         du texte! Je dis d
				u texte maintenant!
				u texte maintenant!
				Wouho
		
					
					Mémoire:
		
				Ceci est
				Le canal 1 est sooooo borin
                                                    //Pourquoi est-ce que cette ligne est effacée?????   //Probablement à cause du push-back?
				u texte maintenant!                             //Mais pourquoi est-ce que cette ligne est dupliquée? 
				u texte maintenant!
				Wouho		
		
		*/ 
									//Ok, le problème est réellement au push-back du 'g' du canal 1.
											//Probablement que c'est juste la recopie des lignes qui ne va pas assez loin.
													//à l'intérieur du newline.

				//Updater les positions dans le canal actuel
				if(canaux.pt[canpos].txt[0]=='\n') {canaux.pt[canpos].posx = -1;} else canaux.pt[canpos].posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
				canaux.pt[canpos].posy++;
				
				
				/*	
				
						//DEBUGGGG
					for(int posy=0; posy<base.chary; posy++){
						for(int posx=0; posx<base.charx; posx++) {
							for(int countcan = 0; countcan < canaux.nb; countcan++) {
								if(posy==canaux.pt[countcan].posy&posx==canaux.pt[countcan].posx) {
									curspos(canaux.pt[countcan].posx,canaux.pt[countcan].posy); cout << countcan<< "Tralala";}
								}
							}
						}
					cout << "\n\nCanal 0: posx: " << canaux.pt[0].posx << ", posy: " << canaux.pt[0].posy;			
					cout << "\n\nCanal 1: posx: " << canaux.pt[1].posx << ", posy: " << canaux.pt[1].posy;	
					cout << "\n\nMémoire:\n";
					
					for(int y=0; y<base.chary; y++){
						for(int x=0; x<base.charx; x++) cout << mem.souvenir[x][y];
					}								
					abort();	
									//Ah. Rigth. Ici, posx est -1 pour le canal 1. Mais posy = 1.
										//C'est donc normal qui ne s'affiche pas, mais... Pour le reste?
				
								//Right. Je crois que je comprends. Non?
											//Non.
									//Je croyais que ça ne marchait pas quand le canal 0 arrivait à changer de ligne, car il était
										//techniquement encore sur la ligne 0... Mais non, dans le fond. Sa position est la ligne 2.			
				
							//Arrrrhhh. Ok. La mémoire est vide.
									//Pourquoi?
								//C'est le newline, c'est sûr que c'est le newline.	
										//Nope, c'était pas ça. 
											//Y'a un bout de code qui touche à la mémoire, mais qui n'est pas inclus dans le newline.
												//Juste avant le newline (dans lire()).
										//CHANGER ÇA, C'EST BÊTE.
												
				
			*/	
				
				
																				   //en y 
			} else {canaux.pt[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caractère       //À partir d'ici, les posx et posy sont la position du charactère actuel (dans la mémoire)!		
		if(canaux.pt[canpos].txt[0]!='\n') {
			curspos(canaux.pt[canpos].posx,canaux.pt[canpos].posy-base.consy) ; out(canaux.pt[canpos].txt[0]);     //Inscrire dans la console
			mem.souvenir[canaux.pt[canpos].posx][canaux.pt[canpos].posy] = canaux.pt[canpos].txt[0];   //Inscrire dans la mémoire			
		}	
		//Effacer le caractère du canal
		canaux.pt[canpos].txt.supprim(1);                     	   
	}
	//Vérifier s'il reste toujours du texte à passer dans le canal
	if(canaux.pt[canpos].txt.debut==canaux.pt[canpos].txt.fin) canaux.pt[canpos].actif = false;
}	
					
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unités sont en pixels!
       		                                                                //200x200 pixels = 13 lignes; 27 colonnes

	//Créer l'objet base, qui contiendra les information sur la fenêtre de base
	//fen base(27,13);     //EN CE MOMENT, A LES DIMENSIONS DE 27 COLONNES ET 13 LIGNES (VOIR JEU GRAPHIQUE SIMPLE)
	
	
		
	fen base(27,12);     //JE CHANGE LES DIMENSIONS POUR SIMULER AVEC LE DERNIER ESPACE EN BAS POUR ÉCRIRE!

	
	//Créer l'objet de mémoire, qui stockera tous les caractères utilisés
	memoire mem {27};                   //INITIALISATION DE L'OBJET; VÉRIFIER AVEC LES BONNES DIMENSIONS POUR LA FENÊTRE!!!
	

	//Créer les canaux utilisés
	canal can1;
	canal can2;
	
	//Test: changer les délais manuellement
	can1.delay = 140;
	can2.delay = 230;
	
	//Test: changer les positions manuellement
	//can2.posy = 3;
	//mem.frontline = 3;
	//can1.posy = 11;
	//can2.posy = 10;
	//mem.frontline = 13;
	
	//Ajouter du texte aux canaux
	string txt0 = "Ceci est du texte!\nJe dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	string txt1 = "§p1000§\nLe canal 1 \n              est sooooo boring. Ark.§p1000§\n§p1000§Je suis le canal 2.";
	can1.txt.ajout(txt0); can2.txt.ajout(txt1);
	
	//Rendre manuellement les canaux actifs
	can1.actif = true; can2.actif = true;	
	
	//Ajouter les canaux dans l'objet arr<canal>
	canal canx [2] = {can1,can2};
	arr<canal> canaux (canx,2);          
	
	//Faire une boucle pour que les canaux s'expriment!
	bool gogogo = true;
	while(gogogo){
		int currentt = timems();
			if(canaux.pt[0].actif&canaux.pt[0].nxtt<currentt) lire(canaux,0,base,mem);
			if(canaux.pt[1].actif&canaux.pt[1].nxtt<currentt) lire(canaux,1,base,mem);
			if(!canaux.pt[0].actif&!canaux.pt[1].actif) gogogo = false;
		}		
		
	curspos(0,13);
	
/*		
	//Lire la mémoire, pour voir elle a l'air de quoi	
	Sleep(5000);
	curspos(0,0);
	for(int posy=0; posy<mem.frontline; posy++){
		for(int posx=0; posx<base.charx; posx++) cout << mem.souvenir[posx][posy];
	}	
*/


}		

			//Bon. Là, la première ligne est réglée.
			
				//Maintenant. Pour le manque de push-back....

			//Bon. Ça push-back, tout est beau de ce côté.
					//C'est simplement que la ligne qui a été push-back n'est plus effacée dans la console. Dans la mémoire, oui.
						//Pas dans la console.
								//Bon. C'est fait.
								
										//Reste à tester pour quand la console est saturée?
										
										//Bien entendue, tout fuck.
												//La mémoire n'est même pas bonne pour rendre les bonnes choses?????
														//La mémoire semble avoir effacé la première ligne du canal 1, et la dernière du canal 0.
														
										//Ok. La mémoire a l'air correcte.
											//Je pense que c'est simplement la console qui a besoin d'un coup de pouce.
											
										//Voilà ce que je pense. Pas besoin de décalage. La console se souvient. Et est capable d'aller à l'infini vers le bas. Selon moi.	
											
											
										//Je pense qu'il y a un problème. 
											//La console a un comportement built-in pour gérer les changements de lignes.
											
												//Tout marcherait bien si j'avais un seul canal, en fait, avec une histoire linéaire.
												//Ou juste une dernière ligne que marche avec le reste
														//(si je veux faire afficher le texte qui est tapé,
														//sans le support de std::cin, ça va malheureusement prendre cette dernière ligne,
														//et me condamner à jouer drôlement avec la mémoire et les autres trucs comme ça).
														
											//Je devrais donc complètement l'ignorer, et faire mes petites affaires.
												//Le truc, c'est que j'utilise le caractère '\n' des fois littéralement,
												//pour changer de ligne facilement.
												//Et si je fais ça dans la dernière ligne de la console, tout fuck.
												
												//Wait. Je viens d'écrire que je n'aurais pas à faire ça....
												
												//J'essaie de mettre base.charx à nbmax - 1.
												
									//Wouhou! Techniquement, ça marche. Je vais quand même laisser une note en haut.			
															
															
				//Bon. En bref, ce que j'ai changé pour quand la console est saturée:
											//curspos(0,canaux.pt[canpos].posy-base.consy+1); for(int countx = 0; countx < base.charx ; countx++) out(' '); 
										//(ajouté le +1)
											//for(int county = base.consy; county <= canaux.pt[canpos].posy; county++){             //base.consy : facteur de décalage de la console
										//Mis <= à la place de <
										
						//Pis ça marche. Bon. 
								//C'est un peu patantée, comme solution.				
																					//Mais pour l'instant, ça va être ça qui va être ça.
															
															
