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
	2019-07-05:
				Dans les fonctions integration() et UserInputInterpret(),
				j'utilise beaucoup d'indexation. Ça devient difficile à lire.
				Je pense que ça n'alourdirait pas trop l'exécution de créer un objet temporaire pour chaque chainon (rendrait le tout plus clair).
				J'ai par contre peur que ça fuck avec les pointeurs, que les objets soient modifiés (sont tous par & référence), etc.
					Je conserve donc cette idée quand j'aurai minimalement une version testée, qui fonctionne.
*/

/*
	2019-07-13:
				Ce qu'il me reste à faire:
					-Tester, avec des vraies mailles (manuelles), si le UserInputInterpret agit comme il le devrait.
								-Tout marche comme il le faudrait; presque.
								
								
								Aussi, je n'arrive pas à lire le deuxième maillon. Est-il actif?
											Ça, c'est parce que les codes spéciaux ne s'update pas. Est-ce parce que la biblio n'est pas "par référence?" (bibliotheque&)
								Nope. La biblio semble travailler sans encombre. Ça doit être... que l'évaluation de la condition?
										Comment voir à l'intérieur de cette évaluation?
										Comment la rendre transparente? Partir de la base?
								
								
											Ce qui serait bien, ce serait de faire un double de la fonction "eval" (dans tous les objets .eval), qui a une verbose.
											Et que je place seulement à l'endroit précis où je veux savoir ce qui se passe.
											
											Ou bien. Je crée une touche spéciale (genre CTRL+I) qui m'évalue en détail les conditions de chaque chapitre?
													Oui, j'aime mieux ça.
								
												Je viens de faire un double de eval(), test(), qui fait une verbose du processus.
												Il ne reste qu'à le faire activer par la touche spéciale.
												Genre la touche spéciale fait seulement,
													pour le premier chapitre (0), tester la condition de chaque maillon; puis out(\n);
															Prendre genre Ctrl + t, mettons. C'est fait.
																
												Le problème qui semble se poser est que l'opérateur '!' ne semble pas reconnu lorsqu'il n'est pas placé en tête de string.
													Les valeurs sensées être '!' sont évaluées comme "==TRUE" et leur valeur est aléatoire -> comme quand la mémoire n'a pas été assignée.
														
								
								
								
								
									Also, c'est étrange, le clignotement des mauvaises commandes finit sans effacer la commande, contrairement à la version précédente...?
									
									
									Ah, autre chose également, une bordée d'espaces (" ") suit la première commande;
													C'est pour cette raison que la deuxième itération suit avec beaucoup de décalage.
												Pourquoi y-a-t-il tant d'espaces?
									
									
					-Créer un équivalent de la fonction pour les mailles automatiques
					-Intégrer dans l'interprétation de l'input la première (ou toutes?) majuscule optionnelle
					-Peut-être changer la mémoire de "long terme, finie" à "court terme, infinie" en sauvant moins de lignes mais en écrivant par-dessus?
					-Je ne sais pas si j'ai fait tous les "checks" de (dés)activation des canaux... À la fois quand le canal s'épuise, et quand il est overridé!
*/					

/*
	2019-09-04:
				Liste des séparateurs maison:
					'§' sert à séparer les codes spéciaux du reste dans le texte à lire
					';' sert à séparer les genres (féminin;non binaire/neutre;masculin)
					'µ' sert à séparer les segments de texte (mailles) dans la construction d'un chaînon
					';' sert à séparer les différents enchaînements
					'-' sert à séparer les chiffres d'un même enchaînement
					';' sert à séparer les différentes probabilités d'enchaînement (pratique mais ± logique; considérer un changement?)
					Dans les commandes, '|' sépare les synonymes, '&' sépare les groupes de mots, "[]" dénote les mots à exclure et "()" séparent les façons de le dire
*/

/*
	2019-09-19:
				Oh; il serait pertinent de changer la fonction pour changer de couleur, et de mettre au lieu des références
				à la bibliothèque; genre avoir une fonction "changer couleur à" qui prend un string ou un numéro en argument;
				genre "clignotement" ou quelque chose du genre...? Genre mettre catégories comme "clair", "obscur", "normal"...?
							//Si je le mets dans la bibliothèque, faudra que ce soit en 'int': Donc séparer le back-ground et le texte?
								//Et après, à chaque fois que je change de couleur, de faire la conversion?
									//Et peut-être mettre des systèmes de vérifications à chaque fois que je dois changer la couleur;
										: Est-ce que c'était déjà setté sur 'clair'?		
*/

/*
	2019-09-22:
				Idée: il serait peut-être bien, pour les rayons "rigides" de la bibliothèque, comme les marqueurs de genre, les références de couleur et les *...*,
				de:
					a) Soit les intégrer de manière immuable à la classe, dans le constructeur de l'objet, et peut-être même mettre un membre de cette classe spécifiant leur position;
					b) Soit les lier à des objets additionnels, stockés dans "monde", qui conservent la position *actuelle* du rayon.
							//Juste à l'écrire comme ça, j'ai beaucoup mieux a).
*/

/*
	2019-10-22:
				Eurggghhh. 
				La fonction "substr()" n'agit vraiment pas comme je le pensais (j'ai simplement mal lu).
				Je pensais qu'elle agissait comme ma fonction "intervalle()": prendre le début et la fin comme arguments.
				À la place, elle prend le début, puis le nombre de caractères à inclure.
				Il faudra donc que je remplace toutes les "substr()" par une fonction maison que je coderai moi-même. Beurgh.
*/


//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent (??? Optionnel?)
#include <windows.h>           //Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>            //Nécessaire pour savoir la position du curseur sur Windows
#include <winuser.h>		   //Nécessaire pour savoir la position du curseur sur Windows
#include <conio.h>             //Nécessaire pour enregistrer les inputs du clavier
#include <io.h>				   //Nécessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>			   //Nécessaire pour décrypter les accents en unicode
#include <stdlib.h>     	   //Nécessaire pour jouer avec des nombres aléatoires  /* srand, rand */

/*
	2019-07-05:
A typical way to generate trivial pseudo-random numbers in a determined range using rand is to use the modulo of the returned value 
		by the range span and add the initial value of the range:

v1 = rand() % 100;         // v1 in the range 0 to 99
v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 
*/


