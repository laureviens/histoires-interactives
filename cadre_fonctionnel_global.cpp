/*
			///||================================---2018/06/15---================================||\\\
\\\||================================---Cadre fonctionnel global pour lire des histoires---================================||///
*/

//Debbugg: pour avoir l'option de "sleep"
#include <unistd.h>

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


//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Définir les classes-contenantes dynamiques

	//i) classe : arr ; sauvegarde un array avec son nombre d'éléments
						//Les membres spéciaux ont été copiés de : http://www.cplusplus.com/doc/tutorial/classes2/
	template <class Type>
		class arr {
			//Valeurs membres	
			public:
				Type* pt;  //Déclarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'extérieur 
				int nb;  //Déclarer le nombre d'objets de l'array
			//Constructeurs	
				arr<Type>() : nb(0), pt(new Type) {}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
				arr<Type>(Type nxt) : nb(1), pt(new Type [1]) {pt[0] = nxt;}  //Créer un constructeur pour créer l'objet avec une seule valeur
				arr<Type>(Type nxt[], int nbpos) : nb(nbpos), pt(new Type[nbpos]) {for(int pos=0; pos < nbpos; pos++) pt[pos] = nxt[pos];}  //Créer un constructeur pour créer à partir d'un array
			//Destructeur
				~arr<Type>() {delete[] pt;}
			//Copy constructor
				arr<Type>(const arr<Type>& nxt) : nb(nxt.nb), pt(new Type {nxt.pt}) {}
			//Copy assignment
				arr<Type>& operator= (const arr<Type>& nxt) {
					delete[] pt;     //Efface l'array vers lequel je pointe actuellement
					nb = nxt.nb;     //Change le nombre d'éléments
					pt = new Type [nb] = nxt.pt;     //Alloue un nouvel espace pour le nouvel objet, et copie
					return *this;                        //???????? Pourquoi retourner quelque chose dans un = ?
				}	
			//Move constructor
				arr<Type>(arr<Type>&& nxt) : nb(nxt.nb), pt(nxt.pt) {nxt.pt = nullptr;}  //Copie seulement le pointeur (pas son contenu), et efface le temporaire
			//Move assignement
				arr<Type>& operator= (arr<Type>&& nxt) {
					delete[] pt;
					nb = nxt.nb;
					pt = nxt.pt;         //Copier seulement le pointeur, sans faire une copie du contenu
					nxt.pt = nullptr;    //Rendre nul le pointeur temporaire
					return *this;
				}
	   		//Opérateur d'accès : []
			   arr<Type>& operator[] (int pos) {
			   		return(pt[pos]);
			   }			
		};
	
	
	//ii) classe : StringAsVect ; permet un simulâcre d'allocation dynamique de mémoire, avec la magie de voir plus grand + indexation
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
					try{pt = new char{*nxt.pt};}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)			
				pt = new char{*nxt.pt};             	//Vraiment allouer l'espace			
			}
		//Copy assignment
			StringAsVect& operator= (const StringAsVect& nxt) {
				delete[] pt;     //Efface l'array vers lequel je pointe actuellement
				nb = nxt.nb;     //Change le nombre d'éléments
				debut = nxt.debut; fin = nxt.fin;           //Change la position de début et de fin du vecteur accessible
					try{pt = new char [nb] {*nxt.pt};}  //Essayer d'allouer l'espace 
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)				
				pt = new char [nb] {*nxt.pt};     		//Vraiment allouer un nouvel espace pour le nouvel objet, et copie
				return *this;                        //???????? Pourquoi retourner quelque chose dans un = ?
			}	
		//Move constructor
			StringAsVect(StringAsVect&& nxt) : nb(nxt.nb), debut(nxt.debut), fin(nxt.fin), pt(nxt.pt) {nxt.pt = nullptr;}  //Copie seulement le pointeur (pas son contenu), et efface le temporaire
		//Move assignement
			StringAsVect& operator= (StringAsVect&& nxt) {
				delete[] pt;
				nb = nxt.nb;
				debut = nxt.debut; fin = nxt.fin;
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

	//iii) classe : memoire ; permet de sauvegarder la "mémoire" de la console, c'est-à-dire tous le texte s'y étant déjà inscrit
		
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
				frontline = 1;                         //Ce qui suit semble être la seule manière de créer des arrays dynamiques
				nbligne = TailleBase;            
					try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
				souvenir = new char* [nbcol];   //Créer un premier array contenant des pointers
				for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}    //Créer les lignes pour chaque colonne
			}
			//Constructeur pour avoir le bon nombre de colonnes
			memoire(int ncol) {
				nbcol = ncol;
				frontline = 1;                         //Ce qui suit semble être la seule manière de créer des arrays dynamiques
				nbligne = TailleBase;            
					try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)								
				souvenir = new char* [nbcol];   //Créer un premier array contenant des pointers
				for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}    //Créer les lignes pour chaque colonne
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
					for(int col = 0; col < nbcol; col++) souvenir[col][emptypos];   //Remplir la position vide
					//Déplacer de 1 tout ce qui vient ensuite, en commençant par la fin
					for(int lin = frontline; lin > emptypos+1; lin--) for(int col = 0; col < nbcol; col++) souvenir[col][lin+1]=souvenir[col][lin]; 
					frontline++;   //Noter qu'on ajoute une ligne
				} else {
					int emptypos = pos + 1;   //Calculer la position qui sera vide
						try{char** nwsouv = new char* [nbcol] ; for(int col = 0; col<nbcol ; col++) {nwsouv [col] = new char [nbligne+TailleBase];}}  //Tenter d'allouer l'espace
					  	catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la mémoire est saturée (exceptions)
					char** nwsouv = new char* [nbcol] ; for(int col = 0; col<nbcol ; col++) {nwsouv [col] = new char [nbligne+TailleBase];}  //Initialiser le nouveau bloc de mémoire à l'aide d'un pointeur temporaire
					int oldpos = 0;  //Déclarer un compteur pour les vieilles positions				
					for(int nwpos=0; nwpos < frontline; nwpos++) {  //Remplir, en laissant une position vide
						if(nwpos==emptypos) {continue;} 
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
		memoire mem {27};                   //INITIALISATION DE L'OBJET; VÉRIFIER AVEC LES BONNES DIMENSIONS POUR LA FENÊTRE!!!
		
							//ENCORE MIEUX: METTRE L'OBJET DE MÉMOIRE EN TANT QU'ARGUMENT DE READ, POUR QU'ON PUISSE LE DÉFINIR QUAND ON VEUT!

//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) Définir les fonctions et objets de manipulation

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
			
		/*		
			//DEBUGGING
			cout << "\n Longueur, avant la boucle while()";

			cout << "\nLongueur : Le string passé est:";
			for(int a=str.debut; a<str.fin; a++) out(str.pt[a]); Sleep(5000);
		
			cout<< "\nLongueur : la longueur donnée est: " << longueur; Sleep(5000);
		*/
			
		
			//for(int pos = str.debut + 1; !fini&pos<str.fin ; pos++) {longueur++; out(str[pos]); Sleep(1000); if(str[pos]=='§') {fini = true; cout<< "DEBUGGINGGGG!!!!!"; Sleep(1000);}} 
	
		for(int pos = str.debut + 1; !fini&pos<str.fin ; pos++) {longueur++; if(str.pt[pos]=='§') fini = true;} 
		
		
		
			
		return(longueur);		
	}

	//vii) Fonction : CodeSpecialExtract ; extrait une valeur numérique d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
	double CodeSpecialExtractDouble(const StringAsVect& str, int longueur){
		string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
		int longmax = longueur - 1 + str.debut;      //Le dernier caractère étant le '§'
		
		/*
			//DEBUGGING
			cout << "\nExtract : Le string passé est:";
			for(int a=str.debut; a<str.fin; a++) out(str.pt[a]); Sleep(5000);
		*/	


			
		for(int pos=2+str.debut; pos<longmax; pos++) nbonly += str.pt[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)
		
		/*
			//DEBUGGING
			cout << "\n Extract, avant la conversion de \"" << nbonly << "\"";
		*/

		
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
		fen(int x, int y) {charx = x; chary = y; consy = 0; refoule = false;}      //Créer un constructeur permettant d'assigner manuellement les dimensions de la fenêtre	
	};
		//Créer l'objet base, qui contiendra les information sur la fenêtre de base
		fen base(27,13);     //EN CE MOMENT, A LES DIMENSIONS DE 27 COLONNES ET 13 LIGNES (VOIR JEU GRAPHIQUE SIMPLE)


//------------------------------------------------------------------------------------------------------------------------------------------------------
//4) Écrire la fonction read()
read(canal& can) {
	//Updater le "next time"
	can.nxtt += can.delay;
	//Interpréter les "codes spéciaux" (§...§)
	if(can.txt[0]=='§'){		
	
			//DEBUGGGINGGG
	
	/*
				cout << "\n\n\n\nWouhouuu!! Code spécial!!!";
	*/
	
	
	
		//Déterminer la longueur du code spécial
			int CodeSpecialLong = CodeSpecialLongueur(can.txt);	
	
	/*		
					//DEBUGGING
						cout << "\nLa longueur du code spécial est connue!!";
	*/
									
			
		//Lire le code spécial		
			if(can.txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture
			
		/*	
					//DEBUGGING
						cout << "\nLe code spécial a ete reconnu!";
		*/
			
			
				double val = CodeSpecialExtractDouble(can.txt,CodeSpecialLong);       //Extraire le temps que durera la pause
				can.nxtt += round(val * can.vit);                    //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					

		/*	
				//DEBUGGGING
					cout << "\nLe temps d'attente extrait est: " << val*can.vit;
		*/


			} else if(can.txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = CodeSpecialExtractDouble(can.txt,CodeSpecialLong);       //Extraire la nouvelle vitesse
				can.vit = val;
			}  //EN AJOUTER UN (code spécial) POUR PLACER LE CURSEUR À LA FIN DE LA CONSOLE
			
			/*
					//DEBUGGING
						cout << "\nLe code spécial a ete computed";
			*/
			
			/*
					//DEBUGGING
						cout << "\nLa longueur du code spécial était de: " << CodeSpecialLong;
			*/
			
					
		//Effacer le code spécial du canal
		can.txt.supprim(CodeSpecialLong);                 
		
		/*
				//DEBUGGINGGGGG
					cout << "\nMaintenant, le reste du texte est:";
					for(int a=can.txt.debut; a<can.txt.fin; a++) out(can.txt[a]);
		*/
		
		      
	} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
		//Dealer avec la situation où on a à sauter une ligne (créer les lignes supplémentaires et updater les diverses positions)
			bool jump = false;
			if(can.txt[0]=='\n'|can.posx>=base.charx-1) jump = true;     //base.charx - 1 ; car c'est en integer, et can.posx commence à 0!
			if(jump) {
				
				
			
				//DÉBUGGGINNGGG
			/*	
				cout << "\nJUMP! \n    JUMP! \n           JUMP!";  //détecter les jumps
			*/	
				
				
				
				
				//Sauter une ligne dans la mémoire
				for(int countx = can.posx + 1; countx < base.charx ; countx++) mem.souvenir[countx][can.posy] = ' ';     //Effacer le reste de la ligne avec des espaces    
				mem.newline(can.posy);                     //Introduit une nouvelle ligne à la suite de la position qui lui est fournie			
				//Updater le correctif de décalage de la console par rapport à la mémoire
					if(base.refoule) base.consy++; else if(mem.frontline>base.chary) {base.refoule = true; base.consy++;} 					
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore saturée: on pousse vers le bas!
						if(can.posy==mem.frontline-1) {               //Si le canal gère la dernière ligne de la console, c'est plus simple    //-1 : à cause de [0]
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-même!   //-1 : à cause de [0]
						} else {                             //S'il y a d'autres lignes à repousser vers le bas
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-même!   //-1 : à cause de [0]
							//Ré-écrire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,can.posy-base.consy + 2);  //Mettre le curseur au début de la reconstruction
								for(int county = can.posy + 2 ; county < mem.frontline ; county++) {    // + 2, parce que la mémoire a déjà été updatée
									for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est saturée: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "reléguant ce qui y était déjà vers le haut")
							curspos(can.posy-base.consy,0); for(int countx = 0; countx < base.charx ; countx++) out(' '); 					
						//Tout ré-écrire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county < can.posy; county++){             //base.consy : facteur de décalage de la console
										//VÉRIFIER L'INITIATION DE COUNTY: ÇA SEMBLE UN BEL ADON QUE base.consy, UN "count" EN INTEGER SIMPLE,
										//S'EMBOÎTE PARFAITEMENT AVEC L'INDEXATION QUI COMMENCE À 0!
								for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}
					
					
/*                         	////////////Va falloir débuguer cette partir éventuellement!!!					
					
				//Updater les positions dans les autres canaux    //Parce que leur position dans la mémoire a bougé //la position dans la console est quant à elle gérée par base.consy
				for(int countcan = 0 ; countcan < canx.nb ; countcan++) {        
					if(canx[countcan].posy > can.posy) canx[countcan].posy++;         //la mémoire refoule toujours vers le bas!
				}            
				//En passant, je l'ai effacé, mais canx est un argument de read() de type arr<canal>&   */
				
				
				
				//Updater les positions dans le canal actuel
				if(can.txt[0]=='\n') {can.posx = -1;} else can.posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
	////////										//FLAG POUR POSITION IMPOSSIBLE; PEUT-ÊTRE QUE ÇA VA EMMENER UN BUG ÉVENTUELLEMENT?
				can.posy++;																   //en y 
			} else {can.posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caractère       //À partir d'ici, les posx et posy sont la position du charactère actuel (dans la mémoire)!		
		if(can.txt[0]!='\n') {
			curspos(can.posx,can.posy-base.consy) ; out(can.txt[0]);     //Inscrire dans la console
			
			/*
						/////DDEEBBUUGGINNGG
						curspos(0,can.posx + 8); cout << can.posx;	
			*/
			
			mem.souvenir[can.posx][can.posy] = can.txt[0];   //Inscrire dans la mémoire
				
				/*		
						////////DDDDDDDEBUGING
						curspos(1,can.posx + 8); cout << "Mem recorded on " << can.posx << cout << " : " << mem.souvenir[can.posx][can.posy];
				*/
						
		}	
		//Effacer le caractère du canal
		can.txt.supprim(1);                     
		
	/*
		//       DDDDDDDDDEEEEEEEEEEEEEEEEEEEBBBBBBBBBBBUUUUUUUUUUUUUUUUGGGGGGGGGGGGGGGGGGIIIIIIIIIIIIINNNNNNNNNNNNNNNGGGGGGGGGGGG//////////////
		//Écrire les positions en x et y!
		curspos(1,can.posy-base.consy+4); cout << "posx: "<< can.posx << "; posy: " << can.posy << "; debut: " << can.txt.debut << "; fin: " << can.txt.fin;
		sleep(1);
		curspos(1,can.posy-base.consy+4); cout << "                                    ";		  
	*/	
		   
	}
	//Tester si le canal est toujours actif
	if(can.txt.debut==can.txt.fin) can.actif = false;
}

	
//Et maintenant... Tester?
						//Avec les dimensions du jeu graphique simple!


		/*			
					
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unités sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	out('H'); out('e'); out('l'); out('l'); out('o'); out('?');	out('\n');  //Fonctionne!

	canal can1;
	can1.txt.ajout("Je pèse des éléphants géants, malheureusement.");

	string teststring = "Lalalilalere";
	int testpos = 0;

	StringAsVect teststringas;
	teststringas.ajout("Lalalilalere");
	
	StringAsVect teststringasaccent;
	teststringasaccent.ajout("LéLôlùlà");
	

	int currentt = timems();
	int nxtt = currentt + 500;

	cout << "  Initialisation terminée";


	while(true){
		currentt = timems();
		//if(currentt>nxtt) {cout << "Test"; nxtt = currentt + 200;}	//Fonctionne		
		if(currentt>nxtt) {read(can1); nxtt = currentt + 200;}			//Commence à s'afficher, mais avorte le processus après invariablement le 4e caractère
														//Si on enlève la ligne qui alloue à la mémoire, ça marche bien.
		
		
		
				/////Ce qui suit devrait théoriquement +- marche, selon moi; mais je n'ai pas testé. 
		
		//if(currentt>nxtt) {out(can1.txt[0]); can1.txt-1; nxtt = currentt + 200;}			//Ne s'affiche pas
		//if(currentt>nxtt) {mem.souvenir[can1.posx][can1.posy] = can1.txt[0]; nxtt = currentt + 200; can1.posx++;}     //Avorte le process
		/*if(currentt>nxtt) {
			mem.souvenir[testpos][0] = teststring[testpos];                         //Avorte le process, mais s'affiche (avant de crasher)
			cout << mem.souvenir[testpos][0] ; nxtt = currentt + 200; testpos++;}     
		}
		//if(currentt>nxtt) {cout << teststringas[testpos]; nxtt = currentt + 200; testpos++;}    //S'affiche complètement.	                                         
		//if(currentt>nxtt) {out(teststringas[testpos]); nxtt = currentt + 200; testpos++;}    //S'affiche complètement... Des fois. Sinon s'avorte.	                                         
		//if(currentt>nxtt) {out(teststringasaccent[testpos]); nxtt = currentt + 200; testpos++;}    //S'est affiché à un moment donné? Sinon s'avorte.                        
		//if(currentt>nxtt) {out(teststringas[0]); teststringas-1; nxtt = currentt + 200;}			//S'affiche n'importe comment

	}
}
				//Conclusions:
				
				//C'est la fonction read() qui fait planter,
						//et non le compteur.
						
				//Yé! Faut maintenant trouver ce qui ne fonctionne pas dans read()!
					//Indice: La première lettre s'affiche correctement.		
					//Indice: les caractères spéciaux n'ont même pas été abordés.
					//Indice: ce n'est pas dans les jumps non plus. Y'a pas de jump qui se passe.
		
					//Ce qui nous laisse donc, à peut-être bugger:
							//Effacer le caractère du canal
							//Inscrire le caractère dans la console et dans la mémoire      		

					//Coupable: inscrire le caractère dans la mémoire bug.
					//Indice: le texte ne s'affiche toujours pas correctement même si on enlève cette partie fautive.
					//Coupable: juste la partie d'affichage du canal, sans read(), ne fonctionne pas. genre[] et -.
					
					//Indice: Rine ne semble plus marcher. Je pense que le point que j'ai changé est que j'ai ajouté un StringAsAccent dans la mémoire dynamique.
					
					//Indice: Une itération m'a donné: terminate called after throwing an instance of 'std::bad_alloc' what():   std::bad_alloc
					
							/*In general you cannot and should not try to respond to this error. bad_alloc indicates that a resource cannot be allocated because not enough memory is available. In most scenarios your program cannot hope to cope with that, and terminating soon is the only meaningful behaviour.
							
							Worse, modern operating systems often over-allocate: malloc and new will always return a valid pointer, even if there is technically no (or not enough) free memory left – so std::bad_alloc will never be thrown, or is at least not a reliable sign of memory exhaustion. Instead, attempts to access the allocated memory will then result in an error, which is not catchable.
							
							The only thing you could do when catching std::bad_alloc is to perhaps log the error, and try to ensure a safe program termination by freeing outstanding resources (but this is done automatically in the normal course of stack unwinding after the error gets thrown if the program uses RAII appropriately).*/					
			
							//Donc... C'est un peu weird.
									//Parce que techniquement, y'aurait pas vraiment d'autres instances de "new" qui seraient callées at this point,
									//puisque je ne fait littéralement rien dans la plupart des tentatives.
									//On pire, je supprime dans un StringAsVect, qui ne lance pas de new.
									
							//La conclusion la plus probable est sûrement que ma mémoire dynamique est déjà saturée.		 
							//Ce qui est un peu triste, parce que j'ai pas tant de trucs en mémoire que ça.
							
					//Indice: J'ai tenté de mettre tout les objets de grosse initiation en commentaire, en oubliant la mémoire;
					//        ce qui a donné std::bad_alloc. J'ai ensuite mis la mémoire en commentaire, et j'ai obtenu une belle run.
					
					//Indice: J'ai encore eu un std::bad_alloc, même si je n'ai maintenant que 3 StringAsFactor d'actifs.
					//        Je ne comprends définitivement pas ce qui se passe.
					
					//Indice: J'ai fermé le logiciel d'écriture+compilation en c++, et l'ai rouvert. Ça marche maintenant.
					
					//Indice: Le texte qui ne s'affichait pas était dû simplement à une erreur dans StringAsVect operator- (debut-fin au lieu de fin-debut). Corrigée.
					
					//Indice: Je pensais que les erreurs étaient dues à un manque d'espace d'allocation.
								//Mais après avoir ajouté des message d'erreur contre ces erreurs, rien n'apparaît.
								//Ça plante sans rien dire.
							
						//C'était juste parce que je n'avais pas la bonne taille pour la mémoire, finalement. Il semble.
					
					//Là, tout semble marcher.
					
					
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unités sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	//Créer les canaux utilisés
	canal can1;
	canal can2;
	
	//Test: changer les délais manuellement
	can1.delay = 140;
	can2.delay = 230;
	
	//Test: changer les positions manuellement
	can2.posy = 6;
	
	//Ajouter du texte aux canaux
	string txt0 = "Ceci est du texte! Je dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	string txt1 = "Le canal 1 est sooooo boring. Ark. §p1000§\n Je suis le canal 2.";
	can1.txt.ajout(txt0); can2.txt.ajout(txt1);
	
	//Rendre manuellement les canaux actifs
	can1.actif = true; can2.actif = true;	
	
	//Faire une boucle pour que les canaux s'expriment!
	while(true){
		int currentt = timems();
			if(can1.actif&can1.nxtt<currentt) read(can1);
			if(can2.actif&can2.nxtt<currentt) read(can2);
		}
}					

			//Conclusion: Ça marche... jusqu'à geler éventuellement? 
					//Ça gèle quand ça tombe sur le code spécial...
	
					//C'était dû à des erreurs dans les fonctions de conversions. Dont des erreurs de compteurs d'itération.
						//Mais y'avait aussi des fuck avec les types utilisés;
							//Pour passer les strings correctement, fallait les passer comme constantes;
								//Mais ça empêchait d'utiliser l'opérateur[] overridé; mais comme str.pt[], ça marche.


		//Right. Faudrait juste ajouter un truc pour que la fonction read() s'arrête un jour. Genre s'inactive. J'avais oublié ça.
						//Done!
