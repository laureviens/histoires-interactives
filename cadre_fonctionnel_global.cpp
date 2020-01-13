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
	2019-07-05:
				Dans les fonctions integration() et UserInputInterpret(),
				j'utilise beaucoup d'indexation. �a devient difficile � lire.
				Je pense que �a n'alourdirait pas trop l'ex�cution de cr�er un objet temporaire pour chaque motif (rendrait le tout plus clair).
				J'ai par contre peur que �a fuck avec les pointeurs, que les objets soient modifi�s (sont tous par & r�f�rence), etc.
					Je conserve donc cette id�e quand j'aurai minimalement une version test�e, qui fonctionne.
*/

/*
	2019-07-13:
				Ce qu'il me reste � faire:
					-Tester, avec des vraies mailles (manuelles), si le UserInputInterpret agit comme il le devrait.
								-Tout marche comme il le faudrait.				
					-Cr�er un �quivalent de la fonction pour les mailles automatiques
									-L�, on a tout de m�me plusieurs choix:
									
										-Soit on �value les conditions simplement TOUT LE TEMPS
										-Soit on �value les conditions � un intervalle de temps fixe, disons 10 ou 100 millisecondes
										-Soit on se fie UNIQUEMENT aux valeurs de la biblioth�que pour enclencher les motifs auto, donc on �value � chaque fois que la biblio est modifi�e.
												-Bien entendu, ce dernier est pr�f�r�, car plus parsimonious (moins de charge pour l'ordinateur).
												
						-Bon, j'ai techniquement termin� de coder cette partie... Reste � tester.
					
							-Bon.
									La maille automatique appara�t � l'�cran, ce qui est bien.
									
									Sauf qu'� la fin, �a lance un message en mot "�grenage", comme si c'�tait dans le canal,
									"eur n'est pas complet dans : "  
												Pis �a c'est weird, parce que la seule place o� j'ai quelque chose de marqu� qui ressemble � �a,
													c'est dans genre interoper, o� c'est "out()", la fonction, et non "ajouter � un canal()".
													
										En fait, j'ai check�, et c'est vraiment dans le canal.
											Donc probablement que la derni�re ligne o� j'suis sens�e ajouter le code sp�cial "�m...;...� ne marche pas,
													et met � la place ce message vraiment bizarre?
														� revoir plus tard...
																//BTW, c'est � la fonction Integrationauto() (ou quelque chose comme �a) que �a se trouve, ces lignes
								-Bon, j'ai chang� la mani�re d'int�grer le code sp�cial sp�cial � la fin, et l� �a marche. Mon �criture originelle �tait un peu random, crammant ensemble strings, char et integer.									
					
					
					-Int�grer dans l'interpr�tation de l'input la premi�re (ou toutes?) majuscule optionnelle
								-Fait, pour la premi�re lettre seulement.
					-Peut-�tre changer la m�moire de "long terme, finie" � "court terme, infinie" en sauvant moins de lignes mais en �crivant par-dessus?
					-Je ne sais pas si j'ai fait tous les "checks" de (d�s)activation des canaux... � la fois quand le canal s'�puise, et quand il est overrid�!
								-J'ai ajout� la d�sactivation dans la fonction d'overridecanal(), et la fonction lirecanal() a d�j� un check de �a � sa toute fin. C'est beau!
								-Int�gration, techniquement la seule chose qui peut ajouter du texte � un canal (?), a aussi un check qui active � la fin. C'est donc beau.
					-Ajouter un menu
					-D�finir des premiers rayons de la biblioth�que comme {"Menu","Accords", etc...}
					-Pr�sentement, les commandes tap�es �valuent les mots des motifs DANS L'ORDRE. D�cider si je garde �a, ou si j'accepte le d�sordre.
								-J'pense �a enl�ve quelques ambiguit�s possibles si je garde �a dans l'ordre.. Genre mettre le biscuit sur la table VS mettre la table sur le biscuit.
					-Urgh. J'pense que j'ai foir� avec "prendre les titres comme des commandes exactes". 
							-Parce que y'a pas d'�quivalent pour les motifs automatiques, j'ai fini par cr�er un membre "titre" aux motifs auto... 
								-Et me semble que �a serait simplement plus logique si les motifs manu disposaient eux aussi d'un titre?
									-Fait que j'veux redonner (�ventuellement) le r�le unique de titre aux titres (qui serviront quand m�me si plusieurs motifs sont appel�s par une seule commande),
										et laisserai leur job aux commandes exactes.	
									-Eh, euhm, j'ai kinda r�gl� cette question? 
										-Mais le bout o� y'a des commmandes ambig�es est louche, 
											m�me si on ne mentionne pas le fait que j'utilise "pause()" l�-dedans... Yrkh.
												J'vais retravailler tout ce bout quand j'vais faire les menus, ok?
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
*/

/*
	2019-09-19:
				Oh; il serait pertinent de changer la fonction pour changer de couleur, et de mettre au lieu des r�f�rences
				� la biblioth�que; genre avoir une fonction "changer couleur �" qui prend un string ou un num�ro en argument;
				genre "clignotement" ou quelque chose du genre...? Genre mettre cat�gories comme "clair", "obscur", "normal"...?
							//Si je le mets dans la biblioth�que, faudra que ce soit en 'int': Donc s�parer le back-ground et le texte?
								//Et apr�s, � chaque fois que je change de couleur, de faire la conversion?
									//Et peut-�tre mettre des syst�mes de v�rifications � chaque fois que je dois changer la couleur;
										: Est-ce que c'�tait d�j� sett� sur 'clair'?		
*/

/*
	2019-09-22:
				Id�e: il serait peut-�tre bien, pour les rayons "rigides" de la biblioth�que, comme les marqueurs de genre, les r�f�rences de couleur et les *...*,
				de:
					a) Soit les int�grer de mani�re immuable � la classe, dans le constructeur de l'objet, et peut-�tre m�me mettre un membre de cette classe sp�cifiant leur position;
					b) Soit les lier � des objets additionnels, stock�s dans "monde", qui conservent la position *actuelle* du rayon.
							//Juste � l'�crire comme �a, j'ai beaucoup mieux a).
*/



//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entr�es/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contr�le du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //N�cessaire pour la taille de la fen�tre: informe qu'on est sur Windows 2000 ou plus r�cent (??? Optionnel?)
#include <windows.h>           //N�cessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>            //N�cessaire pour savoir la position du curseur sur Windows
#include <winuser.h>		   //N�cessaire pour savoir la position du curseur sur Windows
#include <conio.h>             //N�cessaire pour enregistrer les inputs du clavier
#include <io.h>				   //N�cessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>			   //N�cessaire pour d�crypter les accents en unicode
#include <stdlib.h>     	   //N�cessaire pour jouer avec des nombres al�atoires  /* srand, rand */

/*
	2019-07-05:
A typical way to generate trivial pseudo-random numbers in a determined range using rand is to use the modulo of the returned value 
		by the range span and add the initial value of the range:

v1 = rand() % 100;         // v1 in the range 0 to 99
v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 
*/


