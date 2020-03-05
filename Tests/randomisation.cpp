//Test des randomisations
#define _USE_MATH_DEFINES						//Nécessaire pour aller chercher la valeur de pi
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent (??? Optionnel?)
#include <windows.h>			//Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>				//Nécessaire pour savoir la position du curseur sur Windows
#include <winuser.h>			//Nécessaire pour savoir la position du curseur sur Windows
#include <conio.h>				//Nécessaire pour enregistrer les inputs du clavier
#include <io.h>					//Nécessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>				//Nécessaire pour décrypter les accents en unicode
#include <stdlib.h>				//Nécessaire pour jouer avec des nombres aléatoires  /* srand, rand */	//Ce n'est pas celle qu'on utilise!
#include <random>				//Nécessaire pour jouer avec des distributions statistiques (uniform_int_distribution, normal_distribution, etc.)	//Nécessite c++11	//C'est celle qu'on utilise!

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)


//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Fonctions et objets pour interagir avec la console (Attention: séparé entre Windows et Linux) 	//WINDOWS SEULEMENT EST FAIT!!!

	//i) Classe : consoleobjet ; divers objets permettant de modifier le texte affiché dans la console   	            	//WINDOWS ONLY
	class consoleobjet {
		//Membres
		public:
			HANDLE TxtConsole;									        //Objet permettant de modifier le texte affiché dans la console 
			COORD CursorPosition;                                     	//Objet permettant de se situer sur la console
			CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;                //Objet permettant de connaître la position du curseur dans la console
			CONSOLE_CURSOR_INFO CursorInfo;	                            //Objet permettant de modifier le curseur
			HWND DimConsole;		 			                      //Objet permettant de modifier les dimensions + la position de la console
		//Constructeurs
			//Constructeur par défaut			//Attention, est seulement là pour initier les objets
			consoleobjet() {			
			TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			DimConsole = GetConsoleWindow(); 
			}
	};

	//ii) Fonction: curspos ; déplacer le curseur sur la console                                                          //WINDOWS ONLY
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
		
	//iv) Fonction : chgcol ; change la couleur du texte à entrer                        		                                   //WINDOWS ONLY
	void chgcol(consoleobjet& cons, int txtcol, int bgcol) {
		SetConsoleTextAttribute(cons.TxtConsole, txtcol + 16*bgcol);		//Voir l'entrée du 2020-02-22 pour la légende!
	}
	

	
	//v) Classe : fenetre ; permet de sauvegarder les paramètres relatifs aux caractéristiques de la fenêtre de sortie (console)   	            	//WINDOWS ONLY
	class fenetre {
		//Membres
		public:
			int posfenx, posfeny;     //Positions de la fenêtre sur l'écran                                                    //WINDOWS ONLY
			int sizefenx, sizefeny;   //Taille de la fenêtre en pixel														   //WINDOWS ONLY
			int limfenx, limfeny;     //Dimensions de la fenêtre en terme de nombre de caractères pouvant y être contenus
			int limtxtx, limtxty;     //Dimensions de la portion où le texte s'affiche en terme de nombre de caractères pouvant y être contenus
			int consy;             //Facteur de décalement de la console où apparaît le texte avec la mémoire, où il est stocké
			bool refoule;          //Flag pour voir si le facteur de décalement entre en compte													
		//Constructeurs
			//Constructeur par défaut			//Attention, est seulement là pour initier l'objet hors de la fonction "int main(){}"
			fenetre() {}
		//Fonction de modification : nouvfenetre ; permet de créer une fenêtre de la taille désirée		//Attention! À mettre obligatoirement dans le main()!
		void nouvfenetre(consoleobjet& cons, int posx, int posy, int sizex, int sizey) {
				//MoveWindow(window_handle, x, y, width, height, redraw_window);       //Les unités sont en pixels!
			MoveWindow(cons.DimConsole, posx, posy, sizex, sizey, TRUE);                    //Créer la fenêtre de la bonne taille          //WINDOWS ONLY
			GetConsoleScreenBufferInfo(cons.TxtConsole, &cons.ScreenBufferInfo);                 //Accéder à la taille de la console            //WINDOWS ONLY
			curson(cons,false);                                                     		   //Faire disparaître le curseur                 //WINDOWS ONLY
    		_setmode(_fileno(stdout), _O_U16TEXT);									   //Permettre l'affichage de l'UNICODE           //WINDOWS ONLY  
			limfenx = cons.ScreenBufferInfo.srWindow.Right + 1; limfeny = cons.ScreenBufferInfo.srWindow.Bottom + 1;     //Le srWindow est le seul membre qui donne les bonnes informations
			limtxtx = limfenx; limtxty = limfeny - 1;
		}                  //JE PROFITE DE CETTE FONCTION POUR ÉGALEMENT CHANGER LES PARAMÈTRES DE BASE! ATTENTION!	
	};			

