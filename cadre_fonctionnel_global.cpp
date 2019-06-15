/*
			///||================================---2018/06/15---================================||\\\
\\\||================================---Cadre fonctionnel global pour lire des histoires---================================||///
*/

//Debbugg: pour avoir l'option de "sleep"
#include <unistd.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entr�es/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round()
#include <chrono>     //Pour avoir un meilleur contr�le du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
#define _WIN32_WINNT 0x0500    //N�cessaire pour la taille de la fen�tre: informe qu'on est sur Windows 2000 ou plus r�cent
#include <windows.h>           //N�cessaire pour toute modification de la console sur Windows (utilie "Windows API")
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)


//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) D�finir les classes-contenantes dynamiques

	//i) classe : arr ; sauvegarde un array avec son nombre d'�l�ments
						//Les membres sp�ciaux ont �t� copi�s de : http://www.cplusplus.com/doc/tutorial/classes2/
	template <class Type>
		class arr {
			//Valeurs membres	
			public:
				Type* pt;  //D�clarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'ext�rieur 
				int nb;  //D�clarer le nombre d'objets de l'array
			//Constructeurs	
				arr<Type>() : nb(0), pt(new Type) {}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
				arr<Type>(Type nxt) : nb(1), pt(new Type [1]) {pt[0] = nxt;}  //Cr�er un constructeur pour cr�er l'objet avec une seule valeur
				arr<Type>(Type nxt[], int nbpos) : nb(nbpos), pt(new Type[nbpos]) {for(int pos=0; pos < nbpos; pos++) pt[pos] = nxt[pos];}  //Cr�er un constructeur pour cr�er � partir d'un array
			//Destructeur
				~arr<Type>() {delete[] pt;}
			//Copy constructor
				arr<Type>(const arr<Type>& nxt) : nb(nxt.nb), pt(new Type {nxt.pt}) {}
			//Copy assignment
				arr<Type>& operator= (const arr<Type>& nxt) {
					delete[] pt;     //Efface l'array vers lequel je pointe actuellement
					nb = nxt.nb;     //Change le nombre d'�l�ments
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
	   		//Op�rateur d'acc�s : []
			   arr<Type>& operator[] (int pos) {
			   		return(pt[pos]);
			   }			
		};
	
	
	//ii) classe : StringAsVect ; permet un simul�cre d'allocation dynamique de m�moire, avec la magie de voir plus grand + indexation
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
		//Constructeurs	
			StringAsVect() : nb(TailleBase), debut(0), fin(0) {  //D�faut
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace					
			}
			StringAsVect(char nxt) : nb(TailleBase), debut(0), fin(1) {  //� partir d'une seule valeur
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
				pt[0] = nxt;
			}
			StringAsVect(char nxt[], int nbpos) : nb(nbpos + TailleBase), debut(0), fin(nbpos) {   //� partir d'un array
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
					for(int pos=0; pos<fin; pos++) pt[pos] = nxt[pos];
			}
			StringAsVect(std::string nxt) : nb(nxt.length() + TailleBase), debut(0), fin(nxt.length()) {      //� partir d'un string
					try{pt =new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt =new char [nb];             		//Vraiment allouer l'espace
					for(int pos=0; pos<fin; pos++) pt[pos] = nxt[pos];
			}	
		//Destructeur
			~StringAsVect() {delete[] pt;}	
		//Copy constructor
			StringAsVect(const StringAsVect& nxt) : nb(nxt.nb), debut(nxt.debut), fin(nxt.fin) {
					try{pt = new char{*nxt.pt};}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt = new char{*nxt.pt};             	//Vraiment allouer l'espace			
			}
		//Copy assignment
			StringAsVect& operator= (const StringAsVect& nxt) {
				delete[] pt;     //Efface l'array vers lequel je pointe actuellement
				nb = nxt.nb;     //Change le nombre d'�l�ments
				debut = nxt.debut; fin = nxt.fin;           //Change la position de d�but et de fin du vecteur accessible
					try{pt = new char [nb] {*nxt.pt};}  //Essayer d'allouer l'espace 
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)				
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
   		//Op�rateur d'acc�s : []
		   char operator[] (int pos) {return(pt[debut + pos]);}
		//Fonction d'acc�s : nbactif
			int nbactif (void) {return(debut-fin);}		
		//Fonction de modification : ajout          //Ajoute les valeurs en right-hand � la SUITE des valeurs d�j� contenues
		   void ajout (char nxt) {
		   		if(fin + 1 < nb) {      //Pas besoin de r�-allouer la m�moire
		   			pt[fin] = nxt; fin++;
				} else {                //Besoin de r�-allouer
					int NombreActifVieux = debut - fin;      	//D�terminer le nombre d'�l�ments actifs d�j� contenus dans l'objet
					int NombreActifNeuf = NombreActifVieux + 1; //D�terminer le nombre d'�l�ments actifs � contenir dans l'objet
					nb = NombreActifNeuf + TailleBase;             	//D�terminer le nombre d'�l�ments du prochain bloc de m�moire
						try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 
					  	catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de m�moire � l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de m�moire des vieux �l�ments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					nwpt[posNeuf] = nxt;                        //Ajouter le nouvel �l�ment
					debut = 0; fin = NombreActifNeuf;           //R�-initialiser les compteurs de position
					delete[] pt;       							//Supprimer les �l�ments contenus dans le viel array						
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }
		   void ajout (string nxt) {
		   		if(fin + nxt.length() < nb) {      //Pas besoin de r�-allouer la m�moire
		   			int nbnxt = nxt.length();
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt[posnxt];   
					 fin+=nwend;
				} else {                //Besoin de r�-allouer
					int nbnxt = nxt.length();    
					int NombreActifVieux = debut - fin;      	//D�terminer le nombre d'�l�ments actifs d�j� contenus dans l'objet
					int NombreActifNeuf = NombreActifVieux + nbnxt; //D�terminer le nombre d'�l�ments actifs � contenir dans l'objet
					nb = NombreActifNeuf + TailleBase;             	//D�terminer le nombre d'�l�ments du prochain bloc de m�moire
						try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 					
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de m�moire � l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de m�moire des vieux �l�ments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[posNeuf++] = nxt[posnxt]; //Ajouter les nouveaux �l�ments
					debut = 0; fin = NombreActifNeuf;           //R�-initialiser les compteurs de position
					delete[] pt;       							//Supprimer les �l�ments contenus dans le viel array	
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }		   
		   void ajout (StringAsVect nxt) {
		   		if(fin + nxt.nb < nb) {      //Pas besoin de r�-allouer la m�moire
		   			int nbnxt = nxt.nb;
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt[posnxt];   
					 fin+=nwend;
				} else {                //Besoin de r�-allouer
					int nbnxt = nxt.nb;    
					int NombreActifVieux = debut - fin;      	//D�terminer le nombre d'�l�ments actifs d�j� contenus dans l'objet
					int NombreActifNeuf = NombreActifVieux + nbnxt; //D�terminer le nombre d'�l�ments actifs � contenir dans l'objet
					nb = NombreActifNeuf + TailleBase;             	//D�terminer le nombre d'�l�ments du prochain bloc de m�moire
							try{char* nwpt = new char [nb];} 			//Essayer d'allouer l'espace 					
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)
					char* nwpt = new char [nb];                   	//Initialiser le nouveau bloc de m�moire � l'aide d'un pointeur temporaire
					int posNeuf = 0; for(int posVieux=debut; posVieux<fin; posVieux++) {   //Remplir le nouveau bloc de m�moire des vieux �l�ments
      	  				nwpt[posNeuf++] = pt[posVieux];
					}
					for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[posNeuf++] = nxt[posnxt]; //Ajouter les nouveaux �l�ments
					debut = 0; fin = NombreActifNeuf;           //R�-initialiser les compteurs de position
					delete[] pt;       							//Supprimer les �l�ments contenus dans le viel array	
      	  			pt = nwpt;                                  //Copier seulement le pointeur, sans faire une copie du contenue
      	  			nwpt = nullptr;                             //Rendre nul le pointeur temporaire
				}
		   }
		//Op�rateur de modification : supprim          //"Supprime" le nombre de positions en right-hand AU D�BUT des valeurs d�j� contenues
			void supprim (int pos) {
				if(pos > fin-debut) debut = fin; else debut+=pos; 
			}
	};		

	//iii) classe : memoire ; permet de sauvegarder la "m�moire" de la console, c'est-�-dire tous le texte s'y �tant d�j� inscrit
		
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
				frontline = 1;                         //Ce qui suit semble �tre la seule mani�re de cr�er des arrays dynamiques
				nbligne = TailleBase;            
					try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
				souvenir = new char* [nbcol];   //Cr�er un premier array contenant des pointers
				for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}    //Cr�er les lignes pour chaque colonne
			}
			//Constructeur pour avoir le bon nombre de colonnes
			memoire(int ncol) {
				nbcol = ncol;
				frontline = 1;                         //Ce qui suit semble �tre la seule mani�re de cr�er des arrays dynamiques
				nbligne = TailleBase;            
					try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
				souvenir = new char* [nbcol];   //Cr�er un premier array contenant des pointers
				for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}    //Cr�er les lignes pour chaque colonne
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
					for(int col = 0; col < nbcol; col++) souvenir[col][emptypos];   //Remplir la position vide
					//D�placer de 1 tout ce qui vient ensuite, en commen�ant par la fin
					for(int lin = frontline; lin > emptypos+1; lin--) for(int col = 0; col < nbcol; col++) souvenir[col][lin+1]=souvenir[col][lin]; 
					frontline++;   //Noter qu'on ajoute une ligne
				} else {
					int emptypos = pos + 1;   //Calculer la position qui sera vide
						try{char** nwsouv = new char* [nbcol] ; for(int col = 0; col<nbcol ; col++) {nwsouv [col] = new char [nbligne+TailleBase];}}  //Tenter d'allouer l'espace
					  	catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)
					char** nwsouv = new char* [nbcol] ; for(int col = 0; col<nbcol ; col++) {nwsouv [col] = new char [nbligne+TailleBase];}  //Initialiser le nouveau bloc de m�moire � l'aide d'un pointeur temporaire
					int oldpos = 0;  //D�clarer un compteur pour les vieilles positions				
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
		memoire mem {27};                   //INITIALISATION DE L'OBJET; V�RIFIER AVEC LES BONNES DIMENSIONS POUR LA FEN�TRE!!!
		
							//ENCORE MIEUX: METTRE L'OBJET DE M�MOIRE EN TANT QU'ARGUMENT DE READ, POUR QU'ON PUISSE LE D�FINIR QUAND ON VEUT!