using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Classes-contenantes g�n�rales

	//i) classe : StaticVect ; sauvegarde un array "semi-dynamique", o� la m�moire utilis�e est fixe, mais les fonctionnalit�s sont les m�mes que StringAsVect.
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
		
	//iv) Fonction: curson ; affiche ou cache le curseur                        		                                   //WINDOWS ONLY
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
	template<int Taille>
	void out(StaticVect<char,Taille> phrase){
		for(int pos=0; pos<phrase.longueur; pos++){
			out(phrase[pos]);
		}
	}
	//void out(int chiffre) {std::wcout << to_string(chiffre);}      //Nope. �a marche pas, car la conversion en wchar ne se fait pas bien...
	//void out(double chiffre) {std::wcout << to_string(chiffre);}


	//vi) Fonction : chgcol ; change la couleur du texte � entrer
	void chgcol(string color) {
		WORD code;                                            //Voir Internet pour la l�gende
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
		//Failsafe: Si aucune it�ration de "str" n'a �t� trouv�e
		curspos(4,4); out("Aucune it�ration de \""); out(str); out("\" n'a �t� trouv�e dans {");
		for(int poscol = 0; poscol<col.longueur; poscol++) {out("\""); out(col[poscol]); out("\""); out(" ; ");} out("}"); abort();
	}
	
	//ix Fonction : stop ; arr�te manuellement l'ex�cution d'un programme. � utiliser seulement dans un menu!
	void stop(int val) {
		int targett = timems() + val;
		while(TRUE) {if(timems()>targett) return;}
	}

	//x Fonction : egrener ; fait appara�tre le texte manuellement, comme s'il �tait dans un canal. � utiliser seulement dans un menu!
	void egrener(string str, int delay) {
		for(int pos=0; pos<str.length(); pos++) {out(str[pos]); stop(delay);}
	}
	
	//xi Fonction : strintervalle ; retourne un string
	string strintervalle(string str, int deb, int fin) {
		string nwstr;
		for(int pos=deb;pos<=fin;pos++) nwstr+=str[pos];          
		return(nwstr);
	}
	
	//xii Fonction : majuscule ; retourne le char, mais en majuscule
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

	//xiii Fonction : randomnb ; retourne un integer entre un min et un max (les valeurs sont comprises; "inclusivement")
	int randomnb(int min, int max) {
		return(rand() % (max+1) + min);
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//3) Classes-contenantes sp�cialis�es (canaux et autres)

	const int taillecanal = 2;
	const int taillegroupes = 5;
									//2019-08-18: Ouin, �a se peut que cette m�thode soit permanente, puisque je n'arrive pas � bien inclure ces nombres
												// � l'int�rieur des classes. 

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
			}			
			//Destructeur
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
			string txt;   		//D�clarer le texte qui reste � lire  				
			bool actif;			//D�clarer le compteur d'activit�
			double vit;         //D�clarer la vitesse actuelle de d�filement et de pauses (toujours par rapport � la base, 1)
			string nom;			//D�clarer le nom que porte le canal
		//Constructeur
		canal() : delay(150), posx(-1), posy(0), actif(false), vit(1) {nxtt = timems();}  //Cr�er un constructeur par d�faut, pour initialiser tous les param�tres
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
			string couleur;           //Couleur de base du texte													//PT LE BOUGER DANS BIBLIO, OU JUSTE BONIFIER L'INFO ICI?
																															////////////////////////////////////////////////////////////////////
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
			bool accepted;                  //Flag concernant la derni�re commande; utile pour l'affichage visuel
			bool busy;						//Flag concernant la derni�re commande; utile pour l'affichage visuel
		//Constructeur par d�faut
			input() : inputpos(0), accepted(false), busy(false) {}
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
		void modif(string rayonstr, string livrestr, int value) {
			int posrayon = ColNameFind(rayonstr,nomrayon); 
			int poslivre = ColNameFind(livrestr,nomlivre[posrayon]);
			rayon[posrayon][poslivre] = value;
		}
	};

	//vii) classe : inteval ; contient l'expression � �valuer (la plus simple) ; constructeur transforme les noms de "livre" en position d'indexation
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

	//viii) classe : intoper ; contient les op�rations d'expressions bool�ennes �valuables
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
			//Cas g�n�ral : on cherche '+' ou '-', car '*' et '/' ont la priorit� d'op�ration
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


	//ix) classe : boolcompar ; contient les comparaisons d'expressions bool�ennes �valuables
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
					curspos(2,20); out("Le string \""); out(str); out("\" a �t� pass� � la fonction boolcompar(), le compositeur '!' n'ayant pas �t� d�tect� par la fonction boolcompos. Cette partie du code n'est donc pas bonne.''"); abort();			
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


	//x) classe : boolcompos ; permet de stoker des expressions bool�ennes �valuables; (LH = "left hand", � gauche ; RH = "Right hand", � droite)
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
				} if(!trouvPAR) {out("\n\nLa parenth�se n'est pas referm�e dans: "); out(str); abort();}
				if(trouvPAR&&pos==strnb) {str = strintervalle(str,1,strnb-2); trouvPAR = false; pos = 0;   //L'expression enti�re est entre parenth�se : Supprimer celles-ci et remettre les compteurs � 0, pour continuer au cas g�n�ral
				} else Lcompos = true;		//Noter l'expression � droite comme composite (car elle contient au minimum une parenth�se), et continuer au cas g�n�ral � partir d'apr�s la parenth�se
			} else if(str[0]=='!'&&str[1]=='(') {  
			//Cas sp�cial: l'expression commence par "le contraire" d'une parenth�se (ex: "!( 6<2 | 4==4 )"  ou  "!( 6>3 | 5<6) & 1==3" )			
				while(!trouvPAR&&pos<strnb) {
					if(str[pos]=='(') nbPAR++;	//G�re les parenth�ses imbriqu�es 
					if(str[pos]==')') {if(nbPAR==0) {posPAR = pos; trouvPAR = true;} else nbPAR--;}
					pos++;
				} if(!trouvPAR) {out("\n\nLa parenth�se n'est pas referm�e dans: "); out(str); abort();}
				if(trouvPAR&&pos==strnb) {compositeur = '!'; LH = strintervalle(str,2,strnb-2); Lcompos = true; general = false;   //L'expression enti�re est "contraire" : passer le cas g�n�ral		
				} else Lcompos = true;		//Noter l'expression � droite comme composite (car elle contient un "contraire"), et continuer au cas g�n�ral � partir d'apr�s la parenth�se	
			}
			if(general) {
			//Cas g�n�ral : on cherche '|', car '!' et '&' ont la priorit� d'op�ration
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
					if(trouvEX|trouvET) Lcompos = true; //(car '!' et '&' ont la priorit� d'op�ration sur '|')
					while(!Rcompos&&pos<strnb) {if(str[pos]=='|'||str[pos]=='&'||(str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=')) Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite
				} else if(trouvET) {  
					compositeur = '&';
					LH = strintervalle(str,0,posET-1);					//D�finir les limites de l'expression � gauche		
					RH = strintervalle(str,posET+1,strnb-1);		//D�finir les limites de l'expression � droite
					pos = posET + 1; while(!Rcompos&&pos<strnb) {if(str[pos]=='&'||(str[pos]=='!'&&pos+1<strnb&&str[pos+1]!='=')) Rcompos = true; pos++;}	//Trouver si l'expression � droite est composite				
				} else if(trouvEX&&posEX==0) {
					compositeur = '!';
					LH = strintervalle(str,1,strnb-1);					//D�finir les limites de l'expression � gauche	
																//Il n'y a pas d'expression � droite
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


//xi) classe : commande ; permet le stockage de "mots de passe" pour les commandes, � chercher dans le USERINPT
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
			StaticVect<StaticVect<string,taillegroupes>,tailledifferentes> exclus;						//Mots qui doivent �tre absents de l'expression
					//Niveau le plus ext�rieur: Diff�rentes fa�on de dire la commande
					//Niveau le plus int�rieur: Diff�rents mots qui ne doivent pas se retrouver dans la commande
			StaticVect<string,taillegroupes> exact;										//Expressions qui doivent exactement �tre recopi�es, sans faute (soit seule mani�re d'appeler, soit confirmation si ambiguit�; voir UserInputInterpret())
			bool ifexact;													//TRUE si une expression exacte est n�cessairement recherch�e
		//Constructeur
		commande() : ifexact(false) {};	
	};		
	
	
	//xii) classe : motifauto ; permet le stockage du texte et des conditions d'apparition (automatique)
	class motifauto {
		//Membres
		public:
			StaticVect<string,10> maille;						//Texte � lire
			StaticVect<StaticVect<int,10>,10> enchainement;  	//int r�f�re aux positions des mailles         
			StaticVect<intoper,10> enchaineprob;        	 	//Avec le m�me ordre d'indexation que encha�nement
			boolcompos condition;								//Conditions � respecter pour l'ajout au canal sans UserInput 
			string codespeciauxdebut;
			string codespeciauxfin;
			bool override;										//TRUE si l'activation de motif vide instantann�ment le canal utilis�
			bool encours;										//Va changer dynamiquement, permet de ne pas d�doubler le m�me motif (� un temps d'attente obligatoire)
			int canal;											//Position du canal dans lequel �crire le texte
			string titre;										//Ne sert qu'� identifier le motif; n'appara�t jamais � l'�cran
		//Constructeur
		motifauto() : override(false), encours(false) {};
	};
	
	//xii) classe : motifmanu ; permet le stockage du texte et des conditions d'apparition (manuelle)
	class motifmanu {
		//Membres
		public:
			StaticVect<string,10> maille;						//Texte � lire
			StaticVect<StaticVect<int,10>,10> enchainement;  	//int r�f�re aux positions des mailles         
			StaticVect<intoper,10> enchaineprob;        	 	//Avec le m�me ordre d'indexation que encha�nement
			boolcompos condition;								//Conditions � respecter pour l'ajout au canal avec UserInput				
			string codespeciauxdebut;
			string codespeciauxfin;
			bool override;										//TRUE si l'activation de motif vide instantann�ment le canal utilis�
			int canal;											//Position du canal dans lequel �crire le texte
			commande commandes;                					//Mots � rechercher pour l'ajout au canal � partir du UserInput			
			bool getbusy;                                       //TRUE si le UserInput devient bloqu� apr�s que ce motif ait �t� appel�
			string titre;										//Sert � identifier le motif + � savoir quel motif est appel� en cas d'ambiguit� de la commande
		//Constructeur
		motifmanu() : getbusy(true), override(false) {};	
	};
	
	//xiii) classe : ouvrage ; permet de stocker toutes les textes + commandes selon des cat�gories (ex: chapitres), pour faciliter la recherche
	class ouvrage {
		//Membres
		public:
			static const int taille = 1;												//Nombre de "chapitre" actuellement disponibles
			static const int taillechapitre = 40;
			StaticVect<StaticVect<motifmanu,taillechapitre>,taille> filmanu;		//Groupes de textes + commandes ("chapitres") pour activation manuelle
			StaticVect<StaticVect<motifauto,taillechapitre>,taille> filauto;		//Groupes de textes + commandes ("chapitres") pour activation automatique
			StaticVect<boolcompar,taille> cadenas;										//Conditions d'activation des "chapitres"
	};

//------------------------------------------------------------------------------------------------------------------------------------------------------
//4) Fonction sp�cialis�es de petite taille

	//i) Fonction : CodeSpecialLong ; retourne la longueur d'un code sp�cial ('�' compris)
	int CodeSpecialLongueur(string str){
		int longueur = 1;               //Initier l'objet � retourner
		bool fini = false; int pos = 1;
		while(!fini&&pos<str.length()) {
			longueur++; pos++;
			if(str[pos]=='�') fini = true;
		}              
		return(longueur);		
	}

	//ii) Fonction : CodeSpecialExtract ; extrait une valeur num�rique d'une suite de caract�res encadr�s par '�' (pour extraire les codes sp�ciaux)
	double CodeSpecialExtractDouble(string str, int longueur){
		string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres (2X'�' + 1 identifiant en char)
		int longmax = longueur - 1;      //Le dernier caract�re �tant le '�'		
		for(int pos=2; pos<longmax; pos++) nbonly += str[pos];    //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire (identifiant en char)	
		return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}		
	//ii) Fonction : CodeSpecialExtract ; extrait une valeur num�rique d'une suite de caract�res encadr�s par '�' (pour extraire les codes sp�ciaux)
	int CodeSpecialExtractInt(string str, int longueur){
		string nbonly;                  //Initier un string, dans lequel ins�rer seulement les chiffres (2X'�' + 1 identifiant en char)
		int longmax = longueur - 1;      //Le dernier caract�re �tant le '�'		
		for(int pos=2; pos<longmax; pos++) nbonly += str[pos];    //Commencer � la position [2], le [0] �tant occup� par '�' et le [1] par le type de valeur � extraire (identifiant en char)	
		return(stoi(nbonly));           //La fonction stoi convertit les strings en int (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}			

	//iii) Fonction : UserInputEcho ; validant graphiquement l'acceptation ou le refus des commandes envoy�es
	void UserInputEcho(input& inp, inputecho& inpecho, const fen& base) {	
		chgcol(inpecho.couleur);
		//Clignoter
		if(inpecho.clignote[0]>0){
			curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(inpecho.commande[pos]);
		} else {
			curspos(inp.commande.longueur,base.limtxty); for(int pos=inp.commande.longueur; pos < inpecho.commande.fin; pos++) out(' ');		
		}
		chgcol(base.couleur);                       //Revenir � la couleur de base	
		inpecho.nxtt += abs(inpecho.clignote[0]);        //Updater le "next time"
		inpecho.clignote.suppression(1);            //Passer � la prochaine instruction
		if(inpecho.clignote.longueur==0) inpecho.actif = false;			//V�rifier s'il reste toujours du stock � passer dans le canal	
		}	
	
	//iv) Fonction : pause ; arr�te les compteurs des canaux
	void pause(StaticVect<canal,taillecanal>& canaux) {
		int currentt = timems();
		for(int poscan=0; poscan<canaux.longueur; poscan++) canaux[poscan].pausedt = canaux[poscan].nxtt - currentt;			
	}
	void unpause(StaticVect<canal,taillecanal>& canaux) {
		int currentt = timems();
		for(int poscan=0; poscan<canaux.longueur; poscan++) canaux[poscan].nxtt = currentt + canaux[poscan].pausedt + canaux[poscan].delay * 5;					
	}
	
	//v) Fonction : overridecanal() ; vide le canal, en appliquant cependant les codes sp�ciaux s�lectionn�s qui s'y trouvent
	void overridecanal(StaticVect<canal,taillecanal>& canaux, int canpos, ouvrage& histoire, bibliotheque& biblio) {
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
		canaux[canpos].txt = "";      //Vider le canal
		canaux[canpos].actif = false;           //D�sactiver le canal
	}
	
	//vi) Fonction : integration ; ajoute un motif � un canal
	void integrationmanu(int chapitrepos, int motifpos, StaticVect<canal,taillecanal>& canaux, ouvrage& histoire, bibliotheque& biblio) {
		int currentt = timems();	
		//Overloader le canal si n�cessaire
		if(histoire.filmanu[chapitrepos][motifpos].override) overridecanal(canaux, histoire.filmanu[chapitrepos][motifpos].canal, histoire, biblio);
		//Choisir l'encha�nement � ins�rer dans le canal
		int sumprob = 0; StaticVect<int,10> vectprob;
		for(int posprob=0; posprob<histoire.filmanu[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {	//�valuer chaque probabilit�
			sumprob += histoire.filmanu[chapitrepos][motifpos].enchaineprob[posprob].eval(biblio); vectprob[posprob] = sumprob; 
		}
		int randval = randomnb(0,sumprob-1);  //Obtenir un integer al�atoire entre [0,sumprob[
		int choix; 
		for(int posprob=0; posprob<histoire.filmanu[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {
			if(randval<vectprob[posprob]) {choix = posprob; break;}
		}	
		//Ajouter le texte au canal
		canaux[histoire.filmanu[chapitrepos][motifpos].canal].txt += histoire.filmanu[chapitrepos][motifpos].codespeciauxdebut;   //Codes sp�ciaux d�but
		for(int posench=0; posench<histoire.filmanu[chapitrepos][motifpos].enchainement[choix].longueur; posench++) {
			canaux[histoire.filmanu[chapitrepos][motifpos].canal].txt += histoire.filmanu[chapitrepos][motifpos].maille[histoire.filmanu[chapitrepos][motifpos].enchainement[choix][posench]];
		}		
		canaux[histoire.filmanu[chapitrepos][motifpos].canal].txt += histoire.filmanu[chapitrepos][motifpos].codespeciauxfin;		//Codes sp�ciaux fin	
		//Updater le nxtt pour qu'il commence � partir de l'int�gration
		if(!canaux[histoire.filmanu[chapitrepos][motifpos].canal].actif) canaux[histoire.filmanu[chapitrepos][motifpos].canal].nxtt = timems();
		//Marquer le canal comme actif
		if(canaux[histoire.filmanu[chapitrepos][motifpos].canal].txt.length()>0) canaux[histoire.filmanu[chapitrepos][motifpos].canal].actif = true;
	}
	void integrationauto(int chapitrepos, int motifpos, StaticVect<canal,taillecanal>& canaux, ouvrage& histoire, bibliotheque& biblio) {
		int currentt = timems();	
		//Overloader le canal si n�cessaire
		if(histoire.filauto[chapitrepos][motifpos].override) overridecanal(canaux, histoire.filauto[chapitrepos][motifpos].canal, histoire, biblio);
		//Choisir l'encha�nement � ins�rer dans le canal
		int sumprob = 0; StaticVect<int,10> vectprob;
		for(int posprob=0; posprob<histoire.filauto[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {	//�valuer chaque probabilit�
			sumprob += histoire.filauto[chapitrepos][motifpos].enchaineprob[posprob].eval(biblio); vectprob[posprob] = sumprob; 
		}
		int randval = randomnb(0,sumprob-1);  //Obtenir un integer al�atoire entre [0,sumprob[
		int choix; 
		for(int posprob=0; posprob<histoire.filauto[chapitrepos][motifpos].enchaineprob.longueur; posprob++) {
			if(randval<vectprob[posprob]) {choix = posprob; break;}
		}	
		//Ajouter le texte au canal
		canaux[histoire.filauto[chapitrepos][motifpos].canal].txt += histoire.filauto[chapitrepos][motifpos].codespeciauxdebut;   //Codes sp�ciaux d�but
		for(int posench=0; posench<histoire.filauto[chapitrepos][motifpos].enchainement[choix].longueur; posench++) {
			canaux[histoire.filauto[chapitrepos][motifpos].canal].txt += histoire.filauto[chapitrepos][motifpos].maille[histoire.filauto[chapitrepos][motifpos].enchainement[choix][posench]];
		}		
		canaux[histoire.filauto[chapitrepos][motifpos].canal].txt += histoire.filauto[chapitrepos][motifpos].codespeciauxfin;		//Codes sp�ciaux fin
		canaux[histoire.filauto[chapitrepos][motifpos].canal].txt += "�m" + to_string(chapitrepos) + ';' + to_string(motifpos) +'�';		//Code sp�cial permettant d'enlever le status en cours du motif     //Faut convertir les int en string...
		//Updater le nxtt pour qu'il commence � partir de l'int�gration
		if(!canaux[histoire.filauto[chapitrepos][motifpos].canal].actif) canaux[histoire.filauto[chapitrepos][motifpos].canal].nxtt = timems();
		//Marquer le canal comme actif
		if(canaux[histoire.filauto[chapitrepos][motifpos].canal].txt.length()>0) canaux[histoire.filauto[chapitrepos][motifpos].canal].actif = true;
		//Marquer le motif comme "en cours"
		histoire.filauto[chapitrepos][motifpos].encours = true;     
	}
	
//------------------------------------------------------------------------------------------------------------------------------------------------------
//5) Fonctions de remplissage ais� des objets utilis�s
	
	//Contenant pour conserver tous les objets
	class univers {
	//Membres
	public:
		ouvrage histoire;
		bibliotheque biblio;
		StaticVect<canal,taillecanal> canaux;
		input inp;
		inputecho inpecho;
	//Constructeur
		univers() {};
	}; 
	
	//Fonction pour cr�er un nouveau rayon et le nommer
	void nvrayon(univers& monde, const string& str) {
		monde.biblio.rayon.ajoutvide();								//Passer au prochain rayon
		monde.biblio.nomrayon.ajout(str);
	}
	
	//Fonction pour cr�er un nouveau livre et le nommer
	void nvlivre(univers& monde, const string& str) {
		monde.biblio.rayon[monde.biblio.rayon.longueur-1].ajoutvide();		//Passer au prochain livre
		monde.biblio.nomlivre[monde.biblio.rayon.longueur-1].ajout(str); monde.biblio.modif(monde.biblio.rayon.longueur-1,monde.biblio.rayon[monde.biblio.rayon.longueur-1].longueur-1,0);		//Mettre 0 comme valeur par d�faut (par d�faut, tous les livres = FALSE)
	}
	
	//Fonction pour cr�er un nouveau canal et le nommer
	void nvcanal(univers& monde, const string& str) {
		monde.canaux.ajoutvide();
		monde.canaux[monde.canaux.longueur-1].nom = str;
	}
	
	//Fonction pour modifier le d�lai du canal
	void canaldelai(univers& monde, int val) {
		monde.canaux[monde.canaux.longueur-1].delay = val;
	}
	
	//Fonction pour modifier la vitesse du canal
	void canalvit(univers& monde, double val) {
		monde.canaux[monde.canaux.longueur-1].vit = val;
	}
	
	//Fonction pour cr�er un nouveau chapitre
	void nvchapt(univers& monde) {
		monde.histoire.filauto.ajoutvide();											//ATTENTION! ICI, LES CHAPITRES SONT TH�ORIQUEMENT S�PAR�S ENTRE MANUELS ET AUTOMATIQUES,
		monde.histoire.filmanu.ajoutvide();												//MAIS LE CODE LES TRAITE EN TOUT TEMPS COMME LA M�ME ENTIT�! LE GARDER EN T�TE!
	}
	
	//Fonction pour d�finir les conditions d'activation du chapitre
	void ccond(univers& monde, const string& str) {
		monde.histoire.cadenas[monde.histoire.filmanu.longueur-1].set(str,monde.biblio);
	}

	//Fonction pour "cr�er" un nouveau motif et le nommer (manuel)
	void mtitre(univers& monde, const string& str) {		
		int poschap = monde.histoire.filmanu.longueur-1;
		monde.histoire.filmanu[poschap].ajoutvide();			//Passer au prochain motif
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;		
		monde.histoire.filmanu[poschap][posmotif].titre = str;     //Conserver le titre, pour y r�f�rer au cas o� une m�me commande appelerait plusieurs motifs.
	} 
	//Fonction pour "cr�er" un nouveau motif et le nommer (automatique)
	void atitre(univers& monde, const string& str) {		
		int poschap = monde.histoire.filauto.longueur-1;
		monde.histoire.filauto[poschap].ajoutvide();			//Passer au prochain motif
		int posmotif = monde.histoire.filauto[monde.histoire.filauto.longueur-1].longueur-1;		
		monde.histoire.filauto[poschap][posmotif].titre = str;     //Conserver le titre, simplement parce que �a me tente.
	}
	
	//Fonction pour �cire le texte ("mailles") du motif (manuel)
	void mtexte(univers& monde, const string& str) {
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;			
		int strnb = str.length();		//Aller chercher la taille du string
		int debmaille = 0;				//Cr�er un compteur pour le d�but de la maille actuelle
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='�') {										
				if(countstr-debmaille>0) {
					monde.histoire.filmanu[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,countstr-1));
				} else monde.histoire.filmanu[poschap][posmotif].maille.ajout("");   
				debmaille = countstr+1;		//if(...) : �vite les intervalles [1,0] (� la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "��")
			}
		}
		monde.histoire.filmanu[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,strnb-1));		//Entrer la derni�re maille
		//Ajouter par d�faut un encha�nement lisant l'int�gralit� des mailles, dans l'ordre, avec une probabilit� de 1 (peut alors �tre �cras� par les commandes suivantes)
		monde.histoire.filmanu[poschap][posmotif].enchainement.ajoutvide();      //Cr�er le premier encha�nement
		for(int countmaille = 0; countmaille<monde.histoire.filmanu[poschap][posmotif].maille.longueur; countmaille++){
			monde.histoire.filmanu[poschap][posmotif].enchainement[0].ajout(countmaille);	
		}
		monde.histoire.filmanu[poschap][posmotif].enchaineprob.ajoutvide();      //Cr�er la premi�re probabilit�
		monde.histoire.filmanu[poschap][posmotif].enchaineprob[0].set("1",monde.biblio);	
	}																						
	//Fonction pour �cire le texte ("mailles") du motif (automatique)
	void atexte(univers& monde, const string& str) {
		int poschap = monde.histoire.filauto.longueur-1;
		int posmotif = monde.histoire.filauto[monde.histoire.filauto.longueur-1].longueur-1;			
		int strnb = str.length();		//Aller chercher la taille du string
		int debmaille = 0;				//Cr�er un compteur pour le d�but de la maille actuelle
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='�') {										
				if(countstr-debmaille>0) {
					monde.histoire.filauto[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,countstr-1));
				} else monde.histoire.filauto[poschap][posmotif].maille.ajout("");   
				debmaille = countstr+1;		//if(...) : �vite les intervalles [1,0] (� la place de [0,1]), et skippe seulement la maille si la maille est vide (ex: "��")
			}
		}
		monde.histoire.filauto[poschap][posmotif].maille.ajout(strintervalle(str,debmaille,strnb-1));		//Entrer la derni�re maille
		//Ajouter par d�faut un encha�nement lisant l'int�gralit� des mailles, dans l'ordre, avec une probabilit� de 1 (peut alors �tre �cras� par les commandes suivantes)
		monde.histoire.filauto[poschap][posmotif].enchainement.ajoutvide();      //Cr�er le premier encha�nement
		for(int countmaille = 0; countmaille<monde.histoire.filauto[poschap][posmotif].maille.longueur; countmaille++){
			monde.histoire.filauto[poschap][posmotif].enchainement[0].ajout(countmaille);	
		}
		monde.histoire.filauto[poschap][posmotif].enchaineprob.ajoutvide();      //Cr�er la premi�re probabilit�
		monde.histoire.filauto[poschap][posmotif].enchaineprob[0].set("1",monde.biblio);	
	}		
	
		
	//Fonction pour d�finir les encha�nements possibles (manuel)
	void mordre(univers& monde, const string& str) {
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;		
		int strnb = str.length();		//Aller chercher la taille du string
		int countordre = 0;				//Cr�er un compteur pour l'ordre
		int debnombre = 0;				//Cr�er un compteur d'indexation pour le d�but du nombre
		//Effacer les encha�nements d�j� existants (celles par d�faut)
		monde.histoire.filmanu[poschap][posmotif].enchainement[0].vide();        //Conserve quand m�me le fait qu'un premier encha�nement a �t� cr��
		monde.histoire.filmanu[poschap][posmotif].enchaineprob[0].clean();        //Conserve quand m�me le fait qu'une premi�re probabilit� a �t� cr��e    
		//Ajouter les encha�nements inscrits
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='-'||str[countstr]==';') {
				if(countstr-debnombre>0) {
					monde.histoire.filmanu[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
				} else {out("L'encha�nement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing � la position "); out(countstr); out(". Changer �a svp."); abort();}			
				if(str[countstr]=='-') {}
				if(str[countstr]==';') {countordre++; monde.histoire.filmanu[poschap][posmotif].enchainement.ajoutvide();}
				debnombre = countstr+1;
			}
		}
		monde.histoire.filmanu[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,strnb-1))-1);		//Entrer le dernier chiffre	
		//Ajouter par d�faut une probabilit� de 1 pour tous les encha�nements inscrits (peut alors �tre �cras� par la commande suivante)
		for(int countench = 0; countench<monde.histoire.filmanu[poschap][posmotif].enchainement.longueur; countench++){
			monde.histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("1",monde.biblio);	
		}		
	}																						
	//Fonction pour d�finir les encha�nements possibles (automatique)
	void aordre(univers& monde, const string& str) {
		int poschap = monde.histoire.filauto.longueur-1;
		int posmotif = monde.histoire.filauto[monde.histoire.filauto.longueur-1].longueur-1;		
		int strnb = str.length();		//Aller chercher la taille du string
		int countordre = 0;				//Cr�er un compteur pour l'ordre
		int debnombre = 0;				//Cr�er un compteur d'indexation pour le d�but du nombre
		//Effacer les encha�nements d�j� existants (celles par d�faut)
		monde.histoire.filauto[poschap][posmotif].enchainement[0].vide();        //Conserve quand m�me le fait qu'un premier encha�nement a �t� cr��
		monde.histoire.filauto[poschap][posmotif].enchaineprob[0].clean();        //Conserve quand m�me le fait qu'une premi�re probabilit� a �t� cr��e    
		//Ajouter les encha�nements inscrits
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='-'||str[countstr]==';') {
				if(countstr-debnombre>0) {
					monde.histoire.filauto[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,countstr-1))-1);			//La fonction stoi() transforme les strings en int
				} else {out("L'encha�nement \""); out(str); out("\" contient une valeur vide qui fait planter le parsing � la position "); out(countstr); out(". Changer �a svp."); abort();}			
				if(str[countstr]=='-') {}
				if(str[countstr]==';') {countordre++; monde.histoire.filauto[poschap][posmotif].enchainement.ajoutvide();}
				debnombre = countstr+1;
			}
		}
		monde.histoire.filauto[poschap][posmotif].enchainement[countordre].ajout(stoi(strintervalle(str,debnombre,strnb-1))-1);		//Entrer le dernier chiffre	
		//Ajouter par d�faut une probabilit� de 1 pour tous les encha�nements inscrits (peut alors �tre �cras� par la commande suivante)
		for(int countench = 0; countench<monde.histoire.filauto[poschap][posmotif].enchainement.longueur; countench++){
			monde.histoire.filauto[poschap][posmotif].enchaineprob[countench].set("1",monde.biblio);	
		}		
	}			
	
	
	//Fonction pour d�finir les probabilit�s associ�es avec chaque encha�nement (manuel)
	void mprob(univers& monde, const string& str){
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;		
		int strnb = str.length();		//Aller chercher la taille du string
		int debench = 0;				//Noter la position d'indexation du d�but de l'encha�nement
		int countench = 0;				//Position de l'encha�nement vis�
		//Effacer les probabilit�s d�j� existantes (celles par d�faut)
		for(int countench = 0; countench<monde.histoire.filmanu[poschap][posmotif].enchainement.longueur; countench++){
			monde.histoire.filmanu[poschap][posmotif].enchaineprob[countench].clean();				//Conserve le fait que les probabilit�s ont �t� cr��es en nombre �gal au nombre d'encha�nements
		}				
		//Ajouter les probabilit�s inscrites
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]==';') {
				if(countstr-debench>0){
					monde.histoire.filmanu[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,countstr-1),monde.biblio);
				} else monde.histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("0",monde.biblio); //Si deux ';' se suivent, mettre la probabilit� de l'encha�nement vide comme 0. �a lui apprendra.
				debench = countstr + 1; countench++;
			}
		}
		if(debench!=strnb) {		//Entrer le dernier chiffre
		monde.histoire.filmanu[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,strnb-1),monde.biblio);
		}
		while(countench++<monde.histoire.filmanu[poschap][posmotif].enchainement.longueur-1){             //Si moins de probabilit�s ont �t� inscrites qu'il n'y a d'encha�nements
			monde.histoire.filmanu[poschap][posmotif].enchaineprob[countench].set("0",monde.biblio);
		}
	}
	//Fonction pour d�finir les probabilit�s associ�es avec chaque encha�nement (automatique)
	void aprob(univers& monde, const string& str){
		int poschap = monde.histoire.filauto.longueur-1;
		int posmotif = monde.histoire.filauto[monde.histoire.filauto.longueur-1].longueur-1;		
		int strnb = str.length();		//Aller chercher la taille du string
		int debench = 0;				//Noter la position d'indexation du d�but de l'encha�nement
		int countench = 0;				//Position de l'encha�nement vis�
		//Effacer les probabilit�s d�j� existantes (celles par d�faut)
		for(int countench = 0; countench<monde.histoire.filauto[poschap][posmotif].enchainement.longueur; countench++){
			monde.histoire.filauto[poschap][posmotif].enchaineprob[countench].clean();				//Conserve le fait que les probabilit�s ont �t� cr��es en nombre �gal au nombre d'encha�nements
		}				
		//Ajouter les probabilit�s inscrites
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]==';') {
				if(countstr-debench>0){
					monde.histoire.filauto[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,countstr-1),monde.biblio);
				} else monde.histoire.filauto[poschap][posmotif].enchaineprob[countench].set("0",monde.biblio); //Si deux ';' se suivent, mettre la probabilit� de l'encha�nement vide comme 0. �a lui apprendra.
				debench = countstr + 1; countench++;
			}
		}
		if(debench!=strnb) {		//Entrer le dernier chiffre
		monde.histoire.filauto[poschap][posmotif].enchaineprob[countench].set(strintervalle(str,debench,strnb-1),monde.biblio);
		}
		while(countench++<monde.histoire.filauto[poschap][posmotif].enchainement.longueur-1){             //Si moins de probabilit�s ont �t� inscrites qu'il n'y a d'encha�nements
			monde.histoire.filauto[poschap][posmotif].enchaineprob[countench].set("0",monde.biblio);
		}
	}
	
	//Fonction pour d�finir les codes sp�ciaux appel�s au d�but du motif (manuel)
	void mdeb(univers& monde, const string& str){
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;		
		monde.histoire.filmanu[poschap][posmotif].codespeciauxdebut = str;
	}
	//Fonction pour d�finir les codes sp�ciaux appel�s au d�but du motif (automatique)
	void adeb(univers& monde, const string& str){
		int poschap = monde.histoire.filauto.longueur-1;
		int posmotif = monde.histoire.filauto[monde.histoire.filauto.longueur-1].longueur-1;		
		monde.histoire.filauto[poschap][posmotif].codespeciauxdebut = str;
	}
	
	//Fonction pour d�finir les codes sp�ciaux appel�s � la fin du motif (manuel)
	void mfin(univers& monde, const string& str){
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;
		monde.histoire.filmanu[poschap][posmotif].codespeciauxfin = str;
	}
	//Fonction pour d�finir les codes sp�ciaux appel�s � la fin du motif (automatique)
	void afin(univers& monde, const string& str){
		int poschap = monde.histoire.filauto.longueur-1;
		int posmotif = monde.histoire.filauto[monde.histoire.filauto.longueur-1].longueur-1;
		monde.histoire.filauto[poschap][posmotif].codespeciauxfin = str;
	}
	
		
		//ICI, '|' S�PARE LES SYNONYMES, '&' S�PARE LES GROUPES DE MOTS N�CESSAIRES, "[]" D�NOTE LES MOTS � EXCLURE ET "()" S�PARENT LES DIFF�RENTES FA�ONS DE LE DIRE
			//NOTE: LES MOTS � EXCLURE N'ONT PAS DE GROUPES DE MOTS, ILS N'ONT QUE DES SYNONYMES!
	//Fonction pour d�finir les combinaisons de mots qui appeleront le motif (manuel)
	void mcomm(univers& monde, const string& str){
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;
		int strnb = str.length();
		int posfac = 0;			//Position des diff�rentes fa�ons de dire la commande
		int posgr = 0;          //Position des groupes de mots n�cessaires
		int possyn = 0;			//Position des synonymes
		bool exclus = false;	//Marqueur pour les mots � exclure
		string mot;				//Mot � inclure/exclure dans la commande
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='('|str[countstr]=='[') {		
				if(str[countstr]=='(') {
					monde.histoire.filmanu[poschap][posmotif].commandes.inclus.ajoutvide();         //Noter qu'une nouvelle fa�on de dire la commande commence
					monde.histoire.filmanu[poschap][posmotif].commandes.exclus.ajoutvide();	
				} else if(str[countstr]=='[') exclus = true;
			}else {
				if(countstr==0) {
					monde.histoire.filmanu[poschap][posmotif].commandes.inclus.ajoutvide();         //Noter qu'une nouvelle fa�on de dire la commande commence
					monde.histoire.filmanu[poschap][posmotif].commandes.exclus.ajoutvide();								//Si la premi�re parenth�se est omise (par ex, lorsqu'il y a une seule fa�on de le dire)					
				}
				if(str[countstr]=='|'||str[countstr]=='&'||str[countstr]==')'||str[countstr]==']'){
					if(mot.length()>0&&!(mot.length()==1&&mot[0]==' ')) {		//Si un mot d'au moins une lettre et qui n'est pas seulement un espace a �t� sauvegard�				
						//Enregistrer le mot comme commande
						if(mot[0]==' ') mot = strintervalle(mot,1,mot.length()-1);		//Enlever les espaces en d�but et en fin de mot; permet d'espacer l'�criture des commandes au besoin
						if(mot[mot.length()]==' ') mot = strintervalle(mot,0,mot.length()-2);
						if(exclus) {monde.histoire.filmanu[poschap][posmotif].commandes.exclus[posfac].ajout(mot);		//Enregistrer le mot
						} else {
							if(monde.histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].longueur==0) monde.histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].ajoutvide();	//Noter qu'un nouveau groupe de mots commence
							monde.histoire.filmanu[poschap][posmotif].commandes.inclus[posfac][posgr].ajout(mot);
						}
						mot.clear();			//Vider le string de stockage temporaire
						//Interpr�ter le caract�re exact
						if(str[countstr]=='|') {						//Ne rien faire
						}else if(str[countstr]=='&') {posgr++; monde.histoire.filmanu[poschap][posmotif].commandes.inclus[posfac].ajoutvide();
						} else if(str[countstr]==')') {posgr=0; posfac++;
						} else if(str[countstr]==']') {exclus = false;
						}
					} 
				} else mot+=str[countstr];		//Ajouter la lettre si c'est un caract�re simple	
			}
		}
	}
	
	//Fonction pour d�finir les commandes exactes qui appeleront le motif (manuel)
	void mcommexact(univers& monde, const string& str){
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;		
		int strnb = str.length();
		int debmot = 0;			//Noter la position d'indexation du d�but du mot
		for(int countstr=0; countstr<strnb; countstr++){
			if(str[countstr]=='|') {
				if(countstr-debmot>0){ 
					monde.histoire.filmanu[poschap][posmotif].commandes.exact.ajout(strintervalle(str,debmot,countstr-1));
				} else monde.histoire.filmanu[poschap][posmotif].commandes.exact.ajout(""); //Si deux ';' se suivent, mettre *RIEN* comme commande exacte possible
				debmot = countstr + 1;
			}
		}	
		if(debmot!=strnb) monde.histoire.filmanu[poschap][posmotif].commandes.exact.ajout(strintervalle(str,debmot,strnb-1));		//Entrer le dernier mot
	}
	
	//Fonction pour d�finir les conditions sous lesquelles le motif pourra �tre appel� (manuel)
	void mcond(univers& monde, const string& str){
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;		
		monde.histoire.filmanu[poschap][posmotif].condition.set(str,monde.biblio);
	}
	//Fonction pour d�finir les conditions sous lesquelles le motif pourra �tre appel� (automatique)
	void acond(univers& monde, const string& str){
		int poschap = monde.histoire.filauto.longueur-1;
		int posmotif = monde.histoire.filauto[monde.histoire.filauto.longueur-1].longueur-1;		
		monde.histoire.filauto[poschap][posmotif].condition.set(str,monde.biblio);
	}
		
	//Fonction pour d�finir si le canal sera vid� d�s l'activation de ce motif (manuel)
	void mover(univers& monde, bool bl){
		int poschap = monde.histoire.filmanu.longueur-1;
		int posmotif = monde.histoire.filmanu[monde.histoire.filmanu.longueur-1].longueur-1;		
		monde.histoire.filmanu[poschap][posmotif].override = bl;
	}				
	//Fonction pour d�finir si le canal sera vid� d�s l'activation de ce motif (automatique)
	void aover(univers& monde, bool bl){
		int poschap = monde.histoire.filauto.longueur-1;
		int posmotif = monde.histoire.filauto[monde.histoire.filauto.longueur-1].longueur-1;		
		monde.histoire.filauto[poschap][posmotif].override = bl;
	}					
				
	/*		//EXEMPLE:
			mtitre(monde,"Je suis confortable");
			mtexte(monde,"Bien.�p6000� �Parfait.�p6000� �\n\n                   D�sirez-vous vous divertir�p1000�...?");
			mordre(monde,"1-3;1-2");
			mprob(monde,"1;1");
			mcomm(monde,"(Je|J' & suis|reste & confortable|bien install�|bien install�e|bien install�.e [ne suis pas|jamais]) (�a va|Correct)");
			mcond(monde,"Laure�debut&!Laure�confo");
			mdeb(monde,"�bLaure�actif=1��bLaure�confo=1��v0.8�");
			mfin(monde,"�bLaure�actif=0�")
	*/	 

