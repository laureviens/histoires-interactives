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
					try{pt = new char [nb];}        //Essayer d'allouer l'espace
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)			
				pt = new char [nb];             	//Vraiment allouer l'espace		
				for(int pos=debut; pos<fin; pos++) pt[pos] = nxt.pt[pos];        //Copier le contenu					
			}
		//Copy assignment
			StringAsVect& operator= (const StringAsVect& nxt) {
				nb = nxt.nb; debut = nxt.debut; fin = nxt.fin;				
				delete[] pt;     //Effacer l'array vers lequel je pointe actuellement
					try{pt = new char [nb];}  //Essayer d'allouer l'espace 
					catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class StringAsVect: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)				
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

	//ii) classe : memoire ; permet de sauvegarder la "m�moire" de la console, c'est-�-dire tous le texte s'y �tant d�j� inscrit
		
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
					for(int col = 0; col < nbcol; col++) souvenir[col][emptypos] = ' ';   //Remplir la position vide d'espace
					//D�placer de 1 tout ce qui vient ensuite, en commen�ant par la fin
					for(int lin = frontline; lin > emptypos; lin--) for(int col = 0; col < nbcol; col++) souvenir[col][lin+1]=souvenir[col][lin]; 
					frontline++;   //Noter qu'on ajoute une ligne
					
					
				/*	
					//DEBUGINGG: afficher la m�moire, pour voir c'que �a donne.
						//curspos(0,0);
						for(int posy=0; posy<13; posy++){
							cout << posy;
							for(int posx=0; posx<27; posx++) cout << souvenir[posx][posy];
							}
							abort();
						Sleep(4000);
				*/	
					
					
					
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
								//Au pire, simplement en utilisant fonction genre GetCursPos(); et en notant c'est apr�s combien de ++ qu'on revient � 0.
		fen(int x, int y) {charx = x; chary = y; consy = 0; refoule = false;}      //Cr�er un constructeur permettant d'assigner manuellement les dimensions de la fen�tre	
	};
	

	//iii) classe : arr ; sauvegarde un array avec son nombre d'�l�ments
						//Les membres sp�ciaux ont �t� copi�s de : http://www.cplusplus.com/doc/tutorial/classes2/
	template <class Type>
		class arr {
			//Valeurs membres	
			public:
				Type* pt;  //D�clarer l'array(pointeur) comme public, pour qu'on puisse changer facilement des valeurs depuis l'ext�rieur 
				int nb;  //D�clarer le nombre d'objets de l'array
			//Constructeurs	:
				arr<Type>() : nb(0), pt(nullptr) {cout << "\nAttention: cet objet arr<> est vide (nullptr)";}  //D�faut 
				arr<Type>(Type nxt) : nb(1), pt(nxt) {}  //Une seule valeur
				arr<Type>(Type* nxt, int nbpos) : nb(nbpos), pt(nxt) {}  //Array pr�-existant
	   		//Op�rateur d'acc�s : []
			   Type operator[] (int pos) {
			   		return(pt[pos]);
			   }			
		};	