//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) Classes et fonctions générales

	//i) Classes-contenantes	----------------------------------------------------------------------
	
		//a) classe : StaticVect ; sauvegarde un array "semi-dynamique", où la mémoire utilisée est fixe, mais les fonctionnalités sont les mêmes que StringAsVect.
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
					bool ajout(Type nxt, int pos) {			//Ajoute l'entrée à une position précise
						if(fin+1 <= taille) {
							for(int ptpos = fin; ptpos>pos; ptpos--) pt[ptpos] = pt[ptpos-1];
							pt[pos] = nxt; fin++; longueur++;
							return(true);
						} else return(false);
					}
					bool ajout(Type* nxt, int nb) {			//Ajoute un array à la suite du StaticVect
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
				//Fonction d'"ajout" : ajoutvide           //Sert à noter le passage à une entrée supérieure sans ajouter directement un élément (ex: dans StaticVect<TAILLE2,StaticVect<TAILLE1,TYPE>>)			
					void ajoutvide (void) {fin++; longueur++;}
				};		
			
	//ii) Fonctions de conversion	----------------------------------------------------------------------
		
		//a) Fonction : majuscule ; retourne le char, mais en majuscule
		char majuscule(char chr) {
			if(chr=='a') return('A'); else if(chr=='à') return('À'); else if(chr=='â') return('Â'); else if(chr=='ä') return('Ä'); else{
			} if(chr=='b') return('B'); else if(chr=='c') return('C'); else if(chr=='ç') return('Ç'); else if(chr=='d') return('D'); else{
			} if(chr=='e') return('E'); else if(chr=='é') return('É'); else if(chr=='è') return('È'); else if(chr=='ê') return('Ê'); else if(chr=='ë') return('Ê'); else{
			} if(chr=='f') return('F'); else if(chr=='g') return('G'); else if(chr=='h') return('H'); else if(chr=='i') return('I'); else if(chr=='ì') return('Ì'); else if(chr=='î') return('Î'); else if(chr=='ï') return('Ï'); else {
			} if(chr=='j') return('J'); else if(chr=='k') return('K'); else if(chr=='l') return('L'); else if(chr=='m') return('M'); else{
			} if(chr=='n') return('N'); else if(chr=='o') return('O'); else if(chr=='ò') return('Ò'); else if(chr=='ô') return('Ô'); else if(chr=='ö') return('Ö'); else{	
			} if(chr=='p') return('P'); else if(chr=='q') return('Q'); else if(chr=='r') return('R'); else if(chr=='s') return('S'); else{
			} if(chr=='t') return('T'); else if(chr=='u') return('U'); else if(chr=='ù') return('Ù'); else if(chr=='û') return('Û'); else if(chr=='ü') return('Ü'); else{		
			} if(chr=='v') return('V'); else if(chr=='w') return('W'); else if(chr=='x') return('X'); else if(chr=='y') return('Y'); else{
			} if(chr=='z') return('Z'); else return(chr);
		}
				
		//b) Fonction : strintervalle ; retourne un string
		string strintervalle(string str, int deb, int fin) {
			string nwstr;
			for(int pos=deb;pos<=fin;pos++) nwstr+=str[pos];          
			return(nwstr);
		}			
				
		//c) Fonction : CodeSpecialLong ; retourne la longueur d'un code spécial (les deux '§' étant compris)
		int CodeSpecialLongueur(string str){
			int longueur = 1;               //Initier l'objet à retourner
			bool fini = false; int pos = 0;
			int strnb = str.length();
			while(!fini&&pos<strnb) {
				longueur++; pos++;
				if(str[pos]=='§') fini = true;
			}              
			return(longueur);		
		}
		int CodeSpecialLongueurInv(string str){								//Part de la fin du string (pour les msn qui reculent)
			int longueur = 1;               //Initier l'objet à retourner
			bool fini = false; int pos = str.length()-1;
			while(!fini&&pos>0) {
				longueur++; pos--;
				if(str[pos]=='§') fini = true;
			}              
			return(longueur);		
		}
	
		//d) Fonction : CodeSpecialExtract ; extrait une valeur numérique d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
		double CodeSpecialExtractDouble(string str, int longueur){
			string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
			for(int pos=2; pos<longueur-1; pos++) nbonly += str[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)	
			return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
		}		
		int CodeSpecialExtractInt(string str, int longueur){
			string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
			for(int pos=2; pos<longueur-1; pos++) nbonly += str[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)	
			return(stoi(nbonly));           //La fonction stoi convertit les strings en int (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
		}					
		
		//e) Fonction : out ; affiche le caractère dans la console			//Change des char en unicode, genre, un peu?
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
		template<int Taille>
		void out(StaticVect<char,Taille> phrase){
			for(int pos=0; pos<phrase.longueur; pos++){
				out(phrase[pos]);
			}
		}
		void out(int chiffre) {out(to_string(chiffre));}
		void out(unsigned chiffre) {out(to_string(chiffre));}
		void out(double chiffre) {out(to_string(chiffre));}
								
		//f) Fonction : strtobool ; interprète un string pour renvoyer un booléen (similaire à stoi() ou stod() )
		bool strtobool(string str) {
			if(str[0]=='0') {return(false);
			} else if(str[0]=='f'&&str[1]=='a'&&str[2]=='l'&&str[3]=='s'&&str[4]=='e') {return(false);
			} else if(str[0]=='F'&&str[1]=='A'&&str[2]=='L'&&str[3]=='S'&&str[4]=='e') {return(false);
			} else if(str[0]=='1') {return(true);
			} else if(str[0]=='t'&&str[1]=='r'&&str[2]=='u'&&str[3]=='e') {return(true);
			} else if(str[0]=='T'&&str[1]=='R'&&str[2]=='U'&&str[3]=='E') {return(true);
			} else {out("\n\nTentative d'évaluer \""); for(int pos = 0; pos<str.length(); pos++) {out(str[pos]);} out("\" comme un booléen."); abort();}
		}									
								
		//g) Fonction : ColNameFind ; trouve une (la première rencontrée) position d'indexation dans un StaticVect<string,Taille> qui correspond exactement à un string
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
			//Failsafe: Si aucune itération de "str" n'a été trouvée
			out("Aucune itération de \""); out(str); out("\" n'a été trouvée dans {");
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
			//Failsafe: Si aucune itération de "str" n'a été trouvée
			out("Aucune itération de \""); out(str); out("\" n'a été trouvée dans {");
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
	
		//a) Classe : horloge ; permet de stocker le temps depuis le début du programme
		class horloge {
			private:
				unsigned debutt;
			public:
				unsigned currentt;	 
			//Constructeur
			horloge() {debutt = std::chrono::duration_cast< std::chrono::milliseconds >(
		    	std::chrono::system_clock::now().time_since_epoch()
				).count(); currentt = 0;}
			//Fonction de modification : reglerheure ; ré-initie currentt
			void reglerheure() {currentt = std::chrono::duration_cast< std::chrono::milliseconds >(
		    	std::chrono::system_clock::now().time_since_epoch()
				).count() - debutt;}
			//Fonction d'accès
			int getdebutt() {return(debutt);}	
			//Fonctions de statis
			void stop(int val);
			void egrener(string str, int delay);
		};
	
		//b) Fonction : stop ; arrête manuellement l'exécution d'un programme. À utiliser seulement dans un menu!
		void horloge::stop(int val) {
			int targett = currentt + val;
			while(TRUE) {this->reglerheure(); if(currentt>targett) return;}
		}
	
		//c) Fonction : egrener ; fait apparaître le texte manuellement, comme s'il était dans un canal. À utiliser seulement dans un menu!
		void horloge::egrener(string str, int delay) {
			for(int pos=0; pos<str.length(); pos++) {out(str[pos]); stop(delay);}
		}

	//iv) Fonctions de randomisation	----------------------------------------------------------------------		
	
		//a) Fonction : randseed ; initie le générateur de nombre aléatoire rand() avec le "time since epoch" (1er janvier 1970), en millisecondes
		void randseed(horloge clock) {
			srand(abs(clock.getdebutt() -	1583418000));		//La soustraction ici est simplement le temps à l'heure où j'écris cette ligne; pour être sûre que ça bug pas si le nombre est trop grand
		}
	  
		//b) Fonction : randunif ; retourne un integer entre [min, max] (les valeurs sont comprises; "inclusivement")
		int randunif(int min, int max) {
			return(rand() % (max+1) + min);
		}

		//c) Classe : normdist ; construit et conserve une distribution de probabilités approximée, afin d'en tirer des nombres aléatoires à l'aide seulement de la fonction rand()
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
					normdist() {		//Par défaut; permet de construire la distribution de probabilités
						//Donner une probabilité à chaque valeur de 'x' (les 'x' sont les positions de l'array "prob")
							//Je me base sur la définition de la distribution normale pour faire ça, qui va un peu comme suit:
							// f(x) = 1/(sd*(2*pi)^(1/2)) * e^((-1/2)*((x-mean)/sd)^2)
							//Je multiplie les probabilités données ici par la résolution, pour n'avoir que des integer de taille sensible
						double yconst = 1/(originsd*pow(2*M_PI,1/2));		//M_PI, c'est la valeur de pi
						sumprob = 0;
						for(int x=0; x<range; x++){
							prob[x] = round(yconst * exp(-pow(x-originmean,2)/pow(2*originsd,2)) * resolution);
							sumprob += prob[x];				//J'en profite pour aller chercher le total exact des probabilités, qui devrait tendre vers "résolution"
						}
					}						
					//Fonction d'accès : randnormapprox ; retourne un integer aléatoire respectant une distribution normale de (mean,sd)
					int randnormapprox(int mean, int sd){						
						int randprob = randunif(1,sumprob);
						int sumprobnow = 0; int x = -1;
						while(sumprobnow<randprob) sumprobnow += prob[++x];
						//Maintenant, on a obtenu un nombre aléatoire 'x' grâce à une distribution normale de mean = originmean et sd = originsd						
						return(round((x-originmean)*sd/originsd + mean));
					}
			};		
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Test		