//------------------------------------------------------------------------------------------------------------------------------------------------------
//6) Fonction AutoInterpret()
void AutoInterpret(StaticVect<canal,taillecanal>& canaux, bibliotheque& biblio, ouvrage& histoire, const fen& base, input& inp, memoire& mem) {
	
	//ATTENTION! 
				//ICI, Y'A QUELQUE CHOSE DONT JE NE SUIS PAS S�RE:
	/*
		C'est que: Si j'�value � CHAQUE FOIS qu'un code sp�cial se fait lire, j'ai une chance d'int�grer le m�me motif deux fois de suite, si le prochain code sp�cial lu
		n'est pas exactement celui qui emp�che le motif. 
			-Une premi�re solution serait de "disable" les motifs automatiques d�s leur lecture: ils seraient donc � usage unique.
			-Une deuxi�me solution serait d'utiliser un rayon de la biblioth�que pour "disable" (automatiquement) les motifs automatiques... et d'ensuite s'assurer que le
				message pour r�tablir leur fonctionnement soit lu: 
					soit en le mettant dans un autre canal que celui qui est utilis� (mais alors, il faudrait autant de canaux qu'il y a de motifs),
					soit en le mettant comme code sp�cial automatique � la fin du canal, mais QUI EST "LU" M�ME SI LE CANAL EST CLEAR�.
						En fait, �a semble �tre overall une bonne pratique de conserver des "codes sp�ciaux" arounds, qui sont lu m�me si le canal est overrid�.	 
	
				Deuxi�me solution, donc, celle de g�rer tout cet automatisme simplement par un rayon de la biblioth�que dont les noms sont automatiquement g�n�r�s, 
					et dont l'activation se trouve en dehors m�me du syst�me habituel de codes sp�ciaux.
					En fait... Je ne pense pas que j'aie r�ellement besoin d'un rayon de la biblioth�que.
					Ce serait beaucoup plus simple si l'information �tait simplement conserv�e dans un bool�en � M�ME LE MOTIF AUTOMATIQUE, non?
												C'est cette deuxi�me solution qui a �t� impl�ment�e.
	*/
	//Pour chaque chapitre
	for(int chapitrepos=0; chapitrepos<histoire.filmanu.longueur; chapitrepos++) { if(histoire.cadenas[chapitrepos].eval(biblio)) {			
		//Pour chaque motif dans l'histoire
		for(int motifpos=0; motifpos<histoire.filmanu[chapitrepos].longueur; motifpos++) {if(histoire.filauto[chapitrepos][motifpos].condition.eval(biblio)&&!histoire.filauto[chapitrepos][motifpos].encours) {
			integrationauto(chapitrepos,motifpos,canaux,histoire,biblio);            //Int�grer tout de suite le motif dans le canal	
		}}
	}}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
//7) Fonction LireCanal()
void LireCanal(StaticVect<canal,taillecanal>& canaux, int canpos, fen& base, memoire& mem, bibliotheque& biblio, ouvrage& histoire, input& inp) {
	//Updater le "next time"
	canaux[canpos].nxtt += canaux[canpos].delay;
	//Interpr�ter les "codes sp�ciaux" (�...�)
	if(canaux[canpos].txt[0]=='�'){		
		//D�terminer la longueur du code sp�cial
			int CodeSpecialLong = CodeSpecialLongueur(canaux[canpos].txt);			
		//Lire le code sp�cial		
			if(canaux[canpos].txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause � la lecture		
				double val = CodeSpecialExtractDouble(canaux[canpos].txt,CodeSpecialLong);       //Extraire le temps que durera la pause
				canaux[canpos].nxtt += round(val * canaux[canpos].vit);                    //Ajouter le temps d'attente        //round() est n�cessaire pour arrondir correctement					
			} else if(canaux[canpos].txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = CodeSpecialExtractDouble(canaux[canpos].txt,CodeSpecialLong);       //Extraire la nouvelle vitesse
				canaux[canpos].vit = val;
			} else if(canaux[canpos].txt[1]=='g'){		//'g' pour "gender" -> choisir le bon accord
																								 //S�lectionner le genre
				int genreselect;
				
				//S�LECTIONNER LE GENRE						//RESTE � FAIRE! 
														//PEUT-�TRE SIMPLEMENT R�SERVER LE PREMIER RAYON DE LA BIBLIOTH�QUE AUX GENRES?
				
				
				
				int genreactuel = 0; 
				int posdebut = 3; int posfin = CodeSpecialLong - 1;		//Valeurs par d�fauts
				for(int posSpecial=3;posSpecial<CodeSpecialLong; posSpecial++) {				 //D�limiter le bon accord				
					if(canaux[canpos].txt[posSpecial]==';') {
						genreactuel++;
						if(genreactuel==genreselect) posdebut = posSpecial + 1; else if(genreactuel==genreselect-1) posfin = posSpecial - 1;
					}
				}
				string temptxt;										//Ajouter le bon accord � la suite du code sp�cial (devient: Code sp�cial - accord - reste du canal
				temptxt  += strintervalle(canaux[canpos].txt,0,CodeSpecialLong); temptxt += strintervalle(canaux[canpos].txt,posdebut,posfin); temptxt += strintervalle(canaux[canpos].txt,CodeSpecialLong,canaux[canpos].txt.length()-1);				
				canaux[canpos].txt = temptxt;
				canaux[canpos].nxtt -= canaux[canpos].delay;									//Ajuster le "next time" pour supprimer le d�lai entre l'interpr�tation du code et la lecture de l'accord
			} else if(canaux[canpos].txt[1]=='b'){		//'b' pour "biblio" -> modifier la biblioth�que
				string nomrayon; string nomlivre; string val;
				int posSpecial = 2;
				while(canaux[canpos].txt[posSpecial] != '�') nomrayon += canaux[canpos].txt[posSpecial++]; 
				posSpecial++; while(canaux[canpos].txt[posSpecial] != '=') nomlivre += canaux[canpos].txt[posSpecial++];
				posSpecial++; while(canaux[canpos].txt[posSpecial] != '�') val += canaux[canpos].txt[posSpecial++];							
				biblio.modif(nomrayon,nomlivre,stoi(val));	
				AutoInterpret(canaux, biblio, histoire, base, inp, mem);      //V�rifier si un motif automatique doit �tre int�gr� aux canaux		
			} else if(canaux[canpos].txt[1]=='m'){		//'m' pour "motif" -> marquer le motif automatique comme n'�tant plus en cours			
				string poschap; string posmotif;
				int posSpecial = 2;
				while(canaux[canpos].txt[posSpecial] != ';') poschap += canaux[canpos].txt[posSpecial++]; 
				posSpecial++; while(canaux[canpos].txt[posSpecial] != '�') posmotif += canaux[canpos].txt[posSpecial++];
				histoire.filauto[stoi(poschap)][stoi(posmotif)].encours = false;    //D�signer le motif signal� comme n'�tant plus en cours
			}
		
							
			  //EN AJOUTER UN (code sp�cial) POUR PLACER LE CURSEUR � LA FIN DE LA CONSOLE	
			
			
				//AJOUTER AUSSI UN CODE SP�CIAL POUR OVERLOADER DES CANAUX
			
			
			   //AJOUTER AUSSI UN CODE SP�CIAL POUR ...?
			
				
			
		//Effacer le code sp�cial du canal
		canaux[canpos].txt = strintervalle(canaux[canpos].txt,CodeSpecialLong+1,canaux[canpos].txt.length()-1);
	} else {  //Interpr�ter le reste des caract�res (pas des codes sp�ciaux)
		//Dealer avec la situation o� on a � sauter une ligne (cr�er les lignes suppl�mentaires et updater les diverses positions)
			bool jump = false;
			if(canaux[canpos].txt[0]=='\n'|canaux[canpos].posx>=base.limtxtx-1) jump = true;     //base.limtxtx - 1 ; car c'est en integer, et canaux[canpos].posx commence � 0!
			if(jump) {	
				mem.newline(canaux[canpos].posy);                     //Introduit une nouvelle ligne � la suite de la position qui lui est fournie	
				//Updater le correctif de d�calage de la console par rapport � la m�moire
					if(base.refoule) base.consy++; else if(mem.frontline>base.limtxty) {base.refoule = true; base.consy++;} 						
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore satur�e: on pousse vers le bas!
						if(canaux[canpos].posy!=mem.frontline-1) {                             //S'il y a d'autres lignes � repousser vers le bas
							//R�-�crire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,canaux[canpos].posy+1);  //Mettre le curseur au d�but de la reconstruction
								for(int county = canaux[canpos].posy + 1 ; county <= mem.frontline ; county++) {   
									for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est satur�e: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "rel�guant ce qui y �tait d�j� vers le haut")
							curspos(0,canaux[canpos].posy-base.consy+1); for(int countx = 0; countx < base.limtxtx ; countx++) out(' '); 												
						//Tout r�-�crire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county <= canaux[canpos].posy; county++){             //base.consy : facteur de d�calage de la console
								for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}	
				//Updater les positions dans les autres canaux    //Parce que leur position dans la m�moire a boug� //la position dans la console est quant � elle g�r�e par base.consy
				for(int countcan = 0 ; countcan < canaux.fin ; countcan++) {
					if(countcan==canpos) continue;                                    //la m�moire refoule toujours vers le bas!
					if(canaux[countcan].posy > canaux[canpos].posy) canaux[countcan].posy++; else if(canaux[countcan].posy == canaux[canpos].posy) canaux[countcan].posy+=2;
				}       // == : Si deux canaux se situe sur la m�me ligne, le canal qui change de ligne va couper l'autre en deux, et le renvoyer apr�s sa propre ligne.    	        
				//Updater les positions dans le canal actuel
				if(canaux[canpos].txt[0]=='\n') {canaux[canpos].posx = -1;} else canaux[canpos].posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a chang� de ligne, mais �crire le prochain � la bonne place
				canaux[canpos].posy++;	  																					   //en y 		
			} else {canaux[canpos].posx++;}       //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caract�re       //� partir d'ici, les posx et posy sont la position du charact�re actuel (dans la m�moire)!		
		if(canaux[canpos].txt[0]!='\n') {
			curspos(canaux[canpos].posx,canaux[canpos].posy-base.consy) ; out(canaux[canpos].txt[0]);     //Inscrire dans la console
			mem.souvenir[canaux[canpos].posx][canaux[canpos].posy] = canaux[canpos].txt[0];   //Inscrire dans la m�moire			
		}	
		canaux[canpos].txt = strintervalle(canaux[canpos].txt,1,canaux[canpos].txt.length()-1);       //Effacer le caract�re du canal     	   
	}
	if(canaux[canpos].txt.length()==0) canaux[canpos].actif = false;			//V�rifier s'il reste toujours du texte � passer dans le canal
}	
					
          
         
//------------------------------------------------------------------------------------------------------------------------------------------------------
//8) Fonction : UserInputInterpret ; v�rifie si la commande entr�e correspond � une des actions actuellement autoris�e
	template<int Taille>
	void UserInputInterpret(StaticVect<char,Taille>& command, StaticVect<canal,taillecanal>& canaux, bibliotheque& biblio, ouvrage& histoire, const fen& base, input& inp, memoire& mem) {
		//Cr�er des compteurs
		StaticVect<int,20> bonchapitre;	  //Cr�er des StaticVect pour noter la position des motifs qui correspondent � la commande
		StaticVect<int,20> bonmotif;											//Taille arbitraire de 20; j'esp�re qu'aucune commande n'appelera simultann�ment 20 maillons
		StaticVect<bool,taillegroupes> groupebon; 	   	 //Cr�er un StaticVect pour noter si chaque groupe de mot est bon
		int diffpos; bool exactbon; int commpos; bool exactmauvais; 	//Cr�er les compteurs pour les expressions exactes
		int groupepos; int synpos; int motpos; int precedpos; bool inclusbon; bool exclusbon;	//Cr�er les compteurs pour les mots � inclure/exclure	

		//Pour chaque chapitre
		for(int chapitrepos=0; chapitrepos<histoire.filmanu.longueur; chapitrepos++) { if(histoire.cadenas[chapitrepos].eval(biblio)) {			
			//Pour chaque motif dans l'histoire
			for(int motifpos=0; motifpos<histoire.filmanu[chapitrepos].longueur; motifpos++) {if(histoire.filmanu[chapitrepos][motifpos].condition.eval(biblio)) {
				if(histoire.filmanu[chapitrepos][motifpos].commandes.ifexact) {	//Si une commande exacte est n�cessaire
					diffpos = 0; exactbon = false;
					while(diffpos<histoire.filmanu[chapitrepos][motifpos].commandes.exact.longueur&&!exactbon) {
						commpos = 0; exactmauvais = false;
						while(!exactmauvais&&commpos<command.longueur) {if(command[commpos]!=histoire.filmanu[chapitrepos][motifpos].commandes.exact[diffpos][commpos]) exactmauvais = true; else commpos++;}	
						if(exactmauvais==false) exactbon = true; else diffpos++;
					}
					if(exactbon)	{integrationmanu(chapitrepos,motifpos,canaux,histoire,biblio); return;}            //Int�grer tout de suite le bon motif dans le canal					
				} else {								//Si plusieurs mots cl�s doivent �tre pr�sents
					inclusbon = false; diffpos = 0;
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
									while(commpos<command.longueur&&!groupebon[groupepos]) {						//DONC, ICI, L'ORDRE EST IMPORTANT DANS LA COMMANDE. PARCE QU'ON PART DE LA POSITION PR�C�DENTE. CHANGER �A? GARDER �A?	
										//PUISQUE L'ORDRE EST IMPORTANT, LA CONVERSION EN MAJUSCULE NE SERA EFFECTU�E QUE POUR LE PREMIER GROUPE DE MOT (ET POUR LA PREMI�RE LETTRE DE LA COMMANDE)
										if(commpos==0&&groupepos==0&&motpos==0)	{			//Premi�re lettre de la commande
											if(command[commpos]==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos][motpos]||command[commpos]==majuscule(histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos][motpos])) {
											commpos++; motpos++; if(motpos==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos].length()) {groupebon[groupepos] = true; precedpos = commpos;}	
											} else {commpos++;}
										} else {                 //Toutes autres lettres																	
											if(command[commpos++]==histoire.filmanu[chapitrepos][motifpos].commandes.inclus[diffpos][groupepos][synpos][motpos++]) {
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
								while(commpos<command.longueur&&exclusbon) {		//Si le mot est retrouv�, la commande ne correspond pas au motif																			
									if(command[commpos++]==histoire.filmanu[chapitrepos][motifpos].commandes.exclus[diffpos][synpos][motpos++]) {
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
			}}
		}}
		//Maintenant, on a l'information sur quels motifs correspondent (sans expression exacte) � la commande
		if(bonmotif.longueur==0) {
			inp.accepted = false; 			
			return;
		} else if(bonmotif.longueur==1) {	
			inp.accepted = true; if(histoire.filmanu[bonchapitre[0]][bonmotif[0]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input					
			integrationmanu(bonchapitre[0],bonmotif[0],canaux,histoire,biblio); return;            //Int�grer le bon motif dans le canal
		} else {
			//D�terminer si la commande correspond au titre d'un canal
			int bonpos = 0; exactbon = false; 
			while(bonpos<bonmotif.longueur&&!exactbon) {
				exactmauvais = false; commpos = 0;
					while(!exactmauvais&&commpos<command.longueur) {if(command[commpos]!=histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre[commpos]) exactmauvais = true; else commpos++;}	
					if(exactmauvais==false) {
						exactbon = true; 	
						inp.accepted = true; if(histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].getbusy) inp.busy = true;							
						integrationmanu(bonchapitre[bonpos],bonmotif[bonpos],canaux,histoire,biblio); return;}            //Int�grer tout de suite le bon motif dans le canal	
			}	
			//Si l'ambiguit� demeure: mettre le jeu sur pause, et faire appara�tre les options	
			pause(canaux);
			chgcol("gris sombre"); curspos(0,0);		//Recopier tout le texte affich� dans la console, mais en gris fonc� (background)
			for(int county = base.consy ; county <= mem.frontline ; county++) {   
				for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);
			}			
			chgcol("blanc"); curspos(5,3); int cursorposy = 3;
			egrener("Vouliez-vous dire (recopiez la ligne qui correspond � votre choix) :",160);
			for(int bonpos=0; bonpos<bonmotif.longueur; bonpos++) {
				if(bonpos==bonmotif.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy); egrener("ou",120);}}
				cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy);; egrener(histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre,120);}
				if(bonpos==bonmotif.longueur-1) {cursorposy+=2; if(cursorposy<base.limtxty) {curspos(2,cursorposy); egrener("              ?",120);}}				
			}
			string reformulation;
			cin >> reformulation;
				//V�rifier de nouveau
				bonpos = 0; exactbon = false; 
				while(bonpos<bonmotif.longueur&&!exactbon) {
					exactmauvais = false; commpos = 0;
						while(!exactmauvais&&commpos<reformulation.length()) {if(reformulation[commpos]!=histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre[commpos]) exactmauvais = true; else commpos++;}	
						if(exactmauvais==false) {
							exactbon = true; 
							curspos(3,0); chgcol("gris sombre"); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][base.consy + 3]); chgcol("blanc");
							stop(800);
							curspos(3,2); egrener("Parfait.",220);		
							stop(1500);
							curspos(0,0); for(int county = base.consy ; county <= mem.frontline ; county++) {for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);}			
							unpause(canaux);
							inp.accepted = true; if(histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input							
							integrationmanu(bonchapitre[bonpos],bonmotif[bonpos],canaux,histoire,biblio); return;}            //Int�grer tout de suite le bon motif dans le canal	
				}				
			//Si l'ambiguit� persiste: le demander une derni�re fois
			curspos(3,0); chgcol("gris sombre"); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][base.consy + 3]); chgcol("blanc");
			curspos(3,3); egrener("Vouliez-vous dire (recopiez EXACTEMENT la ligne qui correspond � votre choix) :",200);
			cin >> reformulation;	
				//V�rifier de nouveau
				bonpos = 0; exactbon = false; 
				while(bonpos<bonmotif.longueur&&!exactbon) {
					exactmauvais = false; commpos = 0;
						while(!exactmauvais&&commpos<reformulation.length()) {if(reformulation[commpos]!=histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].titre[commpos]) exactmauvais = true; else commpos++;}	
						if(exactmauvais==false) {
							exactbon = true; 
							curspos(3,0); chgcol("gris sombre"); for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][base.consy + 3]); chgcol("blanc");
							stop(800);
							curspos(3,2); egrener("C'est bon.",220);		
							stop(1500);
							curspos(0,0); for(int county = base.consy ; county <= mem.frontline ; county++) {for(int countx = 0 ; countx < base.limtxtx ; countx++) out(mem.souvenir[countx][county]);}			
							unpause(canaux);
							inp.accepted = true; if(histoire.filmanu[bonchapitre[bonpos]][bonmotif[bonpos]].getbusy) inp.busy = true;		//Envoyer le bon message au gestionnaire d'Input
							integrationmanu(bonchapitre[bonpos],bonmotif[bonpos],canaux,histoire,biblio); return;}            //Int�grer tout de suite le bon motif dans le canal	
				}				
			//Si l'ambiguit� est insolvable
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
//9) Fonction UserInput()
void UserInput(input& inp, inputecho& inpecho, const fen& base, bibliotheque& biblio, StaticVect<canal,taillecanal>& canaux, ouvrage& histoire, memoire& mem) {
	if(_kbhit()){
	//i) Capter la lettre tap�e
	bool enter = false;
	char charkey; int intkey = _getch();                  		//Enregistrer quelle touche a �t� press�e
			if (intkey == 0 || intkey == -32 || intkey == 224) {      //La valeur est sp�ciale: elle n�cessite de la r�-examiner
				intkey = _getch();                              //Examiner une deuxi�me valeur pour identifier
				if(intkey == 75) {     								 				 //fl�che gauche : reculer dans la commande tap�e 
					if(inp.inputpos!=0) {
						if(inp.inputpos!=inp.commande.longueur) {
							curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						}          //Remettre en gris la position pr�c�dente
						inp.inputpos--;  
					}
				}
				else if (intkey == 77) {											 	 //fl�che droite : avancer dans la commande tap�e				
					if(inp.inputpos!=inp.commande.longueur) {
						curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]);	
						inp.inputpos++;		
					}			//Remettre en gris la position pr�c�dente
				} 
				else if (intkey == 72)  ;  											 //Fl�che du haut   ... Rien ne se passe?
				else if (intkey == 80)  ;  											 //Fl�che du bas    ... Rien ne se passe?
				else if (intkey == 83) {                                                //Delete : supprimer un caract�re de la commande actuelle
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
					curspos(0,base.limtxty); out("Vous avez entr� ESC, le programme se ferme donc."); abort(); 
				} else if(intkey == 13) {												 //Enter : envoyer la commande
					enter = true;
				} else if(intkey == 8) {                                                //Backspace : supprimer le caract�re pr�c�dent
					if(inp.inputpos!=0) {
						inp.inputpos--;
						inp.commande.supprposition(inp.inputpos);   
						curspos(inp.inputpos,base.limtxty);
						for(int pos=inp.inputpos; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);   
						out(' ');    					
					}
				
				
				
				
				//DEBUGGG	
				} else if(intkey==20) {														//Ctrl + t : Donne le status des conditions de chaque motif
					curspos(2,8); out("Voici les conditions des cha�nons:");
					for(int posmotif=0; posmotif<histoire.filmanu[0].longueur; posmotif++) {
						curspos(2,9+posmotif); out("     Cha�non "); out(posmotif); out("  :     ");
						histoire.filmanu[0][posmotif].condition.test(biblio);
					}
					//abort();


				//DEBUGGG	
				} else if(intkey==2) {														//Ctrl + b : Donne la valeur de chaque livre de la biblioth�que
					curspos(2,18); out("Voici les valeurs stock�es dans la biblioth�que:");
					int nombrelivres = 0;
					for(int posrayon=0; posrayon<biblio.nomrayon.longueur; posrayon++) {
						curspos(2,19+posrayon+nombrelivres); out("    "); out(biblio.nomrayon[posrayon]); out(" :   ("); out(biblio.nomlivre[posrayon].longueur); out(" rayons)");
						for(int poslivre=0; poslivre<biblio.nomlivre[posrayon].longueur; poslivre++) {
							nombrelivres++;
							curspos(2,19+posrayon+nombrelivres); out("                      "); out(biblio.nomlivre[posrayon][poslivre]); out(" : "); out(biblio.acces(posrayon,poslivre));
						}
					}
					//abort();
					
				
				//DEBUGGG	
				} else if(intkey==10) {														//Ctrl + j : Donne le texte inscrit dans le premier canal
					curspos(2,28); out("Voici le texte restant dans le premier canal : \"");
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
						curspos(inp.inputpos-1,base.limtxty);	                    
						for(int pos=inp.inputpos-1; pos<inp.commande.longueur; pos++) out(inp.commande[pos]);
						if(inp.commande.longueur==inpecho.commande.fin) inpecho.actif = false;                   //D�sactiver le canal d'�cho si la commande actuelle le d�passe
					}
						
								//BTW: FAUDRAIT AUSSI TOUT UN PAN DE CODE POUR G�RER LES COMMANDES TROP LONGUES, POUR FAIRE RECULER LE TEXTE
										//Pour l'instant, je restreint l'espace � la largeur de la console, simplement.
							
				}
			}	
		//Remettre la lettre s�lectionn�e en surbrillance
		if(inp.inputpos!=inp.commande.longueur) {chgcol("blanc"); curspos(inp.inputpos,base.limtxty); out(inp.commande[inp.inputpos]); chgcol(base.couleur);}
			
		//�valuer la commande		
		if(enter) {								//BTW: Faire changer la vitesse/fr�n�sie du clignotage avec la vitesse globale. Tu veux �a plus vite? �a va �tre plus agressant aussi!
			UserInputInterpret(inp.commande,canaux,biblio,histoire,base,inp,mem);
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
			inp.inputpos = 0; inp.commande.vide();                               //Nettoyer l'objet input			
		}	
	}
}     

