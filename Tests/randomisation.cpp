//Test des randomisations
#define _USE_MATH_DEFINES						//N�cessaire pour aller chercher la valeur de pi
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
#include <stdlib.h>				//N�cessaire pour jouer avec des nombres al�atoires  /* srand, rand */	//Ce n'est pas celle qu'on utilise!
#include <random>				//N�cessaire pour jouer avec des distributions statistiques (uniform_int_distribution, normal_distribution, etc.)	//N�cessite c++11	//C'est celle qu'on utilise!

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)


//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Fonctions et objets pour interagir avec la console (Attention: s�par� entre Windows et Linux) 	//WINDOWS SEULEMENT EST FAIT!!!

	//i) Classe : consoleobjet ; divers objets permettant de modifier le texte affich� dans la console   	            	//WINDOWS ONLY
	class consoleobjet {
		//Membres
		public:
			HANDLE TxtConsole;									        //Objet permettant de modifier le texte affich� dans la console 
			COORD CursorPosition;                                     	//Objet permettant de se situer sur la console
			CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;                //Objet permettant de conna�tre la position du curseur dans la console
			CONSOLE_CURSOR_INFO CursorInfo;	                            //Objet permettant de modifier le curseur
			HWND DimConsole;		 			                      //Objet permettant de modifier les dimensions + la position de la console
		//Constructeurs
			//Constructeur par d�faut			//Attention, est seulement l� pour initier les objets
			consoleobjet() {			
			TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			DimConsole = GetConsoleWindow(); 
			}
	};

	//ii) Fonction: curspos ; d�placer le curseur sur la console                                                          //WINDOWS ONLY
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
		
	//iv) Fonction : chgcol ; change la couleur du texte � entrer                        		                                   //WINDOWS ONLY
	void chgcol(consoleobjet& cons, int txtcol, int bgcol) {
		SetConsoleTextAttribute(cons.TxtConsole, txtcol + 16*bgcol);		//Voir l'entr�e du 2020-02-22 pour la l�gende!
	}
	

	
	//v) Classe : fenetre ; permet de sauvegarder les param�tres relatifs aux caract�ristiques de la fen�tre de sortie (console)   	            	//WINDOWS ONLY
	class fenetre {
		//Membres
		public:
			int posfenx, posfeny;     //Positions de la fen�tre sur l'�cran                                                    //WINDOWS ONLY
			int sizefenx, sizefeny;   //Taille de la fen�tre en pixel														   //WINDOWS ONLY
			int limfenx, limfeny;     //Dimensions de la fen�tre en terme de nombre de caract�res pouvant y �tre contenus
			int limtxtx, limtxty;     //Dimensions de la portion o� le texte s'affiche en terme de nombre de caract�res pouvant y �tre contenus
			int consy;             //Facteur de d�calement de la console o� appara�t le texte avec la m�moire, o� il est stock�
			bool refoule;          //Flag pour voir si le facteur de d�calement entre en compte													
		//Constructeurs
			//Constructeur par d�faut			//Attention, est seulement l� pour initier l'objet hors de la fonction "int main(){}"
			fenetre() {}
		//Fonction de modification : nouvfenetre ; permet de cr�er une fen�tre de la taille d�sir�e		//Attention! � mettre obligatoirement dans le main()!
		void nouvfenetre(consoleobjet& cons, int posx, int posy, int sizex, int sizey) {
				//MoveWindow(window_handle, x, y, width, height, redraw_window);       //Les unit�s sont en pixels!
			MoveWindow(cons.DimConsole, posx, posy, sizex, sizey, TRUE);                    //Cr�er la fen�tre de la bonne taille          //WINDOWS ONLY
			GetConsoleScreenBufferInfo(cons.TxtConsole, &cons.ScreenBufferInfo);                 //Acc�der � la taille de la console            //WINDOWS ONLY
			curson(cons,false);                                                     		   //Faire dispara�tre le curseur                 //WINDOWS ONLY
    		_setmode(_fileno(stdout), _O_U16TEXT);									   //Permettre l'affichage de l'UNICODE           //WINDOWS ONLY  
			limfenx = cons.ScreenBufferInfo.srWindow.Right + 1; limfeny = cons.ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations
			limtxtx = limfenx; limtxty = limfeny - 1;
		}                  //JE PROFITE DE CETTE FONCTION POUR �GALEMENT CHANGER LES PARAM�TRES DE BASE! ATTENTION!	
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

	//iv) Fonctions de randomisation	----------------------------------------------------------------------		
	
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
//3) Test		

int main() {
	horloge clock;		//Setter le temps
	randseed(clock);		//Setter le g�n�rateur de nombres al�atoires
	out("\n\nVoici des nombres distribu�s uniform�ment entre 0 et 10 :\n");
	for(int test = 0; test<20; test++){
		out(randunif(0,10)); out(", ");
	}
	out("\n\nVoici des nombres distribu�s normalement, mean = 50 et sd = 20 :\n");
	normdist normbase;
	for(int test = 0; test<20; test++){
		out(normbase.randnormapprox(50,20)); out(", ");
	}	
	out("\n\nVoici un graphique prouvant que ma distribution est bien normale :\n");
	//out("\nVoici la moyenne: "); out(normbase.getmean());;	
	int preuve[20];
	int roll; 
	roll = normbase.randnormapprox(50,20);									//Cette ligne l� ne bug pas.
	roll = normbase.randnormapprox(50,20);									//Cette ligne l� ne bug pas.
		
	for(int CACA=0; CACA<100; CACA++) preuve[CACA] = 0;		//Toute mettre les valeurs � 0	

	roll = normbase.randnormapprox(50,20);									//Cette ligne l� bug.
		
				//MAIS QU'EST-CE QUE LA LIGNE "for(int CACA=0; CACA<100; CACA++) preuve[CACA] = 0;" PEUT BIEN FAIRE DE MAL???????
	
	
	
	for(int nroll=0; nroll<300; nroll++){
		roll = normbase.randnormapprox(9,3);
		if(roll>=0&&roll<20) preuve[roll]++;
	}		
	for(int x=0; x<20; x++){
		out("\n "); out(x); out(" : "); for(int nb=0; nb<preuve[x]; nb++) out('-');
	}
}