using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Classes-contenantes générales

	//i) classe : StaticVect ; sauvegarde un array "semi-dynamique", où la mémoire utilisée est fixe, mais les fonctionnalités sont les mêmes que StringAsVect.
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
		
	//iv) Fonction: curson ; affiche ou cache le curseur                        		                                   //WINDOWS ONLY
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
	template<int Taille>
	void out(StaticVect<char,Taille> phrase){
		for(int pos=0; pos<phrase.longueur; pos++){
			out(phrase[pos]);
		}
	}
	void out(int chiffre) {std::wcout << chiffre;}
	void out(double chiffre) {std::wcout << chiffre;}


	//vi) Fonction : chgcol ; change la couleur du texte à entrer
	void chgcol(string color) {
		WORD code;                                            //Voir Internet pour la légende
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

	//vii) Fonction : strtobool ; interprète un string pour renvoyer un booléen (similaire à stoi() ou stod() )
	bool strtobool(string str) {
		if(str[0]=='0') {return(false);
		} else if(str[0]=='f'&str[1]=='a'&str[2]=='l'&str[3]=='s'&str[4]=='e') {return(false);
		} else if(str[0]=='F'&str[1]=='A'&str[2]=='L'&str[3]=='S'&str[4]=='e') {return(false);
		} else if(str[0]=='1') {return(true);
		} else if(str[0]=='t'&str[1]=='r'&str[2]=='u'&str[3]=='e') {return(true);
		} else if(str[0]=='T'&str[1]=='R'&str[2]=='U'&str[3]=='E') {return(true);
		} else {out("\n\nTentative d'évaluer \""); for(int pos = 0; pos<str.length(); pos++) {out(str[pos]);} out("\" comme un booléen."); abort();}
	}
	
	//viii) Fonction : ColNameFind ; trouve une (la première rencontrée) position d'indexation dans un StaticVect<string,Taille> qui correspond exactement à un string
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
	
	//ix Fonction : stop ; arrête manuellement l'exécution d'un programme. À utiliser seulement dans un menu!
	void stop(int val) {
		int targett = timems() + val;
		while(TRUE) {if(timems()>targett) return;}
	}

	//x Fonction : egrener ; fait apparaître le texte manuellement, comme s'il était dans un canal. À utiliser seulement dans un menu!
	void egrener(string str, int delay) {
		for(int pos=0; pos<str.length(); pos++) {out(str[pos]); stop(delay);}
	}
	
	//xi Fonction : strintervalle ; retourne un string
	string strintervalle(string str, int deb, int fin) {
		string nwstr;
		for(int pos=deb;pos<=fin;pos++) nwstr+=str[pos];
		return(nwstr);
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Classes-contenantes spécialisées (canaux et autres)

	//DEBUGGG                  //But no longer debug??
	const int taillecanal = 2;
	const int taillegroupes = 5;
									//2019-08-18: Ouin, ça se peut que cette méthode soit permanente, puisque je n'arrive pas à bien inclure ces nombres
												// à l'intérieur des classes. 

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
			int pausedt;	    //Différence entreposée entre nxtt et currentt, dans le cas où l'exécution est arrêtée (ex: faire apparaître un menu)				
			int delay;          //Déclarer le délai de base entre chaque entrée
			int posx, posy;		//Déclarer les coordonnées de la dernière entrée dans la mémoire (la précédente)   
								//les positions de la consoles sont définies en décalant ces dernières
			string txt;   		//Déclarer le texte qui reste à lire  				
			bool actif;			//Déclarer le compteur d'activité
			double vit;         //Déclarer la vitesse actuelle de défilement et de pauses (toujours par rapport à la base, 1)
			string nom;			//Déclarer le nom que porte le canal
		//Constructeur
		canal() : delay(150), posx(-1), posy(0), actif(false), vit(1) {nxtt = timems();}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
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
			string couleur;           //Couleur de base du texte													//PT LE BOUGER DANS BIBLIO, OU JUSTE BONIFIER L'INFO ICI?
																															////////////////////////////////////////////////////////////////////
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
	class input {
		//Valeurs membres
		public:
			StaticVect<char,200> commande;          	//Phrase que contient le buffer        
			int inputpos;                   //Position d'indexation du prochain caractère    == StaticVect.fin? Non! Car ça peut bouger!
			bool accepted;                  //Flag concernant la dernière commande; utile pour l'affichage visuel
			bool busy;						//Flag concernant la dernière commande; utile pour l'affichage visuel
		//Constructeur par défaut
			input() : inputpos(0), accepted(false), busy(false) {}
	};							
						
	//v) classe : inputecho ; permet l'affichage résiduel des commandes (acceptées ou refusées)	
	class inputecho {
		//Valeurs membres
		public:
			StaticVect<char,200> commande;
			StaticVect<int,50> clignote;               //Conserve les instructions pour le clignotement : positif = affiche, négatif = pause.	
			string couleur;                            //Conserve la couleur du clignotement
			bool actif;							       //Compteur d'activité
			int nxtt;         						   //Moment où la prochaine entrée sera traitée         
			int pausedt;							   //Différence entreposée entre nxtt et currentt, dans le cas où l'exécution est arrêtée (ex: faire apparaître un menu)				
		//Constructeur par défaut
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
		//Fonction d'accès : acces ; retourner la valeur à certaines positions
		int acces(int posrayon, int poslivre) {return(rayon[posrayon][poslivre]);}
		//Fonction de modification : modif ; modifie la valeur à certaines positions
		void modif(int posrayon, int poslivre, int value) {rayon[posrayon][poslivre] = value;}
		void modif(string rayonstr, string livrestr, int value) {
			int posrayon = ColNameFind(rayonstr,nomrayon);
			int poslivre = ColNameFind(livrestr,nomlivre[posrayon]);
			rayon[posrayon][poslivre] = value;
			
			out("Ceci est la valeur voulue: "); out(value); out(".   Ceci est la valeur enregistrée: "); out(rayon[posrayon][poslivre]);  out("Ceci est leur position: ("); out(posrayon); out(","); out(poslivre); out(")");      //DEBUG
		}
	};

	//vii) classe : inteval ; contient l'expression à évaluer (la plus simple) ; constructeur transforme les noms de "livre" en position d'indexation
	class inteval {
		//Valeurs membres
		public:
			int rayonpos;   		//Position d'indexation de la "famille" de l'argument comparé à gauche					
			int livrepos;			//Position d'indexation de l'argument comparé à gauche, à l'intérieur de sa "famille"
			int boolval; int intval;
			int constbool; int constint;      //TRUE si les valeurs sont booléennes ou int, à la place d'évaluées.
		//Constructeur
		inteval ()  : constbool(false), constint(false) {}; //Constructeur par défaut : vide. 
		//Fonction de modification : set() ; permet de construire l'objet avec une expression
		void set(string str, bibliotheque& biblio) {
			int strnb = str.length();
			string rayon, livre;    //Initier un string, dans lequel seront insérés seulement les noms des rayons/livres
			int strpos, pos; strpos = 0; pos = 0; while(str[pos]!='¶'&&pos<strnb) rayon += str[pos++];
			//Évaluer si le string contient des noms ou une valeur														//CHANGER CETE LIGNE??????
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
		//Fonction d'accès : eval()	
		int eval(bibliotheque& biblio) {if(constbool) return(boolval); else if(constint) return(intval); else return(biblio.acces(rayonpos,livrepos));}	
		
		
		
		//DEBUGGGGGGG
		void test(bibliotheque& biblio) {if(constbool) out(boolval); else if(constint) out(constint); else out(biblio.acces(rayonpos,livrepos));}
		
		
		
	};	

	//viii) classe : intoper ; contient les opérations d'expressions booléennes évaluables
	class intoper {
		//Valeurs membres
		public:
			char operateur;      	//Opérateur
			intoper* LHcompos;
			intoper* RHcompos;
			inteval* LHsimple;
			inteval* RHsimple;
			bool Lcompos; bool Rcompos;				//TRUE si les valeurs sont composites
		//Constructeur
		intoper ()  : Lcompos(false), Rcompos(false) {}; //Constructeur par défaut : vide. 
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
					if(str[pos]=='(') nbPAR++;	//Gère les parenthèses imbriquées 
					if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
					pos++;
				} if(!trouvPAR) out("\n\nLa parenthèse n'est pas refermée dans: "+str); abort();
				if(trouvPAR&&pos==strnb) {str = strintervalle(str,1,strnb-1); trouvPAR = false; pos = 0;   //Supprimer la parenthèse et remettre les compteurs à 0, pour continuer		
				} else Lcompos = true;		//Noter l'expression à droite comme composite (car elle contient au minimum une parenthèse), et continuer à partir d'après la parenthèse
			} else { 							
			//Cas général : on cherche '+' ou '-', car '*' et '/' ont la priorité d'opération
				while(!trouvAD&&pos<strnb) {
					if(str[pos]=='+'||str[pos]=='-') {posAD = pos; trouvAD = true;}
					if(!trouvMU&&(str[pos]=='*'||str[pos]=='/')) {posMU = pos; trouvMU = true;}
					pos++;							
				}
				if(trouvAD) {
					operateur = str[posAD]; 					
					LH = strintervalle(str,0,posAD);					//Définir les limites de l'expression à gauche						
					RH = strintervalle(str,posAD+1,strnb);		//Définir les limites de l'expression à droite						
					if(trouvMU) Lcompos = true; //(car '*''/' ont la priorité d'opération sur '+''-')
					while(!Rcompos&&pos<strnb) {if(str[pos]=='+'||str[pos]=='-'||str[pos]=='*'||str[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite
				} else if(trouvMU) {
					operateur = str[posMU];  
					LH = strintervalle(str,0,posMU);					//Définir les limites de l'expression à gauche						
					RH = strintervalle(str,posMU+1,strnb);		//Définir les limites de l'expression à droite
					pos = posMU + 1; while(!Rcompos&&pos<strnb) {if(str[pos]=='*'||str[pos]=='/') Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite				
				} else {
					operateur = ' '; LH = str;   //Aucune opération, seulement une évaluation				
				}		
			}			
			//Assigner les valeurs aux membres
			if(Lcompos) {LHcompos = new intoper; LHcompos->set(LH,biblio); LHsimple = nullptr;} else {LHsimple = new inteval; LHsimple->set(LH,biblio); LHcompos = nullptr;}
			if(operateur!=' ') {if(Rcompos) {RHcompos = new intoper; RHcompos->set(RH,biblio); RHsimple = nullptr;} else {RHsimple = new inteval; RHsimple->set(RH,biblio); RHcompos = nullptr;}}
		}			
		//Fonction d'accès : eval()				
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


	//ix) classe : boolcompar ; contient les comparaisons d'expressions booléennes évaluables
	class boolcompar {
		//Valeurs membres
		public:
			char comparateur;      //Opérateur de comparaison
			intoper* LH;
			intoper* RH;
			bool constbool;			   //TRUE si l'argument à gauche doit être comparé à un booléen implicite
			bool boolval;		
		//Constructeur ;
		boolcompar () : constbool(false), boolval(0) {}; //Constructeur par défaut : vide. 
		//Fonction de modification : set() ; permet de construire l'objet avec une expression
		void set(string str, bibliotheque& biblio) {
			int strnb = str.length();
			if(strnb==0) {comparateur = ' ';}        //Cas spécial: retourne TRUE automatiquement
			//Recueillir l'opérateur			
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
				if(posEX==0) {constbool = true; boolval = false; comparateur = '=';	poscomparateur = strnb; //Cas spécial réchappé de la fonction précédente (si jamais elle en laisse passer un)
				
						//ÉCRIT COMME CELÀ, ÇA NE MARCHE PAS, CAR ÇA N'EFFACE PAS LE '!' (À LA FIN, LH EST DÉFINI COMME [0, strnb])
				
				
				curspos(2,20); out("CACACACACACACACACACACACACACACA"); abort();
									//Bon. C'est officiel, "la fonction précédente laisse échapper des cas comme ça".
												//Faire soit que ça n'arrive pas, soit qu'ils soient normalisés et bien écrits.
														//Genre que le LH soit 			LH->set(strintervalle(str,1,poscomparateur),biblio);
				
											//Mais je préférerais savoir pourquoi ça arrive et éliminer cette fuite.
											
												//Oh, tiens, la réponse est simple. Mettons dans:
																//  0 == 1 & ! 3 == 4
																//Le comparateur va être '&', et LH et RH vont être simples, séparés entre "0 == 1" et "! 3 == 4"
											
														//Ici, le '!' est clairement un compositeur. Il permet de modifier l'expression de la comparaison "3 == 4".
																//Il faudrait donc le traiter comme tel.
																
																	//a) Que L'ÉCRITURE soit obligatoirement " 0 == 1 & !( 3 == 4 ) ",   //(boooooohhhhhh)
																	
																	//b) Intégrer '!X' où X est n'importe quoi sauf '=' comme vrai compositeur (pas comme exception)
																			//b) est bien entendu l'option à choisir.
																			
																				//Et si b) est sélectionné... Techniquement, y'aura plus de "cas réchappés".
																	
																	
											
				
				
				} else {poscomparateur = posEX;	comparateur = '!'; if(trouvEG&&posEG!=posEX+1) erreur = true;}		//!=
			} else if(trouvPE) {poscomparateur = posPE; if(trouvEG&&posEG==posPE+1) {comparateur = '«';    			//<=
				} else if(!trouvEG) comparateur = '<'; else erreur = true;											//<	
			} else if(trouvGR) {poscomparateur = posGR;	if(trouvEG&&posGR==posGR+1) {comparateur = '»';   			//>=
				} else if(!trouvEG) comparateur = '>'; else erreur = true;											//>	
			} else if(trouvEG) {poscomparateur = posEG; if(str[posEG+1]=='=') comparateur = '='; else erreur = true;		//==	
			} else {constbool = true; boolval = true; comparateur = '=';	poscomparateur = strnb;} //Cas spécial : "comparaison implicite de la valeur à true"
			//Message d'erreur
			if(erreur) {out("\n\nL'opérateur n'est pas complet dans: "+str); abort();}
			//Créer les objets intoper
			LH = new intoper; LH->set(strintervalle(str,0,poscomparateur),biblio);
			if(!constbool){
				RH = new intoper;
				if(comparateur=='='||comparateur=='!'||comparateur=='«'||comparateur=='»') RH->set(strintervalle(str,poscomparateur+2,strnb),biblio); else RH->set(strintervalle(str,poscomparateur+1,strnb),biblio);	
			}			
		}
		//Fonction d'accès : eval
		bool eval(bibliotheque& biblio) {
			if(comparateur=='=') {
				if(constbool) return(LH->eval(biblio)==boolval); else return(LH->eval(biblio)==RH->eval(biblio));				// ==
			} else if(comparateur=='!') {
				if(constbool) return(LH->eval(biblio)!=boolval); else return(LH->eval(biblio)!=RH->eval(biblio));				// !=
			} else if(comparateur=='<') {
				if(constbool) return(LH->eval(biblio)<boolval); else return(LH->eval(biblio)<RH->eval(biblio));					// <
			} else if(comparateur=='«') {
				if(constbool) return(LH->eval(biblio)<=boolval); else return(LH->eval(biblio)<=RH->eval(biblio));				// <=
			} else if(comparateur=='<') {
			if(constbool) return(LH->eval(biblio)>boolval); else return(LH->eval(biblio)>RH->eval(biblio));						// >
			} else if(comparateur=='»') {
			if(constbool) return(LH->eval(biblio)>=boolval); else return(LH->eval(biblio)>=RH->eval(biblio));					// >=
			}
		}
		
		
		//DEBUGGGG
		bool test(bibliotheque& biblio) {
				if(constbool) {LH->test(biblio); out(comparateur); out(comparateur); out(boolval);} else {LH->test(biblio); out(comparateur); out(comparateur); RH->test(biblio);}	
		}
		
		
		
		
	};


	//x) classe : boolcompos ; permet de stoker des expressions booléennes évaluables; (LH = "left hand", à gauche ; RH = "Right hand", à droite)
	class boolcompos {
		//Valeurs membres
		public:
			char compositeur;   //'&' ou '|' ou '!' (==false) ou ' ' (==true, sans comparaison)
			boolcompar* LHsimple; boolcompos* LHcompos; 
			boolcompar* RHsimple; boolcompos* RHcompos;
			bool Lcompos; bool Rcompos;	
		//Constructeur
		boolcompos () : Lcompos(false), Rcompos(false)	{}; //Constructeur par défaut : vide. 
		//Fonction de modification : set() ; permet de construire l'objet avec une expression		
		void set(string str, bibliotheque& biblio) {    //false : valeurs par défaut qui pourront changer à l'intérieur du constructeur
			int strnb = str.length();
			string LH;
			string RH;
			int posPAR; bool trouvPAR = false; int nbPAR = 0;
			int posOU; bool trouvOU = false; 
			int posET; bool trouvET = false;
			int posEX; bool trouvEX = false;
			int pos = 0;
			bool general = true;
			
			
			/*
						//Toute la section du cas spécial "!" est fausse et mal écrite!
						
								//Effectivement, une expression telle que !0 == 1 & 3 == 4 devrait être lue comme "!(0 == 1) & (3 == 4)", plutôt que "!(0 == 1 & 3 == 4)"
									//Il faudrait simplement traiter le compositeur '!' au même titre que les autres compositeurs, c'est-à-dire lui donner un "trouvEX" et un "posEX".
									//Le point d'exclammation aurait alors la plus XXXXX priorité d'opération. (plus grande? parce qu'on doit le régler dans les petits bouts avant de passer aux grands bouts?)
										//Donc, il se chercherait à la fin, quand il n'y a plus de | ni de &.
									
						
	        if(str[0]=='!') {  
			//Cas spécial : compositeur '!'
	       		compositeur = '!'; 							//le (opérateur + RH) deviennent : "==false" : régler ce cas particulier tout de suite
				while(!trouvOU&&pos<strnb) {
					if(!trouvET&&str[pos]=='&') {posET = pos; trouvET = true;}
					if(!trouvOU&&str[pos]=='|') {posOU = pos; trouvOU = true;}		
					pos++;		
				}
				LH = strintervalle(str,1,strnb);		//Définir les limites de l'expression à gauche					
				if(trouvET||trouvOU) Lcompos = true;     //Définir si LH est composite
		    } else 
			*/
			
			
			
			if(str[0]=='(') {  
			//Cas spécial: l'expression commence par une parenthèse (ex: "( 0==4 | 5<2 )"  ou  "(3>=5) & 3==7" ) 			
				while(!trouvPAR&&pos<strnb) {
					if(str[pos]=='(') nbPAR++;	//Gère les parenthèses imbriquées 
					if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
					pos++;
				} if(!trouvPAR) {out("\n\nLa parenthèse n'est pas refermée dans: "); out(str); abort();}
				if(trouvPAR&&pos==strnb) {str = strintervalle(str,1,strnb-1); trouvPAR = false; pos = 0;   //L'expression entière est entre parenthèse : Supprimer celles-ci et remettre les compteurs à 0, pour continuer au cas général
				} else Lcompos = true;		//Noter l'expression à droite comme composite (car elle contient au minimum une parenthèse), et continuer au cas général à partir d'après la parenthèse
			} else if(str[0]=='!'&&str[1]=='(') {  
			//Cas spécial: l'expression commence par "le contraire" d'une parenthèse (ex: "!( 6<2 | 4==4 )"  ou  "!( 6>3 | 5<6) & 1==3" )			
				while(!trouvPAR&&pos<strnb) {
					if(str[pos]=='(') nbPAR++;	//Gère les parenthèses imbriquées 
					if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
					pos++;
				} if(!trouvPAR) {out("\n\nLa parenthèse n'est pas refermée dans: "); out(str); abort();}
				if(trouvPAR&&pos==strnb) {compositeur = '!'; LH = strintervalle(str,2,strnb-1); Lcompos = true; general = false;   //L'expression entière est "contraire" : passer le cas général		
				} else Lcompos = true;		//Noter l'expression à droite comme composite (car elle contient un "contraire"), et continuer au cas général à partir d'après la parenthèse	
			}
			if(general) {
			//Cas général : on cherche '|', car '!' et '&' ont la priorité d'opération
				while(!trouvOU&&pos<strnb) {
					if(str[pos]=='|') {posOU = pos; trouvOU = true;}
					if(!trouvET&&str[pos]=='&') {posET = pos; trouvET = true;}
					if(!trouvEX&&str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=') {posEX = pos; trouvEX = true;}   //Si '!' agit bien comme compositeur, c'est-à-dire qu'il n'est pas accolé à un '='
					pos++;							
				}
				if(trouvOU) {
					compositeur = '|';
					LH = strintervalle(str,0,posOU);					//Définir les limites de l'expression à gauche						
					RH = strintervalle(str,posOU+1,strnb);		//Définir les limites de l'expression à droite						
					if(trouvEX|trouvET) Lcompos = true; //(car '!' et '&' ont la priorité d'opération sur '|')
					while(!Rcompos&&pos<strnb) {if(str[pos]=='|'||str[pos]=='&'||(str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=')) Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite
				} else if(trouvET) {  
					compositeur = '&';
					LH = strintervalle(str,0,posET);					//Définir les limites de l'expression à gauche						
					RH = strintervalle(str,posET+1,strnb);		//Définir les limites de l'expression à droite
					pos = posET + 1; while(!Rcompos&&pos<strnb) {if(str[pos]=='&'||(str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=')) Rcompos = true; pos++;}	//Trouver si l'expression à droite est composite				
				} else if(trouvEX&&posEX==0) {
					compositeur = '!';
					LH = strintervalle(str,1,strnb);					//Définir les limites de l'expression à gauche	
																//Il n'y a pas d'expression à droite
				} else {
					compositeur = ' '; LH = str;   //Aucune comparaison, seulement une évaluation (et il n'y a pas d'expression à droite)				
				}		
			}			
			//Assigner les valeurs aux membres
			if(Lcompos) {LHcompos = new boolcompos; LHcompos->set(LH,biblio); LHsimple = nullptr;} else {LHsimple = new boolcompar; LHsimple->set(LH,biblio); LHcompos = nullptr;}
			if(compositeur!='!'&&compositeur!=' ') {if(Rcompos) {RHcompos = new boolcompos; RHcompos->set(RH,biblio); RHsimple = nullptr;} else {RHsimple = new boolcompar; RHsimple->set(RH,biblio); RHcompos = nullptr;}}		
		}
		//Fonction d'accès : eval
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
		
		
		
		
		
	//DEBUGGG	
		void test(bibliotheque& biblio) {
			if(compositeur==' '||compositeur=='!'){
				out(compositeur); out(compositeur); out(compositeur); if(Lcompos) LHcompos->test(biblio); else LHsimple->test(biblio);
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


//xi) classe : commande ; permet le stockage de "mots de passe" pour les commandes, à chercher dans le USERINPT
	class commande {
		//Valeurs membres
		public:
			static const int tailledifferentes = 5;
			static const int taillegroupes = 5;
			static const int taillesynonymes = 12;
			StaticVect<StaticVect<StaticVect<string,taillesynonymes>,taillegroupes>,tailledifferentes> inclus;		//Mots qui doivent être inclus dans l'expression
					//Niveau le plus extérieur: Différentes façon de dire la commande (ex: manger le concombre / se nourrir / mastiquer) ... Genre?
					//Niveau médian: Différents groupes de mots qui doivent être inclus (ex: manger / concombre)
					//Niveau le plus intérieur: Différents synonymes à l'intérieur du groupe de mots (ex: manger/absorber/grignoter/engouffrer/avaler)
			StaticVect<StaticVect<string,taillegroupes>,tailledifferentes> exclus;						//Mots qui doivent être absents de l'expression
					//Niveau le plus extérieur: Différentes façon de dire la commande
					//Niveau le plus intérieur: Différents mots qui ne doivent pas se retrouver dans la commande
			StaticVect<string,taillegroupes> exact;										//Expressions qui doivent exactement être recopiées, sans faute (soit seule manière d'appeler, soit confirmation si ambiguité; voir UserInputInterpret())
			bool ifexact;													//TRUE si une expression exacte est nécessairement recherchée
		//Constructeur
		commande() : ifexact(false) {};	
	};		
	
	
	//xii) classe : chainonauto ; permet le stockage du texte et des conditions d'apparition (automatique)
	class chainonauto {
		//Membres
		public:
			StaticVect<string,10> maille;						//Texte à lire
			StaticVect<StaticVect<int,10>,10> enchainement;  	//int réfère aux positions des mailles         
			StaticVect<intoper,10> enchaineprob;        	 	//Avec le même ordre d'indexation que enchaînement
			boolcompos condition;								//Conditions à respecter pour l'ajout au canal sans UserInput 
			string codespeciauxdebut;
			string codespeciauxfin;
			bool override;										//TRUE si l'activation de chaînon vide instantannément le canal utilisé
			int canal;											//Position du canal dans lequel écrire le texte
		//Constructeur
		chainonauto() : override(false) {};
	};
	
	//xii) classe : chainonmanu ; permet le stockage du texte et des conditions d'apparition (manuelle)
	class chainonmanu {
		//Membres
		public:
			StaticVect<string,10> maille;						//Texte à lire
			StaticVect<StaticVect<int,10>,10> enchainement;  	//int réfère aux positions des mailles         
			StaticVect<intoper,10> enchaineprob;        	 	//Avec le même ordre d'indexation que enchaînement
			boolcompos condition;								//Conditions à respecter pour l'ajout au canal avec UserInput				
			string codespeciauxdebut;
			string codespeciauxfin;
			bool override;										//TRUE si l'activation de chaînon vide instantannément le canal utilisé
			int canal;											//Position du canal dans lequel écrire le texte
			commande commandes;                					//Mots à rechercher pour l'ajout au canal à partir du UserInput			
			bool getbusy;                                       //TRUE si le UserInput devient bloqué après que ce chaînon ait été appelé
		//Constructeur
		chainonmanu() : getbusy(true), override(false) {};	
	};
	
	//xiii) classe : fil ; permet de stocker toutes les textes + commandes selon des catégories (ex: chapitres), pour faciliter la recherche
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
//4) Fonction spécialisées de petite taille

	//i) Fonction : CodeSpecialLong ; retourne la longueur d'un code spécial ('§' compris)
	int CodeSpecialLongueur(string str){
		int longueur = 1;               //Initier l'objet à retourner
		bool fini = false; int pos = 1;
		while(!fini&&pos<str.length()) {
			longueur++; pos++;
			if(str[pos]=='§') fini = true;
		}              
		return(longueur);		
	}

	//ii) Fonction : CodeSpecialExtract ; extrait une valeur numérique d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
	double CodeSpecialExtractDouble(string str, int longueur){
		string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
		int longmax = longueur - 1;      //Le dernier caractère étant le '§'		
		for(int pos=2; pos<longmax; pos++) nbonly += str[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)	
		return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}		
	//ii) Fonction : CodeSpecialExtract ; extrait une valeur numérique d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
	int CodeSpecialExtractInt(string str, int longueur){
		string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres (2X'§' + 1 identifiant en char)
		int longmax = longueur - 1;      //Le dernier caractère étant le '§'		
		for(int pos=2; pos<longmax; pos++) nbonly += str[pos];    //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire (identifiant en char)	
		return(stoi(nbonly));           //La fonction stoi convertit les strings en int (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}			

	//iii) Fonction : UserInputEcho ; validant graphiquement l'acceptation ou le refus des commandes envoyées
	void UserInputEcho(input& inp, inputecho& inpecho, const fen& base) {	
		chgcol(inpecho.couleur);
		//Clignoter
		if(inpecho.clignote[0]>0){
			curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
		} else {
			curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(' ');			
		}
		chgcol(base.couleur);                       //Revenir à la couleur de base	
		inpecho.nxtt += abs(inpecho.clignote[0]);        //Updater le "next time"
		inpecho.clignote.suppression(1);            //Passer à la prochaine instruction
		if(inpecho.clignote.longueur==0) inpecho.actif = false;			//Vérifier s'il reste toujours du stock à passer dans le canal	
		}	
	
	//iv) Fonction : pause ; arrête les compteurs des canaux
	void pause(StaticVect<canal,taillecanal>& canaux) {
		int currentt = timems();
		for(int poscan=0; poscan<canaux.longueur; poscan++) canaux[poscan].pausedt = canaux[poscan].nxtt - currentt;			
	}
	void unpause(StaticVect<canal,taillecanal>& canaux) {
		int currentt = timems();
		for(int poscan=0; poscan<canaux.longueur; poscan++) canaux[poscan].nxtt = currentt + canaux[poscan].pausedt + canaux[poscan].delay * 5;					
	}
	
	//vi) Fonction : integration ; ajoute un chainon à un canal
	void integrationmanu(int chapitrepos, int chainonpos, StaticVect<canal,taillecanal>& canaux, fil& histoire, bibliotheque& biblio) {
		int currentt = timems();	
		//Overloader le canal si nécessaire
		if(histoire.chainemanu[chapitrepos][chainonpos].override) canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].txt = "";
		//Choisir l'enchaînement à insérer dans le canal
		int sumprob = 0; StaticVect<int,10> vectprob;
		for(int posprob=0; posprob<histoire.chainemanu[chapitrepos][chainonpos].enchaineprob.longueur; posprob++) {	//Évaluer chaque probabilité
			sumprob += histoire.chainemanu[chapitrepos][chainonpos].enchaineprob[posprob].eval(biblio); vectprob[posprob] = sumprob; 
		}
		int randval = rand() % sumprob;  //Obtenir une valeur aléatoire entre [0,sumprob[			
		int choix; 
		for(int posprob=0; posprob<histoire.chainemanu[chapitrepos][chainonpos].enchaineprob.longueur; posprob++) {
			if(randval<vectprob[posprob]) {choix = posprob; break;}
		}	
		
		/*
		
		
			//DEBUG:::
			curspos(2,4); out("L'enchaînement voulu est :");
		for(int posench=0; posench<histoire.chainemanu[chapitrepos][chainonpos].enchainement[choix].longueur; posench++) {
			out(histoire.chainemanu[chapitrepos][chainonpos].enchainement[choix][posench]); out("-");
		}	
		
			curspos(2,9); out("Le texte voulu est :");
		for(int posench=0; posench<histoire.chainemanu[chapitrepos][chainonpos].enchainement[choix].longueur; posench++) {
			out(histoire.chainemanu[chapitrepos][chainonpos].maille[histoire.chainemanu[chapitrepos][chainonpos].enchainement[choix][posench]]); out("µ");
		}	
		
		
			out("\nFait que c'est weird, parce que ... Oh shit. C'est cave. C'est juste que les positions que j'ai mis, c'est les positions normales. -1 en C++");
		
		
			curspos(2,13); out("Pis le nombre de mailles est: "); out(histoire.chainemanu[chapitrepos][chainonpos].maille.longueur);
			curspos(2,15); out("Pis toutes les mailles bout à bout ressemblent à: ");
		for(int posm=0; posm<histoire.chainemanu[chapitrepos][chainonpos].maille.longueur; posm++) {
			out(histoire.chainemanu[chapitrepos][chainonpos].maille[posm]);
		}
		
		
		
		*/
		
		//Ajouter le texte au canal
		canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].txt += histoire.chainemanu[chapitrepos][chainonpos].codespeciauxdebut;   //Code spéciaux début
		for(int posench=0; posench<histoire.chainemanu[chapitrepos][chainonpos].enchainement[choix].longueur; posench++) {
			canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].txt += histoire.chainemanu[chapitrepos][chainonpos].maille[histoire.chainemanu[chapitrepos][chainonpos].enchainement[choix][posench]];
		}		
		canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].txt += histoire.chainemanu[chapitrepos][chainonpos].codespeciauxfin;		//Code spéciaux fin	
		//Updater le nxtt pour qu'il commence à l'intégration
		if(!canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].actif) canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].nxtt = timems();
		//Marquer le canal comme actif
		if(canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].txt.length()>0) canaux[histoire.chainemanu[chapitrepos][chainonpos].canal].actif = true;
	}

	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//5) Fonctions de remplissage aisé des objets utilisés
	
	//Contenant pour conserver tous les objets
	class univers {
	//Membres
	public:
		fil histoire;
		bibliotheque biblio;
		StaticVect<canal,taillecanal> canaux;
		input inp;
		inputecho inpecho;
		
	//Constructeur
		univers() {};
	}; 
	
	//Fonction pour créer un nouveau rayon et le nommer
	void nvrayon(univers& monde, const string& str) {
		monde.biblio.rayon.ajoutvide();								//Passer au prochain rayon
		monde.biblio.nomrayon.ajout(str);
	}
	
	//Fonction pour créer un nouveau livre et le nommer
	void nvlivre(univers& monde, const string& str) {
		monde.biblio.rayon[monde.biblio.rayon.longueur-1].ajoutvide();		//Passer au prochain livre
		monde.biblio.nomlivre.ajout(str); monde.biblio.modif(monde.biblio.rayon.longueur-1,monde.biblio.rayon[monde.biblio.rayon.longueur-1].longueur-1,0);		//Mettre 0 comme valeur par défaut (par défaut, tous les livres = FALSE)
	}
	
	//Fonction pour créer un nouveau canal et le nommer
	void nvcanal(univers& monde, const string& str) {
		monde.canaux.ajoutvide();
		monde.canaux[monde.canaux.longueur-1].nom = str;
	}
	
	//Fonction pour modifier le délai du canal
	void canaldelai(univers& monde, int val) {
		monde.canaux[monde.canaux.longueur-1].delay = val;
	}
	
	//Fonction pour modifier la vitesse du canal
	void canalvit(univers& monde, double val) {
		monde.canaux[monde.canaux.longueur-1].vit = val;
	}
	
	//Fonction pour créer un nouveau chapitre
	void nvchapt(univers& monde) {
		monde.histoire.chaineauto.ajoutvide();
		monde.histoire.chainemanu.ajoutvide();
	}
	
	//Fonction pour définir les conditions d'activation du chapitre
	void ccond(univers& monde, const string& str) {
		monde.histoire.cadenas[monde.histoire.chainemanu.longueur-1].set(str,monde.biblio);
	}

	//Fonction pour "créer" un nouveau chaînon et le nommer (manuel)
	void mtitre(univers& monde, const string& str) {		
		int poschap = monde.histoire.chainemanu.longueur-1;
		monde.histoire.chainemanu[poschap].ajoutvide();			//Passer au prochain chaînon
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;		
		monde.histoire.chainemanu[poschap][poschai].commandes.exact.ajout(str);     //Conserver le titre comme "commande exacte"
	} 
	
	//Fonction pour écire le texte ("mailles") du chaînon (manuel)
	void mtexte(univers& monde, const string& str) {
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;			
		int strnb = str.length();		//Aller chercher la taille du string
		int debmaille = 0;				//Créer un compteur pour le début de la maille actuelle
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='µ') {										
				if(countstr-debmaille>0) {
					monde.histoire.chainemanu[poschap][poschai].maille.ajout(strintervalle(str,debmaille,countstr-1));
				} else monde.histoire.chainemanu[poschap][poschai].maille.ajout("");   
				debmaille = countstr+1;		//if(...) : évite les intervalles [1,0] (à la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "µµ")
			}
		}
		monde.histoire.chainemanu[poschap][poschai].maille.ajout(strintervalle(str,debmaille,strnb));		//Entrer la dernière maille
	}																						//AJOUTER PAR DÉFAUT UN SEUL ENCHAÎNEMENT LISANT TOUTES LES MAILLES DANS L'ORDRE + SA PROBABILITÉ DE 1; (sera overridé par la prochaine commande)
	
	//Fonction pour définir les enchaînements possibles (manuel)
	void mordre(univers& monde, const string& str) {
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;		
		int strnb = str.length();		//Aller chercher la taille du string
		int countordre = 0;				//Créer un compteur pour l'ordre
		int debnombre = 0;				//Créer un compteur d'indexation pour le début du nombre
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='-'||str[countstr]==';') {
				if(countstr-debnombre>0) {
					monde.histoire.chainemanu[poschap][poschai].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
				} else {out("L'enchaînement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing à la position "); out(countstr); out(". Changer ça svp."); abort();}			
				if(str[countstr]=='-') {}
				if(str[countstr]==';') {countordre++; monde.histoire.chainemanu[poschap][poschai].enchainement.ajoutvide();}
				debnombre = countstr+1;
			}
		}
		monde.histoire.chainemanu[poschap][poschai].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,strnb))-1);		//Entrer le dernier chiffre
		
		
		/*
		//DEBUGGG			
		curspos(2,6); out("La longueur des enchaînements est: "); out(monde.histoire.chainemanu[poschap][poschai].enchainement.longueur);
				//Maintenant, que contient le maillon?
		curspos(2,8); out("Les enchaînements enregistrés sont:");
		for(int countench = 0; countench<monde.histoire.chainemanu[poschap][poschai].enchainement.longueur; countench++){
			for(int countordre = 0; countordre<monde.histoire.chainemanu[poschap][poschai].enchainement[countench].longueur; countordre++){
				out(monde.histoire.chainemanu[poschap][poschai].enchainement[countench][countordre]); out("-");
			}
			
			out(";");
		}		
		abort();
		*/
		
	}																						//AJOUTER PAR DÉFAUT UNE PROBABILITÉ DE 1 POUR TOUS LES ENCHAÎNEMENTS; (sera overridé par la prochaine commande)
	
	//Fonction pour définir les probabilités associées avec chaque enchaînement (manuel)
	void mprob(univers& monde, const string& str){
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;		
		int strnb = str.length();		//Aller chercher la taille du string
		int debench = 0;				//Noter la position d'indexation du début de l'enchaînement
		int countench = 0;				//Position de l'enchaînement visé
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]==';') {
				if(countstr-debench>0){
					monde.histoire.chainemanu[poschap][poschai].enchaineprob[countench].set(strintervalle(str,debench,countstr-1),monde.biblio);
				} else monde.histoire.chainemanu[poschap][poschai].enchaineprob[countench].set("0",monde.biblio); //Si deux ';' se suivent, mettre la probabilité de l'enchaînement vide comme 0. Ça lui apprendra.
				debench = countstr + 1; countench++; monde.histoire.chainemanu[poschap][poschai].enchaineprob.ajoutvide();
			}
		}
		if(debench!=strnb) {		//Entrer le dernier chiffre
		monde.histoire.chainemanu[poschap][poschai].enchaineprob[countench].set(strintervalle(str,debench,strnb),monde.biblio);
		monde.histoire.chainemanu[poschap][poschai].enchaineprob.ajoutvide();
		}
	}
	
	//Fonction pour définir les codes spéciaux appelés au début du chaînon (manuel)
	void mdeb(univers& monde, const string& str){
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;		
		monde.histoire.chainemanu[poschap][poschai].codespeciauxdebut = str;
	}
	
	//Fonction pour définir les codes spéciaux appelés au début du chaînon (manuel)
	void mfin(univers& monde, const string& str){
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;
		monde.histoire.chainemanu[poschap][poschai].codespeciauxfin = str;
	}
	
		//ICI, '|' SÉPARE LES SYNONYMES, '&' SÉPARE LES GROUPES DE MOTS NÉCESSAIRES, "[]" DÉNOTE LES MOTS À EXCLURE ET "()" SÉPARENT LES DIFFÉRENTES FAÇONS DE LE DIRE
			//NOTE: LES MOTS À EXCLURE N'ONT PAS DE GROUPES DE MOTS, ILS N'ONT QUE DES SYNONYMES!
	//Fonction pour définir les combinaisons de mots qui appeleront le chaînon (manuel)
	void mcomm(univers& monde, const string& str){
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;
		int strnb = str.length();
		int posfac = 0;			//Position des différentes façons de dire la commande
		int posgr = 0;          //Position des groupes de mots nécessaires
		int possyn = 0;			//Position des synonymes
		bool exclus = false;	//Marqueur pour les mots à exclure
		string mot;				//Mot à inclure/exclure dans la commande
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='('|str[countstr]=='[') {		
				if(str[countstr]=='(') {
					monde.histoire.chainemanu[poschap][poschai].commandes.inclus.ajoutvide();         //Noter qu'une nouvelle façon de dire la commande commence
					monde.histoire.chainemanu[poschap][poschai].commandes.exclus.ajoutvide();	
				} else if(str[countstr]=='[') exclus = true;
			}else {
				if(countstr==0) {
					monde.histoire.chainemanu[poschap][poschai].commandes.inclus.ajoutvide();         //Noter qu'une nouvelle façon de dire la commande commence
					monde.histoire.chainemanu[poschap][poschai].commandes.exclus.ajoutvide();								//Si la première parenthèse est omise (par ex, lorsqu'il y a une seule façon de le dire)					
				}
				if(str[countstr]=='|'||str[countstr]=='&'||str[countstr]==')'||str[countstr]==']'){
					if(mot.length()>0&&!(mot.length()==1&&mot[0]==' ')) {		//Si un mot d'au moins une lettre et qui n'est pas seulement un espace a été sauvegardé				
						//Enregistrer le mot comme commande
						if(mot[0]==' ') mot = strintervalle(mot,1,mot.length());		//Enlever les espaces en début et en fin de mot; permet d'espacer l'écriture des commandes au besoin
						if(mot[mot.length()]==' ') mot = strintervalle(mot,0,mot.length()-1);
						if(exclus) {monde.histoire.chainemanu[poschap][poschai].commandes.exclus[posfac].ajout(mot);		//Enregistrer le mot
						} else {
							if(monde.histoire.chainemanu[poschap][poschai].commandes.inclus[posfac].longueur==0) monde.histoire.chainemanu[poschap][poschai].commandes.inclus[posfac].ajoutvide();	//Noter qu'un nouveau groupe de mots commence
							monde.histoire.chainemanu[poschap][poschai].commandes.inclus[posfac][posgr].ajout(mot);
						}
						mot.clear();			//Vider le string de stockage temporaire
						//Interpréter le caractère exact
						if(str[countstr]=='|') {						//Ne rien faire
						}else if(str[countstr]=='&') {posgr++; monde.histoire.chainemanu[poschap][poschai].commandes.inclus[posfac].ajoutvide();
						} else if(str[countstr]==')') {posgr=0; posfac++;
						} else if(str[countstr]==']') {exclus = false;
						}
					} 
				} else mot+=str[countstr];		//Ajouter la lettre si c'est un caractère simple	
			}
		}
	}
	
	//Fonction pour définir les commandes exactes qui appeleront le chaînon (manuel)
	void mcommexact(univers& monde, const string& str){
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;		
		int strnb = str.length();
		int debmot = 0;			//Noter la position d'indexation du début du mot
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='|') {
				if(countstr-debmot>0){ 
					monde.histoire.chainemanu[poschap][poschai].commandes.exact.ajout(strintervalle(str,debmot,countstr-1));
				} else monde.histoire.chainemanu[poschap][poschai].commandes.exact.ajout(""); //Si deux ';' se suivent, mettre *RIEN* comme commande exacte possible
				debmot = countstr + 1;
			}
		}	
		if(debmot!=strnb) monde.histoire.chainemanu[poschap][poschai].commandes.exact.ajout(strintervalle(str,debmot,strnb));		//Entrer le dernier mot
	}
	
	//Fonction pour définir les conditions sous lesquelles le chaînon pourra être appelé (manuel)
	void mcond(univers& monde, const string& str){
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;		
		monde.histoire.chainemanu[poschap][poschai].condition.set(str,monde.biblio);
	}
	
	//Fonction pour définir si le canal sera vidé dès l'activation de ce chaînon (manuel)
	void mover(univers& monde, bool bl){
		int poschap = monde.histoire.chainemanu.longueur-1;
		int poschai = monde.histoire.chainemanu[monde.histoire.chainemanu.longueur-1].longueur-1;		
		monde.histoire.chainemanu[poschap][poschai].override = bl;
	}				
	
				
	/*		//EXEMPLE:
			mtitre(monde,"Je suis confortable");
			mtexte(monde,"Bien.§p6000§ µParfait.§p6000§ µ\n\n                   Désirez-vous vous divertir§p1000§...?");
			mordre(monde,"1-3;1-2");
			mprob(monde,"1;1");
			mcomm(monde,"(Je|J' & suis|reste & confortable|bien installé|bien installée|bien installé.e [ne suis pas|jamais]) (Ça va|Correct)");
			mcond(monde,"Laure¶debut&!Laure¶confo");
			mdeb(monde,"§bLaure¶actif=1§§bLaure¶confo=1§§v0.8§");
			mfin(monde,"§bLaure¶actif=0§")
	*/	