//------------------------------------------------------------------------------------------------------------------------------------------------------
//10) Fonction jouer();
void jouer(univers& monde, fen& base, memoire& mem){
	int currentt;
	srand(timems());										// "setseed" de la fonction rand, pour ne pas avoir la "seed" par d�faut, qui est toujours la m�me
	while(true){				//� faire tout le temps:
		currentt = timems();		
		for(int canpos=0; canpos<=monde.canaux.longueur; canpos++) {if(monde.canaux[canpos].actif&&monde.canaux[canpos].nxtt<currentt) LireCanal(monde.canaux,canpos,base,mem,monde.biblio,monde.histoire,monde.inp);}  //Lire chaque canal, s'il est pr�t	
		if(monde.inpecho.actif&&monde.inpecho.nxtt<currentt) UserInputEcho(monde.inp,monde.inpecho,base);
		UserInput(monde.inp,monde.inpecho,base,monde.biblio,monde.canaux,monde.histoire,mem);	//Interpr�ter la touche jou�e		
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//11) Aire de tests
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit �tre d�fini � l'int�rieur du main() pour fonctionner!
	//x, y, width, height,
	fen base(600,30,500,500);                                           //Cr�e �galement l'objet dans lequel ces param�tres sont d�finis       
	memoire mem(base.limtxtx);

	//Cr�er l'objet o� tout est initi�
	univers monde;
		
		//Cr�er une biblioth�que
		nvrayon(monde,"Laure");
			nvlivre(monde,"actif");
			nvlivre(monde,"debut");
			nvlivre(monde,"confo");
			nvlivre(monde,"divertir");
			nvlivre(monde,"long");
				
		//Cr�er un canal
		nvcanal(monde,"narration");
		
		//D�buter un chapitre
		nvchapt(monde);
			ccond(monde,"1");        //Rendre le premier chapitre accessible tout le temps
	
			//Cr�er un maillon manuel
			mtitre(monde,"Commencer le jeu");		
			mtexte(monde,"Bienvenue dans mon ordinateur.\n��a fait plaisir de vous recevoir, vraiment.\n�J'esp�re que vous �tes bien install�.es.\n��tes-vous bien install�.es?� �tes-vous confortable?");				
			mordre(monde,"1-4;1-5;2-4;2-5;3-4;4-5");
			mprob(monde,"1;1;1;1;1;1");
			mcomm(monde,"(start|d�buter|commencer)");
			mcond(monde,"!Laure�debut");	
			mdeb(monde,"�bLaure�actif=1��bLaure�debut=1�");
			mfin(monde,"�bLaure�actif=0��p10000��bLaure�long=1�");
			mover(monde,0);	

			//Cr�er un maillon AUTOMATIQUE!!!!
			atitre(monde,"C'est long.");
			atexte(monde,"\n\n         Eh. Je t'ai parl�.e.�p2000�\n                   J'veux une r�ponse.");
			acond(monde,"Laure�long");
			adeb(monde,"�bLaure�actif=1��bLaure�long=0��v0.9�");
			afin(monde,"�bLaure�actif=0�");

			//Cr�er un maillon manuel
			mtitre(monde,"Je suis confortable");
			mtexte(monde,"\nBien.�p6000� �Parfait.�p600� �\n\n                   D�sirez-vous vous divertir�p1000�...?");
			mordre(monde,"1-3;1-2-3");
			mprob(monde,"1;1");
			mcomm(monde,"(je|j' & suis|reste & confortable|bien install� [ne suis pas|jamais]) (�a va|correct) (oui)");		//BTW, ici, install� inclut aussi install�e et install�.e (pas besoin de r�p�ter)
			mcond(monde,"Laure�debut&!Laure�confo");
			mdeb(monde,"�bLaure�actif=1��bLaure�confo=1��v0.8�");
			mfin(monde,"�bLaure�actif=0��p10000��bLaure�long=1�");
			mover(monde,1);
			
			//Cr�er un maillon manuel
			mtitre(monde,"Je veux me divertir");
			mtexte(monde,"\n\n\n\nZut�p2000�;�p2000� \n\n\n            J'ai bien peur que vous ne soyez pas � la bonne place.��v0.3�\n\n         �p4000�Too fucking bad.");		
			mordre(monde,"1;2");
			mprob(monde,"1;1");
			mcomm(monde,"(oui|�videmment|certainement|volontier|pourquoi pas|why not|d'accord) (veux|voudrais|aimerais|d�sire & cela|�a|bien)");
			mcond(monde,"Laure�confo&!Laure�divertir");
			mdeb(monde,"�bLaure�actif=1��bLaure�divertir=1��p1100�");
			mfin(monde,"�bLaure�actif=0�");	
			mover(monde,1);
			
		
	//Faire une boucle pour que les canaux s'expriment!
	jouer(monde,base,mem);		
		
	curspos(0,13);			//Mettre le curseur dans un bel endroit � la fin


}							
	