//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) D�finir les fonctions et objets de manipulation

	//i) Fonction : timems ; avoir le temps actuel en millisecondes (depuis l'epoch, soit 1er janvier 1970)
	int timems (void) {
		return(std::chrono::duration_cast< std::chrono::milliseconds >(
	    	std::chrono::system_clock::now().time_since_epoch()
			).count());
	}	

	//ii) Objets : TxtConsole et CursorPosition ; permet de modifier le texte affich� dans la console   	            	//WINDOWS ONLY
	HANDLE TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);        //Objet permettant de modifier le texte affich� dans la console 
	COORD CursorPosition;                                     	//Objet permettant de se situer sur la console

	//iii) Objet : DimConsole ; permet de modifier les dimensions et la position de la console  			            	//WINDOWS ONLY
	HWND DimConsole = GetConsoleWindow();                       //Objet permettant de modifier les dimensions + la position de la console

	//iv) Fonction: curspos ; d�placer le curseur sur la console                                                            //WINDOWS ONLY
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(TxtConsole,CursorPosition);
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

	//vi) Fonction : CodeSpecialLong ; retourne la longueur d'un code sp�cial ('�' compris)
	int CodeSpecialLongueur(const StringAsVect& str){
		int longueur = 1;               //Initier l'objet � retourner
		bool fini = false;              
			
		/*		
			//DEBUGGING
			cout << "\n Longueur, avant la boucle while()";

			cout << "\nLongueur : Le string pass� est:";
			for(int a=str.debut; a<str.fin; a++) out(str.pt[a]); Sleep(5000);
		
			cout<< "\nLongueur : la longueur donn�e est: " << longueur; Sleep(5000);
		*/
			
		
			//for(int pos = str.debut + 1; !fini&pos<str.fin ; pos++) {longueur++; out(str[pos]); Sleep(1000); if(str[pos]=='�') {fini = true; cout<< "DEBUGGINGGGG!!!!!"; Sleep(1000);}} 
	
		for(int pos = str.debut + 1; !fini&pos<str.fin ; pos++) {longueur++; if(str.pt[pos]=='�') fini = true;} 
		
		
		
			
		return(longueur);		
	}

	//vii) Fonction : CodeSpecialExtract ; extrait une valeur num�rique d'une suite de caract�res encadr�s par '�' (pour extraire les codes sp�ciaux)
	double CodeSpecialExtractDouble(const StringAsVect& str, int longueur){
		string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres (2X'�' + 1 identifiant en char)
		int longmax = longueur - 1 + str.debut;      //Le dernier caract�re �tant le '�'
		
		/*
			//DEBUGGING
			cout << "\nExtract : Le string pass� est:";
			for(int a=str.debut; a<str.fin; a++) out(str.pt[a]); Sleep(5000);
		*/	


			
		for(int pos=2+str.debut; pos<longmax; pos++) nbonly += str.pt[pos];    //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire (identifiant en char)
		
		/*
			//DEBUGGING
			cout << "\n Extract, avant la conversion de \"" << nbonly << "\"";
		*/

		
		return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}		
	int CodeSpecialExtractInt(StringAsVect& str, int longueur){
		string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres (2X'�' + 1 identifiant en char)
		int longmax = longueur - 1;      //Le dernier caract�re �tant le '�'
		int nbonlypos = 0; for(int pos=2; pos<longmax; pos++) nbonly[nbonlypos++] += str.pt[pos];    //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire (identifiant en char)
		return(stoi(nbonly));           //La fonction stoi convertit les strings en int (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}		

//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) D�finir les classes-contenantes statiques
	
	//i) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant � lire, la vitesse, etc.
	class canal {
		//Membres
		public:
			int nxtt;           //D�clarer le moment o� la prochaine entr�e sera trait�e         
			int delay;          //D�clarer le d�lai de base entre chaque entr�e
			int posx, posy;		//D�clarer les coordonn�es de la derni�re entr�e dans la m�moire (la pr�c�dente)   
								//les positions de la consoles sont d�finies en d�calant ces derni�res
			StringAsVect txt;   //D�clarer le texte qui reste � lire  				
			bool actif;			//D�clarer le compteur d'activit�
			double vit;         //D�clarer la vitesse actuelle de d�filement et de pauses (toujours par rapport � la base, 1)
		//Constructeur
		canal() {nxtt = timems() ; delay = 400 ; posx = -1; posy = 0; actif = false; vit = 1;}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
	};


	//ii) Classe : fen ; permet de sauvegarder les param�tres relatifs aux caract�ristiques de la fen�tre de sortie (console)
	class fen {
		//Membres
		public:
			int charx, chary;     //D�clarer les dimensions de la fen�tre en terme de nombre de caract�res pouvant y �tre contenus
			int consy;             //D�clarer le facteur de d�calement de la console o� appara�t le texte avec la m�moire, o� il est stock�
			bool refoule;          //D�clarer le flag pour voir si le facteur de d�calement entre en compte
		//Constructeurs
		fen() {charx = 1; chary = 1; consy = 0; refoule = false;}      //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
					//� RETRAVAILLER POUR Y METTRE UNE FONCTION PERMETTANT DE DEVINER AUTOMATIQUEMENT LES DIMENSIONS DE LA FEN�TRE!
		fen(int x, int y) {charx = x; chary = y; consy = 0; refoule = false;}      //Cr�er un constructeur permettant d'assigner manuellement les dimensions de la fen�tre	
	};
		//Cr�er l'objet base, qui contiendra les information sur la fen�tre de base
		fen base(27,13);     //EN CE MOMENT, A LES DIMENSIONS DE 27 COLONNES ET 13 LIGNES (VOIR JEU GRAPHIQUE SIMPLE)


//------------------------------------------------------------------------------------------------------------------------------------------------------
//4) �crire la fonction read()
read(canal& can) {
	//Updater le "next time"
	can.nxtt += can.delay;
	//Interpr�ter les "codes sp�ciaux" (�...�)
	if(can.txt[0]=='�'){		
	
			//DEBUGGGINGGG
	
	/*
				cout << "\n\n\n\nWouhouuu!! Code sp�cial!!!";
	*/
	
	
	
		//D�terminer la longueur du code sp�cial
			int CodeSpecialLong = CodeSpecialLongueur(can.txt);	
	
	/*		
					//DEBUGGING
						cout << "\nLa longueur du code sp�cial est connue!!";
	*/
									
			
		//Lire le code sp�cial		
			if(can.txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause � la lecture
			
		/*	
					//DEBUGGING
						cout << "\nLe code sp�cial a ete reconnu!";
		*/
			
			
				double val = CodeSpecialExtractDouble(can.txt,CodeSpecialLong);       //Extraire le temps que durera la pause
				can.nxtt += round(val * can.vit);                    //Ajouter le temps d'attente        //round() est n�cessaire pour arrondir correctement					

		/*	
				//DEBUGGGING
					cout << "\nLe temps d'attente extrait est: " << val*can.vit;
		*/


			} else if(can.txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = CodeSpecialExtractDouble(can.txt,CodeSpecialLong);       //Extraire la nouvelle vitesse
				can.vit = val;
			}  //EN AJOUTER UN (code sp�cial) POUR PLACER LE CURSEUR � LA FIN DE LA CONSOLE
			
			/*
					//DEBUGGING
						cout << "\nLe code sp�cial a ete computed";
			*/
			
			/*
					//DEBUGGING
						cout << "\nLa longueur du code sp�cial �tait de: " << CodeSpecialLong;
			*/
			
					
		//Effacer le code sp�cial du canal
		can.txt.supprim(CodeSpecialLong);                 
		
		/*
				//DEBUGGINGGGGG
					cout << "\nMaintenant, le reste du texte est:";
					for(int a=can.txt.debut; a<can.txt.fin; a++) out(can.txt[a]);
		*/
		
		      
	} else {  //Interpr�ter le reste des caract�res (pas des codes sp�ciaux)
		//Dealer avec la situation o� on a � sauter une ligne (cr�er les lignes suppl�mentaires et updater les diverses positions)
			bool jump = false;
			if(can.txt[0]=='\n'|can.posx>=base.charx-1) jump = true;     //base.charx - 1 ; car c'est en integer, et can.posx commence � 0!
			if(jump) {
				
				
			
				//D�BUGGGINNGGG
			/*	
				cout << "\nJUMP! \n    JUMP! \n           JUMP!";  //d�tecter les jumps
			*/	
				
				
				
				
				//Sauter une ligne dans la m�moire
				for(int countx = can.posx + 1; countx < base.charx ; countx++) mem.souvenir[countx][can.posy] = ' ';     //Effacer le reste de la ligne avec des espaces    
				mem.newline(can.posy);                     //Introduit une nouvelle ligne � la suite de la position qui lui est fournie			
				//Updater le correctif de d�calage de la console par rapport � la m�moire
					if(base.refoule) base.consy++; else if(mem.frontline>base.chary) {base.refoule = true; base.consy++;} 					
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore satur�e: on pousse vers le bas!
						if(can.posy==mem.frontline-1) {               //Si le canal g�re la derni�re ligne de la console, c'est plus simple    //-1 : � cause de [0]
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-m�me!   //-1 : � cause de [0]
						} else {                             //S'il y a d'autres lignes � repousser vers le bas
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-m�me!   //-1 : � cause de [0]
							//R�-�crire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,can.posy-base.consy + 2);  //Mettre le curseur au d�but de la reconstruction
								for(int county = can.posy + 2 ; county < mem.frontline ; county++) {    // + 2, parce que la m�moire a d�j� �t� updat�e
									for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est satur�e: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")
							curspos(can.posy-base.consy,0); for(int countx = 0; countx < base.charx ; countx++) out(' '); 					
						//Tout r�-�crire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county < can.posy; county++){             //base.consy : facteur de d�calage de la console
										//V�RIFIER L'INITIATION DE COUNTY: �A SEMBLE UN BEL ADON QUE base.consy, UN "count" EN INTEGER SIMPLE,
										//S'EMBO�TE PARFAITEMENT AVEC L'INDEXATION QUI COMMENCE � 0!
								for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}
					
					
/*                         	////////////Va falloir d�buguer cette partir �ventuellement!!!					
					
				//Updater les positions dans les autres canaux    //Parce que leur position dans la m�moire a boug� //la position dans la console est quant � elle g�r�e par base.consy
				for(int countcan = 0 ; countcan < canx.nb ; countcan++) {        
					if(canx[countcan].posy > can.posy) canx[countcan].posy++;         //la m�moire refoule toujours vers le bas!
				}            
				//En passant, je l'ai effac�, mais canx est un argument de read() de type arr<canal>&   */
				
				
				
				//Updater les positions dans le canal actuel
				if(can.txt[0]=='\n') {can.posx = -1;} else can.posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
	////////										//FLAG POUR POSITION IMPOSSIBLE; PEUT-�TRE QUE �A VA EMMENER UN BUG �VENTUELLEMENT?
				can.posy++;																   //en y 
			} else {can.posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du charact�re actuel (dans la m�moire)!		
		if(can.txt[0]!='\n') {
			curspos(can.posx,can.posy-base.consy) ; out(can.txt[0]);     //Inscrire dans la console
			
			/*
						/////DDEEBBUUGGINNGG
						curspos(0,can.posx + 8); cout << can.posx;	
			*/
			
			mem.souvenir[can.posx][can.posy] = can.txt[0];   //Inscrire dans la m�moire
				
				/*		
						////////DDDDDDDEBUGING
						curspos(1,can.posx + 8); cout << "Mem recorded on " << can.posx << cout << " : " << mem.souvenir[can.posx][can.posy];
				*/
						
		}	
		//Effacer le caract�re du canal
		can.txt.supprim(1);                     
		
	/*
		//       DDDDDDDDDEEEEEEEEEEEEEEEEEEEBBBBBBBBBBBUUUUUUUUUUUUUUUUGGGGGGGGGGGGGGGGGGIIIIIIIIIIIIINNNNNNNNNNNNNNNGGGGGGGGGGGG//////////////
		//�crire les positions en x et y!
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

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unit�s sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	out('H'); out('e'); out('l'); out('l'); out('o'); out('?');	out('\n');  //Fonctionne!

	canal can1;
	can1.txt.ajout("Je p�se des �l�phants g�ants, malheureusement.");

	string teststring = "Lalalilalere";
	int testpos = 0;

	StringAsVect teststringas;
	teststringas.ajout("Lalalilalere");
	
	StringAsVect teststringasaccent;
	teststringasaccent.ajout("L�L�l�l�");
	

	int currentt = timems();
	int nxtt = currentt + 500;

	cout << "  Initialisation termin�e";


	while(true){
		currentt = timems();
		//if(currentt>nxtt) {cout << "Test"; nxtt = currentt + 200;}	//Fonctionne		
		if(currentt>nxtt) {read(can1); nxtt = currentt + 200;}			//Commence � s'afficher, mais avorte le processus apr�s invariablement le 4e caract�re
														//Si on enl�ve la ligne qui alloue � la m�moire, �a marche bien.
		
		
		
				/////Ce qui suit devrait th�oriquement +- marche, selon moi; mais je n'ai pas test�. 
		
		//if(currentt>nxtt) {out(can1.txt[0]); can1.txt-1; nxtt = currentt + 200;}			//Ne s'affiche pas
		//if(currentt>nxtt) {mem.souvenir[can1.posx][can1.posy] = can1.txt[0]; nxtt = currentt + 200; can1.posx++;}     //Avorte le process
		/*if(currentt>nxtt) {
			mem.souvenir[testpos][0] = teststring[testpos];                         //Avorte le process, mais s'affiche (avant de crasher)
			cout << mem.souvenir[testpos][0] ; nxtt = currentt + 200; testpos++;}     
		}
		//if(currentt>nxtt) {cout << teststringas[testpos]; nxtt = currentt + 200; testpos++;}    //S'affiche compl�tement.	                                         
		//if(currentt>nxtt) {out(teststringas[testpos]); nxtt = currentt + 200; testpos++;}    //S'affiche compl�tement... Des fois. Sinon s'avorte.	                                         
		//if(currentt>nxtt) {out(teststringasaccent[testpos]); nxtt = currentt + 200; testpos++;}    //S'est affich� � un moment donn�? Sinon s'avorte.                        
		//if(currentt>nxtt) {out(teststringas[0]); teststringas-1; nxtt = currentt + 200;}			//S'affiche n'importe comment

	}
}
				//Conclusions:
				
				//C'est la fonction read() qui fait planter,
						//et non le compteur.
						
				//Y�! Faut maintenant trouver ce qui ne fonctionne pas dans read()!
					//Indice: La premi�re lettre s'affiche correctement.		
					//Indice: les caract�res sp�ciaux n'ont m�me pas �t� abord�s.
					//Indice: ce n'est pas dans les jumps non plus. Y'a pas de jump qui se passe.
		
					//Ce qui nous laisse donc, � peut-�tre bugger:
							//Effacer le caract�re du canal
							//Inscrire le caract�re dans la console et dans la m�moire      		

					//Coupable: inscrire le caract�re dans la m�moire bug.
					//Indice: le texte ne s'affiche toujours pas correctement m�me si on enl�ve cette partie fautive.
					//Coupable: juste la partie d'affichage du canal, sans read(), ne fonctionne pas. genre[] et -.
					
					//Indice: Rine ne semble plus marcher. Je pense que le point que j'ai chang� est que j'ai ajout� un StringAsAccent dans la m�moire dynamique.
					
					//Indice: Une it�ration m'a donn�: terminate called after throwing an instance of 'std::bad_alloc' what():   std::bad_alloc
					
							/*In general you cannot and should not try to respond to this error. bad_alloc indicates that a resource cannot be allocated because not enough memory is available. In most scenarios your program cannot hope to cope with that, and terminating soon is the only meaningful behaviour.
							
							Worse, modern operating systems often over-allocate: malloc and new will always return a valid pointer, even if there is technically no (or not enough) free memory left � so std::bad_alloc will never be thrown, or is at least not a reliable sign of memory exhaustion. Instead, attempts to access the allocated memory will then result in an error, which is not catchable.
							
							The only thing you could do when catching std::bad_alloc is to perhaps log the error, and try to ensure a safe program termination by freeing outstanding resources (but this is done automatically in the normal course of stack unwinding after the error gets thrown if the program uses RAII appropriately).*/					
			
							//Donc... C'est un peu weird.
									//Parce que techniquement, y'aurait pas vraiment d'autres instances de "new" qui seraient call�es at this point,
									//puisque je ne fait litt�ralement rien dans la plupart des tentatives.
									//On pire, je supprime dans un StringAsVect, qui ne lance pas de new.
									
							//La conclusion la plus probable est s�rement que ma m�moire dynamique est d�j� satur�e.		 
							//Ce qui est un peu triste, parce que j'ai pas tant de trucs en m�moire que �a.
							
					//Indice: J'ai tent� de mettre tout les objets de grosse initiation en commentaire, en oubliant la m�moire;
					//        ce qui a donn� std::bad_alloc. J'ai ensuite mis la m�moire en commentaire, et j'ai obtenu une belle run.
					
					//Indice: J'ai encore eu un std::bad_alloc, m�me si je n'ai maintenant que 3 StringAsFactor d'actifs.
					//        Je ne comprends d�finitivement pas ce qui se passe.
					
					//Indice: J'ai ferm� le logiciel d'�criture+compilation en c++, et l'ai rouvert. �a marche maintenant.
					
					//Indice: Le texte qui ne s'affichait pas �tait d� simplement � une erreur dans StringAsVect operator- (debut-fin au lieu de fin-debut). Corrig�e.
					
					//Indice: Je pensais que les erreurs �taient dues � un manque d'espace d'allocation.
								//Mais apr�s avoir ajout� des message d'erreur contre ces erreurs, rien n'appara�t.
								//�a plante sans rien dire.
							
						//C'�tait juste parce que je n'avais pas la bonne taille pour la m�moire, finalement. Il semble.
					
					//L�, tout semble marcher.
					
					
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unit�s sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	//Cr�er les canaux utilis�s
	canal can1;
	canal can2;
	
	//Test: changer les d�lais manuellement
	can1.delay = 140;
	can2.delay = 230;
	
	//Test: changer les positions manuellement
	can2.posy = 6;
	
	//Ajouter du texte aux canaux
	string txt0 = "Ceci est du texte! Je dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	string txt1 = "Le canal 1 est sooooo boring. Ark. �p1000�\n Je suis le canal 2.";
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

			//Conclusion: �a marche... jusqu'� geler �ventuellement? 
					//�a g�le quand �a tombe sur le code sp�cial...
	
					//C'�tait d� � des erreurs dans les fonctions de conversions. Dont des erreurs de compteurs d'it�ration.
						//Mais y'avait aussi des fuck avec les types utilis�s;
							//Pour passer les strings correctement, fallait les passer comme constantes;
								//Mais �a emp�chait d'utiliser l'op�rateur[] overrid�; mais comme str.pt[], �a marche.


		//Right. Faudrait juste ajouter un truc pour que la fonction read() s'arr�te un jour. Genre s'inactive. J'avais oubli� �a.
						//Done!
