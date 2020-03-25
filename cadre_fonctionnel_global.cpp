
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
	2020-01-23:
				Maintenant que la d�mo marche, j'observe que cr�er une nouvelle ligne quand la console est pleine (ce qui implique de r��crire toute
				la fen�tre au complet) prend un peu de temps et cr�e un "mini lag". Il serait peut-�tre b�n�fique de revoir les interactions avec la console
				au complet.
				Puisque le code interne de la console semble n'avoir aucun probl�me avec le changement de ligne "en douceur", je pourrais peut-�tre simplement 
				l'exploiter: laisser la console passer une ligne (avec '\n'), puis simplement r�-�crire la ligne de commandes.
				Je pense que �a aurait �galement l'avantage de laisser explorer toute la m�moire, qui resterait �crire dans la console.
				Rendant donc l'objet "m�moire" un peu obsol�te (non, car si je veux ajouter des effets "bugs", je dois avoir une sauvegarde du texte)?
					Bref, jouer AVEC la console par d�faut, plut�t que contre.
						Contre l'utilisation d'une m�moire (� long terme):
							-Les effets "bugs" peuvent tr�s bien enregistrer la lettre remplac�e, d�j� qu'ils enregistrent sa position et le remplacement
							-Les interruptions (ajout d'une ligne en plein milieu) et les menus "pause" n�cessitent de conna�tre le texte pr�sent dans la console...
								peut �tre soit une m�moire � court terme, soit une fonction pour "aller chercher" le texte de la console
								(les deux sont assez rares et "interrompant" pour que le l�ger lag cr�er ne pose aucun probl�me)
								
								
				//Pour plus d'infos sur les possibilit�s, voir https://docs.microsoft.com/en-us/windows/console/scrolling-a-screen-buffer-s-contents			
								
*/

/*
	2019-07-13:
				Ce qu'il me reste � faire:
					-V�rifier si �a fonctionne comme du monde quand la console est pleine de msn / y'a trop de msn pour la taille de messagerie.
					-En ce moment, pour les commandes mots-cl�s, si on ne met pas de parenth�ses, �a ne marche pas. Messemble dans la fonction de remplissage c'�tait suppos� marcher?
					-Peut-�tre changer la m�moire de "long terme, finie" � "court terme, infinie" en sauvant moins de lignes mais en �crivant par-dessus?
					-Ajouter un menu
					-Retravailler le "menu" de quand la commande est ambig�e, pour la mettre plus en ligne avec le reste des menus
							(� la limite, j'pense s�rieusement � simplement avoir une s�lection de "peser sur ENTER entre des ic�nes" pour �viter les erreurs connes de frappe)
							(genre, c'est suppos� NE PAS ARRIVER, les ambiguit�, si l'histoire est si mal �crite que �a, j'pense que �a va pas d�ranger de perdre un peu) 
							( d' "immersion"  en s�lectionnant un bouton � la place de recopier lettre � lettre un mot. Also, c'est plus facile � coder pour moi.)
											
*/					

/*
	2019-09-04:
				Liste des s�parateurs maison:
					'�' sert � s�parer les codes sp�ciaux du reste dans le texte � lire
					';' sert � s�parer les genres (f�minin;non binaire/neutre;masculin)
					'�' sert � s�parer les segments de texte (mailles) dans la construction d'un motif
					';' sert � s�parer les diff�rents encha�nements
					'-' sert � s�parer les chiffres d'un m�me encha�nement
					';' sert � s�parer les diff�rentes probabilit�s d'encha�nement (pratique mais � logique; consid�rer un changement?)
					Dans les commandes, '|' s�pare les synonymes, '&' s�pare les groupes de mots, "[]" d�note les mots � exclure et "()" s�parent les fa�ons de le dire
					'�' sert � marquer les cellules transparentes dans les dessins (pr�sentement : dans les titres des menus)
*/

/*
	2020-02-22:
				J'ai retrouv� la l�gende pour la couleur:
					FOREGROUND_BLUE 		Text color contains blue.
					FOREGROUND_GREEN 		Text color contains green.
					FOREGROUND_RED 			Text color contains red.
					FOREGROUND_INTENSITY 	Text color is intensified.
					BACKGROUND_BLUE 		Background color contains blue.
					BACKGROUND_GREEN 		Background color contains green.
					BACKGROUND_RED 			Background color contains red.
					BACKGROUND_INTENSITY	Background color is intensified.
			
					// colors are 0=black 1=blue 2=green, 3=aqua, 4=red, 5=pink, 6=yellow, 7=white; et on rajoute une autre couche de 8 couleurs en changeant l'intensit�.  
					// colorattribute = foreground + background * 16
					// to get red text on yellow use 4 + 14*16 = 228
					// light red on yellow would be 12 + 14*16 = 236		
	*/
	
	
/*
	2020-03-08:
	
				De l'info par rapport � jouer avec la fen�tre:
				
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
						
					//Pour conna�tre la taille (en nbr de caract�res) de la plus grande fen�tre possible:	
					COORD WINAPI GetLargestConsoleWindowSize(
					  _In_ HANDLE hConsoleOutput
					);
					
					//Pour modifier la taille (en nbr de caract�res)
					BOOL WINAPI SetConsoleScreenBufferSize(
					  _In_ HANDLE hConsoleOutput,
					  _In_ COORD  dwSize
					);
*/	

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard

#define _USE_MATH_DEFINES		//N�cessaire pour aller chercher la valeur de pi
#include <iostream>   //Pour les entr�es/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contr�le du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //N�cessaire pour la taille de la fen�tre: informe qu'on est sur Windows 2000 ou plus r�cent (??? Optionnel?)
#include <windows.h>			//N�cessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>				//N�cessaire pour savoir la position du curseur sur Windows
#include <winuser.h>			//N�cessaire pour savoir la position du curseur sur Windows
#include <conio.h>				//N�cessaire pour enregistrer les inputs du clavier
#include <io.h>					//N�cessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>				//N�cessaire pour d�crypter les accents en unicode
#include <stdlib.h>				//N�cessaire pour jouer avec des nombres al�atoires  /* srand, rand */

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Fonctions et objets pour interagir avec la console (Attention: s�par� entre Windows et Linux) 	//WINDOWS SEULEMENT EST FAIT!!!

		//1) Fonctions et objets pour interagir avec la console (Attention: s�par� entre Windows et Linux) 	//WINDOWS SEULEMENT EST FAIT!!!		
		
			//i) Classe : consoleobjet ; divers objets permettant de modifier le texte affich� dans la console   	            	//WINDOWS ONLY
			class fenetre {
				//Membres
				private:
					HANDLE TxtConsole;									        //Objet permettant de modifier le texte affich� dans la console 
					COORD CursorPosition;                                     	//Objet permettant de se situer sur la console
					CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;                //Objet permettant de conna�tre la position du curseur dans la console
					CONSOLE_CURSOR_INFO CursorInfo;	                            //Objet permettant de modifier le curseur
					COORD tailleactu;			//Ces deux objets sont n�cessaires pour changer les dimensions de la console
					SMALL_RECT rectactu;		//Ces deux objets sont n�cessaires pour changer les dimensions de la console				
					COORD taillemin;
					COORD taillemax;
				public:
					int limfenx, limfeny;     	//Dimensions de la fen�tre en terme de nombre de caract�res pouvant y �tre contenus
					int milieufenx, milieufeny;	//Point au milieu, ou un caract�re en haut (dans le cas de dimensions paires), de toute la fen�tre
					int limtxtx, limtxty;     	//Dimensions de la portion o� le texte s'affiche en terme de nombre de caract�res pouvant y �tre contenus
					int consy;            	 	//Facteur de d�calement de la console o� appara�t le texte avec la m�moire, o� il est stock�
					bool refoule;          		//Flag pour voir si le facteur de d�calement entre en compte																							
				//Fonctions membres
					//i) Fonction: curspos ; d�placer le curseur sur la console                                                          //WINDOWS ONLY
					void curspos(int x, int y) { 
						CursorPosition.X = x; CursorPosition.Y = y; 
						SetConsoleCursorPosition(TxtConsole,CursorPosition);
					}
					//ii) Fonction : chgcol ; change la couleur du texte � entrer                        		                                   //WINDOWS ONLY
					void chgcol(int txtcol, int bgcol) {
						SetConsoleTextAttribute(TxtConsole, txtcol + 16*bgcol);		//Voir l'entr�e du 2020-02-22 pour la l�gende!
					}
					//iii) Fonction : modifdim ; change les dimensions de la fen�tre, un caract�re � la fois
					void modifdim(bool plus, bool ligne) {
						if(ligne) {
							if(plus) {tailleactu.Y++; rectactu.Bottom++;} else if(tailleactu.Y!=taillemin.Y) {tailleactu.Y--; rectactu.Bottom--;}
						} else if(plus) {tailleactu.X++; rectactu.Right++;} else if(tailleactu.X!=taillemin.X) {tailleactu.X--; rectactu.Right--;}
					    SetConsoleWindowInfo(TxtConsole, TRUE, &rectactu);
						SetConsoleScreenBufferSize(TxtConsole,tailleactu);
						GetConsoleScreenBufferInfo(TxtConsole, &ScreenBufferInfo);           				//Acc�der � la taille de la console
						limfenx = ScreenBufferInfo.srWindow.Right + 1; limfeny = ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations
						milieufenx = round(limfenx/2); milieufeny = round(limfeny/2); limtxtx = limfenx; limtxty = limfeny - 1;				
					}
					//iv) Fonction : dimmin ; d�finit les dimensions minimales de la fen�tre (� faire en fonction du background du menu principal, genre : le plus petit dessin acceptable)
					void dimmin(int x, int y) {taillemin.X = x; taillemin.Y = y;}
					//v) Fonction : dimdef ; d�finit les dimensions par d�faut de la fen�tre (� faire en fonction du bg du menu principal, genre : le plus beau dessin)
					void dimdef(int x, int y) {tailleactu.X = x; tailleactu.Y = y; rectactu.Right = x-1; rectactu.Bottom = y-1;}					
					//vi) Fonction : defaultwin ; initie les param�tres et la fen�tre de base avec Windows
					void defaultwin() {
						//Faire les choses de base	
						TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);										//Aller chercher la bon objet pour la fen�tre actuelle
			    		_setmode(_fileno(stdout), _O_U16TEXT);												//Permettre l'affichage de l'UNICODE         					
						//Obtenir les tailles de r�f�rence
						taillemax = GetLargestConsoleWindowSize(TxtConsole);	//Taille maximale d�termin�e objectivement par les limites de la console
						//Faire appara�tre une fen�tre de la taille par d�faut
					    SetConsoleWindowInfo(TxtConsole, TRUE, &rectactu);
						SetConsoleScreenBufferSize(TxtConsole,tailleactu);					
						//D�terminer les limites de la fen�tre actuelle
						GetConsoleScreenBufferInfo(TxtConsole, &ScreenBufferInfo);           				//Acc�der � la taille de la console
						limfenx = ScreenBufferInfo.srWindow.Right + 1; limfeny = ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations
						milieufenx = round(limfenx/2); milieufeny = round(limfeny/2); limtxtx = limfenx; limtxty = limfeny - 1;
						//Cacher le curseur (ce qui clignote)
						CursorInfo.bVisible = false; SetConsoleCursorInfo(TxtConsole,&CursorInfo);
					}
				//Constructeurs
					//Constructeur par d�faut
					fenetre() {tailleactu.X = 40; tailleactu.Y = 20; rectactu.Left = 0; rectactu.Top = 0; rectactu.Right = 40-1; rectactu.Bottom = 20-1;}		//Taille par d�faut arbitraire; peut �tre chang�e avec la fonction dimdef()
			};

		