//------------------------------------------------------------------------------------------------------------------------------------------------------
//6) Fonction LireCanal()
void LireCanal(StaticVect<canal,taillecanal>& canaux, int canpos, fen& base, memoire& mem, bibliotheque& biblio) {
	//Updater le "next time"
	canaux[canpos].nxtt += canaux[canpos].delay;
	//Interpréter les "codes spéciaux" (§...§)
	if(canaux[canpos].txt[0]=='§'){		
		//Déterminer la longueur du code spécial
			int CodeSpecialLong = CodeSpecialLongueur(canaux[canpos].txt);			
		//Lire le code spécial		
			if(canaux[canpos].txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture		
				double val = CodeSpecialExtractDouble(canaux[canpos].txt,CodeSpecialLong);       //Extraire le temps que durera la pause
				canaux[canpos].nxtt += round(val * canaux[canpos].vit);                    //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					
			} else if(canaux[canpos].txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = CodeSpecialExtractDouble(canaux[canpos].txt,CodeSpecialLong);       //Extraire la nouvelle vitesse
				canaux[canpos].vit = val;
			} else if(canaux[canpos].txt[1]=='g'){		//'g' pour "gender" -> choisir le bon accord
																								 //Sélectionner le genre
				int genreselect;
				
				//SÉLECTIONNER LE GENRE						//RESTE À FAIRE! 
														//PEUT-ÊTRE SIMPLEMENT RÉSERVER LE PREMIER RAYON DE LA BIBLIOTHÈQUE AUX GENRES?
				
				
				
				int genreactuel = 0; 
				int posdebut = 3; int posfin = CodeSpecialLong - 1;		//Valeurs par défauts
				for(int posSpecial=3;posSpecial<CodeSpecialLong; posSpecial++) {				 //Délimiter le bon accord				
					if(canaux[canpos].txt[posSpecial]==';') {
						genreactuel++;
						if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect-1) posfin = posSpecial - 1;
					}
				}
				string temptxt;										//Ajouter le bon accord à la suite du code spécial (devient: Code spécial - accord - reste du canal
				temptxt  += strintervalle(canaux[canpos].txt,0,CodeSpecialLong); temptxt += strintervalle(canaux[canpos].txt,posdebut,posfin); temptxt += strintervalle(canaux[canpos].txt,CodeSpecialLong,canaux[canpos].txt.length());				
				canaux[canpos].txt = temptxt;
				canaux[canpos].nxtt -= canaux[canpos].delay;									//Ajuster le "next time" pour supprimer le délai entre l'interprétation du code et la lecture de l'accord
			} else if(canaux[canpos].txt[1]=='b'){		//'b' pour "biblio" -> modifier la bibliothèque
				string nomrayon; string nomlivre; string val;
				int posSpecial = 3;
				while(canaux[canpos].txt[posSpecial] != '¶') nomrayon += canaux[canpos].txt[posSpecial++]; 
				posSpecial++; while(canaux[canpos].txt[posSpecial] != '=') nomlivre += canaux[canpos].txt[posSpecial++];
				posSpecial++; while(canaux[canpos].txt[posSpecial] != '§') val += canaux[canpos].txt[posSpecial++];							
				biblio.modif(nomrayon,nomlivre,stoi(val));
				
				
				//DEBUGGGG
				out("        Ceci est la valeur enregistrée dans LireCanal(): "); out(biblio.acces(ColNameFind(nomrayon,biblio.nomrayon),ColNameFind(nomlivre,biblio.nomlivre[ColNameFind(nomrayon,biblio.nomrayon)])));
				
			}
		
							
			  //EN AJOUTER UN (code spécial) POUR PLACER LE CURSEUR À LA FIN DE LA CONSOLE	
			
			
				//AJOUTER AUSSI UN CODE SPÉCIAL POUR OVERLOADER DES CANAUX
			
			
			   //AJOUTER AUSSI UN CODE SPÉCIAL POUR ...?
			
				
			
		//Effacer le code spécial du canal
		canaux[canpos].txt = strintervalle(canaux[canpos].txt,CodeSpecialLong+1,canaux[canpos].txt.length());
	} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
		//Dealer avec la situation où on a à sauter une ligne (créer les lignes supplémentaires et updater les diverses positions)
			bool jump = false;
			if(canaux[canpos].txt[0]=='\n'|canaux[canpos].posx>=base.limtxtx-1) jump = true;     //base.limtxtx - 1 ; car c'est en integer, et canaux[canpos].posx commence à 0!
			if(jump) {	
				mem.newline(canaux[canpos].posy);                     //Introduit une nouvelle ligne à la suite de la position qui lui est fournie	
				//Updater le correctif de décalage de la console par rapport à la mémoire
					if(base.refoule) base.consy++; else if(mem.frontline>base.limtxty) {base.refoule = true; base.consy++;} 						
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore saturée: on pousse vers le bas!
						if(canaux[canpos].posy!=mem.frontline-1) {                             //S'il y a d'autres lignes à repousser vers le bas
							//Ré-écrire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,canaux[canpos].posy+1);  //Mettre le curseur au début de la reconstruction
								for(int county = canaux[canpos].posy + 1 ; county <= mem.frontline ; county++) {   
									for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est saturée: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "reléguant ce qui y était déjà vers le haut")
							curspos(0,canaux[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
						//Tout ré-écrire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county <= canaux[canpos].posy; county++){             //base.consy : facteur de décalage de la console
								for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}	
				//Updater les positions dans les autres canaux    //Parce que leur position dans la mémoire a bougé //la position dans la console est quant à elle gérée par base.consy
				for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {
					if(countcan==canpos) continue;                                    //la mémoire refoule toujours vers le bas!
					if(canaux[countcan].posy > canaux[canpos].posy) canaux[countcan].posy++; else if(canaux[countcan].posy == canaux[canpos].posy) canaux[countcan].posy+=2;
				}       // == : Si deux canaux se situe sur la même ligne, le canal qui change de ligne va couper l'autre en deux, et le renvoyer après sa propre ligne.    	        
				//Updater les positions dans le canal actuel
				if(canaux[canpos].txt[0]=='\n') {canaux[canpos].posx = -1;} else canaux[canpos].posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
				canaux[canpos].posy++;	  																					   //en y 		
			} else {canaux[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caractère       //À partir d'ici, les posx et posy sont la position du charactère actuel (dans la mémoire)!		
		if(canaux[canpos].txt[0]!='\n') {
			curspos(canaux[canpos].posx,canaux[canpos].posy-base.consy) ; out(canaux[canpos].txt[0]);     //Inscrire dans la console
			mem.souvenir[canaux[canpos].posx][canaux[canpos].posy] = canaux[canpos].txt[0];   //Inscrire dans la mémoire			
		}	
		canaux[canpos].txt = strintervalle(canaux[canpos].txt,1,canaux[canpos].txt.length());       //Effacer le caractère du canal     	   
	}
	if(canaux[canpos].txt.length()==0) canaux[canpos].actif = false;			//Vérifier s'il reste toujours du texte à passer dans le canal
}	
					
          
         
//------------------------------------------------------------------------------------------------------------------------------------------------------
//7) Fonction : UserInputInterpret ; vérifie si la commande entrée correspond à une des actions actuellement autorisée
	template<int Taille>
	void UserInputInterpret(StaticVect<char,Taille>& command, StaticVect<canal,taillecanal>& canaux, bibliotheque& biblio, fil& histoire, const fen& base, input& inp, memoire& mem) {
		//

			//IDÉE:
			//		PEUT-ÊTRE INCLURE DIRECTEMENT DANS L'ÉVALUATION LA MISE EN MAJUSCULE AUTOMATIQUE DU PREMIER MOT?
			//		
			
					//CE N'EST PAS ENCORE FAIT!!! IL SERAIT IMPORTANT DE L'INTÉGRER!!!
			
			
			
		//Créer des compteurs
		StaticVect<int,20> bonchapitre;	  //Créer des StaticVect pour noter la position des chainons qui correspondent à la commande
		StaticVect<int,20> bonchainon;											//Taille arbitraire de 20; j'espère qu'aucune commande n'appelera simultannément 20 maillons
		StaticVect<bool,taillegroupes> groupebon; 	   	 //Créer un StaticVect pour noter si chaque groupe de mot est bon
		int diffpos; bool exactbon; int commpos; bool exactmauvais; 	//Créer les compteurs pour les expressions exactes
		int groupepos; int synpos; int motpos; int precedpos; bool inclusbon; bool exclusbon;	//Créer les compteurs pour les mots à inclure/exclure	

		//Pour chaque chapitre
		for(int chapitrepos=0; chapitrepos<histoire.chainemanu.longueur; chapitrepos++) { if(histoire.cadenas[chapitrepos].eval(biblio)) {			
			//Pour chaque chainon dans l'histoire
			for(int chainonpos=0; chainonpos<histoire.chainemanu[chapitrepos].longueur; chainonpos++) {if(histoire.chainemanu[chapitrepos][chainonpos].condition.eval(biblio)) {
				
				
				//DEBUGGG
				curspos(1,chainonpos+13); out("Le chainon \""); out(histoire.chainemanu[chapitrepos][chainonpos].commandes.exact[0]); out("\" a sa condition remplie.");
				
				
				
				
				if(histoire.chainemanu[chapitrepos][chainonpos].commandes.ifexact) {	//Si une commande exacte est nécessaire
					diffpos = 0; exactbon = false;
					while(diffpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.exact.longueur&&!exactbon) {
						commpos = 0; exactmauvais = false;
						while(!exactmauvais&&commpos<command.longueur) {if(command[commpos]!=histoire.chainemanu[chapitrepos][chainonpos].commandes.exact[diffpos][commpos]) exactmauvais = true; else commpos++;}	
						if(exactmauvais==false) exactbon = true; else diffpos++;
					}
					if(exactbon)	{integrationmanu(chapitrepos,chainonpos,canaux,histoire,biblio); return;}            //Intégrer tout de suite le bon chaînon dans le canal					
				} else {								//Si plusieurs mots clés doivent être présents
					inclusbon = false; diffpos = 0;
					//Pour chaque façon différente de dire la commande
					while(diffpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus.longueur&&!(inclusbon&&exclusbon)) {
						//Vérifier si les mots à être inclus sont présents
							groupepos = 0;  precedpos = 0;   														//Remettre tous les groupes de mots comme incorrects jusqu'à preuve du contraire
							groupebon.remplacement(false); for(int clearpos=1; clearpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos].longueur; clearpos++) groupebon.ajout(false); 
							//Pour chaque groupe de mots
							while(groupepos<histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos].longueur) {    
								synpos=0;
								//Pour chaque synonyme
								while(synpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos][groupepos].longueur&&!groupebon[groupepos]) {		
									commpos = precedpos;
									motpos = 0;
									//Pour chaque lettre
									while(commpos<command.longueur&&!groupebon[groupepos]) {						//DONC, ICI, L'ORDRE EST IMPORTANT DANS LA COMMANDE. PARCE QU'ON PART DE LA POSITION PRÉCÉDENTE. CHANGER ÇA? GARDER ÇA?															
										if(command[commpos++]==histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos][groupepos][synpos][motpos++]) {
											if(motpos==histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos][groupepos][synpos].length()) {groupebon[groupepos] = true; precedpos = commpos;}
										} else motpos = 0;
									}
									synpos++;
								}
								groupepos++;					
							}	
							//Maintenant, on a l'information sur quel groupe de mots, dans l'intervalle [0,longueur_de_cette_differente_façon], a un membre qui est présent dans la commande.
							groupepos=0 ; while(groupebon[groupepos++]) if(groupepos==histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos].longueur) inclusbon = true;
						if(inclusbon) {
						//Vérifier si les mots à être exclus sont absents
							synpos=0; exclusbon = true;
							//Pour chaque synonyme
							while(synpos<histoire.chainemanu[chapitrepos][chainonpos].commandes.exclus[diffpos].longueur&&exclusbon) {
								commpos = 0;
								motpos = 0;
								//Pour chaque lettre
								while(commpos<command.longueur&&exclusbon) {		//Si le mot est retrouvé, la commande ne correspond pas au chaînon																			
									if(command[commpos++]==histoire.chainemanu[chapitrepos][chainonpos].commandes.exclus[diffpos][synpos][motpos++]) {
										if(motpos==histoire.chainemanu[chapitrepos][chainonpos].commandes.inclus[diffpos][synpos].longueur) exclusbon = false; inclusbon = false;	
									} else motpos = 0;
								}
								synpos++;
							}
						}
						diffpos++;
					}
					if(inclusbon&&exclusbon) {bonchapitre.ajout(chapitrepos); bonchainon.ajout(chainonpos);}
				}		
			}}
		}}
		//Maintenant, on a l'information sur quels chaînons correspondent (sans expression exacte) à la commande
		if(bonchainon.longueur==0) {
			inp.accepted = false; 			
			return;
		} else if(bonchainon.longueur==1) {	
			inp.accepted = true; if(histoire.chainemanu[bonchapitre[0]][bonchainon[0]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input					
			integrationmanu(bonchapitre[0],bonchainon[0],canaux,histoire,biblio); return;            //Intégrer le bon chaînon dans le canal
		} else {
			//Déterminer si la commande correspond à une expression exacte
			int bonpos = 0; exactbon = false; 
			while(bonpos<bonchainon.longueur&&!exactbon) {
				exactmauvais = false; commpos = 0;
					while(!exactmauvais&&commpos<command.longueur) {if(command[commpos]!=histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0][commpos]) exactmauvais = true; else commpos++;}	
					if(exactmauvais==false) {
						exactbon = true; 	
						inp.accepted = true; if(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].getbusy) inp.busy = true;							
						integrationmanu(bonchapitre[bonpos],bonchainon[bonpos],canaux,histoire,biblio); return;}            //Intégrer tout de suite le bon chaînon dans le canal	
			}	
			//Si l'ambiguité demeure: mettre le jeu sur pause, et faire apparaître les options	
			pause(canaux);
			chgcol("gris sombre"); curspos(0,0);		//Recopier tout le texte affiché dans la console, mais en gris foncé (background)
			for(int county = base.consy ; county <= mem.frontline ; county++) {   
				for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
			}			
			chgcol("blanc"); curspos(5,3); int cursorposy = 3;
			egrener("Vouliez-vous dire (recopiez la ligne qui correspond à votre choix) :",160);
			for(int bonpos=0; bonpos<bonchainon.longueur; bonpos++) {
				if(bonpos==bonchainon.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy); egrener("ou",120);}}
				cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy);; egrener(histoire.chainemanu[bonchapitre[bonpos]][bonchainon[bonpos]].commandes.exact[0],120);}
				if(bonpos==bonchainon.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy); egrener("              ?",120);}}				
			}
			string reformulation;
			cin >> reformulation;
				//Vérifier de nouveau
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
							integrationmanu(bonchapitre[bonpos],bonchainon[bonpos],canaux,histoire,biblio); return;}            //Intégrer tout de suite le bon chaînon dans le canal	
				}				
			//Si l'ambiguité persiste: le demander une dernière fois
			curspos(3,0); chgcol("gris sombre"); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][base.consy + 3]); chgcol("blanc");
			curspos(3,3); egrener("Vouliez-vous dire (recopiez EXACTEMENT la ligne qui correspond à votre choix) :",200);
			cin >> reformulation;	
				//Vérifier de nouveau
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
							integrationmanu(bonchapitre[bonpos],bonchainon[bonpos],canaux,histoire,biblio); return;}            //Intégrer tout de suite le bon chaînon dans le canal	
				}				
			//Si l'ambiguité est insolvable
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
//8) Fonction UserInput()
void UserInput(input& inp, inputecho& inpecho, const fen& base, bibliotheque& biblio, StaticVect<canal,taillecanal>& canaux, fil& histoire, memoire& mem) {
	if(_kbhit()){
	//i) Capter la lettre tapée
	bool enter = false;
	char charkey; int intkey = _getch();                  		//Enregistrer quelle touche a été pressée
			if (intkey == 0 || intkey == -32 || intkey == 224) {      //La valeur est spéciale: elle nécessite de la ré-examiner
				intkey = _getch();                              //Examiner une deuxième valeur pour identifier
				if(intkey == 75) {     								 				 //flèche gauche : reculer dans la commande tapée 
					if(inp.inputpos!=0) {
						if(inp.inputpos!=inp.commande.longueur) {
							curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						}          //Remettre en gris la position précédente
						inp.inputpos--;  
					}
				}
				else if (intkey == 77) {											 	 //flèche droite : avancer dans la commande tapée				
					if(inp.inputpos!=inp.commande.longueur) {
						curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						inp.inputpos++;		
					}			//Remettre en gris la position précédente
				} 
				else if (intkey == 72)  ;  											 //Flèche du haut   ... Rien ne se passe?g
				else if (intkey == 80)  ;  											 //Flèche du bas    ... Rien ne se passe?
				else if (intkey == 83) {                                                //Delete : supprimer un caractère de la commande actuelle
					if(inp.inputpos!=inp.commande.longueur) {
						inp.commande.supprposition(inp.inputpos);    
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);    
						out(' ');
					}
				}
			} else 	{                                        //La valeur est "normale"
				//Touches-fonctions
				if(intkey == 27) {														 //Escape : terminer le programme
					curspos(0,base.limtxty); out("Vous avez entré ESC, le programme se ferme donc."); abort(); 
				} else if(intkey == 13) {												 //Enter : envoyer la commande
					enter = true;
				} else if(intkey == 8) {                                                //Backspace : supprimer le caractère précédent
					if(inp.inputpos!=0) {
						inp.inputpos--;
						inp.commande.supprposition(inp.inputpos);   
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);   
						out(' ');    					
					}
				
				
				
				
				//DEBUGGG	
				} else if(intkey==20) {														//Ctrl + T : Donne le status des conditions de chaque chainon
					curspos(2,10); out("Voici les conditions des chaînons:");
					for(int poschai=0; poschai<histoire.chainemanu[0].longueur; poschai++) {
						curspos(2,11+poschai); out("     Chaînon "); out(poschai); out("  :     ");
						histoire.chainemanu[0][poschai].condition.test(biblio);
					}
					//abort();
					
				
				
					
				} else {							//Caractère non ASCII
					if(intkey==183) charkey = 'À'; else if(intkey==133) charkey = 'à'; else if(intkey==128) charkey = 'Ç'; else if(intkey==135) {charkey = 'ç';
					} else if(intkey==144) charkey = 'É'; else if(intkey==130) charkey = 'é'; else if(intkey==212) charkey = 'È'; else if(intkey==138) {charkey = 'è';
					} else if(intkey==210) charkey = 'Ê'; else if(intkey==136) charkey = 'ê'; else if(intkey==215) charkey = 'Î'; else if(intkey==140) {charkey = 'î';
					} else if(intkey==216) charkey = 'Ï'; else if(intkey==139) charkey = 'ï'; else if(intkey==226) charkey = 'Ô'; else if(intkey==147) {charkey = 'ô';
					} else if(intkey==235) charkey = 'Ù'; else if(intkey==151) charkey = 'ù'; else if(intkey==234) charkey = 'Û'; else if(intkey==150) {charkey = 'û';
					} else charkey = intkey;		//Caractère ASCII		 
				//Caractère normal : l'ajouter à la commande	
					if(inp.commande.longueur<base.limtxtx-1){
						inp.commande.ajout(charkey,inp.inputpos);
						inp.inputpos++;
						curspos(inp.inputpos-1,base.limtxty);	                    
						for(int pos=inp.inputpos-1; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);
						if(inp.commande.longueur==inpecho.commande.fin) inpecho.actif = false;                   //Désactiver le canal d'écho si la commande actuelle le dépasse
					}
						
								//BTW: FAUDRAIT AUSSI TOUT UN PAN DE CODE POUR GÉRER LES COMMANDES TROP LONGUES, POUR FAIRE RECULER LE TEXTE
										//Pour l'instant, je restreint l'espace à la largeur de la console, simplement.
							
				}
			}	
		//Remettre la lettre sélectionnée en surbrillance
		if(inp.inputpos!=inp.commande.longueur) {chgcol("blanc"); curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); chgcol(base.couleur);}
			
		//Évaluer la commande		
		if(enter) {								//BTW: Faire changer la vitesse/frénésie du clignotage avec la vitesse globale. Tu veux ça plus vite? Ça va être plus agressant aussi!
			UserInputInterpret(inp.commande,canaux,biblio,histoire,base,inp,mem);
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
			inp.inputpos = 0; inp.commande.vide();                               //Nettoyer l'objet input			
		}	
	}
}     

