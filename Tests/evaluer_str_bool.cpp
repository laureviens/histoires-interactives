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
	2019-06-22:
				En passant: Quand on active un canal, ou qu'on le reset, va falloir resetter son nxtt (timer) aussi. Bien y penser.
*/

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entr�es/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contr�le du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //N�cessaire pour la taille de la fen�tre: informe qu'on est sur Windows 2000 ou plus r�cent
#include <windows.h>           //N�cessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>            //N�cessaire pour savoir la position du curseur sur Windows
#include <winuser.h>		   //N�cessaire pour savoir la position du curseur sur Windows
#include <conio.h>             //N�cessaire pour enregistrer les inputs du clavier
#include <io.h>				   //N�cessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>			   //N�cessaire pour d�crypter les accents en unicode
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
		   char& operator[] (int pos) {return(pt[debut + pos]);}
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
		   void ajout (string nxt) {
		   		if(fin + nxt.length() < nb) {      //Pas besoin de r�-allouer la m�moire
		   			int nbnxt = nxt.length();
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt[posnxt];   
					 fin+=nwend;
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
		   void ajout (StringAsVect nxt) {
		   		if(fin + nxt.nb < nb) {      //Pas besoin de r�-allouer la m�moire
		   			int nbnxt = nxt.nb;
		   			int nwend = fin + nbnxt; 
					int pos = fin; for(int posnxt=0; posnxt<nbnxt; posnxt++) pt[pos++] = nxt[posnxt];   
					 fin+=nwend;
				} else {                //Besoin de r�-allouer
					int nbnxt = nxt.nb;    
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
		//Op�rateur de modification : suppression          //"Supprime" le nombre de positions en right-hand AU D�BUT des valeurs d�j� contenues
			void suppression (int nb) {
				if(nb > fin-debut) debut = fin; else debut+=nb; 
				longueur--;
			}
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
				StaticVect<Type,Taille> operator = (const StaticVect<Type,Taille>& nxt) {
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
						//StaticVect<Type,Taille> returnvect (*this);
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
		WORD code;                                            //Voir la biblioth�que pour la l�gende
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

//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Classes-contenantes sp�cialis�es (canaux et autres)

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
			StaticVect<char,200> commande;          	//Phrase que contient le buffer
			int inputpos;                   //Position d'indexation du prochain caract�re    == StaticVect.fin? Non! Car �a peut bouger!
			int inputlong;                  //Nombre de caract�res total de la commande actuelle (0 : inputpos = 0)   //== StaticVect.fin - StaticVect.debut
			bool accepted;                  //Flag concernant la derni�re commande; utile pour l'affichage visuel
			bool busy;						//Flag concernant la derni�re commande; utile pour l'affichage visuel
		//Constructeur par d�faut
			input() : inputpos(0), inputlong(0), accepted(false), busy(false) {}
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

	//vii) classe : booleval ; contient l'expression � �valuer (la plus simple) ; constructeur transforme les noms de "livre" en position d'indexation
	class booleval {
		//Valeurs membres
		public:
			int rayonpos;   		//Position d'indexation de la "famille" de l'argument compar� � gauche					
			int livrepos;			//Position d'indexation de l'argument compar� � gauche, � l'int�rieur de sa "famille"
			int boolval; int intval;
			int constbool; int constint;      //TRUE si les valeurs sont bool�ennes ou int, � la place d'�valu�es.
		//Constructeur
		template<int Taille>
		booleval(StaticVect<char,Taille> exp, bibliotheque& biblio) : constbool(false), constint(false) {
			
			
			

			
						
			
			
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
			
						
					//DEGBUUGGG
					out("\n\nbooleval exp  : "); out(exp);
					out("\nValeur que �a donne : "); out(this->eval(biblio));
					//DEGBUUGG
					
			
			
			
		}
		//Fonction d'acc�s : eval()	
		int eval(bibliotheque& biblio) {if(constbool) return(boolval); else if(constint) return(intval); else return(biblio.acces(rayonpos,livrepos));}	
	};	

	//viii) classe : booloper ; contient les op�rations d'expressions bool�ennes �valuables
	class booloper {
		//Valeurs membres
		public:
			char operateur;      	//Op�rateur
			booloper* LHcompos;
			booloper* RHcompos;
			booleval* LHsimple;
			booleval* RHsimple;
			bool Lcompos; bool Rcompos;				//TRUE si les valeurs sont composites
		//Constructeur
		template<int Taille>
		booloper(StaticVect<char,Taille> exp, bibliotheque& biblio) : Lcompos(false), Rcompos(false) {
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
			
			
			
						
			//DEBUGGGG
			out("\n\nOp�rateur : \""); out(operateur); out("\"");
			out("\nBooloper exp : "); out(exp);
			out("\nBooloper LH : "); out(LH);
			out("\nBooloper RH : "); out(RH);
			//DEBUGGG
			
			
					
			
			
			
			
			//Assigner les valeurs aux membres
			if(Lcompos) {LHcompos = new booloper (LH,biblio); LHsimple = nullptr;} else {LHsimple = new booleval(LH,biblio); LHcompos = nullptr;}
			if(operateur!=' ') {if(Rcompos) {RHcompos = new booloper (RH,biblio); RHsimple = nullptr;} else {RHsimple = new booleval(RH,biblio); RHcompos = nullptr;}}
		}			
		//Fonction d'acc�s : eval()				
		bool eval(bibliotheque& biblio) {
			
			
			
			
			//DEBUGGG
			//out("\nBoolopereval LH = "); if(!Lcompos) out(LHsimple->eval(biblio)); else out(LHcompos->eval(biblio));
			//out("\nBoolopereval RH = "); if(!Rcompos) out(RHsimple->eval(biblio)); else out(RHcompos->eval(biblio));
			//DEBUGG
			
						
			
			
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
			booloper* LH;
			booloper* RH;
			bool constbool;			   //TRUE si l'argument � gauche doit �tre compar� � un bool�en implicite
			bool boolval;		
		//Constructeur ;
		template<int Taille>
		boolcompar(StaticVect<char,Taille>& exp, bibliotheque& biblio) : constbool(false), boolval(0) {
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
			
						
			
			
						
			//DEBUGGGG
			out("\n\nComparateur : \""); out(comparateur); out("\"");
			out("\nconstbool : "); out(constbool);
			out("\nboolval : "); out(boolval);
			out("\nBoolcompar exp : "); out(exp);
			//DEBUGGG
			
			
			
			
		
			
			//Cr�er les objets booloper
			LH = new booloper(exp.intervalle(0,poscomparateur),biblio);
			if(!constbool){
				if(comparateur=='='||comparateur=='!'||comparateur=='�'||comparateur=='�') RH = new booloper(exp.intervalle(poscomparateur+2,exp.longueur),biblio); else RH = new booloper(exp.intervalle(poscomparateur+1,exp.longueur),biblio);	
			}			
		}
		//Fonction d'acc�s : eval
		bool eval(bibliotheque& biblio) {
			
			
			//DEBUGGG
			out("\n\nBoolcompareval LH = "); out(LH->eval(biblio));
			if(!constbool) {out("\nBoolcompareval RH = "); out(RH->eval(biblio));}
			//DEBUGG
			
			
			
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
			boolcompar* LHsimple; boolcompos* LHcompos;    //PROBL�ME!!! UNE CLASSE NE PEUT PAS AVOIR UN MEMBRE DU M�ME TYPE QU'ELLE! SINON L'INITIALISATION EST R�CURSIVE + INFINIE!
			boolcompar* RHsimple; boolcompos* RHcompos; 			//SEULE MANI�RE DE LE R�GLER EST D'EN FAIRE DES POINTEURS, ET D'UTILISER LA M�MOIRE DYNAMIQUE!
			bool Lcompos; bool Rcompos;	
		//Constructeur
		template<int Taille>		
		boolcompos (StaticVect<char,Taille>& exp, bibliotheque& biblio) : Lcompos(false), Rcompos(false)	{    //false : valeurs par d�faut qui pourront changer � l'int�rieur du constructeur
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
			
			//DEBUGGG	
			out("\nCompositeur : \""); out(compositeur); out("\"");
			out("\nboolcompos exp : "); out(exp);
			out("\nboolcompos LH : "); out(LH);
			out("\nboolcompos RH : "); out(RH);
			//DEBUGGG			
			
			
			//Assigner les valeurs aux membres
			if(Lcompos) {LHcompos = new boolcompos (LH,biblio); LHsimple = nullptr;} else {LHsimple = new boolcompar(LH,biblio); LHcompos = nullptr;}
			if(compositeur!='!'&&compositeur!=' ') {if(Rcompos) {RHcompos = new boolcompos (RH,biblio); RHsimple = nullptr;} else {RHsimple = new boolcompar(RH,biblio); RHcompos = nullptr;}}		
		}
		//Fonction d'acc�s : eval
		bool eval(bibliotheque& biblio) {
			
			
			
			
			//DEBUGGG
			//out("\n\nCompositeur : "); out(compositeur);
			//if(Lcompos) {out("\nBoolcomposeval LH = "); out(LHcompos->eval(biblio));} else {out("\nBoolcomposeval LH = "); out(LHsimple->eval(biblio));}
			//if(compositeur=='&'||compositeur=='|') {if(Rcompos){out("\nBoolcomposeval RH = "); out(RHcompos->eval(biblio));} else {out("\nBoolcomposeval RH = "); out(RHsimple->eval(biblio));}}
			//DEBUGG
			
			
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


//xi) classe : mots ; permet le stockage de "mots de passe" pour les commandes, � chercher dans le USERINPT

	//??????
				//Quelle forme?
									//Utiliser des strings, ou une structure plus directe, genre mots.cluster= {"jambon","porc","bacon"} ???

	
/*	
	//xii) classe : chainon ; permet le stockage du texte et des conditions d'apparition
	class chainon {
		//Membres
		public:
			bool pret;
			bool fini;
			StaticVect<boolcompos,30> cond;
			StaticVect<staticvect<int,10>,10> enchainement;   //int r�f�re aux positions des mailles         
			StaticVect<booloper,10> enchaineprob;        	  //Avec le m�me ordre d'indexation que encha�nement
								//Pour l'instant, peuvent tr�s bien �tre fixes
			StaticVect<string,10> maille;
			StaticVect<???,10> commandes                             //PROBABLEMENT FAIRE UNE STRUCTURE PERSONALIS�E AVEC & ET | ET !=   ?????
			StaticVect<string,10> codespeciauxdebut;
			StaticVect<string,10> codespeciauxfin;
			StaticVect<int,10> override;
			StaticVect<string,10> overridename;
			int canal;
			string canalname;
	};
*/



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
	int CodeSpecialExtractInt(StringAsVect& str, int longueur){
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
			curspos(inp.inputlong,base.limtxty); for(int pos=inp.inputlong; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
		} else {
			curspos(inp.inputlong,base.limtxty); for(int pos=inp.inputlong; pos < inpecho.commande.fin; pos++) out(' ');			
		}
		chgcol(base.couleur);                       //Revenir � la couleur de base	
		inpecho.nxtt += abs(inpecho.clignote[0]);        //Updater le "next time"
		inpecho.clignote.suppression(1);            //Passer � la prochaine instruction
		if(inpecho.clignote.debut==inpecho.clignote.fin) inpecho.actif = false;			//V�rifier s'il reste toujours du stock � passer dans le canal	
		}	
	
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//5) Fonction LireCanal()
template<int Taille>
void LireCanal(StaticVect<canal,Taille>& canaux, int canpos, fen& base, memoire& mem) {
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
		canaux.pt[canpos].txt.suppression(CodeSpecialLong);                 
	} else {  //Interpr�ter le reste des caract�res (pas des codes sp�ciaux)
		//Dealer avec la situation o� on a � sauter une ligne (cr�er les lignes suppl�mentaires et updater les diverses positions)
			bool jump = false;
			if(canaux.pt[canpos].txt[0]=='\n'|canaux.pt[canpos].posx>=base.limtxtx-1) jump = true;     //base.limtxtx - 1 ; car c'est en integer, et canaux.pt[canpos].posx commence � 0!
			if(jump) {	
				mem.newline(canaux.pt[canpos].posy);                     //Introduit une nouvelle ligne � la suite de la position qui lui est fournie	
				//Updater le correctif de d�calage de la console par rapport � la m�moire
					if(base.refoule) base.consy++; else if(mem.frontline>base.limtxty) {base.refoule = true; base.consy++;} 						
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore satur�e: on pousse vers le bas!
						if(canaux.pt[canpos].posy!=mem.frontline-1) {                             //S'il y a d'autres lignes � repousser vers le bas
							//R�-�crire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,canaux.pt[canpos].posy+1);  //Mettre le curseur au d�but de la reconstruction
								for(int county = canaux.pt[canpos].posy + 1 ; county <= mem.frontline ; county++) {   
									for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est satur�e: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")
							curspos(0,canaux.pt[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
						//Tout r�-�crire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county <= canaux.pt[canpos].posy; county++){             //base.consy : facteur de d�calage de la console
								for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}	
				//Updater les positions dans les autres canaux    //Parce que leur position dans la m�moire a boug� //la position dans la console est quant � elle g�r�e par base.consy
				for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {
					if(countcan==canpos) continue;                                    //la m�moire refoule toujours vers le bas!
					if(canaux.pt[countcan].posy > canaux.pt[canpos].posy) canaux.pt[countcan].posy++; else if(canaux.pt[countcan].posy == canaux.pt[canpos].posy) canaux.pt[countcan].posy+=2;
				}       // == : Si deux canaux se situe sur la m�me ligne, le canal qui change de ligne va couper l'autre en deux, et le renvoyer apr�s sa propre ligne.    	        
				//Updater les positions dans le canal actuel
				if(canaux.pt[canpos].txt[0]=='\n') {canaux.pt[canpos].posx = -1;} else canaux.pt[canpos].posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
				canaux.pt[canpos].posy++;	  																					   //en y 		
			} else {canaux.pt[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du charact�re actuel (dans la m�moire)!		
		if(canaux.pt[canpos].txt[0]!='\n') {
			curspos(canaux.pt[canpos].posx,canaux.pt[canpos].posy-base.consy) ; out(canaux.pt[canpos].txt[0]);     //Inscrire dans la console
			mem.souvenir[canaux.pt[canpos].posx][canaux.pt[canpos].posy] = canaux.pt[canpos].txt[0];   //Inscrire dans la m�moire			
		}	
		canaux.pt[canpos].txt.suppression(1);       //Effacer le caract�re du canal     	   
	}
	if(canaux.pt[canpos].txt.debut==canaux.pt[canpos].txt.fin) canaux.pt[canpos].actif = false;			//V�rifier s'il reste toujours du texte � passer dans le canal
}	
					
//------------------------------------------------------------------------------------------------------------------------------------------------------
//6) Fonction UserInput()
void UserInput(input& inp, inputecho& inpecho, const fen& base) {
	if(_kbhit()){
	//i) Capter la lettre tap�e
	bool enter = false;
	char key = _getch();                  		//Enregistrer quelle touche a �t� press�e
			if (key == 0 || key == -32 || key == 224) {      //La valeur est sp�ciale: elle n�cessite de la r�-examiner
				key = _getch();                              //Examiner une deuxi�me valeur pour identifier
				if(key == 75) {     								 				 //fl�che gauche : reculer dans la commande tap�e 
					if(inp.inputpos!=0) {
						if(inp.inputpos!=inp.inputlong) {
							curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						}          //Remettre en gris la position pr�c�dente
						inp.inputpos--;  
					}
				}
				else if (key == 77) {											 	 //fl�che droite : avancer dans la commande tap�e				
					if(inp.inputpos!=inp.inputlong) {
						curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						inp.inputpos++;		
					}			//Remettre en gris la position pr�c�dente
				} 
				else if (key == 72)  ;  											 //Fl�che du haut   ... Rien ne se passe?
				else if (key == 80)  ;  											 //Fl�che du bas    ... Rien ne se passe?
				else if (key == 83) {                                                //Delete : supprimer un caract�re de la commande actuelle
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
					curspos(0,base.limtxty); out("Vous avez entr� ESC, le programme se ferme donc."); abort(); 
				} else if(key == 13) {												 //Enter : envoyer la commande
					enter = true;
				} else if(key == 8) {                                                //Backspace : supprimer le caract�re pr�c�dent
					if(inp.inputpos!=0) {
						inp.inputpos--; inp.inputlong--;
						inp.commande.supprposition(inp.inputpos);   
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.inputlong; pos++) out(inp.commande[pos]);   
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
					if(inp.inputlong<base.limtxtx-1){
						inp.commande.ajout(key,inp.inputpos);
						inp.inputpos++; inp.inputlong++;
						curspos(inp.inputpos-1,base.limtxty);	                    
						for(int pos=inp.inputpos-1; pos<inp.inputlong; pos++) out(inp.commande[pos]);
						if(inp.inputlong==inpecho.commande.fin) inpecho.actif = false;                   //D�sactiver le canal d'�cho si la commande actuelle le d�passe
					}
						
								//BTW: FAUDRAIT AUSSI TOUT UN PAN DE CODE POUR G�RER LES COMMANDES TROP LONGUES, POUR FAIRE RECULER LE TEXTE
										//Pour l'instant, je restreint l'espace � la largeur de la console, simplement.
							
				}
			}	
		//Remettre la lettre s�lectionn�e en surbrillance
		if(inp.inputpos!=inp.inputlong) {chgcol("blanc"); curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); chgcol(base.couleur);}
			
		//�valuer la commande		
		if(enter) {								//BTW: Faire changer la vitesse/fr�n�sie du clignotage avec la vitesse globale. Tu veux �a plus vite? �a va �tre plus agressant aussi!

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
			inp.inputpos = 0; inp.inputlong = 0; inp.commande.vide();                               //Nettoyer l'objet input			
		}	
	}
}               
         
         
//------------------------------------------------------------------------------------------------------------------------------------------------------
//7) Aire de tests
				
	//Function dummy, pour voir si j'acc�de comme du monde			
	void dummy(int x, int y,bibliotheque& biblio) {
		out(biblio.acces(x,y));
	}				
							
int main(void) {

	//Cr�er la biblioth�que
	bibliotheque biblio;
	biblio.modif(0,0,false);
	out(biblio.acces(0,0));
	out("\n");
		
	
	//Cr�er des conditions ne r�f�rant qu'� des positions de la biblioth�que
	StaticVect<char,30> testStaticVect("!0�0",4);
	boolcompos test(testStaticVect,biblio);

	//�valuer
	if(test.eval(biblio)) out("\n\nTRUE"); else out("\n\nOh non!");
	
	//Cr�er des conditions plus funky
	out("\n\nUn nouveau, maintenant, ");
	StaticVect<char,30> testStaticVect2("3-3==0�0*1&true",16);
	boolcompos test2(testStaticVect2,biblio);	
	
	//�valuer
	if(test2.eval(biblio)) out("\n\nTRUE"); else out("\n\nOh non!");
	
/*
	//Cr�er la biblioth�que
	bibliotheque biblio;
	biblio.modifint(0,0,9);
	
	//Cr�er des conditions ne r�f�rant qu'� des positions de la biblioth�que
	StaticVect<char,30> testStaticVect("0�0<9999&0�0>19",8);
	mevalb test(testStaticVect);

	//�valuer
	test.eval(biblio);
	
	out("\nLHvalue en dehors de la fonction : "); out(biblio.accesint(0,0));
	out("\nLHvalue que j'avais plac� manuellement : 9.'");
	out("\nEt en y allant sans la fonction acc�s? : "); out(biblio.rayonint[0][0]);
	
		//if(test.eval(biblio)) out("true"); else out("\nWHT?");
	//if(biblio.accesint(0,0)) out("\ntrue: ");
	
	
				//ATTENTION!!!  LES BOLL�ENS SONT DIFF�RENTI�S DES int JUSTE PARCE QU'ILS COMMENCENT PAR <f,F,t,T>! C'EST PAS SUPER FIABLE, COMME CLASSIFICATION!
							//(m�ME SI �A VA MARCHER SI JE FAIS ATTENTION)
							
							
				//PROBL�ME! LES VALEURS STOCK�ES DANS BIBLIO SONT PAS BONNES LORSQUE ACC�D�ES � PARTIR DE LA FONCTION �VAL()!
								//TROUVER POURQUOI, ET R�GLER �A!!!!
	out("\nEt avec un dummy?"); dummy(0,0,biblio);							
	out("\nEst-ce que le dummy est constant?"); dummy(0,0,biblio);		//Nope.
						
		//Conclusion: Probablement qu'on acc�de pas au bon pointeur?
	out("\nEt est-ce que l'environnement global est constant? : "); out(biblio.accesint(0,0));
	
			//Right. Les arguments ne sont pas pass�s par r�f�rence. �a doit �tre �a.							

						//Yap. Le dummy est constant (et a raison) seulement quand l'argument est pass� par r�f�rence.
								//NE PAS OUBLIER DE PASSER LES ARGUMENTS PAR R�F�RENCES POUR BIEN AVOIR ACC�S AUX POINTEURS
*/

}								