//------------------------------------------------------------------------------------------------------------------------------------------------------
//4) �crire la fonction lire()
lire(arr<canal>& canaux, int canpos, fen& base, memoire& mem) {
	//Updater le "next time"
	canaux.pt[canpos].nxtt += canaux.pt[canpos].delay;
	//Interpr�ter les "codes sp�ciaux" (�...�)
	if(canaux.pt[canpos].txt[0]=='�'){		
		//D�terminer la longueur du code sp�cial
			int CodeSpecialLong = CodeSpecialLongueur(canaux.pt[canpos].txt);			
		//Lire le code sp�cial		
			if(canaux.pt[canpos].txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause � la lecture		
				double val = CodeSpecialExtractDouble(canaux.pt[canpos].txt,CodeSpecialLong);       //Extraire le temps que durera la pause
				canaux.pt[canpos].nxtt += round(val * canaux.pt[canpos].vit);                    //Ajouter le temps d'attente        //round() est n�cessaire pour arrondir correctement					
			} else if(canaux.pt[canpos].txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = CodeSpecialExtractDouble(canaux.pt[canpos].txt,CodeSpecialLong);       //Extraire la nouvelle vitesse
				canaux.pt[canpos].vit = val;
			}  //EN AJOUTER UN (code sp�cial) POUR PLACER LE CURSEUR � LA FIN DE LA CONSOLE	
		//Effacer le code sp�cial du canal
		canaux.pt[canpos].txt.supprim(CodeSpecialLong);                 
	} else {  //Interpr�ter le reste des caract�res (pas des codes sp�ciaux)
		//Dealer avec la situation o� on a � sauter une ligne (cr�er les lignes suppl�mentaires et updater les diverses positions)
			bool jump = false;
			if(canaux.pt[canpos].txt[0]=='\n'|canaux.pt[canpos].posx>=base.charx-1) jump = true;     //base.charx - 1 ; car c'est en integer, et canaux.pt[canpos].posx commence � 0!
			if(jump) {	
				//Sauter une ligne dans la m�moire
				for(int countx = canaux.pt[canpos].posx + 1; countx < base.charx ; countx++) mem.souvenir[countx][canaux.pt[canpos].posy] = ' ';     //Effacer le reste de la ligne avec des espaces    
				mem.newline(canaux.pt[canpos].posy);                     //Introduit une nouvelle ligne � la suite de la position qui lui est fournie	
				//Updater le correctif de d�calage de la console par rapport � la m�moire
					if(base.refoule) base.consy++; else if(mem.frontline>base.chary) {base.refoule = true; base.consy++;} 					
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore satur�e: on pousse vers le bas!
						if(canaux.pt[canpos].posy==mem.frontline-1) {               //Si le canal g�re la derni�re ligne de la console, c'est plus simple    //-1 : � cause de [0]		
							if(canaux.pt[canpos].posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-m�me!   //-1 : � cause de [0]
						} else {                             //S'il y a d'autres lignes � repousser vers le bas
							if(canaux.pt[canpos].posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-m�me!   //-1 : � cause de [0]
							
							
							
								//C'est le bout qui blesse!
							
							//R�-�crire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,canaux.pt[canpos].posy-base.consy + 2);  //Mettre le curseur au d�but de la reconstruction
								for(int county = canaux.pt[canpos].posy + 2 ; county <= mem.frontline ; county++) {    // + 2, parce que la m�moire a d�j� �t� updat�e
									for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
				
						
						
						
						
						
					} else {                         //La console est satur�e: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")
							curspos(canaux.pt[canpos].posy-base.consy,0); for(int countx = 0; countx < base.charx ; countx++) out(' '); 					
						//Tout r�-�crire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county < canaux.pt[canpos].posy; county++){             //base.consy : facteur de d�calage de la console
										//V�RIFIER L'INITIATION DE COUNTY: �A SEMBLE UN BEL ADON QUE base.consy, UN "count" EN INTEGER SIMPLE,
										//S'EMBO�TE PARFAITEMENT AVEC L'INDEXATION QUI COMMENCE � 0!
								for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}	
				//Updater les positions dans les autres canaux    //Parce que leur position dans la m�moire a boug� //la position dans la console est quant � elle g�r�e par base.consy
				for(int countcan = 0 ; countcan < canaux.nb ; countcan++) {
					if(countcan==canpos) continue;        
					if(canaux.pt[countcan].posy > canaux.pt[canpos].posy) canaux.pt[countcan].posy++;         //la m�moire refoule toujours vers le bas!
				}            	
				//Updater les positions dans le canal actuel
				if(canaux.pt[canpos].txt[0]=='\n') {canaux.pt[canpos].posx = -1;} else canaux.pt[canpos].posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
				canaux.pt[canpos].posy++;																   //en y 
			} else {canaux.pt[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du charact�re actuel (dans la m�moire)!		
		if(canaux.pt[canpos].txt[0]!='\n') {
			curspos(canaux.pt[canpos].posx,canaux.pt[canpos].posy-base.consy) ; out(canaux.pt[canpos].txt[0]);     //Inscrire dans la console
			mem.souvenir[canaux.pt[canpos].posx][canaux.pt[canpos].posy] = canaux.pt[canpos].txt[0];   //Inscrire dans la m�moire			
		}	
		//Effacer le caract�re du canal
		canaux.pt[canpos].txt.supprim(1);                     	   
	}
	//V�rifier s'il reste toujours du texte � passer dans le canal
	if(canaux.pt[canpos].txt.debut==canaux.pt[canpos].txt.fin) canaux.pt[canpos].actif = false;
}	
					
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unit�s sont en pixels!
       		                                                                //200x200 pixels = 13 lignes; 27 colonnes

	//Cr�er l'objet base, qui contiendra les information sur la fen�tre de base
	fen base(27,13);     //EN CE MOMENT, A LES DIMENSIONS DE 27 COLONNES ET 13 LIGNES (VOIR JEU GRAPHIQUE SIMPLE)
	
	//Cr�er l'objet de m�moire, qui stockera tous les caract�res utilis�s
	memoire mem {27};                   //INITIALISATION DE L'OBJET; V�RIFIER AVEC LES BONNES DIMENSIONS POUR LA FEN�TRE!!!
	

	//Cr�er les canaux utilis�s
	canal can1;
	canal can2;
	
	//Test: changer les d�lais manuellement
	can1.delay = 140;
	can2.delay = 230;
	
	//Test: changer les positions manuellement
	can2.posy = 3;
	mem.frontline = 3;
	
	//Ajouter du texte aux canaux
	string txt0 = "Ceci est du texte! Je dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	string txt1 = "�p1000�Le canal 1 est sooooo boring. Ark.�p1000�\n�p1000�Je suis le canal 2.";
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
		
	//Lire la m�moire, pour voir elle a l'air de quoi	
	Sleep(5000);
	curspos(0,0);
	for(int posy=0; posy<base.chary; posy++){
		for(int posx=0; posx<base.charx; posx++) cout << mem.souvenir[posx][posy];
	}	
				//Bon, clairement que la m�moire ne va pas.
							//Bon, l�, j'ai r�ussi � arranger la m�moire.
									//Suffisait, dans le nextline, de se rendre � emptypos au lieu de emptypos + 1 (je n'ai pas pens� aux maths impliqu�s encore).
				//Maintenant, il reste � arranger l'affichage dans la console. C'est lui qui tire de la patte.		

						//Done. Fallait changer �a: for(int county = canaux.pt[canpos].posy + 3 ; county < mem.frontline ; county++) {    // + 2, parce que la m�moire a d�j� �t� updat�e
										//Pour �a:  for(int county = canaux.pt[canpos].posy + 2 ; county <= mem.frontline ; county++) {    // + 2, parce que la m�moire a d�j� �t� updat�e


}		