//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) Classes et fonctions g�n�rales

	//i) Classes-contenantes	----------------------------------------------------------------------
	
		//a) classe : StaticVect ; sauvegarde un array "semi-dynamique", o� la m�moire utilis�e est fixe, mais les fonctionnalit�s sont les m�mes que StringAsVect.
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
					bool ajout(Type nxt, int pos) {			//Ajoute l'entr�e � une position pr�cise
						if(fin+1 <= taille) {
							for(int ptpos = fin; ptpos>pos; ptpos--) pt[ptpos] = pt[ptpos-1];
							pt[pos] = nxt; fin++; longueur++;
							return(true);
						} else return(false);
					}
					bool ajout(Type* nxt, int nb) {			//Ajoute un array � la suite du StaticVect
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
				//Fonction d'"ajout" : ajoutvide           //Sert � noter le passage � une entr�e sup�rieure sans ajouter directement un �l�ment (ex: dans StaticVect<TAILLE2,StaticVect<TAILLE1,TYPE>>)			
					void ajoutvide (void) {fin++; longueur++;}
				};		
			
	//ii) Fonctions de conversion	----------------------------------------------------------------------
		
		//a) Fonction : majuscule ; retourne le char, mais en majuscule
		char majuscule(char chr) {
			if(chr=='a') return('A'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else{
			} if(chr=='b') return('B'); else if(chr=='c') return('C'); else if(chr=='�') return('�'); else if(chr=='d') return('D'); else{
			} if(chr=='e') return('E'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else{
			} if(chr=='f') return('F'); else if(chr=='g') return('G'); else if(chr=='h') return('H'); else if(chr=='i') return('I'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else {
			} if(chr=='j') return('J'); else if(chr=='k') return('K'); else if(chr=='l') return('L'); else if(chr=='m') return('M'); else{
			} if(chr=='n') return('N'); else if(chr=='o') return('O'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else{	
			} if(chr=='p') return('P'); else if(chr=='q') return('Q'); else if(chr=='r') return('R'); else if(chr=='s') return('S'); else{
			} if(chr=='t') return('T'); else if(chr=='u') return('U'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else if(chr=='�') return('�'); else{		
			} if(chr=='v') return('V'); else if(chr=='w') return('W'); else if(chr=='x') return('X'); else if(chr=='y') return('Y'); else{
			} if(chr=='z') return('Z'); else return(chr);
		}
				
		//b) Fonction : strintervalle ; retourne un string
		string strintervalle(string str, int deb, int fin) {
			string nwstr;
			for(int pos=deb;pos<=fin;pos++) nwstr+=str[pos];          
			return(nwstr);
		}			
				
		//c) Fonction : CodeSpecialLong ; retourne la longueur d'un code sp�cial (les deux '�' �tant compris)
		int CodeSpecialLongueur(string str){
			int longueur = 1;               //Initier l'objet � retourner
			bool fini = false; int pos = 0;
			int strnb = str.length();
			while(!fini&&pos<strnb) {
				longueur++; pos++;
				if(str[pos]=='�') fini = true;
			}              
			return(longueur);		
		}
		int CodeSpecialLongueurInv(string str){								//Part de la fin du string (pour les msn qui reculent)
			int longueur = 1;               //Initier l'objet � retourner
			bool fini = false; int pos = str.length()-1;
			while(!fini&&pos>0) {
				longueur++; pos--;
				if(str[pos]=='�') fini = true;
			}              
			return(longueur);		
		}
	
		//d) Fonction : CodeSpecialExtract ; extrait une valeur num�rique d'une suite de caract�res encadr�s par '�' (pour extraire les codes sp�ciaux)
		double CodeSpecialExtractDouble(string str, int longueur){
			string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres (2X'�' + 1 identifiant en char)
			for(int pos=2; pos<longueur-1; pos++) nbonly += str[pos];    //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire (identifiant en char)	
			return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
		}		
		int CodeSpecialExtractInt(string str, int longueur){
			string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres (2X'�' + 1 identifiant en char)
			for(int pos=2; pos<longueur-1; pos++) nbonly += str[pos];    //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire (identifiant en char)	
			return(stoi(nbonly));           //La fonction stoi convertit les strings en int (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
		}					
		
		//e) Fonction : out ; affiche le caract�re dans la console			//Change des char en unicode, genre, un peu?
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
		template<int Taille>
		void out(StaticVect<char,Taille> phrase){
			for(int pos=0; pos<phrase.longueur; pos++){
				out(phrase[pos]);
			}
		}
		void out(int chiffre) {out(to_string(chiffre));}
		void out(unsigned chiffre) {out(to_string(chiffre));}
		void out(double chiffre) {out(to_string(chiffre));}
								
		//f) Fonction : strtobool ; interpr�te un string pour renvoyer un bool�en (similaire � stoi() ou stod() )
		bool strtobool(string str) {
			if(str[0]=='0') {return(false);
			} else if(str[0]=='f'&&str[1]=='a'&&str[2]=='l'&&str[3]=='s'&&str[4]=='e') {return(false);
			} else if(str[0]=='F'&&str[1]=='A'&&str[2]=='L'&&str[3]=='S'&&str[4]=='e') {return(false);
			} else if(str[0]=='1') {return(true);
			} else if(str[0]=='t'&&str[1]=='r'&&str[2]=='u'&&str[3]=='e') {return(true);
			} else if(str[0]=='T'&&str[1]=='R'&&str[2]=='U'&&str[3]=='E') {return(true);
			} else {out("\n\nTentative d'�valuer \""); for(int pos = 0; pos<str.length(); pos++) {out(str[pos]);} out("\" comme un bool�en."); abort();}
		}									
								
		//g) Fonction : ColNameFind ; trouve une (la premi�re rencontr�e) position d'indexation dans un StaticVect<string,Taille> qui correspond exactement � un string
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
			//Failsafe: Si aucune it�ration de "str" n'a �t� trouv�e
			out("Aucune it�ration de \""); out(str); out("\" n'a �t� trouv�e dans {");
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
			//Failsafe: Si aucune it�ration de "str" n'a �t� trouv�e
			out("Aucune it�ration de \""); out(str); out("\" n'a �t� trouv�e dans {");
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
			
		//j) Fonction : floor ; retourne la valeur arrondie � l'entier inf�rieur
		//int floor(double val){
		//	if(val==round(val)) return(round(val)); else return(round(val)-1);
		//}

		//j) Fonction : ceiling ; retourne la valeur arrondie � l'entier sup�rieur
		int ceiling(double val){
			if(val==floor(val)) return(val); else return(floor(val)+1);
		}
								
	//iii) Fonctions et classe de manipulation du temps	----------------------------------------------------------------------
	
		//a) Classe : horloge ; permet de stocker le temps depuis le d�but du programme
		class horloge {
			private:
				unsigned debutt;
			public:
				unsigned currentt;	 
			//Constructeur
			horloge() {debutt = std::chrono::duration_cast< std::chrono::milliseconds >(
		    	std::chrono::system_clock::now().time_since_epoch()
				).count(); currentt = 0;}
			//Fonction de modification : reglerheure ; r�-initie currentt
			void reglerheure() {currentt = std::chrono::duration_cast< std::chrono::milliseconds >(
		    	std::chrono::system_clock::now().time_since_epoch()
				).count() - debutt;}
			//Fonction d'acc�s
			int getdebutt() {return(debutt);}	
			//Fonctions de statis
			void stop(int val);
			void egrener(string str, int delay);
		};
	
		//b) Fonction : stop ; arr�te manuellement l'ex�cution d'un programme. � utiliser seulement dans un menu!
		void horloge::stop(int val) {
			int targett = currentt + val;
			while(TRUE) {this->reglerheure(); if(currentt>targett) return;}
		}
	
		//c) Fonction : egrener ; fait appara�tre le texte manuellement, comme s'il �tait dans un canal. � utiliser seulement dans un menu!
		void horloge::egrener(string str, int delay) {
			for(int pos=0; pos<str.length(); pos++) {out(str[pos]); stop(delay);}
		}

	//iv) Classes et fonctions de randomisation	----------------------------------------------------------------------		
	
		//a) Fonction : randseed ; initie le g�n�rateur de nombre al�atoire rand() avec le "time since epoch" (1er janvier 1970), en millisecondes
		void randseed(horloge clock) {
			srand(abs(clock.getdebutt() -	1583418000));		//La soustraction ici est simplement le temps � l'heure o� j'�cris cette ligne; pour �tre s�re que �a bug pas si le nombre est trop grand
		}
	  
		//b) Fonction : randunif ; retourne un integer entre [min, max] (les valeurs sont comprises; "inclusivement")
		int randunif(int min, int max) {
			return(rand() % (max+1) + min);
		}

		//c) Classe : normdist ; construit et conserve une distribution de probabilit�s approxim�e, afin d'en tirer des nombres al�atoires � l'aide seulement de la fonction rand()
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
					normdist() {		//Par d�faut; permet de construire la distribution de probabilit�s
						//Donner une probabilit� � chaque valeur de 'x' (les 'x' sont les positions de l'array "prob")
							//Je me base sur la d�finition de la distribution normale pour faire �a, qui va un peu comme suit:
							// f(x) = 1/(sd*(2*pi)^(1/2)) * e^((-1/2)*((x-mean)/sd)^2)
							//Je multiplie les probabilit�s donn�es ici par la r�solution, pour n'avoir que des integer de taille sensible
						double yconst = 1/(originsd*pow(2*M_PI,1/2));		//M_PI, c'est la valeur de pi
						sumprob = 0;
						for(int x=0; x<range; x++){
							prob[x] = round(yconst * exp(-pow(x-originmean,2)/pow(2*originsd,2)) * resolution);
							sumprob += prob[x];				//J'en profite pour aller chercher le total exact des probabilit�s, qui devrait tendre vers "r�solution"
						}
					}						
					//Fonction d'acc�s : randnormapprox ; retourne un integer al�atoire respectant une distribution normale de (mean,sd)
					int randnormapprox(int mean, int sd){						
						int randprob = randunif(1,sumprob);
						int sumprobnow = 0; int x = -1;
						while(sumprobnow<randprob) sumprobnow += prob[++x];
						//Maintenant, on a obtenu un nombre al�atoire 'x' gr�ce � une distribution normale de mean = originmean et sd = originsd						
						return(round((x-originmean)*sd/originsd + mean));
					}
			};
		
//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Classes-contenantes sp�cialis�es (canaux et autres)

	//i) Classe de sauvegarde des informations	----------------------------------------------------------------------		

		//a) classe : bibliotheque ; permet de stocker tous les status (int) modifiables
		class bibliotheque {
			//Valeurs membres
			public:
				static const int nbrayons = 5;		//static: un seul membre partag� par tous les objets de cette classe; const: ce nombre ne chagera pas (d�fini � la compilation)
				static const int nblivres = 30;
				StaticVect<StaticVect<int,nblivres>,nbrayons> rayon;	//c'est le r�pertoire de valeurs qui va �tre utilis�
				StaticVect<string,nbrayons> nomrayon; StaticVect<StaticVect<string,nblivres>,nbrayons> nomlivre;     //Liste des noms des rayons et des livres
				static const int nbrayonsfixes = 3;		//Nombre de rayons dont le nom a d�j� �t� fix� (rayons obligatoires)
				static const int posmenu = 0;
				static const int poscouleur = 1;
				static const int posgenre = 2;
			//Constructeur par d�faut
			bibliotheque() {
				//Mettre tous les livres � 0 par d�faut
				for(int countray=0; countray<nbrayons; countray++) for(int countli=0; countli<nblivres; countli++) rayon[countray][countli] = 0;
				//Ajouter le rayon des menus			//Contient le status actuel des menus					
				rayon.ajoutvide();	
				nomrayon.ajout("menu");
					rayon[posmenu].ajoutvide();	nomlivre[posmenu].ajout("");
				//Ajouter le rayon des couleurs			//Contient les diff�rentes couleurs de la console
				rayon.ajoutvide();	
				nomrayon.ajout("couleur");
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("actutxt"); this->modif("couleur","actutxt",7);			//Blanc fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("actubg"); this->modif("couleur","actubg",0);				//Noir fonc�			
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("cantxt"); this->modif("couleur","cantxt",7);				//Blanc fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("canbg"); this->modif("couleur","canbg",0);				//Noir fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("msntxt"); this->modif("couleur","msntxt",15);			//Blanc clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("msnbg"); this->modif("couleur","msnbg",0);				//Noir fonc�	
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commtxt"); this->modif("couleur","commtxt",8);			//Gris clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbg"); this->modif("couleur","commbg",0);				//Noir fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbontxt"); this->modif("couleur","commbontxt",7);		//Blanc fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbonbg"); this->modif("couleur","commbonbg",0);		//Noir fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbusytxt"); this->modif("couleur","commbusytxt",4);	//Rouge fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commbusybg"); this->modif("couleur","commbusybg",0);		//Noir fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commmauvtxt"); this->modif("couleur","commmauvtxt",12);	//Rouge clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commmauvbg"); this->modif("couleur","commmauvbg",0);		//Noir fonc�												
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commpostxt"); this->modif("couleur","commpostxt",15);	//Blanc clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("commposbg"); this->modif("couleur","commposbg",0);		//Noir fonc�	
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menutxt"); this->modif("couleur","menutxt",15);			//Blanc clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menubg"); this->modif("couleur","menubg",0);				//Noir fonc�						
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menuselecttxt"); this->modif("couleur","menuselecttxt",0);	//Noir fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menuselectbg"); this->modif("couleur","menuselectbg",15);	//Blanc clair
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menuarrplantxt"); this->modif("couleur","menuarrplantxt",7);	//Blanc fonc�
					rayon[poscouleur].ajoutvide(); nomlivre[poscouleur].ajout("menuarrplanbg"); this->modif("couleur","menuarrplanbg",0);	//Noir fonc�
				//Ajouter le rayon des genres			//Contient le genre de chaque personnage: 0 = f�minin, 1 = non binaire, 2 = masculin
				rayon.ajoutvide();
				nomrayon.ajout("genre");
					rayon[posgenre].ajoutvide(); nomlivre[posgenre].ajout("tu"); this->modif("genre","tu",0);		//Lu joueuxe, cellui qui est appel�.e "tu" tout le long!			
			};
			//Fonction d'acc�s : acces ; retourner la valeur � certaines positions
			int acces(int posrayon, int poslivre) {return(rayon[posrayon][poslivre]);}
			int acces(int posrayon, string livrestr) {int poslivre = ColNameFind(livrestr,nomlivre[posrayon]); return(rayon[posrayon][poslivre]);}	//Pour les rayons fixes
			//Fonction de modification : modif ; modifie la valeur � certaines positions
			void modif(int posrayon, int poslivre, int value) {rayon[posrayon][poslivre] = value;}
			void modif(int posrayon, string livrestr, int value) {int poslivre = ColNameFind(livrestr,nomlivre[posrayon]); rayon[posrayon][poslivre] = value;}	//Pour les rayons fixes
			void modif(string rayonstr, string livrestr, int value) {
				int posrayon = ColNameFind(rayonstr,nomrayon); 
				int poslivre = ColNameFind(livrestr,nomlivre[posrayon]);
				rayon[posrayon][poslivre] = value;
			}
		};

		//b) classe : memoire ; permet de sauvegarder la "m�moire" de la console, c'est-�-dire tous le texte s'y �tant d�j� inscrit
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
					//Tester si on a assez de m�moire dynamique       
						try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
					souvenir = new char* [nbcol];   //Cr�er un premier array contenant des pointers
					//Cr�er les lignes pour chaque colonne, et les remplir d'espace
					for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}
				}
				//Constructeur pour avoir le bon nombre de colonnes
				memoire(int ncol) {
					nbcol = ncol;
					frontline = 0;                         //Ce qui suit semble �tre la seule mani�re de cr�er des arrays dynamiques
					nbligne = TailleBase;            
					//Tester si on a assez de m�moire dynamique       
						try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
					souvenir = new char* [nbcol];   //Cr�er un premier array contenant des pointers
					//Cr�er les lignes pour chaque colonne, et les remplir d'espace
					for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}
				}			
				//Destructeur
				~memoire() {
					for(int col=0; col<nbcol ; col++) delete[] souvenir[col] ; delete[] souvenir;   //Bien d�construire tout proprement
				}
				//Fonction d'acc�s : retourner certaines positions
				char acces (int posx, int posy) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
					return(souvenir[posx][posy]);
				}
				int accesfrontline() {return(frontline);}
				//Fonction de modification : met quelque chose dans la position
				void modif (int posx, int posy, char caract) { 
					souvenir[posx][posy] = caract;
				}				
				//Fonction de modification : setsize ; d�faire la m�moire construite par d�faut pour en fabriquer une de bonnes dimensions
				void setsize(int ncol) {
					for(int col=0; col<nbcol ; col++) delete[] souvenir[col] ; delete[] souvenir;   //Bien d�construire tout proprement ce qui �tait l� avant d'aller plus loin					
					nbcol = ncol;					//R�initialiser les param�tres
					frontline = 0;                         
					nbligne = TailleBase;            
					//Tester si on a assez de m�moire dynamique       
						try{souvenir = new char* [nbcol]; for(int col=0; col<nbcol ; col++) {souvenir[col] = new char [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
					souvenir = new char* [nbcol];   //Cr�er un premier array contenant des pointers
					//Cr�er les lignes pour chaque colonne, et les remplir d'espace
					for(int col=0; col<nbcol; col++) {souvenir[col] = new char [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) souvenir[col][ligne] = ' ';}					
				}
				//Fonction de modification : newline ; ajouter une ligne � la suite de la position sp�cifi�e
				void newline (int pos) {
					if(frontline+1<nbligne) {
						int emptypos = pos + 1;   //Calculer la position qui sera vide
						//D�placer de 1 tout ce qui vient ensuite, en commen�ant par la fin
						for(int lin = frontline; lin > pos; lin--) for(int col = 0; col < nbcol; col++) souvenir[col][lin+1]=souvenir[col][lin]; 
						for(int col = 0; col < nbcol; col++) souvenir[col][emptypos] = ' ';   //Remplir la position vide d'espace
						frontline++;   //Noter qu'on ajoute une ligne
					} else {
						int emptypos = pos + 1;   //Calculer la position qui sera vide
							//Tester si on a assez de m�moire dynamique       				
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
	
		//c) classe : msnmemoire ; permet de sauvegarder les positions occup�es par les msn
			class msnmemoire{
				//Membres
				public: 
					int nbcol;                  //Nombre de colonnes (fixe)
					int nbligne;                //Nombre de lignes (fixe)
					bool** caselibre;           //L'objet contient, en fa�ades, des pointeurs pointant � d'autres pointeurs		//Pour savoir quelle case est occup�e
					bool* lignelibre;			//Pour savoir quelle ligne est occup�e
				//Constructeur par d�faut
				msnmemoire() {
					nbcol = 1; nbligne = 1;
					//Tester si on a assez de m�moire dynamique       
						try{caselibre = new bool* [nbcol+1]; for(int col=0; col<nbcol+1 ; col++) {caselibre[col] = new bool [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
					//Cr�er l'objet caselibre 
						caselibre = new bool* [nbcol];   //Cr�er un premier array contenant des pointers
						//Cr�er les lignes pour chaque colonne, et les remplir de "TRUE"
						for(int col=0; col<nbcol; col++) {caselibre[col] = new bool [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) caselibre[col][ligne] = true;}
					//Cr�er l'objet lignelibre, et le remplir de "TRUE"
						lignelibre = new bool [nbligne];  for(int ligne=0; ligne<nbligne; ligne++) lignelibre[ligne] = true;	
				}
				//Constructeur pour avoir le bon nombre de colonnes et de lignes
				msnmemoire(int ncol, int nligne) {
					nbcol = ncol; nbligne = nligne;            
					//Tester si on a assez de m�moire dynamique       
						try{caselibre = new bool* [nbcol+1]; for(int col=0; col<nbcol+1 ; col++) {caselibre[col] = new bool [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
					//Cr�er l'objet caselibre 
						caselibre = new bool* [nbcol];   //Cr�er un premier array contenant des pointers
						//Cr�er les lignes pour chaque colonne, et les remplir de "TRUE"
						for(int col=0; col<nbcol; col++) {caselibre[col] = new bool [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) caselibre[col][ligne] = true;}
					//Cr�er l'objet lignelibre, et le remplir de "TRUE"
						lignelibre = new bool [nbligne];  for(int ligne=0; ligne<nbligne; ligne++) lignelibre[ligne] = true;	
				}			
				//Destructeur
				~msnmemoire() {
					for(int col=0; col<nbcol ; col++) delete[] caselibre[col] ; delete[] caselibre; delete[] lignelibre;  //Bien d�construire tout proprement
				}
				//Fonction de modification : setsize ; d�faire la m�moire construite par d�faut pour en fabriquer une de bonnes dimensions
				void setsize(int ncol, int nligne) {
					for(int col=0; col<nbcol ; col++) delete[] caselibre[col] ; delete[] caselibre; delete[] lignelibre;  //Bien d�construire tout proprement avant d'aller plus loin					
					nbcol = ncol; nbligne = nligne;            	//Mettre les bonnes valeurs aux param�tres
					//Tester si on a assez de m�moire dynamique       
						try{caselibre = new bool* [nbcol+1]; for(int col=0; col<nbcol+1 ; col++) {caselibre[col] = new bool [nbligne];}}  	//Tenter d'allouer l'espace
						catch (std::bad_alloc & ba) {std::cerr << "bad_alloc caught in class memoire: " << ba.what();}    //Lire les messages d'erreur si la m�moire est satur�e (exceptions)								
					//Cr�er l'objet caselibre 
						caselibre = new bool* [nbcol];   //Cr�er un premier array contenant des pointers
						//Cr�er les lignes pour chaque colonne, et les remplir de "TRUE"
						for(int col=0; col<nbcol; col++) {caselibre[col] = new bool [nbligne]; for(int ligne=0; ligne<nbligne; ligne++) caselibre[col][ligne] = true;}
					//Cr�er l'objet lignelibre, et le remplir de "TRUE"
						lignelibre = new bool [nbligne];  for(int ligne=0; ligne<nbligne; ligne++) lignelibre[ligne] = true;					
				}
				//Fonction de modification : met quelque chose dans la position
				void modifcase (int posx, int posy, bool val) { 
					caselibre[posx][posy] = val;
				}
				void modifligne (int posy, bool val) { 
					lignelibre[posy] = val;
				}
				//Fonctions d'acc�s : retourner certaines positions
				bool accescase (int posx, int posy) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
					return(caselibre[posx][posy]);
				}
				bool accesligne (int posy) { //Cr�er une fonction permettant d'aller chercher une valeur de l'array (une seule position)
					return(lignelibre[posy]);
				}
			};
	
	//ii) Classes de sauvegarde des expressions math�matiques et logiques	----------------------------------------------------------------------		
	
		//a) classe : inteval ; contient l'expression � �valuer (la plus simple) ; constructeur transforme les noms de "livre" en position d'indexation
		class inteval {
			//Valeurs membres
			public:
				int rayonpos;   		//Position d'indexation de la "famille" de l'argument compar� � gauche					
				int livrepos;			//Position d'indexation de l'argument compar� � gauche, � l'int�rieur de sa "famille"
				int boolval; int intval;
				int constbool; int constint;      //TRUE si les valeurs sont bool�ennes ou int, � la place d'�valu�es.
			//Constructeur
			inteval ()  : constbool(0), constint(0) {}; //Constructeur par d�faut : vide. 
			//Fonction de modification : clean() ; permet de remettre l'objet � l'�tat initial, dans le but de le "set()" de nouveau
			void clean(void) {
				rayonpos = -1; livrepos = -1;
				boolval = 0; intval = 0;
				constbool = 0; constint = 0;
			}
			//Fonction de modification : set() ; permet de construire l'objet avec une expression
			void set(string str, bibliotheque& biblio) {
				int strnb = str.length();
				string rayon, livre;    //Initier un string, dans lequel seront ins�r�s seulement les noms des rayons/livres
				int strpos, pos; strpos = 0; pos = 0; while(str[pos]!='�'&&pos<strnb) rayon += str[pos++];
				//�valuer si le string contient des noms ou une valeur														//CHANGER CETE LIGNE??????
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
			//Fonction d'acc�s : eval()	
			int eval(bibliotheque& biblio) {if(constbool) return(boolval); else if(constint) return(intval); else return(biblio.acces(rayonpos,livrepos));}	
			
			
			//DEBUGGGGGGG
			void test(bibliotheque& biblio) {if(constbool) out(boolval); else if(constint) out(constint); else out(biblio.acces(rayonpos,livrepos));}
			
				
		};	
	
		//b) classe : intoper ; contient les op�rations d'expressions bool�ennes �valuables
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
			intoper ()  : Lcompos(false), Rcompos(false) {}; //Constructeur par d�faut : vide. 
			//Destructeur
			~intoper(){
				if(Lcompos) delete LHcompos; else delete LHsimple;
				if(Rcompos) delete RHcompos; else delete RHsimple;
			}		
			//Fonction de modification : clean() ; permet de remettre l'objet � l'�tat initial, dans le but de le "set()" de nouveau
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
						if(str[pos]=='(') nbPAR++;	//G�re les parenth�ses imbriqu�es 
						if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
						pos++;
					} if(!trouvPAR) out("\n\nLa parenth�se n'est pas referm�e dans: "+str); abort();
					if(trouvPAR&&pos==strnb) {str = strintervalle(str,1,strnb-2); trouvPAR = false; pos = 0;   //Supprimer la parenth�se et remettre les compteurs � 0, pour continuer		
					} else Lcompos = true;		//Noter l'expression � droite comme composite (car elle contient au minimum une parenth�se), et continuer � partir d'apr�s la parenth�se
				} else { 							
				//Cas g�n�ral : on cherche '+' ou '-', car '*' et '/' ont la priorit� d'op�ration (s'appliquent d'abord � l'�chelle locale)
					while(!trouvAD&&pos<strnb) {
						if(str[pos]=='+'||str[pos]=='-') {posAD = pos; trouvAD = true;}
						if(!trouvMU&&(str[pos]=='*'||str[pos]=='/')) {posMU = pos; trouvMU = true;}
						pos++;							
					}
					if(trouvAD) {
						operateur = str[posAD]; 					
						LH = strintervalle(str,0,posAD-1);					//D�finir les limites de l'expression � gauche						
						RH = strintervalle(str,posAD+1,strnb-1);		//D�finir les limites de l'expression � droite						
						if(trouvMU) Lcompos = true; //(car '*''/' ont la priorit� d'op�ration sur '+''-')
						while(!Rcompos&&pos<strnb) {if(str[pos]=='+'||str[pos]=='-'||str[pos]=='*'||str[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite
					} else if(trouvMU) {
						operateur = str[posMU];  
						LH = strintervalle(str,0,posMU-1);					//D�finir les limites de l'expression � gauche						
						RH = strintervalle(str,posMU+1,strnb-1);		//D�finir les limites de l'expression � droite
						pos = posMU + 1; while(!Rcompos&&pos<strnb) {if(str[pos]=='*'||str[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite				
					} else {
						operateur = ' '; LH = str;   //Aucune op�ration, seulement une �valuation				
					}		
				}			
				//Assigner les valeurs aux membres
				if(Lcompos) {LHcompos = new intoper; LHcompos->set(LH,biblio); LHsimple = nullptr;} else {LHsimple = new inteval; LHsimple->set(LH,biblio); LHcompos = nullptr;}
				if(operateur!=' ') {if(Rcompos) {RHcompos = new intoper; RHcompos->set(RH,biblio); RHsimple = nullptr;} else {RHsimple = new inteval; RHsimple->set(RH,biblio); RHcompos = nullptr;}}
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
	
		//c) classe : boolcompar ; contient les comparaisons d'expressions bool�ennes �valuables
		class boolcompar {
			//Valeurs membres
			public:
				char comparateur;      //Op�rateur de comparaison
				intoper* LH;
				intoper* RH;
				bool constbool;			   //TRUE si l'argument � gauche doit �tre compar� � un bool�en implicite
				bool boolval;		
			//Constructeur ;
			boolcompar () : constbool(false), boolval(0) {}; //Constructeur par d�faut : vide. 
			//Destructeur
			~boolcompar(){
				delete LH;
				if(!constbool) delete RH;
			}		
			//Fonction de modification : clean() ; permet de remettre l'objet � l'�tat initial, dans le but de le "set()" de nouveau
			void clean(void) {
				delete LH;
				if(!constbool) delete RH;
				constbool = false; boolval = 0; comparateur = ' ';
			}
			//Fonction de modification : set() ; permet de construire l'objet avec une expression
			void set(string str, bibliotheque& biblio) {
				int strnb = str.length();
				if(strnb==0) {comparateur = ' ';}        //Cas sp�cial: retourne TRUE automatiquement
				//Recueillir l'op�rateur			
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
					if(posEX==0) { //Cas sp�cial r�chapp� de la fonction pr�c�dente (si jamais elle en laisse passer un)
						constbool = true; boolval = false; comparateur = '=';	poscomparateur = strnb;  //�CRIT COMME CELA, �A NE MARCHE PAS, CAR �A N'EFFACE PAS LE '!' (� LA FIN, LH EST D�FINI COMME [0, strnb])
						out("Le string \""); out(str); out("\" a �t� pass� � la fonction boolcompar(), le compositeur '!' n'ayant pas �t� d�tect� par la fonction boolcompos. Cette partie du code n'est donc pas bonne.''"); abort();			
					} else {poscomparateur = posEX;	comparateur = '!'; if(trouvEG&&posEG!=posEX+1) erreur = true;}		//!=
				} else if(trouvPE) {poscomparateur = posPE; if(trouvEG&&posEG==posPE+1) {comparateur = '�';    			//<=
					} else if(!trouvEG) comparateur = '<'; else erreur = true;											//<	
				} else if(trouvGR) {poscomparateur = posGR;	if(trouvEG&&posGR==posGR+1) {comparateur = '�';   			//>=
					} else if(!trouvEG) comparateur = '>'; else erreur = true;											//>	
				} else if(trouvEG) {poscomparateur = posEG; if(str[posEG+1]=='=') comparateur = '='; else erreur = true;		//==	
				} else {constbool = true; boolval = true; comparateur = '=';	poscomparateur = strnb;} //Cas sp�cial : "comparaison implicite de la valeur � true"
				//Message d'erreur
				if(erreur) {out("\n\nL'op�rateur n'est pas complet dans: "+str); abort();}
				//Cr�er les objets intoper
				LH = new intoper; LH->set(strintervalle(str,0,poscomparateur-1),biblio);
				if(!constbool){
					RH = new intoper;
					if(comparateur=='='||comparateur=='!'||comparateur=='�'||comparateur=='�') RH->set(strintervalle(str,poscomparateur+2,strnb-1),biblio); else RH->set(strintervalle(str,poscomparateur+1,strnb-1),biblio);	
				}			
			}
			//Fonction d'acc�s : eval
			bool eval(bibliotheque& biblio) {
				if(comparateur=='=') {
					if(constbool) return(LH->eval(biblio)==boolval); else return(LH->eval(biblio)==RH->eval(biblio));				// ==
				} else if(comparateur=='!') {
					if(constbool) return(LH->eval(biblio)!=boolval); else return(LH->eval(biblio)!=RH->eval(biblio));				// !=
				} else if(comparateur=='<') {
					if(constbool) return(LH->eval(biblio)<boolval); else return(LH->eval(biblio)<RH->eval(biblio));					// <
				} else if(comparateur=='�') {
					if(constbool) return(LH->eval(biblio)<=boolval); else return(LH->eval(biblio)<=RH->eval(biblio));				// <=
				} else if(comparateur=='<') {
				if(constbool) return(LH->eval(biblio)>boolval); else return(LH->eval(biblio)>RH->eval(biblio));						// >
				} else if(comparateur=='�') {
				if(constbool) return(LH->eval(biblio)>=boolval); else return(LH->eval(biblio)>=RH->eval(biblio));					// >=
				}
			}
			
			
			//DEBUGGGG
			bool test(bibliotheque& biblio) {
					if(constbool) {LH->test(biblio); out(comparateur); out(comparateur); out(boolval);} else {LH->test(biblio); out(comparateur); out(comparateur); RH->test(biblio);}	
			}
			
			
		};
	
	
		//d) classe : boolcompos ; permet de stoker des expressions bool�ennes �valuables; (LH = "left hand", � gauche ; RH = "Right hand", � droite)
		class boolcompos {
			//Valeurs membres
			public:
				char compositeur;   //'&' ou '|' ou '!' (==false) ou ' ' (==true, sans comparaison)
				boolcompar* LHsimple; boolcompos* LHcompos; 
				boolcompar* RHsimple; boolcompos* RHcompos;
				bool Lcompos; bool Rcompos;	
			//Constructeur
			boolcompos () : Lcompos(false), Rcompos(false)	{}; //Constructeur par d�faut : vide. 
			//Destructeur
			~boolcompos(){
				if(Lcompos) delete LHcompos; else delete LHsimple;
				if(Rcompos) delete RHcompos; else delete RHsimple;
			}
			//Fonction de modification : clean() ; permet de remettre l'objet � l'�tat initial, dans le but de le "set()" de nouveau
			void clean(void) {
				if(Lcompos) delete LHcompos; else delete LHsimple;
				if(Rcompos) delete RHcompos; else delete RHsimple;
				Lcompos = false; Rcompos = false; compositeur = ' ';
			}
			//Fonction de modification : set() ; permet de construire l'objet avec une expression		
			void set(string str, bibliotheque& biblio) {    //false : valeurs par d�faut qui pourront changer � l'int�rieur du constructeur
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
				//Cas sp�cial: l'expression commence par une parenth�se (ex: "( 0==4 | 5<2 )"  ou  "(3>=5) & 3==7" ) 			
					while(!trouvPAR&&pos<strnb) {
						if(str[pos]=='(') nbPAR++;	//G�re les parenth�ses imbriqu�es 
						if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
						pos++;
					} if(!trouvPAR) {out("\n\nLa parenth�se n'est pas referm�e dans : \""); out(str); out("\""); abort();}
					if(trouvPAR&&pos==strnb) {str = strintervalle(str,1,strnb-2); trouvPAR = false; pos = 0;   //L'expression enti�re est entre parenth�ses : Supprimer celles-ci et remettre les compteurs � 0, pour continuer au cas g�n�ral
					} else Lcompos = true;		//Noter l'expression � gauche comme composite (car elle contient au minimum une parenth�se), et continuer au cas g�n�ral � partir d'apr�s la parenth�se
				} else if(str[0]=='!'&&str[1]=='(') {  
				//Cas sp�cial: l'expression commence par "le contraire" d'une parenth�se (ex: "!( 6<2 | 4==4 )"  ou  "!( 6>3 | 5<6) & 1==3" )			
					while(!trouvPAR&&pos<strnb) {
						if(str[pos]=='(') nbPAR++;	//G�re les parenth�ses imbriqu�es 
						if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
						pos++;
					} if(!trouvPAR) {out("\n\nLa parenth�se n'est pas referm�e dans : \""); out(str); out("\""); abort();}
					if(trouvPAR&&pos==strnb) {compositeur = '!'; LH = strintervalle(str,2,strnb-2); Lcompos = true; general = false;   //L'expression enti�re est "contraire" : passer le cas g�n�ral		
					} else Lcompos = true;		//Noter l'expression � gauche comme composite (car elle contient un "contraire"), et continuer au cas g�n�ral � partir d'apr�s la parenth�se	
				}
				if(general) {
				//Cas g�n�ral : on cherche '|', car '!' et '&' ont la priorit� d'op�ration (s'appliquent d'abord � l'�chelle locale)
					while(!trouvOU&&pos<strnb) {
						if(str[pos]=='|') {posOU = pos; trouvOU = true;}
						if(!trouvET&&str[pos]=='&') {posET = pos; trouvET = true;}
						if(!trouvEX&&str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=') {posEX = pos; trouvEX = true;}   //Si '!' agit bien comme compositeur, c'est-�-dire qu'il n'est pas accol� � un '='
						pos++;							
					}
					if(trouvOU) {
						compositeur = '|';
						LH = strintervalle(str,0,posOU-1);					//D�finir les limites de l'expression � gauche	
						RH = strintervalle(str,posOU+1,strnb-1);		//D�finir les limites de l'expression � droite						
						if(trouvEX||trouvET) Lcompos = true; //(car '!' et '&' ont la priorit� d'op�ration sur '|')
						while(!Rcompos&&pos<strnb) {if(str[pos]=='|'||str[pos]=='&'||(str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=')) Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite
					} else if(trouvET) {  
						compositeur = '&';
						LH = strintervalle(str,0,posET-1);					//D�finir les limites de l'expression � gauche		
						RH = strintervalle(str,posET+1,strnb-1);		//D�finir les limites de l'expression � droite
						if(trouvEX) Lcompos = true;   //(car '!' a la priorit� d'op�ration sur '&')
						pos = posET + 1; while(!Rcompos&&pos<strnb) {if(str[pos]=='&'||(str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=')) Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite				
					} else if(trouvEX) {
						if(posEX==0){						
							compositeur = '!';
							LH = strintervalle(str,1,strnb-1);					//D�finir les limites de l'expression � gauche	
																				//Il n'y a pas d'expression � droite
						} else {out("\n\nLe symbole de contraire, '!', n'est pas en position [0] dans : \""); out(str); out("\", mais bien en position "); out(posEX); abort();}
					} else {
						compositeur = ' '; LH = str;   //Aucune comparaison, seulement une �valuation (et il n'y a pas d'expression � droite)						
					}		
				}			
				//Assigner les valeurs aux membres
				if(Lcompos) {LHcompos = new boolcompos; LHcompos->set(LH,biblio); LHsimple = nullptr;} else {LHsimple = new boolcompar; LHsimple->set(LH,biblio); LHcompos = nullptr;}
				if(compositeur!='!'&&compositeur!=' ') {if(Rcompos) {RHcompos = new boolcompos; RHcompos->set(RH,biblio); RHsimple = nullptr;} else {RHsimple = new boolcompar; RHsimple->set(RH,biblio); RHcompos = nullptr;}}		
			}
			//Fonction d'acc�s : eval
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
	
	//iii) Classes portant les textes qui s'affichent � l'�cran (� court terme)	----------------------------------------------------------------------		
	
		//a) Classe : canal ; porte les textes composant le corps de la fiction, qui seront affich�s comme fond de la console (vraiment � la base)
		class canal {
			//Membres
			public:
				unsigned nxtt;       						//Moment o� la prochaine entr�e sera trait�e         
				unsigned pausedt;	    					//Diff�rence entrepos�e entre nxtt et currentt, dans le cas o� l'ex�cution est arr�t�e (ex: faire appara�tre un menu)				
				unsigned delay;								//D�lai de base entre chaque entr�e
				int posx, posy;								//Coordonn�es de la derni�re entr�e dans la m�moire (la pr�c�dente)   
															//les positions de la consoles sont d�finies en d�calant ces derni�res
				int alinea;									//Nombre d'espace depuis la marge droite qui viendront s'ajouter � chaque nouvelle ligne					
				string txt;   								//Texte qui reste � lire  				
				bool actif;									//Compteur d'activit�
				bool pause;									//Compteur qui s'active si le canal est arr�t� par un processus ind�pendant (ex: un menu, ou le code sp�cial "freeze")
				bool frozen;								//Compteur pour diff�rencier les pauses initi�s par le code sp�cial "freeze" de celles initi�es par un menu
				string nom;									//Nom que porte le canal
				string terminaison;							//Texte � placer juste apr�s toute interruption ("override"), pour en quelque sorte terminer sur une belle note. Peut �tre chang� � tout moment par le code sp�cial "�t�".
			//Constructeur						
			canal() : delay(150), posx(-1), posy(0), alinea(0), actif(false), nom("defaut"), terminaison(""), nxtt(0), pausedt(0), pause(false), frozen(false) {}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
		};

		//b) Classe : msn ; permet d'afficher des messages instantann�s par-dessus le texte du "fond de la console", qui s'effacent d'eux-m�mes apr�s un moment
		class msn {
			//Membres
			public:
				int posdebx, posdeby;							//Coordonn�es de la premi�re entr�e dans la m�moire
				int posx, posy;         						//Coordonn�es de la derni�re entr�e dans la m�moire
				unsigned nxtt;									//Moment o� la prochaine entr�e sera trait�e
				unsigned pausedt;								//Diff�rence entrepos�e entre nxtt et currentt, dans le cas o� l'ex�cution est arr�t�e (ex: faire appara�tre un menu)
				unsigned delay;									//D�lai de base entre chaque entr�e
				string txt;										//Texte int�gral de la messagerie
				int postxt;										//Position de la prochaine lettre qui va �tre lue / prochaine lettre qui va �tre effac�e
				int nbysupp;									//Nombre de lignes (donc en 'y') ajout�es � la ligne de d�part
				bool construire;								//Compteur qui dit s'il est temps de construire le message (ou d'effacer le texte)
				bool attente;									//Compteur qui s'active s'il n'y a pas de place pour ajouter une autre ligne
				bool pause;										//Compteur qui s'active si le msn est arr�t� par un processus ind�pendant (ex: un menu, ou le code sp�cial "freeze")
				bool frozen;									//Compteur pour diff�rencier les pauses initi�s par le code sp�cial "freeze" de celles initi�es par un menu
			//Constructeur
			msn() : posdebx(0), posdeby(0), posx(-1), posy(0), delay(80), postxt(0), nbysupp(0), construire(true), attente(false), nxtt(0), pausedt(0), pause(false), frozen(false) {}	//Constructeur par d�faut
		};

	//iv) Classes g�rant les entr�es de la joueuse	----------------------------------------------------------------------		
	
		//a) classe : input ; sauvegarde les informations relatives � ce qu'�crit la joueuse
		class input {
			//Valeurs membres
			public:
				StaticVect<char,200> commande;          	//Phrase que contient le buffer        
				int inputpos;                   //Position d'indexation du prochain caract�re    == StaticVect.fin? Non! Car �a peut bouger!
				bool accepted;                  //Flag concernant la derni�re commande; utile pour l'affichage visuel
				bool reserve;					//Flag concernant la derni�re commande; met le motif en r�serve et bloque l'acceptation de nouvelles commandes
				int reservechap;				//Position du chapitre du motif � mettre en r�serve
				int reservemotif;				//Position du motif � mettre en r�serve (� l'int�rieur de son chapitre)
				double vit;						//Multiplicateur de d�lais de d�filement du texte, pour modifier la vitesse de lecture			
			//Constructeur par d�faut
				input() : inputpos(0), accepted(false), reserve(false), vit(1) {}
		};							
							
		//b) classe : inputecho ; permet l'affichage r�siduel des commandes (accept�es ou refus�es)	
		class inputecho {
			//Valeurs membres
			public:
				StaticVect<char,200> commande;
				StaticVect<int,50> clignote;               //Conserve les instructions pour le clignotement : positif = affiche, n�gatif = pause.	
				int txtcol; int bgcol;                     //Conservent la couleur du clignotement actuel
				bool actif;							       //Compteur d'activit�
				int nxtt;         						   //Moment o� la prochaine entr�e sera trait�e         
				int pausedt;							   //Diff�rence entrepos�e entre nxtt et currentt, dans le cas o� l'ex�cution est arr�t�e (ex: faire appara�tre un menu)				
			//Constructeur par d�faut
			inputecho() : txtcol(8), bgcol(0), actif(false), nxtt(0) {}			//Couleur par d�faut: gris sombre sur noir
		};

	//v) Classes g�rant les conditions d'apparition du texte	----------------------------------------------------------------------		
			
		//a) classe : commande ; permet le stockage de "mots de passe" pour les commandes
		class commande {
			//Valeurs membres
			public:
				static const int tailledifferentes = 5;
				static const int taillegroupes = 5;
				static const int taillesynonymes = 12;
				StaticVect<StaticVect<StaticVect<string,taillesynonymes>,taillegroupes>,tailledifferentes> inclus;		//Mots qui doivent �tre inclus dans l'expression
						//Niveau le plus ext�rieur: Diff�rentes fa�on de dire la commande (ex: manger le concombre / se nourrir / mastiquer) ... Genre?
						//Niveau m�dian: Diff�rents groupes de mots qui doivent �tre inclus (ex: manger / concombre)
						//Niveau le plus int�rieur: Diff�rents synonymes � l'int�rieur du groupe de mots (ex: manger/absorber/grignoter/engouffrer/avaler)
				StaticVect<StaticVect<string,taillesynonymes>,tailledifferentes> exclus;						//Mots qui doivent �tre absents de l'expression
						//Niveau le plus ext�rieur: Diff�rentes fa�on de dire la commande
						//Niveau le plus int�rieur: Diff�rents mots qui ne doivent pas se retrouver dans la commande
				StaticVect<string,taillegroupes> exact;										//Expressions qui doivent exactement �tre recopi�es, sans faute (soit seule mani�re d'appeler, soit confirmation si ambiguit�; voir UserInputInterpret())
			//Constructeur
			commande() {};	
		};		
				
		//b) classe : motifauto ; permet le stockage du texte et des conditions d'apparition (automatique)
		class motifauto {
			//Membres
			public:
				StaticVect<string,10> maille;						//Texte � lire
				StaticVect<StaticVect<int,8>,32> enchainement;  	//int r�f�re aux positions des mailles         
				StaticVect<intoper,32> enchaineprob;        	 	//Avec le m�me ordre d'indexation que encha�nement
				boolcompos condition;								//Conditions � respecter pour l'ajout au canal sans UserInput 
				string codespeciauxdebut;
				string codespeciauxfin;
				bool override;										//TRUE si l'activation de motif vide instantann�ment le canal utilis�
				bool encours;										//Va changer dynamiquement, permet de ne pas d�doubler le m�me motif (� un temps d'attente obligatoire)
				int canal;											//Position du canal dans lequel �crire le texte
				bool msn;											//Si TRUE, le motif va activer un nouveau msn � la place de s'inscrire dans un canal
			//Constructeur
			motifauto() : override(false), encours(false), msn(false) {};
		};
		
		//c) classe : motifmanu ; permet le stockage du texte et des conditions d'apparition (manuelle)
		class motifmanu {
			//Membres
			public:
				StaticVect<string,10> maille;						//Texte � lire
				StaticVect<StaticVect<int,8>,32> enchainement;  	//int r�f�re aux positions des mailles         
				StaticVect<intoper,32> enchaineprob;        	 	//Avec le m�me ordre d'indexation que encha�nement
				boolcompos condition;								//Conditions � respecter pour l'ajout au canal avec UserInput				
				string codespeciauxdebut;
				string codespeciauxfin;
				bool override;										//TRUE si l'activation de motif vide instantann�ment le canal utilis�
				int canal;											//Position du canal dans lequel �crire le texte
				bool msn;											//Si TRUE, le motif va activer un nouveau msn � la place de s'inscrire dans un canal			
				commande commandes;                					//Mots � rechercher pour l'ajout au canal � partir du UserInput			
				bool reserve;                                       //TRUE si le UserInput devient bloqu� apr�s que ce motif ait �t� appel� (le motif est stock� en r�serve, jusqu'� son activation)
				string titre;										//Sert � identifier le motif + � savoir quel motif est appel� en cas d'ambiguit� de la commande
			//Constructeur
			motifmanu() : reserve(false), override(false), msn(false) {};	
		};
		
		//d) classe : ouvrage ; permet de stocker toutes les textes + commandes selon des cat�gories (ex: chapitres), pour faciliter la recherche
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
				int selectdelay;				//D�lai total de l'animation de s�lection ([HAUT] ou [BAS]), en millisecondes
				int enterdelay;				//D�lai total de l'animation de confirmation ([ENTER] ou [ESCAPE]), en millisecondes
				StaticVect<string,nombrebouton> boutons;
				StaticVect<string,nombrebouton> effets;
				string effetescape;
				bool isbgdessin;			//TRUE si le background est un dessin; FALSE si le background est simplement ce que contient la m�moire (m�moire des canaux + msn + etc.)
				string bgdessin; int bgdessinnbligne;
				int bgptinteretx; int bgptinterety;													//Points du dessin qu'on va tenter de placer � un position pr�cise
				double bgposinteretx; double bgposinterety;											//Position (en fraction de la fen�tre) souhait�e pour les points d'int�r�t
				bool bgleftlocked; bool bgrightlocked; bool bgtoplocked; bool bgbottomlocked;		//C�t�s fix�s aux limites du dessin dans l'agrandissement de la fen�tre (si la fen�tre est plus grande, mettre des espaces aux c�t�s non fixes)				
				string titretxt;
				string titredessin; int titredessinnbligne;
				bool istitredessin;			//TRUE si le titre est un dessin; FALSE si le titre est du texte
				double titrehauteur;		//La fraction de la hauteur � laquelle on veut que le titre commence
				bool actif;
				int posactu; int pospreced;
				int selectpos; int selectneg; int selectesc; int selectenter;			//Compteurs des animations
				int selectpost; int selectnegt; int selectesct; int selectentert;		//Compteurs de temps pour les animations
			//Constructeur
			menu() : actif(false), posactu(0), pospreced(0), isbgdessin(false), istitredessin(false), titretxt(""), effetescape("�a�"),
				largeurbouton(19), hauteurbouton(3), espacebouton(2), selectdelay(600), enterdelay(1300) {}
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
			//Membres d'affichage � court terme
			static const int taillecanaux = 2;			//Taille des objets de type StaticVect<canal,Taille>				
			static const int taillemessagerie = 15;		//Taille des objets de type StaticVect<msn,Taille>
			static const int taillegroupes = 5;			//Taille des groupes de mots qui doivent �tre bons dans une commande; copie de la ligne pr�sente dans "class commande"; pas id�al			
			StaticVect<canal,taillecanaux> canaux;
			StaticVect<string,taillecanaux> nomcanaux;
			StaticVect<msn,taillemessagerie> messagerie;
			//Membres de menus
			static const int taillemenus = 5;
			StaticVect<menu,taillemenus> menus;
			StaticVect<string,taillemenus> nommenus;
			static const int nombrebouton = 5;			//Nombre maximal de boutons; copie de la ligne pr�sente dans "class menu"; pas id�al			
			static const int menunblignesmax = 5;		//Nombre maximal de lignes diff�rente pouvant �tre tol�r� dans le titre ou le bouton d'un menu; n�cessaire pour cr�er des StaticVect<int, menunblignesmax> dans LireMenus()
			//Membres d'entr�es par la joueuse 
			input inp;
			inputecho inpecho;
			//Membre de conditions d'affichage	
			ouvrage histoire;	
			//Membre permettant d'utiliser une distribution normale	
			normdist normbase;
			//Membre donnant l'heure
			horloge clock;
		//Constructeurs
			//Constructeur par d�faut
			univers() {
				randseed(clock);			//Poser un d�part unique (bas� sur l'heure d'ex�cution du programme) au g�n�rateur de nombres al�atoires
			};
		//Fonctions de jeu
			//Fonctions pour modifier la taille de la fen�tre
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
			//Fonctions pour transf�rer le texte d'un motif vers un canal ou un msn	
				void integrationmanu(int chapitrepos, int motifpos);
				void integrationauto(int chapitrepos, int motifpos);
				void AutoInterpret();
			//Fonctions pour lire les canaux/messagerie et appliquer leurs effets sur la console	
				void LireCanaux();
				void LireMessagerie();
			//Fonctions pour recevoir et interpr�ter les commandes de la joueuse	
				void UserInputInterpret(); 
			    void UserInput();
			//Fonction pour utiliser les menus
				void LireMenus(string nommenu); 
				void modiffen();
			//Fonction pour tout coordonner harmonieusement
				void jouer();
				void debuter();
		//Fonction de remplissage ais�
			//Fonctions pour nommer les livres et les rayons de la biblioth�que
				void nvrayon(const string& str);
				void nvlivre(const string& str);
			//Fonctions pour cr�er de nouveaux canaux et les personaliser
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
				void mprob(const string& str); void aprob(const string& str); 
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
				void menunvbouton(const string& strbout, const string& streff);
				void menuescape(const string& str);
	};
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//5) Fonctions sp�cialis�es pour la bonne marche du jeu

	//i) Fonctions pour modifier la taille de la fen�tre	----------------------------------------------------------------------		

		//a) Fonction : setfenetredefaut ; configure une taille par d�faut de la fen�tre de jeu -> � choisir en fonction du plus beau dessin de background pour le menu principal!
		void univers::setfenetredefaut(int x, int y) {base.dimdef(x,y);}
	
		//b) Fonction : setfenetremin ; configure une taille par d�faut de la fen�tre de jeu -> � choisir en fonction du plus petit dessin possible pour le menu principal!
		void univers::setfenetremin(int x, int y) {base.dimmin(x,y);}

	//ii) Fonctions de petite taille	----------------------------------------------------------------------		

		//a) Fonction : configmemoire ; initie les objets de m�moire avec des tailles qui cadrent avec la fen�tre actuelle
		void univers::configmemoire() {
			mem.setsize(base.limtxtx);
			msnmem.setsize(base.limtxtx,base.limtxty);	
		}
		
		//b) Fonction : UserInputEcho ; validant graphiquement l'acceptation ou le refus des commandes envoy�es
		void univers::UserInputEcho() {	
			if(inpecho.actif&&inpecho.nxtt<clock.currentt) {
				base.chgcol(inpecho.txtcol,inpecho.bgcol);
				//Clignoter
				if(inpecho.clignote[0]>0){
					base.curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
				} else {
					base.curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(' ');		
				}
				base.chgcol(biblio.acces(biblio.poscouleur,"actutxt"),biblio.acces(biblio.poscouleur,"actubg"));                       //Revenir � la couleur de base	
				inpecho.nxtt = clock.currentt + round(abs(inpecho.clignote[0])*pow(inp.vit,1/2));        //Updater le "next time"		//vit ^ (1/2), pour ne pas TROP modifier la vitesse...
				inpecho.clignote.suppression(1);            //Passer � la prochaine instruction
				if(inpecho.clignote.longueur==0) inpecho.actif = false;			//V�rifier s'il reste toujours du stock � passer dans le canal	
			}	
		}
		
		//c) Fonction : pauseall/unpauseall ; arr�te les compteurs des tous les canaux et msn, et les repart
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
		
		//d) Fonction : overridecanal() ; vide le canal, en appliquant cependant les codes sp�ciaux s�lectionn�s qui s'y trouvent
		void univers::overridecanal(int canpos) {
			//Passer tous les codes sp�ciaux importants
			int strnb = canaux[canpos].txt.length(); bool cdsp = false;
			for(int txtpos=0; txtpos<strnb; txtpos++) { 
				if(cdsp) {		//Si l'on est dans un code sp�cial
					if(canaux[canpos].txt[txtpos]=='m'){		//'m' pour "motif" -> marquer le motif automatique comme n'�tant plus en cours
						string poschap; string posmotif; 
						txtpos++; while(canaux[canpos].txt[txtpos] != ';') poschap += canaux[canpos].txt[txtpos++]; 
						txtpos++; while(canaux[canpos].txt[txtpos] != '�') posmotif += canaux[canpos].txt[txtpos++];
						histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //D�signer le motif signal� comme n'�tant plus en cours
					} else while(canaux[canpos].txt[txtpos] != '�') txtpos++;
					txtpos++; cdsp = false;      //Terminer le code sp�cial actuel
				} else if(canaux[canpos].txt[txtpos]=='�') cdsp = true;          //Si l'on n'est pas dans un code sp�cial
			}
			if(canaux[canpos].txt.length()==0) canaux[canpos].txt = canaux[canpos].terminaison;     //Remplacer ce qui �tait dans le canal par la "terminaison" de ce canal (par d�faut, c'est "" - c'est � dire rien)
			if(canaux[canpos].txt.length()==0) canaux[canpos].actif = false;           //D�sactiver le canal, si le canal est vide
		}

		//e) Fonction ReecrireMemoire()			
		void univers::ReecrireMemoire() {
			base.curspos(0,0);   //Commencer en haut, puis descendre naturellement
			for(int county = base.consy; county < base.limtxty; county++){             //base.consy : facteur de d�calage de la console
				for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
			}	
		}
		
		//f) Fonction ReecrireMsn()			
		void univers::ReecrireMsn(int msnpos) {
			//Cr�er un raccourci pour la position � laquelle on est rendue (la "suivante")
			int posrc = messagerie[msnpos].postxt;		//rc pour raccourci
			//R�-�crire depuis le d�but, jusqu'� la "position pr�c�dente"
			int posx = messagerie[msnpos].posdebx -1; int posy = messagerie[msnpos].posdeby;		//S'initie � la m�me position que dans la fonction Integration()
			int counttxt = 0;
			while(counttxt<posrc) {
				if(messagerie[msnpos].txt[counttxt]=='�') {
					counttxt += CodeSpecialLongueur(strintervalle(messagerie[msnpos].txt,counttxt,messagerie[msnpos].txt.length()-1));	//Skipper les codes sp�ciaux						
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
							
		//g) Fonction EffacerMsn()				//Pour r�-�crire par-dessus � l'aide de la m�moire!
		void univers::EffacerMsn(int msnpos) {
			//Cr�er un raccourci pour la position � laquelle on est rendue (la "suivante")
			int posrc = messagerie[msnpos].postxt;		//rc pour raccourci
			//R�-�crire depuis le d�but, jusqu'� la "position pr�c�dente"
			int posx = messagerie[msnpos].posdebx-1; int posy = messagerie[msnpos].posdeby;		//S'initie � la m�me position que dans la fonction Integration()
			int counttxt = 0;
			while(counttxt<posrc) {
				if(messagerie[msnpos].txt[counttxt]=='�') {
					counttxt += CodeSpecialLongueur(strintervalle(messagerie[msnpos].txt,counttxt,messagerie[msnpos].txt.length()-1));	//Skipper les codes sp�ciaux						
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
		
		//i) Fonction ReecrireTout()			//Pour r�-�crire tous les �l�ments affich�s � l'�cran lors de l'histoire!
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
		
	//iii) Fonctions pour transf�rer le texte d'un motif vers un canal ou un msn	----------------------------------------------------------------------		
		
		//a) Fonction : integration ; ajoute un motif � un canal
		void univers::integrationmanu(int chapitrepos, int motifpos) {
			//V�rifier d'abord si on doit mettre le motif en r�serve
			if(histoire.filmanu[chapitrepos][motifpos].reserve&&!inp.reserve) {		//La fonction integrationmanu() ne sera jamais lanc�e si la r�serve est pleine, hormis dans le cas du code sp�cial "�r�". Donc c'est safe.
				inp.reservechap = chapitrepos; inp.reservemotif = motifpos; inp.reserve = true;
			} else {
				inp.reserve = false;
				bool msnbool = histoire.filmanu[chapitrepos][motifpos].msn;
				bool msnskip = false; 
				int xpos; int ypos;
				//V�rifier s'il y a de la place pour un nouveau msn (si c'est un msn qui est updat�)
				if(msnbool) {
					//Choisir le msn qui sera utilis�
					bool msnvide = false; bool lignelibrechoisie = false;
					if(messagerie.longueur<messagerie.taille) msnvide = true;
					if(msnvide) {
						//Choisir la position de d�part!
							xpos = round(min(max(normbase.randnormapprox(25,12),0),80)*base.limtxtx/100);		//Dist normale(mean=0.25,sd=0.15), born�e � 0% et 80% de la console
							ypos = round(min(max(normbase.randnormapprox(28,16),0),80)*base.limtxty/100);
							//Choisir une ligne de d�part non occup�e
							lignelibrechoisie = true; 
							if(!msnmem.accesligne(ypos)) {
								lignelibrechoisie = false; int countligne = 1;
								while(!lignelibrechoisie) {
									if(ypos+countligne<base.limtxty&&msnmem.accesligne(ypos+countligne)) { ypos += countligne; lignelibrechoisie = true;
									} else if(ypos-countligne>=0&&msnmem.accesligne(ypos-countligne)) { ypos -= countligne; lignelibrechoisie = true;}
									countligne++;
									if(ypos+countligne>=base.limtxty&&ypos-countligne<0) break;		//Si on arrive hors des limites � la fois vers le haut et vers le bas, aucune ligne n'est libre
								}
							}
					}
					if(!msnvide||!lignelibrechoisie) {msnskip = true; inp.accepted = false;}	//Aucune ligne ou msn n'est libre : refuser d'int�grer le motif, m�me si la commande est bonne			
				} 
				if(!msnskip){
					//Choisir l'encha�nement � ins�rer
					int sumprob = 0; StaticVect<int,10> vectprob;
					for(int posprob=0; posprob<histoire.filmanu[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {	//�valuer chaque probabilit�
						sumprob += histoire.filmanu[chapitrepos][motifpos].enchaineprob[posprob].eval(biblio); vectprob[posprob] = sumprob; 
					}
					int randval = randunif(0,sumprob-1);  //Obtenir un integer al�atoire entre [0,sumprob[
					int choix; 
					for(int posprob=0; posprob<histoire.filmanu[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {
						if(randval<vectprob[posprob]) {choix = posprob; break;}
					}	
					//D�finir le texte � ins�rer
					string txtmotif;
					txtmotif += histoire.filmanu[chapitrepos][motifpos].codespeciauxdebut;   //Codes sp�ciaux d�but
					for(int posench=0; posench<histoire.filmanu[chapitrepos][motifpos].enchainement[choix].longueur; posench++) {
						txtmotif += histoire.filmanu[chapitrepos][motifpos].maille[histoire.filmanu[chapitrepos][motifpos].enchainement[choix][posench]];
					}		
					txtmotif += histoire.filmanu[chapitrepos][motifpos].codespeciauxfin;		//Codes sp�ciaux fin  
					//Updater le canal/msn 
					if(msnbool) {
						messagerie.ajoutvide();																					//Ajouter officiellement un objet msn � la messagerie
						messagerie[messagerie.longueur-1].posdebx = xpos; messagerie[messagerie.longueur-1].posdeby = ypos;		//D�finir les positions de d�part
						msnmem.modifligne(ypos,false);																			//D�finir la ligne comme occup�e
						messagerie[messagerie.longueur-1].posx = xpos-1; messagerie[messagerie.longueur-1].posy = ypos;			//D�finir les positions du curseur (avant la premi�re entr�e)
						messagerie[messagerie.longueur-1].postxt = 0;															//Remettre au d�but du texte
						messagerie[messagerie.longueur-1].construire = true; messagerie[messagerie.longueur-1].nbysupp = 0;		//Remettre les autres compteurs � leur position initiale
						messagerie[messagerie.longueur-1].delay = normbase.randnormapprox(110,10);								//Mettre un d�lai al�atoire
						messagerie[messagerie.longueur-1].txt += txtmotif;														//Ajouter le texte				
						messagerie[messagerie.longueur-1].nxtt = clock.currentt; 														//Updater le nxtt pour qu'il commence � partir de l'int�gration
					} else {
						if(histoire.filmanu[chapitrepos][motifpos].override) overridecanal(histoire.filmanu[chapitrepos][motifpos].canal);	//Overloader le canal si n�cessaire			//Ne s'applique pas aux msn			
						canaux[histoire.filmanu[chapitrepos][motifpos].canal].txt += txtmotif;																			//Ajouter le texte				
						if(!canaux[histoire.filmanu[chapitrepos][motifpos].canal].actif) canaux[histoire.filmanu[chapitrepos][motifpos].canal].nxtt = clock.currentt; 		//Updater le nxtt pour qu'il commence � partir de l'int�gration
						if(canaux[histoire.filmanu[chapitrepos][motifpos].canal].txt.length()>0) canaux[histoire.filmanu[chapitrepos][motifpos].canal].actif = true;	//Marquer le canal comme actif
					}	
				}			
			}
		}
		void univers::integrationauto(int chapitrepos, int motifpos) {
			bool msnbool = histoire.filauto[chapitrepos][motifpos].msn;
			bool msnskip = false;
			int xpos; int ypos;			
			//V�rifier s'il y a de la place pour un nouveau msn (si c'est un msn qui est updat�)
			if(msnbool) {
				//Choisir le msn qui sera utilis�
				bool msnvide = false; bool lignelibrechoisie = false;
				if(messagerie.longueur<messagerie.taille) msnvide = true;
				if(msnvide) {
					//Choisir la position de d�part!
						xpos = round(min(max(normbase.randnormapprox(25,12),0),80)*base.limtxtx/100);		//Dist normale(mean=0.25,sd=0.15), born�e � 0% et 80% de la console
						ypos = round(min(max(normbase.randnormapprox(28,16),0),80)*base.limtxty/100);
						//Choisir une ligne de d�part non occup�e
						lignelibrechoisie = true; 
						if(!msnmem.accesligne(ypos)) {
							lignelibrechoisie = false; int countligne = 1;
							while(!lignelibrechoisie) {
								if(ypos+countligne<base.limtxty&&msnmem.accesligne(ypos+countligne)) { ypos += countligne; lignelibrechoisie = true;
								} else if(ypos-countligne>=0&&msnmem.accesligne(ypos-countligne)) { ypos -= countligne; lignelibrechoisie = true;}
								countligne++;
								if(ypos+countligne>=base.limtxty&&ypos-countligne<0) break;		//Si on arrive hors des limites � la fois vers le haut et vers le bas, aucune ligne n'est libre
							}
						}
				}
				if(!msnvide||!lignelibrechoisie) {msnskip = true; }	//Aucune ligne ou msn n'est libre : attendre pour jouer le motif (ne pas l'int�grer)			
			} 
			if(!msnskip){
				//Choisir l'encha�nement � ins�rer
				int sumprob = 0; StaticVect<int,10> vectprob;
				for(int posprob=0; posprob<histoire.filauto[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {	//�valuer chaque probabilit�
					sumprob += histoire.filauto[chapitrepos][motifpos].enchaineprob[posprob].eval(biblio); vectprob[posprob] = sumprob; 
				}
				int randval = randunif(0,sumprob-1);  //Obtenir un integer al�atoire entre [0,sumprob[
				int choix; 
				for(int posprob=0; posprob<histoire.filauto[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {
					if(randval<vectprob[posprob]) {choix = posprob; break;}
				}	
				//D�finir le texte � ins�rer
				string txtmotif;
				txtmotif += histoire.filauto[chapitrepos][motifpos].codespeciauxdebut;   //Codes sp�ciaux d�but
				for(int posench=0; posench<histoire.filauto[chapitrepos][motifpos].enchainement[choix].longueur; posench++) {
					txtmotif += histoire.filauto[chapitrepos][motifpos].maille[histoire.filauto[chapitrepos][motifpos].enchainement[choix][posench]];
				}		
				txtmotif += histoire.filauto[chapitrepos][motifpos].codespeciauxfin;		//Codes sp�ciaux fin
				txtmotif += "�a" + to_string(chapitrepos) + ';' + to_string(motifpos) +'�';		//Code sp�cial permettant d'enlever le status en cours du motif     //Faut convertir les int en string...
				//Marquer le motif comme "en cours"
				histoire.filauto[chapitrepos][motifpos].encours = true;     
				//Updater le canal/msn 
				if(msnbool) {
					messagerie.ajoutvide();																					//Ajouter officiellement un objet msn � la messagerie
					messagerie[messagerie.longueur-1].posdebx = xpos; messagerie[messagerie.longueur-1].posdeby = ypos;		//D�finir les positions de d�part
					msnmem.modifligne(ypos,false);																			//D�finir la ligne comme occup�e
					messagerie[messagerie.longueur-1].posx = xpos-1; messagerie[messagerie.longueur-1].posy = ypos;			//D�finir les positions du curseur (avant la premi�re entr�e)
					messagerie[messagerie.longueur-1].postxt = 0;															//Remettre au d�but du texte
					messagerie[messagerie.longueur-1].construire = true; messagerie[messagerie.longueur-1].nbysupp = 0;		//Remettre les autres compteurs � leur position initiale
					messagerie[messagerie.longueur-1].attente = false; messagerie[messagerie.longueur-1].pause = false;
					messagerie[messagerie.longueur-1].delay = normbase.randnormapprox(100,10);								//Mettre un d�lai al�atoire
					messagerie[messagerie.longueur-1].txt = txtmotif;														//Ajouter le texte				
					messagerie[messagerie.longueur-1].nxtt = clock.currentt; 												//Updater le nxtt pour qu'il commence � partir de l'int�gration
				} else {
					if(histoire.filauto[chapitrepos][motifpos].override) overridecanal(histoire.filauto[chapitrepos][motifpos].canal);	//Overloader le canal si n�cessaire			//Ne s'applique pas aux msn			
					canaux[histoire.filauto[chapitrepos][motifpos].canal].txt += txtmotif;																			//Ajouter le texte				
					if(!canaux[histoire.filauto[chapitrepos][motifpos].canal].actif) canaux[histoire.filauto[chapitrepos][motifpos].canal].nxtt = clock.currentt; 		//Updater le nxtt pour qu'il commence � partir de l'int�gration
					if(canaux[histoire.filauto[chapitrepos][motifpos].canal].txt.length()>0) canaux[histoire.filauto[chapitrepos][motifpos].canal].actif = true;	//Marquer le canal comme actif
					canaux[histoire.filauto[chapitrepos][motifpos].canal].pause = false;
				}	
			}
		}

		//b) Fonction : AutoInterpret ; permet de v�rifier si les conditions d'application des motifs automatiques sont remplies
		void univers::AutoInterpret() {
			//Pour chaque chapitre
			for(int chapitrepos=0; chapitrepos<histoire.filauto.longueur; chapitrepos++) { if(histoire.cadenas[chapitrepos].eval(biblio)) {			
				//Pour chaque motif dans l'histoire
				for(int motifpos=0; motifpos<histoire.filauto[chapitrepos].longueur; motifpos++) {if(histoire.filauto[chapitrepos][motifpos].condition.eval(biblio)&&!histoire.filauto[chapitrepos][motifpos].encours) {
					integrationauto(chapitrepos,motifpos);            //Int�grer tout de suite le motif dans le canal	
				}}
			}}
		}		
	
	//iii) Fonctions pour lire les canaux/messagerie et appliquer leurs effets sur la console	----------------------------------------------------------------------		

		//a) Fonction LireCanaux()
		void univers::LireCanaux() {
			//Lire tous les canaux, si ils sont pr�ts
			for(int canpos=0; canpos<canaux.longueur; canpos++) {if(canaux[canpos].actif&&canaux[canpos].nxtt<clock.currentt&&(!canaux[canpos].pause)) {
				//Interpr�ter les "codes sp�ciaux" (�...�)
				if(canaux[canpos].txt[0]=='�'){		
					//D�terminer la longueur du code sp�cial
						int CodeSpecialLong = CodeSpecialLongueur(canaux[canpos].txt);			
					//Lire le code sp�cial	
						if(canaux[canpos].txt[1]=='a'){		//'a' pour "automatique" -> marquer le motif automatique comme n'�tant plus en cours			
							string poschap; string posmotif; int posSpecial = 2;
							while(canaux[canpos].txt[posSpecial] != ';') poschap += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(canaux[canpos].txt[posSpecial] != '�') posmotif += canaux[canpos].txt[posSpecial++];
							histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //D�signer le motif signal� comme n'�tant plus en cours
						} else if(canaux[canpos].txt[1]=='b'){		//'b' pour "biblio" -> modifier la biblioth�que
							string nomrayon; string nomlivre; string val;
							int posSpecial = 2;
							while(canaux[canpos].txt[posSpecial] != '�') nomrayon += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(!(canaux[canpos].txt[posSpecial] == '~' && canaux[canpos].txt[posSpecial+1] == '>')) nomlivre += canaux[canpos].txt[posSpecial++];  //ex: "�bintro�desuet~>1�"
							posSpecial+=2; while(canaux[canpos].txt[posSpecial] != '�') val += canaux[canpos].txt[posSpecial++];							
							biblio.modif(nomrayon,nomlivre,stoi(val));	
							AutoInterpret();      //V�rifier si un motif automatique doit �tre int�gr� aux canaux/msn					
						} else if(canaux[canpos].txt[1]=='c'){		//'c' pour "cut" -> descendre le canal dans la derni�re ligne possible, en coupant en deux le canal qui l'occupe.
							//Cr�e deux nouvelles lignes, une pour le canal qui coupe et une pour le canal coup�
							mem.newline(mem.accesfrontline()); mem.newline(mem.accesfrontline());                   
							//Updater le correctif de d�calage de la console par rapport � la m�moire
							if(base.refoule) base.consy++; else if(mem.accesfrontline()>=base.limtxty) {base.refoule = true; base.consy++;} 				
							if(base.refoule) base.consy++; else if(mem.accesfrontline()>=base.limtxty) {base.refoule = true; base.consy++;} 				
							//Sauter deux lignes dans la console
							if(base.refoule) {                         //La console est satur�e: on pousse le texte vers le haut!
								chgcolcan();	//Mettre la bonne couleur					
								//Effacer toute les deux lignes avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")
									base.curspos(0,mem.accesfrontline()-base.consy-1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
									base.curspos(0,mem.accesfrontline()-base.consy); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout r�-�crire la m�moire, mais une ligne plus haut
			    					base.curspos(0,0);   //Commencer en haut, puis descendre naturellement
									for(int county = base.consy; county <= mem.accesfrontline()-2; county++){             //base.consy : facteur de d�calage de la console
										for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
									}	
								//R�-�crire tous les msn
									chgcolmsn();	//Mettre la bonne couleur					
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) ReecrireMsn(countmsn);										      
							}	   	        
							//Updater les positions dans le canal actuel
							canaux[canpos].posx = -1;						//en x    //-1 est une position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
							canaux[canpos].posy = mem.accesfrontline()-1;			//en y 	
							//Updater les positions dans l'ancien canal de frontline
							for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {if(canaux[countcan].posy == mem.accesfrontline()-2) canaux[countcan].posy+=2;}
						} else if(canaux[canpos].txt[1]=='d'){      //'d' pour "d�lai" -> changer le d�lai entre chaque lettre, donc la vitesse de lecture
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
						} else if(canaux[canpos].txt[1]=='g'){		//'g' pour "gender" -> choisir le bon accord   format: �gNomAGenrer(f�minin;non binaire/neutre;masculin)�
							int genreselect;										 //S�lectionner le genre
								string NomAGenrer;
								for(int posSpecial=2;posSpecial<CodeSpecialLong;posSpecial++) {
									if(canaux[canpos].txt[posSpecial]=='(') {break; 			//Sortir de la boucle si on a atteint la fin du Nom-�-Genrer           
									} else NomAGenrer += canaux[canpos].txt[posSpecial];							//PEUT-�TRE OPTIMISER CETTE BOUCLE AVEC strintervalle()????????
								}
								genreselect = biblio.acces(biblio.posgenre,ColNameFind(NomAGenrer,biblio.nomlivre[biblio.posgenre]));		//Le rayon "genre" de la biblioth�que contient le genre de tous les personnages (0 = f�minin, 1 = non binaire, 2 = masculin)
							int genreactuel = 0;										//Aller chercher le bon accord
								int posdebut = 3; int posfin = CodeSpecialLong - 2;		//Valeurs par d�fauts		//Code sp�cial Long -2 : pour ne pas avoir ")�" � la fin!
								for(int posSpecial=3;posSpecial<CodeSpecialLong; posSpecial++) {				 //D�limiter le bon accord				
									if(canaux[canpos].txt[posSpecial]==';') {
										genreactuel++;
										if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect+1) posfin = posSpecial - 1;
									}
								}
							string temporairetxt;										//Ajouter le bon accord � la suite du code sp�cial 
								temporairetxt  += strintervalle(canaux[canpos].txt,0,CodeSpecialLong-1); 		//Ajouter le code sp�cial
								temporairetxt += strintervalle(canaux[canpos].txt,posdebut,posfin); 		//Ajouter le bon accord
								temporairetxt += strintervalle(canaux[canpos].txt,CodeSpecialLong,canaux[canpos].txt.length()-1);	//Ajouter le reste du texte	
								canaux[canpos].txt = temporairetxt;
						} else if(canaux[canpos].txt[1]=='m'){		//'m' pour "manuel" -> forcer l'int�gration d'un motif manuel (quand �a fait trop longtemps qu'on attend pour une commande)
							string titremotif; int posSpecial = 2;
							while(canaux[canpos].txt[posSpecial] != '�') titremotif += canaux[canpos].txt[posSpecial++];
							//Rechercher quel motif correspond � ce titre
							bool exacttrouve = false; int chapitrepos=0; int motifpos=0;
							bool exactmauvais = false; int titrepos = 0; int titrelong = titremotif.length();
							while(exacttrouve&&chapitrepos<histoire.filmanu.longueur) if(histoire.cadenas[chapitrepos].eval(biblio)) {		//Pour chaque chapitre		
								while(exacttrouve&&motifpos<histoire.filmanu[chapitrepos].longueur) if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)) {	//Pour chaque motif dans l'histoire					
								exactmauvais = false; titrepos = 0;
								while(!exactmauvais&&titrepos<titrelong) if(titremotif[titrepos]!=histoire.filmanu[chapitrepos][motifpos].titre[titrepos]) exactmauvais = true; else titrepos++;
								if(titrepos==titrelong) exacttrouve = true; else motifpos++;
								}		
							if(!exacttrouve) chapitrepos++;
							}
							integrationmanu(chapitrepos,motifpos);			//Int�grer le motif
							if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);			//R�-int�grer, au cas o� le motif entrait en r�serve					
						} else if(canaux[canpos].txt[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionn�
							string canaloverr = strintervalle(canaux[canpos].txt,2,CodeSpecialLong-2);   //Obtenir le nom du canal � overrider
							overridecanal(ColNameFind(canaloverr,nomcanaux)); 						
						} else if(canaux[canpos].txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause � la lecture		
							int val = CodeSpecialExtractInt(canaux[canpos].txt,CodeSpecialLong);       //Extraire le temps que durera la pause
							canaux[canpos].nxtt = clock.currentt + round(val * inp.vit);      //Ajouter le temps d'attente        //round() est n�cessaire pour arrondir correctement					
						} else if(canaux[canpos].txt[1]=='r'){		//'r' pour "r�serve" -> int�grer les motifs manuels qui attendent dans la r�serve; sert � ne pas couper une phrase en deux
							if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);		
						} else if(canaux[canpos].txt[1]=='s'){		//'s' pour "skip" -> descendre le canal dans la derni�re ligne possible, sans couper le canal qui l'occupe.
							//Cr�e une nouvelle ligne pour que le texte puisse vraiment descendre
							mem.newline(mem.accesfrontline());                   
							//Updater le correctif de d�calage de la console par rapport � la m�moire
							if(base.refoule) base.consy++; else if(mem.accesfrontline()>=base.limtxty) {base.refoule = true; base.consy++;} 				
							//Sauter une ligne dans la console
							if(base.refoule) {                         //La console est satur�e: on pousse le texte vers le haut!
								chgcolcan();	//Mettre la bonne couleur
								//Effacer toute la ligne avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")
									base.curspos(0,mem.accesfrontline()-base.consy); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout r�-�crire, mais une ligne plus haut
			    					base.curspos(0,0);   //Commencer en haut, puis descendre naturellement
									for(int county = base.consy; county <= mem.accesfrontline()-1; county++){             //base.consy : facteur de d�calage de la console
										for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
									}	
								//R�-�crire tous les msn
									chgcolmsn();	//Mettre la bonne couleur								
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) ReecrireMsn(countmsn);										                 
							}	   	        
							//Updater les positions dans le canal actuel
							canaux[canpos].posx = -1;						//en x     //-1 est une position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
							canaux[canpos].posy = mem.accesfrontline();			//en y 	

						} else if(canaux[canpos].txt[1]=='t'){      //'t' pour "terminaison" -> changer le texte de terminaison, qui sera ajout� apr�s chaque override (si du texte a effectivement �t� effac�)
							string nomcanal; string terminaison; int posSpecial = 2;
							while(canaux[canpos].txt[posSpecial] != '�') nomcanal += canaux[canpos].txt[posSpecial++]; 
							posSpecial++; while(canaux[canpos].txt[posSpecial] != '�') terminaison += canaux[canpos].txt[posSpecial++];							
							canaux[ColNameFind(nomcanal,nomcanaux)].terminaison = terminaison;
						}
					//Effacer le code sp�cial du canal
					canaux[canpos].txt = strintervalle(canaux[canpos].txt,CodeSpecialLong,canaux[canpos].txt.length()-1);				//J'COMPRENDS PAS LE "+1" DANS "CodeSpecialLong+1"!!!!!!
				} else {  //Interpr�ter le reste des caract�res (pas des codes sp�ciaux)
					//Updater le "next time"
						canaux[canpos].nxtt = clock.currentt + round(canaux[canpos].delay * inp.vit);
					//Dealer avec la situation o� on a � sauter une ligne (cr�er les lignes suppl�mentaires et updater les diverses positions)
						bool jump = false;
						if(canaux[canpos].txt[0]=='\n'|canaux[canpos].posx>=base.limtxtx-1) jump = true;     //base.limtxtx - 1 ; car c'est en integer, et canaux[canpos].posx commence � 0!
						if(jump) {	
							mem.newline(canaux[canpos].posy);                     //Introduit une nouvelle ligne � la suite de la position qui lui est fournie	
							//Updater le correctif de d�calage de la console par rapport � la m�moire
							if(base.refoule) base.consy++; else if(mem.accesfrontline()>=base.limtxty) {base.refoule = true; base.consy++;} 				
							//Sauter une ligne dans la console
							if(!base.refoule) {          //La console n'est pas encore satur�e: on pousse vers le bas!
								if(canaux[canpos].posy<mem.accesfrontline()) {                             //S'il y a d'autres lignes � repousser vers le bas
									//R�-�crire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
										chgcolcan();	//Mettre la bonne couleur					
										base.curspos(0,canaux[canpos].posy+1);  //Mettre le curseur au d�but de la reconstruction
										for(int county = canaux[canpos].posy + 1 ; county <= mem.accesfrontline() ; county++) {   
											for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
										}
									//R�-�crire tous les msn
										chgcolmsn();	//Mettre la bonne couleur									
										for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) ReecrireMsn(countmsn);	
								}
							} else {                         //La console est satur�e: on pousse le texte vers le haut!
								chgcolcan();	//Mettre la bonne couleur					
								//Effacer toute la ligne avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")								
									base.curspos(0,canaux[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
								//Tout r�-�crire, mais une ligne plus haut
			    					base.curspos(0,0);   //Commencer en haut, puis descendre naturellement
									for(int county = base.consy; county <= canaux[canpos].posy; county++){             //base.consy : facteur de d�calage de la console
										for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.acces(countx,county));
									}				                 
								//R�-�crire tous les msn
									chgcolmsn();	//Mettre la bonne couleur
									for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) ReecrireMsn(countmsn);		
							}	
							//Updater les positions dans les autres canaux    //Parce que leur position dans la m�moire a boug� //la position dans la console est quant � elle g�r�e par base.consy
							for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {
								if(countcan==canpos) continue;                                    //la m�moire refoule toujours vers le bas!
								if(canaux[countcan].posy > canaux[canpos].posy) canaux[countcan].posy++; else if(canaux[countcan].posy == canaux[canpos].posy) canaux[countcan].posy+=2;
							}       // == : Si deux canaux se situe sur la m�me ligne, le canal qui change de ligne va couper l'autre en deux, et le renvoyer apr�s sa propre ligne.    	        
							//Updater les positions dans le canal actuel
							if(canaux[canpos].txt[0]=='\n') {canaux[canpos].posx = -1;} else canaux[canpos].posx = 0;			       //en x    
												//-1 est une position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
							canaux[canpos].posy++;	  																					   //en y 		
						} else {canaux[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
					//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du charact�re actuel (dans la m�moire)!
					if(canaux[canpos].txt[0]!='\n') {
						chgcolcan();	//Mettre la bonne couleur
						if(canaux[canpos].posx==0){	if(canaux[canpos].alinea>0) {										//Mettre l'alin�a
							for(int alinpos=0; alinpos<canaux[canpos].alinea; alinpos++){
								if(msnmem.accescase(alinpos,canaux[canpos].posy-base.consy)) {base.curspos(alinpos,canaux[canpos].posy-base.consy) ; out(' ');}  //Inscrire dans la console seulement si la place n'est pas d�j� prise par un msn
								mem.modif(alinpos,canaux[canpos].posy,' '); 		
								canaux[canpos].posx++;
							}
						}}
						//Inscrire le caract�re dans la console seulement si la place n'est pas d�j� prise par un msn
						if(msnmem.accescase(canaux[canpos].posx,canaux[canpos].posy-base.consy)) {base.curspos(canaux[canpos].posx,canaux[canpos].posy-base.consy) ; out(canaux[canpos].txt[0]);} 
						mem.modif(canaux[canpos].posx, canaux[canpos].posy, canaux[canpos].txt[0]);   //Inscrire le caract�re dans la m�moire
					}	
					canaux[canpos].txt = strintervalle(canaux[canpos].txt,1,canaux[canpos].txt.length()-1);       //Effacer le caract�re du canal     	   
				}
				if(canaux[canpos].txt.length()==0) canaux[canpos].actif = false;			//V�rifier s'il reste toujours du texte � passer dans le canal
			}}
		}	
				
		//b) Fonction LireMessagerie()
		void univers::LireMessagerie() {
			//Lire toutes les messageries, si elles sont pr�tes
			for(int msnpos=0; msnpos<messagerie.longueur; msnpos++) {if(messagerie[msnpos].nxtt<clock.currentt&&(!messagerie[msnpos].pause)) {	
				//Cr�er un raccourci pour la position du texte � lire
				int posrc = messagerie[msnpos].postxt;		//rc pour raccourci
				//Interpr�ter les "codes sp�ciaux" (�...�)
				if(messagerie[msnpos].txt[posrc]=='�'){
					if(messagerie[msnpos].construire) {
						//Cr�er un raccourci du texte � lire � partir du code sp�cial
						string txtrc = strintervalle(messagerie[msnpos].txt,posrc,messagerie[msnpos].txt.length()-1);
						//D�terminer la longueur du code sp�cial
						int CodeSpecialLong = CodeSpecialLongueur(txtrc);			
						//Lire le code sp�cial	
							if(txtrc[1]=='a'){		//'a' pour "automatique" -> marquer le motif automatique comme n'�tant plus en cours			
								string poschap; string posmotif;
								int posSpecial = 2;
								while(txtrc[posSpecial] != ';') poschap += txtrc[posSpecial++]; 
								posSpecial++; while(txtrc[posSpecial] != '�') posmotif += txtrc[posSpecial++];
								histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //D�signer le motif signal� comme n'�tant plus en cours						
							} else if(txtrc[1]=='b'){		//'b' pour "biblio" -> modifier la biblioth�que
								string nomrayon; string nomlivre; string val;
								int posSpecial = 2;
								while(txtrc[posSpecial] != '�') nomrayon += txtrc[posSpecial++]; 
								posSpecial++; while(!(txtrc[posSpecial] == '~' && txtrc[posSpecial+1] == '>')) nomlivre += txtrc[posSpecial++];
								posSpecial+=2; while(txtrc[posSpecial] != '�') val += txtrc[posSpecial++];							
								biblio.modif(nomrayon,nomlivre,stoi(val));	
								AutoInterpret();      //V�rifier si un motif automatique doit �tre int�gr� aux canaux/msn							
							} else if(txtrc[1]=='d'){      //'d' pour "d�lai" -> changer le d�lai entre chaque lettre, donc la vitesse de lecture
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
							} else if(txtrc[1]=='g'){		//'g' pour "gender" -> choisir le bon accord   format: �gNomAGenrer(f�minin;non binaire/neutre;masculin)�
								int genreselect;										 //S�lectionner le genre
									string NomAGenrer;
									for(int posSpecial=2;posSpecial<CodeSpecialLong;posSpecial++) {
										if(txtrc[posSpecial]=='(') {break; 			//Sortir de la boucle si on a atteint la fin du Nom-�-Genrer           
										} else NomAGenrer += txtrc[posSpecial];							//PEUT-�TRE OPTIMISER CETTE BOUCLE AVEC strintervalle()????????
									}
									genreselect = biblio.acces(biblio.posgenre,ColNameFind(NomAGenrer,biblio.nomlivre[biblio.posgenre]));		//Le rayon "genre" de la biblioth�que contient le genre de tous les personnages (0 = f�minin, 1 = non binaire, 2 = masculin)
								int genreactuel = 0;										//Aller chercher le bon accord
									int posdebut = 3; int posfin = CodeSpecialLong - 2;		//Valeurs par d�fauts			//Code sp�cial Long -2 : pour ne pas avoir ")�" � la fin!
									for(int posSpecial=3;posSpecial<CodeSpecialLong; posSpecial++) {				 //D�limiter le bon accord				
										if(txtrc[posSpecial]==';') {
											genreactuel++;
											if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect+1) posfin = posSpecial - 1;
										}
									}
								string temporairetxt;										//Ajouter le bon accord � la place du code sp�cial dans le texte � lire
									temporairetxt += strintervalle(messagerie[msnpos].txt, 0, posrc);	//Ajouter le texte avant le code sp�cial
									temporairetxt += strintervalle(txtrc, posdebut, posfin);			//Ajouter le bon accord
									temporairetxt += strintervalle(txtrc,CodeSpecialLong,messagerie[msnpos].txt.length()-1);				//Ajouter le reste du texte
									messagerie[msnpos].txt = temporairetxt;
									messagerie[msnpos].postxt -= (CodeSpecialLong);					//Neutraliser l'avancement de la position qui va venir apr�s, puisqu'on a supprim� le code sp�cial
							} else if(txtrc[1]=='m'){		//'m' pour "manuel" -> forcer l'int�gration d'un motif manuel (quand �a fait trop longtemps qu'on attend pour une commande)
								string titremotif; int posSpecial = 2;
								while(txtrc[posSpecial] != '�') titremotif += txtrc[posSpecial++];
								//Rechercher quel motif correspond � ce titre
								bool exacttrouve = false; int chapitrepos=0; int motifpos=0;
								bool exactmauvais = false; int titrepos = 0; int titrelong = titremotif.length();
								while(exacttrouve&&chapitrepos<histoire.filmanu.longueur) if(histoire.cadenas[chapitrepos].eval(biblio)) {		//Pour chaque chapitre		
									while(exacttrouve&&motifpos<histoire.filmanu[chapitrepos].longueur) if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)) {	//Pour chaque motif dans l'histoire					
									exactmauvais = false; titrepos = 0;
									while(!exactmauvais&&titrepos<titrelong) if(titremotif[titrepos]!=histoire.filmanu[chapitrepos][motifpos].titre[titrepos]) exactmauvais = true; else titrepos++;
									if(titrepos==titrelong) exacttrouve = true; else motifpos++;
									}		
								if(!exacttrouve) chapitrepos++;
								}
								integrationmanu(chapitrepos,motifpos);			//Int�grer le motif
								if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);			//R�-int�grer, au cas o� le motif entrait en r�serve																
							} else if(txtrc[1]=='p'){      //'p' pour "pause" -> ajouter une pause � la lecture		
								double val = CodeSpecialExtractInt(txtrc,CodeSpecialLong);       //Extraire le temps que durera la pause
								messagerie[msnpos].nxtt = clock.currentt + round(val * inp.vit);     //Ajouter le temps d'attente        //round() est n�cessaire pour arrondir correctement					
							} else if(txtrc[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionn�
								string canaloverr = strintervalle(txtrc,2,CodeSpecialLong-2);   //Obtenir le nom du canal � overrider
								overridecanal(ColNameFind(canaloverr,nomcanaux)); 																
							} else if(txtrc[1]=='r'){		//'r' pour "r�serve" -> int�grer les motifs manuels qui attendent dans la r�serve; sert � ne pas couper une phrase en deux
								if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);									
							} else if(txtrc[1]=='t'){      //'t' pour "terminaison" -> changer le texte de terminaison, qui sera ajout� apr�s chaque override (si du texte a effectivement �t� effac�)
								string nomcanal; string terminaison; int posSpecial = 2;
								while(txtrc[posSpecial] != '�') nomcanal += txtrc[posSpecial++]; 
								posSpecial++; while(txtrc[posSpecial] != '�') terminaison += txtrc[posSpecial++];							
								canaux[ColNameFind(nomcanal,nomcanaux)].terminaison = terminaison;
							}
						//Passer � la prochaine position du texte � lire
						messagerie[msnpos].postxt += (CodeSpecialLong);
					} else 	messagerie[msnpos].postxt -= CodeSpecialLongueurInv(strintervalle(messagerie[msnpos].txt,0,posrc));		//Si le msn est en d�construction 			
				} else {  //Interpr�ter le reste des caract�res (pas des codes sp�ciaux)
					//Updater le "next time"
						if(messagerie[msnpos].construire) {messagerie[msnpos].nxtt = clock.currentt + round(messagerie[msnpos].delay * inp.vit);
						} else messagerie[msnpos].nxtt = clock.currentt + round((messagerie[msnpos].delay * inp.vit)*messagerie[msnpos].postxt/messagerie[msnpos].txt.length() );	//�a s'efface de plus en plus vite (mais pas trop)!
					//Dealer avec les sauts de lignes
						if(messagerie[msnpos].construire) {			//Si on est en train d'�crire
							bool jump = false;
							if(messagerie[msnpos].posx>=base.limtxtx-1) {messagerie[msnpos].posx = -1; jump = true;}
							if(messagerie[msnpos].txt[posrc]=='\n') {jump = true;}
							if(jump||messagerie[msnpos].attente) {
								bool sautdelignereussi = false;
								//V�rifier si le changement de ligne empi�te sur un autre msn ou sur la ligne de commandes (situ�e � limtxty)
								if(messagerie[msnpos].posy==base.limtxty||!msnmem.accesligne(messagerie[msnpos].posy+1)){
									//V�rifier s'il y a de l'espace pour refouler vers le bas
									bool refoulebaspossible = false; int poslibrebas;
									for(int countligne=messagerie[msnpos].posy; countligne<base.limtxty; countligne++) if(msnmem.accesligne(countligne)) {refoulebaspossible = true; poslibrebas = countligne; break;}
									if(refoulebaspossible) {
										//Refouler jusqu'� atteindre la position libre (peut conduire � r�action en cha�ne)
										int posrefoule = messagerie[msnpos].posy + 1;
										int msnrefoule;
										while(posrefoule<poslibrebas) {
											//Trouver quel msn refouler vers le bas
											for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(posrefoule==messagerie[countmsn].posdeby) {msnrefoule = countmsn; break;}
											//R�-�crire le msn, mais une ligne plus bas
											messagerie[msnrefoule].posdeby++; messagerie[msnrefoule].posy++;		//descendre ses positions en y d'une ligne
											ReecrireMsn(msnrefoule);					//R�-�crire le msn, maintenant une ligne plus bas
											posrefoule += messagerie[msnrefoule].nbysupp + 1;		//Passer � l'espace juste apr�s ce msn 
										}
										sautdelignereussi = true;
										msnmem.modifligne(poslibrebas, false);		//Marquer la ligne comme maintenant occup�e
									} else {	//Il n'y a pas d'espace pour refouler vers le bas: v�rifier s'il est possible de refouler vers le haut
										bool refoulehautpossible = false; int poslibrehaut;
										for(int countligne=messagerie[msnpos].posy; countligne>=0; countligne--) if(msnmem.accesligne(countligne)) {refoulebaspossible = true; poslibrehaut = countligne; break;}
										if(refoulehautpossible){
											//Refouler jusqu'� atteindre la position libre (peut conduire � r�action en cha�ne)
											int posrefoule = messagerie[msnpos].posy;			//Oui, �a d�signe le msn � [msnpos] comme le premier � �tre refoul�; c'est normal.
											int msnrefoule;
											while(posrefoule>poslibrehaut) {
												//Trouver quel msn refouler vers le haut
												for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(posrefoule==messagerie[countmsn].posdeby+messagerie[countmsn].nbysupp) {msnrefoule = countmsn; break;}
												//R�-�crire le msn, mais une ligne plus haut
												messagerie[msnrefoule].posdeby--; messagerie[msnrefoule].posy--;		//monter ses positions en y d'une ligne
												ReecrireMsn(msnrefoule);					//R�-�crire le msn, maintenant une ligne plus haut
												posrefoule -= messagerie[msnrefoule].nbysupp + 1;		//Passer � l'espace juste apr�s ce msn 
											}
											sautdelignereussi = true;			
											msnmem.modifligne(poslibrehaut, false);	//Marquer la ligne comme maintenant occup�e					
										} else {	//Il n'y a pas d'espace pour refouler, ni vers le bas ni vers le haut : attendre qu'il s'en lib�re
											messagerie[msnpos].attente = true;
											//V�rifier si tous les msn sont en attente
											bool attentepossible = false;
											for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(!messagerie[msnpos].pause&&!messagerie[countmsn].attente) {attentepossible = true; break;}
											if(!attentepossible) {	//Tous les msn sont en attente qu'une ligne se lib�re : forcer celui qui est le plus pr�s de la fin � terminer pr�matur�ment
												//Trouver quel msn est le plus pr�s de la fin
												int mintxt = messagerie[msnpos].txt.length() - messagerie[msnpos].postxt;
												int msnoverr;
												for(int countmsn=0; countmsn<messagerie.longueur;countmsn++) {	//Si plusieurs msn ont le m�me nombre de caract�res restant, le dernier dans la liste l'emporte
													if((messagerie[countmsn].txt.length()-messagerie[countmsn].postxt)<=mintxt) {
														mintxt = messagerie[countmsn].txt.length()-messagerie[countmsn].postxt; msnoverr = countmsn;	
													}
												}
												//Activer les codes sp�ciaux restants s'ils modifient la biblioth�que
												int counttxt=messagerie[msnoverr].postxt;
												while(counttxt<messagerie[msnoverr].txt.length()){
													if(messagerie[msnpos].txt[counttxt]=='�'){
														//Cr�er un raccourci pour la position du texte � lire
														string txtrc = strintervalle(messagerie[msnpos].txt,counttxt,messagerie[msnpos].txt.length()-1); //Cr�er un raccourci du texte � lire � partir du code sp�cial												
														int CodeSpecialLong = CodeSpecialLongueur(txtrc);	//D�terminer la longueur du code sp�cial		
														if(txtrc[1]=='a'){		//'a' pour "automatique" -> marquer le motif automatique comme n'�tant plus en cours			
															string poschap; string posmotif;
															int posSpecial = 2;
															while(txtrc[posSpecial] != ';') poschap += txtrc[posSpecial++]; 
															posSpecial++; while(txtrc[posSpecial] != '�') posmotif += txtrc[posSpecial++];
															histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //D�signer le motif signal� comme n'�tant plus en cours
														} else if(txtrc[1]=='b'){		//'b' pour "biblio" -> modifier la biblioth�que
															string nomrayon; string nomlivre; string val;
															int posSpecial = 2;
															while(txtrc[posSpecial] != '�') nomrayon += txtrc[posSpecial++]; 
															posSpecial++; while(!(txtrc[posSpecial] == '~' && txtrc[posSpecial+1] == '>')) nomlivre += txtrc[posSpecial++];
															posSpecial+=2; while(txtrc[posSpecial] != '�') val += txtrc[posSpecial++];							
															biblio.modif(nomrayon,nomlivre,stoi(val));	
															AutoInterpret();      //V�rifier si un motif automatique doit �tre int�gr� aux canaux/msn	
														} else if(txtrc[1]=='f') {		//'f' pour "freeze" -> mettre en pause tous les canaux et msn, sauf celui-ci
															if(txtrc[2]=='1'){				//FREEZE
																for(int countcan=0; countcan<canaux.longueur; countcan++) {pausecan(countcan); canaux[countcan].frozen = true;}
																for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) {pausemsn(countmsn); messagerie[countmsn].frozen = true;}
															} else if(txtrc[2]=='0'){		//UN-FREEZE
																for(int countcan=0; countcan<canaux.longueur; countcan++) {unpausecan(countcan); canaux[countcan].frozen = false;}
																for(int countmsn=0; countmsn<messagerie.longueur; countmsn++) if(countmsn!=msnpos) {unpausemsn(countmsn); messagerie[countmsn].frozen = false;}
															}
														} else if(txtrc[1]=='m'){		//'m' pour "manuel" -> forcer l'int�gration d'un motif manuel (quand �a fait trop longtemps qu'on attend pour une commande)
															string titremotif; int posSpecial = 2;
															while(txtrc[posSpecial] != '�') titremotif += txtrc[posSpecial++];
															//Rechercher quel motif correspond � ce titre
															bool exacttrouve = false; int chapitrepos=0; int motifpos=0;
															bool exactmauvais = false; int titrepos = 0; int titrelong = titremotif.length();
															while(exacttrouve&&chapitrepos<histoire.filmanu.longueur) if(histoire.cadenas[chapitrepos].eval(biblio)) {		//Pour chaque chapitre		
																while(exacttrouve&&motifpos<histoire.filmanu[chapitrepos].longueur) if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)) {	//Pour chaque motif dans l'histoire					
																exactmauvais = false; titrepos = 0;
																while(!exactmauvais&&titrepos<titrelong) if(titremotif[titrepos]!=histoire.filmanu[chapitrepos][motifpos].titre[titrepos]) exactmauvais = true; else titrepos++;
																if(titrepos==titrelong) exacttrouve = true; else motifpos++;
																}		
															if(!exacttrouve) chapitrepos++;
															}
															integrationmanu(chapitrepos,motifpos);			//Int�grer le motif
															if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);			//R�-int�grer, au cas o� le motif entrait en r�serve
														} else if(txtrc[1]=='o') {		//'o' pour "override" -> effacer le contenu du canal (ou msn) mentionn�
															string canaloverr = strintervalle(txtrc,2,CodeSpecialLong-1);   //Obtenir le nom du canal � overrider
															overridecanal(ColNameFind(canaloverr,nomcanaux)); 																
														} else if(txtrc[1]=='r'){		//'r' pour "r�serve" -> int�grer les motifs manuels qui attendent dans la r�serve; sert � ne pas couper une phrase en deux
															if(inp.reserve) integrationmanu(inp.reservechap,inp.reservemotif);																										
														}
													} else counttxt++;
												}
												//Mettre le msn en "d�construction"
												messagerie[msnoverr].construire = false; messagerie[msnoverr].attente = false; messagerie[msnoverr].pause = false;
											}
										}
									}
								} else {sautdelignereussi = true; msnmem.modifligne(messagerie[msnpos].posy, false);}	//Si l'on ne refoule pas, passer simplement � la prochaine ligne
								if(sautdelignereussi) {
									messagerie[msnpos].posy++;		
									messagerie[msnpos].nbysupp++;		//le msn occupe une ligne de plus � partir de sa ligne de d�part
									if(messagerie[msnpos].attente) messagerie[msnpos].attente = false;		//Enlever l'attente, puisqu'on a r�ussi � atteindre une position libre
								}
							}
						} else {									//Si on est en train d'effacer
							if(messagerie[msnpos].posx==0) {messagerie[msnpos].posy--; messagerie[msnpos].posx = base.limtxtx;}
							if(messagerie[msnpos].txt[posrc]=='\n') messagerie[msnpos].posy--;					
						}								
					if(!messagerie[msnpos].attente){		//Si le msn n'est pas en attente, inscrire simplement le caract�re
						//Updater le posx
						if(messagerie[msnpos].construire) messagerie[msnpos].posx++; else messagerie[msnpos].posx--;		
						//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du caract�re actuel!
						if(messagerie[msnpos].txt[posrc]!='\n') {
							if(messagerie[msnpos].construire) {			//Si on est en train d'�crire							
								chgcolmsn();	//Mettre la bonne couleur
								base.curspos(messagerie[msnpos].posx,messagerie[msnpos].posy); out(messagerie[msnpos].txt[posrc]);	//Inscrire le caract�re dans la console
								msnmem.modifcase(messagerie[msnpos].posx, messagerie[msnpos].posy, false); 						//Noter que la position est prise par un msn				
							} else {									//Si on est en train d'effacer
								chgcolcan();	//Mettre la bonne couleur
								base.curspos(messagerie[msnpos].posx,messagerie[msnpos].posy); out(mem.acces(messagerie[msnpos].posx,messagerie[msnpos].posy+base.consy));     //Remettre la console comme elle �tait
								msnmem.modifcase(messagerie[msnpos].posx, messagerie[msnpos].posy, true); 						//Noter que la position est maintenant libre															
							}
						}	
						if(messagerie[msnpos].construire) messagerie[msnpos].postxt++; else messagerie[msnpos].postxt--;       //Passer � la prochaine position du texte � lire	   
					}	
				}
				if(messagerie[msnpos].construire&&messagerie[msnpos].postxt==messagerie[msnpos].txt.length()) {			//V�rifier s'il reste toujours du texte � lire		
					messagerie[msnpos].construire = false; 
					//Replacer les compteurs pour repartir � la bonne place
					messagerie[msnpos].postxt--; messagerie[msnpos].posx++;		//on fait posx++, pour �tre � la "position pr�c�dente", mais � l'envers (genre plus � droite de ce qui va �tre effac� � un moment donn�)										
				} else if(!messagerie[msnpos].construire&&messagerie[msnpos].postxt<0) {		//V�rifier s'il reste toujours du texte � effacer
					for(int countsupp=1; countsupp<=messagerie[msnpos].nbysupp; countsupp++) msnmem.modifligne(messagerie[msnpos].posdeby+countsupp,true);	//Lib�rer les lignes dans la m�moire
					messagerie.supprposition(msnpos);	//"Supprimer" le msn
				}
			}}
		}	
								
          
	//iv) Fonctions pour recevoir et interpr�ter les commandes de la joueuse	----------------------------------------------------------------------		
                  
		//a) Fonction : UserInputInterpret ; v�rifie si la commande entr�e correspond � une des actions actuellement autoris�e
			void univers::UserInputInterpret() {
				//Cr�er des compteurs
				StaticVect<int,20> bonchapitre;	  //Cr�er des StaticVect pour noter la position des motifs qui correspondent � la commande
				StaticVect<int,20> bonmotif;											//Taille arbitraire de 20; j'esp�re qu'aucune commande n'appelera simultann�ment 20 maillons
				StaticVect<bool,taillegroupes> groupebon; 	   	 //Cr�er un StaticVect pour noter si chaque groupe de mot est bon
				int diffpos; bool exactbon; int commpos; bool exactmauvais; 	//Cr�er les compteurs pour les expressions exactes
				int groupepos; int synpos; int motpos; int precedpos; bool inclusbon; bool exclusbon;	//Cr�er les compteurs pour les mots � inclure/exclure	
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
							if(exactbon)	{         //Int�grer tout de suite le bon motif dans le canal					
								inp.accepted = true;	//Envoyer le bon message au gestionnaire d'Input				
								integrationmanu(chapitrepos,motifpos); return;            //Int�grer le bon motif dans le canal
							}   
						//Passer maintenant aux mots-cl�s	
						inclusbon = false; diffpos = 0;
						//Cas sp�cial: Aucun mot exact ni mot-cl� � inclure fourni, mais des mots � �viter: accepter n'importe quand, tant que l'interdit n'est pas pr�sent
						if(histoire.filmanu[chapitrepos][motifpos].commandes.inclus.longueur==0&&histoire.filmanu[chapitrepos][motifpos].commandes.exact.longueur==0) {
							//V�rifier si les mots � �tre exclus sont absents		
							while(diffpos<histoire.filmanu[chapitrepos][motifpos].commandes.exclus.longueur&&!exclusbon) {	
								synpos=0; exclusbon = true;
								//Pour chaque synonyme
								while(synpos<histoire.filmanu[chapitrepos][motifpos].commandes.exclus[diffpos].longueur&&exclusbon) {
									commpos = 0;
									motpos = 0;
									//Pour chaque lettre
									while(commpos<inp.commande.longueur&&exclusbon) {		//Si le mot est retrouv�, la commande ne correspond pas au motif																			
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
						//Mots-cl�s � inclure	
						 	//Pour chaque fa�on diff�rente de dire la commande
							while(diffpos<histoire.filmanu[chapitrepos][motifpos].commandes.inclus.longueur&&!(inclusbon&&exclusbon)) {
								//V�rifier si les mots � �tre inclus sont pr�sents
									groupepos = 0;  precedpos = 0;   														//Remettre tous les groupes de mots comme incorrects jusqu'� preuve du contraire
									groupebon.remplacement(false); for(int clearpos=1; clearpos<histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos].longueur; clearpos++) groupebon.ajout(false); 
									//Pour chaque groupe de mots
									while(groupepos<histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos].longueur) {    
										synpos=0;
										//Pour chaque synonyme
										while(synpos<histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos].longueur&&!groupebon[groupepos]) {		
											commpos = precedpos;
											motpos = 0;
											//Pour chaque lettre
											while(commpos<inp.commande.longueur&&!groupebon[groupepos]) {						//DONC, ICI, L'ORDRE EST IMPORTANT DANS LA COMMANDE. PARCE QU'ON PART DE LA POSITION PR�C�DENTE. CHANGER �A? GARDER �A?	
												//PUISQUE L'ORDRE EST IMPORTANT, LA CONVERSION EN MAJUSCULE NE SERA EFFECTU�E QUE POUR LE PREMIER GROUPE DE MOT (ET POUR LA PREMI�RE LETTRE DE LA COMMANDE)
												if(commpos==0&&groupepos==0&&motpos==0)	{			//Premi�re lettre de la commande
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
									//Maintenant, on a l'information sur quel groupe de mots, dans l'intervalle [0,longueur_de_cette_differente_fa�on], a un membre qui est pr�sent dans la commande.
									groupepos=0 ; while(groupebon[groupepos++]) if(groupepos==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos].longueur) inclusbon = true;
								if(inclusbon) {
								//V�rifier si les mots � �tre exclus sont absents
									synpos=0; exclusbon = true;
									//Pour chaque synonyme
									while(synpos<histoire.filmanu[chapitrepos][motifpos].commandes.exclus[diffpos].longueur&&exclusbon) {
										commpos = 0;
										motpos = 0;
										//Pour chaque lettre
										while(commpos<inp.commande.longueur&&exclusbon) {		//Si le mot est retrouv�, la commande ne correspond pas au motif																			
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
				//Maintenant, on a l'information sur quels motifs correspondent (sans expression exacte) � la commande
				if(bonmotif.longueur==0) {
					inp.accepted = false; 			
					return;
				} else if(bonmotif.longueur==1) {	
					inp.accepted = true;	//Envoyer le bon message au gestionnaire d'Input					
					integrationmanu(bonchapitre[0],bonmotif[0]); return;            //Int�grer le bon motif dans le canal
				} else {
					//D�terminer si la commande correspond au titre d'un canal
					int bonpos = 0; exactbon = false; 
					while(bonpos<bonmotif.longueur&&!exactbon) {
						exactmauvais = false; commpos = 0;
							while(!exactmauvais&&commpos<inp.commande.longueur) {if(inp.commande[commpos]!=histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre[commpos]) exactmauvais = true; else commpos++;}	
							if(exactmauvais==false) {
								exactbon = true; 	
								inp.accepted = true;							
								integrationmanu(bonchapitre[bonpos],bonmotif[bonpos]); return;}            //Int�grer tout de suite le bon motif dans le canal	
					}	
					//Si l'ambiguit� demeure : les commandes sont mal �crites;
					
								//D�CIDER QUOI FAIRE DANS CE CAS!
								
									//INT�GRER UN MSN CUSTOM (genre qui vient vraiment avec la base, et qui dit simplement que le code a �t� mal fait, et que "commande"
									// pouvait dire "", "", ou ""?)
									
									//SIMPLEMENT REFUSER (c'est �a qui arrive pr�sentement)?
									
					inp.accepted = false; return;				
				}
			}        

		//b) Fonction UserInput()				//Enregistre quelle touche est press�e et sauvegarde la commande actuelle
		void univers::UserInput() {
			if(_kbhit()){
			//i) Capter la lettre tap�e
			bool enter = false;
			char charkey; int intkey = _getch();                  		//Enregistrer quelle touche a �t� press�e
					if (intkey == 0 || intkey == -32 || intkey == 224) {      //La valeur est sp�ciale: elle n�cessite de la r�-examiner
						intkey = _getch();                              //Examiner une deuxi�me valeur pour identifier
						if(intkey == 75) {     								 				 	//fl�che gauche : reculer dans la commande tap�e 
							if(inp.inputpos!=0) {
								if(inp.inputpos!=inp.commande.longueur) {
									base.curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
								}          //Remettre en gris la position pr�c�dente
								inp.inputpos--;  
							}
						}
						else if (intkey == 77) {											 	 //fl�che droite : avancer dans la commande tap�e				
							if(inp.inputpos!=inp.commande.longueur) {
								base.curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
								inp.inputpos++;		
							}			//Remettre en gris la position pr�c�dente
						} 
						else if (intkey == 72) {									  			 //Fl�che du haut : acc�l�rer la vitesse de d�filement
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
						else if (intkey == 80) {									  			 //Fl�che du bas : rallentir la vitesse de d�filement
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
						else if (intkey == 83) {                                                //Delete : supprimer un caract�re de la commande actuelle
							if(inp.inputpos!=inp.commande.longueur) {
								inp.commande.supprposition(inp.inputpos);    
								base.curspos(inp.inputpos,base.limtxty);
								for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);    
								out(' ');
							}
						}
					} else 	{                                        //La valeur est "normale"
						//Touches-fonctions
						if(intkey == 27) {														 //Escape : appeler le menu de pause
							pauseall();
							LireMenus("pause");											//ATTENTION! N�cessite un menu appel� "pause" !
						} else if(intkey == 13) {												 //Enter : envoyer la commande
							enter = true;
						} else if(intkey == 8) {                                                //Backspace : supprimer le caract�re pr�c�dent
							if(inp.inputpos!=0) {
								inp.inputpos--;
								inp.commande.supprposition(inp.inputpos);   
								base.curspos(inp.inputpos,base.limtxty);
								for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);   
								out(' ');    					
							}
						
						//DEBUGGG	
						} else if(intkey==14) {														//Ctrl + n : Donne la vitesse actuelle
							base.curspos(2,20); out("Voici la vitesse actuelle : "); out(inp.vit);				
						
						//DEBUGGG	
						} else if(intkey==11) {														//Ctrl + k : V�rifie manuellement s'il y a des mailles automatiques � int�grer
							AutoInterpret();   					
						
						//DEBUGGG	
						} else if(intkey==20) {														//Ctrl + t : Donne le status des conditions de chaque motif manuel
							base.curspos(2,8); out("Voici les conditions des "); out(histoire.filmanu[0].longueur); out(" cha�nons manu :");
							for(int posmotif=0; posmotif<histoire.filmanu[0].longueur; posmotif++) {
								base.curspos(2,9+posmotif); out("     Cha�non "); out(posmotif); out(" : ");
								histoire.filmanu[0][posmotif].condition.test(biblio); 
								if(histoire.filmanu[0][posmotif].condition.eval(biblio)) out("  : TRUE"); else out("  : FALSE");
							}
							//abort();
			
						//DEBUGGG	
						} else if(intkey==25) {														//Ctrl + y : Donne le status des conditions de chaque motif automatique du premier chapitre
							base.curspos(2,8); out("Voici les conditions des "); out(histoire.filauto[0].longueur); out(" cha�nons auto :");
							for(int posmotif=0; posmotif<histoire.filauto[0].longueur; posmotif++) {
								base.curspos(2,9+posmotif); out("     Cha�non "); out(posmotif); out(" : ");
								histoire.filauto[0][posmotif].condition.test(biblio); 
								if(histoire.filauto[0][posmotif].condition.eval(biblio)) out("  : TRUE"); else out("  : FALSE");						
								out("    ; en cours: "); if(histoire.filauto[0][posmotif].encours) out("TRUE"); else out("FALSE");
							}
							//abort();

			
						//DEBUGGG	
						} else if(intkey==26) {														//Ctrl + z : Donne le status des conditions de chaque motif manuel
							int decal = 0;
							for(int poschap=0; poschap<histoire.filmanu.longueur; poschap++){
								base.curspos(0,6+decal); out("Pour le chapitre "); out(poschap); out(" :");
								base.curspos(2,8+decal); out("Voici les conditions des "); out(histoire.filmanu[poschap].longueur); out(" cha�nons manu :");
								for(int posmotif=0; posmotif<histoire.filmanu[poschap].longueur; posmotif++) {
									base.curspos(2,9+decal); out("     Cha�non "); out(posmotif); out(" : ");
									histoire.filmanu[poschap][posmotif].condition.test(biblio); 
									if(histoire.filmanu[poschap][posmotif].condition.eval(biblio)) out("  : TRUE"); else out("  : FALSE");						
									decal++;
								}
								decal++;
							}
								
							//abort();

		
						//DEBUGGG	
						} else if(intkey==2) {														//Ctrl + b : Donne la valeur de chaque livre de la biblioth�que
							base.curspos(2,18); out("Voici les valeurs stock�es dans la biblioth�que:");
							int nombrelivres = 0;
							for(int posrayon=0; posrayon<biblio.nomrayon.longueur; posrayon++) {
								base.curspos(2,19+posrayon+nombrelivres); out("    "); out(biblio.nomrayon[posrayon]); out(" :   ("); out(biblio.nomlivre[posrayon].longueur); out(" rayons)");
								for(int poslivre=0; poslivre<biblio.nomlivre[posrayon].longueur; poslivre++) {
									nombrelivres++;
									base.curspos(2,19+posrayon+nombrelivres); out("                      "); out(biblio.nomlivre[posrayon][poslivre]); out(" : "); out(biblio.acces(posrayon,poslivre));
								}
							}
							//abort();
							
						//DEBUGGG	
						} else if(intkey==10) {														//Ctrl + j : Donne le texte inscrit dans le premier canal
							base.curspos(2,28); out("Voici le texte restant dans le premier canal : \"");
							out(canaux[0].txt); out("\"");
							//abort();
							
											
						} else {							//Caract�re non ASCII
							if(intkey==183) charkey = '�'; else if(intkey==133) charkey = '�'; else if(intkey==128) charkey = '�'; else if(intkey==135) {charkey = '�';
							} else if(intkey==144) charkey = '�'; else if(intkey==130) charkey = '�'; else if(intkey==212) charkey = '�'; else if(intkey==138) {charkey = '�';
							} else if(intkey==210) charkey = '�'; else if(intkey==136) charkey = '�'; else if(intkey==215) charkey = '�'; else if(intkey==140) {charkey = '�';
							} else if(intkey==216) charkey = '�'; else if(intkey==139) charkey = '�'; else if(intkey==226) charkey = '�'; else if(intkey==147) {charkey = '�';
							} else if(intkey==235) charkey = '�'; else if(intkey==151) charkey = '�'; else if(intkey==234) charkey = '�'; else if(intkey==150) {charkey = '�';
							} else charkey = intkey;		//Caract�re ASCII		 
						//Caract�re normal : l'ajouter � la commande	
							if(inp.commande.longueur<base.limtxtx-1){
								inp.commande.ajout(charkey,inp.inputpos);
								inp.inputpos++;
								chgcolcommande();	//Mettre la bonne couleur
								base.curspos(inp.inputpos-1,base.limtxty);	                    
								for(int pos=inp.inputpos-1; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);
								if(inp.commande.longueur==inpecho.commande.fin) inpecho.actif = false;                   //D�sactiver le canal d'�cho si la commande actuelle le d�passe
							}
						}
					}	
				//Remettre la lettre s�lectionn�e en surbrillance
				if(inp.inputpos!=inp.commande.longueur) {base.chgcol(biblio.acces(biblio.poscouleur,"commpostxt"),biblio.acces(biblio.poscouleur,"commposbg"));  base.curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); base.chgcol(biblio.acces(biblio.poscouleur,"actutxt"),biblio.acces(biblio.poscouleur,"actubg"));}
				//�valuer la commande		
				if(enter) {
					bool dejareserve = false;
					if(inp.reserve) dejareserve = true; else UserInputInterpret();		//Interpr�ter la commande seulement s'il n'y a pas d�j� un motif en r�serve
					inpecho.commande.remplacement(inp.commande);						
					inpecho.actif = true; inpecho.nxtt = clock.currentt;          							 //Mettre � l'heure le "nexttime"					
					if(dejareserve)	{		//Faire clignoter le texte lentement pendant quelques secondes
							inpecho.txtcol = biblio.acces(biblio.poscouleur,"commbusytxt"); inpecho.bgcol = biblio.acces(biblio.poscouleur,"commbusybg");
							int clignarr [4] {1000,-1000,1000,-1};
							inpecho.clignote.remplacement(clignarr, 4);						
					} else if(inp.accepted) {
						if(inp.reserve) {			//Conserver le texte en place pendant quelques secondes. Peut �tre effac� progressivement par une nouvelle commande
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
			//Cr�er des raccourcis pour les coins en haut � droite de chaque bouton
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
			//Cr�er un array pour chaque bouton, pour les dessiner plus rapidement
			char dessinbout[menus[posmenu].nombrebouton][menus[posmenu].hauteurbouton][menus[posmenu].largeurbouton];		//Cr�er un array pour chaque bouton
			for(int countbout=0; countbout<menus[posmenu].boutons.longueur; countbout++) {
				//Trouver le texte comporte combien de lignes, et la longueur de chaque ligne
				int nblignetxt = 1; int nbchartxt = 0; StaticVect<int,menunblignesmax> longueurlignetxt;
				for(int strpos=0; strpos<menus[posmenu].boutons[countbout].length(); strpos++) {
					if(menus[posmenu].boutons[countbout][strpos]=='\n') {nblignetxt++; longueurlignetxt.ajout(nbchartxt); nbchartxt=0;} else nbchartxt++;
				} longueurlignetxt.ajout(nbchartxt);								
				//Faire la premi�re ligne
				dessinbout[countbout][0][0] = '|'; dessinbout[countbout][0][menus[posmenu].largeurbouton-1] = '|'; for(int countchar=1; countchar<menus[posmenu].largeurbouton-1; countchar++) dessinbout[countbout][0][countchar] = '�';
				//Faire la derni�re ligne
				dessinbout[countbout][menus[posmenu].hauteurbouton-1][0] = '|'; dessinbout[countbout][menus[posmenu].hauteurbouton-1][menus[posmenu].largeurbouton-1] = '|'; for(int countchar=1; countchar<menus[posmenu].largeurbouton-1; countchar++) dessinbout[countbout][menus[posmenu].hauteurbouton-1][countchar] = '_';
				//Centrer le texte
				int beginpos = floor(((menus[posmenu].hauteurbouton-2)-nblignetxt)/2) + 1 ; int strpos = 0;
				for(int lignecount=1; lignecount<menus[posmenu].hauteurbouton-1; lignecount++) {
					dessinbout[countbout][lignecount][0] = '|'; dessinbout[countbout][menus[posmenu].hauteurbouton-1-lignecount][1] = ' ';
					dessinbout[countbout][lignecount][menus[posmenu].largeurbouton-1] = '|'; dessinbout[countbout][menus[posmenu].hauteurbouton-1-lignecount][menus[posmenu].largeurbouton-2] = ' ';
					if(lignecount<beginpos||lignecount>beginpos+(nblignetxt)) {	//Si on doit remplir avec des espaces
						for(int charpos = 2; charpos<menus[posmenu].largeurbouton-2; charpos++) dessinbout[countbout][lignecount][charpos] = ' ';
					} else {
						for(int charpos = 2; charpos<menus[posmenu].largeurbouton-2; charpos++) {	//Si on doit remplir avec le nom du bouton
							if(charpos>=ceiling((menus[posmenu].largeurbouton-longueurlignetxt[lignecount-beginpos])/2)&&charpos<floor((menus[posmenu].largeurbouton-longueurlignetxt[lignecount-beginpos])/2)+longueurlignetxt[lignecount-beginpos]&&strpos < menus[posmenu].boutons[countbout].length()) {
								dessinbout[countbout][lignecount][charpos] = menus[posmenu].boutons[countbout][strpos]; strpos++;
							} else dessinbout[countbout][lignecount][charpos] = ' ';
						}
						strpos++;		//Faire avancer le texte � la fin de la ligne, car on tombe sur un '\n' qu'on ne veut pas printer!
					}
				}
			}
			//Afficher le menu
				//Afficher l'arri�re plan
				chgcolmenuarrplan();	//Mettre la bonne couleur
				if(menus[posmenu].isbgdessin) {
					int nbcolbg = menus[posmenu].bgdessin.length()/menus[posmenu].bgdessinnbligne;
					//Placer le dessin correctement en fonction de la taille de la fen�tre
					int bgdecalx = 0; int bgdecaly = 0;				//L'origine du dessin, soit le coin "top-left", en haut � gauche, va �tre d�cal� pour placer le point d'int�r�t � la bonne place
						//Commencer par les coordonn�es en "x"
						int bgdiffx = base.limfenx-nbcolbg;
						int bgposinteretx = round(menus[posmenu].bgposinteretx*base.limfenx);	//Id�alement, on veut que le point d'int�r�t soit exactement � ces coordonn�es!
						if(bgdiffx<0) {							//La fen�tre est plus petite que l'image totale: d�caler pour positionner le point d'int�r�t
							for(int countdiff=0; countdiff<abs(bgdiffx); countdiff++) {		//D�filer l'image jusqu'� atteindre sa limite droite
								//tirer graduellement l'image vers la gauche, pour laisser appara�tre la partie de droite � la fen�tre
								if(menus[posmenu].bgptinteretx - bgdecalx > bgposinteretx) bgdecalx++; else break;
							}
						} else if(bgdiffx>0) {					//La fen�tre est plus grande que l'image totale: agrandir pour positionner le point d'int�r�t
							if(!menus[posmenu].bgleftlocked&&!menus[posmenu].bgrightlocked) {		//Augmenter l'espace � gauche seulement si c'est permis
								for(int countdiff=0; countdiff<bgdiffx; countdiff++) {		//Tasser l'image vers la droite en la gardant tout de m�me enti�re en tout temps
									if(menus[posmenu].bgptinteretx - bgdecalx < bgposinteretx) bgdecalx--; else break;
								}
							} else if(menus[posmenu].bgrightlocked) bgdecalx = bgdiffx; else if(menus[posmenu].bgleftlocked) bgdecalx = 0;		//Valeurs automatiques si un c�t� est bloqu� (ne peut pas s'agrandir)
							//Le trou qui n'a pas �t� combl� en d�calant va �tre rempli par des espaces � droite					
						}								
						//Poursuivre avec les coordonn�es en "y"
						int bgdiffy = base.limfeny-menus[posmenu].bgdessinnbligne;
						int bgposinterety = round(menus[posmenu].bgposinterety*base.limfeny);	//Id�alement, on veut que le point d'int�r�t soit exactement � ces coordonn�es!
						if(bgdiffy<0) {							//La fen�tre est plus petite que l'image totale: d�caler pour positionner le point d'int�r�t
							for(int countdiff=0; countdiff<abs(bgdiffy); countdiff++) {		//D�filer vers le haut jusqu'� atteindre sa limite en bas
								//tirer graduellement l'image vers le haut, pour laisser appara�tre la partie basse � la fen�tre
								if(menus[posmenu].bgptinterety - bgdecaly > bgposinterety) bgdecaly++; else break;
							}
						} else if(bgdiffx>0) {					//La fen�tre est plus grande que l'image totale: agrandir pour positionner le point d'int�r�t
							if(!menus[posmenu].bgtoplocked&&!menus[posmenu].bgbottomlocked) {		//Augmenter l'espace en haut seulement si c'est permis
								for(int countdiff=0; countdiff<bgdiffy; countdiff++) {		//Tasser l'image vers le bas en la gardant tout de m�me enti�re en tout temps
									if(menus[posmenu].bgptinterety - bgdecaly < bgposinterety) bgdecaly--; else break;
								}	
							} else if(menus[posmenu].bgbottomlocked) bgdecaly = bgdiffy; else if(menus[posmenu].bgtoplocked) bgdecaly = 0;		//Valeurs automatiques si un c�t� est bloqu� (ne peut pas s'agrandir)
							//Le trou qui n'a pas �t� combl� en d�calant va �tre rempli par des espaces en bas					
						}				
					//Dessiner le background
					int posdessinx = bgdecalx; int posdessiny = bgdecaly;
					for(int countligne=0; countligne<base.limfeny; countligne++) {
						base.curspos(0,countligne);
						posdessinx = bgdecalx;
						for(int countcol=0; countcol<base.limfenx; countcol++) {
							if(countligne==base.limfeny-1&&countcol==base.limfenx-1) continue;		//Ne pas remplir le dernier coin (en bas � droite), pour �viter de changer de ligne automatiquement et de d�border de la fen�tre
							if(posdessinx>=0&&posdessinx<nbcolbg&&posdessiny>=0&&posdessiny<menus[posmenu].bgdessinnbligne) { 
								out(menus[posmenu].bgdessin[posdessinx+posdessiny*nbcolbg]); 
							} else out('A');		//Si les positions exc�dent les limites du dessin, remplir par des espaces vides							
							posdessinx++;
						}
						posdessiny++;
					}
				} else {	//La m�moire de l'histoire comme background
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
						base.curspos(titretopleftx, titretoplefty+countligne);		//Mettre le curseur au d�but de la ligne
						for(int countcol=0; countcol<nbcoltitre; countcol++) {
							if(menus[posmenu].titredessin[titrestrpos]!='�') out(menus[posmenu].titredessin[titrestrpos]); 		//'�' est le caract�re transparent pour les dessins (laisse para�tre le background).
							titrestrpos++;
						}			//Pas besoin d'avancer de 1 � la fin de la ligne, car toutes les lignes sont de la m�me longueur, qui est connue
					}
				} else {				//Si le titre est simplement du texte
					//Trouver le texte comporte combien de lignes, et la longueur de chaque ligne
					int nblignetxt = 1; int nbchartxt = 0; StaticVect<int,menunblignesmax> longueurlignetxt;		
					while(titrestrpos<menus[posmenu].titretxt.length()){
						if(menus[posmenu].titretxt[titrestrpos]=='\n') {nblignetxt++; longueurlignetxt.ajout(nbchartxt); nbchartxt=0;} else nbchartxt++;
					} longueurlignetxt.ajout(nbchartxt);	
					//�crire le titre	
					for(int countligne=0; countligne<nblignetxt; countligne++) {
						base.curspos(floor((base.limfenx-longueurlignetxt[countligne])/2), titretoplefty+countligne);		//Mettre le curseur au d�but de la ligne
						for(int countcol=0; countcol<longueurlignetxt[countligne]; countcol++) {
							out(menus[posmenu].titretxt[titrestrpos]); titrestrpos++;
						}
						titrestrpos++;		//� la fin d'une ligne, avancer quand m�me de 1, car on veut d�passer le '\n' qui change de ligne (et qu'on ne veut pas printer)
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
			//Permettre le choix de diff�rents boutons
			while(menus[posmenu].actif){
				clock.reglerheure();
				//Afficher l'effet de s�lection positive		//Un contour s�lectionn� qui s'expend vers l'int�rieur
				if(selectpos>0&&selectpost<clock.currentt){
					chgcolmenuselect(); 
					for(int bouty=0; bouty<menus[posmenu].hauteurbouton; bouty++) {
						for(int boutx=0; boutx<menus[posmenu].largeurbouton; boutx++) {
							if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) > selectpos-2) {	//�quation d'un cercle de rayon de s�lectpos (-2, parce qu'on ne se rend pas � selectpos==0)!
								base.curspos(postopleftx+boutx,postoplefty[menus[posmenu].posactu]+bouty); out(dessinbout[menus[posmenu].posactu][bouty][boutx]);
							}
						}
					}
					selectpos--; selectpost = clock.currentt + round(menus[posmenu].selectdelay/(menus[posmenu].largeurbouton/2));
				}		
				//Afficher l'effet de s�lection n�gative		//Un centre non s�lectionn� qui s'expend vers l'ext�rieur
				if(selectneg>0&&selectnegt<clock.currentt){
					chgcolmenu(); 
					for(int bouty=0; bouty<menus[posmenu].hauteurbouton; bouty++) {
						for(int boutx=0; boutx<menus[posmenu].largeurbouton; boutx++) {
							if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) <= pow(pow(menus[posmenu].hauteurbouton/2,2)+pow(menus[posmenu].largeurbouton/2,2),0.5)-selectneg+1) {	//�quation d'un cercle de rayon de l'hypoth�nuse entre la 1/2 hauteur et la 1/2 largeur!
								base.curspos(postopleftx+boutx,postoplefty[menus[posmenu].pospreced]+bouty); out(dessinbout[menus[posmenu].pospreced][bouty][boutx]);																	//+1, car on ne se rend pas � selectneg == 0.
							}
						}
					}
					selectneg--; selectnegt = clock.currentt + round(menus[posmenu].selectdelay/(menus[posmenu].largeurbouton/2));	
				}
				//Afficher l'effet de "enter"		//Une vague non s�lectionn�e depuis l'int�rieur, vers l'ext�rieur
				if(selectenter>0&&selectentert<clock.currentt){
					chgcolmenu(); 
					for(int bouty=0; bouty<menus[posmenu].hauteurbouton; bouty++) {
						for(int boutx=0; boutx<menus[posmenu].largeurbouton; boutx++) {
							if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) <= pow(pow(menus[posmenu].hauteurbouton/2,2)+pow(menus[posmenu].largeurbouton/2,2),0.5)-selectenter+4) {			//petit cercle non s�lectionn�
								if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) <= pow(pow(menus[posmenu].hauteurbouton/2,2)+pow(menus[posmenu].largeurbouton/2,2),0.5)-selectenter+1) {		//centre s�lectionn� qui prend le dessus
									chgcolmenuselect();			//L'int�rieur qui va �ventuellement prendre le dessus est de couleur s�lectionn�e
								} else chgcolmenu();		//La bande de 3 char de large va �tre de couleur non s�lectionn�e
								base.curspos(postopleftx+boutx,postoplefty[menus[posmenu].pospreced]+bouty); out(dessinbout[menus[posmenu].pospreced][bouty][boutx]);
							}
						}
					}
					if(selectenter!=1) {		//La derni�re fois, il ne faut pas updater, pour que la fin de la boucle puisse comprendre le message!
						selectenter--;
						selectentert = clock.currentt + round(menus[posmenu].enterdelay/(menus[posmenu].largeurbouton/2+3));						
					}			
				}				
				//Afficher l'effet de "escape"					//Une vague s�lectionn�e depuis l'ext�rieur, vers le centre, suivit d'une couronne non s�lectionn�e, mais sur tous les boutons!
				if(selectesc>0&&selectesct<clock.currentt){
					for(int boutcount=0; boutcount<menus[posmenu].boutons.longueur; boutcount++) {		//Propager l'effet � tous les boutons, �ventuellement!
						for(int bouty=0; bouty<menus[posmenu].hauteurbouton; bouty++) {
							for(int boutx=0; boutx<menus[posmenu].largeurbouton; boutx++) {
								if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) > selectesc - 2*abs(boutcount-menus[posmenu].posactu)-5) {		//Faire l'arc le plus pr�s du centre (va finir par dispara�tre)
									if(pow(pow((boutx-menus[posmenu].largeurbouton/2),2)+pow((bouty-menus[posmenu].hauteurbouton/2),2),0.5) > selectesc - 2*abs(boutcount-menus[posmenu].posactu)-2) {		//Faire l'arc �loign� du centre		
										chgcolmenu();		//L'arc le plus �loign�, qui va �ventuellement prendre le dessus, est de couleur non s�lectionn�e		//- 2*abs(boutcount-menus[posmenu].posactu) : c'est pour faire que les boutons les plus loins "se ferment" plus vite
									} else chgcolmenuselect();		//La bande de 3 char de large va �tre de couleur s�lectionn�e: invisible pour le posactu, visible pour les autres boutons.
									base.curspos(postopleftx+boutx,postoplefty[boutcount]+bouty); out(dessinbout[boutcount][bouty][boutx]);
								} 
							}
						}
					}
					if(selectesc!=1)  { 		//La derni�re fois, il ne faut pas updater, pour que la fin de la boucle puisse comprendre le message!
						selectesc--;
						selectesct = clock.currentt + round(menus[posmenu].enterdelay/(menus[posmenu].largeurbouton/2+3+2*max(abs(menus[posmenu].posactu),abs(menus[posmenu].posactu-menus[posmenu].nombrebouton))));
					}
				}			
				//�tre � l'affut de touches du clavier
				if(selectenter==0&&selectesc==0&&selectpos==0&&selectneg==0) {
					if(_kbhit()){
						char charkey; int intkey = _getch();                  		//Enregistrer quelle touche a �t� press�e
						if (intkey == 0 || intkey == -32 || intkey == 224) {      //La valeur est sp�ciale: elle n�cessite de la r�-examiner
							intkey = _getch();                              //Examiner une deuxi�me valeur pour identifier				
							if (intkey == 72) {				//Fl�che du haut : passer au bouton d'en haut
								if(menus[posmenu].posactu>0) {
									selectpos = floor(menus[posmenu].largeurbouton/2); selectpost = clock.currentt;	selectneg = floor(menus[posmenu].largeurbouton/2); selectnegt = clock.currentt;		//Enclencher les effets de s�lection
									menus[posmenu].pospreced = menus[posmenu].posactu; menus[posmenu].posactu--;
								}
							} else if (intkey == 80) {		//Fl�che du bas : passer au bouton d'en bas
								if(menus[posmenu].posactu<menus[posmenu].boutons.longueur-1) {
									selectpos = floor(menus[posmenu].largeurbouton/2); selectpost = clock.currentt;	selectneg = floor(menus[posmenu].largeurbouton/2); selectnegt = clock.currentt;		//Enclencher les effets de s�lection
									menus[posmenu].pospreced = menus[posmenu].posactu; menus[posmenu].posactu++;
								}						
							}
						} else {			//Si la valeur n'est pas "sp�ciale"
							if(intkey == 27) {
								selectesc = floor(menus[posmenu].largeurbouton/2) + 2*max(abs(menus[posmenu].posactu),abs(menus[posmenu].posactu-menus[posmenu].nombrebouton)); 
								menus[posmenu].pospreced = menus[posmenu].posactu; selectesct = clock.currentt;		 //Escape : annuler le menu (va envoyer � l'effet assign� correspondant)
							} else if(intkey == 13) {
								selectenter = floor(menus[posmenu].largeurbouton/2) + 3; 
								menus[posmenu].pospreced = menus[posmenu].posactu; selectentert = clock.currentt;}	 //Enter : confirmer le choix (va envoyer � l'effet assign� correspondant)				
						}
					}		
				}
				//R�aliser l'effet de "enter" / "escape"
				if((selectesc==1&&selectesct<clock.currentt)||(selectenter==1&&selectentert<clock.currentt)) {	
					menus[posmenu].actif = false;			//Fermer ce menu-ci
					if(selectesc==1) effetalire = menus[posmenu].effetescape; else effetalire = menus[posmenu].effets[menus[posmenu].posactu];		//D�cider d'o� on prend les effets � lire
					int counteffet = 0; int effetnb = effetalire.length();
					while(counteffet<effetnb) {
						if(effetalire[counteffet+1]=='a') {				//'a' pour "abort()" -> force la fin du programme
							abort();
						} else if(effetalire[counteffet+1]=='b') {		//'b' pour "biblio" -> modifie une des valeurs de la biblioth�que!
							string nomrayon; string nomlivre; string val;
							int posSpecial = 2;
							while(effetalire[posSpecial] != '�') nomrayon += effetalire[posSpecial++]; 
							posSpecial++; while(!(effetalire[posSpecial] == '~' && effetalire[posSpecial+1] == '>')) nomlivre += effetalire[posSpecial++];
							posSpecial+=2; while(effetalire[posSpecial] != '�') val += effetalire[posSpecial++];							
							biblio.modif(nomrayon,nomlivre,stoi(val));	
						} else if(effetalire[counteffet+1]=='c') {		//'c' pour "clear" -> r�-initialise toute la biblioth�que � z�ro (sauf les rayons fixes)
							for(int rayonpos=biblio.nbrayonsfixes; rayonpos<biblio.rayon.longueur; rayonpos++) {
								for(int livrepos=0; livrepos<biblio.rayon[rayonpos].longueur; livrepos++) {
									biblio.modif(rayonpos,livrepos,0);			//Tout remettre � 0.
								}
							}
						} else if(effetalire[counteffet+1]=='j') {		//'j' pour "jouer" -> checker les motifs automatiques, puis enclencher la boucle "jouer()"
							AutoInterpret();
							ReecrireToutAvecCouleurs();		//Remettre l'�cran au "jeu"
							menus[posmenu].effets[menus[posmenu].posactu] = "�u�";		//Changer le code de ce bouton-ci, pour qu'il retourne au jeu la prochaine fois, plut�t que de lancer une nouvelle session		//ATTENTION! C'EST INORTHODOXE COMME MANI�RE DE PROC�DER!
							jouer();			
						} else if(effetalire[counteffet+1]=='u') {		//'u' pour "unpause" -> remet l'�cran de jeu et remet en activit� les compteurs de temps
																			//ATTENTION! Ce code sp�cial est fait uniquement pour les menus cr��s directement � partir du jeu, dont la fin signifie le retour � la boucle "jouer()" d�j� commenc�e!
							ReecrireToutAvecCouleurs();		//Remettre l'�cran au "jeu"
							counteffet = effetnb;	//�tre certaine d'arr�ter de lire des codes sp�ciaux, pour sortir imm�diatement de ce menu et revenir au jeu
							unpauseall();		
						} else if(effetalire[counteffet+1]=='z') {		//(�z�, 'z' pour... rien en fait. 'm' �tait d�j� pris dans les codes sp�ciaux de canaux, alors j'ai pris z. Que je r�-utilise ici).
							string name; int charcount = counteffet+2;
							while(effetalire[charcount]!='�') {name += effetalire[charcount]; charcount++;}
							counteffet = effetnb;	//�tre certaine d'arr�ter de lire des codes sp�ciaux, pour ne pas d�faire ce que des menus ult�rieurs ont fait
							LireMenus(name);
						}
						if(counteffet < effetnb) counteffet += CodeSpecialLongueur(strintervalle(effetalire,counteffet,effetnb));
					}
				}
			}
		}
		
		//b) Fonction : modiffen ; permet de modifier la taille de le fen�tre de jeu; � mettre obligatoirement � l'int�rieur d'un menu!
		void univers::modiffen() {
			chgcolmenuselect();
			base.curspos(0,0); out("Pour modifier la taille de la fen�tre, utilise les fl�ches du clavier (ou [W]-[A]-[S]-[D]).\nLa taille choisie sera finale. Lorsque tu es satisfait.e, appuie sur [ENTER].");
			bool modifen = true;
			while(modifen) {
				if(_kbhit()){
					char charkey; int intkey = _getch();                  		//Enregistrer quelle touche a �t� press�e
					if (intkey == 0 || intkey == -32 || intkey == 224) {      //La valeur est sp�ciale: elle n�cessite de la r�-examiner
						intkey = _getch();                              //Examiner une deuxi�me valeur pour identifier
						if(intkey == 75) {base.modifdim(false,false);			//fl�che gauche : rapetisser la fen�tre en largeur (colonnes)
						} else if (intkey == 77) {base.modifdim(false,true);	//fl�che droite : agrandir la fen�tre en largeur (colonnes)				
						} else if (intkey == 72) {base.modifdim(true,true);		//Fl�che du haut : agrandir la fen�tre en hauteur (lignes)
						} else if (intkey == 80) {base.modifdim(true,false);}	//Fl�che du bas : rapetisser la fen�tre en hauteur (lignes)
						base.curspos(0,0); out("Pour modifier la taille de la fen�tre, utilise les fl�ches du clavier (ou [W]-[A]-[S]-[D]).\nLa taille choisie sera finale. Lorsque tu es satisfait.e, appuie sur [ENTER].");	
					} else {			//Si la valeur n'est pas "sp�ciale"
						if(intkey == 27) {														 //Escape : terminer le programme
							base.curspos(10,10); out("Vous avez entr� ESC, le programme se ferme donc. Bye-bye!"); abort(); 
						} else if(intkey == 13) {												 //Enter : confirmer le choix
							modifen = false;
							}									
					}
				}
			}
			mem.setsize(base.limtxtx); msnmem.setsize(base.limtxtx,base.limtxty);		//Initier les m�moires du jeu de la bonne taille			
			LireMenus("principal");			//Toujours avoir un menu principal!
		}							//� LA PLACE DE CEL�, CR�ER LE MODIFFEN COMME UN MENU SP�CIAL! POUR QUE RETOURNER AU MENU PR�C�DENT PUISSE BIEN SE PASSER!

	//vi) Fonction pour tout coordonner harmonieusement	----------------------------------------------------------------------		
		
		//a) Fonction jouer();
		void univers::jouer(){
			while(true){				//� faire tout le temps:
				clock.reglerheure();	//Aller chercher le temps
				LireCanaux();		//Lire chaque canal, s'il est pr�t	
				LireMessagerie();		//Lire chaque messagerie, si elle est pr�te	
				UserInputEcho();	//Afficher le fant�me de la commande pr�c�dente
				UserInput();		//Interpr�ter la touche jou�e		
			}
		}


		//b) Fonction debuter();
		void univers::debuter(){
			base.defaultwin();			//Initier la fen�tre par d�faut
			mem.setsize(base.limtxtx); msnmem.setsize(base.limtxtx,base.limtxty);		//Initier les m�moires du jeu de la bonne taille
			LireMenus("principal");		//Initier le menu principal
		}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//6) Fonctions de remplissage ais� des objets utilis�s
	
	//i) Fonctions pour nommer les livres et les rayons de la biblioth�que	----------------------------------------------------------------------		

		//a) Fonction pour cr�er un nouveau rayon et le nommer
		void univers::nvrayon(const string& str) {
			if(biblio.rayon.longueur==biblio.rayon.taille) {out("Il manque de place pour construire le rayon \""); out(str); out("\"!\n\nAgrandissez la biblioth�que pour r�soudre ce probl�me."); abort();}
			biblio.rayon.ajoutvide();								//Passer au prochain rayon
			biblio.nomrayon.ajout(str);
		}
		
		//b) Fonction pour cr�er un nouveau livre et le nommer
		void univers::nvlivre(const string& str) {
			if(biblio.rayon[biblio.rayon.longueur-1].longueur==biblio.rayon[biblio.rayon.longueur-1].taille) {out("Il manque de place pour construire le livre \""); out(str); out("\"!\n\nAgrandissez la biblioth�que ou changez de rayon pour r�soudre ce probl�me."); abort();}
			biblio.rayon[biblio.rayon.longueur-1].ajoutvide();		//Passer au prochain livre
			biblio.nomlivre[biblio.rayon.longueur-1].ajout(str); biblio.modif(biblio.rayon.longueur-1,biblio.rayon[biblio.rayon.longueur-1].longueur-1,0);		//Mettre 0 comme valeur par d�faut (par d�faut, tous les livres = FALSE)
		}

	//ii) Fonctions pour cr�er de nouveaux canaux et les personaliser	----------------------------------------------------------------------		
	
		//a) Fonction pour cr�er un nouveau canal et le nommer
		void univers::nvcanal(const string& str) {                    
			if(canaux.longueur==canaux.taille) {out("Il manque de place pour construire le canal \""); out(str); out("\"!\n\nAugmentez le nombre de canaux dans l'objet \"univers\" pour r�soudre ce probl�me."); abort();}		
			canaux.ajoutvide();
			canaux[canaux.longueur-1].nom = str;
			nomcanaux.ajout(str);
		}
		
		//b) Fonction pour modifier le d�lai du canal    
		void univers::canaldelai(int val) {				
			canaux[canaux.longueur-1].delay = val;          
		}
		
		//c) Fonction pour modifier l'alin�a du canal (l'indentation par d�faut)
		void univers::canalalinea(int val) {
			canaux[canaux.longueur-1].alinea = val;
		}

		//d) Fonction pour modifier la terminaison du canal (qui sera ajout� � la fin lorsque l'on forcera le canal � se vider - pour par exemple fermer les guillements d'une r�plique)
		void univers::canalterminaison(const string& str) {
			canaux[canaux.longueur-1].terminaison = str;
		}

	//iii) Fonctions pour organiser les chapitres et les motifs (permettent l'activation des textes)	----------------------------------------------------------------------		
	
		//a) Fonction pour cr�er un nouveau chapitre
		void univers::nvchapt() {
			if(histoire.filauto.longueur==histoire.filauto.taille) {out("Il manque de place pour construire un nouveau chapitre � l'histoire!\n\nAugmentez le nombre de chapitres dans l'objet \"histoire\" pour r�soudre ce probl�me."); abort();}		
			histoire.filauto.ajoutvide();		
			histoire.filmanu.ajoutvide();											
		}
		
		//b) Fonction pour d�finir les conditions d'activation du chapitre
		void univers::ccond(const string& str) {
			histoire.cadenas[histoire.filmanu.longueur-1].set(str,biblio);
		}
	
		//c) Fonction pour "cr�er" un nouveau motif et le nommer (manuel)
		void univers::nvmanu(const string& str) {
			int poschap = histoire.filmanu.longueur-1;
			if(histoire.filmanu[poschap].longueur==histoire.filmanu[poschap].taille) {out("Il manque de place pour construire le nouveau motif manuel \""); out(str); ;out("\" � l'int�rieur du dernier chapitre!\n\nAugmentez le nombre de motifs dans l'objet \"histoire\", ou passez au prochain chapitre, pour r�soudre ce probl�me."); abort();}						
			histoire.filmanu[poschap].ajoutvide();			//Passer au prochain motif
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].titre = str;     //Conserver le titre, pour y r�f�rer au cas o� une m�me commande appelerait plusieurs motifs.
		} 
		//c)Fonction pour "cr�er" un nouveau motif (automatique)
		void univers::nvauto() {				
			int poschap = histoire.filauto.longueur-1;
			if(histoire.filauto[poschap].longueur==histoire.filauto[poschap].taille) {out("Il manque de place pour construire un nouveau motif automatique � l'int�rieur du dernier chapitre!\n\nAugmentez le nombre de motifs dans l'objet \"histoire\", ou passez au prochain chapitre, pour r�soudre ce probl�me."); abort();}		
			histoire.filauto[poschap].ajoutvide();			//Passer au prochain motif
		}
		
	//iv) Fonctions pour remplir les motifs	----------------------------------------------------------------------			
		
		//a) Fonction pour d�finir le canal du motif (manuel)		//Si le nom fourni est "msn", le motif activera un nouveau "msn" au lieu de s'inscrire dans un canal
		void univers::mcanal(const string& str) {		
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;
			if((str[0]=='m'||str[0]=='M')&&(str[1]=='s'||str[1]=='S')&&(str[2]=='n'||str[2]=='N')&&str.length()==3) { histoire.filmanu[poschap][posmotif].msn = true;	//Msn
			} else histoire.filmanu[poschap][posmotif].canal = ColNameFind(str,nomcanaux);	//Canal
		} 
		//a) Fonction pour d�finir le canal du motif (automatique)		//Si le nom fourni est "msn", le motif activera un nouveau "msn" au lieu de s'inscrire dans un canal
		void univers::acanal(const string& str) {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;
			if((str[0]=='m'||str[0]=='M')&&(str[1]=='s'||str[1]=='S')&&(str[2]=='n'||str[2]=='N')&&str.length()==3) { histoire.filauto[poschap][posmotif].msn = true;	//Msn
			} else histoire.filauto[poschap][posmotif].canal = ColNameFind(str,nomcanaux);  //Canal
		}	
		
		//b) Fonction pour �cire le texte ("mailles") du motif (manuel)
		void univers::mtexte(const string& str) {
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;			
			int strnb = str.length();		//Aller chercher la taille du string
			int debmaille = 0;				//Cr�er un compteur pour le d�but de la maille actuelle
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='�') {
					if(histoire.filmanu[poschap][posmotif].maille.longueur==histoire.filmanu[poschap][posmotif].maille.taille) {out("Dans le motif manuel :\n\n\""); out(str); out("\"\n\n   il y a trop de \"mailles\" diff�rentes, c'est-�-dire de bouts de phrases s�par�s par '�'. Augmentez le nombre de mailles d'un motif manuel ou s�parez celui-ci en plusieurs pour r�soudre ce probl�me."); abort();}		
					if(countstr-debmaille>0) {
						histoire.filmanu[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,countstr-1));
					} else histoire.filmanu[poschap][posmotif].maille.ajout("");   
					debmaille = countstr+1;		//if(...) : �vite les intervalles [1,0] (� la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "��")
				}
			}
			if(histoire.filmanu[poschap][posmotif].maille.longueur==histoire.filmanu[poschap][posmotif].maille.taille) {out("Dans le motif manuel :\n\n\""); out(str); out("\"\n\n   il y a trop de \"mailles\" diff�rentes, c'est-�-dire de bouts de phrases s�par�s par '�'. Augmentez le nombre de mailles d'un motif manuel ou s�parez celui-ci en plusieurs pour r�soudre ce probl�me."); abort();}					
			histoire.filmanu[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,strnb-1));		//Entrer la derni�re maille
			//Ajouter par d�faut un encha�nement lisant l'int�gralit� des mailles, dans l'ordre, avec une probabilit� de 1 (peut alors �tre �cras� par les commandes suivantes)
			histoire.filmanu[poschap][posmotif].enchainement.ajoutvide();      //Cr�er le premier encha�nement
			for(int countmaille = 0; countmaille<histoire.filmanu[poschap][posmotif].maille.longueur; countmaille++){
				histoire.filmanu[poschap][posmotif].enchainement[0].ajout(countmaille);	
			}
			histoire.filmanu[poschap][posmotif].enchaineprob.ajoutvide();      //Cr�er la premi�re probabilit�
			histoire.filmanu[poschap][posmotif].enchaineprob[0].set("1",biblio);	
		}																						
		//b) Fonction pour �cire le texte ("mailles") du motif (automatique)
		void univers::atexte(const string& str) {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;			
			int strnb = str.length();		//Aller chercher la taille du string
			int debmaille = 0;				//Cr�er un compteur pour le d�but de la maille actuelle
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='�') {										
					if(countstr-debmaille>0) {
						if(histoire.filauto[poschap][posmotif].maille.longueur==histoire.filauto[poschap][posmotif].maille.taille) {out("Dans le motif automatique :\n\n\""); out(str); out("\"\n\n   il y a trop de \"mailles\" diff�rentes, c'est-�-dire de bouts de phrases s�par�s par '�'. Augmentez le nombre de mailles d'un motif automatique ou s�parez celui-ci en plusieurs pour r�soudre ce probl�me."); abort();}		
						histoire.filauto[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,countstr-1));
					} else histoire.filauto[poschap][posmotif].maille.ajout("");   
					debmaille = countstr+1;		//if(...) : �vite les intervalles [1,0] (� la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "��")
				}
			}
			if(histoire.filauto[poschap][posmotif].maille.longueur==histoire.filauto[poschap][posmotif].maille.taille) {out("Dans le motif automatique :\n\n\""); out(str); out("\"\n\n   il y a trop de \"mailles\" diff�rentes, c'est-�-dire de bouts de phrases s�par�s par '�'. Augmentez le nombre de mailles d'un motif automatique ou s�parez celui-ci en plusieurs pour r�soudre ce probl�me."); abort();}					
			histoire.filauto[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,strnb-1));		//Entrer la derni�re maille
			//Ajouter par d�faut un encha�nement lisant l'int�gralit� des mailles, dans l'ordre, avec une probabilit� de 1 (peut alors �tre �cras� par les commandes suivantes)
			histoire.filauto[poschap][posmotif].enchainement.ajoutvide();      //Cr�er le premier encha�nement
			for(int countmaille = 0; countmaille<histoire.filauto[poschap][posmotif].maille.longueur; countmaille++){
				histoire.filauto[poschap][posmotif].enchainement[0].ajout(countmaille);	
			}
			histoire.filauto[poschap][posmotif].enchaineprob.ajoutvide();      //Cr�er la premi�re probabilit�
			histoire.filauto[poschap][posmotif].enchaineprob[0].set("1",biblio);	
		}		
			
		//c) Fonction pour d�finir les encha�nements possibles (manuel)
		void univers::mordre(const string& str) {
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int countordre = 0;				//Cr�er un compteur pour l'ordre
			int debnombre = 0;				//Cr�er un compteur d'indexation pour le d�but du nombre
			//Effacer les encha�nements d�j� existants (celles par d�faut)
			histoire.filmanu[poschap][posmotif].enchainement[0].vide();        //Conserve quand m�me le fait qu'un premier encha�nement a �t� cr��
			histoire.filmanu[poschap][posmotif].enchaineprob[0].clean();        //Conserve quand m�me le fait qu'une premi�re probabilit� a �t� cr��e    
			//Ajouter les encha�nements inscrits
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='-'||str[countstr]==';') {
					if(histoire.filmanu[poschap][posmotif].enchainement[countordre].longueur==histoire.filmanu[poschap][posmotif].enchainement[countordre].taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\"\n\n   il y a trop de \"mailles\" � l'\"encha�nement\" #"); out(countordre+1); out(" ( fonction mordre() ). Augmentez le nombre de mailles par encha�nement ou faites �a moins compliqu�, pour r�soudre ce probl�me."); abort();}		
					if(countstr-debnombre>0) {
						histoire.filmanu[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
					} else {out("L'encha�nement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing � la position "); out(countstr); out(". Changer �a svp."); abort();}			
					if(str[countstr]=='-') {}
					if(str[countstr]==';') {
						if(histoire.filmanu[poschap][posmotif].enchainement.longueur==histoire.filmanu[poschap][posmotif].enchainement.taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\"\n\n   il y a trop d'\"encha�nements\" ( fonction mordre() ). Augmentez le nombre d'encha�nements dans un motif manuel ou mettez moins de vari�t�, pour r�soudre ce probl�me. N'oubliez pas d'aussi augmenter le nombre de probabilit�s si vous faites la premi�re option!"); abort();}							
						countordre++; 
						histoire.filmanu[poschap][posmotif].enchainement.ajoutvide(); histoire.filmanu[poschap][posmotif].enchaineprob.ajoutvide();
					}
					debnombre = countstr+1;
				}
			}
			histoire.filmanu[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,strnb-1))-1);		//Entrer le dernier chiffre	
			//Ajouter par d�faut une probabilit� de 1 pour tous les encha�nements inscrits (peut alors �tre �cras� par la commande suivante)
			for(int countench = 0; countench<histoire.filmanu[poschap][posmotif].enchainement.longueur; countench++){
				histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("1",biblio);	
			}		
		}																						
		//c) Fonction pour d�finir les encha�nements possibles (automatique)
		void univers::aordre(const string& str) {
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int countordre = 0;				//Cr�er un compteur pour l'ordre
			int debnombre = 0;				//Cr�er un compteur d'indexation pour le d�but du nombre
			//Effacer les encha�nements d�j� existants (celles par d�faut)
			histoire.filauto[poschap][posmotif].enchainement[0].vide();        //Conserve quand m�me le fait qu'un premier encha�nement a �t� cr��
			histoire.filauto[poschap][posmotif].enchaineprob[0].clean();        //Conserve quand m�me le fait qu'une premi�re probabilit� a �t� cr��e    
			//Ajouter les encha�nements inscrits
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='-'||str[countstr]==';') {
					if(histoire.filauto[poschap][posmotif].enchainement[countordre].longueur==histoire.filauto[poschap][posmotif].enchainement[countordre].taille) {out("Dans le motif automatique :\n\n\""); out(histoire.filauto[poschap][posmotif].maille[0]); out("...\"\n\n   il y a trop de \"mailles\" � l'\"encha�nement\" #"); out(countordre+1); out(" ( fonction mordre() ). Augmentez le nombre de mailles par encha�nement ou faites �a moins compliqu�, pour r�soudre ce probl�me."); abort();}							
					if(countstr-debnombre>0) {
						histoire.filauto[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
					} else {out("L'encha�nement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing � la position "); out(countstr); out(". Changer �a svp."); abort();}			
					if(str[countstr]=='-') {}
					if(str[countstr]==';') {
						if(histoire.filauto[poschap][posmotif].enchainement.longueur==histoire.filauto[poschap][posmotif].enchainement.taille) {out("Dans le motif automatique :\n\n\""); out(histoire.filauto[poschap][posmotif].maille[0]); out("...\"\n\n   il y a trop d'\"encha�nements\" ( fonction mordre() ). Augmentez le nombre d'encha�nements dans un motif automatique ou mettez moins de vari�t�, pour r�soudre ce probl�me. N'oubliez pas d'aussi augmenter le nombre de probabilit�s si vous faites la premi�re option!"); abort();}													
						countordre++; 
						histoire.filauto[poschap][posmotif].enchainement.ajoutvide(); histoire.filauto[poschap][posmotif].enchaineprob.ajoutvide();
						}
					debnombre = countstr+1;
				}
			}
			histoire.filauto[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,strnb-1))-1);		//Entrer le dernier chiffre	
			//Ajouter par d�faut une probabilit� de 1 pour tous les encha�nements inscrits (peut alors �tre �cras� par la commande suivante)
			for(int countench = 0; countench<histoire.filauto[poschap][posmotif].enchainement.longueur; countench++){
				histoire.filauto[poschap][posmotif].enchaineprob[countench].set("1",biblio);	
			}		
		}			
		
		//d) Fonction pour d�finir les probabilit�s associ�es avec chaque encha�nement (manuel)
		void univers::mprob(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int debench = 0;				//Noter la position d'indexation du d�but de l'encha�nement
			int countench = 0;				//Position de l'encha�nement vis�
			//Effacer les probabilit�s d�j� existantes (celles par d�faut)
			for(int countench = 0; countench<histoire.filmanu[poschap][posmotif].enchainement.longueur; countench++){
				histoire.filmanu[poschap][posmotif].enchaineprob[countench].clean();				//Conserve le fait que les probabilit�s ont �t� cr��es en nombre �gal au nombre d'encha�nements
			}				
			//Ajouter les probabilit�s inscrites
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]==';') {					
					if(countstr-debench>0){
						histoire.filmanu[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,countstr-1),biblio);
					} else histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("0",biblio); //Si deux ';' se suivent, mettre la probabilit� de l'encha�nement vide comme 0. �a lui apprendra.
					debench = countstr + 1; countench++;
				}
			}
			if(debench!=strnb) {		//Entrer le dernier chiffre
			histoire.filmanu[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,strnb-1),biblio);
			}
			while(countench++<histoire.filmanu[poschap][posmotif].enchainement.longueur-1){             //Si moins de probabilit�s ont �t� inscrites qu'il n'y a d'encha�nements
				histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("0",biblio);
			}
		}
		//d) Fonction pour d�finir les probabilit�s associ�es avec chaque encha�nement (automatique)
		void univers::aprob(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			int strnb = str.length();		//Aller chercher la taille du string
			int debench = 0;				//Noter la position d'indexation du d�but de l'encha�nement
			int countench = 0;				//Position de l'encha�nement vis�
			//Effacer les probabilit�s d�j� existantes (celles par d�faut)
			for(int countench = 0; countench<histoire.filauto[poschap][posmotif].enchainement.longueur; countench++){
				histoire.filauto[poschap][posmotif].enchaineprob[countench].clean();				//Conserve le fait que les probabilit�s ont �t� cr��es en nombre �gal au nombre d'encha�nements
			}				
			//Ajouter les probabilit�s inscrites
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]==';') {
					if(countstr-debench>0){
						histoire.filauto[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,countstr-1),biblio);
					} else histoire.filauto[poschap][posmotif].enchaineprob[countench].set("0",biblio); //Si deux ';' se suivent, mettre la probabilit� de l'encha�nement vide comme 0. �a lui apprendra.
					debench = countstr + 1; countench++;
				}
			}
			if(debench!=strnb) {		//Entrer le dernier chiffre
			histoire.filauto[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,strnb-1),biblio);
			}
			while(countench++<histoire.filauto[poschap][posmotif].enchainement.longueur-1){             //Si moins de probabilit�s ont �t� inscrites qu'il n'y a d'encha�nements
				histoire.filauto[poschap][posmotif].enchaineprob[countench].set("0",biblio);
			}
		}
		
		//e) Fonction pour d�finir les codes sp�ciaux appel�s au d�but du motif (manuel)
		void univers::mdeb(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].codespeciauxdebut = str;
		}
		//e) Fonction pour d�finir les codes sp�ciaux appel�s au d�but du motif (automatique)
		void univers::adeb(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].codespeciauxdebut = str;
		}
		
		//f) Fonction pour d�finir les codes sp�ciaux appel�s � la fin du motif (manuel)
		void univers::mfin(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;
			histoire.filmanu[poschap][posmotif].codespeciauxfin = str;
		}
		//f) Fonction pour d�finir les codes sp�ciaux appel�s � la fin du motif (automatique)
		void univers::afin(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;
			histoire.filauto[poschap][posmotif].codespeciauxfin = str;
		}
		
		//g) Fonction pour d�finir les conditions sous lesquelles le motif pourra �tre appel� (manuel)
		void univers::mcond(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].condition.set(str,biblio);
		}
		//g) Fonction pour d�finir les conditions sous lesquelles le motif pourra �tre appel� (automatique)
		void univers::acond(const string& str){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].condition.set(str,biblio);
		}
			
		//h) Fonction pour d�finir que le canal sera vid� (override) d�s l'activation de ce motif (manuel)   (d�sactiv� par d�faut)
		void univers::mover(){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].override = true;
		}				
		//h) Fonction pour d�finir que le canal sera vid� (override) d�s l'activation de ce motif (automatique)   (d�sactiv� par d�faut)
		void univers::aover(){
			int poschap = histoire.filauto.longueur-1;
			int posmotif = histoire.filauto[histoire.filauto.longueur-1].longueur-1;		
			histoire.filauto[poschap][posmotif].override = true;
		}					
					
		//i) Fonction pour d�finir que le canal sera mis en attente ("r�serve") lorsque la bonne commande sera envoy�e, et ce jusqu'� la lecture du code sp�cial "�r�" (manuel seulement)   (d�sactiv� par d�faut)
		void univers::mreserve(){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			histoire.filmanu[poschap][posmotif].reserve = true;
		}					
					
		//j) Fonction pour d�finir les combinaisons de mots qui appeleront le motif - les commandes (manuel)
		void univers::mcomm(const string& str){
			int poschap = histoire.filmanu.longueur-1;		//ICI, '|' S�PARE LES SYNONYMES, '&' S�PARE LES GROUPES DE MOTS N�CESSAIRES, "[]" D�NOTE LES MOTS � EXCLURE ET "()" S�PARENT LES DIFF�RENTES FA�ONS DE LE DIRE
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;			//NOTE: LES MOTS � EXCLURE N'ONT PAS DE GROUPES DE MOTS, ILS N'ONT QUE DES SYNONYMES!
			int strnb = str.length();
			int posfac = 0;			//Position des diff�rentes fa�ons de dire la commande
			int posgr = 0;          //Position des groupes de mots n�cessaires
			int possyn = 0;			//Position des synonymes
			bool exclus = false;	//Marqueur pour les mots � exclure
			string mot;				//Mot � inclure/exclure dans la commande
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='('|str[countstr]=='[') {		
					if(str[countstr]=='(') {
						if(histoire.filmanu[poschap][posmotif].commandes.inclus.longueur==histoire.filmanu[poschap][posmotif].commandes.inclus.taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appel� par ::\n\n\""); out(str); out("\"\n\n   il y a trop de diff�rentes fa�ons d'appeler le motif (chaque fa�on diff�rente est suppos�e �tre entre parenth�ses). Augmentez le nombre de fa�ons diff�rentes dans la classe \"commande\" ou mettez moins de vari�t�, pour r�soudre ce probl�me. N'oubliez pas d'augmenter � la fois les mots inclus et les mots exclus, si vous faites la premi�re option!"); abort();}
						histoire.filmanu[poschap][posmotif].commandes.inclus.ajoutvide();         //Noter qu'une nouvelle fa�on de dire la commande commence
						histoire.filmanu[poschap][posmotif].commandes.exclus.ajoutvide();	
					} else if(str[countstr]=='[') exclus = true;
				}else {
					if(countstr==0) {
						histoire.filmanu[poschap][posmotif].commandes.inclus.ajoutvide();         //Noter qu'une nouvelle fa�on de dire la commande commence
						histoire.filmanu[poschap][posmotif].commandes.exclus.ajoutvide();								//Si la premi�re parenth�se est omise (par ex, lorsqu'il y a une seule fa�on de le dire)					
					}
					if(str[countstr]=='|'||str[countstr]=='&'||str[countstr]==')'||str[countstr]==']'){
						if(mot.length()>0&&!(mot.length()==1&&mot[0]==' ')) {		//Si un mot d'au moins une lettre et qui n'est pas seulement un espace a �t� sauvegard�				
							//Enregistrer le mot comme commande
							if(mot[0]==' ') mot = strintervalle(mot,1,mot.length()-1);		//Enlever les espaces en d�but et en fin de mot; permet d'espacer l'�criture des commandes au besoin
							if(mot[mot.length()]==' ') mot = strintervalle(mot,0,mot.length()-2);
							if(exclus) {
								if(histoire.filmanu[poschap][posmotif].commandes.exclus[posfac].longueur==histoire.filmanu[poschap][posmotif].commandes.exclus[posfac].taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appel� par ::\n\n\""); out(str); out("\"\n\n   il y a trop de mots � exclure dans la "); out(posfac); out("e fa�on de dire la commande (chaque mot � exclure est s�par� par '|', et inclus entre crochets \"[]\"). Augmentez le nombre de mots � exclure dans la classe \"commande\" pour r�soudre ce probl�me."); abort();}
								histoire.filmanu[poschap][posmotif].commandes.exclus[posfac].ajout(mot);		//Enregistrer le mot
							} else {
								if(histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].longueur==0) histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].ajoutvide();	//Noter qu'un nouveau groupe de mots commence
								if(histoire.filmanu[poschap][posmotif].commandes.inclus[posfac][posgr].longueur==histoire.filmanu[poschap][posmotif].commandes.inclus[posfac][posgr].taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appel� par ::\n\n\""); out(str); out("\"\n\n   il y a trop de synonymes dans le "); out(posgr); out("e groupe de la "); out(posfac); out("e fa�on de dire la commande (chaque synonyme est s�par� par '|'). Augmentez le nombre synonymes dans la classe \"commande\" our supprimez les plus farfelus, pour r�soudre ce probl�me."); abort();}
								histoire.filmanu[poschap][posmotif].commandes.inclus[posfac][posgr].ajout(mot);
							}
							mot.clear();			//Vider le string de stockage temporaire
							//Interpr�ter le caract�re exact
							if(str[countstr]=='|') {						//Ne rien faire
							}else if(str[countstr]=='&') {
								if(histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].longueur==histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].taille)  {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appel� par ::\n\n\""); out(str); out("\"\n\n   il y a trop de groupes de mots � inclure dans la "); out(posfac); out("e fa�on de dire la commande (chaque fa�on groupe de mot � inclure est s�par� par '&'). Augmentez le nombre de groupes de mots � inclure dans la classe \"commande\" ou simplifiez votre commande pour r�soudre ce probl�me."); abort();}						
								posgr++; histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].ajoutvide();
							} else if(str[countstr]==')') {posgr=0; posfac++;
							} else if(str[countstr]==']') {exclus = false;
							}
						} 
					} else mot+=str[countstr];		//Ajouter la lettre si c'est un caract�re simple	
				}
			}
		}
		
		//k) Fonction pour d�finir les commandes exactes qui appeleront le motif (manuel)
		void univers::mcommexact(const string& str){
			int poschap = histoire.filmanu.longueur-1;
			int posmotif = histoire.filmanu[histoire.filmanu.longueur-1].longueur-1;		
			int strnb = str.length();
			int debmot = 0;			//Noter la position d'indexation du d�but du mot
			for(int countstr=0; countstr<strnb; countstr++){
				if(str[countstr]=='|') {
					if(histoire.filmanu[poschap][posmotif].commandes.exact.longueur==histoire.filmanu[poschap][posmotif].commandes.exact.taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appel� par les commandes exactes :\n\n\""); out(str); out("\"\n\n   il y a trop de fa�ons exactes d'appeler le motif (s�par�es par '|'). Augmentez le nombre de fa�ons exactes diff�rentes dans la classe \"commande\" ou changez de m�thode pour des groupes de mots, ou encore divisez le motif en deux motifs diff�rents, pour r�soudre ce probl�me."); abort();}					
					if(countstr-debmot>0){ 
						histoire.filmanu[poschap][posmotif].commandes.exact.ajout(strintervalle(str,debmot,countstr-1));
					} else histoire.filmanu[poschap][posmotif].commandes.exact.ajout(""); //Si deux ';' se suivent, mettre *RIEN* comme commande exacte possible
					debmot = countstr + 1;
				}
			}	
			if(histoire.filmanu[poschap][posmotif].commandes.exact.longueur==histoire.filmanu[poschap][posmotif].commandes.exact.taille) {out("Dans le motif manuel :\n\n\""); out(histoire.filmanu[poschap][posmotif].maille[0]); out("...\", appel� par les commandes exactes :\n\n\""); out(str); out("\"\n\n   il y a trop de fa�ons exactes d'appeler le motif (s�par�es par '|'). Augmentez le nombre de fa�ons exactes diff�rentes dans la classe \"commande\" ou changez de m�thode pour des groupes de mots, ou encore divisez le motif en deux motifs diff�rents, pour r�soudre ce probl�me."); abort();}								
			if(debmot!=strnb) histoire.filmanu[poschap][posmotif].commandes.exact.ajout(strintervalle(str,debmot,strnb-1));		//Entrer le dernier mot
		}
		
	//iv) Fonctions pour remplir les menus	----------------------------------------------------------------------			
	
		//a) Fonction pour cr�er un nouveau menu (et lui donner un nom)
		void univers::nvmenu(const string& str) {menus.ajoutvide(); nommenus.ajout(str);}

		//b) Fonction pour ajouter un dessin en background au menu
		void univers::menubg(const string& str, int nbligne)  {
			if(str.length()%nbligne!=0) {int nbcharstr = str.length(); out("Le dessin en backgound du menu \""); out(nommenus[menus.longueur-1]); out("\" a "); out(nbligne); out(" lignes, mais poss�dent "); out(nbcharstr); out(" caract�res (il y a des lignes qui ne sont pas compl�tement remplies - il devrait y avoir "); out(ceiling(nbcharstr/nbligne)*nbligne); out(" caract�res)."); abort();}
			menus[menus.longueur-1].bgdessin = str; 
			menus[menus.longueur-1].bgdessinnbligne = nbligne; 
			menus[menus.longueur-1].isbgdessin = true;
			}
		
		//c) Fonction pour d�finir un point d'int�r�t ainsi que sa position souhait�e pour le dessin de background
		void univers::menubgpointinteret(int coordx, int coordy, double fractionfenetrex, double fractionfenetrey) {
			menus[menus.longueur-1].bgptinteretx = coordx; menus[menus.longueur-1].bgptinterety = coordy; 
			menus[menus.longueur-1].bgposinteretx = fractionfenetrex; menus[menus.longueur-1].bgposinterety = fractionfenetrey; 
		}
		
		//d) Fonction pour d�finir des c�t�s comme "bloqu�s" pour le dessin de background, afin qu'ils restent contre le bord de la fen�tre dans les fen�tres trop grandes
		void univers::menubglock(const string& str) {
			if(str.length()==4&&str[0]=='l'&&str[1]=='e'&&str[2]=='f'&&str[3]=='t') { menus[menus.longueur-1].bgleftlocked = true; menus[menus.longueur-1].bgrightlocked = false; 
			} else if(str.length()==5&&str[0]=='r'&&str[1]=='i'&&str[2]=='g'&&str[3]=='h'&&str[4]=='t') { menus[menus.longueur-1].bgrightlocked = true; menus[menus.longueur-1].bgleftlocked = false;
			} else if(str.length()==3&&str[0]=='t'&&str[1]=='o'&&str[2]=='p'){  menus[menus.longueur-1].bgtoplocked = true; menus[menus.longueur-1].bgbottomlocked = false;
			} else if(str.length()==6&&str[0]=='b'&&str[1]=='o'&&str[2]=='t'&&str[3]=='t'&&str[4]=='o'&&str[5]=='m') { menus[menus.longueur-1].bgbottomlocked = true; menus[menus.longueur-1].bgtoplocked = false;
			} else {out("\nLe c�t� bloqu� du menu \""); out(nommenus[menus.longueur-1]); out("\" nomm� comme \""); out(str); out("\" ne correspond pas aux valeurs admises, soit \"left\", \"right\", \"top\" ou \"bottom\"."); abort();}
		}
		
		//e) Fonction pour ajouter un titre en format texte ("string") au menu
		void univers::menutitretxt(const string& str) {menus[menus.longueur-1].titretxt = str;}
		
		//f) Fonction pour ajouter un titre en format dessin au menu
		void univers::menutitredessin(const string& str, int nbligne) {
			if(str.length()%nbligne!=0) {int nbcharstr = str.length(); out("Le dessin en titre du menu \""); out(nommenus[menus.longueur-1]); out("\" a "); out(nbligne); out(" lignes, mais poss�dent "); out(nbcharstr); out(" caract�res (il y a des lignes qui ne sont pas compl�tement remplies - il devrait y avoir "); out(ceiling(nbcharstr/nbligne)*nbligne); out(" caract�res)."); abort();}
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
		
		//i) Fonction pour ajouter un bouton � ce menu, et lui lier des effets
		void univers::menunvbouton(const string& strbout, const string& streff) {
			//Faire les comptes n�cessaires pour voir si le texte du bouton rentre dans l'espace allou�
			int nbligne = 0; int nbcol = 0;
			for(int countstr=0; countstr<strbout.length(); countstr++) {
				if(strbout[countstr]=='\n') {nbligne++; nbcol =0;} else nbcol++;
				if(nbcol>menus[menus.longueur-1].largeurbouton - 4) {out("L'option \""); out(strbout); out("\" du menu \""); out(nommenus[menus.longueur-1]); out("\" a des lignes plus longue que "); out(menus[menus.longueur-1].largeurbouton-4); out(" caract�res (soit la longueur maximale). Pour y rem�dier, trouver un nom plus court, mettre le nom sur davantage de lignes (en utilisant '\\n') ou agrandir tous les \"boutons\" des menus."); abort();}
				if(nbligne>menus[menus.longueur-1].hauteurbouton - 2) {out("L'option \""); out(strbout); out("\" du menu \""); out(nommenus[menus.longueur-1]); out("\" occupe plus de lignes que "); out(menus[menus.longueur-1].hauteurbouton-2); out(" (soit la hauteur maximale du texte). Pour y rem�dier, trouver un nom plus court, le s�parer en moins de fragments (en retirant des '\\n') ou agrandir tous les \"boutons\" des menus."); abort();}				
			}
			menus[menus.longueur-1].boutons.ajout(strbout); menus[menus.longueur-1].effets.ajout(streff);
		}
		
		//j) Fonction pour d�finir l'effet de la touche ESC � l'int�rieur de ce menu
		void univers::menuescape(const string& str) {menus[menus.longueur-1].effetescape = str;}
				
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//7) Aire de tests


/*
				
	int main() {

	//D�clarer l'objet contenant tout
	univers un;		

	//Construire l'univers; puisque ce sont des "member functions", celles-ci doivent obligatoirement �tre dans le "main"		
			
		//Construire la biblioth�que
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
				
		//D�buter un chapitre
		un.nvchapt();
			un.ccond("!intro�desuet");        //Rendre le premier chapitre accessible seulement quand c'est l'intro 
				
		//Construire les motifs
			//Motif automatique : Juste le d�but
				un.nvauto(); un.acanal("je");	                                    	
				un.acond("intro�jeprem");	
				un.adeb("�bintro�jeprem=0�");
				un.afin("�bintro�saraprem=1�");
				un.aover(0);						//N'override pas le canal � son d�but
				un.atexte("T'as froid aux joues.�p1400�"
				"\n�d0�                     �d80�Pis aux cuisses."
				"\nEn fait t'as juste le go�t de r�ler de la marde pour pouvoir agrandir le temps qu'il faut pour trouver l'erreur, les erreurs, � la fois avec le msn qui bug (mais tu crois que tu en a trouv� une bonne?) et avec le texte qui s'affice instantann�ment.'");	
				
			//Motif automatique : Juste le d�but
				un.nvauto(); un.acanal("msn");	                                    	
				un.acond("intro�jeprem");	
				un.adeb("");
				un.afin("�p1000�");
				un.aover(0);						//N'override pas le canal � son d�but
				un.atexte("YoYoYo! Les msn marchent!");				

	//D�buter le jeu
			
		//Ouvrir une fen�tre de bonnes dimensions et initialiser les objets de sauvegarde
		un.MettreDansLeMain();
			
		//Enclencher le premier motif (oui, j'fais �a manuellement pour garder l'uniformit� dans mes enclenchements)
			un.biblio.modif("intro","jeprem",1);
			
		//V�rifier une toute premi�re fois la disponibilit� des motifs automatiques
			un.AutoInterpret();
			
		//Faire une boucle pour que les canaux s'expriment!
			un.jouer();				
			base.curspos(un.cons,0,13);			//Mettre le curseur dans un bel endroit � la fin		
	}		

*/		