int main() {
	horloge clock;		//Setter le temps
	randseed(clock);		//Setter le générateur de nombres aléatoires
	out("\n\nVoici des nombres distribués uniformément entre 0 et 10 :\n");
	for(int test = 0; test<20; test++){
		out(randunif(0,10)); out(", ");
	}
	out("\n\nVoici des nombres distribués normalement, mean = 50 et sd = 20 :\n");
	normdist normbase;
	for(int test = 0; test<20; test++){
		out(normbase.randnormapprox(50,20)); out(", ");
	}	
	out("\n\nVoici un graphique prouvant que ma distribution est bien normale :\n");
	//out("\nVoici la moyenne: "); out(normbase.getmean());;	
	int preuve[20];
	int roll; 
	roll = normbase.randnormapprox(50,20);									//Cette ligne là ne bug pas.
	roll = normbase.randnormapprox(50,20);									//Cette ligne là ne bug pas.
		
	for(int CACA=0; CACA<100; CACA++) preuve[CACA] = 0;		//Toute mettre les valeurs à 0	

	roll = normbase.randnormapprox(50,20);									//Cette ligne là bug.
		
				//MAIS QU'EST-CE QUE LA LIGNE "for(int CACA=0; CACA<100; CACA++) preuve[CACA] = 0;" PEUT BIEN FAIRE DE MAL???????
	
	
	
	for(int nroll=0; nroll<300; nroll++){
		roll = normbase.randnormapprox(9,3);
		if(roll>=0&&roll<20) preuve[roll]++;
	}		
	for(int x=0; x<20; x++){
		out("\n "); out(x); out(" : "); for(int nb=0; nb<preuve[x]; nb++) out('-');
	}
}