//------------------------------------------------------------------------------------------------------------------------------------------------------
//9) Fonction jouer();
void jouer(univers& monde, fen& base, memoire& mem){
	int currentt;
	srand(timems());										// "setseed" de la fonction rand, pour ne pas avoir la "seed" par défaut, qui est toujours la même
	while(true){				//À faire tout le temps:
		currentt = timems();		
		for(int canpos=0; canpos<=monde.canaux.longueur; canpos++) {if(monde.canaux[canpos].actif&&monde.canaux[canpos].nxtt<currentt) LireCanal(monde.canaux,canpos,base,mem,monde.biblio);}  //Lire chaque canal, s'il est prêt	
		if(monde.inpecho.nxtt<currentt) UserInputEcho(monde.inp,monde.inpecho,base);
		UserInput(monde.inp,monde.inpecho,base,monde.biblio,monde.canaux,monde.histoire,mem);	//Interpréter la touche jouée		
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//10) Aire de tests
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
	//x, y, width, height,
	fen base(600,30,500,500);                                           //Crée également l'objet dans lequel ces paramètres sont définis       
	memoire mem(base.limtxtx);

	//Créer l'objet où tout est initié
	univers monde;
		
		//Créer une bibliothèque
		nvrayon(monde,"Laure");
			nvlivre(monde,"actif");
			nvlivre(monde,"debut");
			nvlivre(monde,"confo");
			nvlivre(monde,"divertir");
				
		//Créer un canal
		nvcanal(monde,"narration");
		
		//Débuter un chapitre
		nvchapt(monde);
			ccond(monde,"1");        //Rendre le premier chapitre accessible tout le temps
	
			//Créer un maillon
			mtitre(monde,"Commencer le jeu");		
			mtexte(monde,"Bienvenue dans mon ordinateur.\nµÇa fait plaisir de vous recevoir, vraiment.\nµJ'espère que vous êtes bien installé.es.\nµÊtes-vous bien installé.es?µÊtes-vous confortable?");				
			mordre(monde,"1-4;1-5;2-4;2-5;3-4;4-5");
			mprob(monde,"1;1;1;1;1;1");
			mcomm(monde,"(Start|start|Débuter|débuter|Commencer|commencer)");
			mcond(monde,"!Laure¶debut");	
			mdeb(monde,"§bLaure¶actif=1§§bLaure¶debut=1§");
			mfin(monde,"§bLaure¶actif=0§");
			mover(monde,0);	

			//Créer un maillon
			mtitre(monde,"Je suis confortable");
			mtexte(monde,"Bien.§p6000§ µParfait.§p6000§ µ\n\n                   Désirez-vous vous divertir§p1000§...?");
			mordre(monde,"1-3;1-2");
			mprob(monde,"1;1");
			mcomm(monde,"(Je|J' & suis|reste & confortable|bien installé [ne suis pas|jamais]) (Ça va|Correct) (Oui)");		//BTW, ici, installé inclut aussi installée et installé.e (pas besoin de répéter)
			mcond(monde,"Laure¶debut&!Laure¶confo");
			mdeb(monde,"§bLaure¶actif=1§§bLaure¶confo=1§§v0.8§");
			mfin(monde,"§bLaure¶actif=0§");
			
			//Créer un maillon
			mtitre(monde,"Je veux me divertir");
			mtexte(monde,"\n\n\n\nZut§p2000§;§p2000§ \n\n\n            J'ai bien peur que vous ne soyez pas à la bonne place.µ§v0.3§\n\n         §p4000§Too fucking bad.");		
			mordre(monde,"1;2");
			mprob(monde,"1;1");
			mcomm(monde,"(Oui|oui|évidemment|certainement|volontier|pourquoi pas|why not|d'accord) (veux|voudrais & cela|ça|bien)");
			mcond(monde,"Laure¶confo&!Laure¶divertir");
			mdeb(monde,"§bLaure¶actif=1§§bLaure¶divertir=1§§p1100§");
			mfin(monde,"§bLaure¶actif=0§");	
			
		
	//Faire une boucle pour que les canaux s'expriment!
	jouer(monde,base,mem);		
		
	curspos(0,13);			//Mettre le curseur dans un bel endroit à la fin


}							


	//DEBUG:::
	
				//Je crois que ce qui ne marche pas, c'est que la longueur des chapitres (le nombre de chaînons inclus) n'est jamais updatée;
						//de même que la longueur de tous les StaticVect intermédiaires, au fond, je crois.
							//Il faudrait... l'updater manuellement dans les fonctions où on ajoute le contenu?
									//Ou bien mettre un compteur...? Genre créer des objets à part pour contenir les nombres de chaque choses?
											//Nan...
	
	
	
	
